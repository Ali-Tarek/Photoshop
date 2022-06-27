/*
 * FCAI - programming 1 - 2022 - Assignment 3
 * Program Name :  mian.cpp
 * Last Modification Date : 02/4/2022
 * Author1 and ID and Group:  Mohamed Wael Mohamed      20210361    S21
 * Author2 and ID and Group:  Ali Tarek Mohamed         20210245    S21
 * Author3 and ID anf Group:  Omar Mohamed Gamal        20210270    S21
 * Teaching Assistant:  Abdulrahman Abdulmonem
 * Purpose: This is Photoshop console app on gray photos
 */

// include all libraries
#include <bits/stdc++.h>
#include "Functions-body.cpp"

using namespace std;

// start of program
int main()
{
    // load image into 2d array
    load();

    while (true)
    {
        applyFilter(displayMenu()); // pass choice of user to applyfilter
    }
}
