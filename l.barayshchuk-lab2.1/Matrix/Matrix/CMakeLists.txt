# CMakeList.txt: проект CMake для Matrix; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Matrix "Main.cpp" "Matrix.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Matrix PROPERTY CXX_STANDARD 20)
endif()



# TODO: Добавьте тесты и целевые объекты, если это необходимо.

if(MSVC)
  target_compile_options(Matrix PRIVATE /W4 /WX)
else()
  target_compile_options(Matrix PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()