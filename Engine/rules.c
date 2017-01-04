#include <stdio.h>
#include <stdlib.h>
#include "rules.h"

int getX(int c){
	return c >> 16;
}

int getY(int c){
	return c & 0xFFFF;
}

int getCoord(int x,int y){
	return x << 16 | y;
}

int main()
{
	return 0;
}
