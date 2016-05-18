
//#ifndef SPHERE_OBJECT_H
//#define SPHERE_OBJECT_H

#include "scene_object.h"


class sphere_object : public scene_object
{
	float radius;
public:
	float intersect(Ray& ray);
	vector3 surface_normal(vector3&);
	sphere_object(float rad, vector3 pos) : scene_object(pos) { radius = rad; }
	sphere_object(float rad, vector3 pos, rgbf nat, rgbf amb) : scene_object(pos) { radius = rad; }
	rgbf altcol(vector3& pos) { return natrual_colour; }
};

float sphere_object::intersect(Ray& ray)
{
	vector3& A = ray.position;
	vector3& B = ray.direction;
	vector3& C = position;
	
	float a = B * B;
	float b = 2 * (B * (A - C));
	float c = (A - C) * (A - C) - radius * radius;

	if (b * b - 4 * a * c < 0 || a < 0) 
	{
		return 0; //No intersection
	}

	//Compute such ts as discriminant is > 0
	float t1 = (-b + sqrt(b * b - 4 * a * c))/(2 * a);
	float t2 = (-b - sqrt(b * b - 4 * a * c))/(2 * a);

	if (t1 > t2)
	{
		return t2 > 0 ? t2 : t1;
	}

	return t1 > 0 ? t1 : t2;	
}

vector3 sphere_object::surface_normal(vector3& a)
{
	return !(a - position);
}

//#endif

