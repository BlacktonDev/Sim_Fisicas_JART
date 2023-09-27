# Hola Luna

## Código 
Los cambios que `hola_luna` tiene sobre el código de `hola_mundo` son los siguientes:
- Gravedad equivalente a la de la luna `-1.6`
- Fricción nula como sería en el espacio `0.0f`

### Gravedad
```c++
b2Vec2 gravity(0.0f, -1.62f);
```

### Fricción 
```cpp
fixtureDef.friction = 0.0f; 
```

## Ejecución

Las características de la caja son las mismas que en `hola_mundo` solo afecta la velocidad de caída y la distancia recorrida de la caja que en ambos casos es menor. 