#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "../libs/image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3) {
        printf("Usage: I256.ppm Compressed.ppm\n");
        exit (1) ;
    }

    sscanf(argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    FILE *fp = NULL;
    fp = fopen("data.txt" ,"w");

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    int cpt;
    std::map<std::string, int> colorMap;
    std::map<std::string, int>::iterator it;
    
    int outCpt;
    
    for (int i = 0; i < nTaille3; i += 3) {        
        std::string color = std::to_string(ImgIn[i]);
        color += ",";
        color += std::to_string(ImgIn[i + 1]);
        color += ",";
        color += std::to_string(ImgIn[i + 2]);
        
        if((it = colorMap.find(color)) == colorMap.end()){
            //INSERTION NEEDED
            colorMap.insert(std::pair<std::string, int>(color, cpt));
            ImgOut[outCpt] = cpt;
            fprintf(fp, "%s\n", color.c_str());
            ++cpt;
        }
        else{
            //ALREADY INSIDE
            std::cout  << "Already inside : first = " << it->first << " / second = " << it->second << std::endl;
            ImgOut[outCpt] = it->second;
        }
        ++outCpt;
    }
    
    fclose(fp);
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);

    return 0;
}
