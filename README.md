# Photoshop
This repo for team in assigment 3 int Programming
## pseudo code of filter 3 (merge)
Taking the second filename
declare array merged_image[SIZE][SIZE]
do nested loop to pass on each pixel of the image 
each pixel becomes the average of the corresponding pixel in the first and the second image

## pseudo code of filter 6 (Darken and ligthen)
declare array adjusted_image[SIZE][SIZE]
input contrast
if contrast == 'D' or 'd'
do nested loop that make each pixel in the adjusted_image = 1/2 uploded_image

if contrast == 'L' or 'l'
do nested loop that make each pixel in the  adjusted_image = pow(image,0.8)+150 // this equation make it ligthen
