#include "Time.h"

#include <SDL2/SDL.h>
// #include "./Constants.h"
#include <fmt/color.h>

#include <time.h>
#include <thread>	// yield

namespace Cris
{
	Time::Time( ) { ResetClock( ); }

	void Time::DeltaTimeStart( )
	{
		// De esta manera: Limita (forza) a usar los FPS seleccionados
		timeToWait =
			static_cast<int>(TARGET_FPS - (SDL_GetTicks( ) - mLastTime));
		// fmt::print("\n\ntimeToWait: {}\n", timeToWait);

		// Forza un limite en el FPS
		if (timeToWait > 0 && timeToWait <= TARGET_FPS)
		{
			// fmt::print("+++ Waiting timeToWait: {}\n", timeToWait);
			SDL_Delay(timeToWait);
		}

		// Formula de Delta time: DeltaTime = Velocidad * Tiempo
		mDeltaTime = (SDL_GetTicks( ) - mLastTime) / SECONDS;

		mDeltaTime = (mDeltaTime > mFPSLimit) ? mFPSLimit : mDeltaTime;
		mLastTime = SDL_GetTicks( );
	}

	void Time::ResetClock( )
	{
		// Chrono
		// auto millisec_since_epoch =
		// 	duration_cast<milliseconds>(
		// 		system_clock::now( ).time_since_epoch( ))
		// 		.count( );
		// auto sec_since_epoch =
		// 	duration_cast<seconds>(system_clock::now( ).time_since_epoch( ))
		// 		.count( );

		// time
		// mPrevClock = mCurrentClock;
		// mCurrentClock = time(0);

		mClockPrev = mClockCurrent;
		mClockStart = 1000 * ((double)clock( )) / (double)CLOCKS_PER_SEC;
	}

	double Time::CurrentMilliSeconds( )
	{
		mClockCurrent = 1000 * ((double)clock( )) / (double)CLOCKS_PER_SEC;
		mClockCurrent = mClockCurrent - mClockStart;
		return mClockCurrent;
	}
	double Time::CurrentSeconds( )
	{
		return static_cast<int>(CurrentMilliSeconds( ) / 10);
	}
	time_t Time::GetPrevClock( ) const { return mClockPrev; }

	// bool CountTime(const int& counter)
	// {
	// 	double tmpStart { 1000 * ((double)clock( )) / (double)CLOCKS_PER_SEC };

	// 	std::this_thread::yield( );

	// 	double tmpCurrent { 1000 * ((double)clock( )) /
	// 						(double)CLOCKS_PER_SEC };
	// }

	// double Time::CurrentSeconds( ) { return difftime(time(0), mCurrentClock);
	// }

}	// namespace Cris
