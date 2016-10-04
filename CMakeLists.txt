cmake_minimum_required (VERSION 2.6)
project (Robot)

find_package (OpenCV REQUIRED)

set (SOURCES
    main.cpp
    Robot.cpp
    serialib.cpp
    )

add_executable (Robot ${SOURCES})
target_link_libraries (Robot ${OpenCV_LIBS})
