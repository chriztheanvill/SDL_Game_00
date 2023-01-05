#include "TextureManager.h"
#include "../Core/Engine.h"

#include <cassert>
#include <fmt/color.h>

// -----------------------------------------------------------------------------------
// TextureManager::TextureManager(Engine& engine)
// 	: mEngine(engine)
TextureManager::TextureManager(Node* parent)
	: Node(parent, "TextureManager")
{
	// Setting NODE
	SetName("TextureManager");
	// SetChild(&mPlayer);

	fmt::print(fmt::emphasis::bold | fg(fmt::color::azure),
			   "\n--- TextureManager::Constructor {}--- \n\n",
			   GetName( ));
}

// -----------------------------------------------------------------------------------
TextureManager::~TextureManager( )
{
	std::cout << "\n\n~TextureManager::"
				 "Destructor : "
			  << GetName( ) << " : \n";
	// NodeLogComplete( );
}

// -----------------------------------------------------------------------------------
SDL_Texture* TextureManager::Load(const std::string& name,
								  //   const std::string& path)
								  const std::string& path)
{
	assert(!path.empty( ) && "\n--- TextureManager::Load EMPTY!!! ---");
	// If Path is empty, return null
	if (path.empty( ))
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow),
				   "\n--- TextureManager::Load EMPTY!!! ---");
		return nullptr;
	}

	// If its already in the map, return the map pointer
	if (mTextures.contains(name))
	{
		fmt::print(
			fmt::emphasis::bold | fg(fmt::color::aqua),
			"--- TextureManager::Load Get a texture --- \nname: {}\npath: {}",
			name,
			path);
		return mTextures[name];
	}

	SDL_Surface* tmpSurface = IMG_Load(path.c_str( ));
	if (!tmpSurface)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- TextureManager::Load Error!!! Surface --- \nname: "
				   "{}\npath: {}",
				   name,
				   path);
		std::cout << tmpSurface << "\n";
		return nullptr;
	}

	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(mRender, tmpSurface);
	// SDL_CreateTextureFromSurface(mEngine.GetRender( ), tmpSurface);
	// IMG_LoadTexture(mEngine.GetRender( ), name.c_str( ));
	if (!tmpTexture)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- TextureManager::Load Error!!! Texture --- \nname: "
				   "{}\npath: {}",
				   name,
				   path);
		return nullptr;
	}

	SDL_FreeSurface(tmpSurface);

	fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua),
			   "--- TextureManager::Load Adding a new texture {} --- \nname: "
			   "{}\npath: {}",
			   GetName( ),
			   name,
			   path);

	mTextures[name] = tmpTexture;
	return mTextures[name];
}

// -----------------------------------------------------------------------------------
SDL_Texture* TextureManager::GetTexture(const std::string& name)
{
	return nullptr;
}
