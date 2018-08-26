game: include/*.h src/*cpp
	g++ src/*cpp -o game -std=c++11 -g
clean:
	rm game