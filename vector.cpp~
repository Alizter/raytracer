#include <iostream>
#include <math.h>

//////////////////////////////////////////////////
// A vector math class written by Ali Caglayan	//
// Let a, b be vectors (vector3 a, b)		//
// a + b (vector addition)			//
// a - b (vector subtraction)			//
//  -a	 (vector negation)			//
// a * b (dot product)				//
// r * a (scalar product (r is float))		//
// a ^ b (cross product)		 	//
//  !a	 (normalise vector)			//
//////////////////////////////////////////////////

struct vector3
{
	float x, y, z;
	
	vector3(float a =0, float b =0, float c =0) { x = a; y = b; z = c; }

	vector3 operator+(vector3, vector3); 	//vector addition
	vector3 operator-(vector3, vector3); 	//vector subtraction
	vector3 operator-();			//negation
	float	operator*(vector3, vector3);	//dot product
	vector3 operator*(float, vector3);	//scalar product
	vector3 operator^(vector3, vector3); 	//cross product
	vector3 operator!();			//normalise

	double&	 norm(vector3, vector3);	//norm
};

float norm(vector3 a) { return sqrt(a * a); } 				//vector norm (magnitude)

vector3 operator!()			{ return 1.0f / norm(a) * a; }	//normalise
vector3 operator-() 			{ return {-a.x, -a.y, -a.z}; }	//negation


vector3 operator+(vector3 a, vector3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }	//vector addition
vector3 operator-(vector3 a, vector3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }	//vector subtraction
float 	operator*(vector3 a, vector3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }	//dot product
vector3 operator*(float a,   vector3 b) { return {a * b.x, a * b.y, a * b.z}; }		//scalar product
vector3 operator^(vector3 a, vector3 b) { return {a.y * b.z - a.z * b.y,		//*
						  a.z * b.x - a.x * b.z,		//cross product 
						  a.x * b.y - a.y * b.x }; }		//*

//Allow for output stream
std::ostream& operator<<(std::ostream& os, const vector3& a)
{
	return os << '(' << a.x << ',' << a.y << ',' << a.z << ')';
}
