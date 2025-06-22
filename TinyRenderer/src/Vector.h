#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
	float x;
	float y;
} Vector2f;

typedef struct  
{
	float x;
	float y;
	float z;
} Vector3f;

Vector3f RotateX(Vector3f point, float angle);
Vector3f RotateY(Vector3f point, float angle);
Vector3f RotateZ(Vector3f point, float angle);

#endif // !VECTOR_H
