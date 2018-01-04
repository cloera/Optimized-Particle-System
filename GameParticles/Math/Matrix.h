#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"
#include <xmmintrin.h>
#include <smmintrin.h>  
#include "Align16.h"

// forward declare
//class Vect4D;

// class
class Matrix : public Align16
{
public:

	Matrix();	
	Matrix( const Matrix& t );
	const Matrix & operator= ( const Matrix &t );
	~Matrix();

	Matrix(const Vect4D &inV0, const Vect4D &inV1, const Vect4D &inV2, const Vect4D &inV3);

	const void setIdentMatrix();
	const void setTransMatrix(const Vect4D &t );
	const void setScaleMatrix(const Vect4D &s );
	const void setRotZMatrix( const float Z_Radians );

	const float &operator[]( const INDEX_ENUM e);
	
	//const Matrix operator*( const Matrix &t ) const;

	const float Determinant() const;
	
	const Matrix GetAdjugate() const;
	const Matrix& Matrix::operator/=( const float t);
	
	const void Matrix::Inverse( Matrix &out ) const;


	/*
	*
	*  Begin M * M * M * M * M * V  Proxy Structs
	*
	*/


	// First Proxy MmultM
	struct MmultM
	{
		const Matrix &mA;
		const Matrix &mB;

		MmultM()
			: mA(Matrix()), mB(Matrix())
		{
		}

		MmultM(const MmultM &in)
			: mA(in.mA), mB(in.mB)
		{
		}

		MmultM & operator = (const MmultM &)
		{
			return *this;
		}

		MmultM(const Matrix &t1, const Matrix &t2)
			: mA(t1), mB(t2)
		{
		};

