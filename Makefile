CC = clang
CXXFLAGS = -std=c11 -Wall -g
LDFLAGS = -lSDL2

MKDIR_P = mkdir -p

APPNAME = render.out
SRCDIR = src
BIN = bin
OBJDIR = $(BIN)/obj
APPEXEC = $(BIN)/Render

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RM = rm
DELOBJ = $(OBJ)

all: $(APPEXEC)/$(APPNAME)


# Build the app
${APPEXEC}/${APPNAME}: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%.c | obj
	$(CC) $(CXXFLAGS) -o $@ -c $<

#Si no existe el directirio para los .o lo crea
obj:
	${MKDIR_P} ${BIN}
	${MKDIR_P} ${OBJDIR}
	${MKDIR_P} ${APPEXEC}


.PHONY: clean
clean:
	@echo "Cleaning up proyect ..."
	$(RM) $(DELOBJ);


run:
	./$(APPEXEC)/$(APPNAME)
