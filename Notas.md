## ECS

* Una entidad solo es un numero de ID
* Un componente esta aderido a una entidad:
    * Este solo coniene valores
* Un sistema, maneja los valores de los componentes

### Para Agregar un nuevo Entidad

## Cada componente requiere FORZOSAMENTE constructores con valores por default

```c++

#include <iostream>
#include <vector>

struct Sprite{};

struct Base{
    std::vector<Sprite> v;

    template<class T, class... Ts>
    void dSome( Ts&&... ts) {
        //((std::cout << ", " << ts), ...);
        T t( std::forward<Ts>(ts)...); // <------ AQUI
        v.push_back(t);
    }
};

int main(){

    Base b;
    Sprite s;

    b.dSome<Sprite>();

}
```

En la linea 28 `T t( std::forward<Ts>(ts)...);` Este es el motivo por el cual se requiere valores predeterminados.