		operator Matrix()
		{
			Matrix m;
			// mA.v0 * mB
			m.v0._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v0.x), mB.v0._m),
				_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v0.y), mB.v1._m),
					_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v0.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v0.w), mB.v3._m))));
			// mA.v1 * mB
			m.v1._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v1.x), mB.v0._m),
				_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v1.y), mB.v1._m),
					_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v1.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v1.w), mB.v3._m))));
			// mA.v2 * mB
			m.v2._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v2.x), mB.v0._m),
				_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v2.y), mB.v1._m),
					_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v2.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v2.w), mB.v3._m))));
			// mA.v3 * mB
			m.v3._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v3.x), mB.v0._m),
				_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v3.y), mB.v1._m),
					_mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v3.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v3.w), mB.v3._m))));
			return m;
		}
	};

	friend inline MmultM operator * (const Matrix &t1, const Matrix &t2)
	{
		return MmultM(t1, t2);
	}


	// Second Proxy MmultMM
	struct MmultMM
	{
		const Matrix &mA;
		const Matrix &mB;
		const Matrix &mC;

		MmultMM()
			: mA(Matrix()), mB(Matrix()), mC(Matrix())
		{
		}

		MmultMM(const MmultMM &in)
			: mA(in.mA), mB(in.mB), mC(in.mC)
		{
		}

		MmultMM & operator = (const MmultMM &)
		{
			return *this;
		}

		MmultMM(const MmultM &t1, const Matrix &t2)
			: mA(t1.mA), mB(t1.mB), mC(t2)
		{
		};

	};

	friend inline MmultMM operator * (const MmultM &t1, const Matrix &t2)
	{
		return MmultMM(t1, t2);
	}


	// Third Proxy MmultMMM
	struct MmultMMM
	{
		const Matrix &mA;
		const Matrix &mB;
		const Matrix &mC;
		const Matrix &mD;

		MmultMMM()
			: mA(Matrix()), mB(Matrix()), mC(Matrix()), mD(Matrix())
		{
		}

		MmultMMM(const MmultMMM &in)
			: mA(in.mA), mB(in.mB), mC(in.mC), mD(in.mD)
		{
		}

		MmultMMM & operator = (const MmultMMM &)
		{
			return *this;
		}

		MmultMMM(const MmultMM &t1, const Matrix &t2)
			: mA(t1.mA), mB(t1.mB), mC(t1.mC), mD(t2)
		{
		};

	};

	friend inline MmultMMM operator * (const MmultMM &t1, const Matrix &t2)
	{
		return MmultMMM(t1, t2);
	}

	// Fourth Proxy MmultMMMM
	struct MmultMMMM
	{
		const Matrix &mA;
		const Matrix &mB;
		const Matrix &mC;
		const Matrix &mD;
		const Matrix &mE;

		MmultMMMM()
			: mA(Matrix()), mB(Matrix()), mC(Matrix()),
			mD(Matrix()), mE(Matrix())
		{
		}

		MmultMMMM(const MmultMMMM &in)
			: mA(in.mA), mB(in.mB), mC(in.mC), mD(in.mD), mE(in.mE)
		{
		}

		MmultMMMM & operator = (const MmultMMMM &)
		{
			return *this;
		}

		MmultMMMM(const MmultMMM &t1, const Matrix &t2)
			: mA(t1.mA), mB(t1.mB), mC(t1.mC), mD(t1.mD), mE(t2)
		{
		};

		operator Matrix()
		{
			Matrix m;
			// mA * mB
			m.v0._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v0.x), mB.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v0.y), mB.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v0.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v0.w), mB.v3._m))));
			m.v1._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v1.x), mB.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v1.y), mB.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v1.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v1.w), mB.v3._m))));
			m.v2._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v2.x), mB.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v2.y), mB.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v2.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v2.w), mB.v3._m))));
			m.v3._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v3.x), mB.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v3.y), mB.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(mA.v3.z), mB.v2._m), _mm_mul_ps(_mm_set_ps1(mA.v3.w), mB.v3._m))));
			// (mA * mB) * mC
			m.v0._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.x), mC.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.y), mC.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.z), mC.v2._m), _mm_mul_ps(_mm_set_ps1(m.v0.w), mC.v3._m))));
			m.v1._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.x), mC.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.y), mC.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.z), mC.v2._m), _mm_mul_ps(_mm_set_ps1(m.v1.w), mC.v3._m))));
			m.v2._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.x), mC.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.y), mC.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.z), mC.v2._m), _mm_mul_ps(_mm_set_ps1(m.v2.w), mC.v3._m))));
			m.v3._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.x), mC.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.y), mC.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.z), mC.v2._m), _mm_mul_ps(_mm_set_ps1(m.v3.w), mC.v3._m))));
			// (mA * mB * mC) * mD
			m.v0._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.x), mD.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.y), mD.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.z), mD.v2._m), _mm_mul_ps(_mm_set_ps1(m.v0.w), mD.v3._m))));
			m.v1._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.x), mD.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.y), mD.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.z), mD.v2._m), _mm_mul_ps(_mm_set_ps1(m.v1.w), mD.v3._m))));
			m.v2._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.x), mD.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.y), mD.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.z), mD.v2._m), _mm_mul_ps(_mm_set_ps1(m.v2.w), mD.v3._m))));
			m.v3._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.x), mD.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.y), mD.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.z), mD.v2._m), _mm_mul_ps(_mm_set_ps1(m.v3.w), mD.v3._m))));
			// (mA * mB * mC * mD) * mE
			m.v0._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.x), mE.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.y), mE.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v0.z), mE.v2._m), _mm_mul_ps(_mm_set_ps1(m.v0.w), mE.v3._m))));
			m.v1._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.x), mE.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.y), mE.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v1.z), mE.v2._m), _mm_mul_ps(_mm_set_ps1(m.v1.w), mE.v3._m))));
			m.v2._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.x), mE.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.y), mE.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v2.z), mE.v2._m), _mm_mul_ps(_mm_set_ps1(m.v2.w), mE.v3._m))));
			m.v3._m = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.x), mE.v0._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.y), mE.v1._m), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(m.v3.z), mE.v2._m), _mm_mul_ps(_mm_set_ps1(m.v3.w), mE.v3._m))));
			return m;
		}

	};

	friend inline MmultMMMM operator * (const MmultMMM &t1, const Matrix &t2)
	{
		return MmultMMMM(t1, t2);
	}

	/*
	*
	*  End  M * M * M * M * M  Proxy Structs
	*
	*/

	
public:

	union {
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};
		struct
		{
			// ROW 0
			float m0;
			float m1;
			float m2;
			float m3;

			// ROW 1
			float m4;
			float m5;
			float m6;
			float m7;

			// ROW 2
			float m8;
			float m9;
			float m10;
			float m11;

			// ROW 3
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};

private:
	template<typename T> const void setRotZMatrix(const T Z_Radians) {};
	template<typename T> const Matrix& Matrix::operator/=(const T t) {};
};

#endif  // Matrix.h
