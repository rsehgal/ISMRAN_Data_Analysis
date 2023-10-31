cmake_minimum_required(VERSION 2.8)
project(PositionEstimation)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)


#Added to detect compiler support for C++11
#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
#CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
#if(COMPILER_SUPPORTS_CXX17)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#elseif(COMPILER_SUPPORTS_CXX14)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#    #add_definitions(-DEXPERIMENTAL_FILESYSTEM)
#    message(STATUS "Going to use experimental filesystem. Its recommended to switch to upgraded compile with c++17 support.")
#else()
#    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 or C++17 support. Please use a different C++ compiler.")
#endif()

#if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 8.0)
#else()
#message(STATUS "@@@@@@ Adding EXPERIMENTAL_FILELSYSTEm Macro @@@@@@")
#add_definitions(-DEXPERIMENTAL_FILESYSTEM)
#endif()

#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
#if(COMPILER_SUPPORTS_CXX17)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#endif()

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    add_definitions(-DEXPERIMENTAL_FILESYSTEM)
    message(STATUS "Going to use experimental filesystem. Its recommended to switch to upgraded compile with c++17 support.")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 or C++17 support. Please use a different C++ compiler.")
endif()

if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 8.0)
else()
message(STATUS "@@@@@@ Adding EXPERIMENTAL_FILELSYSTEm Macro @@@@@@")
#add_definitions(-DEXPERIMENTAL_FILESYSTEM)
endif()


find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
message(STATUS ${ROOT_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/inc)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)


add_library(Characterization SHARED ${sources})
target_link_libraries(Characterization ${ROOT_LIBRARIES} -L/home/rsehgal/BackBoneSoftwares/root/lib Spectrum)

#add_executable (Test_Listing test/Test_Listing)
#target_link_libraries(Test_Listing Characterization)

#add_executable (Test_Substring test/core/Test_Substring.cpp)
#target_link_libraries(Test_Substring ${ROOT_LIBRARIES})

add_executable (Test_RegExp test/core/Test_RegExp.cpp)
target_link_libraries(Test_RegExp ${ROOT_LIBRARIES})

add_executable (Test_DirListing test/core/Test_DirListing.cpp)
target_link_libraries(Test_DirListing ${ROOT_LIBRARIES})

#message(STATUS ${ROOT_LIBRARIES})

#Working
#add_executable (Test_GenerateCalibrationFile test/anal/Test_GenerateCalibrationFile.cpp ${sources})
#target_link_libraries(Test_GenerateCalibrationFile ${ROOT_LIBRARIES} -L/home/rsehgal/BackBoneSoftwares/root-6.26.00/lib Spectrum)

#Trying with shared library
add_executable(Test_GenerateCalibrationFile test/anal/Test_GenerateCalibrationFile.cpp)
target_link_libraries(Test_GenerateCalibrationFile Characterization)

#target_link_libraries(Test_GenerateCalibrationFile ${ROOT_LIBRARIES} Spectrum)

