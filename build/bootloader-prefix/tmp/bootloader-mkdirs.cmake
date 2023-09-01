# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/thego/esp/esp-idf/components/bootloader/subproject"
  "D:/personal/TGH_GUI/TGH-GUI/ESP32/TGH_GUI/build/bootloader"
  "D:/personal/TGH_GUI/TGH-GUI/ESP32/TGH_GUI/build/bootloader-prefix"
  "D:/personal/TGH_GUI/TGH-GUI/ESP32/TGH_GUI/build/bootloader-prefix/tmp"
  "D:/personal/TGH_GUI/TGH-GUI/ESP32/TGH_GUI/build/bootloader-prefix/src/bootloader-stamp"
  "D:/personal/TGH_GUI/TGH-GUI/ESP32/TGH_GUI/build/bootloader-prefix/src"
  "D:/personal/TGH_GUI/TGH-GUI/ESP32/TGH_GUI/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/personal/TGH_GUI/TGH-GUI/ESP32/TGH_GUI/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
