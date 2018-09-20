#include <cstdio>
#include <cstdlib>
#include <iostream>
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


    int moyR, moyV;
    
    double moyPixelsR[3];
    double nbR = 0;
    double moyPixelsV[3];
    double nbV = 0;
    
    double tmpR[3];
    double tmpV[3];
    
    
    
    std::copy(std::begin(pixelR), std::end(pixelR), std::begin(tmpR));
    std::copy(std::begin(pixelV), std::end(pixelV), std::begin(tmpV));
    
    int cpt = 0;
    
    do{
        for(int i = 0; i < nTaille3; i+=3){
            moyR = sqrt(pow(ImgIn[i] - tmpR[0], 2) + pow(ImgIn[i + 1] - tmpR[1], 2) + pow(ImgIn[i + 2] - tmpR[2], 2));
            moyV = sqrt(pow(ImgIn[i] - tmpV[0], 2) + pow(ImgIn[i + 1] - tmpV[1], 2) + pow(ImgIn[i + 2] - tmpV[2], 2));
            
            if(moyR > moyV){
                ++nbV;
                for(int j = 0; j < 3; ++j){
                    moyPixelsV[j] += (double)ImgIn[i + j];
                }
            }
            else{
                ++nbR;
                for(int j = 0; j < 3; ++j){
                    moyPixelsR[j] += (double)ImgIn[i + j];
                }
            }
        }
        
        for(int i = 0; i < 3; ++i){
            moyPixelsV[i] /= nbV;
            moyPixelsR[i] /= nbR;
            tmpR[i] = moyPixelsR[i];
            tmpV[i] = moyPixelsV[i];
        }
        ++cpt;
        nbV = 0;
        nbR = 0;
    }while(cpt < 1000);
    
    std::cout << "R : " << moyPixelsR[0]  << ", " << moyPixelsR[1] << ", " << moyPixelsR[2] << std::endl;
    std::cout << "V : " << moyPixelsV[0]  << ", " << moyPixelsV[1] << ", " << moyPixelsV[2] << std::endl;
    
    for(int i = 0; i < nTaille3; i+=3){
        moyR = sqrt(pow(ImgIn[i] - moyPixelsR[0], 2) + pow(ImgIn[i + 1] - moyPixelsR[1], 2) + pow(ImgIn[i + 2] - moyPixelsR[2], 2));
        moyV = sqrt(pow(ImgIn[i] - moyPixelsV[0], 2) + pow(ImgIn[i + 1] - moyPixelsV[1], 2) + pow(ImgIn[i + 2] - moyPixelsV[2], 2));
        
        for(int j = 0; j < 3; ++j){
            if(moyR > moyV){
                ImgOut[i + j] = moyPixelsV[j];
            }
            else{
                ImgOut[i + j] = moyPixelsR[j];
            }
        }
        
        
    }

    ecrire_image_ppm("Out3.ppm", ImgOut,  nH, nW);

    free(ImgIn);
    return 1;
}
