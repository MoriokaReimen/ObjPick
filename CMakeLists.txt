# ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
# ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
# ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
# ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
# ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
# ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
# 2023/1/7 
cmake_minimum_required(VERSION 3.20...3.23)
project(OpenGL CXX)

###########################################################################
# Configure compiler settings
###########################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###########################################################################
# Fetch Boost and CGAL libraries
###########################################################################
include(${CMAKE_CURRENT_LIST_DIR}/cmake/ThirdParty.cmake)

###########################################################################
# Configure sample build
###########################################################################
file(GLOB RENDER_SRC ${CMAKE_CURRENT_LIST_DIR}/src/Render/*.cpp)
add_library(Render STATIC ${RENDER_SRC})
target_include_directories(Render PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)
target_link_libraries(Render Boost::Boost EnTT::EnTT glfw Eigen3::Eigen fmt::fmt
                             glad spdlog::spdlog)

