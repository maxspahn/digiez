#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"
#include <iostream>
#include "EasyBMP.h"
using namespace std;

int** getPixels(BMP image,int div,  int a, int b){
	int** values = new int*[div*div];
	int i = 0;
	for (int c = 1; c <= div; c++) {
		for (int d = 1; d <= div; d++) {
			values[i] = new int[3];
			values[i][0] = image(c*a, d*b)->Red;
			values[i][1] = image(c*a, d*b)->Green;
			values[i][2] = image(c*a, d*b)->Blue;
			i++;
		}
	}
	return values;

};

int getSumDiff(int nbPnt, int** first, int** second){
	int diff = 0;
	for (int i = 0; i < nbPnt; i++) {
		for (int a = 0; a < 3; a++) {
			diff +=abs(first[i][a]-second[i][a]);
		}
	}
	return diff;

};

int main(int argc, const char *argv[])
{
	BMP im;
	im.ReadFromFile("images/out1.bmp");
	int width = im.TellWidth();
	int height = im.TellHeight();
	
	int nbDiv = atoi(argv[1]);
	int points = nbDiv*nbDiv;


	int w = width/(nbDiv+1);
	int h = height/(nbDiv+1);

	BMP im1;
	BMP im2;	

	for (int i = 2; i < 10; i++) {
		int a = i-1;
		char buffer[32];

		sprintf(buffer, "images/out%d.bmp", a);
		im1.ReadFromFile(buffer);
		sprintf(buffer, "images/out%d.bmp", i);
		im2.ReadFromFile(buffer);
		

		int** pi1 = getPixels(im1,nbDiv, w,h);
		int** pi2 = getPixels(im2,nbDiv ,w,h);

		printf("%d\n", getSumDiff(points, pi1, pi2));
		/*
		for (int i = 0; i < points; i++) {
			printf("Differences in point %d\n", i);
			for (int a = 0; a < 3; a++) {
				printf("%d  ", pi1[i][a]-pi2[i][a]);
			}
			printf("\n");
		}
		*/
		for (int i = 0; i < points; i++) {
			delete [] pi1[i];
			delete [] pi2[i];
		}
		delete [] pi1;
		delete [] pi2;
			
	}






















	return 0;
}
