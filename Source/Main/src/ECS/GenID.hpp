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

struct IGenID {
 protected:
  static uint16_t m_nextID;
};

template<typename T> class GenID : public IGenID {
  // static uint16_t my_id;
 public:
  // Regresa un unico ID de Component<T>
  static constexpr auto ID() -> uint16_t {
    // my_id++;
    // my_id: Ese solo se incrementara, cuando existan 2 clases iguales
    // m_nextID: desde IComponent, se incrementa, al agregar cualquier clase
    // Se usa id, para tener la enumeración desde 0, ya que nextID, inicia
    // desde 1
    static uint16_t id = m_nextID++;
    return id;
  }
};

#endif // GENID_HPP
