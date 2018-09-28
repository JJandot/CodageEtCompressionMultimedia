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

    OCTET *ImgInY, *ImgInCr, *ImgInCb;
    OCTET *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLueG, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgInCr, OCTET, nTaille);
    lire_image_pgm(cNomImgLueG, ImgInCr, nH * nW);
    
    allocation_tableau(ImgInY, OCTET, nTaille);
    lire_image_pgm(cNomImgLueR, ImgInY, nH * nW);
    
    allocation_tableau(ImgInCb, OCTET, nTaille);
    lire_image_pgm(cNomImgLueB, ImgInCb, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille3);
    
    int r, g, b;
    
    for (int i=0; i < nTaille3; i+=3) {
        r = ImgInY[i/3] + 1.402 * (ImgInCr[i/3] - 128);
        g = ImgInY[i/3] - 0.34414 * (ImgInCb[i/3] - 128) - 0.71414 * (ImgInCr[i/3] - 128);
        b = ImgInY[i/3] + 1.772 * (ImgInCb[i/3] - 128);
    
        if(r < 0)
            r = 0;
        if(r > 255)
            r = 255;
        if(g < 0)
            g = 0;
        if(g > 255)
            g = 255;
        if(b < 0)
            b = 0;
        if(b > 255)
            b = 255;    
        ImgOut[i] = r;
        ImgOut[i+1] = g;
        ImgOut[i+2] = b;    
    }

    ecrire_image_ppm("YCrCb/Decompression.ppm", ImgOut,  nH, nW);

    free(ImgInCr);
    free(ImgInCb);
    free(ImgInY);
    return 0;
}
