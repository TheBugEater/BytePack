CC_CPP = g++ 
CC_C = gcc

PROJECTDIR = BytePack
SOURCEDIR = $(PROJECTDIR)/Source
BUILDDIR = build
EXECUTABLEDIR = bin

INC =-I $(PROJECTDIR)/Include

CPP_Flags = -std=c++11

C_SOURCES = $(wildcard $(SOURCEDIR)/**/*.c)
CPP_SOURCES = $(wildcard $(SOURCEDIR)/**/*.cpp)

C_OBJECTS = $(C_SOURCES:.c=.o)
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)

EXECUTABLE = BytePack

all: compile

compile:
	@echo "Compiling C++ File" $<
	$(CC_CPP) $(CPP_Flags) $(INC) $(CPP_SOURCES) -o $(BUILDDIR)/$(EXECUTABLE)

clean:
	@echo "Cleaning Build Directories and Files..." $<
	@rm -R -f $(BUILDDIR)
	@rm -R -f $(EXECUTABLEDIR)

