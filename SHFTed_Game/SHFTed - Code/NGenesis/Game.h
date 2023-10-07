#pragma once

#include "Vector3f.h"
#include "Model.h"
#include "Sprite.h"
#include "ToolsWindow.h"
#include "Shader.h"
#include "Keyboard.h"
#include "Quad.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Particle.h"
#include "Camera.h"
#include "Sound.h"
#include "Skeleton.h"
#include "Parser.h"
#include "Text.h"
#include "Timer.h"
#include "Skin.h"
#include "Character.h"
#include "Enemy.h"
#include "Include.h"

#include <vector>
#include <array>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <fstream>

#define NG_MAIN_MENU 0
#define NG_GAME 1
#define NG_GAME_FAILED 2
#define NG_GAME_CLEARED 3
#define NG_LOADING 4
#define NG_INTRO_CUTSCENE 5

#define NG_QUAD 0
#define NG_3D_QUAD 1
#define NG_2D_QUAD 2

#define NG_PROJECTILE_DESPAWN_DISTANCE 300

#define NG_ICE_INDEX 5 
#define NG_LIGHTNING_INDEX 6 
#define NG_FIRE_INDEX 7 
#define NG_SUN_INDEX 8 
#define NG_LEAF_INDEX 9 
#define NG_DAMAGE_INDEX 12 
#define NG_PAUSED_INDEX 11 

#define NG_SHRUB_COUNT 30
#define NG_CORAL_COUNT 10
#define NG_BIRD_COUNT 3
#define NG_FISH_COUNT 5

#define NG_FOREST_LEVEL 0
#define NG_DESERT_LEVEL 1

#define NG_SUNNY_WEATHER 0
#define NG_RAINY_WEATHER 1

class Game
{
public:
	Game();
	~Game();

	//Initializers
	void initVariables();
	void initSounds(); //TEMP
	void initMouse();
	void initWorkspace();
	void initMenu();
	void initLevel();

	//Uninitializers
	void unloadLevel();

	//Event Handlers
	void keyDownHandler(unsigned char &keyPressed, int &x, int &y);
	void keyUpHandler(unsigned char &keyReleased, int &x, int &y);
	void specialKeyDownHandler(int &keyPressed, int &x, int &y);
	void specialKeyUpHandler(int &keyReleased, int &x, int &y);
	void mouseClickHandler(int &mouseButton, int &state, int &x, int &y);
	void mouseMovementHandler(int &x, int &y);
	void enterFrame();

	//General Handlers
	void keyHandler();

	//Picking and Selection

	//Models
	void loadModels(); //Loads ALL the models
	std::vector<Enemy*>* getEnemyList(unsigned int level); //Returns the enemy
	void addLightToDrawList(Model &model, Vector3f lightColor, Vector3f position);
	void drawModels();
	void drawPreviewModel();
	void setLightMatrices();
	void drawShadowModels();

	//Particles
	void drawParticles();
	void spawnParticles(unsigned int num, unsigned int type, Vector3f position);

	//Textures
	void loadTextures(); //Loads ALL the textures
	std::vector<Texture>* getTextures(); //Returns the texture list

	//Sprites
	void loadSprites(); //Loads ALL the sprites
	void loadSpriteAndAddToDrawList(std::string spriteSheetFilename, int frameX, int frameY, int numOfAnimations, int layerIDValue, float posX, float posY);
	void addSpriteToDrawList(Sprite* sprite); //Sticks the sprite in the draw list
	std::vector<Sprite*>* getSpriteDrawList();
	void drawSprites();

	//Attacks
	void swordAttack();
	void fireAttack();
	void smashAttack();
	void iceAttack();
	void windscarAttack();

	//Skeletons and Skin Weights
	void loadSkeletons(); //Loads ALL the skeletons
	void loadSkins(); //Loads ALL the skins

	//Input and Output
	void readLevelData();
	void generateDataFile(); //Generates an external data file

