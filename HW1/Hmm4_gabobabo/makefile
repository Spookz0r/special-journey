CC = g++
#CC = clang
FLAGS = -std=gnu++11 -Wall -pedantic
CPP_FILES := $(wildcard src/*.cpp)
LINKER_FLAGS =-Ofast
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
main.o: $(OBJ_FILES)
	$(CC) $(FLAGS) -o $@ $^ $(LIBRARIES) $(INCLUDES) $(LINKER_FLAGS)
obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $< $(LIBRARIES) $(INCLUDES) $(LINKER_FLAGS)
clean:
	rm -f obj/*.o *.out
