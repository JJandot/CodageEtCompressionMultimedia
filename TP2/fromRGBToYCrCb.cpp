#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "math.h"
#include "../libs/image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250];
    int nH, nW, nTaille, nr, ng, nb;

    if (argc != 2) {
        printf("Usage: ImageIn.ppm\n");
        exit (1);
    }

    sscanf (argv[1],"%s",cNomImgLue);
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    int y, cr, cb;

    for (int i=0; i < nTaille3; i+=3) {
        nr = ImgIn[i];
        ng = ImgIn[i + 1];
        nb = ImgIn[i + 2];
        
        y = 0.299 * nr + 0.587 * ng + 0.114 * nb;
        cr = 0.5 * nr - 0.4187 * ng - 0.0813 * nb + 128;
        cb = -0.1687 * nr - 0.3313 * ng - 0.5 * nb + 128;
        
        ImgOut[i] = y;
        ImgOut[i + 1] = cr;
        ImgOut[i + 2] = cb;
    }
    
    ecrire_image_ppm("YCrCb/YCrCb.ppm", ImgOut,  nH, nW);

    free(ImgIn);
    return 0;
}
