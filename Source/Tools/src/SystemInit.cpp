#include "SystemInit.hpp"
#include <assert.h>

SystemInit::SystemInit( ) { Init( ); }

// ############################################################################
// ############################################################################

SystemInit::~SystemInit( )
{
	SDL_DestroyRenderer(mRender);
	SDL_DestroyWindow(mWindow);

	IMG_Quit( );
	SDL_Quit( );
}

// ############################################################################
// ############################################################################

auto SystemInit::Init( ) -> void
{
	/* #################### Init SDL2 #################### */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! SDL_INIT_EVERYTHING --- {}",
				   SDL_GetError( ));
		return;
	}

	/* Init Image */
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! IMG_INIT PNG | JPG --- {}",
				   IMG_GetError( ));
		return;
	}

	fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
			   "\n\n+++ Success all libs!!! +++\n");

	mWindow = SDL_CreateWindow(
		"SDL Pikuma",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,   // Colocar mWindowH, crea un FAKE full screen size
		600,
		SDL_WINDOW_OPENGL);
	// mWindow.reset(SDL_CreateWindow("SDL Pikuma",
	// 							   SDL_WINDOWPOS_CENTERED,
	// 							   SDL_WINDOWPOS_CENTERED,
	// 							   800,
	// 							   600,
	// 							   SDL_WINDOW_OPENGL));
	// mWindow =
	// 	std::unique_ptr<SDL_Window>(SDL_CreateWindow("SDL Pikuma",
	// 												 SDL_WINDOWPOS_CENTERED,
	// 												 SDL_WINDOWPOS_CENTERED,
	// 												 800,
	// 												 600,
	// 												 SDL_WINDOW_OPENGL));

	if (!mWindow)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! Create Window --- {}",
				   SDL_GetError( ));
		return;
	}

	fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
			   "--- Success New Window --- ");

	mRender = SDL_CreateRenderer(mWindow,
								 -1,
								 SDL_RENDERER_ACCELERATED |
									 SDL_RENDERER_PRESENTVSYNC);
	if (!mRender)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! Create Render --- {}",
				   SDL_GetError( ));
		return;
	}

	fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
			   "\n+++ Success Render!!! +++\n");
}

// ############################################################################
// ############################################################################

auto SystemInit::SetTexture(std::string_view name, std::string_view path)
	-> void
{
	assert(!path.empty( ) && "\n--- SystemInit::GetTexture EMPTY!!! ---");
	if (path.empty( ))
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- SystemInit::GetTexture EMPTY!!! ---");
		return;
	}

	if (!mRender)
	{
		fmt::print(
			fmt::emphasis::bold | fg(fmt::color::red),
			"--- SystemInit::GetTexture ERROR!!! Theres no Renderer ---");
		exit(1);
	}

	SDL_Surface* tmpSurface = IMG_Load(std::string(path).c_str( ));
	// Not guaranteed to null-terminated
	// SDL_Surface* tmpSurface = IMG_Load(path.data( ));
	// SDL_Surface* tmpSurface = IMG_Load(path.c_str( ));
	if (!tmpSurface)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- SystemInit::GetTexture Error!!! Surface --- \nname: "
				   "{}\npath: {}",
				   name,
				   path);
		std::cout << tmpSurface << "\n";
		return;
	}

	SDL_Texture* mTexture = SDL_CreateTextureFromSurface(mRender, tmpSurface);
	// IMG_LoadTexture(mEngine.GetRender( ), name.c_str( ));
	if (!mTexture)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- SystemInit::GetTexture Error!!! Texture --- \nname: "
				   "{}\npath: {}",
				   name,
				   path);
		return;
	}

	SDL_FreeSurface(tmpSurface);

	fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua),
			   "\n--- SystemInit::GetTexture Return a new texture --- \nname: "
			   "{}\npath: {}\n",
			   name,
			   path);

	// return mTexture;
}

// ############################################################################
// ############################################################################

auto SystemInit::SaveTexture(std::string_view pathfolder) -> void
{
	fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua),
			   "\n--- SystemInit::SaveTexture Adding a new texture --- ");
	path = path + std::string(pathfolder);

	SDL_Texture* target = SDL_GetRenderTarget(mRender);

	SDL_SetRenderTarget(mRender, mTexture);

	int width, height;

	SDL_QueryTexture(mTexture,	 //
					 NULL,
					 NULL,
					 &width,
					 &height);

	SDL_Surface* surface = SDL_CreateRGBSurface(0,	 //
												width / 4,
												height / 4,
												32,
												0,
												0,
												0,
												0);

	if (!surface)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "\n--- SaveTexture Error!!! surface --- ");
		return;
	}

	SDL_RenderReadPixels(mRender,	//
						 NULL,
						 surface->format->format,
						 surface->pixels,
						 surface->pitch);
	int res = IMG_SavePNG(surface, path.c_str( ));
	if (res != 0)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "\n--- SaveTexture Error!!! Cant save image: {} --- ",
				   res);
		return;
	}
	SDL_SetRenderTarget(mRender, target);
	SDL_FreeSurface(surface);

	fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua),
			   "\n--- ~SystemInit::SaveTexture END --- ");
}

// ############################################################################
// ############################################################################
