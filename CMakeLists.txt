cmake_minimum_required(VERSION 2.8)
project(PositionEstimation)

#Added to detect compiler support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/modules)

option(SINGLE_POINT_CALIBRATION "Use Single Point Muon Calibration" ON)
option(VERTICAL_ARRANGEMENT "Use VERTICAL_ARRANGEMENT" ON)
option(FOLDED_DATA "Use FOLDED_DATA" ON)
option(VERBOSE "Switching it ON will a lot of debuggin info" OFF)
option(DEB "Use extra data member for debuggin" OFF)
option(USE_EXISTING_MUON_PEAK_FILE "Use the existing muon peak file" ON)
option(USE_PRECOMPILED_DQM_LIB "Use the precomiled dqm libraries" OFF)

if(USE_EXISTING_MUON_PEAK_FILE)
add_definitions(-DUSE_EXISTING_MUON_PEAK_FILE)
endif(USE_EXISTING_MUON_PEAK_FILE)

if(SINGLE_POINT_CALIBRATION)
add_definitions(-DSINGLE_POINT_CALIBRATION)
endif(SINGLE_POINT_CALIBRATION)

if(DEB)
add_definitions(-DDEB)
endif(DEB)

if(VERBOSE)
add_definitions(-DVERBOSE)
endif(VERBOSE)

if(FOLDED_DATA)
add_definitions(-DFOLDED_DATA)
endif(FOLDED_DATA)

if(VERTICAL_ARRANGEMENT)
add_definitions(-DVERTICAL_ARRANGEMENT)
endif(VERTICAL_ARRANGEMENT)

#----------------------------------------------------------------------------
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIR})

find_package(MYSQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})
message(STATUS "mysql inc : ${MYSQL_INCLUDE_DIR}")

if(USE_PRECOMPILED_DQM_LIB)
find_package(Dqm REQUIRED)
message(STATUS ${Dqm_INCLUDE_DIR})
include_directories(${Dqm_INCLUDE_DIR})
SET(DQM_LIB ${Dqm_LIBRARIES})
else()
add_subdirectory(ISMRAN_dqm)
link_directories(${CMAKE_SOURCE_DIR}/ISMRAN_dqm)
include_directories(${CMAKE_SOURCE_DIR}/ISMRAN_dqm/inc)
SET(DQM_LIB Dqm)
endif(USE_PRECOMPILED_DQM_LIB)

add_subdirectory(Characterization)

include_directories(${PROJECT_SOURCE_DIR}/inc)

ROOT_GENERATE_DICTIONARY(G__IsmranAnalysis inc/ScintillatorBar_F.h inc/SingleMuonTrack.h inc/MuonPeakAnalyzer.h LINKDEF inc/DictLinkDef.h)
file(GLOB analysisSources ${PROJECT_SOURCE_DIR}/src/*.cpp) 
add_library(Analysis SHARED ${analysisSources} G__IsmranAnalysis.cxx)
target_link_libraries(Analysis ${ROOT_LIBRARIES})

file(GLOB ROOT_FILES ${PROJECT_SOURCE_DIR}/rootfiles/*)
#message(STATUS ${ROOT_FILES})
file(COPY ${ROOT_FILES} DESTINATION ${PROJECT_SOURCE_DIR}/build)

SET(TESTSDIR ${TESTSDIR}
${CMAKE_SOURCE_DIR}/test
${CMAKE_SOURCE_DIR}/test/calib
${CMAKE_SOURCE_DIR}/test/core
${CMAKE_SOURCE_DIR}/test/ML
#${CMAKE_SOURCE_DIR}/test/toSchedule
)

#COLLECTING ALL TEST FILES
macro(collect_tests TESTS)
  foreach(TEST ${TESTS})
    file(GLOB tests ${tests} ${TEST}/*.cpp)
  endforeach()
endmacro()

macro(build_executables EXECUTABLES)
  foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(TARGET_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${TARGET_NAME} ${EXECUTABLE} ${headers} ${sources})
    target_link_libraries(${TARGET_NAME} ${ROOT_LIBRARIES} Analysis Spectrum stdc++fs ${DQM_LIB})
    #target_link_libraries(${TARGET_NAME} ${ROOT_LIBRARIES} Analysis Spectrum stdc++fs ${Dqm_LIBRARIES})
    #target_link_libraries(${TARGET_NAME} ${ROOT_LIBRARIES} Analysis Spectrum stdc++fs)
 endforeach()
endmacro()

collect_tests("${TESTSDIR}")
build_executables("${tests}")


