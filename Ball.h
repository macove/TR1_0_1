#pragma once
#include <iostream>
#include <cmath>
#include <Input.h>

typedef struct {
    float restitution; 
    float friction;    
} Surface;

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
    bool bouncing;
    float initialRadiusX; 
    float initialRadiusY;
    float depth; 
    float range;
    float segments;
    float frame;
    int count;
    int color;

    Surface ball;


   
    void Initialize();

    void Update();

    void Draw();



    void updatePosition();

    void collide(Surface surface);

    void bounce();

    void createCrater(float centerX, float centerY);

private:

    Surface concreteFloor{ 0.7f,0.6f };
    Surface treeFloor{ 0.5f,0.3f };
    Surface normalFloor{ 0.5f,0.5f };
};

