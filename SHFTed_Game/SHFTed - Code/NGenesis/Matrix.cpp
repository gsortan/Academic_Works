/*

- Note that currently it does not support error checking for sizes
	- IE) If you assign a value to element 4 in a 3x3, it'll work, just wont be used for certain calculations
-	Only multiplication, determinants and inverse use the matrix size

- Remember, all rotation matricies have a determinant of one
	- Something to keep in mind if it's necessary to use sometime in the future
	- We could also probably add a check to see if it's a rotation matrix and then inverse it by transposing instead
*/

#include "Matrix.h"

Matrix::Matrix()
{
	//Defaults to 4x4

	for (unsigned int i = 0; i < 16; ++i)
	{
		_element[i] = 0;
	}

	_column = 4;
	_row = 4;
}

Matrix::Matrix(Vector3f vector)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		_element[i] = 0;
	}

	_element[0] = vector.getX();
	_element[4] = vector.getY();
	_element[8] = vector.getZ();
	_element[12] = 1.0f;

	_column = 4;
	_row = 1;
}

Matrix::Matrix(Vector3f rotate, Vector3f translation, Vector3f scale)
{
	makeHomogenous(rotate, translation, scale);
}

Matrix::~Matrix()
{
}

void Matrix::makeHomogenous(Vector3f rotate, Vector3f translation, Vector3f scale)
{

	if (rotate.getX() == 0 && rotate.getY() == 0 && rotate.getZ() == 0) //If rotations are 0 then we don't need to rotate now do we?
	{
		_element[0] = scale.getX();
		_element[1] = 0.0f;
		_element[2] = 0.0f;		

		_element[4] = 0.0f;
		_element[5] = scale.getY();
		_element[6] = 0.0f;		

		_element[8] = 0.0f;
		_element[9] = 0.0f;
		_element[10] = scale.getZ();	
	}
	else
	{
		Matrix xRotation;
		Matrix yRotation;
		Matrix zRotation;
		Matrix scaleMatrix;
	
		xRotation.setSize(3, 3);
		yRotation.setSize(3, 3);
		zRotation.setSize(3, 3);
		scaleMatrix.setSize(3, 3);

		float currentCos = cos(mDegToRad(rotate.getX()));
		float currentSin = sin(mDegToRad(rotate.getX()));

		xRotation.setElement(0, 1.0f);
		xRotation.setElement(5, currentCos);
		xRotation.setElement(6, -currentSin);
		xRotation.setElement(9, currentSin);
		xRotation.setElement(10, currentCos);

		currentCos = cos(mDegToRad(rotate.getY()));
		currentSin = sin(mDegToRad(rotate.getY()));

		yRotation.setElement(0, currentCos);
		yRotation.setElement(2, currentSin);
		yRotation.setElement(5, 1.0f);
		yRotation.setElement(8, -currentSin);
		yRotation.setElement(10, currentCos);

		currentCos = cos(mDegToRad(rotate.getZ()));
		currentSin = sin(mDegToRad(rotate.getZ()));

		zRotation.setElement(0, currentCos);
		zRotation.setElement(1, -currentSin);
		zRotation.setElement(4, currentSin);
		zRotation.setElement(5, currentCos);
		zRotation.setElement(10, 1.0f);

		scaleMatrix.setElement(0, scale.getX());
		scaleMatrix.setElement(5, scale.getY());
		scaleMatrix.setElement(10, scale.getZ());
		scaleMatrix.setElement(15, 1.0f);

		Matrix rotationMatrix;
		rotationMatrix.setSize(3, 3);
		rotationMatrix = zRotation.multiply(yRotation);
		rotationMatrix.setSize(3, 3);
		rotationMatrix = rotationMatrix.multiply(xRotation);
		rotationMatrix.setSize(3, 3);
		rotationMatrix = scaleMatrix.multiply(rotationMatrix);
		rotationMatrix.setSize(3, 3);

		_element[0] = rotationMatrix.getElement(0);
		_element[1] = rotationMatrix.getElement(1);
		_element[2] = rotationMatrix.getElement(2);		

		_element[4] = rotationMatrix.getElement(4);
		_element[5] = rotationMatrix.getElement(5);
		_element[6] = rotationMatrix.getElement(6);		

		_element[8] = rotationMatrix.getElement(8);
		_element[9] = rotationMatrix.getElement(9);
		_element[10] = rotationMatrix.getElement(10);		
	}

	_element[3] = translation.getX();
	_element[7] = translation.getY();
	_element[11] = translation.getZ();

	_element[12] = 0.0f;
	_element[13] = 0.0f;
	_element[14] = 0.0f;
	_element[15] = 1.0f;
	
	_column = 4;
	_row = 4;

	//clean();
}

