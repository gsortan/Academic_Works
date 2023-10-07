#include "Camera.h"

Quaternion Camera::_position = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
Vector3f Camera::_translation = Vector3f(0.0f, 0.0f, 0.0f);

Camera::Camera()
{
	init();
}

Camera::~Camera()
{
}

void Camera::init()
{
	_initTranslation = Vector3f(0.0f, 25.0f, 75.0f); //Init position for back
	_translation = _initTranslation;
	_position = Quaternion(_translation);
	_rotationAngle = Vector3f(45.0f, 0.0f, 0.0f);
	_focusPos = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
	_distanceFromFocus = 125.0f;

	_leftScrolling = false;		
	_wheelScrolling = false;	
	_rightScrolling = false;	

	_mode = NG_CAMERA_CMR;

	_cameraAngleModifier = 2.0f; //Increase this number if you want camera rotating to be less sensitive. Default is 2
	_cameraScrollModifier = 25.0f; //Increase this number if you want scrolling to be less sensitive. Default is 50

	path = new Path();
	path ->setSpeed(0.005);
}

void Camera::setTranslation(Vector3f translation)
{
	_translation = translation;
}

void Camera::setRotationAngle(Vector3f angle)
{
	_rotationAngle = angle;
}

void Camera::setReferenceAngle(Vector3f angle)
{
	_referenceAngle = angle;
}

void Camera::setReferencePosition(Vector3f referencePosition)
{
	_referencePos = referencePosition;
}

void Camera::setFocus(Vector3f &position, Vector3f &rotation)
{
	_focusPos.setVector(position);
	_focusRotation = rotation;
}

void Camera::setScrolling(unsigned int value, bool state)
{
	if (value == NG_LEFT_MOUSE_BUTTON)
	{
		_leftScrolling = state;
	}
	else if (value == NG_MIDDLE_MOUSE_BUTTON)
	{
		_wheelScrolling = state;
	}
	else
	{
		_rightScrolling = state;
	}
}

void Camera::setMode(unsigned int mode)
{
	_mode = mode;
}

void Camera::moveCameraToLocationAndLookAtSomething(Vector3f position, Vector3f target, Vector3f up)
{
	gluLookAt(position.getX(), position.getY(), position.getZ(), target.getX(), target.getY(), target.getZ(), up.getX(), up.getY(), up.getZ());
}

Vector3f Camera::getInitTranslation()
{
	return _initTranslation;
}

Vector3f Camera::getTranslation()
{
	return _translation;
}

Vector3f Camera::getRotationAngle()
{
	return _rotationAngle;
}

Vector3f Camera::getReferenceAngle()
{
	return _referenceAngle;
}

Vector3f Camera::getReferencePosition()
{
	return _referencePos;
}

Vector3f Camera::getFocusPosition()
{
	return _focusPos.getVector();
}

Quaternion Camera::getPosition()
{
	return _position;
}

unsigned int Camera::getMode()
{
	return _mode;
}

void Camera::scrollHandler(float mouseCurrentX, float mouseCurrentY, float mouseReferenceX, float mouseReferenceY)
{	
	if (_leftScrolling == true) //Rotates the camera if alt and left are down
	{
		if (_mode == NG_CAMERA_FREE)
		{
			_rotationAngle.setX(_referenceAngle.getX() + (mouseCurrentY - mouseReferenceY) / _cameraAngleModifier);
			_rotationAngle.setY(_referenceAngle.getY() + (mouseCurrentX - mouseReferenceX) / _cameraAngleModifier);

			_position = Quaternion(_translation);
			_position = _position.rotate(_rotationAngle.getX(), NG_X);
			_position = _position.rotate(_rotationAngle.getY(), NG_Y);
		}
	}
	else if (_wheelScrolling == true) //Scrolls the camera if alt and wheel are down
	{
		if (_mode == NG_CAMERA_FREE)
		{
			_translation.setX(_referencePos.getX() + (mouseCurrentX - mouseReferenceX) / _cameraScrollModifier);
			_translation.setY(_referencePos.getY() - (mouseCurrentY - mouseReferenceY) / _cameraScrollModifier); //Needs opposite

			_position = Quaternion(_translation);
			_position = _position.rotate(_rotationAngle.getX(), NG_X);
			_position = _position.rotate(_rotationAngle.getY(), NG_Y);
		}
	}
	else if (_rightScrolling == true) //Zooms the camera if alt and right are down
	{
		if (_mode == NG_CAMERA_FREE)
		{
			_translation.setZ(_referencePos.getZ() + (mouseCurrentX - mouseReferenceX) / _cameraScrollModifier); //Compunds X and Y movement
			_translation.setZ(_translation.getZ() + (mouseCurrentY - mouseReferenceY) / _cameraScrollModifier);

			_position = Quaternion(_translation);
			_position = _position.rotate(_rotationAngle.getX(), NG_X);
			_position = _position.rotate(_rotationAngle.getY(), NG_Y);
		}
	}
}

void Camera::update(float aspX, float aspY, double nearPlane, double farPlane)
{
	gluPerspective(60.0, aspX / aspY, nearPlane, farPlane); //Sets perspective mode

	if (_mode == NG_CAMERA_FREE)
	{
		glTranslatef(_translation.getX(), _translation.getY(), _translation.getZ()); //Translates camera
		glRotatef(_rotationAngle.getX(), 1.0f, 0.0f, 0.0f);
		glRotatef(_rotationAngle.getY(), 0.0f, 1.0f, 0.0f);
	}
	else if (_mode == NG_CAMERA_THIRD_PERSON)
	{
		Quaternion displacement = _translation - _initTranslation;

		_position = Vector3f(sin(mDegToRad(_focusRotation.getY())) * -_initTranslation.getZ(), _translation.getY() + _focusPos.getY(), cos(mDegToRad(_focusRotation.getY())) * -_initTranslation.getZ());
		_position = _position.add(displacement); //Adds the displacement afterwards since we're essentially moving the "circle" of rotation

		gluLookAt(_position.getX(), _position.getY(), _position.getZ(),
				  _focusPos.getX(), _focusPos.getY(), _focusPos.getZ(), 
				  0.0f, 1.0f, 0.0f);
	}
	else if (_mode == NG_CAMERA_FIRST_PERSON)
	{
		_position = Vector3f(-_focusPos.getX(), -(_focusPos.getY() + 15.0f), -_focusPos.getZ()); //Hard coding an offset value. WHY NEGATIVE? No idea.

		glRotatef(180 - _focusRotation.getY(), 0.0f, 1.0f, 0.0f); //Rotates second cause we don't want it to move our position
		glTranslatef(_position.getX(), _position.getY(), _position.getZ()); //Translates camera first.
	}
	else if (_mode == NG_CAMERA_THIRD_PERSON_TARGET)
	{
		gluLookAt(_position.getX(), _position.getY(), _position.getZ(),
				  _focusPos.getX(), _focusPos.getY(), _focusPos.getZ(), 
				  0.0f, 1.0f, 0.0f);
	}
	else if (_mode == NG_CAMERA_FIRST_PERSON_TARGET)
	{
	}
	else if (_mode == NG_CAMERA_CMR)
	{
		path ->setActive(true);
		path ->setInfinite(true);

		_position = path ->update();
		
		gluLookAt(_position.getX(), _position.getY(), _position.getZ(),
				  _focusPos.getX(), _focusPos.getY(), _focusPos.getZ(),
				  1.0, 1.0, 1.0);
	}
}