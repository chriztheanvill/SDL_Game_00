# ##### Libraries ######
#
# Type of libraries
# SHARED:		dll, so, dylib
# STATIC:		lib, a
# INTERFACE:	Only headers, Doesnt show up in IDE's
#
# * Shared are small space size, does not uses RAM
# But sometimes needs some 3rds libraries to work on
#
# * Static, does not need 3rds, there all in the lib
# But are bigger in space size, uses RAM to work

# ## Find all files in a folder
#file(GLOB_RECURSE ENGINE_LIB_GLOB
#        CONFIGURE_DEPENDS
#        "src/*.*"
#)

# ## Engine
add_library(

        #        Engine
        #        Engine STATIC
        Engine SHARED

        #        ${ENGINE_LIB_GLOB}

        #        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Component.cpp

        #
        Engine/Utils/Delegates.hpp
        Engine/Utils/EnumComponentID.hpp
        Engine/Utils/Logger.h
        Engine/Utils/Utils.hpp
        Engine/Utils/Vector2D.h
        #
        Engine/ECS/Pool.hpp
        Engine/ECS/GenID.hpp
        Engine/ECS/GenID.cpp
        Engine/ECS/System.cpp
        Engine/ECS/System.hpp
        Engine/ECS/Registry.cpp
        Engine/ECS/Registry.hpp
        Engine/ECS/Entity.cpp
        Engine/ECS/Entity.hpp
        #
        Engine/Core/Core.cpp
        Engine/Core/Core.hpp
        Engine/Core/Engine.h
        Engine/Core/Engine.cpp
        Engine/Core/Time.h
        Engine/Core/Time.cpp
        #
        Engine/Graphics/TextureManager.h
        Engine/Graphics/TextureManager.cpp
        #
        Engine/Input/Controller.h
        Engine/Input/Controller.cpp
        Engine/Input/InputSystem.h
        Engine/Input/InputSystem.cpp
        #
        Engine/Maps/Tile.hpp
        Engine/Maps/TileMap.hpp
        Engine/Maps/TileMap.cpp
        #
        Engine/Parsers/MapFileParser.hpp
        Engine/Parsers/MapFileParser.cpp
        Engine/Parsers/Player_Config.hpp
        Engine/Parsers/Player_Config.cpp
        #
        Engine/Components/AnimationComponent.hpp
        Engine/Components/ColliderComponent.hpp
        Engine/Components/ComponentBase.hpp
        Engine/Components/GraphicComponent.hpp
        Engine/Components/Point.hpp
        Engine/Components/RigidBodyComponent.h
        Engine/Components/TransformComponent.hpp
        #
        Engine/Systems/AnimationSystem.cpp
        Engine/Systems/AnimationSystem.hpp
        Engine/Systems/CollisionSystem.cpp
        Engine/Systems/CollisionSystem.hpp
        Engine/Systems/MovementSystem.cpp
        Engine/Systems/MovementSystem.hpp
        Engine/Systems/RenderSystem.cpp
        Engine/Systems/RenderSystem.hpp
        Engine/Systems/RenderColliderSystem.cpp
        Engine/Systems/RenderColliderSystem.hpp
        #
)

add_library(ImGuiBackends STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_sdl2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_sdl2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_sdlrenderer2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_sdlrenderer2.h
        #        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_opengl3.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_opengl3.h
        #        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_opengl3_loader.h
        #        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_vulkan.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends/imgui_impl_vulkan.h
)

# add_library(
# Component SHARED
# src/Engine/Component.h
# )

# set_target_properties(Component PROPERTIES LINKER_LANGUAGE CXX)

# ## Unique Header file
# # Examples Librarie
# add_library(
# examples_video
# examples/examples_video.h
# )
# ## Set examples_video.h C++ file
# ## This is only for unique headers.
# set_target_properties(examples_video PROPERTIES LINKER_LANGUAGE CXX)
# ## Unique Header file

# PUBLIC:		MAIN + SON_LIBRARY
# PRIVATE:		SON_LIBRARY
# INTERFACE:	MAIN
target_include_directories(
        #        Engine INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src"
        Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Engine"

        ImGuiBackends PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/ImGuiBackends"
        # Entity PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
        # EntityManager PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
        # Component PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
        # Transform PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(Engine PUBLIC ENGINE_VERSION=1)

# ### Add LINKS
target_link_libraries(
        ImGuiBackends PUBLIC
        imgui::imgui
)

target_link_libraries(
        Engine PUBLIC

        ImGuiBackends
        # # Options
        # project_options
        # project_warnings
        #
        # # Pkgs
        #Catch2::Catch2
        fmt::fmt
        nlohmann_json::nlohmann_json
        #        SQLite::SQLite3
        imgui::imgui
        SQLiteCpp


        # CONAN_PKG::imgui-sfml
        # CONAN_PKG::sdl2

        #
        ${LUA_LIBRARY}
        ${THREAD_LIBRARIES}
        ${OPENGL_VIDEO_LIBRARIES}
)

set(CPP_Flags
        -m64
        -march=native
        -static-libgcc
        -static-libstdc++
        -fPIC
        -Wwrite-strings
        -pipe
        #        -O2 ## Disminuir el consumo en CPU
)

target_compile_options(Engine PRIVATE
        ${CPP_Flags}
)