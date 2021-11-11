# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Formative10")

# Include sub-projects.
set(EXECUTABLE_CUSTOM_NAME "japan")
add_subdirectory ("japan")

set(EXECUTABLE_CUSTOM_NAME "mondrian-picture")
add_subdirectory ("mondrianPicture")