	//Collision Detection
	bool mouseHitTestSprite(Sprite &sprite); //THIS SHOULD GO INTO A MOUSE CLASS WHEN I MAKE ONE
	
	//Creation of Stuff
	void createNewEnemy(unsigned int level, Model &model, Texture &texture, Vector3f spawnPos, Vector3f scale, float damage, float health, unsigned int type);
	void createNewInteractable(unsigned int level, Model &model, Texture &texture, Vector3f spawnPos, Vector3f scale);
	void createNewEnvironmental(unsigned int level, Model &model, Texture &texture, Vector3f spawnPos, Vector3f scale);

	//Random Updates
	void updateGame();
	void updateCutscene();
	void updateWeather();

	//QUAD
	void drawQuad(unsigned int type, Quad* quad); //Used as a handler function
	Quad* theQuad; //The main viewing quad
	Quad* the3DQuad; //The one storing only the 3d world
	Quad* the2DQuad; //The one storing only the 2d stuff
	Quad* shadowQuad; //Quad storing the shadows

	//Misc
	Character* getCharacter();
	Camera* getCamera();
	Timer* getTimer();
	unsigned int getMode();

	void displayWorldAxis();
	void drawText();

	void loadImageMap(char* mapName);

private:
	
	//Game Stuff
	Character* _mainChar;
	//Character* _mainCharShadow;
	Character* _mainCharSword;
	Model* _skybox; //Not in the env list cause it's special

	//Sound Effects
	Sound* _walkingSound; //Walking sound
	Sound* _forestMusic; //BG music
	Sound* _desertMusic; //BG music
	Sound* _weaponSwingSound; //Plays when weapon is swung
	Sound* _fireballSound;
	Sound* _iceSound;
	Sound* _quakeSound;
	Sound* _windscarSound;
	Sound* _boingSound; //Jump pad sound
	Sound* _tingSound; //For regular pick ups
	Sound* _tingSlashSound; //For story pick ups
	Sound* _weaponHitSound; //Plays for melee hit
	Sound* _waterSound; //3D sound for water area
	Sound* _poppingSound; //Popping sound for random stuff like jumping
	Sound* _splashSound; //Splash sound for when you fall into the water
	Sound* _rainSound; //Ambient rain sound
	Sound* _thunderSound; //Thunder sound
	Sound* _arrowSound; //Enemy arrow sound

	//Dialogue and Spoken Pieces
	Sound* _introDialogue[5]; //Five pieces of dialogue for the intro cutscene
	Sound* _oomSound; //Out of mana
	Sound* _lowHPSound; //Plays when low HP
	Sound* _shardsFoundDialogue; //The dialogue that points you in the right direction after all five shards are found

	Text* _healthText; //Text for healthbar
	Text* _manaText; //Text for manabar
	//Text* _expText; //Text for exp
	Text* _levelText; //Text for char's level

	Text* _promptText; //Text for prompts

	Text* _commonCollectableText; //Number of common collectables
	Text* _storyCollectableText; //Number of story collectables

	Text* _notificationText[5]; //Text that displays on the side of the screen that displays notifications
	Timer* _notificationTimer[5]; //The timers that control how long notifications are showed for

	Timer* _damageTimer; //Used to keep track of how long the damage sprite is on screen

	std::vector<Model> _projectileList; //The list containing our projectiles. Not pointers because new is slow and spamming new is bad
	std::vector<Model> _enemyProjectileList; //Enemy projectiles
	std::vector<Enemy*> _enemyList[2]; //List containing the enemies
	std::vector<Model*> _environmentList[2]; //The stuff in the environment that we can collision detection with
	std::vector<Model*> _healthbarList[2]; //List containing the enemy healthbars
	std::vector<Model*> _interactableList[2]; //Stuff in the environment that we interact with. AKA when we hit it something happens
	std::vector<Model*> _foliageList[2]; //Random things in the environment that we don't collision detection with
	std::vector<Model*> _levelList[2]; //Holds pieces of the level. Currently theres 2 levels. 
	std::vector<Model*> _critterList[2]; //Holds critters
	std::vector<Character*> _enemyWeaponList[2]; //List holding enemy weapons

