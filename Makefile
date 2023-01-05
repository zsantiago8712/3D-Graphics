build:
	cmake --build /Users/randymarsh/Developer/3D-Graphics/cmake-build-debug --target all -j 6


compile:
	cmake -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_MAKE_PROGRAM=ninja" -G Ninja -S /Users/randymarsh/Developer/3D-Graphics -B /Users/randymarsh/Developer/3D-Graphics/cmake-build-debug

run:
	./cmake-build-debug/3D-Graphics

clean:
	cmake --build /Users/randymarsh/Developer/3D-Graphics/cmake-build-debug --target clean -j 6


make compile_commands:
	rm compile_commands.json
	cp cmake-build-debug/compile_commands.json .

cbb:
	make clean;
	make build;
	make compile;
	make compile_commands;

