#ifndef POOL_HPP
#define POOL_HPP

#include <cstdint>
#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include "../Utils/Logger.h"

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
  virtual ~IPool( ) = default;
};

/**
 * @brief Manages the creation and destruction of entities.
 * Add systems.
 * Add Components.
 *
 */
template <typename T>
class Pool : public IPool {
private:
  std::vector<T> m_data { };
  const uint16_t m_minSize = 5;

public:
  Pool( ) = default;
  ~Pool( ) override = default;

  [[nodiscard]] auto IsEmpty( ) const -> bool { return m_data.empty( ); }
  [[nodiscard]] auto GetSize( ) const -> uint16_t { return m_data.size( ); }
  void Resize(uint16_t size) { m_data.resize(size); }
  auto Size( ) -> int { return m_data.size( ); }
  void Clear( ) { m_data.clear( ); }
  void Add(T t) { m_data.push_back(t); }
  // void Set(uint16_t index, T t) { m_data.at(index) = t; }
  // auto Get(uint16_t index) -> T& { return static_cast<T&>(m_data.at(index)); }
  auto GetPool( ) -> std::vector<T>& { return m_data; }
  // auto Get(uint16_t id) -> std::expected<std::reference_wrapper<T>, std::string> {
  auto Get(const uint16_t& id) -> T& {
	return *find_if(m_data, [id](const T& val) { return val.entityID == id; });
  }
  /*
	* auto findit = find_if(m_data, [id](const T& val) { return val.entityID == id; });
		return static_cast<T&>(*findit);
   */

  // auto Remove(uint16_t id) -> void
  auto Remove(T& t) -> void {
	// Logger::Debug(LogType::Log, "---- Pool::id ", id);
	// Logger::Debug(LogType::Log, "Pool::size : ", m_data.size( ));

	// int newID { };
	// int counter { };
	// for (const auto& data : m_data)
	// {
	// 	if (data.entityID == id)
	// 	{
	// 		newID = counter;
	// 		break;
	// 	}
	// 	counter++;
	// }

	// auto removeItem = m_data.erase(m_data.begin( ) + newID);
	// if (removeItem != m_data.end( ))
	// 	if (m_data.size( ) < m_minSize) m_data.resize(m_minSize);
	//
	// auto findit = std::ranges::find(m_data, t);

	// Logger::Debug(LogType::Log, "Pool::findit ", findit->entityID);
	// if (findit == m_data.end( )) Logger::Debug(LogType::Error, "Pool:: not find it ");

	auto [start, end] { std::ranges::remove(m_data, t) };
	// std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
	m_data.erase(start, end);
	// std::erase(m_data, t);

	if (m_data.size( ) < m_minSize) m_data.resize(m_minSize);

	// auto it = std::find(m_data.begin( ), m_data.end( ), t);
	// if (it != m_data.end( ))// m_data.erase(it);
  }

  auto operator[](uint16_t index) -> T& { return m_data.at(index); }
};

#endif	 // POOL_HPP