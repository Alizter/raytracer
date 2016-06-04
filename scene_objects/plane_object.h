#include "scene_object.h"

class plane_object : public scene_object
{
public:
	vector3 n;
	
	float intersect(Ray& ray);
	vector3 surface_normal(vector3&);

	rgbf altcol(vector3& pos) { return natrual_colour; }
	
	plane_object(vector3 pos, vector3 n_) : scene_object(pos) 
	{
		n = !n_; //Normal for plane
	}
};

float plane_object::intersect(Ray& ray)
{
	float k = ray.direction * n;

	if (k == 0) return 0;
	return fmax(0,((position - ray.position) * n) * (1 / k));
}

vector3 plane_object::surface_normal(vector3&) 
{
	return n; //Surface normal for plane already computed
}

//Plane intersection algorithm

	// Equation for plane is r = a + l b + u c
	// Equation for line is r = d + E e
	// equation for plane is also: r . n = a . n
	// r . (b x c) = a . (b x c)
	// (d + E e) . (b x c) = a . (b x c)
	// d . (b x c) + E e . (b x c) = a . (b x c)
	// E e . (b x c) = a . (b x c) - d . (b x c)
	// E e . (b x c) = (a - d) . (b x c)
	//	      (a - d) . (b x c)
	// ==> E =   ------------------
	//		 e . (b x c)

	//Feasability condition e . (b x c) =/= 0
