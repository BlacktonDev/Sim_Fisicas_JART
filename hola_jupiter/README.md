# Hola Júpiter

## Código 
Los cambios que `hola_jupiter` tiene sobre el código de `hola_mundo` y `hola_luna` son los siguientes:
- Gravedad equivalente a la de Jupiter `-24.79 m/s^2^ `
- Fricción aumentada por la atmosfera cubierta de gases de Júpiter  `0.9f`
- Altura de la nueva caja: `15m`
- Material de la caja: Carburo de Tungsteno = `15600 km*m^3^`

### Gravedad
```c++
b2Vec2 gravity(0.0f, -24.79f);
```
### Fricción 
```cpp
fixtureDef.friction = 0.9f; 
```
### Altura de la caja
```cpp
bodyDef.position.Set(0.0f, 15.0);
```
### Densidad
```cpp
fixtureDef.density = 15600.0f; //densidad del carburo de tungsteno
```

## Ejecución

En este caso las características de la caja cambian, la `densidad` de la caja es mucho mayor, su posición sobre el suelo es menor esto ocasiona que la velocidad de caída y la distancia recorrida de la caja que en ambos casos sea mayor. 