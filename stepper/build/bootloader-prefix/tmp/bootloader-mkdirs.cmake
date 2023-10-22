# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Lincoln/esp/esp-idf/components/bootloader/subproject"
  "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader"
  "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader-prefix"
  "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader-prefix/tmp"
  "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader-prefix/src"
  "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Lincoln/Documents/GitHub/Projeto/stepper/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
