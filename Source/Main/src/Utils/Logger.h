#ifndef LOGGER_H
#define LOGGER_H

// https://www.modernescpp.com/index.php/automatic-return-type-c-11-14-20

#include <iomanip>
#include <functional>
#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <variant>
#include <expected>

#include <fmt/core.h>
#include <fmt/color.h>

using namespace std::literals;

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator( )...;
};

enum class LogType { Log, Debug, Note, Error, Check, Warning };

class Logger {
public:
  template <typename... Ts>
  static auto Debug(LogType log = LogType::Log, std::string_view message = "", Ts&&... params)
	-> void {
	// if (sizeof...(params) == 0) { return; }

	std::string msg = "\n";
	std::string msgFile;
	auto color = fg(fmt::color::white);
	switch (log) {
	  case LogType::Log:
		msg += "> Log::";
		color = fg(fmt::color::aqua);
		break;
	  case LogType::Debug:
		msg += "> Debug::";
		color = fg(fmt::color::gray);
		break;
	  case LogType::Note:
		msg += "> Note::";
		color = fg(fmt::color::light_blue);
		break;
	  case LogType::Error:
		msg += "\n# Error -----------------------------\n";
		color = fg(fmt::color::red);
		break;
	  case LogType::Warning:
		msg += "\n## Warning ----------------------------\n";
		color = fg(fmt::color::green_yellow);
		break;
	  case LogType::Check:
		msg += "\n### Check ----------------------------\n";
		color = fg(fmt::color::sandy_brown);
		break;
	  default: break;
	}

	msgFile = msg;
	msg += " {}";

	fmt::print(fmt::emphasis::bold | color, msg, std::string(message.data( )));

	constexpr overloaded visitor {
	  // Old C++17
	  // [](const auto& arg)
	  // {
	  // 	std::cout << arg;
	  // 	WriteOnFile(arg);
	  // },

	  [](const float arg) {
		std::cout << arg;
		// WriteOnFile(arg);
	  },
	  [](const int arg) {
		std::cout << arg;
		// WriteOnFile(arg);
	  },
	  [](const std::string& arg) {
		std::cout << arg;
		// WriteOnFile(arg);
	  },
	  [](const std::string_view arg) {
		std::cout << arg;
		// WriteOnFile(arg);
	  },

	  // // generic "fallback". You could also just use
	  // // this without the "overloaded" wrapper
	  []<typename T>(const T&& t) {
		// std::cout << "::Generic T&&: ";
		// std::cout << "::Generic T:\n" <<
		// typeid(T).name( );
		if constexpr (requires { std::cout << t; }) {
		  std::cout << t;
		  // WriteOnFile(t);
		  //  std::cout << "\nvalue: " << t <<
		  //  "\n";
		}
		// std::cout << '\n';
	  },
	  []<typename T>(T& t) {
		// std::cout << "::Generic T: ";
		// std::cout << "::Generic T: " <<
		// typeid(T).name( ) <<
		// "\n";
		if constexpr (requires { std::cout << t; }) {
		  std::cout << t;
		  // WriteOnFile(t);
		  //  std::cout << "\nvalue: " << t <<
		  //  "\n";
		}
		// std::cout << '\n';
	  },
	  []<typename T>(const T& t) {
		// std::cout << "::Generic T: ";
		// std::cout << "\n\n::Generic T: " <<
		// typeid(T).name( ) <<
		// "\n";
		if constexpr (requires { std::cout << t; }) {
		  std::cout << t;
		  // WriteOnFile(t);
		  //  std::cout << "\nvalue: " << t <<
		  //  "\n";
		}
		// std::cout << '\n';
	  }	  //
	};	  // Old C++17

	msgFile += message.data( );
	// WriteOnFile(msgFile); // Salvar archivo

	// fold over the comma operator, forwarding each parameter into
	// the overload set we created
	(visitor(std::forward<Ts>(params)), ...);	// Old C++17

												// if (std::is_same_v<std::string_view, Ts...>)
	// {
	// 	// ((msg += params), ...);
	// 	// ((msg += params), ...);
	// 	// std::cout << (params, ...) << '\n';
	// }
	// else { myfile << msg << t; }
  }

  template <typename T>
  static void WriteOnFile(T t) {
	// if (!write) { return; }
	std::ofstream myfile(filePath, std::fstream::app);
	myfile << t;
	myfile.close( );
  }

private:
  // static auto GetFileName( ) -> std::string { return "Log/System.md"; }
  static constexpr std::string filePath = "Log/System.md";
  // static bool write;
};

#endif	 // LOGGER_H

		 // std::string Logger::fileName = "Log/System.md";