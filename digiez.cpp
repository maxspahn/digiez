#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"
#include <iostream>
#include "EasyBMP.h"

using namespace std;

/// @brief Get the color of a given number of pixel and a given image.
//
/// @param image 	The bitmap of the image to be evaluated.
/// @param div 		The number of division in every direction.
/// @param a 		Number of pixels in between two pixels that are evaluated, horizontal direction.
/// @param b 		Number of pixels in between two pixels that are evaluated, vertical direction.
//
/// @return The values of all the pixeles evaluated and every color.

int* getPixels(BMP image,int div,  int a, int b){
	int* values = new int[div*div*3];
	int i = 0;
	for (int c = 1; c <= div; c++) {
		for (int d = 1; d <= div; d++) {
			values[i]   = image(c*a, d*b)->Red;
			values[i+1] = image(c*a, d*b)->Green;
			values[i+2] = image(c*a, d*b)->Blue;
			i+=3;
		}
	}
	return values;

};

/// @brief Get the values of all colors of every pixel for all the images.
//
/// @param images 	A list of all the images to be evaluated.
/// @param div 		Number of division on one direction.
/// @param a 		Number of pixels in between two pixels that are evaluated, horizontal direction.
/// @param b 		Number of pixels in between two pixels that are evaluated, vertical direction.
/// @param nbIm 	Number of imagese in the list.
//
/// @return A two dimensional array with all the values.

int** getAllPixels(BMP * images, int div, int a, int b, int nbIm){
	int** colors = new int*[nbIm];
	for (int i = 0; i < nbIm; i++) {
		colors[i] = getPixels(images[i], div, a, b);
	}
	return colors;
};

/// @brief Compute the sum of differences for all the pixels between two images.
//
/// @param nbPnt 	Number of points to be evaluated.
/// @param first 	Array containing the color values for the first image.
/// @param second 	Array containing the color values for the second image.
//
/// @return The sum of differences.

int getSumDiff(int nbPnt, int* first, int* second){
	int diff = 0;
	for (int i = 0; i < nbPnt*3; i++) {
		diff +=abs(first[i]-second[i]);
	}
	return diff;

};

int compare2Im(int* a, int* b, int div){
	return getSumDiff(div*div,a,b);
	
};

/// @brief Read all images that have been created by they framing into one array of bitmaps.
//
/// @param nbIm Number of images.
//
/// @return An array of all the images.

BMP* readAllImages(int nbIm){
	BMP* imList = new BMP[nbIm];
	char* name = new char[32];
	for (int i = 1; i <= nbIm; i++) {
		sprintf(name, "images/out%d.bmp", i);
		imList[i-1].ReadFromFile(name);
	}
	delete [] name;
	return imList;
};

int main(int argc, const char *argv[])
{

	// line 95-105: getting information concerning the image size and computing the number of points
	BMP im;
	im.ReadFromFile("images/out1.bmp");
	int width = im.TellWidth();
	int height = im.TellHeight();
	
	int nbDiv = atoi(argv[1]);
	int points = nbDiv*nbDiv;


	int w = width/(nbDiv+1);
	int h = height/(nbDiv+1);
	
	
	
	
	int end = atoi(argv[2])-3;
	
	int * changings = new int[end];
	for (int i = 0; i < end; i++) {
		changings[i] = i;
	}

	//set first image
	//
	changings[0] = 30;
	changings[30] = 0;


	BMP* list = readAllImages(end);
	int** col = getAllPixels(list, nbDiv, w, h, end);


	int temp;
	int diff, min, index;
	for (int i = 0; i < end-1; i++) {
		min = 100000000;
		for (int a = i+1; a < end-1; a++) {
			diff  =	compare2Im(col[changings[i]], col[changings[a]], nbDiv);
			printf("difference between %d and %d : %d\n", i, a , diff);
			if(diff < min){
				index = a;
				min = diff;
			}	
		}
		temp = changings[i+1];
		changings[i+1] = changings[index];
		changings[index] = temp;
		
		//printf("Difference between %d and %d : %d\n",i+1, i+2,diff1);
	}
	for (int i = 0; i < end; i++) {
		printf("%d\n", changings[i]+1);
	}
	char * name = new char[32];
	char * newname = new char[32];
	int error;
	for (int i = 0; i < end; i++) {
		sprintf(name, "images/out%d.bmp",changings[i]+1);
		sprintf(newname, "images/new%03d.bmp", i);
		error = rename(name, newname);
	}

	return 0;
}
