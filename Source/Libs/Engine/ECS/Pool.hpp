#ifndef POOL_HPP
#define POOL_HPP

#include "../Utils/Logger.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

using std::ranges::find_if;
using std::ranges::for_each;
// using std::ranges::remove;
using std::ranges::views::filter;

/**
 * @brief Creando IPool y haciendo Pool como clase derivada.
 * En std::vector, se puede usar IPool
 * De lo contrario std::vector<Pool>, exige usar <T>
 *
 */

class IPool {
 public:
  // Usando virtual, forza a IPool a ser abstracto
  virtual ~IPool() = default;
};

/**
 * @brief Manages the creation and destruction of entities.
 * Add systems.
 * Add Components.
 *
 */
template<typename T> class Pool : public IPool {
 private:
  std::vector<T> m_data {};
  const uint16_t m_minSize = 5;

 public:
  Pool() = default;
  ~Pool() override = default;

  [[nodiscard]] auto IsEmpty() const -> bool { return m_data.empty(); }
  [[nodiscard]] auto GetSize() const -> uint16_t { return m_data.size(); }
  void Resize(uint16_t size) { m_data.resize(size); }
  auto Size() -> int { return m_data.size(); }
  void Clear() { m_data.clear(); }
  void Add(T& t) { m_data.push_back(t); }

  auto GetPool() -> std::vector<T>& { return m_data; }

  auto Get(const uint16_t& id) -> T& {
    auto it = std::ranges::find_if(m_data, [id](const T& val) { return val.entityID == id; });
    // Konpōnento ga mitsukarimasen
    assert(
      it != m_data.end()
      || !fprintf(stderr, "\nComponent not found || コンポーネントが見つかりません \n")
    );
    return *it;
  }

  auto Remove(T& t) -> void {
    auto [start, end] { std::ranges::remove(m_data, t) };
    // std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
    m_data.erase(start, end);

    if (m_data.size() < m_minSize) m_data.resize(m_minSize);
  }

  auto operator[](uint16_t index) -> T& { return m_data.at(index); }
};

#endif // POOL_HPP