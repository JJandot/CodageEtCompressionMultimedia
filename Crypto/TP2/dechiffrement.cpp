#include <iostream>
#include <cmath>
#include <vector>
#include "../../libs/ImageBase.h"

int inverseModulaire(int b, int n){
    int n0 = n;
    int b0 = b;
    int t0 = 0;
    int t = 1;
    
    int q = floor(n0 / b0);
    int r = n0 - q * b0;
    int temp;
    while(r > 0){
        temp = t0 - q * t;
        if(temp >= 0){
            temp = temp % n;
        }
        else{
            temp = n - ((-temp) % n);
        }
        t0 = t;
        t = temp;
        n0 = b0;
        b0 = r;
        q = floor(n0 / b0);
        r = n0 - q * b0;
    }
    if(b0 != 1)
        return -1;
    return t;
}

int main(int argc, char* argv[]){
    char cNomImgLue[250], cNomImgEcrite[250];
    if (argc != 3) {
        std::cerr << "Usage: ImageIn.pgm ImgOut.pgm" << std::endl;
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    
    int pq = 253;
    int n = 220;
    int e = 17;
    int d = inverseModulaire(e, n);

    ImageBase imgIn;
    imgIn.load(cNomImgLue);
    
    ImageBase out(imgIn.getHeight(), imgIn.getWidth(), false);
    
    for(int i = 0; i < imgIn.getHeight(); ++i){
        for(int j = 0; j < imgIn.getWidth(); ++j){
            int px = imgIn[i][j];
            for(int k = 0; k < d; ++k){
                px = (px * px) % pq;
            }
            out[i][j] = px;
        }
    }
    out.save(cNomImgEcrite);
    return 0;
}
