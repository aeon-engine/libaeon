find_program(MONO_EXECUTABLE mono)
find_program(MCS_EXECUTABLE mcs)
find_program(GACUTIL_EXECUTABLE gacutil)

find_library(MONO_MAIN_LIBRARY mono-2.0)

set(MONO_FOUND FALSE CACHE INTERNAL "")

if(MONO_EXECUTABLE AND MCS_EXECUTABLE AND GACUTIL_EXECUTABLE AND MONO_MAIN_LIBRARY)
    set(MONO_FOUND TRUE CACHE INTERNAL "")

    # default GAC is located in <prefix>/lib/mono/gac
    find_path(MONO_GAC_PREFIX lib/mono/gac PATHS "/usr;/usr/local")

    set(MONO_GAC_PREFIX "${MONO_GAC_PREFIX}" CACHE PATH "Mono GAC prefix")
    set(MONO_GAC_DIR "${MONO_GAC_PREFIX}/lib/mono" CACHE PATH "Mono GAC directory")

    get_filename_component(MONO_LIBRARY_PATH "${MONO_MAIN_LIBRARY}" DIRECTORY)
    get_filename_component(MONO_INCLUDE_PATH "${MONO_LIBRARY_PATH}/../include/mono-2.0" ABSOLUTE)

    set(MONO_LIBRARIES "${MONO_MAIN_LIBRARY}")
    
    if (APPLE)
        find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
        set(MONO_LIBRARIES "${MONO_LIBRARIES};${CORE_FOUNDATION_LIBRARY}")
    endif ()

    execute_process(COMMAND ${MCS_EXECUTABLE} --version OUTPUT_VARIABLE MONO_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX REPLACE ".*version ([^ ]+)" "\\1" MONO_VERSION "${MONO_VERSION}")
endif()
