#include "Ball.h"
#include <Novice.h>  
#include <imgui.h>

void Ball::Initialize()
{
    mass = 10.0f;
    radiusX = 25.0f;
    radiusY = 25.0f;
    velocityX = 0.0f;
    velocityY = 0.0f;
    gravity = 9.8f;
    positionX = 300.0f;
    positionY = 200.0f;
    bouncing = false;
    initialRadiusX = 25.0f;
    initialRadiusY = 25.0f;
    depth = 10.0f;
    range = 30.0f;
    segments = 64.0f;
    frame = 0.03f;
    ball.restitution = 0.5f;
    ball.friction = 0.3f;
    count = 0;
    color = 0xFFFFFFFF;
    angle = 0.0f;
    input_ = Input::GetInstance();
    currentFloor = FloorType::Concrete;
    isFalling = false;
    isRising = false;
    concreteFloor = { 0.0f, 1.0f };
    treeFloor = { 0.5f, 0.3f };
    normalFloor = { 0.5f, 0.1f };
}

void Ball::Update()
{
    float ground = 600.0;
    
    if (velocityY > 0) {
        isFalling = true;
        isRising = false;
    } else if (velocityY < 0) {
        isFalling = false;
        isRising = true;
    } else {
        isFalling = false;
        isRising = false;
    }
    switch (currentFloor) {
    case FloorType::Concrete:
        if (positionY + radiusY < ground) {
            updatePosition();
            radiusX = initialRadiusX;
            radiusY = initialRadiusY;
        } else{ collide(concreteFloor);
        if (!bouncing) {
            radiusX = initialRadiusX;
            radiusY = initialRadiusY;
               }
        }
        break;
    case FloorType::Tree:
        if (positionY + radiusY < ground) {
            updatePosition();
            radiusX = initialRadiusX;
            radiusY = initialRadiusY;
        } else if (mass >= 30.0f) {
            float craterCenterY = 600.0f + depth;
            createCrater(positionX, craterCenterY);
            positionY = craterCenterY - radiusY;
        } else {
            collide(treeFloor);
            radiusX /= 1.5f;
            radiusY /= 0.8f;
            if (!bouncing) {
                radiusX = initialRadiusX;
                radiusY = initialRadiusY;
            }

        }
        break;
    case FloorType::Normal:
        if (positionY + radiusY < ground) {
            updatePosition();
            radiusX = initialRadiusX;
            radiusY = initialRadiusY;
        } else if (mass >= 30.0f) {
            float craterCenterY = 600.0f + depth;
            createCrater(positionX, craterCenterY);
            positionY = craterCenterY - radiusY;
        } else {
            collide(normalFloor);
            radiusX /= 1.5f;
            radiusY /= 0.8f;
            if (!bouncing) {
                radiusX = initialRadiusX;
                radiusY = initialRadiusY;
            }

        }
        break;
    }
    

        float speed = 0.9f;
        bool rightPressed = input_->PushKey(DIK_RIGHT);
        bool leftPressed = input_->PushKey(DIK_LEFT);
        
        if (rightPressed || leftPressed) {
            positionX += rightPressed ? speed : -speed;
        }

       
        if (mass < 30.0f) {
            if (velocityX > 0.4f) {
                if (isFalling && velocityX > 0 && abs(velocityY) > 7.0f) {
                    angle = 2.2f;
                    radiusX /= 1.2f;
                    radiusY /= 0.8f;
                } else if (isRising && velocityX > 0 && abs(velocityY) > 7.0f)
                {
                    angle = 4.0f;
                    radiusX /= 1.2f;
                    radiusY /= 0.8f;
                } else {
                    angle = 0.0f;
                    radiusX = initialRadiusX;
                    radiusY = initialRadiusY;
                }
            }
        }
       
        
        

        ImGui::Begin("Window");
       
        bool isConcrete = (currentFloor == FloorType::Concrete);
        bool isTree = (currentFloor == FloorType::Tree);
        bool isNormal = (currentFloor == FloorType::Normal);

        if (ImGui::Checkbox("Concrete Floor", &isConcrete)) {
            if (isConcrete) {
                currentFloor = FloorType::Concrete;
            }
        }
        if (ImGui::Checkbox("Tree Floor", &isTree)) {
            if (isTree) {
                currentFloor = FloorType::Tree;
            }
        }
        if (ImGui::Checkbox("Normal Floor", &isNormal)) {
            if (isNormal) {
                currentFloor = FloorType::Normal;
                
            }
        }
        ImGui::SliderFloat("ball mass", &mass, 0.0f, 50.0f, "mass = %.3f");
        ImGui::SliderFloat("ball velocityX", &velocityX, 0.0f, 10.0f, "velocityX = %.4f");
        if (currentFloor == FloorType::Normal) {

            ImGui::SliderFloat("ball Restitution", &normalFloor.restitution, 0.0f, 1.0f, "Restitution = %.1f");
            ImGui::SliderFloat("ball Friction", &normalFloor.friction, 0.0f, 1.0f, "Friction = %.1f");
        }
        if (ImGui::Button("Reset Ball")) {
            Reset();
        }
        ImGui::End();
    
}

void Ball::Draw()
{
    Novice::DrawEllipse(int(positionX), int(positionY), int(radiusX), int(radiusY), angle, color, kFillModeSolid);
}

void Ball::updatePosition()
{
    
    positionX += velocityX * frame;

    velocityY += gravity * frame;
    positionY += velocityY * frame;

    
}

void Ball::collide(Surface surface) {
    positionY = 600.0f - radiusY;  

    float effectiveRestitution = (surface.restitution + ball.restitution) / 2.0f;
    velocityY = -velocityY * effectiveRestitution;  

    float effectiveFriction = (surface.friction + ball.friction) / 2.0f;
    float frictionForce = effectiveFriction * mass * gravity;
    float frictionAcceleration = frictionForce / mass;
    velocityY += (velocityY > 0 ? -1 : 1) * frictionAcceleration;
 
    positionY += velocityY;

  

    if (abs(velocityY) < 9.0f) {
        velocityY = 0;
        bouncing = false;
        positionY = 600.0f - radiusY;
    } else {
        bouncing = true; 
    }

    velocityX -= velocityX * effectiveFriction;

    count++;
    radiusX /= 0.8f;
    radiusY /= 1.5f;

}

void Ball::bounce() {
    if (!bouncing) {
        bouncing = true;
    }
}

void Ball::createCrater(float centerX, float centerY)
{
    float step = 2 * range / segments;

    for (int i = 0; i < segments; ++i) {
        float x1 = -range + i * step;
        float x2 = -range + (i + 1) * step;
        float y1 = -(depth / (powf(range, 2))) * (powf(x1, 2));
        float y2 = -(depth / (powf(range, 2))) * (powf(x2, 2));

        Novice::DrawLine(int(centerX + x1),int( centerY + y1),int( centerX + x2), int(centerY + y2), 0xFFFFFFFF);
    }
}

void Ball::Reset()
{
    Initialize();
}


