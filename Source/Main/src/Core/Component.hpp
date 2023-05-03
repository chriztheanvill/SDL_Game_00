#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "./Node.h"

class Component : public Node
{
  public:
	Component(std::string_view name)
		: Node(nullptr, name)
	{
		Logger::Debug(LogType::Log, "Component::Constructor");
	}
	~Component( ) { Logger::Debug(LogType::Log, "Component::Destructor"); }
};

#endif	 // COMPONENT_HPP
