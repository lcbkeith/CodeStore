#pragma once
#include <string>
#include <vector>

const double DOUBLE_ERROR = 0.000001;
int CompareFloat(float data1, float data2)
{
	if (fabs(data1 - data2) <= DOUBLE_ERROR)
	{
		return 0;
	}
	else
	{
		if (data1 - data2 > DOUBLE_ERROR)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
}

class CVector3
{
public:
	CVector3()
	{
		x_ = 0;
		y_ = 0;
		z_ = 0;
	}

	CVector3(float x, float y, float z)
	{
		x_ = x;
		y_ = y;
		z_ = z;
	}

	CVector3(const CVector3& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
	}

	~CVector3() { }

	float x() const { return x_; }
	float y() const { return y_; }
	float z() const { return z_; }

	void set_x(float x) { x_ = x; }
	void set_y(float y) { y_ = y; }
	void set_z(float z) { z_ = z; }

	void Clear()
	{
		x_ = 0.0f;
		y_ = 0.0f;
		z_ = 0.0f;
	}

	CVector3& operator += (const CVector3& v)
	{
		x_ += v.x();
		y_ += v.y();
		z_ += v.z();
		return *this;
	}

	CVector3& operator -= (const CVector3& v)
	{
		x_ -= v.x();
		y_ -= v.y();
		z_ -= v.z();
		return *this;
	}

	CVector3& operator *= (float f)
	{
		x_ *= f;
		y_ *= f;
		z_ *= f;
		return *this;
	}

	CVector3& operator /= (float f)
	{
		return *this *= (1.0f / f);
	}


	CVector3 operator + (const CVector3& v) const
	{
		CVector3 result(x_ + v.x_, y_ + v.y_, z_ + v.z_);
		return result;
	}

	CVector3 operator - (const CVector3& v) const
	{
		CVector3 result(x_ - v.x_, y_ - v.y_, z_ - v.z_);
		return result;
	}

	CVector3 operator * (float f) const
	{
		CVector3 result(x_ * f, y_ * f, z_ * f);
		return result;
	}

	CVector3 operator / (float f) const
	{
		return *this * (1.0f / f);
	}

	CVector3 operator -() const
	{
		return CVector3(-x_, -y_, -z_);
	}

	bool operator == (const CVector3& v) const
	{
		return  CompareFloat(v.x_, x_) == 0 && CompareFloat(v.z_, z_) == 0;
	}

	bool operator != (const CVector3& v) const
	{
		return !(*this == v);
	}

	float length() const
	{
		return sqrt(x_ * x_ + z_ * z_);
	}

	float sqr_length() const
	{
		return x_ * x_ + z_ * z_;
	}

	CVector3 normalized() const
	{
		if (zero() == true)
		{
			return *this;
		}
		float f = length();
		return *this / f;
	}

	void rotate(float angle)
	{
		angle += ::atan2f(z_, x_);
		float len = length();
		x_ = len * ::cos(angle);
		z_ = len * ::sin(angle);
	}

	//获取角度[0,2π)
	float toangle()
	{
		float f = ::atan2f(z_, x_);
		return z_ < 0 ? f + 2 * 3.1415926 : f;
	}

	//角度转换成矢量
	//f[0,2π)
	void fromangle(float f)
	{
		x_ = ::cos(f);
		z_ = ::sin(f);
	}

	bool zero() const
	{
		return (x_ == 0 && z_ == 0);
	}

private:
	float x_;
	float y_;
	float z_;
};