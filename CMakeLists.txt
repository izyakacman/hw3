# CMakeList.txt: проект CMake для print_ip; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("print_ip" VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})

# Добавьте источник в исполняемый файл этого проекта.
add_executable (print_ip "main.cpp"   "tuple_utils.h"  )

set_target_properties("print_ip" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
