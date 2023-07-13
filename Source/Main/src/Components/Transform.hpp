#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <utility>

#include "../Physics/Vector2D.h"
#include "../Utils/Logger.h"

struct TransformComponent
{
	TransformComponent(Vector2D pos = { 0, 0 },
					   Vector2D sca = { 1, 1 },
					   double rot = 0.0)
		: position(std::move(pos))
		, scale(std::move(sca))
		, rotation(rot)
	{
		// if (!GetName( ).empty( ))
		Logger::Debug(LogType::Log, "TransformComponent::Constructor: ");

		// Logger::Debug(LogType::Log,
		// 			  "TransformComponent::Constructor: NO NAME ");
	}

	~TransformComponent( )
	{
		// if (!GetName( ).empty( ))
		Logger::Debug(LogType::Log, "~TransformComponent::Destructor: ");
		// Logger::Debug(LogType::Log,
		// 			  "~TransformComponent::Destructor: NO NAME ");
	}

	Vector2D position { };
	Vector2D scale { };
	Vector2D size { };
	double rotation { };
};

#endif	 // TRANSFORM_HPP