all:
	g++ -std=c++17 main.cpp -o main.o -lSDL2 -lSDL2_image -ldl

clean:
	rm *.o