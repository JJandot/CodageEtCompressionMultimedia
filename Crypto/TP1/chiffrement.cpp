#include <iostream>
#include <ctime>
#include "../../libs/image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, seed;

    if (argc != 4) {
        std::cerr << "Usage: ImageIn.pgm ImgOut.pgm Seed" << std::endl;
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &seed);
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    int key[nTaille];
    
    srand(seed);
    for(int i = 0; i < nTaille; ++i){
        key[i] = rand() % 256;
    }

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
            ImgOut[i * nW + j] = ImgIn[i * nW + j] ^ key[i * nW + j];
            

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 0;
}
