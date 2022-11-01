#pragma once

class Vec3 {
public:
	Vec3();

	double& operator [] (int idx)
	{
		return mData[idx];
	}

private:
	double mData[3];
};


class Mat3 {
public:
	Mat3();

private:
	Vec3 mData[3];
};