void Matrix::makeHomogenousV2(Matrix rotationMatrix, Vector3f translation, Vector3f scale)
{
	Matrix scaleMatrix;
	
	scaleMatrix.setSize(3, 3);

	scaleMatrix.setElement(0, scale.getX());
	scaleMatrix.setElement(5, scale.getY());
	scaleMatrix.setElement(10, scale.getZ());
	scaleMatrix.setElement(15, 1.0f);

	_element[0] = rotationMatrix.getElement(0);
	_element[1] = rotationMatrix.getElement(1);
	_element[2] = rotationMatrix.getElement(2);
	_element[3] = translation.getX();

	_element[4] = rotationMatrix.getElement(4);
	_element[5] = rotationMatrix.getElement(5);
	_element[6] = rotationMatrix.getElement(6);
	_element[7] = translation.getY();

	_element[8] = rotationMatrix.getElement(8);
	_element[9] = rotationMatrix.getElement(9);
	_element[10] = rotationMatrix.getElement(10);
	_element[11] = translation.getZ();

	_element[12] = 0.0f;
	_element[13] = 0.0f;
	_element[14] = 0.0f;
	_element[15] = 1.0f;

	_column = 4;
	_row = 4;;
}

void Matrix::setSize(unsigned int column, unsigned int row)
{
	_column = column;
	_row = row;
}

unsigned int Matrix::getSize(unsigned int element) //0 for column, 1 for row
{
	if (element == NG_COLUMN)
	{
		return _column;
	}
	else
	{
		return _row;
	}
}

void Matrix::setElement(unsigned int index, float value)
{
	_element[index] = value;
}

float Matrix::getElement(unsigned int index)
{
	return _element[index];
}

void Matrix::set(float* elements)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		_element[i] = elements[i];
	}
}

float* Matrix::get()
{
	return _element;
}

Matrix Matrix::getRotationMatrix() 
{
	Matrix result = *this;
	result.setSize(3, 3);

	return result;
}

Vector3f Matrix::getTranslationVector() 
{
	Vector3f result = Vector3f(_element[3], _element[7], _element[11]);

	return result;
}

Vector3f Matrix::getVector() 
{
	Vector3f result = Vector3f(_element[0], _element[4], _element[8]);

	return result;
}

float* Matrix::getRow(unsigned int row) //Returns the matrix in a float array. Does not account for size
{
	float result[4];
	unsigned int startingPoint = row * 4;

	result[0] = _element[startingPoint];
	result[1] = _element[++startingPoint];
	result[2] = _element[++startingPoint];
	result[3] = _element[++startingPoint];

	return result;
}

Matrix Matrix::add(Matrix &otherMatrix)
{
	Matrix result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.setElement(i, _element[i] + otherMatrix.getElement(i));
	}

	return result;
}

Matrix Matrix::subtract(Matrix &otherMatrix)
{
	Matrix result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.setElement(i, _element[i] - otherMatrix.getElement(i));
	}

	return result;
}

