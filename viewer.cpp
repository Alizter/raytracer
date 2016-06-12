#include "raytracer.cpp"

#include <GL/gl.h>
#include <GL/glut.h>

#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
//#include<time.h>
#include<string>
#include<sstream>



//To compile
//g++ viewer.cpp -o test -lGL -lGLU -lglut
//

unsigned int 
	window_width = 100,
	window_height = 100; //Default size
int size = window_width * window_height;

camera cam1;
scene scene1;
RayTracer rt(4); //Initialise ray tracing depth
float gamCor = 1; //Gamma correction //2.8 is PAL

void colour(float x, float y, rgbf& out) 
{
	Ray ray = cam1.GetRay(x, y);
	//out = rt.shootRay(scene1, ray, 0);
	out = rt.shootRay(scene1, ray, 0).gc(gamCor); //Gamma correction

}

rgbf* pixels = new rgbf[size]; //

#include <chrono>
#include <thread>

void display()
{	
	auto t1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < size; i++)
	{
		colour(i % window_width, i / window_width, pixels[i]);
		//printf("\r%3.2f%%", (float)i / size * 100);
	}

	auto t2 = std::chrono::high_resolution_clock::now();

	float time = std::chrono::duration_cast<std::chrono
			::milliseconds>(t2 - t1).count();

	//printf("\n%d\n", (int)time);

  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glDrawPixels(window_width,window_height,GL_RGB,GL_FLOAT,pixels);
 	glutSwapBuffers();
}

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
	
	cam1.setDirection(vector3(cos(angle) * d.x - sin(angle) * d.y, sin(angle) * d.x + cos(angle) * d.y, 0));
	
	glutPostRedisplay();
	DisplayText();
}


bool fullScreen; //Full screen flag

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

	cam1.setPixelSize(window_width, window_height);
	
	glutPostRedisplay();
}


//Include the testing file with scene constructions
#include "testfunctions.cpp"

void InitialiseScene()
{
	cam1.position = vector3(0, 0, 0);
	cam1.setPixelSize(window_width, window_height);
	cam1.setDirection(vector3(1, 0, 0));

	TestFunction1(scene1);
}

//Command line arguments, argc is number of elements
//argv are the arguments
int main(int argc, char* argv[]) 
{
	if (argc > 2) //There are 3 arguments including name
	{ 
		int w = atoi(argv[1]), h = atoi(argv[2]); //Get integer arguments
		
		window_width = w ? w : 256; //Make sure integer is valide
		window_height = h ? h : 256; //and assign accordingly
		cam1.setPixelSize(window_width, window_height);
	}

	//Set up scenery
	InitialiseScene();
	//initialise glut - not sure how to use cmd line args here
  	glutInit(&argc, argv);
	//Set up display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//Initialise window size
	glutInitWindowSize(window_width, window_height);
	//Create window
  	glutCreateWindow("Ray Tracing Test");
	//Rendering function
  	glutDisplayFunc(display);
	//Key press controls
	glutKeyboardFunc(keyPress);
	//Resize function
	glutReshapeFunc(resize);
	//Start loop
 	glutMainLoop();
}
