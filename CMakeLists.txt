cmake_minimum_required(VERSION 2.8)

include(FindPkgConfig)

add_definitions(-DABC=1)

add_executable(dnimp dnimp/main.cpp)

pkg_check_modules(OPENCV REQUIRED opencv)
pkg_check_modules(ZMQ REQUIRED libzmq )
pkg_check_modules(GMK REQUIRED GraphicsMagick)

target_link_libraries(dnimp ${OPENCV_LIBRARIES} ${ZMQ-LIBRARIES} ${GMK-LIBRARIES})
