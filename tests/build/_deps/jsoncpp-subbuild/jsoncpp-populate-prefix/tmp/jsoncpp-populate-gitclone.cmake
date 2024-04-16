
if(NOT "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-subbuild/jsoncpp-populate-prefix/src/jsoncpp-populate-stamp/jsoncpp-populate-gitinfo.txt" IS_NEWER_THAN "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-subbuild/jsoncpp-populate-prefix/src/jsoncpp-populate-stamp/jsoncpp-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-subbuild/jsoncpp-populate-prefix/src/jsoncpp-populate-stamp/jsoncpp-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/open-source-parsers/jsoncpp.git" "jsoncpp-src"
    WORKING_DIRECTORY "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/open-source-parsers/jsoncpp.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout 1.9.4 --
  WORKING_DIRECTORY "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '1.9.4'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-subbuild/jsoncpp-populate-prefix/src/jsoncpp-populate-stamp/jsoncpp-populate-gitinfo.txt"
    "/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-subbuild/jsoncpp-populate-prefix/src/jsoncpp-populate-stamp/jsoncpp-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/guilhem/delivery/Semestre5/B-CPP-500-LYN-5-2-rtype-erwann.laplante/build/_deps/jsoncpp-subbuild/jsoncpp-populate-prefix/src/jsoncpp-populate-stamp/jsoncpp-populate-gitclone-lastrun.txt'")
endif()

