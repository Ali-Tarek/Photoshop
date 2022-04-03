/**
 * FCAI - programming 1 - 2022 - Assignment 3
 * Program Name :  mian.cpp
 * Last Modification Date : 02/4/2022
 * Author1 and ID and Group:  Mohamed Wael Mohamed  20210361    S21
 * Author2 and ID and Group:  Ali Tarek             20210245    S21
 * Author3 and ID anf Group:  Omar Mohamed          20210270     S21    
 * Teaching Assistant:
 * Purpose: This is photoshop console app
 */

// include all libraries
#include <bits/stdc++.h>


using namespace std;

// library  for manipulate images
#include "bmplib.cpp"

//functions declarations
void Display_menu();
void load();
void save();


// image that will be process
unsigned char image[SIZE][SIZE];

int main(){
    load();
}

// load image to 2d array in memory
void load(){

    char fileName[100]; 
    fstream file;

    // loop until user enter valid image 
    do{
        cout << "Enter picture: ";
        cin >> fileName;

        //append bmp to the end of filename 
        strcat(fileName, ".bmp");
        //see if the image exists or not
        file.open(fileName);
    }while(!file);
        
    readGSBMP(fileName, image);    
}
