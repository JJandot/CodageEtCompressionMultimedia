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
    
    ImageBase ImgOut(imgIn.getHeight(), imgIn.getWidth(), false);
    
    int key[nTaille];
    
    
    
    
    
    for(int k = 0; k <= 100; ++k){
        int cpt = 0;
        
        srand(k);
        for(int i = 0; i < nTaille; ++i){
            key[i] = rand() % 256;
        }

        for (int i=0; i < imgIn.getHeight(); i++)
            for (int j=0; j < imgIn.getWidth(); j++)
                ImgOut[i][j] = imgIn[i][j] ^ key[cpt++];
        

        
        /*-------------------------------------------------------------------*/
        float entropie = 0.0f;
        
        float tabOcc[256];
        memset (tabOcc, 0, sizeof(tabOcc));
        for(int i = 0; i < ImgOut.getWidth(); ++i){
            for(int j = 0; j < ImgOut.getHeight(); ++j){
                tabOcc[ImgOut[i][j]]++;
            }
        }
        
        for(int i = 0; i < 256; ++i){
            tabOcc[i] /= (float)nTaille;

            if(tabOcc[i] <= 0.0)
                continue;
            entropie += (float)((float)tabOcc[i] * (float)log2(tabOcc[i]));
        }
        
        entropie = -entropie;
        
        std::cout << "K = " << k << ", Entropie : " << entropie << std::endl;
    
    }

    return 0;
}
