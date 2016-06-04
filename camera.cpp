#include "ray.h"
#include <math.h>

//TODO:
// - Clean up it looks silly

class camera
{
	int pixelwidth, pixelheight;
	float aspectRatio;

public:
	vector3 position;
	vector3 direction;
	vector3 up;
	vector3 right;
	Ray GetRay(const float& x, const float& y);	

	//Constructor
	camera()
	{
		position = vector3(0, 0, 0);
		direction = vector3(1, 0, 0);
		up = vector3(0, 0, 1);
		pixelwidth = 100;
		pixelheight = 100;

		aspectRatio = 1;
	}

	void setDirection(vector3 dir)
	{
		direction = dir;
		
		right = !(up ^ direction);
	}

	void setPixelSize(int width, int height)
	{	
		pixelwidth = width;
		pixelheight = height;
		aspectRatio = (float)pixelwidth / (float)pixelheight;
		std::cout << "CS: " << width << " X " << height << " " << "AR: " << aspectRatio << std::endl;
	}
};

Ray camera::GetRay(const float& x, const float& y)
{
	return Ray(
		position,  
			right * (2 * x / pixelwidth - 1) * aspectRatio 
			+ up * (2 * y / pixelheight - 1) + direction);
}
