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
            bodydef.type = b2_dynamicBody;
        else
            bodydef.type = b2_staticBody;
        body = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(15.f, 15.f));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(0.f, 0.f);
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

class Ball {
public:
    Ball(b2World &world, float x, float y, float radius, bool dynamic = false)
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

        b2CircleShape circle;
        circle.m_p.Set(10.0f /SCALE,10.0f /SCALE);
        circle.m_radius = radius /SCALE;

        b2FixtureDef fixturedef;
        fixturedef.shape = &circle;
        fixturedef.density = 2.0f;
        body->CreateFixture(&fixturedef);

        ball.setRadius(radius);
        ball.setOrigin(0.0f, 0.0f);

        ball.setFillColor(sf::Color::Blue);
    }

    void update()
    {
        ball.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        ball.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const
    {
        win.draw(ball);
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
    sf::CircleShape ball;
    b2Body *body;
};

class PolygonShape {
public:
    PolygonShape(b2World &world, float x, float y, float p1, float p1_2, float p2, float p2_2, float p3, float p3_2, float p4, float p4_2, float density = 1.0, bool dynamic = false)
    {

        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        //Agrega la caresteristica de poder elegir si el cuerpo es dinamico o no con un parametro booleano
        if (dynamic)
            bodydef.type = b2_dynamicBody;
        else
            bodydef.type = b2_staticBody;
        body = world.CreateBody(&bodydef);

        b2Vec2 verCuad[4];
        verCuad[0].Set(p1 / SCALE, p1_2 / SCALE);
        verCuad[1].Set(p2 / SCALE, p2_2 / SCALE);
        verCuad[2].Set(p3 / SCALE, p3_2 / SCALE);
        verCuad[3].Set(p4 / SCALE, p4_2 / SCALE);

        b2PolygonShape shape;
        shape.Set(verCuad,4);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
        fixturedef.friction = 1.0f;
        body->CreateFixture(&fixturedef);

        polygon.setPointCount(4.f);
        polygon.setPoint(0, sf::Vector2f(p1,p1_2));
        polygon.setPoint(1, sf::Vector2f(p2,p2_2));
        polygon.setPoint(2, sf::Vector2f(p3,p3_2));
        polygon.setPoint(3, sf::Vector2f(p4,p4_2));
        polygon.setFillColor(sf::Color::Green);
        polygon.setOrigin(5.f, 5.f);

    }

    void update()
    {
        polygon.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        polygon.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const
    {
        win.draw(polygon);
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
    sf::ConvexShape polygon;
    b2Body *body;
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Joints");


    b2Vec2 gravity(0.0f, 0.04f);
    b2World world(gravity);
    //Distance Joint
    Cube cube(world, 90, 300,false);
    Cube cube2(world, 0, 300, true);

    //Revolute, Prismatic y Gear Joint
    Cube cube3(world, 500, 500, true);
    Cube cube4(world, 600, 500, true);

    //Wheel Joint
    Cube anchorCube (world, 460, 310, false);
    Cube cube5(world, 460, 310, true); //ancla para soldadura
    PolygonShape pared2(world,400,320,  0.0f, -0.0f, 150.0f, 0.0f, 150.0f, -10.0f, 0.0f, -10.0f,2.0f, false);

    //Pelotas
    Ball ball1(world, 100, 368, 10, true);
    Ball ball2(world, 430, 200, 10, true);
    ball2.getBody()->ApplyForceToCenter(b2Vec2(-2.0f,0.0f), true);

    //Plataformas===============================================================================================

    PolygonShape plataforma(world,90,400, 0.0f, 0.0f, 100.0f, 0.0f, 150.0f, 80.0f, 0.0f, 80.0f,1.0f, false);
    PolygonShape plataforma2(world,350,600, 0.0f, 0.0f, 100.0f, 0.0f, 100.0f, -10.0f, 0.0f, -10.0f,2.0f, false);
    PolygonShape plataforma3(world,500,700, 0.0f, 0.0f, 100.0f, 0.0f, 100.0f, -10.0f, 0.0f, -10.0f,2.0f, false);

    PolygonShape canasta(world,250,500, 0.0f, 0.0f, 50.0f, 50.0f, 100.0f, 0.0f, 50.0f, 100.0f,1.0f, true);

    PolygonShape balancin(world,320,400,  0.0f, 0.0f, 100.0f, 0.0f, 100.0f, -10.0f, 0.0f, -10.0f,2.0f, true);

    PolygonShape piso(world,10,900,  0.0f, 0.0f, 1000.0f, 0.0f, 1000.0f, -10.0f, 0.0f, -10.0f,2.0f, false);

    //Distance Joint ===================================================================================================
    b2DistanceJointDef distanceJoint;
    distanceJoint.Initialize(cube.getBody(), cube2.getBody(), cube.getBody()->GetWorldCenter(),cube2.getBody()->GetWorldCenter());
    float frequencyHz = 4.0f;
    float dampingRatio = 1.0f;
    b2LinearStiffness(distanceJoint.stiffness, distanceJoint.damping,frequencyHz,dampingRatio,cube.getBody(), cube2.getBody());
    distanceJoint.collideConnected=true;

    world.CreateJoint(&distanceJoint);

    //Prismatic Joint ==================================================================================================
    b2PrismaticJointDef prismaticJoint;
    prismaticJoint.Initialize(cube3.getBody(), cube4.getBody(), cube3.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
    prismaticJoint.lowerTranslation = -5.0f;
    prismaticJoint.upperTranslation = 5.0f;
    prismaticJoint.enableLimit = true;

    world.CreateJoint(&prismaticJoint);

    //Revolute Joint ===================================================================================================
    b2RevoluteJointDef revoluteJoint;
    revoluteJoint.Initialize(cube3.getBody(), cube4.getBody(), cube3.getBody()->GetWorldCenter());
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
    wheelJoint.Initialize(cube5.getBody(),pared2.getBody(),cube5.getBody()->GetWorldCenter(),b2Vec2(0.0,0.0));
    wheelJoint.maxMotorTorque = 10.0;
    wheelJoint.motorSpeed = 10.0f;
    wheelJoint.enableMotor = false;

    b2WheelJoint* wheelJointPtr = (b2WheelJoint*)world.CreateJoint(&wheelJoint);

    wheelJointPtr->SetMaxMotorTorque(1);
    wheelJointPtr->SetMotorSpeed(0.0);
    wheelJointPtr->SetLimits(0,0);


    //Weld
    b2WeldJointDef weldJoint;
    b2Vec2 weldCoord = cube5.getBody()->GetWorldCenter();
    weldJoint.Initialize(anchorCube.getBody(),cube5.getBody(),weldCoord);
    world.CreateJoint(&weldJoint);

    //Polea=============================================================================================================

    b2PulleyJointDef pulleyDef;

    Cube pulleyAnchor1(world,250,300, false);
    Cube pulleyAnchor2(world,350,300, false);

    b2Vec2 groundAnchor1 = pulleyAnchor1.getBody()->GetWorldCenter();
    b2Vec2 groundAnchor2 = pulleyAnchor2.getBody()->GetWorldCenter();
    pulleyDef.Initialize(canasta.getBody(),balancin.getBody(),groundAnchor1,groundAnchor2,canasta.getBody()->GetWorldCenter(),balancin.getBody()->GetWorldCenter(),0.5);
    world.CreateJoint(&pulleyDef);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {

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
        pared2.update();
        plataforma.update();
        plataforma2.update();
        plataforma3.update();
        ball1.update();
        ball2.update();
        canasta.update();
        balancin.update();
        pulleyAnchor1.update();
        pulleyAnchor2.update();
        piso.update();

        window.clear();
        cube.draw(window);
        cube2.draw(window);
        cube3.draw(window);
        cube4.draw(window);
        cube5.draw(window);
        pared2.draw(window);
        plataforma.draw(window);
        plataforma2.draw(window);
        plataforma3.draw(window);
        ball1.draw(window);
        ball2.draw(window);
        canasta.draw(window);
        balancin.draw(window);
        pulleyAnchor1.draw(window);
        pulleyAnchor2.draw(window);
        piso.draw(window);

        window.display();
    }
    return 0;
}