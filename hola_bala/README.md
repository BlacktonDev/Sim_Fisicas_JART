# Hola Bala
`hola_bala` es mas diferente a `hola_mundo ` en este código no se crea un suelo ya que se realizará un tiro parabólico de lo que es una "bala". Pero no solo es un tiro parabólico, aquí están los cambios principales

- Gravedad equivalente a la de la luna `-1.6`
- Fricción nula como sería en el espacio `0.0f`
- Ángulo de tiro de `60°` 
- Velocidad de la bala de `900 km/h`
- Densidad aproximada a una bala de cañón de hierro de ``30cm`` de diámetro. 
- No hay necesidad de crear un suelo

## Creación de la bala
Al ser una bala de cañón esta deberá ser circular, entonces después de crear su `dynamicBody` definimos su forma circular asignando el valor del elemento `m_radius` a `15 cm` que se encuentra en la estructura de datos de la variable de tipo `b2CircleShape`. 
```cpp
b2CircleShape dynamicCircle;  
dynamicCircle.m_radius=15.0f;
```
Usualmente se usa otro valor para la posicion pero esta puede ser definida por:
```cpp
bodyDef.position.Set(0.0f,0.0f);
```
### Gravedad
```c++
b2Vec2 gravity(0.0f, -1.62f);
```
### Fricción 
```cpp
fixtureDef.friction = 0.0f; 
```
### Tiro

Se establece el ángulo de tiro en `60°`
```cpp 
float angle = 60.0f;
```
Se establece su velocidad en `900 km/h` que traducido a `m/s` es de `250 m/s`
```cpp
float speed = 250.0f;
```
Se saca el seno para la componente vertical y coseno para la componente horizontal y también se convierte a radianes. Para esto se usa `cmath`
```cpp
float vx = speed * std::cos(angle * M_PI / 180.0f);  
float vy = speed * std::sin(angle * M_PI / 180.0f);
```
Se le aplica el vector resultante a la bala con `SetLinearVelocity` introduciendo los datos del `b2Vec2` con `vx` y `vy` anteriormente establecidos.
```cpp
body->SetLinearVelocity(b2Vec2(vx,vy));
```
