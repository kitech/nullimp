cmake_minimum_required(VERSION 2.8)

#set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_FLAGS "-g -O2 -pipe -std=c99")
set(CMAKE_CXX_FLAGS "-g -O2 -pipe -std=c++11")

add_definitions(-DABC=1)

add_executable(dnimp dnimp/main.cpp dnimp/benchmark.cpp dnimp/baseimp.cpp
  dnimp/ocvimp.cpp dnimp/impfactory.cpp
  )

include(FindPkgConfig)
pkg_check_modules(OPENCV REQUIRED opencv)
pkg_check_modules(ZMQ REQUIRED libzmq )
pkg_check_modules(GMK REQUIRED GraphicsMagick)
pkg_check_modules(GMKW REQUIRED GraphicsMagickWand)
#pkg_check_modules(VIPS REQUIRED vipsCC)

include_directories(${GMKW_INCLUDE_DIRS} ${VIPS_INCLUDE_DIRS})
target_link_libraries(dnimp 
  # ${OPENCV_LIBRARIES}
  opencv_core opencv_imgproc opencv_highgui
  GraphicsMagickWand
  
  ${ZMQ_LIBRARIES}
#  ${GMKW_LIBRARIES}  
#  ${VIPS_LIBRARIES}
#  -lvipsCC
  )
