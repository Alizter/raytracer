#include "ray.h"

//TODO:
// - Encapsulate class
// - make as header file

class camera
{
public:
	vector3 position;
	vector3 direction;
	vector3 up;
	int pixelwidth, pixelheight;
	Ray GetRay(float x, float y);	

	//Constructor
	camera(vector3 pos =vector3(0,0,0), vector3 dir =vector3(1,0,0), vector3 up_ =vector3(0,0,1), int width =100, int height =100)
	{
		position = pos;
		up = up_;
		direction = dir;
		pixelwidth = width;
		pixelheight = height;
	}
};

Ray camera::GetRay(float x, float y)
{
	return Ray(position,  (up ^ direction) * (x / pixelwidth - 0.5) +  up * (y / pixelheight - 0.5) + direction);
}
