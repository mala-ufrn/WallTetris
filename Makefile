game: bin/*.o
	g++ src/*.cpp -o game -std=c++11 -g -lGL -lGLU -lglut
clean:
	rm game