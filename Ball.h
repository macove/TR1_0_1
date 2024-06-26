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
    bool bouncing;
    float initialRadiusX; 
    float initialRadiusY;
    float depth; 
    float range;
    float segments;
    float frame;



   
    void Initialize();

    void Update();

    void Draw();



    void updatePosition();

    void collide(Surface& surface);

    void bounce();

    void createCrater(float centerX, float centerY);
};

