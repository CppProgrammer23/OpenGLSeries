#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>	/*Send stuff to the shader*/
#include <iostream>
#include <string>


void resize_window_callback(GLFWwindow* window, int fbw, int fbh);
void Close_Window_W_Esc(GLFWwindow* window);
bool create_shader(GLuint& program);

struct Vertex		/*Sizeof(Vertex)=32 (4 Bytes*8) 3+3+2*/
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textcoord;
};
