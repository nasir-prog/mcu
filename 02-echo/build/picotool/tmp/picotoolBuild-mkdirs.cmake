# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/nasil/Repositories/pico/mcu/02-echo/build/_deps/picotool-src"
  "/home/nasil/Repositories/pico/mcu/02-echo/build/_deps/picotool-build"
  "/home/nasil/Repositories/pico/mcu/02-echo/build/_deps"
  "/home/nasil/Repositories/pico/mcu/02-echo/build/picotool/tmp"
  "/home/nasil/Repositories/pico/mcu/02-echo/build/picotool/src/picotoolBuild-stamp"
  "/home/nasil/Repositories/pico/mcu/02-echo/build/picotool/src"
  "/home/nasil/Repositories/pico/mcu/02-echo/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/nasil/Repositories/pico/mcu/02-echo/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/nasil/Repositories/pico/mcu/02-echo/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
