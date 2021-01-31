// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#import "Fractals.h"
#include <math.h>

// Include GLEW
#include "dependente\glew\glew.h"

// Include GLFW
#include "dependente\glfw\glfw3.h"

// Include GLM
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"

using namespace std;
//variables
GLFWwindow* window;
const int width = 1024, height = 768;

// SCHIMBAT: Aici.
GLfloat Triangle[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.5f, 0.866f, 0.0f,
};
GLfloat Triangle2[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.5f, 0.866f, 0.0f,
};

// To-DO: Ex 2
unsigned int indicesTriangle[] = {
	0, 1, 2
};

GLfloat Square[] = {

	1.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	
};

unsigned int indicesSquare[] = {
	0, 1, 3,
	1, 2, 3
};

GLfloat RegHex[] = {
	-0.25f, 0.5f, 0.0f,    // left top
	0.25f, 0.5f, 0.0f,    // right top
	0.5f, 0.0f, 0.0f,    // right
	0.25f, -0.5f, 0.0f,    // right bottom (notice sign)
	-0.25f, -0.5f, 0.0f,    // left bottom
	-0.5f, 0.0f, 0.0f,     // left
	0.0f, 0.0f, 0.0f
};

unsigned int Hexagon[] = {
	0, 1, 6,
	1, 2, 6,
	2, 3, 6,
	3, 4, 6,
	4, 5, 6,
	5, 0, 6
};


// lighting
glm::vec3 lightPos(-3.0f, 0.0f, 3.0f);
glm::vec3 lightColor(1.0f);

void window_callback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}

void drawSubTriangle() {

	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTriangle), indicesTriangle, GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_LOOP, 0, 3);
}
void drawSubTriangle2() {

	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2), Triangle2, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTriangle), indicesTriangle, GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_LOOP, 0, 3);
}

void drawFractals(float x1, float x2, float x3, float y1, float y2, float y3)
{
	
	Triangle[0] = x1;
	Triangle[1] = y1;
	Triangle[3] = x2;
	Triangle[4] = y2;
	Triangle[6] = x3;
	Triangle[7] = y3;
	drawSubTriangle();

	auto len = glm::sqrt(glm::pow(x1 - x2, 2.0f) + glm::pow(y1 - y2, 2.0f));
	if (len < 0.1f) {
		return;
	}

	//ensure that the size of the triangles is not too small
	//distance formula is in the if condition
	GLfloat	xm = (x1 + x2) / 2;
	GLfloat	ym = (y1 + y2) / 2;
	GLfloat	xn = (x2 + x3) / 2;
	GLfloat	yn = (y2 + y3) / 2;
	GLfloat	xp = (x3 + x1) / 2;
	GLfloat	yp = (y3 + y1) / 2;

	
	drawFractals(x1, xm, xp, y1, ym, yp);
	drawFractals(x2, xn, xm, y2, yn, ym);
	drawFractals(x3, xp, xn, y3, yp, yn);
	drawFractals(xm, xn, xp, ym, yn, yp); //for sierpirnski just comment this line
}

void drawSierpinski(float x01, float x02, float x03, float y01, float y02, float y03)
{

	Triangle2[0] = x01;
	Triangle2[1] = y01;
	Triangle2[3] = x02;
	Triangle2[4] = y02;
	Triangle2[6] = x03;
	Triangle2[7] = y03;
	drawSubTriangle2();

	auto len = glm::sqrt(glm::pow(x01 - x02, 2.0f) + glm::pow(y01 - y02, 2.0f));
	if (len < 0.1f) {
		return;
	}

	//ensure that the size of the triangles is not too small
	//distance formula is in the if condition
	GLfloat	xm = (x01 + x02) / 2;
	GLfloat	ym = (y01 + y02) / 2;
	GLfloat	xn = (x02 + x03) / 2;
	GLfloat	yn = (y02 + y03) / 2;
	GLfloat	xp = (x03 + x01) / 2;
	GLfloat	yp = (y03 + y01) / 2;


	drawSierpinski(x01, xm, xp, y01, ym, yp);
	drawSierpinski(x02, xn, xm, y02, yn, ym);
	drawSierpinski(x03, xp, xn, y03, yp, yn);
	//drawFractals(xm, xn, xp, ym, yn, yp); //for sierpirnski just comment this line
}

