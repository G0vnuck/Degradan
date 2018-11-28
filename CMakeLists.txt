cmake_minimum_required(VERSION 3.12)
project(Degradan++)

set(CMAKE_CXX_STANDARD 17)
add_executable(Degradan++ main.cpp )

set(GLUT_INCLUDE_DIR "C:/Users/web/Desktop/glut-3.7.6-bin/")

find_package(OPENGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(GL)
include_directories(GLUT)

target_link_libraries(Degradan++ ${OPENGL_LIBRARIES} "C:\\Users\\artyo\\Desktop\\Cl_projects\\Degradan++\\GLUT\\GLAUX.LIB" "freeglut" "libSOIL.a" -lOpenGL32 -lglu32 -LSOIL -Lfreeglut -static-libstdc++ -static-libgcc)



