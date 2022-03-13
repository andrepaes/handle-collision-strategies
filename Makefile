LIBS=-lm
EXECUTAVEL=HashMap

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o
	g++ hash_map.cpp $(LIBS) -o $(EXECUTAVEL)

main.o: hash_map.cpp
	g++ -c hash_map.cpp


clean:
	rm -rf *.o $(EXECUTAVEL)


run: $(EXECUTAVEL)
	./$(EXECUTAVEL)

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./$(EXECUTAVEL)
