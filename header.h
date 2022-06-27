#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;

#ifndef MY_HEADER_H
#define MY_HEADER_H

// functions' prototypes declarations
char displayMenu();
void load();
void save();
void cpyToImage(unsigned char image[][SIZE][RGB]);
void applyFilter(int choice);
void blackWhite();
void invert();
void merge();
void flip(char direction);
void rotate(string degree);
void Darken_and_Lighten_Image(char);
void shrink_image(string size);
void detect();
void blur();
void shuffle();
void cutImage(int quarter, unsigned char fillImage[][SIZE/2][RGB]);
void enlarge();
void mirror();


#endif