#pragma once

#include "Vector3f.h"
#include "Conversion.h"
#include <iostream>

#define NG_COLUMN 0
#define NG_ROW 1

class Matrix
{
public:
	Matrix();
	Matrix(Vector3f vector);
	Matrix(Vector3f rotate, Vector3f translation, Vector3f scale);
	~Matrix();

	void makeHomogenous(Vector3f rotate, Vector3f translation, Vector3f scale);
	void makeHomogenousV2(Matrix rotationMatrix, Vector3f translation, Vector3f scale);

	void setSize(unsigned int column, unsigned int row);
	unsigned int getSize(unsigned int element); //0 for column, 1 for row

	void setElement(unsigned int index, float value);
	float getElement(unsigned int index);

	void set(float* elements);
	float* get();

	Matrix getRotationMatrix();
	Vector3f getTranslationVector();
	Vector3f getVector();

	float* getRow(unsigned int row);

	Matrix add(Matrix &otherMatrix);
	Matrix subtract(Matrix &otherMatrix);
	Matrix multiply(Matrix &otherMatrix);
	Vector3f multiply(Vector3f &vector);
	Matrix multiply(float scalar);

	Matrix getInverse();
	float getDeterminant();
	float getTrace();

	void setIdentity();
	void transpose();
	//void clean();

	void print();

private:
	float _element[16];

	unsigned int _column, _row;
};