message(STATUS "\n++++++++++ CONAN v2 ++++++++++")


# ###############################################################
# # Conan v2
# ## Config
# # https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html
# #
# # NOTA: Solo la primera vez que se va a ejecutar conan2
# # $ conan profile detect --force
# #
# # Construir con conan2
# # $ conan install . --output-folder=build/Debug --build=missing --settings=build_type=Debug
# # $ conan install . --output-folder=build/Release --build=missing
# #
# #
# # $ cd build/Debug
# # $ cd build/Release
# #
# # $ cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ../..
# # $ cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release ../..
# #
# # $ cmake --build . --config Debug
# # $ cmake --build . --config Release
# #
# # $ cd ../.. && rm -rf build CMakeUserPresets.json compile_commands.json
# #
# #
# # # Unix
# # $ conan install . --build=missing --settings=build_type=Debug && cd build/Debug && cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . --config Debug && cd ../..

# # # Ninja
# # $ conan install . --build=missing --settings=build_type=Debug && cd build/Debug && cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . --config Debug && cd ../..

# # $ conan install . --build=missing --settings=build_type=Debug && cd build/Debug && cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . --config Debug -j`nproc` && cd ../..
# #
# #
# # Libs
# https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ConanIntegration.html

find_package(fmt REQUIRED)
find_package(SQLiteCpp REQUIRED)
#find_package(SQLite3 REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(imgui REQUIRED)

#include(${CMAKE_BINARY_DIR}/conan/build/Debug/generators/conan_toolchain.cmake)

#include(${CMAKE_BINARY_DIR}/build/conan_toolchain.cmake)

#message(STATUS "+++ qaaaaaaaaaaaaaaaaaaaaaa " ${CONAN_LIB_DIRS_imgui})
#message(STATUS "+++ qaaaaaaaaaaaaaaaaaaaaaa " ${CMAKE_BINARY_DIR} )
#message(STATUS "+++ imgui " ${IMGUI_DIR} - ${SDL2_INCLUDE_DIRS})
#include(${CMAKE_BINARY_DIR}/conan/build/Debug/generators/conan_toolchain.cmake)
#include(${CMAKE_BINARY_DIR}/conan/build/Debug/generators/conandeps_legacy.cmake)
#include(${CMAKE_BINARY_DIR}/build/conan_deps.cmake)

#find_package(imgui REQUIRED)
#find_package(glfw3 REQUIRED)
#find_package(glew REQUIRED)

# include_directories(${fmt_INCLUDE_DIR})
# link_libraries(${fmt_LIBRARIES})
# find_package(spdlog REQUIRED)
# find_package(glew REQUIRED)
# find_package(catch2)
#find_package(Catch2 REQUIRED)
#find_package(docopt REQUIRED)

# find_package(fmt)

#find_package(sol2 REQUIRED)

# find_package(range-v3)

# find_package(glad REQUIRED) ## No Conan2
# ###############################################

# # find_package(catch2)
# find_package(Catch2)
# find_package(docopt)

# # find_package(fmt)
# find_package(fmt)

# # include_directories(${fmt_INCLUDE_DIR})
# # link_libraries(${fmt_LIBRARIES})
# find_package(spdlog)
# find_package(glew)
# find_package(nlohmann_json)
# find_package(sol2)

# # find_package(range-v3)

# # find_package(glad REQUIRED) ## No Conan2
# #
# # ### (OLD VERSION) Without layout cmake
# # $ conan install . --output-folder=build/Debug --build=missing --settings=build_type=Debug && cd build/Debug && cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ../.. && cmake --build . --config Debug && cd ../..
# #
# #
# #
message(STATUS "\n++++++++++ ~CONAN v2 ++++++++++\n")