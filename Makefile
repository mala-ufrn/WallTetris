game: include/*.h src/*cpp
	g++ src/*cpp -o game -std=c++11 -pthread -g
clean:
	rm game