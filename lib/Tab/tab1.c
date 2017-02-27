#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Liste/lst_double.h"

typedef int bool;

/*void print(int array[], int size){
int i;
for(i = 0;i<size;i++){
printf("%d\n",array[i]);
}
return;
}*/

void print_char(char array[], int size){
int i;
for(i = 0;i<size;i++){
printf("%c",array[i]);
}
puts("");
return;
}

void read1(int array[], int size){
int i;
for(i = 0;i<size;i++){
scanf("%d",&array[i]);
}
return;
}

int valeur_max(int array[], int size){
int i;
int max = 0;
for(i = 0;i<size;i++){
	if(max<array[i]){
		max = array[i];
	}
}
return max;
}

void swap_elt( Liste* array[], int i, int j ){
	Liste* save = array[i];
	array[i] = array[j];
	array[j] = save;
	return;
}

void swap_elt_char( char array[], int size, int i, int j ){
int save = array[i];
array[i] = array[j];
array[j] = save;
return;
}

int occurrences( int array[], int size, int el ){
int i;
int count = 0;
for(i = 0;i<size;i++){
	if(array[i] == el){
		count++;
	}
}
return count;
}

int find_first( int array[ ], int size, int el ){
int i;
for(i = 0;i<size;i++){
	if(array[i] == el){
		return i;
	}
}
return -1;
}

int find_last( int array[ ], int size, int el ){
int i;
for(i = size;i>=0;i--){
	if(array[i] == el){
		return i;
	}
}
return -1;
}

void reverse( int array[ ], int size ){
int i;
for(i = 0;i<size;i++){
	int save = array[size-i];
	array[size-i] = array[i];
	array[i] = save;
}
return;
}

void rotate_right( int array[], int size ){
	int i;
	int save = array[size-1];
	int tab[size];
	memcpy(tab,array,sizeof(tab));
	for(i = 0;i<size-1;i++){
		array[i+1] = tab[i];
	}
	array[0] = save;
	return;
}

void rotate_left( int array[ ], int size ){
int i;
int save = array[0];
int tab[size];
memcpy(tab,array,sizeof(tab));
for(i = 0;i<size-1;i++){
array[i] = tab[i+1];
}
array[size-1] = save;
return;
}

bool is_palindrome(int array[], int size){
int i;
for(i = 0;i<size;i++){
	if(array[i] != array[size-1-i]){
		return 0;
	}
}
return 1;
}

void holland_flag(char array[], int size){
int r = 0;
int w = 0;
int b = size-1;
//Tri du tableau
while(w<b){
switch (array[w]){
	case 'W':
	w++;
	break;
	case 'R':
	swap_elt_char(array,size,r,w);
	w++;r++;
	break;
	case 'B':
	swap_elt_char(array,size,b,w);
	b--;
	break;
	}
	print_char(array,30);
}
}
