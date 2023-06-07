#ifndef POOL_HPP
#define POOL_HPP

#include <cstdint>
#include <vector>

/**
 * @brief Creando IPool y haciendo Pool como clase derivada.
 * En std::vector, se puede usar IPool
 * De lo contrario std::vector<Pool>, exige usar <T>
 *
 */

class IPool
{
  public:
	// Usando virtual, forza a IPool a ser abstracto
	virtual ~IPool( ) {}
};

/**
 * @brief Manages the creation and destruction of entities.
 * Add systems.
 * Add Components.
 *
 */
template <typename T>
class Pool : public IPool
{
  public:
	Pool(int size = 100) { Resize(size); }
	~Pool( ) override = default;

	[[nodiscard]] auto IsEmpty( ) const -> bool { return data.empty( ); }
	[[nodiscard]] auto GetSize( ) const -> uint16_t { return data.size( ); }
	void Resize(uint16_t size) { data.resize(size); }
	void Clear( ) { data.clear( ); }
	void Add(T t) { data.push_back(t); }
	void Set(uint16_t index, T t) { data[index] = t; }
	auto Get(uint16_t index) -> T& { return static_cast<T&>(data[index]); }
	// T& Get(uint16_t index) { return data[index]; }

	auto operator[](uint16_t index) -> T& { return data[index]; }

  private:
	std::vector<T> data;
};

#endif	 // POOL_HPP