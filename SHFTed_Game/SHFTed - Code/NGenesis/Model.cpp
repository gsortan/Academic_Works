//This class deals with ONLY the loading, drawing and transformation of models

#include "Model.h"

std::vector<Vector3f> Model::_lightPos; //Static variables need to be declared outside of scope
std::vector<Vector3f> Model::_lightColor; 
Vector3f Model::_eyePos = Vector3f(0, 0, 0); //Static variables need to be declared outside of scope
float Model::_globalLightIntensity = 1.0f;
float Model::_lightModelViewMatrix[];
float Model::_lightProjectionMatrix[];
float Model::_lightModelViewProjectionMatrix[];
Matrix* Model::_reallyHackyLightModelViewProjectionMatrix = new Matrix();

Model::Model() //Default constructor
{
	initVariables();
}

Model::Model(const std::string &directory, const std::string fileName, unsigned int type) //Constructor that auto calls the load model function
{
	initVariables();

	if (type == NG_OBJ)
	{
		loadOBJ(directory, fileName);
	}
	else if (type == NG_OBJS)
	{
		loadOBJS(directory, fileName);
	}
}

Model::Model(const std::string &directory, const std::string modelName, unsigned int type, char* textureName) //Constructor that auto calls both loads
{
	initVariables();

	if (type == NG_OBJ)
	{
		loadOBJ(directory, modelName);
	}
	else if (type == NG_OBJS)
	{
		loadOBJS(directory, modelName);
	}

	_texture[0].load(textureName);
}

Model::~Model() //Destructor
{

}

void Model::initVariables()
{
	_color.r = 1.0f;
	_color.g = 1.0f;
	_color.b = 1.0f;
	_color.a = 1.0f;


	_vShader = new Shader("Vertex_Easy.cg", "vFragLightingShadow");
	_fShader = new Shader("Fragment_Easy.cg", "fLightingGooch");

	_previousPosition = Vector3f(0.0f, 0.0f, 0.0f);
	_position = Vector3f(0.0f, 0.0f, 0.0f);
	_velocity = Vector3f(0.0f, 0.0f, 0.0f);
	_acceleration = Vector3f(0.0f, 0.0f, 0.0f);
	_speed = 0.0f;
	_scale = Vector3f(1.0f, 1.0f, 1.0f);
	_rotate = Vector3f(0.0f, 0.0f, 0.0f);

	_hitSize = 1.0f;

	transformations.makeHomogenous(_rotate, _position, _scale);

	_modelSizeMin = Vector3f(9001.0f, 9001.0f, 9001.0f);
	_modelSizeMax = Vector3f(-9001.0f, -9001.0f, -9001.0f);
	_adjustedModelSizeMin = Vector3f(9001.0f, 9001.0f, 9001.0f);
	_adjustedModelSizeMax = Vector3f(-9001.0f, -9001.0f, -9001.0f);

	_shaderToggle[0] = true;
	_shaderToggle[1] = true;
	_shaderToggle[2] = true;
	_shaderToggle[3] = true;

	_ke = 0.5f; 
	_ka = 0.2f;
	_ks = 1.0f;
	_kd = 1.0f;
	_shininess = 50.0f;
	_uvOffset = 0.0f;

	_active = true;
	timer = new Timer();

	_linkType = NG_NO_LINK;

	_notificationCounter = 0;

	_path = new Path();
}

void Model::initDrawBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER, _numOfVertices * sizeof(float), _vertexInfo, GL_STATIC_DRAW);
	GLvoid* vertexBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, _texBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numOfVerticesTexture * sizeof(float), _vertexTextureInfo, GL_STATIC_DRAW);
	GLvoid* textureBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, _normBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numOfVerticesNormal * sizeof(float), _vertexNormalInfo, GL_STATIC_DRAW);
	GLvoid* normalBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	glNormalPointer(GL_FLOAT, 0, NULL);

	memcpy(vertexBuffer, _vertexInfo, _numOfVertices * 4);
	memcpy(textureBuffer, _vertexTextureInfo, _numOfVerticesTexture * 4);
	memcpy(normalBuffer, _vertexNormalInfo, _numOfVerticesNormal * 2);
}

void Model::loadOBJ(const std::string &directory, const std::string &modelName) //Loads in an obj
{
	std::cout << "Loading Object: " << modelName << "." << std::endl;

	std::string keyword; //Keyword used for comparisons
	std::ifstream file; //Creates an input stream of the file
	file.open(directory + modelName); //If found, stores information in the ifstream

	vertex tempVertex; //Temp vertex object to store values as we parse them
	triangle tempFace; //Temp triangle object to store values as we parse them
	triangle tempTexture;
	triangle tempNormal;
	unsigned char garbage; //Character to store the garbage characters in faces

	std::vector<triangle> faceTemp; //Vector containing the model's faces
	std::vector<triangle> faceNormalTemp; //Vector containing the normals of the faces
	std::vector<triangle> faceTextureTemp; //Vector containing the textures of the faces

	std::vector<vertex> vertexTemp; //Vector containing the vertices of a model
	std::vector<vertex> vertexNormalTemp; //Vector containing the normals of the vertices
	std::vector<vertex> vertexTextureTemp; //Vector containing the textures of the vertices
	
	if (!file.fail()) //Makes sure the file opens
	{
		while ((file.good()) && (file >> keyword)) //Makes sure the file is good and you can load something in
		{
			if (keyword == "v") //Checks if it's a vertex
			{
				file >> tempVertex.x >> tempVertex.y >> tempVertex.z; //Stores info
				vertexTemp.push_back(tempVertex); //Pushes it in
				updateSize(Vector3f(tempVertex.x, tempVertex.y, tempVertex.z));
			}
			else if (keyword == "vn")
			{
				file >> tempVertex.x >> tempVertex.y >> tempVertex.z;
				vertexNormalTemp.push_back(tempVertex);
			}
			else if (keyword == "vt")
			{
				tempVertex.z = 0; //Z value is not used since all we use are UV
				file >> tempVertex.x >> tempVertex.y;
				vertexTextureTemp.push_back(tempVertex);
			}
			else if (keyword == "f")
			{
				std::string temp; //Temp string to hold current line
				std::getline(file, temp); //Stores info in temp
				std::stringstream line(temp); //Creates a variable line that has the value of temp

				while (line.good()) //As long as the line is fine. Only loads in tris
				{
					line >> tempFace.v1 >> garbage >> tempTexture.v1 >> garbage >> tempNormal.v1; //In the form X/XT/XN Y/YT/YN Z/ZT/ZN
					line >> tempFace.v2 >> garbage >> tempTexture.v2 >> garbage >> tempNormal.v2;
					line >> tempFace.v3 >> garbage >> tempTexture.v3 >> garbage >> tempNormal.v3;

					faceTemp.push_back(tempFace);
					faceTextureTemp.push_back(tempTexture);
					faceNormalTemp.push_back(tempNormal);
				}
			}
		}

		setModelName(modelName);
	}
	else 
	{
		std::cerr << "ERROR - CANNOT OPEN OBJECT: " << modelName << "." << std::endl;
		system("pause");
		exit(1);
	}

	file.close();

	_sortArrays(faceTemp, faceNormalTemp, faceTextureTemp, vertexTemp, vertexNormalTemp, vertexTextureTemp);
	_setupTangents(faceTemp, faceNormalTemp, faceTextureTemp, vertexTemp, vertexNormalTemp, vertexTextureTemp);
	_generateBuffers();
}

