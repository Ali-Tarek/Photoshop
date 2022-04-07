/**
 * FCAI - programming 1 - 2022 - Assignment 3
 * Program Name :  mian.cpp
 * Last Modification Date : 02/4/2022
 * Author1 and ID and Group:  Mohamed Wael Mohamed      20210361    S21
 * Author2 and ID and Group:  Ali Tarek Mohamed         20210245    S21
 * Author3 and ID anf Group:  Omar Mohamed Gamal        20210270    S21
 * Teaching Assistant:
 * Purpose: This is photoshop console app
 */

// include all libraries
#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;

// functions declarations
char displayMenu();
void load();
void save();
void applyFilter(int choice);
void blackWhite();
void Darken_and_Lighten_Image(char);
void merge();
void invert();
void flip(char direction);
void rotate(string degree);
void cpyToImage(unsigned char image[][SIZE]);

// image that will be process
unsigned char image[SIZE][SIZE];

// start of program
int main()
{
    // load image into 2d array
    load();

    while (true)
    {
        // pass choice of user to applyfilter
        applyFilter(displayMenu());
    }
}

// load image to 2d array in memory
void load()
{

    fstream file;
    char fileName[100];

    // loop until user enter valid image
    do
    {
        cout << "please enter file name of the image to process: ";
        cin >> fileName;

        strcat(fileName, ".bmp");
        // see if the image exists or not
        file.open(fileName);
    } while (!file);

    readGSBMP(fileName, image);
}

// create menu for user
char displayMenu()
{

    cout << "Please select a filter to apply or 0 to exit: \n";
    cout << "1- Black & white Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter\n";
    cout << "4- Flip Image\n";
    cout << "5- Darken and Lightern Image\n";
    cout << "6- Rotate Image\n";
    cout << "7- Detect Image Edges\n";
    cout << "8- Enlarge Image\n";
    cout << "9- Shrink Image\n";
    cout << "a- Mirror 1/2 Image\n";
    cout << "b- Shuffle Image\n";
    cout << "c- Blur Image\n";
    cout << "s- Save the image to a file\n";
    cout << "0- Exit\n";

    // filter to apply
    char choice;
    cout << ">> ";
    cin >> choice;

    return tolower(choice);
}

// call filter
void applyFilter(int choice)
{

    switch (choice)
    {
    case '1':
        blackWhite();
        break;

    case '5':
        char contrast;
        cout << "Contrast (D)arken or (L)ighten: ";
        cin >> contrast;
        Darken_and_Lighten_Image(contrast);
        break;
    case '0':
        cout << "GOODBYE :)\n";
        exit(0);
        break;
    case '4':
        char direction;
        cout << "Flip (H)orizontally or (V)ertically: "; // take direction from user
        cin >> direction;
        flip(direction);
        break;

    case '3':
        merge();
        break;
    case '2':
        invert();
        break;
    case '6':
    {
        string degree;
        cout << "Rotate (90), (180) or (270) degrees?: ";
        cin >> degree;
        rotate(degree);
    }
    break;
    case 's':
        save();
        break;
    default:
        cout << "Not available Filter\n";
        break;
        // filter to apply
        char choice;
        cout << ">> ";
        cin >> choice;
    }
}

void save()
{
    char file[100];
    cout << "Please enter target file name: ";
    cin >> file;
    cout << '\n';
    strcat(file, ".bmp");
    writeGSBMP(file, image);
}

// convert image to black and white image
void blackWhite()
{

    // calcualte average
    long long avg = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            avg += image[i][j];
        }
    }

    avg /= 256 * 256;

    unsigned char blackWhiteImage[SIZE][SIZE];

    // convert to black and white image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > avg)
            {
                blackWhiteImage[i][j] = 255;
            }
            else
            {
                blackWhiteImage[i][j] = 0;
            }
        }
    }

    cpyToImage(blackWhiteImage);
}


void Darken_and_Lighten_Image(char contrast)
{
    unsigned char adjusted_image[SIZE][SIZE]; // dorl means darken or ligthen

    if(contrast == 'D' || contrast == 'd') // darken the image
    {
        for(int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                adjusted_image[i][j] = 0.5 * image[i][j]; 
    }


    else if(contrast == 'L' || contrast == 'l')  // ligthen the image
    {
        for(int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                adjusted_image[i][j]=pow(image[i][j],0.8)+150; 
    }


    cpyToImage(adjusted_image);
}

void merge()
{
    fstream file;
    char fileName2[100];
    unsigned char image2[SIZE][SIZE];

    do
    {
        cout << "please enter file name of the second image that you want to merge: ";
        cin >> fileName2;

        strcat(fileName2, ".bmp");
        // see if the image exists or not
        file.open(fileName2);
    } while (!file);

    readGSBMP(fileName2, image2);

    unsigned char merged_image[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            merged_image[i][j] = (image[i][j] + image2[i][j]) / 2;
        
    cpyToImage(merged_image);
}



void flip(char direction)
{

    unsigned char flipImage[SIZE][SIZE];

    // flip vertical
    if (direction == 'V' || direction == 'v')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                flipImage[i][j] = image[255 - i][j];
            }
        }
    }
    else if (direction == 'H' || direction == 'h')
    { // flip horizontal
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                flipImage[i][j] = image[i][255 - j];
            }
        }
    }

    // apply filter to image
    cpyToImage(flipImage);
}

// copy image after filter to globall image
void cpyToImage(unsigned char filterImage[][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = filterImage[i][j];
        }
    }
}

// invert filter
void invert()
{
    unsigned char invertImage[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            invertImage[i][j] = 255 - image[i][j];
        }
    }

    cpyToImage(invertImage);
}

// rotate image by specific degree
void rotate(string degree)
{

    unsigned char rotatedImage[SIZE][SIZE];

    // rotate by 90
    if (degree == "90")
    {

        // transpose image matrix
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                rotatedImage[i][j] = image[j][i];
            }
        }
    }
    else if (degree == "180")
    { // rotate by 180

        flip('v');
        flip('h');
        return;
    }
    else if (degree == "270")
    {
        rotate("90");
        flip('h');
        return;
    }

    cpyToImage(rotatedImage);
}