Matrix Matrix::multiply(Matrix &otherMatrix)
{
	Matrix result;

	if (_row == otherMatrix.getSize(NG_COLUMN))
	{
		for (unsigned int i = 0; i < 16; ++i)
		{
			unsigned int startColumn = i % 4;
			unsigned int startRow;	

			if (i < 4)
			{
				startRow = 0;
			}
			else if (i < 8)
			{
				startRow = 4;
			}
			else if (i < 12)
			{
				startRow = 8;
			}
			else
			{
				startRow = 12;
			}

			result.setElement(i, _element[startRow] * otherMatrix.getElement(startColumn) 
							   + _element[startRow + 1] * otherMatrix.getElement(startColumn + 4)
							   + _element[startRow + 2] * otherMatrix.getElement(startColumn + 8)
							   + _element[startRow + 3] * otherMatrix.getElement(startColumn + 12));
		}
	}
	else
	{
		std::cerr << "ERROR: CANNOT MULTIPLY MATRIX" << std::endl;
	}	

	//result.clean();

	return result;
}

Vector3f Matrix::multiply(Vector3f &vector) //4x4 only
{
	Vector3f result;

	result.setX(_element[0] * vector.getX() + _element[1] * vector.getY() + _element[2] * vector.getZ() + _element[3] * 1);
	result.setY(_element[4] * vector.getX() + _element[5] * vector.getY() + _element[6] * vector.getZ() + _element[7] * 1);
	result.setZ(_element[8] * vector.getX() + _element[9] * vector.getY() + _element[10] * vector.getZ() + _element[11] * 1);

	return result;
}

Matrix Matrix::multiply(float scalar)
{
	Matrix result;

	for (unsigned int i = 0; i < 16; ++i)
	{
		result.setElement(i, _element[i] * scalar);
	}

	return result;
}

