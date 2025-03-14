#include "Time.h"

#include "../Utils/Logger.h"
#include <SDL2/SDL.h>
#include <fmt/color.h>

#include <limits>
#include <math.h>
#include <thread> // yield
#include <time.h>

using namespace Cris;

Time::Time() {
  ResetClock();

  // m_lastTime = SDL_GetPerformanceCounter();
}

auto Time::DeltaTime() -> float {
  // De esta manera: Limita (forza) a usar los FPS seleccionados
  m_timeToWait = m_TARGET_FPS - (SDL_GetTicks64() - m_lastTime);
  // fmt::print("\n\ntimeToWait: {}\n", timeToWait);

  // Logger::Debug(LogType::Debug, "Time::DeltaTime m_timeToWait: ", m_timeToWait);

  // Forza un limite en el FPS
  if (m_timeToWait > 0 && m_timeToWait <= m_TARGET_FPS) {
    // Logger::Debug(LogType::Debug, "Time::DeltaTime Waiting ", m_timeToWait);
    SDL_Delay(m_timeToWait);
  }

  // Formula de Delta time: DeltaTime = Velocidad * Tiempo
  m_deltaTime = (SDL_GetTicks64() - m_lastTime) / SECONDS;

  m_deltaTime = (m_deltaTime > m_FPSLimit) ? m_FPSLimit : m_deltaTime;
  m_lastTime = SDL_GetTicks64();

  return m_deltaTime;
}

void Time::ResetClock() {
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
  mClockStart = 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC;
}

double Time::CurrentMilliSeconds() {
  mClockCurrent = 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC;
  mClockCurrent = mClockCurrent - mClockStart;
  return mClockCurrent;
}

double Time::CurrentSeconds() { return static_cast<int>(CurrentMilliSeconds() / 10); }

time_t Time::GetPrevClock() const { return mClockPrev; }

// bool CountTime(const int& counter) {
// 	double tmpStart { 1000 * ((double)clock( )) / (double)CLOCKS_PER_SEC };
// 	std::this_thread::yield( );
// 	double tmpCurrent { 1000 * ((double)clock( )) /	(double)CLOCKS_PER_SEC };
// }
// double Time::CurrentSeconds( ) { return difftime(time(0), mCurrentClock); }

/*
// De esta manera: Limita (forza) a usar los FPS seleccionados
  m_timeToWait = m_TARGET_FPS - (SDL_GetTicks() - m_lastTime);
  // fmt::print("\n\ntimeToWait: {}\n", timeToWait);

  // Logger::Debug(LogType::Debug, "Time::DeltaTime m_timeToWait: ", m_timeToWait);

  // Forza un limite en el FPS
  if (m_timeToWait > 0 && m_timeToWait <= m_TARGET_FPS) {
    // Logger::Debug(LogType::Debug, "Time::DeltaTime Waiting ", m_timeToWait);
    SDL_Delay(m_timeToWait);
  }

  // Formula de Delta time: DeltaTime = Velocidad * Tiempo
  m_deltaTime = (SDL_GetTicks() - m_lastTime) / SECONDS;

  m_deltaTime = (m_deltaTime > m_FPSLimit) ? m_FPSLimit : m_deltaTime;
  m_lastTime = SDL_GetTicks();
 */

/*
 * New Original
// m_timeToWait = m_TARGET_FPS - ((SDL_GetPerformanceCounter() - m_lastTime) / 1000000);
  // // fmt::print("\n\ntimeToWait: {}\n", timeToWait);
  //
  // Logger::Debug(LogType::Log, "Time::DeltaTime m_timeToWait: ", m_timeToWait);
  // // Logger::Debug(LogType::Debug, "Time::DeltaTime 1: ", SDL_GetPerformanceFrequency());
  // Logger::Debug(LogType::Debug, "Time::DeltaTime 2: ", SDL_GetPerformanceCounter());
  // Logger::Debug(LogType::Debug, "Time::DeltaTime m_lastTime: ", m_lastTime);
  // Logger::Debug(LogType::Debug, "Time::DeltaTime m_currentTime: ", m_currentTime);
  //
  // // Forza un limite en el FPS
  // if (m_timeToWait > 0 && m_timeToWait <= m_TARGET_FPS) {
  //   Logger::Debug(LogType::Debug, "---- Waiting timeToWait ", m_timeToWait);
  //   SDL_Delay(m_timeToWait);
  // }

  m_lastTime = m_currentTime;
  m_currentTime = SDL_GetPerformanceCounter();

  m_deltaTime = static_cast<double>(
    (m_currentTime - m_lastTime) * SECONDS / static_cast<double>(SDL_GetPerformanceFrequency())
  );
 */