	unsigned int _currentLevel; //Your level
	unsigned int _currentWeather; //Your weather

	Timer* _weatherTimer; //Used for misc weather things like thunder

	bool _tempBool;
	bool _hudInitialized;
	bool _mainCharInitialized;
	bool _introCutscene; //Controls whether or not you are doing your intro cutscene
	bool _showHUD; //Controls whether or not 2D elements are drawn
	bool _shardsActivated; //Controls whether or not the shards are activated, aka if the enemies have been all sent to kill you

	unsigned int _enemyActiveCounter; //Counts how many enemies are active

	//General Stuff
	unsigned int _mode;

	Camera* _camera;
	Parser* _parser;
	Timer* _timer;


	std::vector<Model> _modelList; //Vector containing all our models
	std::vector<Model> _lightList; //Vector stores all the objects that emit light
	std::vector<Model> _platformList; //Vector storing the platforms used for collision detection in our level
	std::vector<Texture> _textureList; //Vector containing all our textures
	std::vector<Sprite*> _spriteDrawList; //Vector containing sprites to be drawn
	std::vector<Sprite> _spriteList; //Vector containing all our sprites
	std::vector<Particle> _particleDrawList; //Vector holding particles to be drawn
	std::vector<Skeleton> _skeletonList; //Vector containing skeletons
	std::vector<Text*> _textList; //Vector containing all the text to be printed
	std::vector<Skin> _skinList; //Vector containing skins

	Model _preview; //A temporary model model used to preview textures and the model

	bool _wireframe;	
	bool _shaderOn;
	bool _paused;

	int _weatherParticlesPerFrame; 
	Particle _tempParticle; //Used so I don't have to reinstance new particles when spawning

	Keyboard _keyboard;

	struct mouseInfo
	{
		Vector3f referencePos; //Reference point used for scrolling
		Vector3f currentPos; //Current mouse viewport position

		bool leftDown; //Is true when button is down
		bool middleDown;
		bool rightDown;
	} _mouse;


	float _deltaT; //How much time has passed since last frame

	unsigned int _cutsceneScene; //Which scene of the cutscene are you on?
	Timer* _cutsceneTimer; //Timer used to control cutscene stuff

	//Indices
	unsigned int _LEVEL_MODEL_INDEX; //Stores the index of the object used as the surface as found in _modelList	
	unsigned int _CHAR_MODEL_INDEX;	
	unsigned int _SKY_MODEL_INDEX;	
	unsigned int _LIGHT_MODEL_INDEX;
	unsigned int _ENEMYSOLDIER_MODEL_INDEX;
	unsigned int _ENEMYARCHER_MODEL_INDEX;
	unsigned int _ENEMYHEAVY_MODEL_INDEX;
	unsigned int _HEALTHBAR_MODEL_INDEX;
	unsigned int _CHEST_MODEL_INDEX;
	unsigned int _TREE_MODEL_INDEX;
	unsigned int _JUMPPAD_MODEL_INDEX;
	
	unsigned int _POTION_MODEL_INDEX;
	unsigned int _PLANT_MODEL_INDEX;
	unsigned int _SNAKE_MODEL_INDEX;
	unsigned int _WATER_MODEL_INDEX; //More hacky than others; extracts water index while texturing in init
	unsigned int _SWORD_MODEL_INDEX;
	unsigned int _ARROW_MODEL_INDEX;
	unsigned int _FISH_MODEL_INDEX;
	unsigned int _CORAL_MODEL_INDEX;
	unsigned int _BIRD_MODEL_INDEX;
	unsigned int _CROSSBOW_MODEL_INDEX;
	unsigned int _CLUB_MODEL_INDEX;
	unsigned int _ENEMYSWORD_MODEL_INDEX;

	unsigned int _FIRESHARD_MODEL_INDEX;
	unsigned int _ICESHARD_MODEL_INDEX;
	unsigned int _LEAFSHARD_MODEL_INDEX;
	unsigned int _LIGHTNINGSHARD_MODEL_INDEX;
	unsigned int _SUNSHARD_MODEL_INDEX;

