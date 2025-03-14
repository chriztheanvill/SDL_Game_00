//
// Created by cris on 8/14/24.
//

#ifndef GENID_HPP
#define GENID_HPP

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <expected> // https://en.cppreference.com/w/cpp/utility/expected
#include <functional>
#include <map>
#include <memory>
#include <ranges>
#include <set>
#include <typeindex>
#include <vector>

constexpr uint16_t MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

/** @brief Tener aparte la variable estatica, es para incementar, por tipo (T)
 *
 */
struct IGenID {
 protected:
  static uint64_t m_nextID;
};

/** @brief Solo se incrementara cada vez que se cree un nuevo componente (T)
 *
 */
template<typename T> class GenID : public IGenID {
 public:
  // Regresa un unico ID por cada Component<T>
  static constexpr auto ID() -> uint64_t {
    // my_id++;
    // my_id: Ese solo se incrementara, cuando existan 2 clases iguales

    // m_nextID: desde IGenID, se incrementa, al agregar cualquier clase
    // Se usa id, para tener la enumeración desde 0, ya que nextID, inicia
    // desde 1
    static uint64_t id = m_nextID++;
    return id;
  }
};

#endif // GENID_HPP

       /*

# Sin usar templates, y tratar de usar una clase base.
## No incrementara nada

struct Start {
  static int idStart;
};

struct DataItem : public Start {
  static auto GetID()->int{
    static int id = idStart++;
    return id;
  }
};

===============================
# Solo va a incrementar por el numero de tipo de DataItems: A, B

template <class T>
struct DataItem {
  static auto GetID()->int{
    static int id;
    return id++;
  }
};

int Start::idStart = 0;

struct A{};
struct B{};

int main() {

  auto a = std::make_unique<DataItem<A>>();

  std::cout << "\n ---  A: " << DataItem<A>::GetID();
  std::cout << "\n ---  A: " << DataItem<A>::GetID();
  std::cout << "\n ---  A: " << DataItem<A>::GetID();
  std::cout << "\n ---  B: " << DataItem<B>::GetID();
  std::cout << "\n ---  B: " << DataItem<B>::GetID();
}


---  A: 0
---  A: 1
---  A: 2
---  B: 0
---  B: 1

===============================
# Incrementar por el numero de veces que se llama GetID()

struct DataItem {
  static auto GetID()->int{
      static int id;
      return id++;
  }

  void dSome() { std::cout << "\n DataItem dSome: " << GetID(); }
};

// int DataItem::id = 0; // Error, por que no es un miembro de la clase

int main() {
  auto a = std::make_shared<DataItem>();
  auto b = std::make_shared<DataItem>();
  auto c = std::make_shared<DataItem>();

  a->dSome();
  b->dSome();
  c->dSome();

  std::cout << "\n ---  main: " << DataItem::GetID();
  std::cout << "\n ---  main: " << DataItem::GetID();
}

DataItem dSome: 0
DataItem dSome: 1
DataItem dSome: 2
---  main: 3
---  main: 4


       ================================================
       */