Matrix Matrix::getInverse()
{
	Matrix result;

	if (_column == _row)
	{
		float determinant = getDeterminant();

		if (_column == 4 || determinant != 0)
		{
			if (_column == 2)
			{
				result.setElement(0, _element[5]);
				result.setElement(1, -_element[1]);
				result.setElement(4, -_element[4]);
				result.setElement(5, _element[0]);

				result = result.multiply(1 / determinant);
			}
			else if (_column == 3)
			{
				result.setElement(0, _element[5] * _element[10] - _element[6] * _element[9]);
				result.setElement(1, _element[2] * _element[9] - _element[1] * _element[10]);
				result.setElement(2, _element[1] * _element[6] - _element[2] * _element[5]);

				result.setElement(4, _element[6] * _element[8] - _element[4] * _element[10]);
				result.setElement(5, _element[0] * _element[10] - _element[2] * _element[8]);
				result.setElement(6, _element[2] * _element[4] - _element[0] * _element[6]);

				result.setElement(8, _element[4] * _element[9] - _element[5] * _element[8]);
				result.setElement(9, _element[1] * _element[8] - _element[0] * _element[9]);
				result.setElement(10, _element[0] * _element[5] - _element[1] * _element[4]);

				result = result.multiply(1 / determinant);
			}
			else if (_column == 4)
			{

				result = *this;
				result.transpose();

				Vector3f newVector;
				newVector.setX(-(Vector3f(result.getElement(0), result.getElement(1), result.getElement(2)).dot(getTranslationVector())));
				newVector.setY(-(Vector3f(result.getElement(4), result.getElement(5), result.getElement(6)).dot(getTranslationVector())));
				newVector.setZ(-(Vector3f(result.getElement(8), result.getElement(9), result.getElement(10)).dot(getTranslationVector())));

				result.setElement(3, newVector.getX());
				result.setElement(7, newVector.getY());
				result.setElement(11, newVector.getZ());

				result.setElement(12, 0.0f);
				result.setElement(13, 0.0f);
				result.setElement(14, 0.0f);
				result.setElement(15, 1.0f);
			}
		}
		else
		{
			std::cerr << "ERROR: CANNOT CALCULATE DETERMANANT" << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR: CANNOT CALCULATE DETERMANANT" << std::endl;
	}

	return result;
}

float Matrix::getDeterminant()
{
	if (_column == _row)
	{
		if (_column == 2) 
		{
			return _element[0] * _element[5] - _element[1] * _element[4];
		}
		else if (_column == 3) 
		{
			return	  _element[0] * _element[5] * _element[10]
					+ _element[1] * _element[6] * _element[8]
					+ _element[2] * _element[4] * _element[9]
					- _element[2] * _element[5] * _element[8]
					- _element[1] * _element[4] * _element[10]
					- _element[0] * _element[6] * _element[9];
		}
		else if (_column == 4) 
		{
			return	  _element[0] * _element[5] * _element[10] * _element[15]
					+ _element[0] * _element[6] * _element[11] * _element[13]
					+ _element[0] * _element[7] * _element[9] * _element[14]

					+ _element[1] * _element[4] * _element[11] * _element[14]
					+ _element[1] * _element[6] * _element[8] * _element[15]
					+ _element[1] * _element[7] * _element[10] * _element[12]

					+ _element[2] * _element[4] * _element[9] * _element[15]
					+ _element[2] * _element[5] * _element[11] * _element[12]
					+ _element[2] * _element[7] * _element[8] * _element[13]

					+ _element[3] * _element[4] * _element[10] * _element[13]
					+ _element[3] * _element[5] * _element[8] * _element[14]
					+ _element[3] * _element[6] * _element[9] * _element[12]

					- _element[0] * _element[5] * _element[11] * _element[14]
					- _element[0] * _element[6] * _element[9] * _element[15]
					- _element[0] * _element[7] * _element[10] * _element[13]

					- _element[1] * _element[4] * _element[10] * _element[15]
					- _element[1] * _element[6] * _element[11] * _element[12]
					- _element[1] * _element[7] * _element[8] * _element[14]

					- _element[2] * _element[4] * _element[11] * _element[13]
					- _element[2] * _element[5] * _element[8] * _element[15]
					- _element[2] * _element[7] * _element[9] * _element[12]

					- _element[3] * _element[4] * _element[9] * _element[14]
					- _element[3] * _element[5] * _element[10] * _element[12]
					- _element[3] * _element[6] * _element[8] * _element[13];
		}
	}
	else
	{
		return -1;
	}
}

float Matrix::getTrace()
{
	float result;

	result = _element[0] + _element[5] + _element[10] + 1;

	return result;
}

void Matrix::setIdentity()
{
	_element[0] = 1.0f;
	_element[5] = 1.0f;
	_element[10] = 1.0f;
	_element[15] = 1.0f;
}

void Matrix::transpose()
{
	float saved;
	
	if (_column == 2)
	{
		saved = _element[1];
		_element[1] = _element[4];
		_element[4] = saved;
	}
	else if (_column == 3)
	{
		saved = _element[1];
		_element[1] = _element[4];
		_element[4] = saved;

		saved = _element[2];
		_element[2] = _element[8];
		_element[8] = saved;

		saved = _element[6];
		_element[6] = _element[9];
		_element[9] = saved;
	}
	else if (_column == 4)
	{
		saved = _element[1];
		_element[1] = _element[4];
		_element[4] = saved;

		saved = _element[2];
		_element[2] = _element[8];
		_element[8] = saved;

		saved = _element[3];
		_element[3] = _element[12];
		_element[12] = saved;

		saved = _element[6];
		_element[6] = _element[9];
		_element[9] = saved;

		saved = _element[7];
		_element[7] = _element[13];
		_element[13] = saved;

		saved = _element[11];
		_element[11] = _element[14];
		_element[14] = saved;
	}
}

void Matrix::print()
{
	std::cout << _element[0] << "	" << _element[1] << "	" << _element[2] << "	" << _element[3] << std::endl;
	std::cout << _element[4] << "	" << _element[5] << "	" << _element[6] << "	" << _element[7] << std::endl;
	std::cout << _element[8] << "	" << _element[9] << "	" << _element[10] << "	" << _element[11] << std::endl;
	std::cout << _element[12] << "	" << _element[13] << "	" << _element[14] << "	" << _element[15] << std::endl;
}