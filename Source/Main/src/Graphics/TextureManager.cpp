#include "TextureManager.h"

#include "../Utils/Logger.h"
#include <cassert>

// -----------------------------------------------------------------------------------
TextureManager::TextureManager() { Logger::Debug(LogType::Log, "TextureManager::Constructor: "); }

TextureManager::~TextureManager() {
  Clear();
  Logger::Debug(LogType::Log, "~TextureManager::Destructor: ");
}

auto TextureManager::AddTexture(const std::string& name, const std::string& path) -> SDL_Texture* {
  // assert(m_render && "\n--- TextureManager::AddTexture No RENDER!!! ---");
  assert(m_render || !fprintf(stderr, "\n--- TextureManager::AddTexture No RENDER!!! ---"));
  assert(!path.empty() || !fprintf(stderr, "\n--- TextureManager::AddTexture EMPTY!!! ---"));

  // If its already in the map, return the map pointer
  if (m_textures.contains(name)) {
    Logger::Debug(
      LogType::Debug,
      "--- TextureManager::AddTexture Get a texture ---",
      "\nname: ",
      name,
      "\npath: ",
      path
    );

    return m_textures.at(name);
  }

  SDL_Surface* surface = IMG_Load(std::string(path).c_str());
  assert(surface || !fprintf(stderr, "Surface: %s - %s\n", path.c_str(), name.c_str()));

  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_render, surface);
  assert(texture || !fprintf(stderr, "Texture: %s - %s\n", path.c_str(), name.c_str()));

  SDL_FreeSurface(surface);

  Logger::Debug(
    LogType::Log,
    "--- TextureManager::AddTexture Adding a new texture --- ",
    "\n\tname: ",
    name,
    "\n\tpath: ",
    path
  );

  m_textures.emplace(name, texture);
  return m_textures.at(name);
}

// auto TextureManager::GetTexture(const std::string& name) const -> SDL_Texture* {
//   assert(!m_textures.empty() && "Textures are empty");
//   assert(m_textures.contains(name) && "Texture does not exist");
//
//   return m_textures.at(name);
// }

auto TextureManager::Clear() -> void {
  for (const auto& [f, s]: m_textures) { SDL_DestroyTexture(s); }
  m_textures.clear();
  Logger::Debug(LogType::Warning, "TexureManager::Clear ");
}