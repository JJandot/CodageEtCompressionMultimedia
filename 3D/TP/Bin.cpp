//
// Created by jjandot on 19/11/18.
//

#include "Bin.h"

Bin::Bin(float rMin, float rMax) {
    this->rMin = rMin;
    this->rMax = rMax;
}

const std::vector<Point> &Bin::getPoints() const {
    return points;
}

void Bin::normalise() {
    float val = rMax - rMin;
    for (auto &point : points) {
        std::cout << "before : " << point.getRho();
        point.setRho((point.getRho() - rMin) / val);
        point.setPhi((point.getPhi() - rMin) / val);
        point.setTeta((point.getTeta() - rMin) / val);
        std::cout << ", after : " << point.getRho() << std::endl;
    }
}

void Bin::normaliseInv() {
    float val = rMax - rMin;
    for (auto &p : points) {
        p.setRho(p.getRho() * val  + rMin);
        p.setPhi(p.getPhi() * val  + rMin);
        p.setTeta(p.getTeta() * val  + rMin);
    }
}

float Bin::getMean() {
    float mean = 0;
    for (auto &point : points) {
        mean += point.getRho();
    }
    mean /= points.size();
    return mean;
}

void Bin::addPoint(Point point) {
    points.push_back(point);
}

void Bin::transform(float k) {
    for (auto p : points) {
        p.setRho(std::pow(p.getRho(), k));
        p.setPhi(std::pow(p.getPhi(), k));
        p.setTeta(std::pow(p.getTeta(), k));
    }
}


