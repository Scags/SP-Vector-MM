#if defined _vectormm_included
  #endinput
#endif
#define _vectormm_included

#define RAND_MAX 		32767	// Tyvm cstdlib
#define VALVE_RAND_MAX 	0x7FFF
#define VEC_T_NAN 		view_as< float >(0x7FC00000)

// One day this will work
/*enum struct Vector
{
	float x;
	float y;
	float z;

	void Init(float X = 0.0, float Y = 0.0, float Z = 0.0)
	{
		this.x = X;
		this.y = Y;
		this.z = Z;
	}

	void Zero()
	{
		this.x = this.y = this.z = 0.0;
	}

	float Length()
	{
		return GetVectorLength(view_as< float >(this));	// Fuck lol
	}

	float LengthSqr()
	{
		return GetVectorLength(view_as< float >(this), true);
	}

	bool IsZero(float tolerance = 0.01)
	{
		return (-tolerance < this.x < tolerance && -tolerance < this.y < tolerance && -tolerance < this.z < tolerance);
	}

	float NormalizeInPlace()
	{
		return NormalizeVector(view_as< float >(this), view_as< float >(this));
	}

	bool IsLengthGreaterThan( float val )
	{
		return this.LengthSqr() > val * val;
	}

	bool IsLengthLessThan( float val )
	{
		return this.LengthSqr() < val * val;
	}

	float DistTo(const Vector vOther)
	{
		return GetVectorDistance(view_as< float >(this), view_as< float >(vOther));
	}

	float DistToSqr(const Vector vOther)
	{
		Vector delta;
		delta.x = this.x - vOther.x;
		delta.y = this.y - vOther.y;
		delta.z = this.z - vOther.z;
		return delta.LengthSqr();
	}

	void CopyToArray(float array[3])
	{
		array[0] = this.x;
		array[1] = this.y;
		array[2] = this.z;
	}

	void CopyFromArray(float array[3])
	{
		this.x = array[0];
		this.y = array[1];
		this.z = array[2];
	}

	void MulAdd(const Vector a, const Vector b, float scalar)
	{
		this.x = a.x + b.x * scalar;
		this.y = a.y + b.y * scalar;
		this.z = a.z + b.z * scalar;
	}

	float Dot(const Vector vOther)
	{
		return GetVectorDotProduct(view_as< float >(this), view_as< float >(vOther));
	}

	Vector Cross(const Vector vOther)
	{
		Vector v;
		GetVectorCrossProduct(view_as< float >(this), view_as< float >(vOther), view_as< float >(v));
		return v;
	}

	 bool WithinAABox( const Vector boxmin, const Vector boxmax )
	{
		return ( 
			( boxmin.x <= this.x <= boxmax.x) &&
			( boxmin.y <= this.y <= boxmax.y) &&
			( boxmin.z <= this.z <= boxmax.z)
		);
	}

	Vector Min( const Vector vOther )
	{
		Vector v;
		v.Init(this.x < vOther.x ? this.x : vOther.x, 
		this.y < vOther.y ? this.y : vOther.y, 
		this.z < vOther.z ? this.z : vOther.z);
		return v;
	}

	Vector Max( const Vector vOther )
	{
		Vector v;
		v.Init(this.x > vOther.x ? this.x : vOther.x, 
		this.y > vOther.y ? this.y : vOther.y, 
		this.z > vOther.z ? this.z : vOther.z);
		return v;
	}

	void Copy( Vector dst )
	{
		dst.x = this.x;
		dst.y = this.y;
		dst.z = this.z;
	}

	bool IsValid()
	{
		return IsFinite(this.x) && IsFinite(this.y) && IsFinite(this.z);
	}

	void InValidate()
	{
		this.x = this.y = this.z = VEC_T_NAN;
	}
}*/

