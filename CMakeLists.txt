cmake_minimum_required(VERSION 3.23)
project(aed2223_project)

set(CMAKE_CXX_STANDARD 14)


add_executable(aed2223_project main.cpp student.cpp student.h class.cpp class.h lecture.cpp lecture.h courseunit.cpp courseunit.h schedulemanager.cpp schedulemanager.h request.cpp request.h classesfilemanager.cpp classesfilemanager.h studentsfilemanager.cpp studentsfilemanager.h application.cpp menu.cpp menu.h bst.h studentbst.h studentbst.cpp requestsfilemanager.h requestsfilemanager.cpp)


# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

