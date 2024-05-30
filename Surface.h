#pragma once
#include <iostream>
#include <cmath>

class Surface
{


public:
    float restitution;
    float friction;   
    

    Surface(float res, float fric) : restitution(res), friction(fric) {}

    //void deform(float impactEnergy);
    //
    //void updateWave(float timeStep);

};

