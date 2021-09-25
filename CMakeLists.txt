cmake_minimum_required(VERSION 3.19)
project(aphasia)

set(CMAKE_CXX_STANDARD 20)

SET(wxWidgets_USE_LIBS)
FIND_PACKAGE(wxWidgets REQUIRED)
INCLUDE("${wxWidgets_USE_FILE}")

add_executable(aphasia WIN32 main.cpp AphasiaFrame.cpp AphasiaFrame.h guistring.cpp guistring.h)

target_link_libraries(aphasia ${wxWidgets_LIBRARIES})
