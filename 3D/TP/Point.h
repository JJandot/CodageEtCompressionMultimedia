//
// Created by jjandot on 22/01/18.
//

#ifndef TP1_POINT_H
#define TP1_POINT_H

#include <iostream>

class Point {

private:
    float x;
    float y;
    float z;

    float rho;
    float phi;
    float teta;

public:
    Point();
    Point(float x, float y, float z);
    Point(Point const&);

    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    float getRho() const;
    float getPhi() const;
    float getTeta() const;


    void setPhi(float phi);
    void setRho(float rho);
    void setTeta(float teta);




    //float getDistance(Point point);
    float getDistanceSpherique(Point centreGravite);
    void print();

};


#endif //TP1_POINT_H
