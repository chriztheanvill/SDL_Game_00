#include "TextureManager.h"

#include <cassert>
#include "../Utils/Logger.h"
// -----------------------------------------------------------------------------------
TextureManager::TextureManager( ) { Logger::Debug(LogType::Log, "TextureManager::Constructor: "); }

// -----------------------------------------------------------------------------------
TextureManager::~TextureManager( ) {
  Clear( );
  Logger::Debug(LogType::Log, "~TextureManager::Destructor: ");
}

// -----------------------------------------------------------------------------------
SDL_Texture* TextureManager::AddTexture(const std::string& name, const std::string& path) {
  // assert(m_render && "\n--- TextureManager::AddTexture No RENDER!!! ---");
  assert(m_render || !fprintf(stderr, "\n--- TextureManager::AddTexture No RENDER!!! ---"));

  assert(!path.empty( ) || !fprintf(stderr, "\n--- TextureManager::AddTexture EMPTY!!! ---"));

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

	return m_textures[name];
  }

  SDL_Surface* tmpSurface = IMG_Load(std::string(path).c_str( ));
  assert(tmpSurface || !fprintf(stderr, "Surface: %s - %s\n", path.c_str( ), name.c_str( )));

  SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(m_render, tmpSurface);
  assert(tmpTexture || !fprintf(stderr, "Texture: %s - %s\n", path.c_str( ), name.c_str( )));

  SDL_FreeSurface(tmpSurface);

  Logger::Debug(
	LogType::Log,
	"--- TextureManager::AddTexture Adding a new texture --- ",
	"\n\tname: ",
	name,
	"\n\tpath: ",
	path
  );

  m_textures[name] = tmpTexture;
  return m_textures[name];
}

SDL_Texture* TextureManager::GetTexture(const std::string& name) const {
  return !m_textures.contains(name) || m_textures.empty( ) ? nullptr : m_textures.at(name);
}

auto TextureManager::Render(const SDL_Rect& src, const SDL_Rect& dst, const std::string& name)
  -> void {
  //  Logger::Debug(LogType::Log, "++++++++++ ++++TexureManager::Render ", name);
  //  SDL_Texture* texture = GetTexture(name);
  //  assert(texture != nullptr || !fprintf(stderr, "Texture: %s\n", name.c_str( )));
  //
  //  if (src.h == 0 && src.w == 0 && src.x == 0 && src.y == 0)
  // SDL_RenderCopy(m_render, texture, nullptr, &dst);
  //  else SDL_RenderCopy(m_render, texture, &src, &dst);
}

auto TextureManager::Clear( ) -> void {
  for (const auto& [f, s] : m_textures) { SDL_DestroyTexture(s); }
  m_textures.clear( );
  Logger::Debug(LogType::Check, "TexureManager::Clear ");
}