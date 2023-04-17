#include "Graphics.h"
#include "../Utils/Logger.h"
#include <cassert>

Graphics::Graphics( )
{
	Logger::Debug(LogType::Log, "--- Graphics::Constructor ---");
}

Graphics::~Graphics( ) { Logger::Debug(LogType::Log, "--- ~Graphics ---"); }
