# CMakeList.txt: проект CMake для print_ip; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("print_ip")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (print_ip "main.cpp"   "tuple_utils.h"  )

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
