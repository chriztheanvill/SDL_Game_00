# #
# ## Find all files in a folder
file(GLOB_RECURSE GAME_PROTOTYPE_00
        CONFIGURE_DEPENDS
        "src/*.*"

        # "src/*.cpp"
)

# ## Main proyect ###
add_executable(
        ${PROJECT_NAME}

        ${GAME_PROTOTYPE_00}
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Components/ComponentBase.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Components/GraphicComponent.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Components/Point.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Components/RigidBodyComponent.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Components/SpriteComponent.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Components/TileComponent.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Components/TransformComponent.hpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Core/Constants.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Core/Engine.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Core/Engine.cpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Core/Node.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Core/Time.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Core/Time.cpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/ECS/ECS.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/ECS/ECS.cpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/ECS/Pool.hpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Game/Game.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Game/Game.cpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Graphics/TextureManager.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Graphics/TextureManager.cpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Input/Controller.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Input/Controller.cpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Input/InputSystem.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Input/InputSystem.cpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Maps/Tile.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Maps/TileMap.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Maps/TileMap.cpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Parsers/MapFileParser.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Parsers/MapFileParser.cpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Parsers/Player_Config.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Parsers/Player_Config.cpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Systems/MovementSystem.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Systems/RenderSystem.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Systems/RenderTileMapSystem.hpp
        #        #
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Utils/Delegates.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Utils/EnumComponentID.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Utils/Logger.h
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Utils/Utils.hpp
        #        ${PROJECT_SOURCE_DIR}/Source/Main/src/Utils/Vector2D.h


        main.cpp
)

# target_compile_definitions(file_name PRIVATE #DEFINE)
# target_compile_definitions(main.cpp PRIVATE FRENCH)

# ## Add LINKS
target_link_libraries(
        ${PROJECT_NAME} PUBLIC

        # # Options
        # project_options
        # project_warnings
        #
        # # Pkgs
        Catch2::Catch2
        fmt::fmt
        nlohmann_json::nlohmann_json
        SQLite::SQLite3

        # range-v3::range-v3

        # CONAN_PKG::imgui-sfml
        # CONAN_PKG::sdl2
        # # MY LIBRARIES

        # Component
        # Engine

        # ####################################
        # # Conan v1
        # CONAN_PKG::docopt.cpp
        # CONAN_PKG::fmt
        # CONAN_PKG::spdlog
        # CONAN_PKG::range-v3

        # CONAN_PKG::glew # OpenGL
        # CONAN_PKG::glad # OpenGL
        # CONAN_PKG::nlohmann_json
        #
        ${LUA_LIBRARY}
        ${THREAD_LIBRARIES}
        ${OPENGL_VIDEO_LIBRARIES}
)

# ###############################################################
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    message(STATUS " -- Build Type ${CMAKE_BUILD_TYPE} \n\n")

    # # Conan v1
    message(STATUS "++ Creating Symbolic Links ++\n")
    add_custom_target(
            linking_assets

            # COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/Source/Main/assets
    )
    add_dependencies(${PROJECT_NAME} linking_assets)

    # # Conan v2
    # message(STATUS " -- Copy assets")

    # message(STATUS " -- PROJECT SOURCE DIR ${PROJECT_SOURCE_DIR} \n\n")
    # message(STATUS " -- BINARY DIR ${CMAKE_BINARY_DIR} \n\n")
    # add_custom_command(TARGET ${PROJECT_NAME}
    # POST_BUILD
    # COMMAND mkdir -p ${CMAKE_BINARY_DIR}/Source/Main/assets
    # COMMAND ln -s ${PROJECT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/Source/Main/assets
    # )
    # file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Source/Main/)
else ()
    message(STATUS " -- Build Type RELEASE \n\n")
    message(STATUS "++ Copying files ++\n")

    # file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif ()

# ###############################################################

# ## Add LINKS
