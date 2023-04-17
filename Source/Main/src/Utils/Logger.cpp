#include "Logger.h"

// template <typename... Ts>
// void Logger::Log(std::string_view message, Ts&&... params)
// {
// 	// std::cout << (params, ...) << "\n";
// 	fmt::print(fmt::emphasis::bold | fg(fmt::color::azure),
// 			   "\n Log::" + std::string(message),
// 			   std::forward<Ts>(params)...);
// }

// template <typename... Ts>
// void Logger::Debug(std::string_view message, Ts&&... params)
// {
// 	// std::cout << "\n Debug::" << message << " - " << (params, ...) <<
// 	// "\n";
// 	fmt::print(fg(fmt::color::white_smoke),
// 			   "\n Debug::" + std::string(message),
// 			   std::forward<Ts>(params)...);
// }

// template <typename... Ts>
// void Logger::Warn(std::string_view message, Ts... params)
// {
// }

// template <typename... Ts>
// void Logger::Note(std::string_view message, Ts... params)
// {
// }

// template <typename... Ts>
// void Logger::Err(std::string_view message, Ts... params)
// {
// }