void Model::loadOBJS(const std::string &directory, const std::string &modelName)
{
	std::cout << "Loading Object: " << modelName << "." << std::endl;

	std::string keyword; //Keyword used for comparisons
	std::ifstream file; //Creates an input stream of the file
	file.open(directory + modelName); //If found, stores information in the ifstream

	float tempFloat0, tempFloat1, tempFloat2;
	
	if (!file.fail()) //Makes sure the file opens
	{
		file >> keyword >> _numOfVertices; 
		file >> keyword >> _numOfVerticesTexture;
		file >> keyword >> _numOfVerticesNormal;

		_vertexInfo = new float[_numOfVertices];
		_vertexTextureInfo = new float[_numOfVerticesTexture];
		_vertexNormalInfo = new float[_numOfVerticesNormal];

		for (unsigned int i = 0; i < _numOfVertices; i = i + 3)
		{
			file >> keyword >> tempFloat0 >> tempFloat1 >> tempFloat2;

			_vertexInfo[i] = tempFloat0;
			_vertexInfo[i + 1] = tempFloat1;
			_vertexInfo[i + 2] = tempFloat2;
		}

		for (unsigned int i = 0; i < _numOfVerticesTexture; i = i + 2)
		{
			file >> keyword >> tempFloat0 >> tempFloat1; 

			_vertexTextureInfo[i] = tempFloat0;
			_vertexTextureInfo[i + 1] = tempFloat1;
			_vertexTextureInfo[i + 2] = tempFloat2;
		}

		for (unsigned int i = 0; i < _numOfVerticesNormal; i = i + 3) 
		{
			file >> keyword >> tempFloat0 >> tempFloat1 >> tempFloat2; 

			_vertexNormalInfo[i] = tempFloat0;
			_vertexNormalInfo[i + 1] = tempFloat1;
			_vertexNormalInfo[i + 2] = tempFloat2;
		}

		setModelName(modelName);
	}
	else 
	{
		std::cerr << "ERROR - CANNOT OPEN OBJECT: " << modelName << "." << std::endl;
		system("pause");
		exit(1);
	}

	file.close();

	_generateBuffers();
}

void Model::_sortArrays(std::vector<triangle> &faceTemp, std::vector<triangle> &faceNormalTemp, std::vector<triangle> &faceTextureTemp, 
						std::vector<vertex> &vertexTemp, std::vector<vertex> &vertexNormalTemp, std::vector<vertex> &vertexTextureTemp) //Sorts the obj for the buffer arrays
{

	std::vector<float>* vertex = new std::vector<float>; //Vector containing the vertices of a model in the form x, y, z
	std::vector<float>* vertexNormal = new std::vector<float>; //Vector containing the normals of the vertices in the form x, y, z
	std::vector<float>* vertexTexture = new std::vector<float>; //Vector containing the textures of the vertices in the form x, y, z
	
	_numFaces = faceTemp.size();
	_vertexIndex = new float[faceTemp.size() * 3]; //Creates the array holding the vertex info

	for (unsigned int i = 0; i < faceTemp.size(); ++i) //Sorts the faces and vertices into vectors
	{
		vertexTexture ->push_back(vertexTextureTemp[faceTextureTemp[i].v1 - 1].x);
		vertexTexture ->push_back(vertexTextureTemp[faceTextureTemp[i].v1 - 1].y);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v1 - 1].x);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v1 - 1].y);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v1 - 1].z);
		vertex ->push_back(vertexTemp[faceTemp[i].v1 - 1].x);
		vertex ->push_back(vertexTemp[faceTemp[i].v1 - 1].y);
		vertex ->push_back(vertexTemp[faceTemp[i].v1 - 1].z);

		vertexTexture ->push_back(vertexTextureTemp[faceTextureTemp[i].v2 - 1].x);
		vertexTexture ->push_back(vertexTextureTemp[faceTextureTemp[i].v2 - 1].y);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v2 - 1].x);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v2 - 1].y);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v2 - 1].z);
		vertex ->push_back(vertexTemp[faceTemp[i].v2 - 1].x);
		vertex ->push_back(vertexTemp[faceTemp[i].v2 - 1].y);
		vertex ->push_back(vertexTemp[faceTemp[i].v2 - 1].z);

		vertexTexture ->push_back(vertexTextureTemp[faceTextureTemp[i].v3 - 1].x);
		vertexTexture ->push_back(vertexTextureTemp[faceTextureTemp[i].v3 - 1].y);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v3 - 1].x);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v3 - 1].y);
		vertexNormal ->push_back(vertexNormalTemp[faceNormalTemp[i].v3 - 1].z);
		vertex ->push_back(vertexTemp[faceTemp[i].v3 - 1].x);
		vertex ->push_back(vertexTemp[faceTemp[i].v3 - 1].y);
		vertex ->push_back(vertexTemp[faceTemp[i].v3 - 1].z);

		_vertexIndex[i * 3] = faceTemp[i].v1 - 1;
		_vertexIndex[i * 3 + 1] = faceTemp[i].v2 - 1;
		_vertexIndex[i * 3 + 2] = faceTemp[i].v3 - 1;
	}

	_vertexInfo = new float[vertex ->size()]; //Creates new vectors holding only floats
	_vertexTextureInfo = new float[vertexTexture ->size()];
	_vertexNormalInfo = new float[vertexNormal ->size()];

	_numOfVertices = vertex ->size(); //Stores size
	_numOfVerticesTexture = vertexTexture ->size();
	_numOfVerticesNormal = vertexNormal ->size();

	for (unsigned int i = 0; i < _numOfVertices; ++i) //Stores the verticies into a float vector
	{
		_vertexInfo[i] = vertex ->at(i);
	}

	for (unsigned int i = 0; i < _numOfVerticesTexture; ++i)
	{
		_vertexTextureInfo[i] = vertexTexture ->at(i);
	}

	for (unsigned int i = 0; i < _numOfVerticesNormal; ++i)
	{
		_vertexNormalInfo[i] = vertexNormal ->at(i);
	}
}

void Model::_generateBuffers() //Generates the buffers used for vertex buffering
{
	glGenBuffers(1, &_buffer);
	glGenBuffers(1, &_texBuffer);
    glGenBuffers(1, &_normBuffer);

	initDrawBuffers();
}

