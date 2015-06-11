if (NOT Boost_UNIT_TEST_FRAMEWORK_FOUND)
    message(FATAL_ERROR "Unittests.cmake requires the boost unit_test_framework component.")
endif ()

include(CMakeParseArguments)

include(CTest)
enable_testing()

function(add_unit_test_suite)
    cmake_parse_arguments(
        UNIT_TEST_PARSED_ARGS
        ""
        "TARGET"
        "SOURCES;LIBRARIES;INCLUDES;LABELS"
        ${ARGN}
    )

    if (NOT UNIT_TEST_PARSED_ARGS_TARGET)
        message(FATAL_ERROR "No target name was given for unit test.")
    endif ()

    if (NOT UNIT_TEST_PARSED_ARGS_SOURCES)
        message(FATAL_ERROR "No sources were given for unit test.")
    endif ()

    foreach(_src ${UNIT_TEST_PARSED_ARGS_SOURCES})
        list (APPEND SRCS "${UNIT_TEST_PARSED_ARGS_TARGET}/${_src}")
    endforeach()

    add_executable(${UNIT_TEST_PARSED_ARGS_TARGET} ${SRCS})

    target_include_directories(${UNIT_TEST_PARSED_ARGS_TARGET} PRIVATE ${Boost_INCLUDE_DIRS})

    if (UNIT_TEST_PARSED_ARGS_INCLUDES)
        target_include_directories(${UNIT_TEST_PARSED_ARGS_TARGET} PRIVATE ${UNIT_TEST_PARSED_ARGS_INCLUDES})
    endif ()

    target_link_libraries(
        ${UNIT_TEST_PARSED_ARGS_TARGET}
        ${Boost_LIBRARIES}
    )

    if (UNIT_TEST_PARSED_ARGS_LIBRARIES)
        target_link_libraries(
            ${UNIT_TEST_PARSED_ARGS_TARGET}
            ${UNIT_TEST_PARSED_ARGS_LIBRARIES}
        )
    endif ()

    add_test(
        NAME ${UNIT_TEST_PARSED_ARGS_TARGET}
        WORKING_DIRECTORY $<TARGET_FILE_DIR:${UNIT_TEST_PARSED_ARGS_TARGET}>
        COMMAND $<TARGET_FILE:${UNIT_TEST_PARSED_ARGS_TARGET}>
    )

    list(APPEND UNIT_TEST_PARSED_ARGS_LABELS "unittest")
    set_tests_properties(${UNIT_TEST_PARSED_ARGS_TARGET} PROPERTIES LABELS "${UNIT_TEST_PARSED_ARGS_LABELS}")
endfunction()
