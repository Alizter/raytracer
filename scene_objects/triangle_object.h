#ifndef TRI
#define TRI

#include "scene_object.h"

class triangle_object : public scene_object
{
	vector3 v1;
	vector3 v2; //Coordinates of vertecies in scene space
	vector3 v3;
	vector3 n;

public:
	float intersect(Ray&);
	vector3 surface_normal(vector3&);
	
	//Constructor vertecies are relative to specified position
	triangle_object(vector3 pos, vector3 vert1, vector3 vert2, vector3 vert3, vector3 nor =vector3(0, 0, 0)) : scene_object(pos)
	{
		v1 = pos + vert1;
		v2 = pos + vert2;
		v3 = pos + vert3;

		if (nor.norm() == 0) n = !((v2 - v1)^(v3 - v1));
		else n = nor;
	}
};

//Ray triangle intersection
//Moller-Trumbore intersection algorithm
float triangle_object::intersect(Ray& ray)
{
	float eps = 1E-6;

	vector3 e1 = v2 - v1;
	vector3 e2 = v3 - v1;

	vector3 P = ray.direction ^ e2;

	float det = e1 * P;

	if (fabs(det) < eps) return 0;

	float inv_det = 1.0f / det;

	vector3 T = ray.position - v1;

	float u = (T * P) * inv_det;

	if (u < 0 || u > 1) return 0;

	vector3 Q = T ^ e1;

	float v = (ray.direction * Q) * inv_det;

	if (v < 0 || u + v > 1) return 0;

	float t = (e2 * Q) * inv_det;

	if (t > eps) return t;

	return 0;
}

//Ray triangle normal
vector3 triangle_object::surface_normal(vector3& a) 
{
	return n;
}

#endif
