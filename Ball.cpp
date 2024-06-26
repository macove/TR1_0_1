#include "Ball.h"

#include <vector>
#include <utility> 
#include <cmath>   

void Ball::Initialize()
{
    mass = 10.0f;
    radiusX = 25.0f;
    radiusY = 25.0f;
    velocityX = 0.3f;
    velocityY = 10.0f;
    gravity = 9.8f;
    positionX = 300.0f;
    positionY = 200.0f;
    restitution = 0.5f;
    friction = 0.3f;
    bouncing = false;
    initialRadiusX = 0.0f;
    initialRadiusY = 0.0f;
    depth = 10.0f;
    range = 30.0f;
    segments = 64.0f;
    frame = 0.3f;
}

void Ball::Update()
{

}

void Ball::Draw()
{

}

void Ball::updatePosition()
{
    

    positionX += velocityX * frame;

    velocityY += gravity * frame;
    positionY += velocityY * frame;

    std::cout << "New position: " << positionY << ", New velocity: " << velocityY << std::endl;
}

void Ball::collide(Surface& surface) {
    positionY = 600.0f - radiusY;  

    float effectiveRestitution = (restitution + surface.restitution) / 2.0f;
    velocityY = -velocityY * effectiveRestitution;  

    float effectiveFriction = (friction + surface.friction) / 2.0f;
    float frictionForce = effectiveFriction * mass * gravity;
    float frictionAcceleration = frictionForce / mass;
    velocityY += (velocityY > 0 ? -1 : 1) * frictionAcceleration;
    if (velocityY <= -5.0f) {
   
    bounce();
    } else { bouncing = false; }

    positionY += velocityY;


    if (std::abs(velocityY) < 10.0f) {
        velocityY = 0;
    }

    velocityX -= velocityX * effectiveFriction;

    std::cout << "New velocity after collision: " << velocityY << std::endl;

    if (mass >= 30.0f) {
        float craterCenterY = 600.0f + depth;
        createCrater(positionX, craterCenterY);
    }
}

void Ball::bounce() {
    if (!bouncing) {
        bouncing = true;
    }
}

void Ball::createCrater(float centerX, float centerY)
{
    std::vector<std::pair<float, float>> craterPoints;
    float step = 2 * range / segments;

    for (int i = 0; i <= segments; ++i) {
        float x = -range + i * step;
        float y = -(depth / static_cast<float>(std::pow(range, 2))) * static_cast<float>(std::pow(x, 2));
        craterPoints.push_back(std::make_pair(centerX + x, centerY + y));
    }

    for (const auto& point : craterPoints) {
        std::cout << "Crater point: (" << point.first << ", " << point.second << ")" << std::endl;
    }
}


