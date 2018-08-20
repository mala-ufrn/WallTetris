#include "../include/utils.h"

#include <time.h>
#include <stdlib.h>

bool Utils::init = false;

float Utils::randNum(int x) {
	int num;

	if (!init){
		srand(unsigned(time(0)));
		init = true;
	}

	return rand() % x;
}