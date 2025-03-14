#ifndef LOGGER_H
#define LOGGER_H

// https://www.modernescpp.com/index.php/automatic-return-type-c-11-14-20

#include <cassert>
#include <expected>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string_view>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ranges.h>

using namespace std::literals;

template<class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};

enum class LogType { Log, Debug, Note, Error, Check, Check_01, Warning };

class Logger {
 public:
  template<typename... Ts>
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
        color = fg(fmt::color::cornflower_blue);
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
        msg += "### Check ### ";
        color = fg(fmt::color::sandy_brown);
        break;
      case LogType::Check_01:
        msg += "### Check_01 ### ";
        color = fg(fmt::color::forest_green);
        break;
      default: break;
    }

    msgFile = msg;
    msg += " {}";

    // switch (log) {
    //   case LogType::Check: msg += "\n"; break;
    //   case LogType::Check_01: msg += "\n"; break;
    //   default: break;
    // }

    // Error con consteval
    // fmt::print(fmt::emphasis::bold | color, msg, std::string(message.data())); // ERROR

    fmt::print(color | fmt::emphasis::bold, fmt::runtime(msg), message);

    msgFile += message.data();

    // constexpr overloaded visitor { [](const float arg) { std::cout << arg; },
    // 							   [](const int arg) { std::cout << arg; },
    // 							   [](const std::string& arg) { std::cout << arg; },
    // 							   [](const std::string_view arg) { std::cout << arg; },
    //
    // 							   []<typename T>(const T&& t) {
    // 								 if constexpr (requires { std::cout << t; }) { std::cout << t; }
    // 							   },
    // 							   []<typename T>(T& t) {
    // 								 if constexpr (requires { std::cout << t; }) { std::cout << t; }
    // 							   },
    // 							   []<typename T>(const T& t) {
    // 								 if constexpr (requires { std::cout << t; }) { std::cout << t; }
    // 							   } };

    constexpr overloaded visitor {
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
    } //
    }; // Old C++17

    msgFile += message.data();
    // WriteOnFile(msgFile); // Salvar archivo

    (visitor(std::forward<Ts>(params)), ...);
  }

  template<typename T> static void WriteOnFile(T t) {
    // if (!write) { return; }
    std::ofstream myfile(filePath, std::fstream::app);
    myfile << t;
    myfile.close();
  }

 private:
  // static auto GetFileName( ) -> std::string { return "Log/System.md"; }
  static constexpr std::string filePath = "Log/System.md";
  // static bool write;
};

#endif // LOGGER_H

       // std::string Logger::fileName = "Log/System.md";