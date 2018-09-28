#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "math.h"
#include "../libs/image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue1[250], cNomImgLue2[250];
    int nH, nW, nTaille;

    if (argc != 3) {
        printf("Usage: ImageIn1.ppm ImageIn2.ppm \n");
        exit (1);
    }

    sscanf (argv[1],"%s",cNomImgLue1) ;
    sscanf (argv[2],"%s",cNomImgLue2);
    OCTET *ImgIn1, *ImgIn2;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue1, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn1, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue1, ImgIn1, nH * nW);
    allocation_tableau(ImgIn2, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue2, ImgIn2, nH * nW);

    double tmpEqm= 0;

    for (int i=0; i < nTaille3; i+=3) {
        for(int j = 0; j < 3; ++j){
            tmpEqm += pow(ImgIn1[i + j] - ImgIn2[i + j], 2);
            std::cout << tmpEqm << std::endl;
        }
    }
    
    double eqm = (1.0/nTaille) * tmpEqm;
    std::cout << "EQM : " << eqm << std::endl;
    
    double psnr = 10 * log10(pow(255, 3) / eqm);
    std::cout << "PSNR = " << psnr << std::endl;

    free(ImgIn1);
    free(ImgIn2);
    return 1;
}
