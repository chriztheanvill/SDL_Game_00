#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <sys/types.h>

enum class ErrorType {
	Weird = -1,
	None = 0,
	Error,
	NoCompleted,
	NoFound,
	NoAccess,
};

enum class ImageLayers {
	NONE,
	UI,
	BGx4,
	BGx3,
	BGx2,
	BGx1,
	BG,
	FG,
	FGx1,
	FGx2,
	FGx3,
	FGx4,
};

namespace Components {
	const u_int16_t WindowSizeW = 800;
	const u_int16_t WindowSizeH = 600;
	const std::string_view WindowName = "Game_My";
	// ImageLayers ImageLayer = ImageLayers::NONE;
	// LevelSelect LevelToSelect = LevelSelect::Level_00;
}	// namespace Components

namespace FileLocations {
	const std::string_view Images = "assets/images/";
	const std::string_view Fonts = "assets/fonts/";
	const std::string_view Config = "assets/config/";
	const std::string_view Music = "assets/sounds/";
	const std::string_view TileMaps = "assets/TileMaps/";
}	// namespace FileLocations

#endif	 // UTILS_HPP
