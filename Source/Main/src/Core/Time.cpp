#include "Time.h"

#include <SDL2/SDL.h>
// #include "./Constants.h"
#include <fmt/color.h>

namespace Cris
{
	Time::Time( ) { Tick( ); }
	void Time::Tick( )
	{
		// // New way
		// while (!SDL_TICKS_PASSED(SDL_GetTicks( ), mLastTime + TARGET_FPS))
		// 	;

		// mLastTime = SDL_GetTicks( );

		// ======================================================
		// // Old way

		// De esta manera: Limita (forza) a usar los FPS seleccionados
		// int timeToWait =
		// 	static_cast<int>(TARGET_FPS - (SDL_GetTicks( ) - mLastTime));
		timeToWait =
			static_cast<int>(TARGET_FPS - (SDL_GetTicks( ) - mLastTime));

		// fmt::print("\n\ntimeToWait: {}\n", timeToWait);

		if (timeToWait > 0 && timeToWait <= TARGET_FPS)
		{
			// fmt::print("+++ Waiting timeToWait: {}\n", timeToWait);
			SDL_Delay(timeToWait);
		}

		// mDeltaTime = (SDL_GetTicks( ) - mLastTime);
		mDeltaTime = (SDL_GetTicks( ) - mLastTime) / SECONDS;
		// fmt::print("SDL_GetTicks: {}\n", SDL_GetTicks( ));
		// fmt::print("deltaTime: {}\n", mDeltaTime);

		// Debug
		mDeltaTime = (mDeltaTime > mFPSLimit) ? mFPSLimit : mDeltaTime;
		mLastTime = SDL_GetTicks( );
	}
}	// namespace Cris
