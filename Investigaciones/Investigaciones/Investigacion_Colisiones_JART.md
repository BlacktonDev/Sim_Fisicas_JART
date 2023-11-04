# Investigación - Colisiones

## Introducción:
El Módulo de Colisión en Box2D es la parte que se encarga de detectar y manejar las colisiones entre objetos en un entorno 2D. Incluye definiciones de formas, la detección de colisiones amplia, los puntos de contacto y los colectores, y el árbol dinámico.
Desafortunadamente para esta investigación no pude encontrar una fuente confiable que contenga información del modulo de colisiones de Box2D que no sea ni el libro [_Introduction to game Physics with Box2D_](https://www.taylorfrancis.com/books/mono/10.4324/9781315380636/introduction-game-physics-box2d-ian-parberry), ni la [página de la documentación](https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_collision.html) ni el [GitHub de Erincatto](https://github.com/erincatto/box2d). Por lo tanto procederé a presentar mi interpretación de los conceptos presentados en estas fuentes.
## Formas:
El modulo de formas es bastante importante para el modulo de colisiones, en cualquier motor de juego como Unreal Engine 5 o Unity las formas o primitivos tendrían una caja de colisión, en Box2D se tiene la forma en si. Estas formas tienen funciones que permiten probar la superposición, realizar ray cast, calcular AABB (cuadros delimitadores alineados con el eje) y calcular propiedades de masa. El módulo Formas proporciona las herramientas necesarias para representar y manipular las formas físicas de los objetos con precisión. Para esta sección daré una breve explicación de algunas formas de Box2D.
### Círculo
Para crear un circulo se necesita una posición y un radio. Básicamente la posición es el punto central del circulo y el radio se da en centímetros. 
```c++
b2CircleShape circle;
circle.m_p.Set(2.0f, 3.0f);
circle.m_radius = 0.5f;
```
### Polígonos
Para crear un polígono primero se debe de definir el numero de vértices.
```c++
b2Vec2 vertices[3];
```
Posteriormente se deben declarar los vértices (coordenadas) del polígono, debe de ser **en contra de las manecillas del reloj** ya que así se maneja en box2D, con un contador que va en ese sentido. Ejemplo de como se crearía un triangulo con el uso de vértices:
```c++
b2Vec2 vertices[3];

vertices[0].Set(0.0f, 0.0f);
vertices[1].Set(1.0f, 0.0f);
vertices[2].Set(0.0f, 1.0f);

int32 count = 3;
b2PolygonShape polygon;
polygon.Set(vertices, count);
```
### Bordes
Los bordes en Box2D son líneas básicamente, solo de deben de definir los puntos por donde va a pasar con vértices. Bastante parecido a la creación de un polígono, se declaran los vértices de derecha a izquierda. Ejemplo
```c++
b2Vec2 v1(0.0f, 0.0f);
b2Vec2 v2(1.0f, 0.0f);
 
b2EdgeShape edge;
edge.SetTwoSided(v1, v2);
```
Hay un punto muy importante con las colisiones, se puede crear un borde de dos lados donde puede deslizarse una forma dinámica normalmente, sin embargo existen los fantasmas, que es cuando una forma colisiona con un vértice que utiliza Box2D para detectar colisiones, para evitar eso se utilizan los bordes de un solo lado. Ejemplo:
```c++
b2Vec2 v0(1.7f, 0.0f);
b2Vec2 v1(1.0f, 0.25f);
b2Vec2 v2(0.0f, 0.0f);
b2Vec2 v3(-1.7f, 0.4f);
 
b2EdgeShape edge;
edge.SetOneSided(v0, v1, v2, v3);
```
### Cadenas (formas)
Las cadenas sirven para unir varias líneas, es parecido a los bordes de dos lados pero estas ya tienen un sistema anti colisiones fantasma. Los vértices se declaran en el orden que se declararían los vértices de un polígono. Si son declarados al revés, las normales quedarían volteando hacia el centro de la forma suponiendo que es una forma cerrada.
```c++
b2Vec2 vertices[4];
vertices[0].Set(1.7f, 0.0f);
vertices[1].Set(1.0f, 0.25f);
vertices[2].Set(0.0f, 0.0f);
vertices[3].Set(-1.7f, 0.4f);
 
b2ChainShape chain;
chain.CreateLoop(vertices, 4);
```
Como en los polígonos, las líneas formadas por los vértices no deben de superponerse nunca a la hora que son declarados, esto no es soportado por Box2D. 
## Consultas geométricas
Se pueden realizar consultas geométricas que básicamente son comprobaciones de colisiones de Box2D
### Prueba del punto de la forma
Esta función devuelve un valor booleano que indica si el punto hace un overlap con la forma o no. Las cadenas y los bordes siempre van a regresar falso.
```c++
b2Transform transform;
transform.SetIdentity();
b2Vec2 point(5.0f, 2.0f);
 
bool hit = shape->TestPoint(transform, point);
```
### Ray Cast de Forma
Uso de Ray cast a una dorma para tener el punto de su primer interseccion

```c++
b2Transfrom transform;
transform.SetIdentity();
 
b2RayCastInput input;
input.p1.Set(0.0f, 0.0f);
input.p2.Set(1.0f, 0.0f);
input.maxFraction = 1.0f;
int32 childIndex = 0;
 
b2RayCastOutput output;
bool hit = shape->RayCast(&output, input, transform, childIndex);
 
if (hit)
{
    b2Vec2 hitPoint = input.p1 + output.fraction * (input.p2 -- input.p1);
    ...
}
```
Se crea un objeto `b2Transform`  y se establece en la matriz de identidad utilizando la función miembro `SetIdentity()`. Luego, se crea un objeto `b2RayCastInput`.
Luego, se crea un objeto `b2RayCastOutput`. Después, se llama a la función miembro `RayCast()` de `shape` con los argumentos `&output`, `input`, `transform`, y `childIndex`. Esta función devuelve un valor booleano que indica si el rayo intercepta con la forma o no.
Si el valor devuelto es verdadero, entonces el punto de intersección del rayo con la forma se calcula utilizando la fórmula: 
```c++
hitPoint = input.p1 + output.fraction * (input.p2 - input.p1)
```
## Funciones por pares
### Overlap
Existe una función en Box2D para comprobar un overlap o superposición, para esta se deben de brindar los índices hijo.
```c++
b2Transform xfA = ..., xfB = ...;
bool overlap = b2TestOverlap(shapeA, indexA, shapeB, indexB, xfA, xfB);
```
### Puntos de contacto y colectores:
La detección de colisiones es responsable de determinar los puntos de contacto y los colectores de contacto entre objetos en colisión. Los colectores de contacto constan de una normal de contacto y uno o dos puntos de contacto (por ejemplo, sin un circulo colisiona con un cuadrado o poligono, habrá solo un punto de contacto pero si es cuadrado con cuadrado serian dos puntos ). Estos puntos de contacto representan aproximaciones discretas de regiones continuas de contacto. Ejemplo para obtener estos puntos:
```c++
b2WorldManifold worldManifold;
worldManifold.Initialize(&manifold, transformA, shapeA.m_radius,
transformB, shapeB.m_radius);
 
for (int32 i = 0; i \< manifold.pointCount; ++i)
{
    b2Vec2 point = worldManifold.points[i];
    ...
}
```
La clase `b2WorldManifold` se utiliza para calcular la información de contacto entre dos formas. En este caso, se inicializa con los objetos `manifold`, `transformA`, `shapeA.m_radius`, `transformB` y `shapeB.m_radius`. El bucle `for` itera sobre los puntos de contacto y los almacena en el objeto `point`. 
### Distance
Existe una funcion llamada b2Distance que se usa para calcular la distancia entre 2 formas. Para usar esta funcion necesitas obtener el b2DistanceProxy de los 2 cuerpos. Ejemplo:
Supongamos que tenemos dos cuerpos, bodyA y bodyB, y queremos calcular la distancia entre ellos. Primero, creamos dos objetos b2DistanceProxy para cada cuerpo.
```c++
b2DistanceProxy proxyA, proxyB;
bodyA->GetFixtureList()->CreateProxy(&proxyA, 0);
bodyB->GetFixtureList()->CreateProxy(&proxyB, 0);
```
Luego, creamos dos objetos b2Transform para cada cuerpo.
```c++
b2Transform transformA = bodyA->GetTransform();
b2Transform transformB = bodyB->GetTransform();
```
Finalmente, llamamos a la función b2Distance y pasamos los objetos 
```c++
float32 distance = b2Distance(&proxyA, &transformA, &proxyB, &transformB);
```
## Árbol dinámico:
El módulo de colisión utiliza una estructura de datos de árbol dinámico para organizar objetos de manera eficiente para la detección de colisiones de fase amplia. Esta estructura de datos utiliza cuadros delimitadores alineados axialmente (AABB) para representar la extensión de los objetos. El árbol dinámico permite una rápida inserción, eliminación y consulta de objetos, lo que permite una iteración eficiente a través de pares de colisiones. Al utilizar el árbol dinámico, Box2D optimiza la detección y respuesta de colisiones, mejorando el rendimiento y la precisión.
## Detección de colisiones de fase amplia:
El módulo de colisión incorpora detección de colisiones de fase amplia, cuyo objetivo es reducir el número de pruebas de colisión organizando objetos utilizando una estructura de datos de árbol dinámica. Este árbol dinámico itera eficientemente a través de pares de colisiones, lo que mejora significativamente el rendimiento. Al utilizar la detección de colisiones de fase amplia, Box2D puede identificar rápidamente posibles candidatos a colisiones, lo que reduce la carga computacional y mejora la eficiencia general.
## Conclusiones:
Box2D tiene similitudes con motores gráficos avanzados como Unreal Engine y Unity como por ejemplo la verificación de superposición que en Unreal seria el nodo OnBeginOverlap y en Unity seria algo así como OnCollisionEnter, sin embargo tiene algunas funciones como tomar la distancia entre 2 formas o el método que sirve para obtener los puntos de colisión que no he usado jamás en los motores mencionados. Para usar adecuadamente el modulo de colisiones es necesario conocer los principios básicos de las formas mencionados en esta investigación. El orden que maneja Box2D y el concepto de colisiones fantasmas.
## Referencias

[1]  E. Catto, «Box2D: Collision module». https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_collision.html (accedido 6 de octubre de 2023).
[2]  I. Parberry, _Introduction to game Physics with Box2D_. 2013. doi: 10.1201/b14539.
[3]  Erincatto, «GitHub - erincatto/box2d: Box2D is a 2D physics engine for games», _GitHub_. https://github.com/erincatto/box2d#collision (accedido 6 de octubre de 2023).
[4] U. Technologies, «Unity - Scripting API: Collider.OnCollisionEnter(Collision)». https://docs.unity3d.com/ScriptReference/Collider.OnCollisionEnter.html (accedido 6 de octubre de 2023).
[5] Epic Games, «Collision», _Unreal Engine Documentation_. https://docs.unrealengine.com/5.0/en-US/BlueprintAPI/Collision/ (accedido 6 de octubre de 2023).