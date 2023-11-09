#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Cube {
public:
    Cube(b2World &world, float x, float y, bool dynamic = false)
    {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        //Agrega la caresteristica de poder elegir si el cuerpo es dinamico o no con un parametro booleano
        if (dynamic)
        {
            bodydef.type = b2_dynamicBody;
        } else
        {
            bodydef.type = b2_staticBody;
        }
        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(10.f, 10.f));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(5.f, 5.f);
    }

    void update()
    {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const
    {
        win.draw(box);
    }

    void resetPosition()
    {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }

    void stop()
    {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    b2Body *getBody()
    {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Joints");

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);
    //Distance Joint
    Cube cube(world, 100, 500,false);
    Cube cube2(world, 200, 500, true);

    //Revolute, Prismatic y Gear Joint
    Cube cube3(world, 500, 500, true);
    Cube cube4(world, 600, 500, true);

    //Wheel Joint
    Cube cube5(world, 100, 200, false);
    Cube cube6(world, 200, 200, true);

    //Weld Joint
    Cube cube7(world, 500, 200, false);
    Cube cube8(world, 600, 200, true);



    //Distance Joint ===================================================================================================
    b2DistanceJointDef distanceJoint;
    distanceJoint.Initialize(cube.getBody(), cube2.getBody(), cube.getBody()->GetWorldCenter(),cube2.getBody()->GetWorldCenter());
    float frequencyHz = 4.0f;
    float dampingRatio = 5.0f;
    b2LinearStiffness(distanceJoint.stiffness, distanceJoint.damping,frequencyHz,dampingRatio,cube.getBody(), cube2.getBody());
    distanceJoint.collideConnected=true;

    world.CreateJoint(&distanceJoint);

    cube2.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 5.0f), true);


    //Prismatic Joint ==================================================================================================
    b2PrismaticJointDef prismaticJoint;
    prismaticJoint.Initialize(cube3.getBody(), cube4.getBody(), cube3.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
    prismaticJoint.lowerTranslation = -5.0f;
    prismaticJoint.upperTranslation = 5.0f;
    prismaticJoint.enableLimit = true;


    world.CreateJoint(&prismaticJoint);

    //Revolute Joint ===================================================================================================
    b2RevoluteJointDef revoluteJoint;
    revoluteJoint.Initialize(cube3.getBody(), cube4.getBody(), cube4.getBody()->GetWorldCenter());
    revoluteJoint.maxMotorTorque = 100.0f;
    revoluteJoint.motorSpeed = 0.2f;
    revoluteJoint.enableMotor = true;

    world.CreateJoint(&revoluteJoint);


    //Gear Joint =======================================================================================================
    auto* joint1 = (b2PrismaticJoint*)world.CreateJoint(&prismaticJoint);
    auto* joint2 = (b2RevoluteJoint*)world.CreateJoint(&revoluteJoint);

    b2GearJointDef gearJointDef;
    gearJointDef.bodyA = cube3.getBody();
    gearJointDef.bodyB = cube4.getBody();
    gearJointDef.joint1 = joint1;
    gearJointDef.joint2 = joint2;
    gearJointDef.ratio = 1.0f;

    world.CreateJoint(&gearJointDef);

    //Wheel Joint ======================================================================================================
    b2WheelJointDef wheelJoint;
    wheelJoint.Initialize(cube5.getBody(),cube6.getBody(),cube5.getBody()->GetWorldCenter(),b2Vec2(0.0,0.0));
    wheelJoint.maxMotorTorque = 10.f;
    wheelJoint.motorSpeed = 0.1f;
    wheelJoint.enableMotor = true;
    world.CreateJoint(&wheelJoint);

    //Weld Joint =======================================================================================================
    b2WeldJointDef weldJoint;
    weldJoint.Initialize(cube7.getBody(),cube8.getBody(),cube7.getBody()->GetWorldCenter());
    world.CreateJoint(&weldJoint);

    cube8.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 5.0f), true);//no se mueve ni aplicando la fuerza ya que esta fijado a un objeto estatico

    //==================================================================================================================
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                cube3.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                cube3.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                cube3.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                cube3.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                cube3.resetPosition();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                cube3.stop();
                cube4.stop();
            }

            // The Z key event to close the window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                window.close();
                return 0; // return from the main function, effectively ending the program
            }
        }

        world.Step(1 / 60.f, 8, 3);
        cube.update();
        cube2.update();
        cube3.update();
        cube4.update();
        cube5.update();
        cube6.update();
        cube7.update();
        cube8.update();

        window.clear();
        cube.draw(window);
        cube2.draw(window);
        cube3.draw(window);
        cube4.draw(window);
        cube5.draw(window);
        cube6.draw(window);
        cube7.draw(window);
        cube8.draw(window);
        window.display();
    }
    return 0;
}