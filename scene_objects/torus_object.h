
#include "scene_object.h"


class torus_object : public scene_object
{
	vector3 dir;
	float r;
	float R;
public:
	float intersect(Ray& ray);
	vector3 surface_normal(vector3&);
	torus_object(float rad, float inrad, vector3 pos, vector3 dir =vector3(0, 0, 1)) : scene_object(pos) { r = rad; R = inrad; }
	rgbf altcol(vector3& pos) { return natrual_colour; }
	float quartic(float a, float b, float c, float d, float e);
};

//minimum positive float
float mpf(float a, float b)
{
	if (a < 0 && b < 0) return 0;

	if (a > 0 && b <= 0) return a;
	if (a <= 0 && b > 0) return b;
	
	return fmin(a, b);
}

#include <complex>
#define C std::complex<float>

C sq(C r) { return r * r; }
C cb(C r) { return r * r * r; }
C fr(C r) { return r * r * r * r; }
C cbrt(C r) { return std::pow(r, 1.0f/3); }

//Solves a quartic and gives smallest positive root
float torus_object::quartic(float a, float b, float c, float d, float e)
{
	//Generate parts of quartic equation
	
	C p1 = 2.0f * cb(c) - 9.0f * b * c * d + 27.0f * a * sq(d) 
		+ 27.0f * sq(b) * e - 72.0f * a * c * e;
	C p2 = p1 + sqrt(-4.0f*cb(sq(c) - 3.0f * b * d + 12.0f * a * e)+sq(p1));
	C p3 = (sq(c) - 3.0f * b * d + 12.0f * a * e)/(3.0f * a * cbrt(p2 / 2.0f)) + cbrt(p2 / 2.0f) / (3.0f * a);
	C p4 = sqrt(sq(b)/sq(2.0f*a)-2.0f*c/(3.0f*a) + p3);
	C p5 = sq(b)/(2.0f * sq(a)) - (4.0f * c) / (3.0f * a) - p3;
	C p6 = (-cb(b)/cb(a) + 4.0f * b * c/sq(a) - 8.0f * d / a )/(4.0f * p4);

	C x1 = -b/(4.0f*a) - p4/2.0f - sqrt(p5 - p6)/2.0f;
	C x2 = -b/(4.0f*a) - p4/2.0f + sqrt(p5 - p6)/2.0f;
	C x3 = -b/(4.0f*a) + p4/2.0f - sqrt(p5 + p6)/2.0f;
	C x4 = -b/(4.0f*a) + p4/2.0f + sqrt(p5 + p6)/2.0f;
	
	//Definition of float zero
	float eps = 1E-6;
	
	//Clean non-real values
	float fx1 = abs(x1.imag()) < eps ? x1.real() : 0;
	float fx2 = abs(x2.imag()) < eps ? x2.real() : 0;
	float fx3 = abs(x3.imag()) < eps ? x3.real() : 0;
	float fx4 = abs(x4.imag()) < eps ? x4.real() : 0;

	/*std::cout << fx1 << '\n'
		<< fx2 << '\n'
		<< fx3 << '\n'
		<< fx4 << std::endl;*/

	//if (fx1 == 0 && fx2 == 0 && fx3 == 0 && fx4 == 0) std::cout << mpf(mpf(fx1, fx2), mpf(fx3, fx4)) <<std::endl;

	return mpf(mpf(fx1, fx2), mpf(fx3, fx4));
	 
	//return fmin(fmin(x1.real(), x2.real()), fmin(x3.real(), x4.real()));
}

float torus_object::intersect(Ray& ray)
{
	vector3 A = ray.position - position;
	vector3 B = ray.direction;

	//Check bounding sphere intersection first
	if (4 * (B * A) * (B * A) - 4 * (B * B) * ((A * A) - (r + R) * (r + R)) < 0) return 0;

	float AA = A * A;
	float BB = B * B;
	float AB = A * B;

	float An = A.z;//A * dir;
	float Bn = A.z;//B * dir;

	float ar = AA - R * R - r * r;
	
	float a = BB * BB;
	float b = 4 * AB * BB;
	float c = 2 * BB * ar + 4 * AB * AB + 4 * R * R * Bn * Bn;
	float d = 4 * AB * ar + 8 * R * R * An * Bn;
	float e = ar * ar + 4 * R * R * (An * An - r * r);
	
	//Solving quartic ax4+bx3+cx2+dx+e=0
	
	float t = quartic(a, b, c, d, e);

	if ((A + position + B * t).z < 0.5) return t;
	else return 0;
	
}

vector3 torus_object::surface_normal(vector3& a)
{
	return !(((a - position) ^ dir) ^ (a - position));

	//return vector3(0, 0, 0);// !(a - position);
}

//#endif

