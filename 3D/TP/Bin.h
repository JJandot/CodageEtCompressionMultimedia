//
// Created by jjandot on 19/11/18.
//

#ifndef TP_BIN_H
#define TP_BIN_H


#include <vector>
#include <cmath>
#include "Point.h"

class Bin {
private:
    float rMin;
    float rMax;
    std::vector<Point> points;
public:
    const std::vector<Point> &getPoints() const;
    void setPoints(const std::vector<Point> &points);

public:
    Bin(float rMin, float rMax);
    void normalise();
    void normaliseInv();
    float getMean();
    void addPoint(Point point);
    void transform(float k);

};


#endif //TP_BIN_H
