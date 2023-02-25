#include "Mesh.hpp"
#include <LA/la.hpp>
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

float angle = 0.0f;
#define FOV 640

void process_node(const aiNode* node, const aiScene* scene, std::vector<hasbu::Vertex>& vertex);
hasbu::Vertex process_mesh(const aiMesh* mesh, const aiScene* scene);

namespace hasbu {

bool Mesh::load_model(std::vector<std::string_view> const& files_path)
{
    Assimp::Importer importer;

    for (auto const& file : files_path) {
        const aiScene* scene = importer.ReadFile(file.cbegin(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

        if (nullptr == scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "[ERROR::ASSIMP]: " << importer.GetErrorString();
            continue;
        }

        process_node(scene->mRootNode, scene, m_vertex);
    }
    return true;
}

void Vertex::update(la::vec3 const& camera_position, const unsigned int window_width, const unsigned int window_height)
{
    la::vec3 mesh_vertrices[3];
    la::vec3 transformed_vertex[3];

    const la::vec3 axis { 1.0f, 1.0f, 1.0f };
    const la::mat4 mat_rotation { la::rotate(la::mat4 {}, axis, la::to_radians(angle)) };
    m_numPoints = 0;

    angle += 0.60f;
    for (auto const& face : m_faces) {

        mesh_vertrices[0] = m_vertices[(int)face.x];
        mesh_vertrices[1] = m_vertices[(int)face.y];
        mesh_vertrices[2] = m_vertices[(int)face.z];

        // TRANSFORMATION (ROTATION)
        transformed_vertex[0] = la::vec3 { mat_rotation * la::vec4(mesh_vertrices[0], 1.0f) };
        transformed_vertex[1] = la::vec3 { mat_rotation * la::vec4(mesh_vertrices[1], 1.0f) };
        transformed_vertex[2] = la::vec3 { mat_rotation * la::vec4(mesh_vertrices[2], 1.0f) };

        // NOTE: This adjusnt the object to the camera, with out this you cant see anything
        transformed_vertex[0].z += 5;
        transformed_vertex[1].z += 5;
        transformed_vertex[2].z += 5;

        // TODO BACK FACE CULLING
        //  1) Find Vectors- (B-A) and (C-A)
        //  2) TAKE THEIR CORSS PRODUCT AND FIND PERPENDICULAR NORMAL "N"
        la::vec3 subs_res = transformed_vertex[1] - transformed_vertex[0];
        la::vec3 subs_res2 = transformed_vertex[2] - transformed_vertex[0];
        la::vec3 normal = la::cross(subs_res, subs_res2);

        subs_res = la::normalize(subs_res);
        subs_res2 = la::normalize(subs_res2);
        normal = la::normalize(normal);

        la::vec3 camera_rey = camera_position - transformed_vertex[0];

        float normal_camera = la::dot(normal, camera_rey);

        if (normal_camera > 0.0f) {
            //  PROJECTION

            if (m_points.size() <= m_numPoints) {
                m_points.emplace_back();
            }

            for (int k = 0; k < 3; k++) {

                // TODO PROJECTION ORTHOGONAL
                la::vec2 projected_points {
                    (transformed_vertex[k].x * FOV) / transformed_vertex[k].z,
                    (transformed_vertex[k].y * FOV) / transformed_vertex[k].z
                };

                projected_points.x += ((float)window_width / 2);
                projected_points.y += ((float)window_height / 2);
                m_points[m_numPoints][k] = projected_points;
            }
            m_numPoints++;
        }
    }
}

}

void process_node(const aiNode* node, const aiScene* scene, std::vector<hasbu::Vertex>& vertex)
{

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        vertex.push_back(process_mesh(mesh, scene));
    }

    // for (unsigned int i = 0; i < node->mNumChildren; i++) {
    //     process_node(node->mChildren[i], scene, vertex);
    // }
}

hasbu::Vertex process_mesh(const aiMesh* mesh, const aiScene* scene)
{
    hasbu::Vertex temp;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        const aiVector3D* pPos = &(mesh->mVertices[i]);
        temp.m_vertices.push_back(la::vec3 { pPos->x, pPos->y, pPos->z });
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        temp.m_faces.push_back(la::vec3 { face.mIndices[0], face.mIndices[1], face.mIndices[2] });
    }
    return temp;
}