void Model::_setupTangents(std::vector<triangle> &faceTemp, std::vector<triangle> &faceNormalTemp, std::vector<triangle> &faceTextureTemp, 
						   std::vector<vertex> &vertexTemp, std::vector<vertex> &vertexNormalTemp, std::vector<vertex> &vertexTextureTemp) 
{
	_tangentInfo = new float[faceTemp.size() * 9]; //One for each xyz for each vertex, hence 9
	int tangentCount = 0;

	_bitangentInfo = new float[faceTemp.size() * 9];
	int bitangentCount = 0;

	for (unsigned int i = 0; i < faceTemp.size(); ++i)
	{
		

		_calcTangent(vertexTemp[faceTemp[i].v1 - 1], vertexTemp[faceTemp[i].v2 - 1], vertexTemp[faceTemp[i].v3 - 1],
					 vertexTextureTemp[faceTextureTemp[i].v1 - 1], vertexTextureTemp[faceTextureTemp[i].v2 - 1], vertexTextureTemp[faceTextureTemp[i].v3 - 1],
					 9 * i);

		_calcTangent(vertexTemp[faceTemp[i].v2 - 1], vertexTemp[faceTemp[i].v3 - 1], vertexTemp[faceTemp[i].v1 - 1],
					 vertexTextureTemp[faceTextureTemp[i].v2 - 1], vertexTextureTemp[faceTextureTemp[i].v3 - 1], vertexTextureTemp[faceTextureTemp[i].v1 - 1],
					 9 * i + 3);
		
		_calcTangent(vertexTemp[faceTemp[i].v3 - 1], vertexTemp[faceTemp[i].v1 - 1], vertexTemp[faceTemp[i].v2 - 1],
					 vertexTextureTemp[faceTextureTemp[i].v3 - 1], vertexTextureTemp[faceTextureTemp[i].v1 - 1], vertexTextureTemp[faceTextureTemp[i].v2 - 1],
					 9 * i + 6);
	}
}

void Model::_calcTangent(vertex &p1, vertex &p2, vertex &p3, vertex &t1, vertex &t2, vertex &t3, unsigned int index) //Code from tutorial 7
{
	Vector3f vp1;
	Vector3f vp2;

	vp1.set(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	vp2.set(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);

	Vector3f vt1;
	Vector3f vt2;

	vt1.set(t2.x - t1.x, t2.y - t1.y, 0.0f);
	vt2.set(t3.x - t1.x, t3.y - t1.y, 0.0f);

	float r = 1.0f / (vt1.getX() * vt2.getY() - vt2.getX() * vt1.getY());

	Vector3f sdir;

	sdir.set((vt2.getY() * vp1.getX() - vt1.getY() * vp2.getX()) * r, 
			 (vt2.getY() * vp1.getY() - vt1.getY() * vp2.getY()) * r,
			 (vt2.getY() * vp1.getZ() - vt1.getY() * vp2.getZ()) * r);

	Vector3f tdir;
	
	tdir.set((vt1.getX() * vp2.getX() - vt2.getX() * vp1.getX()) * r, 
			 (vt1.getX() * vp2.getY() - vt2.getX() * vp1.getY()) * r,
			 (vt1.getX() * vp2.getZ() - vt2.getX() * vp1.getZ()) * r);

	_tangentInfo[index] = sdir.getX();
	_tangentInfo[index + 1] = sdir.getY();
	_tangentInfo[index + 2] = sdir.getZ();

	_bitangentInfo[index] = tdir.getX();
	_bitangentInfo[index + 1] = tdir.getY();
	_bitangentInfo[index + 2] = tdir.getZ();
}

void Model::setTexture(unsigned int index, Texture *texture)
{
	_texture[index] = *texture;
}

void Model::setModelName(const std::string &fileName) 
{
	_modelName = fileName;
}

void Model::setPosition(Vector3f &position)
{
	_position = position;
}

void Model::setSpawnPoint(Vector3f &position)
{
	_position = position;
	_spawnPoint = position;
	_adjustedPosition = _adjustedPosition.add(position);
}

void Model::setVelocity(Vector3f velocity)
{
	_velocity = velocity;
}

void Model::setAccel(Vector3f &accel)
{
	_acceleration = accel;
}

void Model::setSpeed(float speed)
{
	_speed = speed;
}

void Model::setScale(Vector3f &scale)
{
	_scale = scale;

	_adjustedModelSizeMin = _modelSizeMin.multiply(_scale);
	_adjustedModelSizeMax = _modelSizeMax.multiply(_scale);
}

void Model::setColor(float r, float g, float b, float a)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
	_color.a = a;
}

void Model::setRotate(Vector3f angle)
{
	_rotate = angle;
}

void Model::setActive(bool status)
{
	_active = status;
}

void Model::setLink(Model* model, unsigned int type)
{
	_link = new Model(); //Initializes this model
	_link = model;
	_linkType = type;
}

std::string Model::getModelName()
{
	return _modelName;
}

std::string Model::getTextureName(unsigned int num)
{
	return _texture[num].getTextureName();
}

Vector3f Model::getPosition()
{
	return _position;
}

Vector3f Model::getAdjustedPosition()
{
	return _adjustedPosition;
}

Vector3f Model::getSpawnPoint()
{
	return _spawnPoint;
}

Vector3f Model::getVelocity()
{
	return _velocity;
}

Vector3f Model::getAccel()
{
	return _acceleration;
}

float Model::getSpeed()
{
	return _speed;
}

Vector3f Model::getScale()
{
	return _scale;
}

float Model::getColor(unsigned int index)
{
	switch (index)
	{
	case (0):
		return _color.r;
		break;
	case (1):
		return _color.g;
		break;
	case (2):
		return _color.b;
		break;
	case (3):
		return _color.a;
		break;
	}

	return -1;
}

Vector3f Model::getRotate()
{
	return _rotate;
}

Vector3f Model::getModelSize()
{
	return _modelSizeMax.subtract(_modelSizeMin);
}

Vector3f Model::getMinSize()
{
	return _adjustedModelSizeMin;
}

Vector3f Model::getMaxSize()
{
	return _adjustedModelSizeMax;
}

bool Model::getActive()
{
	return _active;
}

void Model::increaseScale(Vector3f &scale)
{
	_scale = _scale.add(scale);
}

void Model::updateSize(Vector3f &newPoint)
{
	if (newPoint.getX() > _modelSizeMax.getX())
	{
		_modelSizeMax.setX(newPoint.getX());
	}
	
	if (newPoint.getX() < _modelSizeMin.getX())
	{
		_modelSizeMin.setX(newPoint.getX());
	}

	if (newPoint.getY() > _modelSizeMax.getY())
	{
		_modelSizeMax.setY(newPoint.getY());
	}
	
	if (newPoint.getY() < _modelSizeMin.getY())
	{
		_modelSizeMin.setY(newPoint.getY());
	}

	if (newPoint.getZ() > _modelSizeMax.getZ())
	{
		_modelSizeMax.setZ(newPoint.getZ());
	}
	
	if (newPoint.getZ() < _modelSizeMin.getZ())
	{
		_modelSizeMin.setZ(newPoint.getZ());
	}

	_adjustedModelSizeMin = _modelSizeMin.multiply(_scale);
	_adjustedModelSizeMax = _modelSizeMax.multiply(_scale);

	_adjustedPosition = _modelSizeMax.add(_modelSizeMin).scalarMultiply(0.5); 
}

