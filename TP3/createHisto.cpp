// test_couleur.cpp : Seuille une image couleur 

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "../libs/image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], nomHisto[250];
    int nH, nW;    

    if (argc != 3) {
        std::cerr << "Usage: ImageIn.pgm out/nomHisto.dat" << std::endl;
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nomHisto);

    
    FILE *fp = NULL;
    fp = fopen(nomHisto ,"w");
    
    if(fp == NULL){
        std::cerr << "Erreur file" << std::endl;
        exit(1);
    }

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    allocation_tableau(ImgIn, OCTET, nH * nW);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    
    int tab[256];
    for(int i = 0; i < 256; ++i)
        tab[i] = 0;
    
    for (int i=0; i < nH; i++){
        for (int j=0; j < nW; j++){
            tab[ImgIn[i*nW+j]]++;
        }
    }
    
    for(int i = 0; i < 256; ++i){
        fprintf(fp, "%d %d\n", i ,tab[i]);
    }
    
    fclose(fp);
    free(ImgIn);
    return 0;
}
