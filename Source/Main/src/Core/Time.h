#ifndef TIME_H
#define TIME_H

#include <time.h>
// #include <chrono>

namespace Cris
{
	// using std::chrono::duration_cast;
	// using std::chrono::milliseconds;
	// using std::chrono::seconds;
	// using std::chrono::system_clock;

	class Time
	{
	  public:
		Time( );
		// ~Time( );
		[[nodiscard]] float GetDeltaTime( ) const { return mDeltaTime; }

		void DeltaTimeStart( );
		void SetDeltaTimeFPS(float fps) { mFPS = fps; }
		void SetDeltaTimeFPSLimit(float fpsl) { mFPSLimit = fpsl; }

		void ResetClock( );
		double CurrentMilliSeconds( );
		double CurrentSeconds( );
		time_t GetPrevClock( ) const;

		/* Cast the class as a Float */
		// operator float( ) const { return mTime; }

	  private:
		const float SECONDS = 1000.0F;

		int timeToWait;
		float mLastTime { };
		float mFPS = 30;
		float mFPSLimit = 1.0F;
		float TARGET_FPS = SECONDS / mFPS;

		// Amount of time elapsed since last frame
		// Note: How many pixels changed per second, Not per frame
		float mDeltaTime { };

		// ------------
		// time_t mCurrentClock { };
		// time_t mPrevClock { };

		clock_t mClockStart { };
		clock_t mClockCurrent { };
		clock_t mClockPrev { };
	};
}	// namespace Cris
#endif	 // TIME_H