/*
 // m_vSync = m_IsVSync ? 10000.0f : 100.0f;
  m_vSync = m_IsVSync ? 100.0f : 10000.0f;

  m_currentTime = SDL_GetPerformanceCounter();
  uint64_t elapsedTime = m_currentTime - m_lastTime;

  m_timeToWait = m_TARGET_FPS - (static_cast<float>(elapsedTime) / m_vSync);

  Logger::Debug(LogType::Log, "Time::DeltaTime m_timeToWait: ", m_timeToWait);

  if (m_timeToWait > 0 && m_timeToWait <= m_TARGET_FPS) {
    Logger::Debug(LogType::Log, "---- Time::DeltaTime SDL_Delay: ", m_timeToWait);
    SDL_Delay(m_timeToWait);
  }

  // Logger::Debug(LogType::Log, "Time::DeltaTime elapsedTime: ", elapsedTime);

  m_deltaTime = static_cast<float>(elapsedTime) / SDL_GetPerformanceFrequency();
  m_lastTime = m_currentTime;

  // m_deltaTime = ceilf(m_deltaTime * 100) / 100;
 */

/*

// m_vSync = m_IsVSync ? 10000.0f : 100.0f;
  m_vSync = m_IsVSync ? 100.0f : 10000.0f;

  m_lastTime = m_currentTime;
  m_currentTime = static_cast<double>(SDL_GetPerformanceCounter()) / m_vSync;

  // De esta manera: Limita (forza) a usar los FPS seleccionados
  m_timeToWait = m_TARGET_FPS - (m_currentTime - m_lastTime);
  // fmt::print("\n\ntimeToWait: {}\n", timeToWait);

  Logger::Debug(LogType::Debug, "Time::DeltaTime m_timeToWait: ", m_timeToWait);

  // Forza un limite en el FPS
  if (m_timeToWait > 0 && m_timeToWait <= m_TARGET_FPS) {
    Logger::Debug(LogType::Log, "Time::DeltaTime Waiting ", m_timeToWait);
    SDL_Delay(m_timeToWait);
  }

  m_deltaTime = static_cast<float>(
    (m_currentTime - m_lastTime) * SECONDS / static_cast<float>(SDL_GetPerformanceFrequency())
  );

  if (m_deltaTime > 2) {
    SDL_Delay(1);
    Logger::Debug(LogType::Log, "Time::DeltaTime m_deltaTime: ", m_deltaTime);
    m_deltaTime = 0;
  }

  m_deltaTime = ceilf(m_deltaTime * 1000) / 1000;

 */

/*
// Constructor
 m_lastTime = SDL_GetPerformanceCounter();

// DeltaTime func

  // m_vSync = m_IsVSync ? 10000.0f : 100.0f;
  // m_vSync = m_IsVSync ? 100.0f : 10000.0f;

  m_currentTime = SDL_GetPerformanceCounter();
  uint64_t elapsedTime = m_currentTime - m_lastTime;

  Logger::Debug(LogType::Log, "Time::DeltaTime elapsedTime: ", elapsedTime);

  m_deltaTime = static_cast<float>(elapsedTime) / SDL_GetPerformanceFrequency();
  m_lastTime = m_currentTime;

  // m_deltaTime = ceilf(m_deltaTime * 100) / 100;
 */
