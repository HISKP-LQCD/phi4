cmake_minimum_required(VERSION 3.0)

project(phi4 CXX C)

add_executable(phi4
    lattice.cpp
    metropolis.cpp
    main.cpp
    measurement.cpp
    )
