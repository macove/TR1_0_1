#pragma once
#include <iostream>
#include <cmath>
#include "Surface.h"
#include <chrono>
#include <thread>

class Ball
{

public:

    float mass;
    float radiusX;
    float radiusY;
    float velocityX;
    float velocityY;
    float gravity;
    float positionX;
    float positionY;
    float restitution;  
    float friction;
    bool hasTouchedGround;
    bool bouncing;
    float bounceTime;
    float initialRadiusX; 
    float initialRadiusY;

    Ball(float m, float rX, float rY, float vX, float vY, float g, float x, float y, float res, float fric) :
        mass(m), radiusX(rX), radiusY(rY), velocityX(vX), velocityY(vY), gravity(g), positionX(x), positionY(y), restitution(res), friction(fric), hasTouchedGround(false), bouncing(false), bounceTime(0.0f), initialRadiusX(rX), initialRadiusY(rY) {}

    void updatePosition(float time);

    void collide(Surface& surface);

    void resetTime();

    void bounce();

};

