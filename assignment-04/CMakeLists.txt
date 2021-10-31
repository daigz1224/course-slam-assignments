cmake_minimum_required( VERSION 2.8 )  
 
project( Assignment04 )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_BUILD_TYPE "-03" )
set( CMAKE_CXX_FLAGS "-std=c++11" )

find_package( OpenCV 3.4 REQUIRED )
find_package( Pangolin REQUIRED )

include_directories( "/usr/include/eigen3" )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_executable( undistort_image code/undistort_image.cpp )
target_link_libraries( undistort_image ${OpenCV_LIBS} )

add_executable( disparity code/disparity.cpp )
target_link_libraries( disparity ${Pangolin_LIBRARIES} ${OpenCV_LIBS} )

add_executable( gaussnewton code/gaussnewton.cpp )
target_link_libraries( gaussnewton ${OpenCV_LIBS} )