	unsigned int _FIREBALL_MODEL_INDEX;
	unsigned int _ICE_MODEL_INDEX;
	unsigned int _QUAKE_MODEL_INDEX;
	unsigned int _WINDSCAR_MODEL_INDEX;

	unsigned int _LEVEL_TEXTURE_INDEX; //Stores the index of the main textcure of the plane
	unsigned int _CHAR_TEXTURE_INDEX;	
	unsigned int _SKY_TEXTURE_INDEX;
	unsigned int _ENEMYSOLDIER_TEXTURE_INDEX;
	unsigned int _ENEMYARCHER_TEXTURE_INDEX;
	unsigned int _ENEMYHEAVY_TEXTURE_INDEX;
	unsigned int _HEALTHBAR_TEXTURE_INDEX;
	unsigned int _CHEST_TEXTURE_INDEX;
	unsigned int _TREE_TEXTURE_INDEX;
	unsigned int _JUMPPAD_TEXTURE_INDEX;

	unsigned int _HEALTHPOT_TEXTURE_INDEX;
	unsigned int _MANAPOT_TEXTURE_INDEX;
	unsigned int _PLANT_TEXTURE_INDEX;
	unsigned int _BLACK_TEXTURE_INDEX;
	unsigned int _SNAKE_TEXTURE_INDEX;
	unsigned int _WATER_TEXTURE_INDEX;
	unsigned int _HOUSE_TEXTURE_INDEX;
	unsigned int _LEVELWALL_TEXTURE_INDEX;
	unsigned int _WELL_TEXTURE_INDEX;
	unsigned int _RUIN_TEXTURE_INDEX;
	unsigned int _ARCH_TEXTURE_INDEX;
	unsigned int _PLATFORM_TEXTURE_INDEX;
	unsigned int _HENGE_TEXTURE_INDEX;
	unsigned int _ROCK_TEXTURE_INDEX;
	unsigned int _WALL_TEXTURE_INDEX;
	unsigned int _MOUNTAIN_TEXTURE_INDEX;
	unsigned int _SWORD_TEXTURE_INDEX;
	unsigned int _GEM_TEXTURE_INDEX;
	unsigned int _ARROW_TEXTURE_INDEX;
	unsigned int _FISH_TEXTURE_INDEX;
	unsigned int _CORAL_TEXTURE_INDEX; 
	unsigned int _BIRD_TEXTURE_INDEX;
	unsigned int _TOWER_TEXTURE_INDEX;
	unsigned int _SIGN_TEXTURE_INDEX;
	unsigned int _ENEMYSWORD_TEXTURE_INDEX;

	unsigned int _FIRESHARD_TEXTURE_INDEX;
	unsigned int _ICESHARD_TEXTURE_INDEX;
	unsigned int _LEAFSHARD_TEXTURE_INDEX;
	unsigned int _LIGHTNINGSHARD_TEXTURE_INDEX;
	unsigned int _SUNSHARD_TEXTURE_INDEX;

	unsigned int _SNOW_PARTICLE_TEXTURE_INDEX;
	unsigned int _RAIN_PARTICLE_TEXTURE_INDEX;
	unsigned int _STAR_PARTICLE_TEXTURE_INDEX;

	unsigned int _FIREBALL_TEXTURE_INDEX;
	unsigned int _ICE_TEXTURE_INDEX;
	unsigned int _QUAKE_TEXTURE_INDEX;
	unsigned int _WINDSCAR_TEXTURE_INDEX;

	unsigned int _QUAD_MODEL_INDEX;
	unsigned int _SUCCESS_CUTSCENE_QUAD_INDEX;
	unsigned int _FAILED_CUTSCENE_QUAD_INDEX;
	unsigned int _INTRO_CUTSCENE_QUAD_INDEX;
	unsigned int _LOADING_QUAD_INDEX;
};