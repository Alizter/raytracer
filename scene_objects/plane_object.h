#include "scene_object.h"

class plane_object : public scene_object
{
public:
	vector3 b;
	vector3 c;
	vector3 n;
	
	float intersect(Ray& ray);
	vector3 surface_normal(vector3&);

	rgbf altcol(vector3& pos) { return natrual_colour; }
	
	plane_object(vector3 pos, vector3 b_, vector3 c_) : scene_object(pos) 
	{ 
		b = b_;		//Two vectors that span plane
		c = c_;		//This WILL through divide by zero if parallel
		n = !(b_ ^ c_); //Normal for plane
	}

	plane_object(vector3 pos, vector3 b_, vector3 c_, rgbf nat, rgbf amb) : scene_object(pos)
	{ 
		b = b_;		//Two vectors that span plane
		c = c_;		//This WILL through divide by zero if parallel
		n = !(b_ ^ c_); //Normal for plane
	}
};

float plane_object::intersect(Ray& ray)
{
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
	float k = ray.direction * n;

	if (k == 0) return 0; //Check if line exists in plane
	//std::cin.get();
	//std::cout << ((position - ray.position) * n) * (1 / k) << std::endl;
	return fmax(0,((position - ray.position) * n) * (1 / k));
}

vector3 plane_object::surface_normal(vector3&)
{
	return n; //Surface normal for plane already computed
}
