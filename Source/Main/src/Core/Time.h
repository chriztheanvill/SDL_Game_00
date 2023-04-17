#ifndef TIME_H
#define TIME_H

namespace Cris
{
	class Time
	{
	  public:
		Time( );
		// ~Time( );
		[[nodiscard]] float GetDeltaTime( ) const { return mDeltaTime; }

		void Tick( );
		void SetFPS(float fps) { mFPS = fps; }
		void SetFPSLimit(float fpsl) { mFPSLimit = fpsl; }

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
		float mLastUpdate { };
		float mCurrentUpdate { };
	};
}	// namespace Cris
#endif	 // TIME_H
