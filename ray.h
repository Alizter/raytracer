#include "vector.h"

struct Ray
{
	vector3 position;
	vector3 direction;


	Ray(vector3 pos, vector3 dir)
	{
		position = pos;
		direction = dir;
	}

	vector3 point(float t);
};

vector3 Ray::point(float t)
{
	return position + direction * t;
}