#include "raytracer.cpp"

#include <GL/gl.h>
#include <GL/glut.h>

#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<time.h>
#include<string>
#include<sstream>



//To compile
//g++ viewer.cpp -o raytest -lGL -lGLU -lglut -std=gnu++0x
//

unsigned int 
	window_width = 512,
	window_height = 512; //Default size
int size = window_width * window_height;

camera cam1(
	vector3(0, -1, 0) , //Position
	!vector3(1, 0.5, 0), //Direction			
	!vector3(0, 0, 1), //Up vector
	window_width, window_height);
//
// a= 1/3
//
//
scene scene1(cam1);

RayTracer rt(3);

void colour(float x, float y, rgbf& out) 
{
	Ray ray = cam1.GetRay(x, y);
	out = rt.shootRay(scene1, ray, 0);
}

void display()
{	
	rgbf* pixels = new rgbf[size];

	for (int i = 0; i < size; i++)
		colour(i % window_width, i / window_width, pixels[i]);	

  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glDrawPixels(window_width,window_height,GL_RGB,GL_FLOAT,pixels);
 	glutSwapBuffers();
}

bool fullScreen;

void MoveLight(vector3 p)
{
	scene1.lights[0]->position = scene1.lights[0]->position + p;
	glutPostRedisplay();

	std::ostringstream ss;
	ss << scene1.lights[0]->position;
	const char* cstr = ss.str().c_str();

	glutSetWindowTitle(cstr);
}

void keyPress(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);

	if (key == 'f')
	{
		if (fullScreen)
		{
			glutReshapeWindow(512, 512);
			glutPositionWindow(0,0);
		}
		else
		{
			glutFullScreen();
		}
		
		fullScreen = !fullScreen;
		glutPostRedisplay();
	}

	const float inc = 0.1;

	if (key == 'w')
	{
		MoveLight(vector3(inc, 0, 0));
	}
	
	if (key == 's')
	{
		MoveLight(vector3(-inc, 0, 0));
	}

	if (key == 'q')
	{
		MoveLight(vector3(0, 0, inc));
	}

	if (key == 'e')
	{
		MoveLight(vector3(0, 0, -inc));
	}

	if (key == 'a')
	{
		MoveLight(vector3(0, -inc, 0));
	}

	if (key == 'd')
	{
		MoveLight(vector3(0, inc, 0));
	}

}


//Resize window
void resize(int width, int height)
{
	window_width = width,
	window_height = height; 
	size = window_width * window_height;

	scene1.cam = camera(
		scene1.cam.position, //Position
		scene1.cam.direction, //Direction			
		scene1.cam.up, //Up vector
		window_width, window_height);

	glutPostRedisplay();
}

#include "scene_objects/sphere_object.h"
#include "scene_objects/plane_object.h"
#include "scene_objects/box_object.h"

void InitialiseScene()
{
	sphere_object* sphere1 = new sphere_object(0.5f, vector3(2, 0, 0));
	sphere1->natrual_colour = rgbf(1, 0, 0);
	//sphere1->transparent = true;
	//scene1.add_object(sphere1);

	sphere_object* sphere2 = new sphere_object(0.5f, vector3(2.5, 0.5, 0));
	sphere2->natrual_colour = rgbf(0, 0, 1);
	//scene1.add_object(sphere2);

	plane_object* plane1 = new plane_object(vector3(0, 0, -0.5), vector3(1, 0, 0), vector3(0, 1, 0));
	plane1->natrual_colour = rgbf(0, 1, 0);
	scene1.add_object(plane1);
	 
	box* box1 = new box(vector3(2, 0, 0), vector3(-0.5, -0.5, -0.5), vector3(0.5, 0.5, 0.5));
	box1->natrual_colour = rgbf(0, 0, 1);
	scene1.add_object(box1);
	
	scene1.add_light(new light(vector3(1, 1, 1), rgbf(1, 1, 1), 1.0f));
	
	//scene1.add_light(new light(vector3(1, -1, 1), rgbf(1, 1, 1), 1.0f));
}

int main(int argc, char** argv) 
{
	//std::cout << cam1.direction * cam1.up << std::endl;

	InitialiseScene();
  	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
  	glutCreateWindow("Ray Tracing Test");
	
	//glutFullScreen();
	//fullScreen = true;

  	glutDisplayFunc(display);
	glutKeyboardFunc(keyPress);
	//glutIdleFunc(idle);
	glutReshapeFunc(resize);
 	glutMainLoop(); //Start loop
}
