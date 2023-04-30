project(OpenGL_beginner)
find_package(OpenGL REQUIRED)
include_directories({$OPENGL_INCLUDE_DIR})
message(STATUS "Found OpenGL at ${OPENGL_LIBRARIES}, ${OPENGL_INCLUDE_DIR}")

find_package(GLUT REQUIRED)
include_directories({$GLUT_INCLUDE_DIR})
message(STATUS "Found GLUT at include ${GLUT_INCLUDE_DIR}, ${GLUT_LIBRARIES}")

add_executable(main src/main.cpp)
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
