# README EXAMEN PARCIAL 2
## Escala
```c++
constexpr float SCALE = 30.0f;
```
Se aplica una escala para corregir los tamaños de box2d y sfml.
## Clases
Tenemos la clase Cube que ayuda a formar cubos con coordenadas dadas y se usa también un bool para determinar si es un cuerpo dínamico o no
```c++
        if (dynamic)
            bodydef.type = b2_dynamicBody;
        else
            bodydef.type = b2_staticBody;
```
Así cambia el tipo del cuerpo, el los parametros por defecto es 'true' para poderlo omitir
### Update
```c++
    void update()
    {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }
```
Se encarga de obtener la posición del elemento en el ciclo while.
### Draw
```c++
    void draw(sf::RenderWindow &win) const
    {
        win.draw(box);
    }
```
Dibuja el elemento en cada paso dentro del ciclo while.
### Reset Position
```c++
    void resetPosition()
    {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }
```
Regresa el objeto a su posicion
### Stop
```c++
    void stop()
    {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }
```
Se usa para llamarse y poder detener el movimiento del objeto.
### Get Body
```c++
    b2Body *getBody()
    {
        return body;
    }
```
Se utiliza este elemento para poder acceder de manera sencilla al body del Cube y asi poder usarla para obtener su posicion por ejemplo.
### Elementos privados
```c++
    sf::RectangleShape box;
    b2Body *body;
```
Se establece para sfml que los Cubes tendran forma de tipo box(caja), ya que son simples cuadrados.
## Clase PolygonShape
### Parámetros extras
```c++
PolygonShape(b2World &world, float x, float y, float p1, float p1_2, float p2, float p2_2, float p3, float p3_2, float p4, float p4_2, float density = 1.0, bool dynamic = false)
```
```c++
        b2Vec2 verCuad[4];
        verCuad[0].Set(p1 / SCALE, p1_2 / SCALE);
        verCuad[1].Set(p2 / SCALE, p2_2 / SCALE);
        verCuad[2].Set(p3 / SCALE, p3_2 / SCALE);
        verCuad[3].Set(p4 / SCALE, p4_2 / SCALE);

        fixturedef.density = density;
```
Los parametros pasados a PolygonShape son en este caso los elementos de las coordenadas de los puntos del poligono para crearlo de manera "dinamica".
### Elementos para SFML
```c++
        polygon.setPointCount(4.f);

        polygon.setPoint(0, sf::Vector2f(p1,p1_2));
        polygon.setPoint(1, sf::Vector2f(p2,p2_2));
        polygon.setPoint(2, sf::Vector2f(p3,p3_2));
        polygon.setPoint(3, sf::Vector2f(p4,p4_2));
        
        polygon.setFillColor(sf::Color::Green);
        polygon.setOrigin(5.f, 5.f);

```
Para SFML se tienen que agregar tambien los puntos y a su vez tambien se puede colorear la imagen y colocar su centro.
### Private
```c++
    sf::ConvexShape polygon;
    b2Body *body;
```
El poligono para sfml debe de tener una forma de poligono convexo, entonces aqui se declara como tal.

## Clase Ball
Una clase para crear pelotas, se usa de parametro el mundo, la posicion, el radio y el bool que determina si es dinamico.
```c++
Ball(b2World &world, float x, float y, float radius, bool dynamic = false)
```
Para SFML tambien se tiene que colocar el origen de la pelota, colorearlo y ponerle el radio.
```c++
        ball.setRadius(radius);
        ball.setOrigin(0.0f, 0.0f);

        ball.setFillColor(sf::Color::Blue);
```

La densidad de la pelota es lo suficientemente alta como para detener en seco el pendulo que la empuja.

## Ventana
```c++
sf::RenderWindow window(sf::VideoMode(1000, 900), "Joints");
```
Se inicializa la ventana.

