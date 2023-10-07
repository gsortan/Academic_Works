#pragma once

#include "Quaternion.h"
#include "Include.h"
#include "Path.h"
#include "Model.h"

#define NG_LEFT_MOUSE_BUTTON 0
#define NG_MIDDLE_MOUSE_BUTTON 1
#define NG_RIGHT_MOUSE_BUTTON 2

#define NG_CAMERA_FREE 0 //When your camera is free to move around, maya style
#define NG_CAMERA_THIRD_PERSON 1 //When your camera is focusing on your character, third person
#define NG_CAMERA_FIRST_PERSON 2 //When your camera is on your character, first person
#define NG_CAMERA_THIRD_PERSON_TARGET 3 //When your camera is third person, but focusing on a target
#define NG_CAMERA_FIRST_PERSON_TARGET 4 //When your camera is first person, but focusing on a target
#define NG_CAMERA_THIRD_PERSON_SIDE 5 //When your camera is focusing on your character from the side
#define NG_CAMERA_CMR 6 //catmull-rom

class Camera
{
public:
	Camera();
	~Camera();

	void init();

	void setTranslation(Vector3f translation);
	void setRotationAngle(Vector3f angle);
	void setReferenceAngle(Vector3f angle);
	void setReferencePosition(Vector3f referencePosition);
	void setFocus(Vector3f &position, Vector3f &rotation);
	void setScrolling(unsigned int value, bool state);
	void setMode(unsigned int mode);

	void moveCameraToLocationAndLookAtSomething(Vector3f position, Vector3f target, Vector3f up);

	Vector3f getInitTranslation();
	static Vector3f getTranslation();
	Vector3f getRotationAngle();
	Vector3f getReferenceAngle();
	Vector3f getReferencePosition();
	Vector3f getFocusPosition();
	static Quaternion getPosition();
	unsigned int getMode();

	void scrollHandler(float mouseCurrentX, float mouseCurrentY, float mouseReferenceX, float mouseReferenceY);
	void update(float aspX, float aspY, double nearPlane, double farPlane);

	Path* path;

private:
	Vector3f _initTranslation; //How much the camera is translated by at first

	static Vector3f _translation; //Current position		
	Vector3f _rotationAngle; //Current angle

	Vector3f _referenceAngle; //Reference angle for rotating
	Vector3f _referencePos; //Reference position for scrolling

	Quaternion _focusPos; //Position for what you are looking at
	Vector3f _focusRotation; //Rotation for what you are looking at; used for stayuing behind things
	float _distanceFromFocus; //THe distance how far behind the focus you want to be (player char)
	static Quaternion _position; //Position when adjusted for rotations

	bool _leftScrolling; //Controls whether or not youre scrolling with the left button
	bool _wheelScrolling; //Controls whether or not youre scrolling with the mouse wheel		
	bool _rightScrolling; //Controls whether or not youre scrolling with the right button

	unsigned int _mode; //Controls your camera's mode

	float _cameraScrollModifier; //Amount used for scrolling the camera in the form Displacement (Pixels) / Modifier
	float _cameraAngleModifier; //Amount used for rotating the camera in the form Displacement (Pixels) / Modifier*/	
};