float Model::getRadius(unsigned int type)
{
	
	Vector3f size = _adjustedModelSizeMax.subtract(_adjustedModelSizeMin);

	if (type == NG_3D)
	{
		if (size.getX() >= size.getY() && size.getX() >= size.getZ()) //Checks if the x is wider or the same as z
		{
			return (size.getX() / 1.5f) * _hitSize; //Radius, so we need to divide, but we don't want it exactly /2 since thats too close
		}
		else if (size.getY() >= size.getZ()) //If y is larger
		{
			return (size.getY() / 1.5f) * _hitSize; //1.5 means we get a bit of a bigger bounding sphere
		}
		else //If z is larger
		{
			return (size.getZ() / 1.5f) * _hitSize;
		}
	}
	else
	{
		if (size.getX() >= size.getZ()) //Checks if the x is wider or the same as z
		{
			return (size.getX() / 1.5f) * _hitSize; //Radius, so we need to divide, but we don't want it exactly /2 since thats too close
		}
		else //If z is larger
		{
			return (size.getZ() / 1.5f) * _hitSize;
		}
	}
}

void Model::setAnimation(unsigned int animation, float weight)
{
	_animation.addNewAnimation(animation, weight);
}

void Model::setMesh(float* vertex, unsigned int &vertexSize,
					float* normal, unsigned int &normalSize, 
					float* texture, unsigned int &textureSize, 
					Vector3f &minSize, Vector3f &maxSize, 
					std::string name) 
{
	_vertexInfo = vertex; //Overwrites previous info
	_vertexNormalInfo = normal;
	_vertexTextureInfo = texture;

	_numOfVertices = vertexSize; //Adjusts sizes
	_numOfVerticesTexture = textureSize;
	_numOfVerticesNormal = normalSize;

	_modelSizeMin = minSize;
	_modelSizeMax = maxSize;
	_modelName = name;


	_generateBuffers(); //Generate the buffers
}

void Model::setMesh(Model &model)
{
	_vertexInfo = model.getMesh(NG_VERTEX); //Overwrites previous info
	_vertexNormalInfo = model.getMesh(NG_NORMAL);
	_vertexTextureInfo = model.getMesh(NG_TEXTURE);
	_tangentInfo = model.getMesh(NG_TANGENT);
	_bitangentInfo = model.getMesh(NG_BITANGENT);

	_vertexIndex = model.getMeshIndices();

	_numFaces = model.getMeshFaceNum();

	_numOfVertices = model.getMeshSizes(NG_VERTEX); //Adjusts sizes
	_numOfVerticesTexture = model.getMeshSizes(NG_TEXTURE);
	_numOfVerticesNormal = model.getMeshSizes(NG_NORMAL);

	_modelSizeMin = model.getMinSize();
	_modelSizeMax = model.getMaxSize();
	_adjustedModelSizeMin = _modelSizeMin;
	_adjustedModelSizeMax = _modelSizeMax;

	_modelName = model.getModelName();

	_generateBuffers(); //Generate the buffers
}

float* Model::getMesh(unsigned int type)
{
	if (type == NG_VERTEX)
	{
		return _vertexInfo;
	}
	else if (type == NG_NORMAL)
	{
		return _vertexNormalInfo;
	}
	else if (type == NG_TEXTURE)
	{
		return _vertexTextureInfo;
	}
	else if (type == NG_TANGENT)
	{
		return _tangentInfo;
	}
	else
	{
		return _bitangentInfo;
	}
}

unsigned int& Model::getMeshSizes(unsigned int type)
{
	if (type == NG_VERTEX)
	{
		return _numOfVertices;
	}
	else if (type == NG_NORMAL)
	{
		return _numOfVerticesNormal;
	}
	else
	{
		return _numOfVerticesTexture;
	}
}

float* Model::getMeshIndices()
{
	return _vertexIndex;
}

unsigned int Model::getMeshIndicesSize()
{
	return _numOfVertices / 3;
}

unsigned int Model::getMeshFaceNum()
{
	return _numFaces;
}

void Model::setShader(int shader, const char* shaderFile, const char* shaderName)
{
	if (shader == NG_VERTEX_SHADER)
	{
		_vShader = new Shader(shaderFile, shaderName);
	}
	else
	{
		_fShader = new Shader(shaderFile, shaderName);
	}
}

Shader* Model::getShader(int shader)
{
	if (shader == NG_VERTEX_SHADER)
	{
		return _vShader;
	}
	else
	{
		return _fShader;
	}
}

