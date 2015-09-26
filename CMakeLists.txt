cmake_minimum_required(VERSION 2.8.4)

set(PROJECT_NAME "Viewer")
project(${PROJECT_NAME})

find_package (Threads)

# Pulls in all the needed opencv stuff
#find_package( OpenCV REQUIRED )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system filesystem thread program_options regex REQUIRED)

set(OpenCV_INCLUDE_DIR "/usr/local/include/opencv")
set(OpenCV2_INCLUDE_DIR "/usr/local/include")

set(local_LIBRARY_DIR "/usr/local/lib")

set(project_LIBRARY_DIR "lib")

set(OpenCV_LIBRARIES
	opencv_gpu
	opencv_core
	opencv_imgproc
	opencv_highgui
	opencv_ml
	opencv_video
	opencv_features2d
	opencv_nonfree
	opencv_calib3d
	opencv_objdetect
	opencv_contrib
	opencv_legacy
	opencv_flann
)

set(Pthreads_LIBRARY pthread)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE(GLOB SOURCE_FILES src/*.cpp)

set(HEADER_DIR include)

FILE(GLOB HEADER_FILES ${HEADER_DIR}/*.hpp)

include_directories(${HEADER_DIR} ${Boost_INCLUDE_DIR} ${OpenCV_INCLUDE_DIR} ${OpenCV2_INCLUDE_DIR})
link_directories(${local_LIBRARY_DIR} ${project_LIBRARY_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries (${PROJECT_NAME} ${AV_CODEC_LIB} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBRARIES})
