LIBS=-lm 
CFLAGS=-O0 -std=c++11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
EXECUTAVEL=HashMap

all: $(EXECUTAVEL)

$(EXECUTAVEL): hash_map.o
	g++ hash_map.o $(LIBS) -o $(EXECUTAVEL)

hash_map.o: hash_map.cpp
	g++ $(CFLAGS) -c hash_map.cpp


clean:
	rm -rf *.o $(EXECUTAVEL)


run: clean $(EXECUTAVEL)
	./$(EXECUTAVEL)

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./$(EXECUTAVEL)
