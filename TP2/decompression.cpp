#include <iostream>
#include "../libs/image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLueR[250], cNomImgLueG[250], cNomImgLueB[250];
    int nH, nW, nTaille;

    if (argc != 4) {
        printf("Usage: ImageInR.pgm ImageInG.pgm ImageInB.pgm \n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLueR);
    sscanf(argv[2],"%s",cNomImgLueG);
    sscanf(argv[3],"%s",cNomImgLueB);

    OCTET *ImgInR, *ImgInG, *ImgInB;
    OCTET *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLueG, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgInG, OCTET, nTaille);
    lire_image_pgm(cNomImgLueG, ImgInG, nH * nW);
    
    allocation_tableau(ImgInR, OCTET, nTaille);
    lire_image_pgm(cNomImgLueR, ImgInR, nH * nW);
    
    allocation_tableau(ImgInB, OCTET, nTaille);
    lire_image_pgm(cNomImgLueB, ImgInB, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille3);
    
    for (int i=0; i < nTaille3; i+=3) {
        ImgOut[i] = ImgInR[i/3];
        ImgOut[i+1] = ImgInG[i/3];
        ImgOut[i+2] = ImgInB[i/3];        
    }

    ecrire_image_ppm("Decompression.ppm", ImgOut,  nH, nW);

    free(ImgInR);
    free(ImgInB);
    free(ImgInG);
    return 0;
}
