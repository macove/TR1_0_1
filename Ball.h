#pragma once
#include <iostream>
#include <cmath>
#include <Input.h>

enum class FloorType {
    Concrete,
    Tree,
    Normal
};

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
    float angle;
    bool isFalling;
    bool isRising;

    Surface ball;

    FloorType currentFloor;

    Surface concreteFloor;
    Surface treeFloor;
    Surface normalFloor;
   
    void Initialize();

    void Update();

    void Draw();



    void updatePosition();

    void collide(Surface surface);

    void bounce();

    void createCrater(float centerX, float centerY);

    void Reset();

private:

    Input* input_ = nullptr;
   
};

