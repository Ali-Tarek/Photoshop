#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;

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


// image that will be process
unsigned char image[SIZE][SIZE][RGB];

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
    cout << "7- Detect Image Edges\n";
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

    readRGBBMP(fileName, image);
}



void save()
{
    char file[100];
    cout << "Please enter target file name: ";
    cin >> file;
    cout << '\n';
    strcat(file, ".bmp");
    writeRGBBMP(file, image);
}

// copy image after filter to global image
void cpyToImage(unsigned char filterImage[][SIZE][RGB])
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < RGB; k++)
                image[i][j][k] = filterImage[i][j][k];

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
        {
            invert();
            break;
        }
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
            while(degree != "90" && degree != "180" && degree != "270")
            {
                cout << "Choose only 90, 180 or 270: ";
                cin >> degree;
            }
            rotate(degree);
            break;
        }

        case '7':
            detect();
            break;

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
            cout << "Not available Filter" << endl;
            break;
            // filter to apply
            char choice;
            cout << ">> ";
            cin >> choice;
        }

    }
}


void blackWhite()
{
    unsigned char blackWhiteImage[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {   
            int rgbSum = 0;

            for(int k = 0; k < RGB; k++)
                rgbSum += image[i][j][k];
            
            if(rgbSum  > (SIZE * 3) / 2)
                blackWhiteImage[i][j][0] = blackWhiteImage[i][j][1] = blackWhiteImage[i][j][2] = 255; 

            else
                blackWhiteImage[i][j][0] = blackWhiteImage[i][j][1] = blackWhiteImage[i][j][2] = 0;
        }
    }
  

    cpyToImage(blackWhiteImage);
}


void invert()
{
    unsigned char invertImage[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                invertImage[i][j][k] = 255 - image[i][j][k];
            }
        }
    }

    cpyToImage(invertImage);
}


// Merge two images
void merge()
{
    fstream file;
    char fileName2[100];
    unsigned char image2[SIZE][SIZE][RGB];

    do
    {
        cout << "Please enter name of image file to merge with: ";
        cin >> fileName2;

        strcat(fileName2, ".bmp");
        // see if the image exists or not
        file.open(fileName2);
    } while (!file);

    readRGBBMP(fileName2, image2);

    unsigned char merged_image[SIZE][SIZE][RGB];

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for(int k = 0; k < 3; k++)
                merged_image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
        
    cpyToImage(merged_image);
}

void flip(char direction)
{

    unsigned char flipImage[SIZE][SIZE][RGB];

    // flip vertical
    if (direction == 'V' || direction == 'v')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    flipImage[i][j][k] = image[255 - i][j][k];
                }
            }
        }
    }
    else if (direction == 'H' || direction == 'h')
    { // flip horizontal
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    flipImage[i][j][k] = image[i][255 - j][k];
                }
            }
        }
    }

    // apply filter to image
    cpyToImage(flipImage);
}

// Change the contrast of the image
void Darken_and_Lighten_Image(char contrast)
{
    unsigned char adjusted_image[SIZE][SIZE][RGB]{}; // dorl means darken or ligthen

    if(contrast == 'D' || contrast == 'd') // darken the image
    {
        for(int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < 3; k++)
                    adjusted_image[i][j][k] = 0.5 * image[i][j][k]; 
    }


    else if(contrast == 'L' || contrast == 'l')  // ligthen the image
    {
        for(int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < 3; k++)
                    adjusted_image[i][j][k] = pow(image[i][j][k],0.8)+150; 
    }

    cpyToImage(adjusted_image);
}

// rotate image by specific degree
void rotate(string degree)
{

    unsigned char rotatedImage[SIZE][SIZE][RGB];

    // rotate by 90
    if (degree == "90")
    {

        // transpose image matrix
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                for(int k = 0; k < 3; k++)
                    rotatedImage[i][j][k] = image[j][i][k];

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
    unsigned char shrinked_image[SIZE][SIZE][RGB];

    long long avg{};


    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            for(int k = 0; k < 3; k++)
                shrinked_image[i][j][k] = 255;



    if(size == "1/2")
    {
        long avg{};

        for(int i = 0, x = 0; i < SIZE / 2; i++)
        {
        

            for(int j = 0, y = 0; j < SIZE / 2; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    avg = (image[x][y][k] + image[x][y+1][k] + image[x+1][y][k]  + image[x+1][y+1][k]) / 4;
                    shrinked_image[i][j][k] = avg;
                }
                    y+=2;
            }
            x+=2;
        }
    }
    
    else if(size == "1/3")
    {
        long long avg{};

        for(int i = 0, x = 0; i < SIZE / 3; i++)
        {
        
            for(int j = 0, y = 0; j < SIZE / 3; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    avg = (image[x-1][y-1][k] + image[x-1][y][k] + image[x-1][y+1][k] + image[x][y-1][k] +  image[x][y][k] +  image[x][y+1][k] + image[x+1][y-1][k] +  image[x+1][y][k] + image[x+1][y+1][k]) / 9;
                    shrinked_image[i][j][k] = avg;
                }

                y+=3;
            }
            x+=3;
        }
    }

    else if(size == "1/4")
    {
        for(int i = 0, x = 0; i < SIZE / 4; i++)
        {
            for(int j = 0, y = 0; j < SIZE / 4; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    avg = (image[x][y][k] + image[x][y+1][k] + image[x][y+2][k] + image[x][y+3][k] + image[x+1][y][k] + image[x+1][y+1][k] + image[x+1][y+2][k] + image[x+1][y+3][k] + image[x+2][y][k] + image[x+2][y+1][k] + image[x+2][y+2][k] + image[x+2][y+3][k] + image[x+3][y][k] + image[x+3][y+1][k] + image[x+3][y][k] + image[x+3][y+3][k]) / 16;
                    shrinked_image[i][j][k] = avg;
                }
                y+=4;
            }
            x+=4;
        }
    }

    cpyToImage(shrinked_image);
}

