#include "scene_object.h"

class box : public scene_object
{	
	vector3 lb;
	vector3 rt;	
public:
	float intersect(Ray&);
	vector3 surface_normal(vector3&);

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


//BROKEN
vector3 box::surface_normal(vector3& pos)
{
	//vector3 o = (lb - rt) * 0.5;
	//vector3 in = pos - o;
	//if (in.x - rt.x <= 1E-6) return vector3(1, 0, 0);
	//	else return vector3(-1, 0, 0);
	//if (in.y - rt.y <= 1E-6) return vector3(0, 1, 0);
	//	else return vector3(0, -1, 0);
	//if (in.z - rt.z <= 1E-6) return vector3(0, 0, 1);
	//	else return vector3(0, 0, -1);

	
	//float a = abs(pos.x - o.x);
	//float as = a/(pos.x - o.x);	
	//float b = abs(pos.y - o.y);
	//float bs = b/(pos.y - o.y);
	//float c = abs(pos.z - o.z);
	//float cs = c/(pos.z - o.z);
	
	float eps = 0.1; //Floats must fall within this range to be equal

	float a = abs(pos.x - lb.x); //std::cout << a << std::endl;
	float b = abs(pos.x - rt.x); //std::cout << b << std::endl;
	float c = abs(pos.y - lb.y);
	float d = abs(pos.y - rt.y);
	float e = abs(pos.z - lb.z);
	float f = abs(pos.z - rt.z);

	if (a < eps) return vector3(-1, 0, 0);
	if (b < eps) return vector3( 1, 0, 0);
	if (c < eps) return vector3( 0,-1, 0);
	if (d < eps) return vector3( 0, 1, 0);
	if (e < eps) return vector3( 0, 0, 1);
	if (f < eps) return vector3( 0, 0,-1);
	
	//float cond = fmax(a, fmax(b, c));
	
	//if (cond == a) return vector3(-as, 0, 0);
	//if (cond == b) return vector3(0, -bs, 0);
	//if (cond == c) return vector3(0, 0, cs);
	//return vector3(0, 0, 0);
	//switch()
	//{
	//	case a: return !(vector3(0, o.y, 0) ^ vector3(0, 0, o.z)) * as;
	//	case b: return !(vector3(o.x, 0, 0) ^ vector3(0, 0, o.z)) * bs;
	//	case c: return !(vector3(o.x, 0, 0) ^ vector3(0, o.y, 0)) * cs;
		
	//}
}