void Model::shaderParameterHandler(Shader* shader) //Controls which params to run
{
	if (shader ->getFileName() == "Vertex_Easy.cg") //Vertex Shaders
	{
		cgSetParameter4f(shader ->color, _color.r, _color.g, _color.b, _color.a);
		cgSetParameter4f(shader ->rotationRow0, transformations.getRow(0)[0], transformations.getRow(0)[1], transformations.getRow(0)[2], transformations.getRow(0)[3]);
		cgSetParameter4f(shader ->rotationRow1, transformations.getRow(1)[0], transformations.getRow(1)[1], transformations.getRow(1)[2], transformations.getRow(1)[3]);
		cgSetParameter4f(shader ->rotationRow2, transformations.getRow(2)[0], transformations.getRow(2)[1], transformations.getRow(2)[2], transformations.getRow(2)[3]);

		cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

		if (shader ->getShaderName() == "vColor")
		{

		}
		else if (shader ->getShaderName() == "vDisplacementMap")
		{
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);			
		}
		else if (shader ->getShaderName() == "vLighting")
		{
			cgSetParameter3f(shader ->globalAmbient, 0.1f, 0.1f, 0.1f);

			cgSetParameter3f(shader ->lightColor[0], _lightColor[0].getX(), _lightColor[0].getY(), _lightColor[0].getX());
			cgSetParameter3f(shader ->lightPosition[0], _lightPos[0].getX(), _lightPos[0].getY(), _lightPos[0].getZ());

			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
			cgSetParameter3f(shader ->ke, _ke, _ke, _ke);
			cgSetParameter3f(shader ->ka, _ka, _ka, _ka);
			cgSetParameter3f(shader ->ks, _ks, _ks, _ks);
			cgSetParameter3f(shader ->kd, _kd, _kd, _kd);
			cgSetParameter1f(shader ->shininess, _shininess);
		}
		else if (shader ->getShaderName() == "vFragLighting")
		{
			/*cgGLEnableClientState(shader ->magic0);
			cgGLSetParameterPointer(shader ->magic0, 3, GL_FLOAT, 0, _tangentInfo);
			cgGLEnableClientState(shader ->magic1);
			cgGLSetParameterPointer(shader ->magic1, 3, GL_FLOAT, 0, _bitangentInfo);*/
		}
		else if (shader ->getShaderName() == "vFragLightingShadow")
		{
			cgGLSetMatrixParameterfr(shader ->textureMatrix, Shader::shadowBias);
			cgGLSetMatrixParameterfr(shader ->lightViewMatrix, _reallyHackyLightModelViewProjectionMatrix ->get());
		}
	}
	else if (shader ->getFileName() == "Vertex_Medium.cg")
	{
		cgSetParameter4f(shader ->color, _color.r, _color.g, _color.b, _color.a);
		cgSetParameter4f(shader ->rotationRow0, transformations.getRow(0)[0], transformations.getRow(0)[1], transformations.getRow(0)[2], transformations.getRow(0)[3]);
		cgSetParameter4f(shader ->rotationRow1, transformations.getRow(1)[0], transformations.getRow(1)[1], transformations.getRow(1)[2], transformations.getRow(1)[3]);
		cgSetParameter4f(shader ->rotationRow2, transformations.getRow(2)[0], transformations.getRow(2)[1], transformations.getRow(2)[2], transformations.getRow(2)[3]);
		cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	}
	else if (shader ->getFileName() == "GPU_Skinning.cg")
	{
		if (shader ->getShaderName() == "skinMeshWithLightingAndShadows")
		{
			cgSetParameter4f(shader ->rotationRow0, transformations.getRow(0)[0], transformations.getRow(0)[1], transformations.getRow(0)[2], transformations.getRow(0)[3]);
			cgSetParameter4f(shader ->rotationRow1, transformations.getRow(1)[0], transformations.getRow(1)[1], transformations.getRow(1)[2], transformations.getRow(1)[3]);
			cgSetParameter4f(shader ->rotationRow2, transformations.getRow(2)[0], transformations.getRow(2)[1], transformations.getRow(2)[2], transformations.getRow(2)[3]);
			cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

			cgGLSetMatrixParameterArrayfr(shader ->boneMatricies, 0, 62, _skeletonAnimation ->currentClip ->skeletonMatrix); //64 is offset. Needs to be hard coded depending on number of bones/joints

			cgGLEnableClientState(shader ->weights);
			cgGLSetParameterPointer(shader ->weights, 4, GL_FLOAT, 0, _skeletonAnimation ->skin.weightPtr); //Sets the attribute
			cgGLEnableClientState(shader ->jointIndices);
			cgGLSetParameterPointer(shader ->jointIndices, 4, GL_INT, 0, _skeletonAnimation ->skin.indexPtr); //Sets the attribute

			cgGLSetMatrixParameterfr(shader ->textureMatrix, Shader::shadowBias);
			cgGLSetMatrixParameterfr(shader ->lightViewMatrix, _lightModelViewProjectionMatrix);
		}
		if (shader ->getShaderName() == "skinMeshWithLighting")
		{
			cgSetParameter4f(shader ->rotationRow0, transformations.getRow(0)[0], transformations.getRow(0)[1], transformations.getRow(0)[2], transformations.getRow(0)[3]);
			cgSetParameter4f(shader ->rotationRow1, transformations.getRow(1)[0], transformations.getRow(1)[1], transformations.getRow(1)[2], transformations.getRow(1)[3]);
			cgSetParameter4f(shader ->rotationRow2, transformations.getRow(2)[0], transformations.getRow(2)[1], transformations.getRow(2)[2], transformations.getRow(2)[3]);
			cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

		
			cgGLSetMatrixParameterArrayfr(shader ->boneMatricies, 0, 62, _skeletonAnimation ->currentClip ->skeletonMatrix);

			cgGLEnableClientState(shader ->weights);
			cgGLSetParameterPointer(shader ->weights, 4, GL_FLOAT, 0, _skeletonAnimation ->skin.weightPtr); //Sets the attribute
			cgGLEnableClientState(shader ->jointIndices);
			
			cgGLSetParameterPointer(shader ->jointIndices, 4, GL_INT, 0, _skeletonAnimation ->skin.indexPtr); //Sets the attribute
		}
		else if (shader ->getShaderName() == "skinMesh")
		{
			cgSetParameter4f(shader ->rotationRow0, transformations.getRow(0)[0], transformations.getRow(0)[1], transformations.getRow(0)[2], transformations.getRow(0)[3]);
			cgSetParameter4f(shader ->rotationRow1, transformations.getRow(1)[0], transformations.getRow(1)[1], transformations.getRow(1)[2], transformations.getRow(1)[3]);
			cgSetParameter4f(shader ->rotationRow2, transformations.getRow(2)[0], transformations.getRow(2)[1], transformations.getRow(2)[2], transformations.getRow(2)[3]);
			cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

			
			cgGLSetMatrixParameterArrayfr(shader ->boneMatricies, 0, 62, _skeletonAnimation ->currentClip ->skeletonMatrix);

			cgGLEnableClientState(shader ->weights);
		
			cgGLSetParameterPointer(shader ->weights, 4, GL_FLOAT, 0, _skeletonAnimation ->skin.weightPtr); //Sets the attribute
			cgGLEnableClientState(shader ->jointIndices);
	
			cgGLSetParameterPointer(shader ->jointIndices, 4, GL_INT, 0, _skeletonAnimation ->skin.indexPtr); //Sets the attribute
		}
		
	}
	else if (shader ->getFileName() == "Fragment_Easy.cg")
	{
		if (shader ->getShaderName() == "fColor")
		{

		}
		else if (shader ->getShaderName() == "fTextureReplace" 
				|| shader ->getShaderName() == "fTextureModulate"
				|| shader ->getShaderName() == "fTextureBlur")
		{
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());				
			cgGLEnableTextureParameter(shader ->texture0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "fLighting") 
		{
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);

			cgSetParameter3f(shader ->globalAmbient, 0.1f, 0.1f, 0.1f);

			cgSetParameter3f(shader ->lightColor[0], _lightColor[0].getX(), _lightColor[0].getY(), _lightColor[0].getX());
			cgSetParameter3f(shader ->lightPosition[0], _lightPos[0].getX(), _lightPos[0].getY(), _lightPos[0].getZ());

			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
			cgSetParameter3f(shader ->ke, _ke, _ke, _ke);
			cgSetParameter3f(shader ->ka, _ka, _ka, _ka);
			cgSetParameter3f(shader ->ks, _ks, _ks, _ks);
			cgSetParameter3f(shader ->kd, _kd, _kd, _kd);
			cgSetParameter1f(shader ->shininess, _shininess);

			cgSetParameter1f(shader ->offset, _uvOffset);
		}
		else if (shader ->getShaderName() == "fLightingGooch")
		{
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);

			cgSetParameter3f(shader ->globalAmbient, 0.1f, 0.1f, 0.1f);

			cgSetParameter3f(shader ->lightColor[0], _lightColor[0].getX(), _lightColor[0].getY(), _lightColor[0].getX());
			cgSetParameter3f(shader ->lightPosition[0], _lightPos[0].getX(), _lightPos[0].getY(), _lightPos[0].getZ());

			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
			cgSetParameter3f(shader ->ke, _ke, _ke, _ke);
			cgSetParameter3f(shader ->ka, _ka, _ka, _ka);
			cgSetParameter3f(shader ->ks, _ks, _ks, _ks);
			cgSetParameter3f(shader ->kd, _kd, _kd, _kd);
			cgSetParameter1f(shader ->shininess, _shininess);

			cgSetParameter4f(shader ->color, _color.r, _color.g, _color.b, _color.a);
			cgSetParameter1f(shader ->globalLightIntensity, _globalLightIntensity);

			cgSetParameter1f(shader ->offset, _uvOffset);
		}
		else if (shader ->getShaderName() == "fLightingGoochWithShadow")
		{
			glActiveTextureARB(GL_TEXTURE4_ARB);
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);	

			glActiveTextureARB(GL_TEXTURE2_ARB);
			glBindTexture(GL_TEXTURE_2D, _texture[1].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->shadowMap, _texture[1].get());
			cgGLEnableTextureParameter(shader ->shadowMap);	

			cgSetParameter3f(shader ->globalAmbient, 0.1f, 0.1f, 0.1f);

			cgSetParameter3f(shader ->lightColor[0], _lightColor[0].getX(), _lightColor[0].getY(), _lightColor[0].getX());
			cgSetParameter3f(shader ->lightPosition[0], _lightPos[0].getX(), _lightPos[0].getY(), _lightPos[0].getZ());

			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
			cgSetParameter3f(shader ->ke, _ke, _ke, _ke);
			cgSetParameter3f(shader ->ka, _ka, _ka, _ka);
			cgSetParameter3f(shader ->ks, _ks, _ks, _ks);
			cgSetParameter3f(shader ->kd, _kd, _kd, _kd);
			cgSetParameter1f(shader ->shininess, _shininess);

			cgSetParameter4f(shader ->color, _color.r, _color.g, _color.b, _color.a);
			cgSetParameter1f(shader ->globalLightIntensity, _globalLightIntensity);

			cgSetParameter1f(shader ->offset, _uvOffset);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "fMultiTexture")
		{
			cgSetParameter1f(shader ->on0, _shaderToggle[0]);
			cgSetParameter1f(shader ->on1, _shaderToggle[1]);
			cgSetParameter1f(shader ->on2, _shaderToggle[2]);
			cgSetParameter1f(shader ->on3, _shaderToggle[3]);

			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);	

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glBindTexture(GL_TEXTURE_2D, _texture[1].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture1, _texture[1].get());
			cgGLEnableTextureParameter(shader ->texture1);	

			glActiveTextureARB(GL_TEXTURE2_ARB);
			glBindTexture(GL_TEXTURE_2D, _texture[2].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture2, _texture[2].get());
			cgGLEnableTextureParameter(shader ->texture2);	

			glActiveTextureARB(GL_TEXTURE3_ARB);
			glBindTexture(GL_TEXTURE_2D, _texture[3].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture3, _texture[3].get());
			cgGLEnableTextureParameter(shader ->texture3);	

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	else if (shader ->getFileName() == "Fragment_Medium.cg")
	{
		if (shader ->getShaderName() == "fNormalMap")
		{
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);	

			cgSetParameter3f(shader ->globalAmbient, 0.1f, 0.1f, 0.1f);

			for (unsigned int i = 0; i < _lightPos.size(); ++i)
			{
				cgSetParameter3f(shader ->lightColor[i], _lightColor[i].getX(), _lightColor[i].getY(), _lightColor[i].getX());
				cgSetParameter3f(shader ->lightPosition[i], _lightPos[i].getX(), _lightPos[i].getY(), _lightPos[i].getZ());
			}

			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
			cgSetParameter3f(shader ->ke, _ke, _ke, _ke);
			cgSetParameter3f(shader ->ka, _ka, _ka, _ka);
			cgSetParameter3f(shader ->ks, _ks, _ks, _ks);
			cgSetParameter3f(shader ->kd, _kd, _kd, _kd);
			cgSetParameter1f(shader ->shininess, _shininess);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "fToon")
		{
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);

			cgSetParameter3f(shader ->globalAmbient, 0.1f, 0.1f, 0.1f);

			cgSetParameter3f(shader ->lightColor[0], _lightColor[0].getX(), _lightColor[0].getY(), _lightColor[0].getX());
			cgSetParameter3f(shader ->lightPosition[0], _lightPos[0].getX(), _lightPos[0].getY(), _lightPos[0].getZ());

			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
			cgSetParameter3f(shader ->ke, _ke, _ke, _ke);
			cgSetParameter3f(shader ->ka, _ka, _ka, _ka);
			cgSetParameter3f(shader ->ks, _ks, _ks, _ks);
			cgSetParameter3f(shader ->kd, _kd, _kd, _kd);
			cgSetParameter1f(shader ->shininess, _shininess);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "fMultiLighting")
		{
			glBindTexture(GL_TEXTURE_2D, _texture[0].get()); //Binds current texture to model
			cgGLSetTextureParameter(shader ->texture0, _texture[0].get());
			cgGLEnableTextureParameter(shader ->texture0);

			cgSetParameter3f(shader ->globalAmbient, 0.1f, 0.1f, 0.1f);

			for (unsigned int i = 0; i < _lightPos.size(); ++i)
			{
				cgSetParameter3f(shader ->lightColor[i], _lightColor[i].getX(), _lightColor[i].getY(), _lightColor[i].getX());
				cgSetParameter3f(shader ->lightPosition[i], _lightPos[i].getX(), _lightPos[i].getY(), _lightPos[i].getZ());
			}

			cgSetParameter1f(shader ->numOfLights, _lightPos.size());

			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
			cgSetParameter3f(shader ->ke, _ke, _ke, _ke);
			cgSetParameter3f(shader ->ka, _ka, _ka, _ka);
			cgSetParameter3f(shader ->ks, _ks, _ks, _ks);
			cgSetParameter3f(shader ->kd, _kd, _kd, _kd);
			cgSetParameter1f(shader ->shininess, _shininess);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (shader ->getShaderName() == "fDepth")
		{
			cgSetParameter3f(shader ->eyePosition, _eyePos.getX(), _eyePos.getY(), _eyePos.getZ());
		}
	}
	else if (shader ->getFileName() == "Vertex_Shadow.cg")
	{
		cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
		
		cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
		cgGLSetStateMatrixParameter(shader ->textureMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	}
	else if (shader ->getFileName() == "Fragment_Blur.cg")
	{
	}
	
	shader ->checkForCgError("enable decal texture");	
}

