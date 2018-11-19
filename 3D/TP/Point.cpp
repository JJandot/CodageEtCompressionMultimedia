//
// Created by jjandot on 22/01/18.
//

#include <iostream>
#include "Point.h"


Point::Point() {
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(Point const & point) {
    x = point.x;
    y = point.y;
    z = point.z;
}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

float Point::getZ() const {
    return z;
}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}

void Point::setZ(float z) {
    this->z = z;
}

void Point::print() {
    std::cout << "------Point------" << std::endl;
    std::cout << "X = " << x << std::endl;
    std::cout << "Y = " << y << std::endl;
    std::cout << "Z = " << z << std::endl;
    std::cout << "-----------------" << std::endl;
}

float Point::getRho() const {
    return rho;
}

void Point::setRho(float rho) {
    this->rho = rho;
}

float Point::getPhi() const {
    return phi;
}

void Point::setPhi(float phi) {
    this->phi = phi;
}

float Point::getTeta() const {
    return teta;
}

void Point::setTeta(float teta) {
    this->teta = teta;
}

float Point::getDistanceSpherique(Point centreGravite) {

}

/*

float Point::getDistance(Point point) {
    float x = pow(point.getX() - getX(), 2);
    float y = pow(point.getY() - getY(), 2);
    float z = pow(point.getZ() - getZ(), 2);

    float result = sqrt(x + y + z);
    return result;
}*/
