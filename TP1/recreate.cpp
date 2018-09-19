#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#include "../libs/image_ppm.h"

const std::vector<std::string> explode(const std::string& s, const char& c)
{
    std::string buff;
    std::vector<std::string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && !buff.empty()) {v.push_back(buff); buff = ""; }
    }
    if(!buff.empty()) v.push_back(buff);
    return v;
}


int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3) {
        printf("Usage: Compressed.ppm Recreated.ppm\n");
        exit (1) ;
    }
    
    std::string values[256];

    sscanf(argv[1],"%s",cNomImgLue);
    sscanf(argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    std::ifstream input("data.txt");
    int valCpt = 0;
    std::string line;
    while(std::getline(input, line)){
        values[valCpt++] = line;
    }
    
    //FILLING LOOP
    int inCpt;
    for (int i = 0; i < nTaille3; i += 3) {        
        int indice = ImgIn[inCpt++];
        std::string value = values[indice];
        std::vector<std::string> v{explode(value, ',')};
        
        for(int k = 0; k < v.size(); ++k){
            ImgOut[i + k] = std::stoi(v.at(k));
        }
    }
    
    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);

    return 0;
}
