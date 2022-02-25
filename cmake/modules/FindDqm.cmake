# - Finds Vc installation ( the wrapper library to SIMD intrinsics )
# This module sets up Vc information 
# It defines:
# Dqm_FOUND          If the ROOT is found
# Dqm_INCLUDE_DIR    PATH to the include directory
# Dqm_LIBRARIES      Most common libraries
# Dqm_LIBRARY_DIR    PATH to the library directory 

# look if an environment variable DqmROOT exists
set(DqmROOT $ENV{DqmROOT})
find_library(Dqm_LIBRARIES libDqm.so PATHS ${DqmROOT}/lib)

if (Dqm_LIBRARIES) 
   set(Dqm_FOUND TRUE)	
   #string(REPLACE "/lib/libVc.a" "" DqmROOT  ${Dqm_LIBRARIES})
   set(Dqm_INCLUDE_DIR ${DqmROOT}/inc)
   set(Dqm_LIBRARY_DIR ${DqmROOT}/lib)
   message(STATUS "Found Dqm library in ${Dqm_LIBRARIES}")		
else()
   message(STATUS "Dqm library not found; try to set a DqmROOT environment variable to the base installation path or add -DDqmROOT= to the cmake command")	
endif()

