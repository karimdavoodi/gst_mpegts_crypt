cmake_minimum_required(VERSION 3.10)
project(gst_mpegts_crypt)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)

add_definitions( 
    -fdiagnostics-show-location=every-line
    -fdiagnostics-generate-patch 
    -DBOOST_LOG_DYN_LINK=1
    -DGST_USE_UNSTABLE_API=1
    #-g
    )

#GSTREAMER
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTMM REQUIRED 
    gstreamer-1.0
    glib-2.0    
    gstreamer-base-1.0
    )

set(PLUGIN gstmpegtscrypt )
add_library(${PLUGIN} SHARED src/${PLUGIN}.cpp src/crypt.cpp )
target_link_libraries(${PLUGIN} ${GSTMM_LIBRARIES} 
    -ldvbcsa                  
    -lcrypto
    )
target_include_directories(${PLUGIN} PUBLIC ${GSTMM_INCLUDE_DIRS})

