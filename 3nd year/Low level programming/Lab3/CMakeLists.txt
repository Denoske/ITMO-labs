cmake_minimum_required(VERSION 3.27)
project(untitled2 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled2 main.c
        ../../../../basic_file_manager.h
        ../../../../basic_file_manager.h
        server/include/data/test_data.h
        server/include/generator/empty_generator.h
        server/include/interface/basic_crud.h
        server/include/interface/basic_crud.h
        server/include/interface/configuration.h)
