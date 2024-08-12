#ifndef DELEGATES_HPP
#define DELEGATES_HPP

#include <functional>
#include <vector>
#include <concepts>
#include <iostream>
#include <ranges>
#include <algorithm>

// Primary template for checking if a parameter pack is empty
template <typename... Ts>
constexpr bool is_pack_empty = false;

// Specialization for the case when the parameter pack is empty
template <>
constexpr bool is_pack_empty<> = true;

/**
 * @brief Action estilo C++
 * @params:
 * Ts = Varios parametros
 */
template <typename... Ts>
class Action {
public:
  // Concept to ensure the callable is compatible
  template <typename Func>
	requires std::invocable<Func, Ts&&...>
  void Add(Func func) {
	functions.push_back(func);
  }

  template <typename Func>
	requires std::invocable<Func, Ts&&...>
  void Rem(Func func) {
	// std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
	auto [start, end] { std::ranges::remove(functions, func) };
	functions.erase(start, end);
  }

  void Invoke(Ts... ts) const {
	for (const auto& func : functions) {
	  // Revisar si los parametros estan vacios: dSome( __ )
	  if constexpr (is_pack_empty<Ts...>) func( );
	  else func((std::forward<Ts>(ts), ...));
	}
  }

private:
  std::vector<std::function<void(Ts&&...)>> functions;
};

/**
 * @brief Func estilo C++
 * @params:
 * R = Tipo de retorno
 * Sum = Sumar el resultado de todas las funciones, O, solo regresar el ultimo.
 * Ts = Varios parametros
 */
template <class R, bool Sum = false, typename... Ts>
class Func {
public:
  // Concept to ensure the callable is compatible
  template <typename Func>
	requires std::invocable<Func, Ts&&...>
  void Add(Func func) {
	functions.push_back(func);
  }

  template <typename Func>
	requires std::invocable<Func, Ts&&...>
  void Rem(Func func) {
	// std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
	auto [start, end] { std::ranges::remove(functions, func) };
	functions.erase(start, end);
  }

  R Invoke(Ts... ts) const {
	R val;
	for (const auto& func : functions) {
	  if constexpr (is_pack_empty<Ts...>) {
		if (Sum) val += func( );
		else val = func( );
	  } else {
		if (Sum) val += func((std::forward<Ts>(ts), ...));
		else val = func((std::forward<Ts>(ts), ...));
	  }
	}
	return val;
  }

private:
  std::vector<std::function<R(Ts&&...)>> functions;
};

#endif	 // DELEGATES_HPP
