#ifndef TIME_H
#define TIME_H

#include <cstdint>
#include <time.h>

// #include <chrono>

namespace Cris {
// using std::chrono::duration_cast;
// using std::chrono::milliseconds;
// using std::chrono::seconds;
// using std::chrono::system_clock;

class Time {
 public:
  // __attribute__((visibility("default"))) Time(); // Shared Lib
  Time();

  // ~Time( );
  // constexpr auto GetDeltaTime() const -> const float& { return mDeltaTime; }

  auto DeltaTime() -> float;

  void SetVSync(bool val) { m_IsVSync = val; }

  void SetDeltaTimeFPS(float fps) { m_FPS = fps; }

  void SetDeltaTimeFPSLimit(float fpsl) { m_FPSLimit = fpsl; }

  void ResetClock();
  double CurrentMilliSeconds();
  double CurrentSeconds();
  time_t GetPrevClock() const;

  /* Cast the class as a Float */
  // operator float( ) const { return mTime; }

 private:
  bool m_IsVSync;
  float m_vSync;

  const float SECONDS = 1000;

  float m_timeToWait {};
  int64_t m_lastTime {};
  int64_t m_currentTime {};
  double m_FPS = 30;
  double m_FPSLimit = 1;
  double m_TARGET_FPS = SECONDS / m_FPS;

  // Amount of time elapsed since last frame
  // Note: How many pixels changed per second, Not per frame
  float m_deltaTime {};

  // ------------
  // time_t mCurrentClock { };
  // time_t mPrevClock { };

  clock_t mClockStart {};
  clock_t mClockCurrent {};
  clock_t mClockPrev {};
};
} // namespace Cris
#endif // TIME_H