#ifndef _ENTITY_MATH_H_
#define _ENTITY_MATH_H_

#define PI 3.14159265358979323846

typedef unsigned int Uint;

class Vector2D
{
	public:
		Vector2D(const float x, const float y) : x_(x), y_(y) {}
		Vector2D() : x_(0.0F), y_(0.0F) {}
		
		float x_;
		float y_;
};

class Vector3D
{
	public:
		Vector3D(const float x, const float y, const float z) : x_(x), y_(y), z_(z) {}
		Vector3D() : x_(0.0F), y_(0.0F), z_(0.0F) {}
		
		float x_;
		float y_;
		float z_;
};

class ViewPort2D
{
	public:
		ViewPort2D(const Uint x1, const Uint y1, const Uint x2, const Uint y2) : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}
		ViewPort2D() : x1_(0U), y1_(0U), x2_(0U), y2_(0U) {}
		
		const Vector2D getTopLeft() { return Vector2D(x1_, y1_); }
		const Vector2D getBottomRight() { return Vector2D(x2_, y2_); }
		
		Uint x1_;
		Uint y1_;
		Uint x2_;
		Uint y2_;
};

double deg2rad(double deg);
double rad2deg(double rad);

#endif
