
#include "scene_object.h"


class torus_object : public scene_object
{
	vector3 dir;
	float r;
	float R;
public:
	float intersect(Ray& ray);
	vector3 surface_normal(vector3&);
	torus_object(float rad, float inrad, vector3 pos, vector3 dir_ =vector3(0, 0, 1)) : scene_object(pos) { r = rad; R = inrad;  dir = dir_; }
	rgbf altcol(vector3& pos) { return natrual_colour; }
	//float quartic(double a, double b, double c, double d, double e);
};

////EXPERIMENTAL NEWTONS METHOD

double evPol(double x, int deg, double* coeffs) {
	double result = 0;
	for (int i = 0; i <= deg; i++) result += coeffs[i] * pow(x, i);
	return result;
}

float evDPol(double x, int deg, double* coeffs) {
	double result = 0;
	for (int i = 1; i <= deg; i++) result += i * coeffs[i] * pow(x, i - 1);
	return result;
}

double* poldiv(double r, int deg, double* coeffs) {
	double* q = new double[deg];
	q[deg - 1] = coeffs[deg - 1];
	for (int i = 2; i < deg; i++) q[deg - i - 1] = q[deg - i] * r + coeffs[deg - i];
	return q;
}

double newt(int n, int deg, double* coeffs) {
	double res = 0;
	for (int i = 0; i < n; i++) res = res - evPol(res, deg, coeffs) / evDPol(res, deg, coeffs);
	return (res < 0) ? newt(n, deg - 1, poldiv(res, deg, coeffs)) : res;
}

////EXPERIMENTAL NEWTONS METHOD


//minimum positive float
float mpf(float a, float b)
{
	if (a < 0 && b < 0) return 0;

	if (a > 0 && b <= 0) return a;
	if (a <= 0 && b > 0) return b;
	
	return fmin(a, b);
}

#include <complex>
#define C std::complex<double>

C sq(C r) { return r * r; }
C cb(C r) { return r * r * r; }
C fr(C r) { return r * r * r * r; }
C cbrt(C r) { return std::pow(r, 1.0/3); }

//Solves a quartic and gives smallest positive root
//This has been tested and works 99.9% sure
//This does however need optimisation
float quartic(double a, double b, double c, double d, double e)
{
	//Generate parts of quartic equation
	
	C p1 = 2.0 * cb(c) - 9.0 * b * c * d + 27.0 * a * sq(d) 
		+ 27.0 * sq(b) * e - 72.0 * a * c * e;
	C p2 = p1 + sqrt(-4.0*cb(sq(c) - 3.0 * b * d + 12.0 * a * e)+sq(p1));
	C p3 = (sq(c) - 3.0 * b * d + 12.0 * a * e)/(3.0 * a * cbrt(p2 / 2.0)) + cbrt(p2 / 2.0) / (3.0 * a);
	C p4 = sqrt(sq(b)/sq(2.0*a)-2.0*c/(3.0*a) + p3);
	C p5 = sq(b)/(2.0 * sq(a)) - (4.0 * c) / (3.0 * a) - p3;
	C p6 = (-cb(b)/cb(a) + 4.0 * b * c/sq(a) - 8.0 * d / a )/(4.0 * p4);

	C x1 = -b/(4.0*a) - p4/2.0 - sqrt(p5 - p6)/2.0;
	C x2 = -b/(4.0*a) - p4/2.0 + sqrt(p5 - p6)/2.0;
	C x3 = -b/(4.0*a) + p4/2.0 - sqrt(p5 + p6)/2.0;
	C x4 = -b/(4.0*a) + p4/2.0 + sqrt(p5 + p6)/2.0;
	
	//Definition of float zero
	float eps = 1E-6;
	
	//Clean non-real values
	float fx1 = fabs(x1.imag()) < eps ? x1.real() : 0;
	float fx2 = fabs(x2.imag()) < eps ? x2.real() : 0;
	float fx3 = fabs(x3.imag()) < eps ? x3.real() : 0;
	float fx4 = fabs(x4.imag()) < eps ? x4.real() : 0;

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
	//std::cout << "A: " << A << std::endl; 
	vector3 B = ray.direction;
	//std::cout << "B: " << B << std::endl;
	
	if ((B * A) * (B * A) - (B * B) * (A * A - (R + r) *(R + r)) < 0) return 0; //No intersection

	
	float AA = A * A;
	float BB = B * B;
	float AB = A * B;

	float An = A * dir;
	float Bn = B * dir;

	float ar = AA - R * R - r * r;
	
	float a = BB * BB;
	float b = 4 * AB * BB;
	float c = 2 * BB * ar + 4 * AB * AB + 4 * R * R * Bn * Bn;
	float d = 4 * AB * ar + 8 * R * R * An * Bn;
	float e = ar * ar + 4 * R * R * (An * An - r * r);
	
	//Solving quartic ax4+bx3+cx2+dx+e=0
	
	float t = quartic(a, b, c, d, e);

	//Newtons method
	
	//double cs[5] = {a, b, c, d, e};
	//float t = newt(10, 4, cs);
	
	return t; //Slice top of torus
}

vector3 torus_object::surface_normal(vector3& a)
{
	vector3 p = a - position;
	vector3 radial = !(p - p * dir) * R;
	return !(p - radial);

	//return !(((a - position) ^ dir) ^ (a - position));

	//return vector3(0, 0, 1);// !(a - position);
}

//#endif