void Model::setNotificationStuff(Text** text, Timer** timer)
{
	_notificationText = text;
	_notificationTimer = timer;
}

void Model::setLightPos(Vector3f &pos, unsigned int index)
{
	_lightPos[index] = pos;
}

Vector3f Model::getLightPos(unsigned int index)
{
	return _lightPos[index];
}

void Model::initLight(Vector3f &pos, Vector3f &color)
{
	_lightPos.push_back(pos);
	_lightColor.push_back(color);
}

void Model::setGlobalLightIntensity(float intensity)
{
	_globalLightIntensity = intensity;
}

float Model::getGlobalLightIntensity()
{
	return _globalLightIntensity;
}

void Model::setLightMatrix()
{
	Matrix lightModelView;
	Matrix lightProjection;

	glGetFloatv(GL_MODELVIEW_MATRIX, _lightModelViewMatrix);
	glGetFloatv(GL_PROJECTION_MATRIX, _lightProjectionMatrix);

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

		_lightModelViewProjectionMatrix[i] = _lightProjectionMatrix[startRow] * _lightModelViewMatrix[startColumn]
											+ _lightProjectionMatrix[startRow + 1] * _lightModelViewMatrix[startColumn + 4]
											+ _lightProjectionMatrix[startRow + 2] * _lightModelViewMatrix[startColumn + 8]
											+ _lightProjectionMatrix[startRow + 3] * _lightModelViewMatrix[startColumn + 12];
	}

	_reallyHackyLightModelViewProjectionMatrix ->set(_lightModelViewProjectionMatrix);
	_reallyHackyLightModelViewProjectionMatrix ->transpose();
}

