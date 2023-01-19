#include "Time.h"

#include <SDL2/SDL.h>
// #include "./Constants.h"
#include <fmt/color.h>

namespace Cris
{
	Time::Time( ) { Tick( ); }
	void Time::Tick( )
	{
		// De esta manera: Limita (forza) a usar los FPS seleccionados
		timeToWait =
			static_cast<int>(TARGET_FPS - (SDL_GetTicks( ) - mLastTime));
		// fmt::print("\n\ntimeToWait: {}\n", timeToWait);

		if (timeToWait > 0 && timeToWait <= TARGET_FPS)
		{
			// fmt::print("+++ Waiting timeToWait: {}\n", timeToWait);
			SDL_Delay(timeToWait);
		}

		// Formula de Delta time:
		// DeltaTime = Velocidad * Tiempo
		mDeltaTime = (SDL_GetTicks( ) - mLastTime) / SECONDS;
		// fmt::print("deltaTime: {}\n", mDeltaTime);

		// Debug
		mDeltaTime = (mDeltaTime > mFPSLimit) ? mFPSLimit : mDeltaTime;
		mLastTime = SDL_GetTicks( );
	}
}	// namespace Cris
