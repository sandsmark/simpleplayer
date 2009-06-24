# simple phonon media player
# GPL 2 or later
# copyright 2009 sandsmark
# love long and prosper

# So it won't whine. I'm not aware of any reason we can't go lower.
cmake_minimum_required(VERSION 2.6)

project (simpleplayer)

set (SIMPLEPLAYER_SRCS simpleplayer.cpp)
add_definitions(-Wall -Werror)

find_package(Qt4 REQUIRED)
find_package(Phonon REQUIRED)
include(${QT_USE_FILE} ${PHONON_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

qt4_wrap_cpp(SIMPLEPLAYER_MOC ${SIMPLEPLAYER_SRCS})

add_executable(simpleplayer ${SIMPLEPLAYER_SRCS})
target_link_libraries(simpleplayer ${QT_LIBRARIES} ${PHONON_LIBRARY})

#phononexperimental

