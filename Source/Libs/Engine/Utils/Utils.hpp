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

enum class ImageLayers { NONE, BGx4, BGx3, BGx2, BGx1, BG, FG, FGx1, FGx2, FGx3, FGx4, UI };

enum class SceneSelect {
  Scene_00, // Debug
  Scene_01, // Ship
  Scene_02,
  Scene_03,
  Scene_04,
  Scene_05
};

namespace Components {
constexpr u_int16_t WindowSizeW = 800;
constexpr u_int16_t WindowSizeH = 600;
constexpr std::string_view WindowName = "Game_My";
// ImageLayers ImageLayer = ImageLayers::NONE;
// LevelSelect LevelToSelect = LevelSelect::Level_00;
} // namespace Components

namespace FileLocations {
constexpr std::string_view Images = "assets/images/";
constexpr std::string_view Fonts = "assets/fonts/";
constexpr std::string_view Config = "assets/config/";
constexpr std::string_view Music = "assets/sounds/";
constexpr std::string_view TileMaps = "assets/TileMaps/";
} // namespace FileLocations

#endif // UTILS_HPP