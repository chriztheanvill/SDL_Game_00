# #
# ## Find all files in a folder
#file(GLOB_RECURSE GAME_PROTOTYPE_00
#        CONFIGURE_DEPENDS
#        "src/*.*"
#        # "src/*.cpp"
#)
include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
# ## Main proyect ###
add_executable(
        ${PROJECT_NAME}
        main.cpp

        #        ${GAME_PROTOTYPE_00}

        ##  Game
        src/Game/Game.cpp
        src/Game/Game.hpp
        src/Game/IGameObject.hpp

        ##  Scenes/SceneManager
        src/Scenes/SceneManager.cpp
        src/Scenes/SceneManager.hpp

        ## Scenes
        src/Scenes/SceneBase.cpp
        src/Scenes/SceneBase.hpp
        src/Scenes/Scene00.cpp
        src/Scenes/Scene00.hpp
        src/Scenes/SceneShip00.cpp
        src/Scenes/SceneShip00.hpp

        ## Actors/Player
        src/Actors/Player/Player.cpp
        src/Actors/Player/Player.hpp

        ##

)

if (supported)
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET Engine PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    #set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
else ()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif ()

# target_compile_definitions(file_name PRIVATE #DEFINE)
# target_compile_definitions(main.cpp PRIVATE FRENCH)


# ## Add LINKS
target_link_libraries(
        ${PROJECT_NAME} PRIVATE

        # # MY LIBRARIES
        Engine

        # # Options
        # project_options
        # project_warnings
        #
        # # Pkgs
        #Catch2::Catch2
        fmt::fmt
        nlohmann_json::nlohmann_json
        SQLiteCpp
        imgui::imgui
        #        OpenGL::GL
        #        GLEW::GLEW
        #        glfw


        # CONAN_PKG::imgui-sfml
        # CONAN_PKG::sdl2

        # ####################################

        #
        ${LUA_LIBRARY}
        ${THREAD_LIBRARIES}
        ${OPENGL_VIDEO_LIBRARIES}
)

#target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)

# ###############################################################

message(STATUS " -- Current Build Type ${CMAKE_BUILD_TYPE} \n\n")

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    message(STATUS " -- Build Type Debug \n\n")
    set(target ${PROJECT_SOURCE_DIR}/assets)
    set(link ${CMAKE_BINARY_DIR}/Source/Main/assets)

    #    if (EXISTS ${link})
    #        message(STATUS "++ Assets Symbolic Links Already EXIST ${link} --- \n")
    #    else ()
    #        message(STATUS "++ Assets Creating Symbolic Links ${link} ++\n")
    #        add_custom_target(
    #                linking_assets
    #
    #                # COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets
    #                COMMAND ${CMAKE_COMMAND} -E create_symlink ${target} ${link}
    #        )
    #        add_dependencies(${PROJECT_NAME} linking_assets)
    #    endif ()

    ##
    ##
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${target} ${link}
            #            "$<TARGET_FILE:my_program>" "${SYMLINK_PATH}"
            COMMENT "Creating symlink at ${target}"
    )

    ##
    ##
    ## This way the symlinking will be done during make install only.
    #    INSTALL(CODE "execute_process( \
    #    COMMAND ${CMAKE_COMMAND} -E create_symlink \
    #    ${target} \
    #    ${link}   \
    #    )"
    #    )

    # # Conan v1


    # # Conan v2
    # message(STATUS " -- Copy assets")

    # message(STATUS " -- PROJECT SOURCE DIR ${PROJECT_SOURCE_DIR} \n\n")
    # message(STATUS " -- BINARY DIR ${CMAKE_BINARY_DIR} \n\n")
    #    add_custom_command(TARGET ${PROJECT_NAME}
    #            POST_BUILD
    #            #            COMMAND mkdir -p ${CMAKE_BINARY_DIR}/Source/Main/assets
    #            COMMAND ln -s ${target} ${link}
    #    )
    # file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/Source/Main/)
else ()
    message(STATUS " -- Build Type RELEASE \n\n")
    message(STATUS "++ Copying files ++\n")

    # file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif ()

# ###############################################################

# ## Add LINKS

#if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "+++ Using Clang!!! ${CMAKE_CXX_COMPILER} - ${CMAKE_CXX_COMPILER_VERSION}")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "+++ Using GNU!!! ${CMAKE_CXX_COMPILER} - ${CMAKE_CXX_COMPILER_VERSION}")

    set(CPP_Flags
            -m64
            -march=native
            -static-libgcc
            -static-libstdc++
            -fPIC
            -Wwrite-strings
            -pipe
            #            -O2 ## Disminuir el consumo en CPU
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
            ${CPP_Flags}
    )

    target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:
            #            "-Wl,-R,\\\\$ORIGIN"
            ${CPP_Flags}
            "-Wl,-R,'$$ORIGIN'"
            -g
            >)

    target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:
            ${CPP_Flags}
            -O2
            >)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "+++ Using INTEL!!!")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "+++ Using MSVC!!!")
endif ()

# Obtener y imprimir las opciones de compilación
get_target_property(compile_options ${PROJECT_NAME} COMPILE_OPTIONS)
if (compile_options)
    message(STATUS "Opciones de compilación para mi_ejecutable: ${compile_options}")
else ()
    message(STATUS "No hay opciones de compilación definidas para mi_ejecutable")
endif ()