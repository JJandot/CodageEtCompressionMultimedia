#include <iostream>
#include "../libs/ImageBase.h"

int main(int argc, char* argv[]) {
    char cNomImgLueR[250], cNomImgLueG[250], cNomImgLueB[250];

    if (argc != 4) {
        printf("Usage: ImageInR.pgm ImageInG.pgm ImageInB.pgm \n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLueR);
    sscanf(argv[2],"%s",cNomImgLueG);
    sscanf(argv[3],"%s",cNomImgLueB);

    ImageBase imgInR, imgInG, imgInB;

    imgInR.load(cNomImgLueR);
    imgInG.load(cNomImgLueG);
    imgInB.load(cNomImgLueB);
    
    ImageBase imgTmpR(imgInG.getHeight(), imgInG.getWidth(), false);
    ImageBase imgTmpB(imgInG.getHeight(), imgInG.getWidth(), false);
    
    for(int i = 0; i < imgInG.getHeight(); ++i){
        for(int j = 0; j < imgInG.getWidth(); ++j){
            imgTmpR[i][j] = imgInR[i/2][j/2];
            imgTmpB[i][j] = imgInB[i/2][j/2];
        }
    }

    imgTmpR.save("testTMPR.pgm");
    imgTmpB.save("testTMPB.pgm");
    
    return 0;
}
