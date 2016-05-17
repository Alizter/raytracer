#include <iostream>
#include <math.h>

//////////////////////////////////////////////////
// A vector math class written by Ali Caglayan	//
// Let a, b be vectors (vector3 a, b)		//
// a + b (vector addition)			//
// a - b (vector subtraction)			//
//  -a	 (vector negation)			//
// a * b (dot product)				//
// a * r (scalar product (r is float))		//
// a ^ b (cross product)		 	//
//  !a	 (normalise vector)			//
//////////////////////////////////////////////////

struct vector3
{
	float x, y, z;
	
	vector3(float a =0, float b =0, float c =0) { x = a; y = b; z = c; }

	vector3 operator+(const vector3&) const;//vector addition
	vector3 operator-(const vector3&) const;//vector subtraction
	vector3 operator-() 		  const;//negation
	float   operator*(const vector3&) const;//dot product
	vector3 operator*(float) 	  const;//scalar product
	vector3 operator^(const vector3&) const;//cross product
	vector3 operator!() 		  const;//normalise

	float norm() const;   //norm
};

float vector3::norm() const { return sqrt(*this * *this); } 	//vector norm (magnitude)

vector3 vector3::operator!() const { return *this * (1.0f / norm()); }		//normalise
vector3 vector3::operator-() const { return vector3(-this->x, -this->y, -this->z); }	//negation

vector3 vector3::operator+(const vector3& a) const 
{ return vector3(this->x + a.x, this->y + a.y, this->z + a.z); } //vector addition

vector3 vector3::operator-(const vector3& a) const 
{ return vector3(this->x - a.x, this->y - a.y, this->z - a.z); } //vector subtraction

float 	vector3::operator*(const vector3& a) const 
{ return this->x * a.x + this->y * a.y + this->z * a.z; } //dot product

vector3 vector3::operator*(float a) const 
{ return vector3(a * this->x, a * this->y, a * this->z); } //scalar product
	
vector3 vector3::operator^(const vector3& a) const  //cross product
{ return vector3(this->y * a.z - this->z * a.y, this->z * a.x - this->x * a.z, this->x * a.y - this->y * a.x ); }

//Allow for output stream
std::ostream& operator<<(std::ostream& os, const vector3& a)
{
	return os << '(' << a.x << ',' << a.y << ',' << a.z << ')';
}

