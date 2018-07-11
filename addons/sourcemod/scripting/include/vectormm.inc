//#if defined _vector_included
//  #endinput
//#endif
//#define _vector_included

#define RAND_MAX 		32767	// Tyvm cstdlib
#define VALVE_RAND_MAX 	0x7FFF
#define VEC_T_NAN 		view_as< float >(0x7FC00000)

methodmap Vector < DataPack
{
	public Vector( float x = 0.0, float y = 0.0, float z = 0.0 )
	{
		DataPack pack = new DataPack();
		pack.WriteFloat(x);
		pack.WriteFloat(y);
		pack.WriteFloat(z);
		return view_as< Vector >(pack);
	}

	public static Vector AsRandom( float minVal, float maxVal )
	{
		DataPack pack = new DataPack();
		pack.WriteFloat(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		pack.WriteFloat(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		pack.WriteFloat(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		return view_as< Vector >(pack);
	}

	public static Vector AsVector2D( float x = 0.0, float y = 0.0 )	// Idk why you'd want this, but here
	{
		DataPack pack = new DataPack();
		pack.WriteFloat(x);
		pack.WriteFloat(y);
		return view_as< Vector >(pack);
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
			this.Reset();
			return this.ReadFloat();
		}
		public set( const float i )
		{
			this.Reset();
			this.WriteFloat(i);
		}
	}

	property float y
	{
		public get()
		{
			this.Reset();
			this.ReadFloat();
			return this.ReadFloat();
		}
		public set( const float i )
		{
			this.Reset();
			this.ReadFloat();
			this.WriteFloat(i);
		}
	}

	property float z
	{
		public get()
		{
			this.Reset();
			this.ReadFloat();
			this.ReadFloat();
			return this.ReadFloat();
		}
		public set( const float i )
		{
			this.Reset();
			this.ReadFloat();
			this.ReadFloat();	// .-.
			this.WriteFloat(i);
		}
	}

	public void Random( float minVal, float maxVal )
	{
		this.Reset(true);
		this.WriteFloat(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		this.WriteFloat(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
		this.WriteFloat(minVal + ((GetRandomFloat(0.0, float(RAND_MAX)) / VALVE_RAND_MAX)) * (maxVal - minVal));
	}

	public bool IsZero( float tolerance = 0.01 )
	{
		return (this.x > -tolerance && this.x < tolerance && this.y > -tolerance && this.y < tolerance && this.z > -tolerance && this.z < tolerance);
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
		this.Reset(true);
		this.WriteFloat(0.0);
		this.WriteFloat(0.0);
		this.WriteFloat(0.0);
	}

	public void Clear()
	{
		this.Zero();
	}

	public float Length()
	{
		float v[3];
		this.CopyToArray(v);
		return GetVectorLength(v);
	}
	public float LengthSqr()
	{
		return (this.x * this.x + this.y * this.y + this.z * this.z);
	}

	public float DistTo( const Vector vOther )
	{
		float v[3];
		this.CopyToArray(v)

		float v2[3];
		vOther.CopyToArray(v2);

		return GetVectorDistance(v, v2);
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

		this.x = v[0];
		this.y = v[1];
		this.z = v[2];
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
			( this.x >= boxmin.x ) && ( this.x <= boxmax.x) &&
			( this.y >= boxmin.y ) && ( this.y <= boxmax.y) &&
			( this.z >= boxmin.z ) && ( this.z <= boxmax.z)
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

// :c

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


// WARNING, DO NOT USE THESE OPERATORS UNLESS YOU KNOW WHAT YOU ARE DOING. 
// DO NOT EVER USE A '+=', '-=', '*=', OR '/=' OPERATOR. YOU ARE NOT DEALLOCATING MEMORY BEFOREHAND.

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