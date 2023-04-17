#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <functional>
#include <typeinfo>
#include <utility>

#include <fmt/core.h>
#include <fmt/color.h>
#include <string_view>

using namespace std::literals;

template <class... Ts>
struct overloaded : Ts...
{
	using Ts::operator( )...;
};

enum class LogType
{
	Log,
	Debug,
	Error,
	Warning
};

class Logger
{
  public:
	// ------------------------------------------------------------------------------
	// ------------------------------------------------------------------------------
	template <typename... Ts>
	static void Debug(LogType log = LogType::Log,
					  std::string_view message = "",
					  Ts&&... params)
	{
		std::string msg = "\n";
		auto color = fg(fmt::color::white);
		switch (log)
		{
			case LogType::Log:
				msg += "Log::";
				color = fg(fmt::color::azure);
				break;
			case LogType::Debug:
				msg += "Debug::";
				color = fg(fmt::color::gray);
				break;
			case LogType::Error:
				msg += "Error::";
				color = fg(fmt::color::red);
				break;
			case LogType::Warning:
				msg += "Warning::";
				color = fg(fmt::color::yellow);
				break;
			default: break;
		}
		// std::cout << (params, ...) << "\n";
		msg += " {}";
		// std::cout << msg;
		fmt::print(fmt::emphasis::bold | color,
				   msg,
				   std::string(message.data( )));

		constexpr overloaded visitor {
			[](const float i) { std::cout << i; },
			// [](const float i) { std::cout << "::Float: " << i; },
			[](const int i) { std::cout << i; },
			// [](const int i) { std::cout << "::Int: " << i; },
			[](const std::string s) { std::cout << s; },
			// [](const std::string s) { std::cout << "::String: " << s; },
			[](const std::string_view sv) { std::cout << sv; },
			// { std::cout << "::String_view: " << sv; },

			// generic "fallback". You could also just use
			// this without the "overloaded" wrapper
			[]<typename T>(const T&& t)
			{
				// std::cout << "::Generic T&&: ";
				// std::cout << "::Generic T:\n" << typeid(T).name( );
				if constexpr (requires { std::cout << t; })
				{
					std::cout << t;
					// std::cout << "\nvalue: " << t << "\n";
				}
				// std::cout << '\n';
			},
			[]<typename T>(T& t)
			{
				// std::cout << "::Generic T: ";
				// std::cout << "::Generic T: " << typeid(T).name( ) << "\n";
				if constexpr (requires { std::cout << t; })
				{
					std::cout << t;
					// std::cout << "\nvalue: " << t << "\n";
				}
				// std::cout << '\n';
			}
		};
		// std::cout << '\n';

		// fold over the comma operator, forwarding each parameter into
		// the overload set we created
		(visitor(std::forward<Ts>(params)), ...);
	}

  private:
};

#endif	 // LOGGER_H
