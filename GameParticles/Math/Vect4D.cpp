#include <math.h>
#include <assert.h>

#include "Vect4D.h"


Vect4D::Vect4D()
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
	//this->x = 0.0f;
	//this->y = 0.0f;
	//this->z = 0.0f;
	//this->w = 1.0f;
}

Vect4D::Vect4D( const float tx, const float ty, const float tz, const float tw )
	: x(tx), y(ty), z(tz), w(tw)
{
	//this->x = tx;
	//this->y = ty;
	//this->z = tz;
	//this->w = tw;
}

Vect4D::Vect4D(const Vect4D & in)
	: x(in.x), y(in.y), z(in.z), w(in.w)
{
	//this->x = in.x;
	//this->y = in.y;
	//this->z = in.z;
	//this->w = in.w;
}

const Vect4D & Vect4D::operator=(const Vect4D & in)
{
	if (this != &in)
	{
		this->x = in.x;
		this->y = in.y;
		this->z = in.z;
		this->w = in.w;
	}
	return *this;
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

//const void Vect4D::norm(Vect4D& out) const
//{
//	float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z );
//
//	if( 0.0f < mag )
//	{
//		out.x = this->x / mag;
//		out.y = this->y / mag;
//		out.z = this->z / mag;
//		out.w = 1.0f;
//	}
//}

float& Vect4D::operator[]( const VECT_ENUM e )
{
	switch(e)
	{
	case 0:
			return x;
			break;
	case 1:
			return y;
			break;
	case 2: 
			return z;
			break;
	case 3:
			return w;
			break;
	default:
			assert(0);
			return x;
	}
}

//const void Vect4D::Cross( const Vect4D& vin, Vect4D& vout)
//{
//	vout._m = _mm_sub_ps(_mm_mul_ps(_mm_setr_ps(this->y, this->z, this->x, 0.0f),
//											_mm_setr_ps(vin.z, vin.x, vin.y, 0.0f)),
//								_mm_mul_ps(_mm_setr_ps(this->z, this->x, this->y, 1.0f),
//											_mm_setr_ps(vin.y, vin.z, vin.x, 1.0f)));
//	
//	vout.x = (y*vin.z - z*vin.y);
//	vout.y = (z*vin.x - x*vin.z);
//	vout.z = (x*vin.y - y*vin.x);
//	vout.w = 1.0f;
//}

// End of file