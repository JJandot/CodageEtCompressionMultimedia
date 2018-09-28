#include <iostream>
#include "../libs/ImageBase.h"

int main(int argc, char* argv[]) {
    char cNomImgLueCR[250], cNomImgLueCB[250];

    if (argc != 3) {
        printf("Usage: ImageInCR.pgm ImageInCB.pgm \n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLueCR);
    sscanf(argv[2],"%s",cNomImgLueCB);

    ImageBase imgInCR, imgInCB;

    imgInCR.load(cNomImgLueCR);
    imgInCB.load(cNomImgLueCB);
    
    ImageBase imgTmpCR(imgInCR.getHeight() * 2, imgInCR.getWidth() * 2, false);
    ImageBase imgTmpCB(imgInCR.getHeight() * 2, imgInCR.getWidth() * 2, false);
    
    for(int i = 0; i < imgInCR.getHeight() * 2; ++i){
        for(int j = 0; j < imgInCR.getWidth() * 2; ++j){
            imgTmpCR[i][j] = imgInCR[i/2][j/2];
            imgTmpCB[i][j] = imgInCB[i/2][j/2];
        }
    }

    imgTmpCR.save("YCrCb/BigCr.pgm");
    imgTmpCB.save("YCrCb/BigCb.pgm");
    
    return 0;
}