methodmap Vector < ArrayList
{
	public Vector( float x = 0.0, float y = 0.0, float z = 0.0 )
	{
		ArrayList v = new ArrayList();
		v.Push(x);
		v.Push(y);
		v.Push(z);
		return view_as< Vector >(v);
	}

	public static Vector AsRandom( float minVal, float maxVal )
	{
		ArrayList v = new ArrayList();
		v.Push(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		v.Push(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		v.Push(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		return view_as< Vector >(v);
	}

	public static Vector AsVector2D( float x = 0.0, float y = 0.0 )	// Idk why you'd want this, but here
	{
		ArrayList v = new ArrayList();
		v.Push(x);
		v.Push(y);
		return view_as< Vector >(v);
	}

	public static Vector FromAngles( float fwd[3], float right[3], float up[3] )
	{
		float v[3];
		GetAngleVectors(v, fwd, right, up);
		return new Vector(v[0], v[1], v[2]);
	}

	property float x
	{
		public get()
		{
			return this.Get(0);
		}
		public set( const float i )
		{
			this.Set(0, i);
		}
	}

	property float y
	{
		public get()
		{
			return this.Get(1);
		}
		public set( const float i )
		{
			this.Set(1, i);
		}
	}

	property float z
	{
		public get()
		{
			return this.Get(2);
		}
		public set( const float i )
		{
			this.Set(2, i);
		}
	}

	public void Random( float minVal, float maxVal )
	{
		this.Set(0, minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		this.Set(1, minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		this.Set(2, minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
	}

	public bool IsZero( float tolerance = 0.01 )
	{
		return (-tolerance < this.x < tolerance && -tolerance < this.y < tolerance && -tolerance < this.z < tolerance);
	}

	public void Negate()
	{
		this.x = -this.x;
		this.y = -this.y;
		this.z = -this.z;
	}

	public void CopyToArray( float array[3] )
	{
		array[0] = this.x;
		array[1] = this.y;
		array[2] = this.z;
	}

	public void CopyFromArray( float array[3] )
	{
		this.x = array[0];
		this.y = array[1];
		this.z = array[2];
	}

	public void Zero()
	{
		this.x = this.y = this.z = 0.0;
	}

	public void Clear()
	{
		this.Zero();
	}

	public float Length()
	{
		return SquareRoot(this.x * this.x + this.y * this.y + this.z * this.z);
	}

	public float LengthSqr()
	{
		return (this.x * this.x + this.y * this.y + this.z * this.z);
	}

	public float DistTo( const Vector vOther )
	{
		Vector delta = new Vector(this.x - vOther.x, this.y - vOther.y, this.z - vOther.z);
		float length = delta.Length();
		delete delta;
		return length;
	}

	public float DistToSqr(const Vector vOther)
	{
		Vector delta = new Vector(this.x - vOther.x, this.y - vOther.y, this.z - vOther.z);
		float length = delta.LengthSqr();
		delete delta;
		return length;
	}

	public void MulAdd( const Vector a, const Vector b, float scalar )
	{
		this.x = a.x + b.x * scalar;
		this.y = a.y + b.y * scalar;
		this.z = a.z + b.z * scalar;
	}

	public float Dot( const Vector vOther )
	{
		float v[3];
		this.CopyToArray(v);
		float v2[3];
		vOther.CopyToArray(v2);

		return GetVectorDotProduct(v, v2);
	}

	public Vector Cross( const Vector vOther )
	{
		float v[3];
		this.CopyToArray(v);
		float v2[3];
		vOther.CopyToArray(v2);

		GetVectorCrossProduct(v, v2, v2);
		return new Vector(v2[0], v2[1], v2[2]);
	}

	public float NormalizeInPlace()
	{
		float v[3];
		this.CopyToArray(v);
		float dist = NormalizeVector(v, v);
		this.CopyFromArray(v);
		return dist;
	}

	public Vector Clone()
	{
		return new Vector(this.x, this.y, this.z);
	}

	public Vector Normalized()
	{
		Vector vector = this.Clone();
		vector.NormalizeInPlace();
		return vector;
	}

	public void Angles( float angle[3] )
	{
		float v[3];
		this.CopyToArray(v);
		GetVectorAngles(v, angle);
	}

	public bool IsLengthGreaterThan( float val )
	{
		return this.LengthSqr() > val * val;
	}

	public bool IsLengthLessThan( float val )
	{
		return this.LengthSqr() < val * val;
	}

	public bool WithinAABox( const Vector boxmin, const Vector boxmax )
	{
		return ( 
			( boxmin.x <= this.x <= boxmax.x) &&
			( boxmin.y <= this.y <= boxmax.y) &&
			( boxmin.z <= this.z <= boxmax.z)
		);
	}

	public Vector Min( const Vector vOther )
	{
		return new Vector(this.x < vOther.x ? this.x : vOther.x, 
		this.y < vOther.y ? this.y : vOther.y, 
		this.z < vOther.z ? this.z : vOther.z);
	}

	public Vector Max( const Vector vOther )
	{
		return new Vector(this.x > vOther.x ? this.x : vOther.x, 
		this.y > vOther.y ? this.y : vOther.y, 
		this.z > vOther.z ? this.z : vOther.z);
	}

	public void Copy( Vector dst )
	{
		dst.x = this.x;
		dst.y = this.y;
		dst.z = this.z;
	}

	public bool IsValid()
	{
		return IsFinite(this.x) && IsFinite(this.y) && IsFinite(this.z);
	}

	public void InValidate()
	{
		this.x = this.y = this.z = VEC_T_NAN;
	}
};

// "Operator, Long Distance Please"

stock bool operator==(Vector oper1, Vector oper2)
{
	return ((oper1.x == oper2.x) &&
			(oper1.y == oper2.y) &&
			(oper1.z == oper2.z));
}

stock bool operator!=(Vector oper1, Vector oper2)
{
	return (oper1.x != oper2.x) || (oper1.y != oper2.y) || (oper1.z != oper2.z);
}

stock void operator++(Vector oper)
{
	oper.x++;
	oper.y++;
	oper.z++;
}

stock void operator--(Vector oper)
{
	oper.x--;
	oper.y--;
	oper.z--;
}

// For the love of God please don't use +=, -= or anything of the like

stock Vector operator-(Vector oper1)
{
	Vector v = oper1.Clone();
	v.Negate();
	return v;
}

stock Vector operator-(Vector oper1, Vector oper2)
{
	Vector v = oper1.Clone();
	v.x -= oper2.x;
	v.y -= oper2.y;
	v.z -= oper2.z;
	return v;
}

stock Vector operator-(Vector oper1, float oper2)
{
	Vector v = oper1.Clone();
	v.x -= oper2;
	v.y -= oper2;
	v.z -= oper2;
	return v;
}

stock Vector operator+(Vector oper1, Vector oper2)
{
	Vector v = oper1.Clone();
	v.x += oper2.x;
	v.y += oper2.y;
	v.z += oper2.z;
	return v;
}

stock Vector operator+(Vector oper1, float oper2)
{
	Vector v = oper1.Clone();
	v.x += oper2;
	v.y += oper2;
	v.z += oper2;
	return v;
}

stock Vector operator*(Vector oper1, float oper2)
{
	Vector v = oper1.Clone();
	v.x *= oper2;
	v.y *= oper2;
	v.z *= oper2;
	return v
}

stock Vector operator*(Vector oper1, Vector oper2)
{
	Vector v = oper1.Clone();
	v.x *= oper2.x;
	v.y *= oper2.y;
	v.z *= oper2.z;
	return v;
}

stock Vector operator/(Vector oper1, float oper2)
{
	Vector v = oper1.Clone();
	oper1.x /= oper2;
	oper1.y /= oper2;
	oper1.z /= oper2;
	return v;
}

stock Vector operator/(Vector oper1, Vector oper2)
{
	Vector v = oper1.Clone();
	v.x /= oper2;
	v.y /= oper2;
	v.z /= oper2;
	return v;
}

// Does this even work?
stock bool IsFinite( float f )
{
	return ((view_as< Address >(f) & view_as< Address >(0x7F800000)) != view_as< Address >(0x7F800000));
}