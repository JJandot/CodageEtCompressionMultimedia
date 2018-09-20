#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <math.h>
#include "../libs/image_ppm.h"

/**
 * K-Mean : choix de deux pixels opposés, création d'un tableau, pour chaque pixel, on calcule les deux distances et on garde la plus petite
**/

double pixelR[3] = {198, 52, 39};
double pixelV[3] = {108, 179, 91};


int main(int argc, char* argv[]) {
    char cNomImgLue[250];
    int nH, nW, nTaille;

    if (argc != 2) {
        printf("Usage: ImageIn.ppm \n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLue);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    
    int tabColors[256][3];
    srand(time(NULL));
    int n;
    
    for(int i = 0; i < 256; ++i){
        n = rand() % nTaille;
        for(int j = 0; j < 3; ++j){
            tabColors[i][j] = ImgIn[3 * n + j];
        }
    }
    
    double moy;
    double moyPixels[256][3];
    double occurence[256];
    int js[nTaille];
    int currentJ;
    int cpt = 0;
    
    
    double tmp[256][3];
    for(int i = 0; i < 256; ++i){
        for(int j = 0; j < 3; ++j){
            tmp[i][j] = tabColors[i][j];
        }
    }
    
    do{
        for(int i = 0; i < nTaille3; i+=3){
            moy = 10000;
            currentJ = 0;
            //CALC MOY
            for(int j = 0; j < 256; ++j){
                double temp = sqrt(pow(ImgIn[i] - tmp[j][0], 2) + pow(ImgIn[i + 1] - tmp[j][1], 2) + pow(ImgIn[i + 2] - tmp[j][2], 2));
                if(temp < moy){
                    moy = temp;
                    currentJ = j;
                }
            }
            
            for(int j = 0; j < 3; ++j){
                moyPixels[currentJ][j] += (double)ImgIn[i + j];
                occurence[currentJ]++;
            }
            js[i/3] = currentJ;
        }
        
        for(int i = 0; i < 256; ++i){
            for(int j = 0; j < 3; ++j){
                moyPixels[i][j] /= occurence[i];
                tmp[i][j] = moyPixels[i][j];
            }
            occurence[i] = 0;
        }
        ++cpt;
    }while(cpt < 1);
        

        for(int i = 0; i < nTaille3; i+=3){
            for(int j = 0; j < 3; ++j){
                int temp = js[i/3];
                ImgOut[i + j] = moyPixels[temp][j];
            }
        }
    
    
    
    ecrire_image_ppm("I256Boucle.ppm", ImgOut,  nH, nW);

    free(ImgIn);
    return 1;
}
