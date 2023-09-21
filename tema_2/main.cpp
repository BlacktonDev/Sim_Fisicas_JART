#include <iostream>
#include <box2d/box2d.h>
#include <cmath>

#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

int main() {

    //Creacion del mundo y de la gravedad
    b2Vec2 gravity(0.0f, -9.81f); //con gravedad de la tierra
    b2World world(gravity);

    //Crea un dynamicBody para la bala
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f,0.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    //Define otra caja para la bala
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.2f,0.5f);

    //define el fixture de la bala
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.01f;
    fixtureDef.friction = 0.3f;

    //agrega la forma al cuerpo
    body->CreateFixture(&fixtureDef);

    //Establece la velocidad inicial del cuerpo
    float angle = 45.0f;//angulo en grados
    float speed = 400.0f; //velocidad en m/s
    float vx = speed * std::cos(angle * M_PI / 180.0f);
    float vy = speed * std::sin(angle * M_PI / 180.0f);

    body->SetLinearVelocity(b2Vec2(vx,vy));

    //Simula el mundo
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for(int i = 0; i<60 ; i++)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        std::cout << body->GetPosition().x << " " << body->GetPosition().y << std::endl;

    }

    // destruye la bala
    world.DestroyBody(body);

    return 0;
}

