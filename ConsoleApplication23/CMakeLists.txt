cmake_minimum_required(VERSION 3.12.2)

project(CodeGenerator)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(CodeGenerator
  common.h
  File_IMA.c
  File_IMA.h
  generator.c
  generator.h
  Intel.c
  Intel.h
  Loader.c
  Loader.h
  main.c
  Utils.c
  Utils.h
)
# Preprocessor definitions
target_compile_definitions(CodeGenerator PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;_CRT_SECURE_NO_WARNINGS;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;NDEBUG;_CONSOLE>
)

# SDL check
target_compile_options(CodeGenerator PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(CodeGenerator PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  set_property(SOURCE generator.c Loader.c main.c Utils.c Intel.c File_IMA.c
    APPEND_STRING PROPERTY COMPILE_FLAGS
    "$<$<CONFIG:Release>:/Yu"pch.h">")
endif ()
