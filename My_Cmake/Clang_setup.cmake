# # // TODO Actualizar: EN lugar de CMAKE_CXX_FLAGS usar add_compile_options
## Notes
## Solo usar -fvisibility=hidden con librerias STATIC

## OBSOLETO, Puede que se tenga que borrar este archivo

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "+++ Using Clang!!! ${CMAKE_CXX_COMPILER} - ${CMAKE_CXX_COMPILER_VERSION}")

    # set(CMAKE_CXX_COMPILER "clang++")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a ")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -stdlib=libc++ -fmodules -fbuiltin-module-map -fimplicit-module-maps -fprebuilt-implicit-modules")

    # set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)

    # add_compile_options(-fmodules)
    add_compile_options(-stdlib=libc++)
    #    add_compile_options(-stdlib=libc++ -fvisibility=hidden)

    # add_compile_options(-fbuiltin-module-map)
    # add_compile_options(-fimplicit-module-maps)
    # add_compile_options(-fprebuilt-module-path=${PREBUILT_MODULE_PATH})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "+++ Using GNU!!! ${CMAKE_CXX_COMPILER} - ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "+++ CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ")

    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -march=x86-64 -static-libgcc -static-libstdc++ -fPIC -Wwrite-strings") # Debug
    # Define the common flags
    set(CPP_Flags
            -m64
            -march=native
            -static-libgcc
            -static-libstdc++
            -fPIC
            -Wwrite-strings
            -pipe
    )

    # Define the debug flags
    set(CPP_Flags_Debug
            -Wl,-R,'$$ORIGIN'
            -g
    )

    # Define the release flags
    set(CPP_Flags_Release
            -O2
    )

    # Convert lists to string
    string(JOIN " " CMAKE_CXX_FLAGS "${CPP_Flags}")
    string(JOIN " " CMAKE_CXX_FLAGS_DEBUG "${CPP_Flags}" "${CPP_Flags_Debug}")
    string(JOIN " " CMAKE_CXX_FLAGS_RELEASE "${CPP_Flags}" "${CPP_Flags_Release}")

    # Set the flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-R,'$$ORIGIN' -g -Wwrite-strings")


    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fmodules-ts")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fdiagnostics-color=always ")
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "+++ Using INTEL!!!")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "+++ Using MSVC!!!")
endif ()