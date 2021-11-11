# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

# Solution
project ("formative10Flags")

# Each sub-project
set(EXECUTABLE_CUSTOM_NAME "japan")
add_subdirectory ("japan")