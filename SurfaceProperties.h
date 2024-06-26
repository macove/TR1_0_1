#pragma once

typedef struct {
    float restitution; // ???
    float friction;    // ???
} Surface;


class SurfaceProperties
{
public:
    Surface concreteFloor{ 0.7f,0.6f };
    Surface treeFloor{ 0.5f,0.3f };
    Surface normalFloor{ 0.5f,0.5f };


private:
    
};

