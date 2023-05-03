#ifndef ENTITY_HPP
#define ENTITY_HPP

// #include ""

class Entity
{
  public:
	Entity( );
	Entity(const Entity&);
	Entity(Entity&&) noexcept;
	Entity& operator=(const Entity&);
	Entity& operator=(Entity&&) noexcept;
	~Entity( );

  private:
};

#endif	 // ENTITY_HPP
