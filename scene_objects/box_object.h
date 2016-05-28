#ifndef BOX
#define BOX

#include "scene_object.h"

class box : public scene_object
{	
public:
	vector3 lb;
	vector3 rt;	

	float intersect(Ray&);
	vector3 surface_normal(vector3&);
	
	rgbf altcol(vector3& pos);

	box(vector3 pos, vector3 leftbottom, vector3 righttop) : scene_object(pos)
	{
		lb = leftbottom + pos;
		rt = righttop + pos;
	}
};

//Slab intersection algorithm
float box::intersect(Ray& ray)
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

rgbf box::altcol(vector3& a)
{
	return natrual_colour;
}


//--B-R-O-K-E-N--
//A virtual construct called altcol was added to scene_object.h
//This allows for cube face colouring and better visualisation of cube face finder algorithm
//
//This issue has now been fixed. Use fabs instead of abs


vector3 box::surface_normal(vector3& pos)
{
	float eps = 1E-6; //Floats must fall within this range to be equal

	float a = fabs(pos.x - lb.x); //std::cout << a << std::endl;
	float b = fabs(pos.x - rt.x); //std::cout << b << std::endl;
	float c = fabs(pos.y - lb.y); //std::cout << c << std::endl;
	float d = fabs(pos.y - rt.y); //std::cout << d << std::endl;
	float e = fabs(pos.z - lb.z); //std::cout << e << std::endl;
	float f = fabs(pos.z - rt.z); //std::cout << f << std::endl;

	if (a < eps) return vector3(-1, 0, 0);
	if (b < eps) return vector3( 1, 0, 0);
	if (c < eps) return vector3( 0,-1, 0);
	if (d < eps) return vector3( 0, 1, 0);
	if (e < eps) return vector3( 0, 0,-1);
	if (f < eps) return vector3( 0, 0, 1);

	return vector3(0, 0, 0);
}

#endif
