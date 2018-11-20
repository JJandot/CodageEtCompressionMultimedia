#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Point.h"
#include "Face.h"
#include "Bin.h"


std::vector<Point> vP;
std::vector<Face> vF;
int nbV, nbF, nbE;
float x, y, z;
int t, a, b, c;

Point centreGravite(){
    float x = 0, y = 0, z = 0;

    for (auto &i : vP) {
        x += i.getX();
        y += i.getY();
        z += i.getZ();
    }
    x /= vP.size();
    y /= vP.size();
    z /= vP.size();
    return Point(x, y, z);
}

void lireMaillage(const std::string &path){
    std::ifstream file;
    file.open(path, std::ios::in);
    std::cout<<"OPEN: "<<path<<std::endl;

    std::string line;
    if(file){
        getline(file, line);
        if(line=="OFF"){
            getline(file, line);
            std::stringstream ls(line);
            ls >> nbV >> nbF >> nbE;
            for(int i=0;i<nbV;i++){
                getline(file,line);
                std::stringstream ls(line);
                ls >> x >> y >> z;
                Point p(x, y, z);
                vP.push_back(p);
            }
            for(int i=0;i<nbF;i++){
                getline(file,line);
                std::stringstream ls(line);
                ls >> t >> a >> b >> c;
                Face f(a, b, c);
                vF.push_back(f);
            }
            std::cout<<"LOAD "<<vP.size()<<" "<<vF.size()<< std::endl;
        }else{
            std::cerr << "bad format" << std::endl;
        }
        file.close();
    }
    else
        std::cerr <<"File Error"<< std::endl;
}

void coordSpheriques(const Point &cg){
    float rho, phi, teta;
    for (auto &i : vP) {
        Point p = i;
        rho = static_cast<float>(sqrt(pow(p.getX() - cg.getX(), 2) + pow(p.getY() - cg.getY(), 2) + pow(p.getZ() - cg.getZ(), 2)));
        p.setRho(rho);
        phi = std::acos((p.getZ() - cg.getZ()) / rho);
        p.setPhi(phi);

        teta = static_cast<float>(acos((p.getX() - cg.getX()) / sqrt(pow((p.getX() - cg.getX()), 2) + pow((p.getY() - cg.getX()), 2))));
        if((p.getY() - cg.getY()) < 0)
            teta = static_cast<float>(2 * M_PI - teta);
        p.setTeta(teta);
        i = p;
    }
}

float getMinSpheric(){
    float min = vP[0].getRho();
    for (const auto &p : vP) {
        if (p.getRho() < min) {
            min = p.getRho();
        }
    }
    return min;
}

float getMaxSpheric(){
    float max = vP[0].getRho();
    for (const auto &p : vP) {
        if(p.getRho() > max)
            max = p.getRho();
    }
    return max;
}


/**
 * Need normalized vector of spheric coordinates
 */
void tatouage(int message, float alpha, float k, float deltaK, int nBin){
    float min = getMinSpheric();
    float max = getMaxSpheric();

    std::cout << min << std::endl;
    std::cout << max << std::endl;

    float length = (max - min) / nBin;
    std::vector<Bin> bins;
    float val = min;
    for(int i = 0; i < length; ++i){
        Bin b(val, val + length);


        for (auto &j : vP) {
            if(j.getRho() >= val && j.getRho() < val + length) {
                b.addPoint(j);
            }
        }
        val = val + length;
        b.normalise();

        float mean = b.getMean();
        while(mean < alpha + 0.5){
            b.transform(k);
            mean = b.getMean();
        }
        bins.push_back(b);
    }

}


// vincent.itier@lirmm.fr
// archive JANDOT_codage_compression_TP
// source + compte rendu

int main(int argc, char **argv){
    lireMaillage("../files/bunny.off");
    Point g = centreGravite();
    coordSpheriques(g);

    g.print();
    tatouage(1, 0.1, 1, 0.001, 1);
    return 0;
}