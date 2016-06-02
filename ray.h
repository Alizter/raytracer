#include "vector.h"

struct Ray
{
	vector3 position;
	vector3 direction;


	Ray(const vector3& pos, const vector3& dir)
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
