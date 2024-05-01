# CMakeList.txt: проект CMake для Lab1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.11)

project(4_sem_Lab3 CXX)

set(CMAKE_CXX_STANDARD 23)

# Специфичные настройки для компилятора Visual Studio
if(MSVC)
    # Включаем высокий уровень предупреждений
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Добавьте источник в исполняемый файл этого проекта.
#add_executable (lab3 "4_sem_Lab3.cpp" "libraries/4_sem_Lab3_lib.h" "libraries/4_sem_Lab3_lib.cc")
#target_link_libraries(lab3 4_sem_Lab3)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.


# Добавьте источник в исполняемый файл этого проекта.
add_executable (lab3 "4_sem_Lab3.cpp" "libraries/4_sem_Lab3_lib.h")

# Связываем исполняемый файл с созданной библиотекой
target_link_libraries(lab3 PUBLIC 4_sem_Lab3_lib)
