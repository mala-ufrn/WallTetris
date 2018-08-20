#include "../include/bash_cursor.h"

#include <iostream>
using std::cout;

void BashCursor::save() {
	//save cur and move to destination
	printf("\33[s");	
}

void BashCursor::resume() {
	printf("\33[u");
}

void BashCursor::move(const int x,const int y) {
	int i;
	for(i = 0; i < y; i++) {
		cout << "\33[2C";
	}
	for(i = 0; i < x; i++) {
		cout << "\33[1B";
	}
}