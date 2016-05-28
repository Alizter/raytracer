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
	window_width = 256,
	window_height = 256; //Default size
int size = window_width * window_height;

camera cam1(
	//vector3(2.9, 1.9, 0) , //Position
	vector3(0, 0, 0),	
	//!vector3(0, -1, 0), //Direction			
	!vector3(1, 0, 0),	
	!vector3(0, 0, 1), //Up vector
	window_width, window_height);

scene scene1;

RayTracer rt(4); //Initialise ray tracing depth

void colour(float x, float y, rgbf& out) 
{
	Ray ray = cam1.GetRay(x, y);
	out = rt.shootRay(scene1, ray, 0);

	//std::cout << x << ' ' << y << '\t' << out.r << ' ' << out.g << ' ' << out.b << std::endl;
}

rgbf* pixels = new rgbf[size];

void display()
{	
	//rgbf* pixels = new rgbf[size];

	for (int i = 0; i < size; i++)
		colour(i % window_width, i / window_width, pixels[i]);	

  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glDrawPixels(window_width,window_height,GL_RGB,GL_FLOAT,pixels);
 	glutSwapBuffers();

	//delete pixels;
}

bool fullScreen;


void DisplayText()
{
	
	std::ostringstream ss;
	ss << cam1.position << " " << cam1.direction;
	const char* cstr = ss.str().c_str();

	glutSetWindowTitle(cstr);
}

void Move(float inc, int dir)
{
	switch(dir)
	{
		case 0: cam1.position = cam1.position + cam1.direction * inc; break;
		case 1: cam1.position = cam1.position - !(cam1.direction ^ cam1.up) * inc; break;
		case 2: cam1.position = cam1.position - cam1.direction * inc; break;
		case 3: cam1.position = cam1.position + !(cam1.direction ^ cam1.up) * inc; break;
	}

	glutPostRedisplay();
	DisplayText();

}

void RotateCam(float angle)
{
	vector3 d = cam1.direction;
	
	cam1.direction.x = cos(angle) * d.x - sin(angle) * d.y;
	cam1.direction.y = sin(angle) * d.x + cos(angle) * d.y;	
	
	glutPostRedisplay();
	DisplayText();
}

void keyPress(unsigned char key, int x, int y)
{
	if (key == 27) exit(0);

	if (key == 'f')
	{
		if (fullScreen)
		{
			glutReshapeWindow(256, 256);
			glutPositionWindow(0,0);
		}
		else glutFullScreen();
		
		fullScreen = !fullScreen;
		glutPostRedisplay();
	}

	const float inc = 0.1;

	if (key == 'w') Move(inc, 0);
	if (key == 'd') Move(inc, 1);
	if (key == 's') Move(inc, 2);
	if (key == 'a') Move(inc, 3);

	if (key == 'q') RotateCam(-M_PI / 12);
	if (key == 'e') RotateCam(M_PI / 12);

}


//Resize window
void resize(int width, int height)
{
	window_width = width,
	window_height = height; 
	size = width * height;

	delete pixels;
	pixels = new rgbf[size];

	cam1.pixelwidth = width;
	cam1.pixelheight = height;
	
	glutPostRedisplay();
}


//Include the testing file with scene constructions
#include "testfunctions.cpp"

void InitialiseScene()
{
	SetCam(cam1, vector3(0, 0, 0), vector3(1, 0, 0));
	TestFunction1(scene1);
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
