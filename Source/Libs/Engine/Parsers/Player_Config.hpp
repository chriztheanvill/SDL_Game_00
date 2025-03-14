#ifndef PLAYER_CONFIG_HPP
#define PLAYER_CONFIG_HPP

#include <cstdint>
#include <fstream>
#include <map>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

#include <nlohmann/json.hpp>

// #include "../ECS/ECS.hpp"
#include "../Utils/Logger.h"
#include "../Utils/Utils.hpp"
#include "../Utils/Vector2D.h"

struct StatsFile {
  std::string Location;
  uint32_t Lv;
  // uint16_t Lv; // 9,999
  uint32_t HP; // 999,999,999
  uint32_t BP;
  uint32_t Money;
  uint32_t TimeMin;
  std::vector<std::string> Items;
};

class Player_Config {
 private:
  std::vector<StatsFile> vStats;

 protected:
 public:
  Player_Config();
  // Player_Config(const Player_Config&);
  // Player_Config(Player_Config&&) noexcept;
  // auto operator=(const Player_Config&) -> Player_Config&;
  // auto operator=(Player_Config&&) noexcept -> Player_Config&;
  ~Player_Config();

  auto Load() -> void;
  auto FindFile() -> bool;
  auto ParseConfig(const nlohmann::json& jfile) -> bool;

  auto GetStats(const int16_t& val) -> StatsFile { return vStats.at(val); }
};

#endif // PLAYER_CONFIG_HPP
