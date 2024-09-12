# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/ESP32/esp-idf/components/bootloader/subproject"
  "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader"
  "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader-prefix"
  "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader-prefix/tmp"
  "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader-prefix/src"
  "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/mende/Desktop/DSEI/Tarea_2/esp32_vs/Trabajo_PIC18_ESP32/DSEI_ESP32_PIC18F4550/ESP32/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
