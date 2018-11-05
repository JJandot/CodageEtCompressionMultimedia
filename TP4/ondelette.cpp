#include <iostream>
#include <string>
#include "../libs/ImageBase.h"


void print(std::string s){
    std::cout << s << std::endl;
}

int main(int argc, char* argv[]) {
    char cNomImgLue[250];
    int nbDecomp;

    if (argc != 3) {
        printf("Usage: ImageIn.ppm nbDecomposition \n");
        exit (1) ;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%i", &nbDecomp);

    ImageBase img;

    img.load(cNomImgLue);
    
    int w = img.getWidth();
    int h = img.getHeight();
    
    ImageBase out(img.getHeight(), img.getWidth(), true);
    
    int cptI = 0, cptJ = 0;
    
    for(int i = 0; i < w; i+=2){
        for(int j = 0; j < h; j+=2){
            for(int k = 0; k < 3; ++k){
                int a = img[i][j * 3 + k];
                int b = img[i][(j + 1) * 3 + k];
                int c = img[(i + 1)][j * 3 + k];
                int d = img[(i + 1)][(j + 1) * 3 + k];
                
                int x = (a + b) / 2;
                int y = (c + d) / 2;
                int kab = a - b;
                int l = c - d;
                
                int newA = (x + y) / 2;
                int newB = x - y;
                int newC = (kab + l) / 2;
                int newD = kab - l;
                
                out[cptI][cptJ * 3 + k] = newA;
                out[cptI][(cptJ + w / 2)  * 3  + k] = newB;
                out[(cptI + h / 2)][cptJ * 3 + k] = newC;
                out[(cptI + h / 2)][(cptJ + w / 2)  * 3 + k] = newD;
            }
            ++cptJ;
        }
        ++cptI;
    }
    
    out.save("out.ppm");
    
    return 0;
}
