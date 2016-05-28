#include "scene_objects/sphere_object.h"
#include "scene_objects/plane_object.h"
#include "scene_objects/box_object.h"
#include "scene_objects/torus_object.h"
#include "scene_objects/triangle_object.h"
#include "scene_objects/mesh.h"


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

void AddTriangleToMesh(mesh* m, vector3 v1, vector3 v2, vector3 v3)
{
	triangle_object* tri = new triangle_object(v1, v1 - v1, v2 - v1, v3 - v1);
	tri->natrual_colour = rgbf(1, 1, 1);
	m->add_triangle(tri);
}

void IcoSphere(scene& scene1, vector3 pos)
{
	vector3* verts = new vector3[12];

	float t = (1+sqrt(5))/2;
	
	verts[0] = pos + vector3(-1, t, 0);
	verts[1] = pos + vector3(1, t, 0);
	verts[2] = pos + vector3(-1, -t, 0);
	verts[3] = pos + vector3(1, -t, 0);

	verts[4] = pos + vector3(0, -1, t);
	verts[5] = pos + vector3(0, 1, t);
	verts[6] = pos + vector3(0, -1, -t);
	verts[7] = pos + vector3(0, 1, -t);

	verts[8] = pos + vector3(t, 0, -1);
	verts[9] = pos + vector3(t, 0, 1);
	verts[10] = pos + vector3(-t, 0, -1);
	verts[11] = pos + vector3(-t, 0, 1);

	mesh* m1 = new mesh(pos, vector3(-t, -t, -t), vector3(t, t, t));
	
	AddTriangleToMesh(m1, verts[0], verts[11], verts[5]);
	AddTriangleToMesh(m1, verts[0], verts[6], verts[1]);
	AddTriangleToMesh(m1, verts[0], verts[1], verts[7]);
	AddTriangleToMesh(m1, verts[0], verts[7], verts[10]);
	AddTriangleToMesh(m1, verts[0], verts[10], verts[11]);

	AddTriangleToMesh(m1, verts[1], verts[5], verts[9]);
	AddTriangleToMesh(m1, verts[5], verts[11], verts[4]);
	AddTriangleToMesh(m1, verts[11], verts[10], verts[2]);
	AddTriangleToMesh(m1, verts[10], verts[7], verts[6]);
	AddTriangleToMesh(m1, verts[7], verts[1], verts[8]);

	AddTriangleToMesh(m1, verts[3], verts[9], verts[4]);
	AddTriangleToMesh(m1, verts[3], verts[4], verts[2]);
	AddTriangleToMesh(m1, verts[3], verts[2], verts[6]);
	AddTriangleToMesh(m1, verts[3], verts[6], verts[8]);
	AddTriangleToMesh(m1, verts[3], verts[8], verts[9]);

	AddTriangleToMesh(m1, verts[4], verts[9], verts[5]);
	AddTriangleToMesh(m1, verts[2], verts[4], verts[11]);
	AddTriangleToMesh(m1, verts[6], verts[2], verts[10]);
	AddTriangleToMesh(m1, verts[8], verts[6], verts[7]);
	AddTriangleToMesh(m1, verts[9], verts[8], verts[1]);

	scene1.add_object(m1);
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
	
	AddWall(scene1, vector3(10, 0, -0.5), vector3(0, 1, 0));

	AddFloor(scene1, vector3(0, 0, -0.5));

	//AddBox(scene1, vector3(2, -2, 0), 0.5, rgbf(2, 0, 1), false);

	AddLightBall(scene1, vector3(4, 0, 2), 5, 10);

	//AddLight(scene1, vector3(0, 0, 2));
	//AddLight(scene1, vector3(5, 3, 2));
	//AddLight(scene1, vector3(-5, 3, 2));

	IcoSphere(scene1, vector3(4, 0, 2));

	torus_object* tor1 = new torus_object(0.5,1,vector3(2,0,0));
	//scene1.add_object(tor1);


	
	
}
