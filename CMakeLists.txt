# simple phonon media player
# GPL 2 or later
# copyright 2009 sandsmark
# love long and prosper

# So it won't whine. I'm not aware of any reason we can't go lower.
cmake_minimum_required(VERSION 2.6)

project (simpleplayer)

set (simpleplayer_srcs
    simpleplayer.cpp
    fht.cpp
    analyzerbase.cpp
    boomanalyzer.cpp
    blockanalyzer.cpp)

set (simpleplayer_hdrs
     simpleplayer.h
     boomanalyzer.h
     analyzerbase.h
     blockanalyzer.h)

add_definitions(-Wall -Werror)

find_package(Qt4 REQUIRED)
find_package(Phonon REQUIRED)
include(${QT_USE_FILE} ${PHONON_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

qt4_wrap_cpp(simpleplayer_moc ${simpleplayer_hdrs})

add_executable(simpleplayer ${simpleplayer_srcs} ${simpleplayer_moc})
target_link_libraries(simpleplayer ${QT_LIBRARIES} ${PHONON_LIBRARY})

install(TARGETS simpleplayer DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

