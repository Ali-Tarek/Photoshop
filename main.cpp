/*
 * FCAI - programming 1 - 2022 - Assignment 3
 * Program Name :  mian.cpp
 * Last Modification Date : 02/4/2022
 * Author1 and ID and Group:  Mohamed Wael Mohamed      20210361    S21
 * Author2 and ID and Group:  Ali Tarek Mohamed         20210245    S21
 * Author3 and ID anf Group:  Omar Mohamed Gamal        20210270    S21
 * Teaching Assistant:  Abdulrahman Abdulmonem
 * Purpose: This is photoshop console app
 */

// include all libraries
#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;

// functions' prototypes declarations
char displayMenu();
void load();
void save();
void cpyToImage(unsigned char image[][SIZE]);
void applyFilter(int choice);
void blackWhite();
void invert();
void merge();
void flip(char direction);
void rotate(string degree);
void Darken_and_Lighten_Image(char);
void shrink_image(string size);
void blur();
void shuffle();
void cutImage();
void enlarge();


// image that will be process
unsigned char image[SIZE][SIZE];

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

// create menu for user
char displayMenu()
{
    cout << "Please select a filter to apply or 0 to exit: \n";
    cout << "1- Black & white Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter\n";
    cout << "4- Flip Image\n";
    cout << "5- Darken and Lighten Image\n";
    cout << "6- Rotate Image\n";
    cout << "8- Enlarge Image\n";
    cout << "9- Shrink Image\n";
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



void save()
{
    char file[100];
    cout << "Please enter target file name: ";
    cin >> file;
    cout << '\n';
    strcat(file, ".bmp");
    writeGSBMP(file, image);
}

// copy image after filter to global image
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

// call filter
void applyFilter(int choice)
{
    switch (choice)
    {
        case '0':
            cout << "GOODBYE :)\n";
            exit(0);
            break;

        case '1':
            blackWhite();
            break;

        case '2':
            invert();
            break;

        case '3':
            merge();
            break;

        case '4':
            char direction;
            cout << "Flip (H)orizontally or (V)ertically: "; // take direction from user
            cin >> direction;
            flip(direction);
            break;

        case '5':
            char contrast;
            cout << "Contrast (D)arken or (L)ighten: ";
            cin >> contrast;
            while(contrast != 'D' && contrast != 'd' && contrast != 'L' && contrast != 'l')
                {
                    cout << "Choose only D or L: ";
                    cin >> contrast;
                }
            Darken_and_Lighten_Image(contrast);
            break;

        case '6':
        {
            string degree;
            cout << "Rotate (90), (180) or (270) degrees?: ";
            cin >> degree;
            rotate(degree);
            break;
        }
        case '8':
            enlarge();
            break;
        
        case '9':
        {
            string size;
            cout << "Shrink to (1/2), (1/3) or (1/4)? ";
            cin >> size;
            while(size != "1/2" && size != "1/3" && size != "1/4")
            {
                cout << "Choose (1/2), (1/3) or (1/4) only: ";
                cin >> size;
            }
            shrink_image(size);
            break;
        }
        case 'b':
            shuffle();
            break;
        
        case 'c':
            blur();
            break;

        case 's':
            save();
            break;

        default:
        {
            cout << "Not available Filter\n";
            break;
            // filter to apply
            char choice;
            cout << ">> ";
            cin >> choice;
        }

    }
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

// invert the image
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


// Merge two images
void merge()
{
    fstream file;
    char fileName2[100];
    unsigned char image2[SIZE][SIZE];

    do
    {
        cout << "Please enter name of image file to merge with: ";
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

// Change the contrast of the image
void Darken_and_Lighten_Image(char contrast)
{
    unsigned char adjusted_image[SIZE][SIZE]{}; // dorl means darken or ligthen

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

void shrink_image(string size){
    unsigned char shrinked_image[SIZE][SIZE];

    long long avg{};


    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            shrinked_image[i][j] = 255;



    if(size == "1/2"){
        long avg{};

        for(int i = 0, x = 0; i < SIZE / 2; i++)
        {

            for(int j = 0, y = 0; j < SIZE / 2; j++)
            {
                avg = (image[x][y] + image[x][y+1] + image[x+1][y]  + image[x+1][y+1]) / 4;
                shrinked_image[i][j] = avg;
                y+=2;
            }
            x+=2;
        }
    }else if(size == "1/3"){
        long avg{};

        for(int i = 0, x=1; i < SIZE / 3; i++)
        {
         
            for(int j = 0, y=1; j < SIZE / 3; j++)
            {
            avg = (image[x-1][y-1] + image[x-1][y] + image[x-1][y+1] + image[x][y-1] +  image[x][y] +  image[x][y+1] + image[x+1][y-1] +  image[x+1][y] + image[x+1][y+1]) / 9;
                shrinked_image[i][j] = avg;
                y+=3;
            }
            x+=3;
        }
    
    }
    // else if(size == "1/4")
    // {
    //     for(int i = 1; i < SIZE / 4; i+=2)
    //     {
    //         for(int j = 1; j < SIZE / 4; j+=2)
    //         {

    //         }
    //     }
    // }

    cpyToImage(shrinked_image);
}

void blur()
{
    unsigned char blurred_image[SIZE][SIZE]{};

    //move kernel
    for(int i = 0; i < SIZE-2; i++){
        for(int j = 0; j < SIZE-2; j++){
            
            int avg = 0;

            // claculate avg for kernel
            for(int k=i; k<i+3; k++){
                for(int m=j; m<j+3; m++){
                    avg += image[k][m];
                }
            }

            avg /= 9;

            // update center of kernel in blurred image
            blurred_image[i][j] = avg;
        }
    }

    
    cpyToImage(blurred_image);

}
// cut image to corrspond quarter and fill the image given
void cutImage(int quarter, unsigned char fillImage[][SIZE/2]){
    // corrdinate to cut image
    int startRow, endRow, startCol, endCol;

    // choose start and end for row and col based on quarter
    startRow    = quarter == 1 || quarter == 2 ? 0 : SIZE / 2;
    endRow      = quarter == 1 || quarter == 2 ? SIZE / 2 : SIZE;
    startCol    = quarter == 1 || quarter == 3 ? 0 : SIZE / 2 ;
    endCol      = quarter == 1 || quarter == 3 ? SIZE / 2 : SIZE; 


    // fill given image
    for(int i=startRow, rowIndex=0; i<endRow; i++){
        for(int j=startCol, colIndex=0; j<endCol; j++){

            fillImage[rowIndex][colIndex] = image[i][j];
        
        colIndex++; // increment col in fillImage
        }
        rowIndex++; // increment row in fillImage
    }
    
}

// enlarge quarter from image
void enlarge(){

    int quarter = 0; 
       
    // validate user input
    while ( quarter > 4 || quarter < 1){
        // take quarter pos from user
         cout << "Which quarter to enlarge 1, 2, 3 or 4 ? ";
         cin >> quarter;
    }

    
    unsigned char quarterImage[SIZE/2][SIZE/2];


    cutImage(quarter, quarterImage);


    for(int i=0, rowIndex =0; i<SIZE/2; i++){
        for(int j=0, colIndex=0; j<SIZE/2; j++){

            // duplicate pixel 
            image[rowIndex][colIndex] = quarterImage[i][j];
            image[rowIndex+1][colIndex] = quarterImage[i][j];
            image[rowIndex][colIndex+1] = quarterImage[i][j];
            image[rowIndex+1][colIndex+1] = quarterImage[i][j];

            colIndex += 2;
        }

        rowIndex += 2;
    }

}

// shuffle the order of four quarters of image 
void shuffle(){

    // order of suffle
    int order[4];    

    // get order from user
    cout << "New order of quarters ? ";
    for(int i=0; i<4; i++){
        cin >> order[i];
        if( order[i] > 4 || order[i] < 1){
            cout << "reject\n";
            return;
        }
    }

    // all quarters of image
    vector<unsigned char[SIZE/2][SIZE/2]>quarterImages(4);

    // get quarters of image
    for(int i=0; i<quarterImages.size(); i++){
        cutImage(order[i], quarterImages[i]);
    }

    int rowIndex, colIndex;
    for(int i=0; i<4; i++){ // loop on quartersImage

        // avoid overflow 
        rowIndex = i == 0 || i == 1  ? 0 : SIZE / 2;

        //fiil image with quarter in order
        for(int j=0; j<SIZE/2; j++){

            // avoid overflow
            colIndex = i == 0 || i == 2  ? 0 : SIZE / 2;

            for(int k=0; k<SIZE/2; k++){
                image[rowIndex][colIndex] = quarterImages[i][j][k];
                colIndex++;
            }
            rowIndex++;
        }
    }


}
