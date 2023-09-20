#include <iostream>
#include <box2d/box2d.h>

int main() {
    //===========SUELO========================================
    //Creacion del mundo y de la gravedad
    b2Vec2 gravity(0.0f, -9.81f);
    b2World world(gravity);

    //Creacion de las caracteristicas del cuerpo del suelo
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -1.62f);

    //Creamos el cuerpo del suelo
    b2Body*groundBody = world.CreateBody(&groundBodyDef);

    //Crear su forma del suelo
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50,1);

    groundBody->CreateFixture(&groundBox, 0.0f);

    //===========OBJETO=======================================
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 20.0);

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body ->CreateFixture(&fixtureDef);

    float timeStep = 1.0f/60.0f;

    int32 velocityIterations = 6;
    int32 positionIteration = 2;

    for (int32 i = 0; i < 60; ++i) {
        world.Step(timeStep, velocityIterations, positionIteration);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x,position.y,angle);
    }

}
