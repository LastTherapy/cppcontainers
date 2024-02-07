LIBNAME := s21_matrix_oop.a
FLAGS :=-std=c++17 #-Werror -Wextra -Wall
SOURCES_TEST := $(wildcard tests/*.cc) main.cc
OBJECTS := $(SOURCES:.cpp=.o)
LDFLAGS := -lgtest



all:
	g++ $(FLAGS) $(SOURCES_TEST) $(LDFLAGS)
	./a.out



#	g++ -g -std=c++17 lib/*.cpp main.cpp -o main
#	./main

#%.o: %.cpp
#	g++ $(CFLAGS) $(LDFLAGS) -c $< -o $@

#s21_matrix_oop.a: $(OBJECTS)
#	ar rcs $(LIBNAME) $(OBJECTS)

test: clean
	g++  -g $(SOURCES_TEST) $(FLAGS) $(LDFLAGS) -o  test
	./test

clean:
	rm -f *.a lib/*.o  main test

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test