unsigned int Model::getMaxLights()
{
	return _MAX_LIGHTS;
}

void Model::setEyePos(Vector3f &pos)
{
	_eyePos = pos;
}

Vector3f Model::getEyePos()
{
	return _eyePos;
}

int Model::hitTest(Model &model, unsigned int type) 
{
	if (type == NG_BOX_COLLISION) //Main obj is still a sphere
	{
		float hack = 1.0f; 

		if (std::string::npos != model.getModelName().find("Tree")) 
		{
			

			if (model.getModelSize().getX() < 60) 
			{
				hack = 0.5f;
			}
			else if (model.getModelSize().getX() < 120) 
			{
				hack = -0.5f;
			}
			else 
			{
				hack = -1.5f;
			}
		}
		else if (std::string::npos != model.getModelName().find("Henge") //Henges are sketchy too
				 || std::string::npos != model.getModelName().find("Ruin")) //As are ruins
		{
			hack = 0.75f;
		}

		if ((_position.getX() + getRadius(NG_2D) * hack < model.getMinSize().getX()) //If you are too far left
			|| (_position.getX() - getRadius(NG_2D) * hack > model.getMaxSize().getX()) //If you are too far right
			|| (_position.getZ() + getRadius(NG_2D) * hack < model.getMinSize().getZ()) //If you are too far down
			|| (_position.getZ() - getRadius(NG_2D) * hack > model.getMaxSize().getZ()) //If you are too far up
			|| (_position.getY() + _modelSizeMin.getY() > model.getMaxSize().getY()) //If you are too far vertical (up)
			|| (_position.getY() + _modelSizeMax.getY() < model.getMinSize().getY())) //If you are too far vertical (down)
		{
			
			return NG_NO_HIT;
		}
		else if ((_position.getY() - abs(_modelSizeMin.getY()) + NG_COLLISION_DETECTION_THRESHOLD >= model.getMaxSize().getY()
			&& _position.getY() - abs(_modelSizeMin.getY()) <= model.getMaxSize().getY())
			&& _position.getZ() - abs(_modelSizeMin.getZ()) <= model.getMaxSize().getZ()
			&& _position.getZ() + abs(_modelSizeMax.getZ()) >= model.getMinSize().getZ())
		{
			
			return NG_HIT_TOP;
		}
		else if ((_position.getY() + abs(_modelSizeMax.getY()) - NG_COLLISION_DETECTION_THRESHOLD / 2 <= model.getMinSize().getY() //Divides by 2 becuase this collision detection is bad and needs adjustment
			&& _position.getY() + abs(_modelSizeMax.getY()) >= model.getMinSize().getY())
			&& _position.getZ() + abs(_modelSizeMin.getZ()) <= model.getMaxSize().getZ()
			&& _position.getZ() - abs(_modelSizeMax.getZ()) >= model.getMinSize().getZ())
		{
			
			return NG_HIT_BOTTOM;
		}
		else //Must be a side collision then. 
	
			//Figures out the distance you are from each line of the collision box
			//You are colliding with the one that is closest

			_lineStartHT = Vector3f(model.getMinSize().getX(), 0.0f, model.getMinSize().getZ()); //Checks for left collision first
			_lineEndHT = Vector3f(model.getMinSize().getX(), 0.0f, model.getMaxSize().getZ()); //Checks for left collision first
			_lineHT = _lineEndHT.subtract(_lineStartHT);
			_leftHT = _lineEndHT.subtract(_position).calcProjectionLength(_lineHT);

			_lineStartHT = Vector3f(model.getMinSize().getX(), 0.0f, model.getMaxSize().getZ()); //Checks for down collision
			_lineEndHT = Vector3f(model.getMaxSize().getX(), 0.0f, model.getMaxSize().getZ()); //Checks for down collision
			_lineHT = _lineEndHT.subtract(_lineStartHT);
			_upHT = _lineEndHT.subtract(_position).calcProjectionLength(_lineHT);

			_lineStartHT = Vector3f(model.getMaxSize().getX(), 0.0f, model.getMaxSize().getZ()); //Checks for right collision
			_lineEndHT = Vector3f(model.getMaxSize().getX(), 0.0f, model.getMinSize().getZ()); //Checks for right collision
			_lineHT = _lineEndHT.subtract(_lineStartHT);
			_rightHT = _lineEndHT.subtract(_position).calcProjectionLength(_lineHT);

			_lineStartHT = Vector3f(model.getMaxSize().getX(), 0.0f, model.getMinSize().getZ()); //Checks for up collision
			_lineEndHT = Vector3f(model.getMinSize().getX(), 0.0f, model.getMinSize().getZ()); //Checks for up collision
			_lineHT = _lineEndHT.subtract(_lineStartHT);
			_downHT = _lineEndHT.subtract(_position).calcProjectionLength(_lineHT);

			if (_leftHT <= _rightHT && _leftHT <= _upHT && _leftHT <= _downHT)
			{
			
				return NG_HIT_LEFT;
			}
			else if (_rightHT <= _upHT && _rightHT <= _downHT)
			{
				
				return NG_HIT_RIGHT;
			}
			else if (_upHT <= _downHT)
			{
				
				return NG_HIT_UP;
			}
			else
			{
				return NG_HIT_DOWN;
			}
		}
	
	else if (type == NG_CIRCLE_COLLISION) //2D on the ground
	{
		float distanceBetween = _position.subtract(model.getAdjustedPosition()).calcMagnitude(); //Finds out distance between objects
		float radiusTotal = getRadius(NG_2D) + model.getRadius(NG_2D); //Finds out added radiuses

		if (radiusTotal >= distanceBetween) //Checks if they overlap
		{
			return NG_HIT;
		}
	}
	else if (type == NG_PILL_COLLISION) //2D on the ground, but extended up with the height of the thing
	{
		Vector3f distanceBetween = _position.subtract(model.getAdjustedPosition()); //Finds out how much distance is between the two
		distanceBetween.setY(0); //Zeros out the Y for now
		

		float radiusTotal = getRadius(NG_2D) + model.getRadius(NG_2D); //Finds out added radiuses

		if (radiusTotal >= distanceBetween.calcMagnitude()) //Checks if they overlap in terms of X and Z
		{
			if (_position.getY() >= model.getAdjustedPosition().getY() + model.getMinSize().getY() && _position.getY() <= model.getAdjustedPosition().getY() + model.getMaxSize().getY()) //Checks if the Y is valid
			{
				return NG_HIT;
			}
		}
	}

	return NG_NO_HIT;
}

