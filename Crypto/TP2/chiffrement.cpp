#include <iostream>
#include <cmath>
#include <vector>
#include "../../libs/ImageBase.h"

bool estPremier(int nb){
    int close = floor(sqrt(nb));
    
    for(int i = 2; i <= close; ++i){
        if(nb % i == 0)
            return false;
    }
    return true;
}

bool sontPremiers(int a, int b){
    int mod = a % b;
    if(mod == 1)
        return true;
    while(mod != 0){
        a = b;
        b = mod;
        mod = a % b;
        if(mod == 1)
            return true;
    }
    return false;
}

std::vector<int> exposantsDeChiffrement(int p, int q){
    int phi = (p - 1) * (q - 1);

    std::vector<int> results;
    for(int i = 1; i < phi; ++i)
        if(sontPremiers(phi, i))
            results.push_back(i);
    return results;
}

int main(int argc, char* argv[]){
    char cNomImgLue[250], cNomImgEcrite[250];
    if (argc != 3) {
        std::cerr << "Usage: ImageIn.pgm ImgOut.pgm" << std::endl;
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    ImageBase imgIn;
    imgIn.load(cNomImgLue);

    int p = 11, q = 23, e = 17;
    int pq = p * q;

    ImageBase out(imgIn.getHeight(), imgIn.getWidth(), false);
    
    for(int i = 0; i < imgIn.getHeight(); ++i){
        for(int j = 0; j < imgIn.getWidth(); ++j){
            int px = imgIn[i][j];
            for(int k = 0; k < e; ++k){
                px = (px * px) % pq;
            }
            out[i][j] = px;
        }
    }
    out.save(cNomImgEcrite);   
    return 0;
}