void blur()
{
    unsigned char blurred_image[SIZE][SIZE][RGB]{};

    //move kernel
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                int avg = 0;

                // claculate avg for kernel
                for(int l = i; l < i + 7; l++)
                    for(int m = j; m < j + 7; m++)
                        avg += image[l][m][k];

                avg /= 49;

                // update center of kernel in blurred image
                blurred_image[i][j][k] = avg;
            }
        }
    }

    
    cpyToImage(blurred_image);

}

void detect(){

    unsigned char detectedImage[SIZE][SIZE][RGB];

    // move kernel
    for(int i=0; i<SIZE-2; i++)
    {
        for(int j=0; j<SIZE-2; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                int gy = ((image[i][j][k]*-1) + (image[i][j+2][k]*1) + (image[i+1][j][k]*-2) + (image[i+1][j+2][k]*2) + (image[i+2][j][k] *-1) + (image[i+2][j+2][k]*1));
                int gx = ((image[i][j][k]*-1) + (image[i][j+1][k]*-2) + (image[i][j+2][k]*-1) + (image[i+2][j][k]*1) + (image[i+2][j+1][k] *2) + (image[i+2][j+2][k]*1));
                int total = sqrt(pow(gy, 2)+pow(gx, 2));
                detectedImage[i][j][k] = total;
            }
        }
    }

    cpyToImage(detectedImage);
    invert();

}


void enlarge()
{

    int quarter = 0; 
       
    // validate user input
    while ( quarter > 4 || quarter < 1)
    {
        // take quarter pos from user
         cout << "Which quarter to enlarge 1, 2, 3 or 4 ? ";
         cin >> quarter;
    }

    
    unsigned char quarterImage[SIZE/2][SIZE/2][RGB];


    cutImage(quarter, quarterImage);


    for(int i=0, rowIndex =0; i<SIZE/2; i++)
    {
        for(int j=0, colIndex=0; j<SIZE/2; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                // duplicate pixel 
                image[rowIndex][colIndex][k] = quarterImage[i][j][k];
                image[rowIndex+1][colIndex][k] = quarterImage[i][j][k];
                image[rowIndex][colIndex+1][k] = quarterImage[i][j][k];
                image[rowIndex+1][colIndex+1][k] = quarterImage[i][j][k];
                
            }
            colIndex += 2;
            
        }
        rowIndex += 2;
        
    }
}


// cut image to corrspond quarter and fill the image given
void cutImage(int quarter, unsigned char fillImage[][SIZE/2][RGB])
{
    // corrdinate to cut image
    int startRow, endRow, startCol, endCol;

    // choose start and end for row and col based on quarter
    startRow    = quarter == 1 || quarter == 2 ? 0 : SIZE / 2;
    endRow      = quarter == 1 || quarter == 2 ? SIZE / 2 : SIZE;
    startCol    = quarter == 1 || quarter == 3 ? 0 : SIZE / 2 ;
    endCol      = quarter == 1 || quarter == 3 ? SIZE / 2 : SIZE; 

    // fill given image
    for(int i=startRow, rowIndex=0; i<endRow; i++)
    {
        for(int j=startCol, colIndex=0; j<endCol; j++)
        {
            for(int k = 0; k < RGB; k++)
            {
                fillImage[rowIndex][colIndex][k] = image[i][j][k];
            }
                colIndex++; // increment col in fillImage

        }
        rowIndex++; // increment row in fillImage
    }
}



// shuffle the order of four quarters of image 
void shuffle()
{

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
    vector<unsigned char[SIZE/2][SIZE/2][RGB]>quarterImages(4);

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

            for(int k=0; k<SIZE/2; k++)
            {
                for(int m = 0; m < RGB; m++)
                {
                    image[rowIndex][colIndex][m] = quarterImages[i][j][k][m];
                }
                colIndex++;
            }
            rowIndex++;
        }
    }

}