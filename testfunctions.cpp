#include "scene_objects/sphere_object.h"
#include "scene_objects/plane_object.h"
#include "scene_objects/box_object.h"
#include "scene_objects/torus_object.h"

//Construction helper functions

//Add a point light source
void AddLight(scene& scene1, vector3 pos)
{
	scene1.add_light(new light(pos, rgbf(1, 1, 1), 1.0f));
}

//Add a sphere
void AddSphere(scene& scene1, vector3 pos, float r =0.5f, rgbf col =rgbf(0, 0, 1), bool ref =true)
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
	plane1->reflective = false;
	plane1->k_spec = 0; //No specular on floors
	scene1.add_object(plane1);
}

//Add a wall plane facing in a direction
void AddWall(scene& scene1, vector3 pos, vector3 dir, rgbf col =rgbf(0, 0.5, 0.5))
{
	plane_object* plane1 = new plane_object(pos, vector3(0, 0, 1), dir);
	plane1->natrual_colour = rgbf(0, 0.5, 0.5);
	plane1->reflective = false;
	plane1->k_spec = 0;
	scene1.add_object(plane1);
}

void SetCam(camera cam, vector3 pos, vector3 dir)
{
	cam.position = vector3(1, 0, 0);
	cam.direction = vector3(1, 0, 0);
	cam.up = vector3(0, 0, 1);
}

void TestFunction1(scene& scene1)
{

	AddSphere(scene1, vector3(3, 0, 0));
	
	AddWall(scene1, vector3(5, 0, -0.5), vector3(0, 1, 0));

	AddFloor(scene1, vector3(0, 0, -0.5));

	 
	box* box1 = new box(vector3(2, -2, 0), vector3(-0.5, -0.5, -0.5), vector3(0.5, 0.5, 0.5));
	box1->natrual_colour = rgbf(0, 0, 0.7);
	scene1.add_object(box1);

	//

	AddLight(scene1, vector3(-0.5, 0, 4));
	AddLight(scene1, vector3(0, 0, 4));
	AddLight(scene1, vector3(0.5, 0, 4));
	
}
