cmake_minimum_required(VERSION 3.12.2)

project(One_File_Codegenerator)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(One_File_Codegenerator
  One_File_Codegenerator.c
)
# Preprocessor definitions
target_compile_definitions(One_File_Codegenerator PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;NDEBUG;_CONSOLE>
)

# SDL check
target_compile_options(One_File_Codegenerator PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(One_File_Codegenerator PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  set_property(SOURCE One_File_Codegenerator.c
    APPEND_STRING PROPERTY COMPILE_FLAGS
    "$<$<CONFIG:Release>:/Yu"pch.h">")
endif ()
