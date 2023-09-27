# Hola mundo
Código de C++ con el uso de Box2D que simula una caja en caída libre hacia una superficie plana.
## Definición de la gravedad y el mundo
**b2Vec2 gravity** es un vector 2D donde se definen las fuerzas, la gravedad es una fuerza vertical entonces no se agrega ninguna fuerza en el eje horizontal 
```cpp
b2Vec2 gravity(0.0f, -9.81f);  
b2World world(gravity);
```
Después se le agrega la fuerza a una nueva variable **world** que sería el contexto.
### Definición de los cuerpos
Primero se define el polígono en este caso, después se le da forma de "caja" con una anchura muy grande y una altura muy pequeña para poder simular un suelo. A la caja que caerá se le agrega el tipo `b2_dinamicBody` ya que no será un objeto estático como el suelo. La caja estará a 20 metros sobre el suelo y medirá 1x1.

```c++
b2PolygonShape groundBox;  
groundBox.SetAsBox(50,1);  
  
groundBody->CreateFixture(&groundBox, 0.0f);  
  
b2BodyDef bodyDef;  
bodyDef.type = b2_dynamicBody;  
bodyDef.position.Set(0.0f, 20.0);  
  
b2Body* body = world.CreateBody(&bodyDef);  
  
b2PolygonShape dynamicBox;  
dynamicBox.SetAsBox(1.0f, 1.0f);
```
### Definición de las características físicas de la caja
Se le agregan cualidades físicas a la caja
```c++
b2FixtureDef fixtureDef;  
fixtureDef.shape = &dynamicBox;  
fixtureDef.density = 1.0f;  
fixtureDef.friction = 0.3f;  
```
La variable de tipo **b2FixtureDef** es una estructura que almacena ciertas características físicas.
`fixtureDef.shape` La forma que va a tomar la caja
`fixtureDef.density` La densidad que va a tener la caja
`fixtureDef.friction;` La fricción que va a tener la caja
```cpp
body ->CreateFixture(&fixtureDef);  
```
`CreateFixture` llena el cuerpo físico con una nueva colisión con las propiedades dadas en **fixtureDef**.
### Tiempo
`timeStep` establece el intervalo que va a durar, en este caso es un segundo sobre sesenta. 
```cpp
float timeStep = 1.0f/60.0f;  
```

  ```cpp
int32 velocityIterations = 6;  
int32 positionIteration = 2;  
```
Aumentar o disminuir el numero de iteraciones en velocidad o posición aumenta o disminuye la precisión de la simulación.
```cpp
for (int32 i = 0; i < 60; ++i) {  
    world.Step(timeStep, velocityIterations, positionIteration);  
    b2Vec2 position = body->GetPosition();  
    float angle = body->GetAngle();  
    printf("%4.2f %4.2f %4.2f\n", position.x,position.y,angle);  
}
```
  
Este es un bucle que se ejecuta 60 veces. En cada iteración, se llama a la función `Step` del objeto `world` de Box2D, que actualiza la simulación física e imprime la posición de la caja en cada paso (60 veces con un paso de 1 segundo / 60). 