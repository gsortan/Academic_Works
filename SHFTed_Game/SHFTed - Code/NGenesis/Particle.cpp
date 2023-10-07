#include "Particle.h"

Particle::Particle() //Inits default particle settings
{
	initVariables();
}

Particle::~Particle()
{

}

void Particle::initVariables()
{
	_lifetime = 5.0f; //May need to change based on duration
	_position = Vector3f(0.0f, 0.0f, 0.0f);
	_velocity = Vector3f(0.0f, 0.0f, 0.0f);
	_acceleration = Vector3f(0.0f, 0.0f, 0.0f);
	_active = true;

	_vShader = new Shader("Vertex_Easy.cg", "vParticle");
	_fShader = new Shader("Fragment_Easy.cg", "fTextureModulate");

	_color.r = 1.0f;
	_color.g = 1.0f;
	_color.b = 1.0f;
	_color.a = 1.0f;

	_decay = 0.05f; //Could also change decay instead of lifetime
	_weight = 1.0f;
	_size = 1.0f;

	_attenuationFactor = 1.0f;

	_wind = Vector3f(5.0f, 0.0f, 0.0f);
}

void Particle::initParticle(unsigned int type, Vector3f position) //Initializes particles based on type and num
{
	Vector3f* tempDirection = new Vector3f(1.0f, 0.0f, 0.0f);

	_position = position;

	_type = type;
	_lifetime = 10.0f;

	if (type == NG_WEATHER_SNOW) //Snow
	{
		setColor(1.0f, 0.0f, 1.0f, 1.0f);
		_wind = Vector3f(0.0f, 0.0f, 2.0f); //Default wind

		_position.setX(rand() % 600 - 300.0f);
		_position.setY(250.0f);
		_position.setZ(rand() % 600 - 400.0f);

		tempDirection ->setX((float) (rand() % 2));
		tempDirection ->setY(0.0f); //0 because it turns into -1 later
		tempDirection ->setZ((float) (rand() % 2));

		_weight = 1.0f; //Snow is light
		_size = rand() % 30 - 15.0f;
	}
	else if (type == NG_WEATHER_RAIN)
	{
		setColor(0.0f, 0.0f, 1.0f, 1.0f);
		_wind = Vector3f(0.0f, 0.0f, 2.0f); //Default wind

		_position.setX(rand() % 500 - 250.0f);
		_position.setY(1250.0f);
		_position.setZ(rand() % 500 - 350.0f);

		tempDirection ->setX((float) (rand() % 2));
		tempDirection ->setY(0.0f); //0 because it turns into -1 later
		tempDirection ->setZ((float) (rand() % 2));

		_weight = 8.0f; //Rain is heavier than snow
		_size = rand() % 8 - 4.0f;
	}
	else if (type == NG_PARTICLE_FIREBLAST) //The firey particle effects when a fireball hits an enemy
	{
		setColor(1.0f, 0.0f, 0.0f, 1.0f);
		_wind = Vector3f(0.0f, 0.0f, 0.0f); //No wind

		_position = position;

		tempDirection ->setX((float) (rand() % 2));
		tempDirection ->setY(1.0f);
		tempDirection ->setZ((float) (rand() % 2));

		_weight = 2.0f;
		_size = rand() % 10 - 5.0f;
	}
	else if (type == NG_PARTICLE_ICEBLAST) //The icey particle effects when an icicle hits an enemy
	{
		setColor(0.0f, 0.0f, 1.0f, 1.0f);
		_wind = Vector3f(0.0f, 0.0f, 0.0f); //No wind

		_position = position;

		tempDirection ->setX((float) (rand() % 2));
		tempDirection ->setY(1.0f);
		tempDirection ->setZ((float) (rand() % 2));

		_weight = 2.0f;
		_size = rand() % 10 - 5.0f;
	}
	else if (type == NG_PARTICLE_DEATH) //The death particle effects when an enemy dies
	{
		setColor(0.0f, 0.0f, 0.0f, 1.0f);
		_wind = Vector3f(0.0f, 0.0f, 0.0f); //No wind

		_position = position;

		tempDirection ->setX((float) (rand() % 2));
		tempDirection ->setY(1.0f);
		tempDirection ->setZ((float) (rand() % 2));

		_weight = 2.0f;
		_size = rand() % 20 - 10.0f;
	}
	else if (type == NG_PARTICLE_HIT) //The hit particle effects when an enemy is hit by your sword
	{
		setColor(0.0f, 0.0f, 0.0f, 1.0f);
		_wind = Vector3f(0.0f, 0.0f, 0.0f); //No wind

		_position.setX(rand() % 5 - 2.5f + position.getX());
		_position.setY(rand() % 10 + 5.0f + position.getY());
		_position.setZ(rand() % 5 - 2.5f + position.getZ());

		//_position = position;

		tempDirection ->setX((float) (rand() % 2));
		tempDirection ->setY(1.0f);
		tempDirection ->setZ((float) (rand() % 2));

		_weight = 1.0f;
		_size = rand() % 20 - 10.0f;
	}

	if (tempDirection ->getX() == 0) //Sets the proper directions
	{
		tempDirection ->setX(-1.0f);
	}

	if (tempDirection ->getY() == 0) //Sets the proper directions
	{
		tempDirection ->setY(-1.0f);
	}

	if (tempDirection ->getZ() == 0) //Sets the proper directions
	{
		tempDirection ->setZ(-1.0f);
	}

	_velocity.setX(tempDirection ->getX() * (rand() % 10 + 5.0f)); //Sets random velocity in random direction
	_velocity.setY(tempDirection ->getY() * (rand() % 10 + 5.0f));
	_velocity.setZ(tempDirection ->getZ() * (rand() % 10 + 5.0f));

	_acceleration.setX(_wind.getX());
	_acceleration.setY(_wind.getY() + NG_GRAVITY * _weight);
	_acceleration.setZ(_wind.getZ());

	_active = true; //Sets particle to active
}

