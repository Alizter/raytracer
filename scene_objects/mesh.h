#include "scene_object.h"

class mesh : public scene_object
{
public:
	float intersect(Ray& ray);
	vector3 surface_normal(vector3&);
	
	//Mesh constructor
	mesh(vector3 pos /* Mesh data should go here */) : scene_object(pos)
	{
		
	}

	rgbf altcol(vector3& pos) { return natrual_colour; }
};

//Intersect with bounding box before then actual object
//This prevents unnecessery expensive intersection tests
float mesh::intersect(Ray& ray)
{
	float tbb = bb_intersect(ray);

	//If there isn't an intersection with the bounding box
	//then return no intersection
	if (bb == 0) return 0; 
	
	//Otherwise intersect with object

}

float bb_intersect(Ray& ray)
{
	float ix = 1 / ray.direction.x;
	float iy = 1 / ray.direction.y;
	float iz = 1 / ray.direction.z;

	float t1 = (lb.x - ray.position.x) * ix;
	float t2 = (rt.x - ray.position.x) * ix;
	float t3 = (lb.y - ray.position.y) * iy;
	float t4 = (rt.y - ray.position.y) * iy;
	float t5 = (lb.z - ray.position.z) * iz;
	float t6 = (rt.z - ray.position.z) * iz;

	float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
	float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

	if (tmax < 0) return 0;
	if (tmax < tmin) return 0;

	return tmin;
}

//Surface normals will be worked out later
vector3 mesh::surface_normal(vector3& a)
{
	
}
