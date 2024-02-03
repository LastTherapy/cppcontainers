LIBNAME := s21_matrix_oop.a
FLAGS :=-std=c++17 #-Werror -Wextra -Wall
SOURCES := $(wildcard lib/*cpp)
OBJECTS := $(SOURCES:.cpp=.o)
LDFLAGS := -lgtest



all:
	g++ lib/list.cpp
	./a.out



#	g++ -g -std=c++17 lib/*.cpp main.cpp -o main
#	./main

#%.o: %.cpp
#	g++ $(CFLAGS) $(LDFLAGS) -c $< -o $@

#s21_matrix_oop.a: $(OBJECTS)
#	ar rcs $(LIBNAME) $(OBJECTS)

test: clean
	g++  test.cpp $(FLAGS) $(LDFLAGS) -o test
	./test

clean:
	rm -f *.a lib/*.o  main test

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test