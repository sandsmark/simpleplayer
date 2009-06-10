# So it won't whine. I'm not aware of any reason we can't go lower.
cmake_minimum_required(VERSION 2.6)

project (simpleplayer)

set (SIMPLEPLAYER_SRCS simpleplayer.cpp)
add_definitions(-Wall)

find_package(Qt4 REQUIRED)
find_package(Phonon REQUIRED)
include(${QT_USE_FILE} ${PHONON_INCLUDE_DIR})

add_executable(simpleplayer ${SIMPLEPLAYER_SRCS})
target_link_libraries(simpleplayer ${QT_LIBRARIES} ${PHONON_LIBRARY})

