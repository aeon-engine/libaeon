message("Compiler: ${CMAKE_CXX_COMPILER_ID}")
message("Version: ${CMAKE_CXX_COMPILER_VERSION}")

if (MSVC)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.0)
        message(FATAL_ERROR "Requires Visual Studio 2013 or higher!")
    endif ()

    message("Visual Studio detected. Setting flags:")
    message(" - Defining _SCL_SECURE_NO_WARNINGS")
    message(" - Defining _CRT_SECURE_NO_DEPRECATE")
    message(" - Setting Windows 7 API level (_WIN32_WINNT=0x0601)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -D_WIN32_WINNT=0x0601")
endif ()

if (NOT MSVC)
    message("Not on Visual Studio. Setting flags:")
    message(" - C++1y support")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
endif ()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
        message(FATAL_ERROR "Requires GCC 5.1.0 or higher!")
    else ()
        message("GNU GCC detected. Setting flags:")

        message(" - CLion Debugger STL Renderer workaround")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")

        message(" - Suppressing C++ deprecation warnings.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    endif ()
endif ()

