#ifndef tab1
#define tab1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print(int array[], int size);

void print_char(char array[], int size);

void read(int array[], int size);

int valeur_max(int array[], int size);

void swap_elt( int array[], int size, int i, int j );

void swap_elt_char( char array[], int size, int i, int j );

int occurrences( int array[], int size, int el );

int find_first( int array[ ], int size, int el );

int find_last( int array[ ], int size, int el );

void reverse( int array[ ], int size );
}

void rotate_right( int array[ ], int size );

void rotate_left( int array[ ], int size );

bool is_palindrome(int array[], int size);

void holland_flag(char array[], int size);

#endif
