

project(SDL_OpenGLprogram)
cmake_minimum_required(VERSION 3.0)

set(project 3Dviewer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Listing Required Includes:
set(INCLUDES
	# DISPLAY HEADERS
	includes/display/display.cpp
	includes/display/display.h

	#SHADER HEADERS
	includes/shader/shader.cpp
	includes/shader/shader.h

	#MESH HEADERS
	includes/mesh/mesh.h
	includes/mesh/mesh.cpp

	#IMAGE HANDLING
	includes/stb_image/stb_image.c
	includes/stb_image/stb_image.h

	#TEXTURE HEADERS
	includes/texture/texture.h
	includes/texture/texture.cpp

	#TRANSFORM HEADERS
	includes/transform/transform.h

	#CAMERA HEADERS (PERSPECTIVE)
	includes/camera/camera.h

	#CAMERA HEADERS (ORTHOGRAPHIC)
	includes/cameraOrtho/cameraOrtho.h	

	#MODEL HEADERS
	includes/model/model.h
	includes/model/model.cpp

	#VERTEX HEADERS
	includes/vertex/vertex.h

)

# Finding all required Packages:
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)

################ Requreided to Compile both on Mac and Ubuntu:
IF(UNIX)
	IF(APPLE)
		FIND_PACKAGE(GLM REQUIRED)
	ELSE()
		# Specific for my ubuntu system:
		set(GLM_INCLUDE_DIR ${GLM_INCLUDE_DIR} /usr/local/include/glm/)
	ENDIF()
ELSE()
	# Assumeing windows has a find package (not sure though)
	FIND_PACKAGE(GLM REQUIRED)
ENDIF()
################

################ Including all relevent Directory paths:
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIR})
INCLUDE_DIRECTORIES(includes/)

################ Creating Project:
set(SOURCES main/main.cpp ${INCLUDES})
add_executable(${project} ${SOURCES})
target_link_libraries(${project} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${GLEW_LIBRARIES} ${GLM_LIBRARIES})
