# Todo

- Buscar `*std::ranges::find(m_entities, entity.GetID(), &Entity::GetID);` y quitar el primer asterisco, este da
  problemas para ver si existe o no

# ECS

- Una entidad solo es un numero de ID
- Un componente esta aderido a una entidad:
    - Este solo coniene valores
- Un sistema, maneja los valores de los componentes

## Sistemas

- Cuando se cree un sistema, con el constructor va a agregar que componentes requiere.
    - Estos se van "Agregando" por bits: `m_componentSignature.set(componentID)`
    - Por ejemplo: Sprite su ID es 1, RigidBody es 3
        - El bitset va a ser: **00000101**
    - Una vez que pase un frame, va a buscar que entidades va a agregar a cada sistema.

```c++
RequireComponent<TransformComponent>();
RequireComponent<RigidBodyComponent>();
```

## Para Agregar un nuevo Entidad

### Cada componente requiere FORZOSAMENTE constructores con valores por default

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

--------------------------

# CMAKE

## Static & Shared libs

Para cambiar entre Static y Shared, en el CMakeLists.txt root, habilitar

```cmake
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

if (BUILD_SHARED_LIBS)
    message(STATUS "\n -- BUILD_SHARED_LIBS ON ${BUILD_SHARED_LIBS}")
else ()
    message(STATUS "\n -- BUILD_SHARED_LIBS OFF ${BUILD_SHARED_LIBS}")
    ## Des-habilitar para que SHARED LIBS funcione
    #    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
    set(CMAKE_VISIBILITY_INLINES_HIDDEN "YES")
endif ()
```

### Conan

Habilitar Shared libs en Conan

```shell
[options]
*:shared=True  ## Make Shared libs
```

--------------------------

# Libs

## fmt

- Si da problemas con `consteval`, usar: `fmt::runtime( msg )`

```c++
    fmt::print(fmt::emphasis::bold | color, fmt::runtime(msg), message);
```

## Ranges

### Borrar un elemento de un vector

```c++

  // OK
  auto it = std::find(m_entities.begin(), m_entities.end(), entity);
  if (it != m_entities.end()) { m_entities.erase(it); }

  // OK
   m_entities.erase(
     std::find_if(
       m_entities.begin(),
       m_entities.end(),
       [entity](const std::reference_wrapper<Entity>& ref) {
     return ref.get().GetID() == entity.GetID();
   }
     )
   );

  // OK
   auto it = std::find(m_entities.begin(), m_entities.end(), entity);
   if (it != m_entities.end()) { m_entities.erase(it); }

  // Ok Old
   m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());

  // Ok New
  auto [start, end] { std::ranges::remove(m_entities, entityID, &Entity::GetID) };
  // auto [start, end] { std::ranges::remove(m_entities, entity) };
  // std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
  m_entities.erase(start, end);

```

---

# Advertencias

## CollisionSystem

> Si da problemas con los coliders circuales, en CollisionSystem esta dividiendo la escala por 2

```c++
return AABBCheckBoxCircle(
      abox->position + aTransform.position,
      abox->size * aTransform.scale,
      bcircle->position + bTransform.position,
      bcircle->radius * (bTransform.scale.x / 2)
    );
```

## Input

> Revisar el input cuando suelta/release un button, por que toma tanto el teclado como el control