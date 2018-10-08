#include <iostream>
#include <ctime>
#include <cmath>
#include <cstring>
#include "../../libs/ImageBase.h"


float entropie(ImageBase img){
    /*float entropie = 0.0f;
    
    float tabOcc[256];
    for(int i = 0; i < img.getWidth(); ++i){
        for(int j = 0; j < img.getHeight(); ++j){
            tabOcc[img[i][j]]++;
        }
    }
    
    float taille = (float)img.getWidth() * (float)img.getHeight();
    
    for(int i = 0; i < 256; ++i){
        if(tabOcc[i] == 0)
            continue;
        tabOcc[i] /= taille;
        
        entropie += (float)tabOcc[i] * (float)log2(tabOcc[i]);
    }
    
    std::cout << entropie << std::endl;
    return entropie*/
    return 0;
    //erreur de segmentation meme avec le return 0
}


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
    
    //entropie(imgIn);   
    
    float entropie = 0.0f;
    
    float tabOcc[256];
    memset (tabOcc, 0, sizeof(tabOcc));
    for(int i = 0; i < imgIn.getWidth(); ++i){
        for(int j = 0; j < imgIn.getHeight(); ++j){
            tabOcc[imgIn[i][j]]++;
        }
    }
    
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
