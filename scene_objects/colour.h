
//#ifndef COLOUR_H
//#define COLOUR_H
#include "scene_object.h"

struct rgbf
{
	float r, g, b;
	rgbf(const float x =0, const float y =0, const float z =0) { r = x; g = y; b = z; }
	rgbf operator+(rgbf);
	rgbf operator*(float);
	rgbf operator*(rgbf&);
	rgbf operator!();
};



rgbf rgbf::operator+(rgbf a)
{
	return rgbf(r + a.r, g + a.g, b + a.b);
}

rgbf rgbf::operator*(float a)
{
	return rgbf(a * r, a * g, a* b);
}

rgbf rgbf::operator*(rgbf& a)
{
	return rgbf(r * a.r, g * a.g, b * a.b);
}

rgbf rgbf::operator!()
{
	float s = fmax(fmax(r, g), b);
	return rgbf(r/s, g/s, b/s);
}


//#endif