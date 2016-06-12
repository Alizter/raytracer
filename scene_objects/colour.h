
//#ifndef COLOUR_H
//#define COLOUR_H
#include <math.h>
#include <stdexcept>
#include "scene_object.h"

struct rgbf
{
	float r, g, b;
	rgbf(const float x =0, const float y =0, const float z =0) { r = x; g = y; b = z; }
	float& operator[] (const int index);
	rgbf operator+(rgbf);
	rgbf operator*(float);
	rgbf operator*(rgbf&);
	rgbf operator!();
	rgbf operator+=(rgbf);
	bool operator==(rgbf);
	rgbf gc(float); //Gamma correction
};

float& rgbf::operator[](int a)
{
	switch (a)
	{
		case 0: return r;
		case 1: return g;
		case 2: return b;
		default: throw std::out_of_range("Colour index is out of range");
	}
}

rgbf rgbf::gc(float ga)
{
	return rgbf(pow(r, ga), pow(g, ga), pow(b, ga));
}

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

rgbf rgbf::operator+=(rgbf a)
{
	r += a.r;
	g += a.g;
	b += a.b;
	return *this;
}

bool rgbf::operator==(rgbf a)
{
	return (r == a.r) && (g == a.g) && (b == a.b);
}


//#endif