## Ciclo While
```c++
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                ball1.resetPosition();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                ball1.stop();
                ball2.stop();
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
```
Se encarga de actualizar y dibujar cada figura asi como agregar las funciones necesarias con el teclado tales como stop y reset position.
## Joints
### Distance
```c++
    b2DistanceJointDef distanceJoint;
    distanceJoint.Initialize(cube.getBody(), cube2.getBody(), cube.getBody()->GetWorldCenter(),cube2.getBody()->GetWorldCenter());
    float frequencyHz = 4.0f;
    float dampingRatio = 1.0f;
    b2LinearStiffness(distanceJoint.stiffness, distanceJoint.damping,frequencyHz,dampingRatio,cube.getBody(), cube2.getBody());
    distanceJoint.collideConnected=true;

    world.CreateJoint(&distanceJoint);
```
- Se inicializa un b2DistanceJointDef llamado distanceJoint.
- Se configura el joint de distancia para unir dos cuerpos cube y cube2.
- Se establece una frecuencia y una relación de amortiguamiento para el joint.
- Se permite que los cuerpos conectados colisionen.
- El joint de distancia se crea en el mundo.
### Prismatic
```c++
    b2PrismaticJointDef prismaticJoint;
prismaticJoint.Initialize(cube3.getBody(), cube4.getBody(), cube3.getBody()->GetWorldCenter(), b2Vec2(1.0f, 0.0f));
prismaticJoint.lowerTranslation = -5.0f;
prismaticJoint.upperTranslation = 5.0f;
prismaticJoint.enableLimit = true;

world.CreateJoint(&prismaticJoint);
```
- Se inicializa un b2PrismaticJointDef llamado prismaticJoint.
- Se configura el joint para unir dos cuerpos cube3 y cube4.
- Se establece una limitación en la traslación del joint.
- El joint se crea en el mundo.
### Revolute
```c++
    b2RevoluteJointDef revoluteJoint;
    revoluteJoint.Initialize(cube3.getBody(), cube4.getBody(), cube4.getBody()->GetWorldCenter());
    revoluteJoint.maxMotorTorque = 100.0f;
    revoluteJoint.motorSpeed = 0.2f;
    revoluteJoint.enableMotor = true;

    world.CreateJoint(&revoluteJoint);
```
- Se inicializa un b2RevoluteJointDef llamado revoluteJoint.
- Se configura el joint para unir dos cuerpos cube3 y cube4.
- Se establece un motor en el joint.
- El joint se crea en el mundo.
### Pulley
```c++
    b2PulleyJointDef pulleyDef;

Cube pulleyAnchor1(world,250,300, false);
Cube pulleyAnchor2(world,350,300, false);

b2Vec2 groundAnchor1 = pulleyAnchor1.getBody()->GetWorldCenter();
b2Vec2 groundAnchor2 = pulleyAnchor2.getBody()->GetWorldCenter();
pulleyDef.Initialize(canasta.getBody(),balancin.getBody(),groundAnchor1,groundAnchor2,canasta.getBody()->GetWorldCenter(),balancin.getBody()->GetWorldCenter(),0.5);
world.CreateJoint(&pulleyDef);
```
- Se define un b2PulleyJointDef llamado pulleyDef.
- Se crean dos objetos pulleyAnchor1 y pulleyAnchor2.
- Se establecen puntos de anclaje en el suelo y en los cuerpos canasta y balancin.
- El joint de polea se crea en el mundo.
### Gear
```c++
    auto* joint1 = (b2PrismaticJoint*)world.CreateJoint(&prismaticJoint);
    auto* joint2 = (b2RevoluteJoint*)world.CreateJoint(&revoluteJoint);

    b2GearJointDef gearJointDef;
    gearJointDef.bodyA = cube3.getBody();
    gearJointDef.bodyB = cube4.getBody();
    gearJointDef.joint1 = joint1;
    gearJointDef.joint2 = joint2;
    gearJointDef.ratio = 1.0f;

world.CreateJoint(&gearJointDef);
```
- Se crean los joints prismatic y revolute previamente definidos y se guardan en joint1 y joint2.
- Se inicializa un b2GearJointDef llamado gearJointDef.
- Se configura el joint de engranaje para unir los cuerpos cube3 y cube4.
- La relación de engranaje se establece en 1.0.
- El joint de engranaje se crea en el mundo.
