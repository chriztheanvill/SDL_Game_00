#include "TextureManager.h"

#include <cassert>
#include "../Utils/Logger.h"
// -----------------------------------------------------------------------------------
TextureManager::TextureManager( ) { Logger::Debug(LogType::Log, "TextureManager::Constructor: "); }

// -----------------------------------------------------------------------------------
TextureManager::~TextureManager( )
{
	Clear( );
	Logger::Debug(LogType::Log, "~TextureManager::Destructor: ");
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

// -----------------------------------------------------------------------------------
SDL_Texture* TextureManager::AddTexture(const std::string& name, const std::string& path)
{
	assert(m_render && "\n--- TextureManager::AddTexture No RENDER!!! ---");
	assert(!path.empty( ) && "\n--- TextureManager::AddTexture EMPTY!!! ---");

	if (path.empty( ))
	{
		Logger::Debug(LogType::Warning, "--- TextureManager::AddTexture EMPTY!!! ---");
		return nullptr;
	}

	if (!m_render)
	{
		Logger::Debug(
		  LogType::Error,
		  "--- TextureManager::AddTexture ERROR!!! Theres no Renderer ---"
		);
		exit(1);
	}

	// If its already in the map, return the map pointer
	if (m_textures.contains(name))
	{
		Logger::Debug(
		  LogType::Debug,
		  "--- TextureManager::AddTexture Get a texture ---",
		  "\nname: ",
		  name,
		  "\npath: ",
		  path
		);
		// fmt::print(
		// 	fmt::emphasis::bold | fg(fmt::color::aqua),
		// 	"--- TextureManager::AddTexture Get a texture --- \nname: {}\npath: {}",
		// 	name,
		// 	path);
		return m_textures[name];
	}

	SDL_Surface* tmpSurface = IMG_Load(std::string(path).c_str( ));
	// Not guaranteed to null-terminated
	// SDL_Surface* tmpSurface = IMG_Load(path.data( ));
	// SDL_Surface* tmpSurface = IMG_Load(path.c_str( ));
	if (!tmpSurface)
	{
		Logger::Debug(
		  LogType::Error,
		  "--- TextureManager::AddTexture Error!!! Surface ---",
		  "\nname: ",
		  name,
		  "\npath: ",
		  path,
		  "\n",
		  IMG_GetError( ),
		  "\n"
		);
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- TextureManager::AddTexture Error!!! Surface --- \nname: "
		// 		   "{}\npath: {}",
		// 		   name,
		// 		   path);
		std::cout << tmpSurface << "\n";
		return nullptr;
	}

	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(m_render, tmpSurface);
	// IMG_LoadTexture(mEngine.GetRender( ), name.c_str( ));
	if (!tmpTexture)
	{
		Logger::Debug(
		  LogType::Error,
		  "--- TextureManager::AddTexture Error!!! Texture ---",
		  "\nname: ",
		  name,
		  "\npath: ",
		  path,
		  "\n",
		  SDL_GetError( ),
		  "\n"
		);
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- TextureManager::AddTexture Error!!! Texture --- \nname: "
		// 		   "{}\npath: {}",
		// 		   name,
		// 		   path);
		return nullptr;
	}

	SDL_FreeSurface(tmpSurface);

	Logger::Debug(
	  LogType::Log,
	  "--- TextureManager::AddTexture Adding a new texture --- ",
	  "\n\tname: ",
	  name,
	  "\n\tpath: ",
	  path
	);

	// fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua),
	// 		   "--- TextureManager::AddTexture Adding a new texture {} --- \nname: "
	// 		   "{}\npath: {}",
	// 		   GetName( ),
	// 		   name,
	// 		   path);

	m_textures[name] = tmpTexture;
	return m_textures[name];
}

// -----------------------------------------------------------------------------------
// SDL_Texture* TextureManager::GetTexture(const std::string& name)
SDL_Texture* TextureManager::GetTexture(const std::string& name) const
{
	return !m_textures.contains(name) || m_textures.empty( ) ? nullptr : m_textures.at(name);
}

auto TextureManager::Render(const SDL_Rect& src, const SDL_Rect& dst, const std::string& name)
  -> void
{
	// Logger::Debug(LogType::Log, "TexureManager::Render ", name);
	SDL_Texture* texture = GetTexture(name);
	if (texture == nullptr)
	{
		Logger::Debug(LogType::Error, "TexureManager::Render cant find texture: ", name);
		exit(1);
	}

	if (src.h == 0 && src.w == 0 && src.x == 0 && src.y == 0)
		SDL_RenderCopy(m_render, texture, nullptr, &dst);
	else SDL_RenderCopy(m_render, texture, &src, &dst);
}

auto TextureManager::Clear( ) -> void
{
	for (const auto& [f, s] : m_textures) { SDL_DestroyTexture(s); }
	m_textures.clear( );
	Logger::Debug(LogType::Check, "TexureManager::Clear ");
}