void drawSubSquares()
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(Square), Square, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSquare), indicesSquare, GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void drawSquares(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4)
{

	Square[0] = x1;
	Square[1] = y1;
	Square[3] = x2;
	Square[4] = y2;
	Square[6] = x3;
	Square[7] = y3;
	Square[9] = x4;
	Square[10] = y4;
	drawSubSquares();
	
	if (std::abs(y2 - y1) < 0.1f) {
		return;
	}
	//std::cout << "a intrat in if";
	GLfloat xm = (x1 + x2) / 2;
	GLfloat	ym = (y1 + y2) / 2;
	GLfloat	xn = (x2 + x3) / 2;
	GLfloat	yn = (y2 + y3) / 2;
	GLfloat	xp = (x3 + x4) / 2;
	GLfloat	yp = (y3 + y4) / 2;
	GLfloat xo = (x1 + x4) / 2;
	GLfloat yo = (y1 + y4) / 2;
	GLfloat ox = (x3 + x2) / 2;
	GLfloat oy = (y2 + y1) / 2;

	drawSquares(x1, xm, ox , xo, y1, ym, oy, yo);

	drawSquares(xm, x2, xn, ox, ym, y2, yn, oy);

	drawSquares(ox, xn, x3, xp, oy, yn, y3, yp);

	drawSquares(xo, ox, xp, x4, yo, oy, yp, y4);
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Big HW Exercise 1", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	//specify the size of the rendering window
	glViewport(0, 0, width, height);

	// Dark grey background
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Create and compile our GLSL program from the shaders
	// More about this in the following labs
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	// Create some data for the vertices

	// A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects and is designed to store 
	// the information for a complete rendered object.
	GLuint vbo, vao, ibo, vbo1;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RegHex), RegHex, GL_STATIC_DRAW);
	
	


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Hexagon), Hexagon, GL_STATIC_DRAW);


	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	glUseProgram(programID);
	GLint uniform = glGetUniformLocation(programID, "ShapeColor");
	glUniform3f(uniform, 0.0f, 0.0f, 1.0f);
	glUseProgram(0);

	float rx = 0;
	float ry = 0;
	int stay = 0; //we initialize the variable stay as 0 and we will use it later as a conditon to be fulfilled in order to  draw  a figure
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// SCHIMBAT: Aici, pentru ca acum Triangle are mai multe casute.
	GLfloat x1, x2, x3, y1, y2, y3, x11, y11, x22, y22, x33, y33, x44, y44, x111, x222, x333, x444, x555, x666, x000 , y111, y222, y333, y444, y555, y666, y000 , x01, x02, x03, y01, y02, y03;
	x1 = Triangle[0];
	y1 = Triangle[1];
	x2 = Triangle[3];
	y2 = Triangle[4];
	x3 = Triangle[6];
	y3 = Triangle[7];
	std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " ";
	x01 = Triangle2[0];
	y01 = Triangle2[1];
	x02 = Triangle2[3];
	y02 = Triangle2[4];
	x03 = Triangle2[6];
	y03 = Triangle2[7];
	std::cout << x01 << " " << y01 << " " << x02 << " " << y02 << " " << x03 << " " << y03 << " ";
	x11 = Square[0]  ;
	y11 = Square[1];
	x22 = Square[3];
	y22 = Square[4];
	x33 = Square[6];
	y33 = Square[7];
	x44 = Square[9];
	y44 = Square[10];
	std::cout<<endl;
	std::cout<< x11 << " " << y11 << " " << x22 << " " << y22 << " " << x33 << " " << y33 << " " << x44 << " "<< y44 << " ";
	x111 = RegHex[0];
	y111 = RegHex[1];
	x222 = RegHex[3];
	y222 = RegHex[4];
	x333 = RegHex[6];
	y333 = RegHex[7];
	x444 = RegHex[9];
	y444 = RegHex[10];
	x555 = RegHex[12];
	y555 = RegHex[13];
	x666 = RegHex[15];
	y666 = RegHex[16];
	x000 = RegHex[17];
	y000 = RegHex[18];
	std::cout << endl;
	std::cout << x111 << " " << y111 << " " << x222 << " " << y222 << " " << x333 << " " << y333 << " " << x444 << " " << y444 << " "<< x555 << " "<< y555 << " " << x666 << " " << y666 << " "<< x000 << " "<< y000<< " ";
	int i = 0;
	int cont = 0;
	// Check if the window was closed
	while (!glfwWindowShouldClose(window))
	{
		// Swap buffers
		glfwSwapBuffers(window);

		// Check for events
		glfwPollEvents();
		//enable depth buffer
		glEnable(GL_DEPTH_TEST);


		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		//Implement the ESC button to close
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			//glfwTerminate();
			//return -1;
			glfwSetWindowShouldClose(window, true);
		};

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 10000.0f);

		//Adding view for MVP
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -20.0f, 200.0f), glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));


		//Model
		glm::mat4 model;

		//Button to display the HEXAGON
		int cont3 = 0;
		if (glfwGetKey(window, GLFW_KEY_H)) {
			stay = 1; //we make stay variable equal to 1 always when we press H
			cont3 = 1;
			glBufferData(GL_ARRAY_BUFFER, sizeof(RegHex), RegHex, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Hexagon), Hexagon, GL_STATIC_DRAW);

		}
		if (stay == 1) // draws the figure
		{
			if (cont3 == 1) {
				glDrawArrays(GL_LINE_LOOP, 0, 6);
				cont3 = 2;
			}
			else
			{
				cont3 = 0;
				drawFractals(x111, x222, x000, y111, y222, y000);
				drawFractals(x222, x333, x000, y222, y333, y000);
				drawFractals(x333, x444, x000, y333, y444, y000);
				drawFractals(x444, x555, x000, y444, y555, y000);
				drawFractals(x555, x666, x000, y555, y666, y000);
				drawFractals(x666, x111, x000, y666, y111, y000);

			}
		

		}
		//Button to display the SQUARE
		int cont2 = 0;
		if (glfwGetKey(window, GLFW_KEY_S)) {
			cont2 = 1;
			stay = 2; //we make stay variable equal to 2 always when we press S
			glBufferData(GL_ARRAY_BUFFER, sizeof(Square), Square, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSquare), indicesSquare, GL_STATIC_DRAW);
		}
		if (stay == 2) // draws the figure
		{
			if (cont2 == 1) {
				glDrawArrays(GL_LINE_LOOP, 0, 4);
				cont2 = 2;
			}
			else
			{
				cont2 = 0;
				drawSquares(x11, x22, x33, x44, y11, y22, y33, y44);

			}

			
			//glDrawArrays(GL_LINE_LOOP, 0, 4);
		}

		//Button to display the TRIANGLE
		if (glfwGetKey(window, GLFW_KEY_T)) {
			cont++;
			stay = 3; //we make stay variable equal to 3 always when we press T
			glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTriangle), indicesTriangle, GL_STATIC_DRAW);
		}
		if (stay == 3) // draws the figure
		{
			
			if (cont == 1) {
				glDrawArrays(GL_LINE_LOOP, 0, 3);
				cont=2;
			}
			else
			{
				cont = 0;
				drawFractals(x1, x2, x3, y1, y2, y3);
				
			}
			
			

		}

		//Button to display Sierpinski Triangle
		int cont4 = 0;
		if (glfwGetKey(window, GLFW_KEY_Y)) {
			cont4++;
			stay = 4; //we make stay variable equal to 3 always when we press T
			glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTriangle), indicesTriangle, GL_STATIC_DRAW);
		}
		if (stay == 4) // draws the figure
		{
			
			if (cont4 == 1) {
				glDrawArrays(GL_LINE_LOOP, 0, 3);
				cont4 = 2;
			}
			else
			{
				cont = 0;
				drawSierpinski (x01, x02, x03, y01, y02, y03);

			}



		}

		if (glfwGetKey(window, GLFW_KEY_O)) {
			stay = 0; // equal to 0 always when we press O so it will clear the screen, avoiding to use glClear again
		};


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(rx, ry, 1.0));

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			glUseProgram(programID);
			GLint uniform = glGetUniformLocation(programID, "ShapeColor");
			glUniform3f(uniform, 1.0f, 0.0f, 1.0f);
			glUseProgram(0);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			model = glm::rotate(model, (float)glfwGetTime() * 100, glm::vec3(0.0f, 0.0f, 1.0f));

		}

		glm::mat4 MVP = projection * view * model;

		unsigned int transformLoc = glGetUniformLocation(programID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(MVP));




		//bind VAO
		glBindVertexArray(vao);


	}

	// Cleanup VBO
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}