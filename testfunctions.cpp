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
		light* lig = new light(pos + vector3(r * cos(t), r * sin(t), 0), rgbf(1, 1, 1) , 1.0 / number);
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
	plane_object* plane1 = new plane_object(pos, vector3(0, 0, 1));
	plane1->natrual_colour = col;
	plane1->k_spec = 0; //No specular on floors
	scene1.add_object(plane1);
}

//Add a ceiling
void AddCeiling(scene& scene1, vector3 pos, rgbf col =rgbf(0, 1, 0))
{
	plane_object* plane1 = new plane_object(pos, vector3(0, 0, -1));
	plane1->natrual_colour = col;
	plane1->k_spec = 0; //No specular on floors
	scene1.add_object(plane1);
}

//Add a wall plane facing in a direction
void AddWall(scene& scene1, vector3 pos, vector3 dir, rgbf col =rgbf(0, 0.5, 0.5))
{
	plane_object* plane1 = new plane_object(pos, vector3(0, 0, 1)^dir);
	plane1->natrual_colour = col;
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

//Add triangle to mesh with normal
void ATTMWN(mesh* m, vector3 v1, vector3 v2, vector3 v3, vector3 n)
{
	triangle_object* tri = new triangle_object(v1, v1 - v1, v2 - v1, v3 - v1, n);
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

#include<string>
#include<vector>
#include<fstream>
#include<iostream>

//String splitter http://stackoverflow.com/a/236803
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
	std::stringstream ss(s);
	std::string item;
	
  	while (std::getline(ss, item, delim)) 
	{
        	elems.push_back(item);
	}
	
	return elems;
}

//Reads a mesh from a .obj file centered at 0,0,0
mesh* ReadMesh(std::string fileName, vector3 pos)
{
	mesh* m = new mesh(
			pos, 
			vector3(-1.1, -1.1, -1.1), 
			vector3(1.1, 1.1, 1.1));

	std::vector<vector3> verts;
	std::vector<vector3> norms;
	
	//Reading obj file
	std::ifstream myfile(fileName.c_str());
	std::string line;

	while (std::getline(myfile, line))
	{
		std::vector<std::string> elems;
		split(line, ' ', elems);

		if (elems[0] == "v")
		{
			vector3 vert = pos + vector3(
				   atof(elems[3].c_str()),
				   atof(elems[1].c_str()),
				   atof(elems[2].c_str()));
			//std::cout << vert << std::endl;
			
			verts.push_back(vert);
		}
		else if (elems[0] == "vn")
		{
			vector3 norm = vector3(
				   atof(elems[1].c_str()),
				   atof(elems[2].c_str()),
				   atof(elems[3].c_str()));		

			norms.push_back(norm);
		}
		else if (elems[0] == "f")
		{
			std::vector<std::string> vn1;
			std::vector<std::string> vn2;
			std::vector<std::string> vn3;
			
			split(elems[1], '/', vn1);
			split(elems[2], '/', vn2);
			split(elems[3], '/', vn3);
			
			
			vector3 v1 = verts[atoi(vn1[0].c_str()) - 1];
			vector3 v2 = verts[atoi(vn2[0].c_str()) - 1];
			vector3 v3 = verts[atoi(vn3[0].c_str()) - 1];
			vector3 n = -!(norms[atoi(vn1[2].c_str()) - 1]
				+norms[atoi(vn2[2].c_str()) - 1]
				+norms[atoi(vn3[2].c_str()) - 1]);


			//std::cout <<  verts[atoi(vn1[0].c_str())] << std::endl;

			ATTMWN(m, v1, v2, v3, n);
				
		}
	}

	
	return m;
	
}


void TestFunction1(scene& scene1)
{

	AddSphere(scene1, vector3(1.5, -1.5, 0), 0.5, rgbf(0, 0, 1), false);
	//AddSphere(scene1, vector3(1, 1, 0), 0.5, rgbf(0, 1, 1), true);
		
	sphere_object* s1 = new sphere_object(0.5, vector3(1.5, -1, 0));
	s1->natrual_colour = rgbf(0, 0, 0);
	s1->reflective = true;
	s1->I_refl = 1;
	s1->k_spec = 1;	
	s1->ambient_colour = rgbf(0, 0, 0);
	s1->shininess = 100;
	//scene1.add_object(s1);

	sphere_object* s2 = new sphere_object(0.5, vector3(1.5, 1, 0));
	s2->transparent = true;
	s2->transparency = 0.9;
	s2->refindex = 0.9;
	scene1.add_object(s2);

	rgbf red(1, 0, 0);
	rgbf green(0, 1, 0);
	rgbf blue(0, 0, 1);
	rgbf yellow = red + green;
	rgbf magenta = red + blue;
	rgbf cyan = green + blue;


	AddWall(scene1, vector3(3, 0, -0.5), vector3(0, 1, 0), green * 0.7);
	AddWall(scene1, vector3(0, 3, -0.5), vector3(-1, 0, 0), red* 0.7);
	AddWall(scene1, vector3(-3, 0, -0.5), vector3(0, -1, 0), blue* 0.7);
	AddWall(scene1, vector3(0, -3, -0.5), vector3(1, 0, 0), yellow* 0.7);
	

	AddCeiling(scene1, vector3(0, 0, +3.5), magenta * 0.7);
	AddFloor(scene1, vector3(0, 0, -0.5), cyan * 0.7);

	//AddBox(scene1, vector3(1, -0.5, -0.3), 0.2, rgbf(1, 0, 1), true);

	box* box1 = new box(vector3(1, -0.5, 0), vector3(-0.2, -0.2, -0.2), vector3(0.2, 0.2, 0.2));
	box1->natrual_colour = rgbf(0, 0, 0);
	box1->reflective = false;
	box1->transparent = true;
	box1->transparency = 1;
	box1->I_refr = 1;
	box1->refindex = 2;
	scene1.add_object(box1);

	//AddLightBall(scene1, vector3(-0.8, 0, 3), 3, 0.1);

	AddLight(scene1, vector3(-1.5, 1.5, 3));
	//AddLight(scene1, vector3(2, 0, 4));
	//AddLight(scene1, vector3(-5, 3, 2));

	//IcoSphere(scene1, vector3(4, 0, 2));

	torus_object* tor1 = new torus_object(0.1,0.5,vector3(1,0,-0.5));
	tor1->natrual_colour = rgbf(1, 0, 0);	
	//tor1->ambient_colour = rgbf(0, 0, 0.5);
	//scene1.add_object(tor1);

	mesh* m1 = ReadMesh("teapot.obj", vector3(1, -0.25, -0.5));
	m1->natrual_colour = rgbf(0, 0, 0);
	m1->reflective = false;
	m1->transparent = true;
	m1->transparency = 1;
	m1->I_refr = 1;

	//scene1.add_object(m1);
	
	
}

//TODO
//Need to clean up how scene_objects are constructed etc.