void Particle::draw()
{
	_vShader ->bindAndEnableShaders();
	_fShader ->bindAndEnableShaders();

	shaderParameterHandler(_vShader);
	shaderParameterHandler(_fShader);

	glEnable(GL_BLEND); //Enables blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Enables alpha blending	
	glEnable(GL_POINT_SPRITE_ARB); //Point sprites turn points into "objects"
	glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE, GL_TRUE); //Enables texturing for point sprites, true interpolates UVs

	glPointSize(_size);

	glBegin(GL_POINTS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();

	glDisable(GL_POINT_SPRITE_ARB);
	glDisable(GL_BLEND);

	_vShader ->disableShaders();
	_fShader ->disableShaders();
}

void Particle::update() //Updates particle position
{
	_lifetime -= _decay; //Decays it

	if (_lifetime <= 0.0f)
	{
		if (_type == NG_WEATHER_SNOW || _type == NG_WEATHER_RAIN) //Weather stuff respawns
		{
			initParticle(_type, _position); //Reinitialize it if dead
		}
		else //Other ones do not
		{
			_active = false;
		}
	}
}

void Particle::shaderParameterHandler(Shader* shader) 
{
	if (shader ->getFileName() == "Vertex_Easy.cg") //Vertex Shaders
	{
		if (_type == NG_WEATHER_SNOW || _type == NG_WEATHER_RAIN)
		{
			cgSetParameter3f(shader ->translation, _position.getX() + Camera::getTranslation().getX(), _position.getY() + Camera::getTranslation().getY(), _position.getZ() + Camera::getTranslation().getZ());
		}
		else
		{
			cgSetParameter3f(shader ->translation, _position.getX(), _position.getY(), _position.getZ());
		}

		cgSetParameter4f(shader ->color, _color.r, _color.g, _color.b, _color.a);		
		cgSetParameter4f(shader ->rotationRow0, 1.0f, 0.0f, 0.0f, 0.0f); //Hard code to identity
		cgSetParameter4f(shader ->rotationRow1, 0.0f, 1.0f, 0.0f, 0.0f);
		cgSetParameter4f(shader ->rotationRow2, 0.0f, 0.0f, 1.0f, 0.0f);
		cgGLSetStateMatrixParameter(shader ->modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

		
		cgSetParameter3f(shader ->velocity, _velocity.getX(), _velocity.getY(), _velocity.getZ());
		cgSetParameter3f(shader ->acceleration, _acceleration.getX(), _acceleration.getY(), _acceleration.getZ());
		cgSetParameter1f(shader ->t, (15.0f - _lifetime)); //5 - decay since 5 is max and then divides because normalize
	}
	else if (shader ->getFileName() == "Fragment_Easy.cg")
	{
		glBindTexture(GL_TEXTURE_2D, _texture.get()); //Binds current texture to model
		cgGLSetTextureParameter(shader ->texture0, _texture.get());				
		cgGLEnableTextureParameter(shader ->texture0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	shader ->checkForCgError("enable decal texture");	
}

void Particle::setColor(float r, float g, float b, float a)
{
	_color.r = r;
	_color.g = g;
	_color.g  = b;
	_color.a  = a;
}

void Particle::setPosition(Vector3f &position)
{
	_position = position;
}

void Particle::setVelocity(Vector3f &velocity)
{
	_velocity = velocity;
}

void Particle::setWind(Vector3f &wind)
{
	_wind = wind;
}

void Particle::setSize(float size)
{
	_size = size;
}

void Particle::setTexture(Texture &texture)
{
	_texture = texture;
}

Vector3f Particle::getPosition()
{
	return _position;
}

Vector3f Particle::getVelocity()
{
	return _velocity;
}

Vector3f Particle::getAcceleration()
{
	return _acceleration;
}

float Particle::getSize()
{
	return _size;
}

float Particle::getDecay()
{
	return _decay;
}

float Particle::getLifetime()
{
	return _lifetime;
}

Vector3f Particle::getWind()
{
	return _wind;
}

bool Particle::getActive()
{
	return _active;
}

float Particle::getColor(unsigned int num)
{
	if (num == NG_RED)
	{
		return _color.a;
	}
	else if (num == NG_GREEN)
	{
		return _color.g;
	}
	else if (num == NG_BLUE)
	{
		return _color.b;
	}
	else
	{
		return _color.a;
	}
}

void Particle::setWeight(float weight)
{
	_weight = weight;
}

float Particle::getWeight()
{
	return _weight;
}