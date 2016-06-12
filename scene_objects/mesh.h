#include <vector>
#include "triangle_object.h"
#include "box_object.h"

typedef std::vector<triangle_object*> tvec;

class octmesh
{
	box bb;
	
public:
	octmesh(vector3 lb, vector3 rt) : bb((lb + rt)*0.5, (lb-rt)*0.5, (rt-lb)*0.5)
	{
	}


};

class mesh : public scene_object
{
	box bb;
	triangle_object* lasttri;
public:
	float intersect(Ray& ray);
	vector3 surface_normal(vector3&);
	tvec triangles;

	void add_triangle(triangle_object*);
	float bb_intersect(Ray& ray);
	
	//Mesh constructor
	mesh(vector3 pos, vector3 bblb, vector3 bbrt /* Mesh data should go here */) : scene_object(pos), bb(pos, bblb, bbrt)
	{

	}
};

void mesh::add_triangle(triangle_object* tri)
{
	triangles.push_back(tri);
}

//Intersect with bounding box before then actual object
//This prevents unnecessery expensive intersection tests
float mesh::intersect(Ray& ray)
{
	float tbb = bb_intersect(ray);

	//If there isn't an intersection with the bounding box
	//then return no intersection
	if (tbb == 0) return 0; 
	
	//Otherwise intersect with object
	float t = 0;
	float temp = 0;

	for (int i = 0; i < triangles.size(); i++)
	{
		temp = triangles[i]->intersect(ray);
		if ((temp < t || t == 0) && temp > 0) 
		{
			t = temp;
			lasttri = triangles[i];
		}
	}

	return t;
}

float mesh::bb_intersect(Ray& ray)
{
	float ix = 1 / ray.direction.x;
	float iy = 1 / ray.direction.y;
	float iz = 1 / ray.direction.z;

	float t1 = (bb.lb.x - ray.position.x) * ix;
	float t2 = (bb.rt.x - ray.position.x) * ix;
	float t3 = (bb.lb.y - ray.position.y) * iy;
	float t4 = (bb.rt.y - ray.position.y) * iy;
	float t5 = (bb.lb.z - ray.position.z) * iz;
	float t6 = (bb.rt.z - ray.position.z) * iz;

	float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
	float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

	if (tmax < 0) return 0;
	if (tmax < tmin) return 0;

	return tmin;
}

//Surface normals will be worked out later
vector3 mesh::surface_normal(vector3& a)
{
	return lasttri->surface_normal(a);
}
