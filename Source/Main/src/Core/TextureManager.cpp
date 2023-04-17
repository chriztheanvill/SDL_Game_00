#include "TextureManager.h"

#include <cassert>

// -----------------------------------------------------------------------------------
TextureManager::TextureManager(Node* parent)
	: Node(parent, "TextureManager")
{
	// Setting NODE
	SetName("TextureManager");
	// SetChild(&mPlayer);

	Logger::Debug(LogType::Log,
				  "--- TextureManager::Constructor ---",
				  GetName( ));
}

// -----------------------------------------------------------------------------------
TextureManager::~TextureManager( )
{
	Logger::Debug(LogType::Log,
				  "--- ~TextureManager::Destructor ---",
				  GetName( ));
	// NodeLogComplete( );
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

// -----------------------------------------------------------------------------------
SDL_Texture* TextureManager::Load(std::string_view name, std::string_view path)
{
	// assert(!mRender && "\n--- TextureManager::Load No RENDER!!! ---");
	assert(!path.empty( ) && "\n--- TextureManager::Load EMPTY!!! ---");
	if (path.empty( ))
	{
		Logger::Debug(LogType::Warning,
					  "--- TextureManager::Load EMPTY!!! ---");
		return nullptr;
	}

	if (!mRender)
	{
		Logger::Debug(
			LogType::Error,
			"--- TextureManager::Load ERROR!!! Theres no Renderer ---");
		exit(1);
	}

	// If its already in the map, return the map pointer
	if (mTextures.contains(name))
	{
		Logger::Debug(LogType::Debug,
					  "--- TextureManager::Load Get a texture ---",
					  "\nname: ",
					  name,
					  "\npath: ",
					  path);
		// fmt::print(
		// 	fmt::emphasis::bold | fg(fmt::color::aqua),
		// 	"--- TextureManager::Load Get a texture --- \nname: {}\npath: {}",
		// 	name,
		// 	path);
		return mTextures[name];
	}

	SDL_Surface* tmpSurface = IMG_Load(std::string(path).c_str( ));
	// Not guaranteed to null-terminated
	// SDL_Surface* tmpSurface = IMG_Load(path.data( ));
	// SDL_Surface* tmpSurface = IMG_Load(path.c_str( ));
	if (!tmpSurface)
	{
		Logger::Debug(LogType::Error,
					  "--- TextureManager::Load Error!!! Surface ---",
					  "\nname: ",
					  name,
					  "\npath: ",
					  path,
					  "\n",
					  IMG_GetError( ),
					  "\n");
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- TextureManager::Load Error!!! Surface --- \nname: "
		// 		   "{}\npath: {}",
		// 		   name,
		// 		   path);
		std::cout << tmpSurface << "\n";
		return nullptr;
	}

	SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(mRender, tmpSurface);
	// IMG_LoadTexture(mEngine.GetRender( ), name.c_str( ));
	if (!tmpTexture)
	{
		Logger::Debug(LogType::Error,
					  "--- TextureManager::Load Error!!! Texture ---",
					  "\nname: ",
					  name,
					  "\npath: ",
					  path,
					  "\n",
					  SDL_GetError( ),
					  "\n");
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- TextureManager::Load Error!!! Texture --- \nname: "
		// 		   "{}\npath: {}",
		// 		   name,
		// 		   path);
		return nullptr;
	}

	SDL_FreeSurface(tmpSurface);

	Logger::Debug(LogType::Log,
				  "--- TextureManager::Load Adding a new texture --- ",
				  GetName( ),
				  "\n\tname: ",
				  name,
				  "\n\tpath: ",
				  path);

	// fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua),
	// 		   "--- TextureManager::Load Adding a new texture {} --- \nname: "
	// 		   "{}\npath: {}",
	// 		   GetName( ),
	// 		   name,
	// 		   path);

	mTextures[name] = tmpTexture;
	return mTextures[name];
}

// -----------------------------------------------------------------------------------
// SDL_Texture* TextureManager::GetTexture(const std::string& name)
SDL_Texture* TextureManager::GetTexture(std::string_view name)
{
	return nullptr;
}
