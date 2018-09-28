#include <iostream>
#include "../libs/ImageBase.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250];

    if (argc != 2) {
        printf("Usage: ImageIn.ppm \n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLue);

    ImageBase imgIn;

    imgIn.load(cNomImgLue);
    
    ImageBase imgInR(imgIn.getHeight() / 2, imgIn.getWidth() / 2, false);
    ImageBase imgInG(imgIn.getHeight(), imgIn.getWidth(), false);
    ImageBase imgInB(imgIn.getHeight() / 2, imgIn.getWidth() / 2, false);
    
    for(int i = 0; i < imgIn.getHeight(); ++i){
        for(int j = 0; j < imgIn.getWidth(); ++j){
            imgInG[i][j] = imgIn[i*3][j*3+1];
            
            imgInR[i/2][j/2] = imgIn[i*3][j*3];
            imgInB[i/2][j/2] = imgIn[i*3][j*3+2];
        }
    }

    imgInR.save("r.pgm");
    imgInG.save("g.pgm");
    imgInB.save("b.pgm");
    
    return 0;
}
