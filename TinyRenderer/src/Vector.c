#include <math.h>
#include "Vector.h"

Vector3f RotateX(Vector3f point, float angle)
{
	Vector3f res = { point.x, point.y * cos(angle) - point.z * sin(angle), point.y * sin(angle) + point.z * cos(angle) };
	return res;
}

Vector3f RotateY(Vector3f point, float angle)
{
	Vector3f res = { point.x * cos(angle) - point.z * sin(angle), point.y, point.x * sin(angle) + point.z * cos(angle) };
	return res;
}

Vector3f RotateZ(Vector3f point, float angle)
{
	Vector3f res = { point.x * cos(angle) - point.y * sin(angle), point.x * sin(angle) + point.y * cos(angle), point.z };
	return res;
}
