#include "Ball.h"

void Ball::updatePosition(float time)
{
    positionX += velocityX * time;

    velocityY += gravity * time; 
    positionY += velocityY * time; 
    std::cout << "New position: " << positionY << ", New velocity: " << velocityY << std::endl;
}

void Ball::collide(Surface& surface) {
    positionY = 600.0f - radiusY;  

    hasTouchedGround = true;

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
}

void Ball::resetTime()
{
}

void Ball::bounce() {
    if (!bouncing) {
        bouncing = true;
        bounceTime = 0.0f;
    }
}