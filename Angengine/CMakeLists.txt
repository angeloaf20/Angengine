# CMakeList.txt : CMake project for Angengine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Angengine "Angengine.cpp" "main.cpp" "Window.cpp" "glad/glad.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Angengine PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
