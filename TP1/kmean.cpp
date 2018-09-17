#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "../libs/image_ppm.h"

/**
 * K-Mean : choix de deux pixels opposés, création d'un tableau, pour chaque pixel, on calcule les deux distances et on garde la plus petite
**/

int pixelR[3] = {198, 52, 39};
int pixelV[3] = {108, 179, 91};


int main(int argc, char* argv[]) {
    char cNomImgLue[250];
    int nH, nW, nTaille;

    if (argc != 2) {
        printf("Usage: ImageIn.ppm \n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLue);

    OCTET *ImgIn, *ImgOut, *ImgOut2;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(ImgOut2, OCTET, nTaille3);

    int moyR, moyV;
    
    int moyPixelsR[3];
    int nbR = 0;
    int moyPixelsV[3];
    int nbV = 0;
    
    for(int i = 0; i < nTaille3; i+=3){
        moyR = sqrt(pow(ImgIn[i] - pixelR[0], 2) + pow(ImgIn[i + 1] - pixelR[1], 2) + pow(ImgIn[i + 2] - pixelR[2], 2));
        moyV = sqrt(pow(ImgIn[i] - pixelV[0], 2) + pow(ImgIn[i + 1] - pixelV[1], 2) + pow(ImgIn[i + 2] - pixelV[2], 2));

        for(int j = 0; j < 3; ++j){
            if(moyR > moyV){
                ImgOut[i + j] = pixelV[j];
                //ajout du pixel dans le tableau de tous les verts
                ++nbV;
                moyPixelsV[j] = (moyPixelsV[j] + ImgIn[i + j]) / nbV;
            }
            else{
                ImgOut[i + j] = pixelR[j];
                //ajout du pixel dans le tableau de tous les rouges
                ++nbR;
                moyPixelsR[j] = (moyPixelsR[j] + ImgIn[i + j]) / nbR;
            }
        }
    }
    
    for(int i = 0; i < nTaille3; i+=3){
        moyR = sqrt(pow(ImgIn[i] - moyPixelsR[0], 2) + pow(ImgIn[i + 1] - moyPixelsR[1], 2) + pow(ImgIn[i + 2] - moyPixelsR[2], 2));
        moyV = sqrt(pow(ImgIn[i] - moyPixelsV[0], 2) + pow(ImgIn[i + 1] - moyPixelsV[1], 2) + pow(ImgIn[i + 2] - moyPixelsV[2], 2));
        
        for(int j = 0; j < 3; ++j){
            if(moyR > moyV){
                ImgOut2[i + j] = moyPixelsV[j];
            }
            else{
                ImgOut2[i + j] = moyPixelsR[j];
            }
        }
        
        
    }

    ecrire_image_ppm("Out.ppm", ImgOut,  nH, nW);
    ecrire_image_ppm("Out2.ppm", ImgOut2,  nH, nW);

    free(ImgIn);
    return 1;
}
