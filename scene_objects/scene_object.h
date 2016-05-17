

#ifndef SCENE_OBJECT
#define SCENE_OBJECT
#include "../camera.cpp"


//#include "sphere_object.h"
#include "colour.h"
struct rgbf;
//struct sphere_object;
//struct plane_object;


class scene_object
{

public:
	bool transparent;
	bool reflective;
	float I_ref;
	float k_diff;
	float k_spec;
	float shininess;

	rgbf natrual_colour;
	rgbf ambient_colour;
	vector3 position;
	virtual float intersect(Ray& ray) = 0;
	virtual vector3 surface_normal(vector3&) = 0;
	
	scene_object(vector3 pos) 
	{ 
		transparent = false;
		position = pos;
		reflective = false;
		I_ref = 0;
		k_diff = 1;
		k_spec = 1;
		shininess = 10;

		natrual_colour = rgbf(1, 1, 1);
		ambient_colour = rgbf(0.1, 0.1, 0.1);
	}
	
};




//Light source
class light
{
public:
	vector3 position;// = vector3(0, 0, 0);
	rgbf colour;// = rgbf(1, 1, 1);
	float intensity;// = 1.0f;
	light(vector3, rgbf, float);
};

light::light(vector3 pos, rgbf col, float inte)
{
	position = pos;
	colour = col;
	intensity = inte;
}



#endif
