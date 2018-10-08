#include <iostream>
#include <cmath>
#include "../libs/ImageBase.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];

    if (argc != 3) {
        printf("Usage: ImageIn.pgm ImgOut.pgm\n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLue);
    sscanf(argv[2],"%s",cNomImgEcrite);

    ImageBase imgIn;

    imgIn.load(cNomImgLue);
    
    ImageBase imgPred(imgIn.getHeight(), imgIn.getWidth(), false);
    ImageBase imgDiff(imgIn.getHeight(), imgIn.getWidth(), false);
    
    for(int i = 0; i < imgIn.getHeight(); ++i){
        for(int j = 0; j < imgIn.getWidth(); ++j){
            if(i == 0 || j == 0){
                imgPred[i][j] = imgIn[i][j];
            }
            else{
                int a = imgIn[i][j - 1];
                int b = imgIn[i - 1][j - 1];
                int c = imgIn[i - 1][j];
                imgPred[i][j] = std::abs(a - b) > std::abs(b - c) ? c : a;
            }
            imgDiff[i][j] = imgIn[i][j] - imgPred[i][j] + 128;
        }
    }

    //imgPred.save("out/pred.pgm");   
    imgDiff.save(cNomImgEcrite);
    
    return 0;
}
