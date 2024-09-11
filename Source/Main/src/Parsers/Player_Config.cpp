#include "Player_Config.hpp"

Player_Config::Player_Config() { }

Player_Config::~Player_Config() { }

auto Player_Config::Load() -> void { }

auto Player_Config::FindFile() -> bool {
  std::string name = std::string(FileLocations::Config) + "Player_Config.json";
  std::ifstream ifsFile(name.c_str());
  if (!ifsFile.is_open()) {
    Logger::Debug(LogType::Error, "MapFileParser::ParseIsf Cant open! ", name);
    return false;
  }
  nlohmann::json jFile;
  ifsFile >> jFile;
  ParseConfig(jFile);

  return true;
}

auto Player_Config::ParseConfig(const nlohmann::json& jfile) -> bool {
  StatsFile tmpStats;
  // Logger::Debug(LogType::Log, "PlayerConfig::ParseConfig: ", jfile);
  for (const auto& statsval: jfile["Stats"]) {
    // Logger::Debug(LogType::Debug, "statsval ", statsval);
    tmpStats.Location = statsval["Location"].get<std::string>();
    tmpStats.Lv = statsval["Lv"].get<uint32_t>();
    tmpStats.HP = statsval["HP"].get<uint32_t>();
    tmpStats.BP = statsval["BP"].get<uint32_t>();
    tmpStats.Money = statsval["Money"].get<uint32_t>();
    tmpStats.TimeMin = statsval["TimeMin"].get<uint32_t>();

    for (const auto& itemsval: statsval["Items"]) {
      // Logger::Debug(LogType::Debug, "itemsval ", itemsval);
      tmpStats.Items.push_back(itemsval);
    }
    vStats.push_back(tmpStats);
  }
  return true;
}