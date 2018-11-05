#include <iostream>
#include <ctime>
#include <cmath>
#include <cstring>
#include "../../libs/ImageBase.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250];
    int nTaille;
    if (argc != 2) {
        std::cerr << "Usage: ImageIn.pgm" << std::endl;
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);

    ImageBase imgIn;
    imgIn.load(cNomImgLue);

    nTaille = imgIn.getWidth() * imgIn.getHeight();
    
    FILE *fp = NULL;
    fp = fopen("out/histo.dat" ,"w");
    
    if(fp == NULL){
        std::cerr << "Erreur file" << std::endl;
        exit(1);
    }
    
    float entropie = 0.0f;
    
    float tabOcc[256];
    memset (tabOcc, 0, sizeof(tabOcc));
    for(int i = 0; i < imgIn.getWidth(); ++i){
        for(int j = 0; j < imgIn.getHeight(); ++j){
            tabOcc[imgIn[i][j]]++;
        }
    }
    
    for(int i = 0; i < 256; ++i){
        fprintf(fp, "%d %f\n", i ,tabOcc[i]);
    }
    
    fclose(fp);
    
    for(int i = 0; i < 256; ++i){
        tabOcc[i] /= (float)nTaille;

        if(tabOcc[i] <= 0.0)
            continue;
        std::cout << (float)tabOcc[i] << std::endl;
        entropie += (float)((float)tabOcc[i] * (float)log2(tabOcc[i]));
    }
   
    
    entropie = -entropie;
    
    std::cout << "Entropie : " << entropie << std::endl;

    return 0;
}
