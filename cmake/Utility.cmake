# ███╗░░░███╗░█████╗░██████╗░██╗░█████╗░██╗░░██╗░█████╗░
# ████╗░████║██╔══██╗██╔══██╗██║██╔══██╗██║░██╔╝██╔══██╗
# ██╔████╔██║██║░░██║██████╔╝██║██║░░██║█████═╝░███████║
# ██║╚██╔╝██║██║░░██║██╔══██╗██║██║░░██║██╔═██╗░██╔══██║
# ██║░╚═╝░██║╚█████╔╝██║░░██║██║╚█████╔╝██║░╚██╗██║░░██║
# ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝
# 2023/1/7 Create file
include_guard(DIRECTORY)

###########################################################################
# search_target
# search all build target under the specified directory
# !!remarks!! alias and interfaces are not included
# param: target_dir    top directory to search
# param: out           found target name in list
###########################################################################
function(search_target target_dir out)
    set(targets)
    get_all_targets_recursive(targets ${target_dir})
    set(${out} ${targets} PARENT_SCOPE)
endfunction(search_target)

macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()

    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()

###########################################################################
# search_interface
# search all interface under the specified directory
# param: target_dir    top directory to search
# param: out           found interface name in list
###########################################################################
function(search_interface target_dir out)
  # find CMakeLists.txt under directory
  file(GLOB_RECURSE files CONFIGURE_DEPENDS
    ${target_dir}/CMakeLists.txt
  )

  # search interface for each files
  set(result "")
  foreach(file IN LISTS files)
    file(STRINGS ${file} data)
    foreach(line IN LISTS data)
      if(line MATCHES "(boost_[A-Za-z0-9_]+)[ ]*INTERFACE")
        string(REGEX REPLACE "^numeric_" "numeric/" dep ${CMAKE_MATCH_1})
        list(APPEND result ${dep})
      endif()
    endforeach()
  list(REMOVE_DUPLICATES result)
  set(${out} ${result} PARENT_SCOPE)
  endforeach()
endfunction(search_interface)

