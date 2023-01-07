# ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
# ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
# ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
# ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
# ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
# ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
# 2023/1/7
include_guard(DIRECTORY)
# include cmake modules
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
include(${CMAKE_CURRENT_LIST_DIR}/Utility.cmake)

###########################################################################
# Fetch Boost
###########################################################################
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG        boost-1.81.0
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(Boost)
search_target(${boost_SOURCE_DIR} all_boost)
search_interface(${boost_SOURCE_DIR} all_boost_interface)

# remove libraries which is not builadable by default
list(REMOVE_ITEM all_boost "boost_accumulators")
list(REMOVE_ITEM all_boost "boost_python")
list(REMOVE_ITEM all_boost_interface "boost_accumulators")
list(REMOVE_ITEM all_boost_interface "boost_python")
list(REMOVE_ITEM all_boost_interface "boost_parameter_python")
list(REMOVE_ITEM all_boost "boost_parameter_python")
list(REMOVE_ITEM all_boost_interface "boost_property_map_parallel")
list(REMOVE_ITEM all_boost "boost_property_map_parallel")
list(REMOVE_ITEM all_boost_interface "boost_numpy")
list(REMOVE_ITEM all_boost "boost_numpy")
list(REMOVE_ITEM all_boost "boost_locale_test")
list(REMOVE_ITEM all_boost "boost_url_limits")
list(REMOVE_ITEM all_boost_interface "boost_locale_test")
list(REMOVE_ITEM all_boost_interface "boost_url_limits")

# add Boost::Boost
add_library(boost INTERFACE)
add_library(Boost::Boost ALIAS boost)
target_link_libraries(boost INTERFACE ${all_boost})

# add Boost::Headers
add_library(boost_headers INTERFACE)
add_library(Boost::Headers ALIAS boost_headers)
target_link_libraries(boost_headers INTERFACE ${all_boost_interface})

###########################################################################
# Fetch gtest
###########################################################################
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

###########################################################################
# Fetch glad
###########################################################################
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v2.0.3
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_Populate(glad)
add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
glad_add_library(glad_gl_core_46 STATIC API gl:core=4.6)

###########################################################################
# Fetch glfw
###########################################################################
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(glfw)

###########################################################################
# Fetch entt
###########################################################################
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG        v3.11.1
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(entt)

###########################################################################
# Fetch entt
###########################################################################
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG        v3.11.1
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(entt)

###########################################################################
# Fetch eigen
###########################################################################
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG        3.4.0
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_Populate(eigen)
add_library(eigen INTERFACE)
add_library(Eigen3::Eigen ALIAS eigen)
target_include_directories(eigen INTERFACE ${eigen_SOURCE_DIR})

###########################################################################
# Fetch fmt
###########################################################################
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        9.1.0
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(fmt)

###########################################################################
# Fetch spdlog
###########################################################################
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.11.0
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(spdlog)

###########################################################################
# Fetch cmrc
###########################################################################
FetchContent_Declare(
  cmrc
  GIT_REPOSITORY https://github.com/vector-of-bool/cmrc.git
  GIT_TAG        master
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(cmrc)

###########################################################################
# Fetch glm
###########################################################################
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8 
  GIT_SHALLOW    ON
  QUIET          OFF
  GIT_PROGRESS   ON
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(glm)

