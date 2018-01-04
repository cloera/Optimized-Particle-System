// Vect4D.h
//
// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <xmmintrin.h>
#include <smmintrin.h>  
#include "Align16.h"

// Foward Declarations
class Matrix;

// class
class Vect4D : public Align16
{
public:
	friend class Matrix;

	Vect4D();	
	Vect4D( const float tx, const float ty, const float tz, const float tw = 1.0f );
	Vect4D( const Vect4D &in );
	const Vect4D & operator= ( const Vect4D &in );
	~Vect4D();

	Vect4D(const __m128 &m)
	{
		this->_m = m;
	}

	const void norm(Vect4D &out) const
	{
		__m128 mag = _mm_set_ps1(
			_mm_sqrt_ps(
				_mm_dp_ps(_mm_setr_ps(this->x, this->y, this->z, 0.0f), _mm_setr_ps(this->x, this->y, this->z, 0.0f), 0xF1)
			).m128_f32[0]
		);

		if (0.0f < mag.m128_f32[0])
		{
			mag.m128_f32[3] = 1.0f;
			out._m = _mm_div_ps(_mm_setr_ps(this->x, this->y, this->z, 1.0f), mag);
		}
	}

	const void set(const float tx, const float ty, const float tz, const float tw = 1.0f)
	{
		this->_m = _mm_setr_ps(tx, ty, tz, tw);
	}
	
	const Vect4D operator + (const Vect4D &t) const
	{
		return Vect4D(_mm_add_ps(this->_m, t._m));
	}

	const Vect4D operator - (const Vect4D &t) const
	{
		return Vect4D(_mm_sub_ps(this->_m, t._m));
	}

	const Vect4D operator * (const float scale) const
	{
		return Vect4D(_mm_mul_ps(this->_m, _mm_set_ps1(scale)));
	}

	const void operator *= (const float &scale)
	{
		this->_m = _mm_mul_ps(this->_m, _mm_set_ps1(scale));
	}

	const void operator += (const Vect4D &t)
	{
		this->_m = _mm_add_ps(this->_m, t._m);
	}

	const void Cross(const Vect4D &vin, Vect4D &vout)
	{
		vout._m = _mm_sub_ps(_mm_mul_ps(_mm_setr_ps(this->y, this->z, this->x, 0.0f),
										_mm_setr_ps(vin.z, vin.x, vin.y, 0.0f)),
							_mm_mul_ps(_mm_setr_ps(this->z, this->x, this->y, 1.0f),
										_mm_setr_ps(vin.y, vin.z, vin.x, 1.0f)));
	}

	float &operator[]( const VECT_ENUM e );


public:
	// anonymous union
	union
	{
		__m128    _m;

		// anonymous struct
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};

private:
	template<typename T, typename U, typename V, typename W> Vect4D(const T tx, const U ty, const V tz, const W tw = 1.0f) {};
	template<typename T> const Vect4D operator * (const T scale) const {};
	template<typename T, typename U, typename V, typename W> const void set(const T tx, const U ty, const V tz, const W tw = 1.0f) {};
};

#endif  //Vect4D.h
