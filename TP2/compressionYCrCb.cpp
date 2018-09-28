#include <iostream>
#include "../libs/ImageBase.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250];

    if (argc != 2) {
        printf("Usage: ImageTempIn.ppm \n");
        exit (1) ;
    }
    sscanf(argv[1],"%s",cNomImgLue);

    ImageBase imgIn;

    imgIn.load(cNomImgLue);
    
    ImageBase imgInR(imgIn.getHeight(), imgIn.getWidth(), false);
    ImageBase imgInG(imgIn.getHeight() / 2, imgIn.getWidth() / 2, false);
    ImageBase imgInB(imgIn.getHeight() / 2, imgIn.getWidth() / 2, false);
    
    for(int i = 0; i < imgIn.getHeight(); ++i){
        for(int j = 0; j < imgIn.getWidth(); ++j){
            imgInR[i][j] = imgIn[i*3][j*3];
            imgInG[i/2][j/2] = imgIn[i*3][j*3+1];
            imgInB[i/2][j/2] = imgIn[i*3][j*3+2];
        }
    }


    imgInR.save("YCrCb/Y.pgm");
    imgInG.save("YCrCb/Cr.pgm");
    imgInB.save("YCrCb/Cb.pgm");
    
    return 0;
}