void Model::setHitSize(float size) //Only really used for circle/pill collisions
{
	_hitSize = size;
}

float Model::getHitSize()
{
	return _hitSize;
}

void Model::setSkeleton(Skeleton &skeleton)
{
	_skeleton = &skeleton;
}

void Model::setSkin(Skin &skin)
{
	_skin = &skin;
}

void Model::setupSkeleton() //Requires a skeleton and a skin
{
	_skin ->setJointIndices(_skeleton ->getBoneList()); //Gets the indices of the joints
	_skin ->setAndSortMeshIndices(_vertexIndex, _numOfVertices / 3); //Sorts the indicies based on the mesh
	_skin ->setWeightAndJointPointers(); //Sets up the pointers to be passed into the shader
	_skeleton ->setBindingPose(); //Sets the bind pose and all the matricies
	_skeleton ->setSkeletonMatrix(); //Makes a giant matrix for all your matricies
}

void Model::startAnimationTimer()
{
	_animationTimer ->start();
}

void Model::updateAnimation()
{
	_skeleton ->playAnimation(_animationTimer ->get(NG_TIMER_MILLISECONDS)); //Starts the animation
	_skeleton ->allocateSkeletonMatrix(); //Changes the skeleton matrix
}

playerAnimations* Model::getSkeletonAnimation()
{
	return _skeletonAnimation;
}

void Model::setLightingCharacteristics(float ke, float ka, float ks, float kd, float shininess)
{
	_ke = ke;
	_ka = ka;
	_ks = ks;
	_kd = kd;
	_shininess = shininess;
}

void Model::setUVOffset(float offset)
{
	_uvOffset = offset;
}

float Model::getUVOffset()
{
	return _uvOffset;
}


Path* Model::getPath()
{
	return _path;
}

void Model::draw(unsigned int culling, bool wireframe, bool shaderOn)
{
	if (_active)
	{
		glPushMatrix();

		glLoadIdentity();
		
		glEnable(GL_BLEND); //Enables blending
		glAlphaFunc(GL_GREATER, 0.5f); //Culls anything greater than this threshold
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Enables alpha blending	

		if (shaderOn == true)
		{
			_vShader ->bindAndEnableShaders();
			_fShader ->bindAndEnableShaders();	

			shaderParameterHandler(_vShader);
			shaderParameterHandler(_fShader);
		}

		if (culling == NG_BACKFACE_CULLING)
		{
			glEnable(GL_CULL_FACE); //Enables face culling
			glCullFace(GL_BACK);
			
		}
		else if (culling == NG_FRONTFACE_CULLING)
		{
			glEnable(GL_CULL_FACE); //Enables face culling
			glCullFace(GL_FRONT); //frontface culling
		}

		if (wireframe == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, _texBuffer);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, _normBuffer);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glNormalPointer(GL_FLOAT, 0, NULL);


		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glDrawArrays(GL_TRIANGLES, 0, _numFaces * 3); //Draws the obj

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		if (_vShader ->getShaderName() == "skinMeshWithLighting")
		{
			cgGLDisableClientState(_vShader ->jointIndices);
			cgGLDisableClientState(_vShader ->weights);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (culling == NG_BACKFACE_CULLING || culling == NG_FRONTFACE_CULLING)
		{
			glDisable(GL_CULL_FACE);
		}

		if (shaderOn == true)
		{
			_vShader ->disableShaders();
			_fShader ->disableShaders();
		}

		glDisable(GL_BLEND);
		glAlphaFunc(GL_GREATER, 0.0f); //Turns off this thing
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glPopMatrix();
	}
}

void Model::drawBoundingBox() //Ugh glBegin and glEnd
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMin.getZ()); //Front face
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMin.getZ());

	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMax.getZ()); //Back face
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMax.getZ());
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMax.getZ());
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMax.getZ());

	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMax.getZ()); //Left face
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMax.getZ());

	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMax.getZ()); //Right face
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMax.getZ());
	
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMin.getZ()); //Top face
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMax.getZ());
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMax.getY(), _adjustedModelSizeMax.getZ());

	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMin.getZ()); //Bottom face
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMin.getZ());
	glVertex3f(_adjustedModelSizeMax.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMax.getZ());
	glVertex3f(_adjustedModelSizeMin.getX(), _adjustedModelSizeMin.getY(), _adjustedModelSizeMax.getZ());

	glEnd();
}

void Model::drawBoundingSphere()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(getRadius(NG_2D), 10.0f, 10.0f);
	glPopMatrix();
}

void Model::updateLink() //Updates current model's attributes based on link attributes
{
	if (_linkType == NG_LINK_ABOVE)
	{
		_position = _link ->getPosition().add(Vector3f(0.0f, _link ->getMaxSize().getY() + 5.0f, 0.0f)); //The 10 is a hardcoded displacement above model
	}

	_active = _link ->getActive();
}

void Model::update(float &time)
{
	if (_active)
	{
		if (_linkType == NG_NO_LINK)
		{
			if (!_path ->getActive())
			{
				_previousPosition = _position;
				_velocity = _velocity.add(_acceleration.scalarMultiply(time));
				_position = _position.add(_velocity.scalarMultiply(time));

				_adjustedModelSizeMin = _adjustedModelSizeMin.add(_velocity.scalarMultiply(time));
				_adjustedModelSizeMax = _adjustedModelSizeMax.add(_velocity.scalarMultiply(time));
				_adjustedPosition = _adjustedPosition.add(_velocity.scalarMultiply(time));

				if (_position.getY() < 0) //Temp.
				{
					_position.setY(0.0f);
				}
			}
			else
			{
				_previousPosition = _position;
				_position = _path ->update();

				if (_path ->getActive() == false) //It finished pathing
				{
					_active = false; //Turn off
				}

				float theta = mRadToDeg(atan((_position.getX() - _previousPosition.getX()) / (_position.getZ() - _previousPosition.getZ()))); //TOA in SOH CAH TOA. Also radians

				if ((_position.getZ() - _previousPosition.getZ()) < 0) //TOA only deals with one side of the circle, we need to force the other side
				{
					theta += 180;
				}

				_rotate = Vector3f(0.0f, theta, 0.0f);
			}
		}
		else
		{
			updateLink();
		}

		transformations.makeHomogenous(_rotate, _position, _scale);
	}

	_animation.update();
}