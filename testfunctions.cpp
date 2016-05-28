#include "scene_objects/sphere_object.h"
#include "scene_objects/plane_object.h"
#include "scene_objects/box_object.h"
#include "scene_objects/torus_object.h"
#include "scene_objects/triangle_object.h"


//Construction helper functions

//Add a point light source
void AddLight(scene& scene1, vector3 pos)
{
	scene1.add_light(new light(pos, rgbf(1, 1, 1), 1.0f));
}

void AddLightBall(scene& scene1, vector3 pos, int number, float r)
{
	for (int i = 0; i < number; i++)
	{
		float t = 2 * M_PI / number * i;
		light* lig = new light(pos + vector3(r * cos(t), r * sin(t), 0), rgbf(1, 1, 1), 1.9 / number);
		scene1.add_light(lig);
	}
}

//Add a sphere
void AddSphere(scene& scene1, vector3 pos, float r =0.5f, rgbf col =rgbf(0, 0, 1), bool ref =false)
{
	sphere_object* sphere = new sphere_object(r, pos);
	sphere->natrual_colour = col;
	sphere->reflective = ref;
	scene1.add_object(sphere);
} 


//Add a floor
void AddFloor(scene& scene1, vector3 pos, rgbf col =rgbf(0, 1, 0))
{
	plane_object* plane1 = new plane_object(pos, vector3(1, 0, 0), vector3(0, 1, 0));
	plane1->natrual_colour = col;
	plane1->k_spec = 0; //No specular on floors
	scene1.add_object(plane1);
}

//Add a wall plane facing in a direction
void AddWall(scene& scene1, vector3 pos, vector3 dir, rgbf col =rgbf(0, 0.5, 0.5))
{
	plane_object* plane1 = new plane_object(pos, vector3(0, 0, 1), dir);
	plane1->natrual_colour = rgbf(0, 0.5, 0.5);
	plane1->k_spec = 0;
	scene1.add_object(plane1);
}

void AddBox(scene& scene1, vector3 pos, float r =0.5f, rgbf col =rgbf(0, 0, 1), bool ref =false)
{
	box* box1 = new box(pos, vector3(-r, -r, -r), vector3(r, r, r));
	box1->natrual_colour = col;
	box1->reflective = ref;
	scene1.add_object(box1);
}

void AddTriangle(scene& scene1, vector3 v1, vector3 v2, vector3 v3)
{
	triangle_object* tri = new triangle_object(v1, v1 - v1, v2 - v1, v3 - v1);
	tri->natrual_colour = rgbf(1, 1, 1);
	scene1.add_object(tri);
}

void SetCam(camera cam, vector3 pos, vector3 dir)
{
	cam.position = vector3(1, 0, 0);
	cam.direction = vector3(1, 0, 0);
	cam.up = vector3(0, 0, 1);
}

void TestFunction1(scene& scene1)
{

	//AddSphere(scene1, vector3(1.5, 0, 0), 0.5, rgbf(0, 0, 1), false);
	
	AddWall(scene1, vector3(4, 0, -0.5), vector3(0, 1, 0));

	AddFloor(scene1, vector3(0, 0, -0.5));

	//AddBox(scene1, vector3(2, -2, 0), 0.5, rgbf(2, 0, 1), false);

	//

	AddLight(scene1, vector3(0, 0, 2));


	torus_object* tor1 = new torus_object(0.5,1,vector3(2,0,0));
	//scene1.add_object(tor1);


	
	
}
