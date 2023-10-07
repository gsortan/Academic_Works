

#include "Game.h"

Game::Game() //Initializes core variables
{
	//std::cout << "LOADING ASSETS AND INITIALIZING EDITOR." << std::endl;
	//std::cout << "WARNING: THIS MAY TAKE A LOT OF TIME IF THERE ARE LOTS OF ASSETS." << std::endl;
	//std::cout << std::endl;

	initVariables();
	initMouse();	
	loadModels();
	loadTextures();
	//loadSkeletons();
	loadSkins();
	loadSprites();
	initSounds(); //TEMP
	initWorkspace();
}

Game::~Game()
{
}

void Game::initVariables()
{
	_mode = NG_MAIN_MENU;

	_mainChar = new Character();
	//_mainCharShadow = new Character();
	_mainCharSword = new Character();
	_skybox = new Model();

	_walkingSound = new Sound();
	_forestMusic = new Sound();
	_desertMusic = new Sound();
	_weaponSwingSound = new Sound();
	_fireballSound = new Sound();
	_iceSound = new Sound();
	_quakeSound = new Sound();
	_windscarSound = new Sound();
	_boingSound = new Sound();
	_tingSound = new Sound();
	_tingSlashSound = new Sound();
	_weaponHitSound = new Sound();
	_waterSound = new Sound();
	_poppingSound = new Sound();
	_splashSound = new Sound();
	_rainSound = new Sound();
	_thunderSound = new Sound();
	_arrowSound = new Sound();

	_introDialogue[0] = new Sound(); //Four pieces of dialogue for the intro cutscene
	_introDialogue[1] = new Sound();
	_introDialogue[2] = new Sound();
	_introDialogue[3] = new Sound();
	_introDialogue[4] = new Sound();
	_oomSound = new Sound();
	_lowHPSound = new Sound();
	_shardsFoundDialogue = new Sound();

	//theQuad = new Quad();

	the3DQuad = new Quad();
	the2DQuad = new Quad();	
	shadowQuad = new Quad();

	//theQuad ->setShader(NG_FRAGMENT_SHADER, "Fragment_Blur.cg", "nonEdgeDetection");
	//shadowQuad ->setShader(NG_FRAGMENT_SHADER, "Fragment_Blur.cg", "nonEdgeDetection");
	the2DQuad ->setShader(NG_FRAGMENT_SHADER, "Fragment_Blur.cg", "nonEdgeDetection");

	_camera = new Camera();
	_timer = new Timer(); //General timer

	srand(time(0));
	//_backfaceCulling = true;
	_wireframe = false;
	_shaderOn = true;
	_weatherParticlesPerFrame = 2;

	_mouse.rightDown = false;
	_mouse.middleDown = false;
	_mouse.leftDown = false;	

	_damageTimer = new Timer();

	_cutsceneScene = 0;
	_cutsceneTimer = new Timer();

	//_enemyList[0] = new std::vector<Model>;

	_INTRO_CUTSCENE_QUAD_INDEX = 0;
	_FAILED_CUTSCENE_QUAD_INDEX = 0;
	_SUCCESS_CUTSCENE_QUAD_INDEX = 0;

	_tempBool = false;
	_hudInitialized = false;
	_mainCharInitialized = false;
	_introCutscene = false;
	_showHUD = true;
	_shardsActivated = false;
	_paused = false;

	_currentLevel = NG_FOREST_LEVEL;
	_currentWeather = NG_SUNNY_WEATHER;

	_weatherTimer = new Timer();
}

void Game::initSounds() //TEMP. Should have an init, but it needs to have a separate load
{
	//std::cout << "Loading Sounds" << std::endl;

	//_eight ->load("Audio/Wilhelm Scream.mp3", true, false, NG_LINEAR_ROLLOFF);
	//_thirtyTwo ->load("Audio/glass32.wav", true, false, NG_LINEAR_ROLLOFF);
	_walkingSound ->load("Audio/walk.wav", false, true, NG_LINEAR_ROLLOFF);
	_forestMusic ->load("Audio/The Magical Forest of MysteryHigh.mp3", false, true, NG_LINEAR_ROLLOFF);
	_desertMusic ->load("Audio/The Ancient Ruins of the Desert.mp3", false, true, NG_LINEAR_ROLLOFF);
	_weaponSwingSound ->load("Audio/CHARACTER_SWING.mp3", false, false, NG_LINEAR_ROLLOFF);
	_fireballSound ->load("Audio/FIREBALL.mp3", false, false, NG_LINEAR_ROLLOFF);
	_iceSound ->load("Audio/ICE.mp3", true, false, NG_LINEAR_ROLLOFF);
	_quakeSound ->load("Audio/QUAKE.mp3", true, false, NG_LINEAR_ROLLOFF);
	_windscarSound ->load("Audio/WINDSCAR.mp3", true, false, NG_LINEAR_ROLLOFF);
	_boingSound ->load("Audio/Bloop.wav", false, false, NG_LINEAR_ROLLOFF);
	_tingSound ->load("Audio/ting.wav", false, false, NG_LINEAR_ROLLOFF);
	_tingSlashSound ->load("Audio/highMetallicSlash.wav", false, false, NG_LINEAR_ROLLOFF);
	_weaponHitSound ->load("Audio/metallic_slash.wav", false, false, NG_LINEAR_ROLLOFF);
	_waterSound ->load("Audio/flowingWater2.wav", true, true, NG_LINEAR_ROLLOFF);
	_poppingSound ->load("Audio/ENERGY_BALL.mp3", false, false, NG_LINEAR_ROLLOFF);
	_splashSound ->load("Audio/splashEdit.wav", false, false, NG_LINEAR_ROLLOFF);
	_rainSound ->load("Audio/ambientRain.wav", false, true, NG_LINEAR_ROLLOFF);
	_thunderSound ->load("Audio/Thunder.wav", false, false, NG_LINEAR_ROLLOFF);
	_arrowSound ->load("Audio/BOW.mp3", false, false, NG_LINEAR_ROLLOFF);

	_introDialogue[0] ->load("Audio/Intro1.wav", false, false, NG_LINEAR_ROLLOFF);
	_introDialogue[1] ->load("Audio/Intro2.wav", false, false, NG_LINEAR_ROLLOFF);
	_introDialogue[2] ->load("Audio/Intro3.wav", false, false, NG_LINEAR_ROLLOFF);
	_introDialogue[3] ->load("Audio/Intro4.wav", false, false, NG_LINEAR_ROLLOFF);
	_introDialogue[4] ->load("Audio/Intro5.wav", false, false, NG_LINEAR_ROLLOFF);
	_oomSound ->load("Audio/You_Need_More_Mana.wav", false, false, NG_LINEAR_ROLLOFF);
	_lowHPSound ->load("Audio/Breathing.wav", false, true, NG_LINEAR_ROLLOFF);
	_shardsFoundDialogue ->load("Audio/shardsFound.wav", false, false, NG_LINEAR_ROLLOFF);
}

void Game::initMouse()
{
	_mouse.referencePos = Vector3f(0, 0, 0);
	_mouse.currentPos = Vector3f(0, 0, 0);
}

void Game::initWorkspace() //Initializes variables needed at the start of the editor. Kinda meh now.
{
	//Might be unnmecessary
	//_background ->play();

	//readLevelData();
	initMenu();
	//initLevel();
}

void Game::initMenu()
{
	std::cout << "Initializing menu." << std::endl;

	_camera ->path ->addNewPoint(Vector3f(-200.0f, 100.0f, -200.0f));
	_camera ->path ->addNewPoint(Vector3f(-200.0f, 100.0f, 200.0f));
	_camera ->path ->addNewPoint(Vector3f(200.0f, 100.0f, 200.0f));
	_camera ->path ->addNewPoint(Vector3f(200.0f, 100.0f, -200.0f));

	_skybox ->setMesh(_modelList[_SKY_MODEL_INDEX]);
	_skybox ->setTexture(0, &_textureList[_SKY_TEXTURE_INDEX]);
	//_skybox ->setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vFragmentLighting");
	//_skybox ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");
	
	for (unsigned int i = 0; i < _levelList[NG_FOREST_LEVEL].size(); ++i) //BRANAN LOOK AT THIS
	{
		if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Water.obj"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_WATER_TEXTURE_INDEX]);
			_WATER_MODEL_INDEX = i;
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Tree"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_TREE_TEXTURE_INDEX]);
			_levelList[NG_FOREST_LEVEL][i] ->setHitSize(0.95f);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("House"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_HOUSE_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("LevelWall"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_LEVELWALL_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Well"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_WELL_TEXTURE_INDEX]);
			//_levelList[NG_FOREST_LEVEL][i] ->setLightingCharacteristics(
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Ruin"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_RUIN_TEXTURE_INDEX]);
			_levelList[NG_FOREST_LEVEL][i] ->setHitSize(0.75f);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Arch"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_ARCH_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Platform"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_PLATFORM_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Henge"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_HENGE_TEXTURE_INDEX]);
			_levelList[NG_FOREST_LEVEL][i] ->setHitSize(0.75f);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Rock"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_ROCK_TEXTURE_INDEX]);
			_levelList[NG_FOREST_LEVEL][i] ->setHitSize(0.75f);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Wall"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_WALL_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Mountain"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_MOUNTAIN_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Tower"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_TOWER_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _levelList[NG_FOREST_LEVEL][i] ->getModelName().find("Sign"))
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_SIGN_TEXTURE_INDEX]);
		}
		else
		{
			_levelList[NG_FOREST_LEVEL][i] ->setTexture(0, &_textureList[_LEVEL_TEXTURE_INDEX]);
		}

		_levelList[NG_FOREST_LEVEL][i] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGoochWithShadow");
	}

	for (unsigned int i = 0; i < _levelList[NG_DESERT_LEVEL].size(); ++i)
	{
		_levelList[NG_DESERT_LEVEL][i] ->setTexture(0, &_textureList[_LEVEL_TEXTURE_INDEX]);
	}

	for (unsigned int i = 0; i < _interactableList[_currentLevel].size(); ++i)
	{
		if (std::string::npos != _interactableList[_currentLevel][i] ->getModelName().find("Chest"))
		{
			_interactableList[_currentLevel][i] ->setTexture(0, &_textureList[_CHEST_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _interactableList[NG_FOREST_LEVEL][i] ->getModelName().find("Jump"))
		{
			_interactableList[_currentLevel][i] ->setTexture(0, &_textureList[_JUMPPAD_TEXTURE_INDEX]);
		}
		else if (std::string::npos != _interactableList[NG_FOREST_LEVEL][i] ->getModelName().find("Gem"))
		{
			_interactableList[_currentLevel][i] ->setTexture(0, &_textureList[_GEM_TEXTURE_INDEX]);
		}

		_interactableList[_currentLevel][i] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGoochWithShadow");
	}

	float randX;
	float randY;
	float randZ;

	for (unsigned int i = 0; i < NG_SHRUB_COUNT; ++i)
	{
		randX = rand() % 2500 - 1250;
		randZ = rand() % 2500 - 1250;

		_foliageList[NG_FOREST_LEVEL].push_back(new Model());
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->setMesh(_modelList[_PLANT_MODEL_INDEX]);
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->setSpawnPoint(Vector3f(randX, 0, randZ));
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->setTexture(0, &_textureList[_PLANT_TEXTURE_INDEX]);
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->update(_deltaT);

		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGoochWithShadow");
	}

	for (unsigned int i = 0; i < NG_CORAL_COUNT; ++i)
	{
		//100, 0, -300
		//1350, 0, -1450

		randX = rand() % (1350 - 100) + 100;
		randZ = rand() % 1125; //This one is weird cause the number needs to be negative
		randZ = -randZ - 250; //needs to account for the min and negativeness

		_foliageList[NG_FOREST_LEVEL].push_back(new Model());
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->setMesh(_modelList[_CORAL_MODEL_INDEX]);
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->setSpawnPoint(Vector3f(randX, 0, randZ));
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->setTexture(0, &_textureList[_CORAL_TEXTURE_INDEX]);
		_foliageList[NG_FOREST_LEVEL][_foliageList[NG_FOREST_LEVEL].size() - 1] ->update(_deltaT);
	}

	for (unsigned int i = 0; i < NG_BIRD_COUNT; ++i)
	{
		_critterList[NG_FOREST_LEVEL].push_back(new Model());
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->setMesh(_modelList[_BIRD_MODEL_INDEX]);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->setTexture(0, &_textureList[_BIRD_TEXTURE_INDEX]);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->update(_deltaT);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->setScale(Vector3f(5.0f, 5.0f, 5.0f));

		for (unsigned int a = 0; a < 5; ++a) //5 path points
		{
			randX = rand() % 2500 - 1250;
			randY = rand() % (275 - 225) + 225;
			randZ = rand() % 2500 - 1250;

			_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->getPath() ->addNewPoint(Vector3f(randX, randY, randZ));
		}

		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->getPath() ->setActive(true);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->getPath() ->setInfinite(true);
	}

	for (unsigned int i = 0; i < NG_FISH_COUNT; ++i)
	{
		_critterList[NG_FOREST_LEVEL].push_back(new Model());
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->setMesh(_modelList[_FISH_MODEL_INDEX]);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->setTexture(0, &_textureList[_FISH_TEXTURE_INDEX]);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->update(_deltaT);

		for (unsigned int a = 0; a < 5; ++a) //5 path points
		{
			randX = rand() % (1300 - 200) + 200;
			randY = rand() % 5; //Just want it to surface everyonce and a while maybe
			randZ = rand() % 1150; //This one is weird cause the number needs to be negative
			randZ = -randZ - 300; //needs to account for the min and negativeness

			_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->getPath() ->addNewPoint(Vector3f(randX, randY, randZ));
		}

		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->getPath() ->setActive(true);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->getPath() ->setInfinite(true);
		_critterList[NG_FOREST_LEVEL][_critterList[NG_FOREST_LEVEL].size() - 1] ->getPath() ->setSpeed(0.001);
	}

	addLightToDrawList(_modelList[3], Vector3f(1.0f, 1.0f, 1.0f), Vector3f(0.0f, 2250.0f, 0.0f));

	//Should play all background sounds here and set unneeded ones to zero
	_forestMusic ->play();
	_forestMusic ->setVolume(0.5f); //0.5 is max loudness
	//_desertMusic ->play();
	_desertMusic ->setVolume(0.0f); //Starts off silent
	
	_waterSound ->setVolume(0.0f); //Starts off silent
	_waterSound ->play();
	//_waterSound ->setPosition(Vector3f(875.0f, 0.0f, -1000.0f));

	_walkingSound ->setVolume(0.5f); //Way too loud at 1
}

void Game::initLevel()
{
	std::cout << "Initializing level." << std::endl;		

	if (_hudInitialized == false /*&& _introCutscene == false*/)
	{
		_healthText = new Text(Conversion::floatToString(_mainChar ->getHealth()) + " / " + Conversion::floatToString(_mainChar ->getMaxHealth()), Vector3f(180.0f, 700.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
		_manaText = new Text(Conversion::floatToString(_mainChar ->getMana()) + " / " + Conversion::floatToString(_mainChar ->getMaxMana()), Vector3f(175.0f, 670.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
		//_expText = new Text(Conversion::floatToString(_mainChar ->getExperience()) + " / " + Conversion::floatToString(_mainChar ->getMaxExperience()), Vector3f(175.0f, 600.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
		_levelText = new Text("Level " + Conversion::floatToString(_mainChar ->getLevel()), Vector3f(30.0f, 540.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));

		_textList.push_back(_healthText);
		_textList.push_back(_manaText);
		//_textList.push_back(_expText);
		_textList.push_back(_levelText);

		for (int i = 0; i < 5; ++i) //Initializes and sets up the notification stuff
		{
			_notificationText[i] = new Text(" ", Vector3f(5.0f, -25 * i + 495.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
			_notificationTimer[i] = new Timer();

			_textList.push_back(_notificationText[i]);
		}

		_promptText = new Text("LOLCAKE", Vector3f(10, 10, 0), Vector3f(1.0f, 1.0f, 1.0f)); //Text for prompts
		_promptText ->setEffect(NG_TEXT_TYPE); //Types stuff out

		_commonCollectableText = new Text(" " + Conversion::intToString(_mainChar ->getCommonCount()), Vector3f(1060.0f, 700.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)); //Number of common collectables
		//_storyCollectableText = new Text("Shards Found: " + Conversion::intToString(_mainChar ->getStoryCount()), Vector3f(1135.0f, 625.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)); //Number of story collectables
		_storyCollectableText = new Text("Well, it's ice here.", Vector3f(1100.0f, 625.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)); //Story collectable riddles

		_textList.push_back(_promptText);
		//_textList.push_back(_commonCollectableText);
		_textList.push_back(_storyCollectableText);

		_hudInitialized = true;
	}

	if (_mainCharInitialized == false)
	{
		_mainChar ->setMesh(_modelList[_CHAR_MODEL_INDEX]);
		_mainChar ->setSpawnPoint(Vector3f(1245.0f, 0.0f, 1325.0f));
		_mainChar ->setRotate(Vector3f(0.0f, 180.0f, 0.0f));
		_mainChar ->setAccel(Vector3f(0.0f, NG_GRAVITY * 120, 0.0f)); //If I want it to be affected by gravity..
		_mainChar ->setTexture(0, &_textureList[_CHAR_TEXTURE_INDEX]);
		//_mainChar ->setSpeed(150.0f); //70 is default
		_mainChar ->setSpeed(150.0f); //70 is default
		_mainChar ->setEnvironmentList(NG_FOREST_LEVEL, _levelList[NG_FOREST_LEVEL]);
		_mainChar ->setEnvironmentList(NG_DESERT_LEVEL, _levelList[NG_DESERT_LEVEL]);
		_mainChar ->setInteractableList(NG_FOREST_LEVEL, _interactableList[NG_FOREST_LEVEL]);
		_mainChar ->setInteractableList(NG_DESERT_LEVEL, _interactableList[NG_DESERT_LEVEL]);
		_mainChar ->setNotificationStuff(_notificationText, _notificationTimer);
		_mainChar ->setCollectableText(*_commonCollectableText, *_storyCollectableText);
		_mainChar ->setPromptText(*_promptText);
		_mainChar ->getSkeletonAnimation() ->setSkin(_skinList[NG_CHARACTER_SKIN]); //Be careful with this, the define may not match up to the actual index
		_mainChar ->getSkeletonAnimation() ->bindSkeleton(_mainChar ->getMeshIndices(), _mainChar ->getMeshSizes(NG_VERTEX) / 3);
		_mainChar ->getSkeletonAnimation() ->animationSpeed = 8.0f;
		//_mainChar ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLightingAndShadows");
		_mainChar ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		//_mainChar ->setLightingCharacteristics( //BRANAN LOOK AT THIS
		//_mainChar ->setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vFragLighting");
		_mainChar ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");
		//_mainChar ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLighting"); //USE THIS INSTEAD OF ABOVE TO DISABLE GOOCH BRANAN
		//_mainChar ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fColor");

		/*_mainCharShadow ->setMesh(_modelList[_CHAR_MODEL_INDEX]);
		_mainCharShadow ->setSpawnPoint(Vector3f(1245.0f, 0.1f, 1325.0f));
		_mainCharShadow ->setColor(0.0f, 0.0f, 0.0f, 0.8f);
		_mainCharShadow ->getSkeletonAnimation() ->bindSkeleton(_mainChar ->getMeshIndices(), _mainChar ->getMeshSizes(NG_VERTEX) / 3);
		_mainCharShadow ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		_mainCharShadow ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fColor");*/

		_mainCharSword ->setMesh(_modelList[_SWORD_MODEL_INDEX]);
		_mainCharSword ->setSpawnPoint(Vector3f(1245.0f, 0.0f, 1325.0f));
		_mainCharSword ->setRotate(Vector3f(0.0f, 180.0f, 0.0f));
		_mainCharSword ->setTexture(0, &_textureList[_SWORD_TEXTURE_INDEX]);
		_mainCharSword ->getSkeletonAnimation() ->makeIntoSword();
		_mainCharSword ->getSkeletonAnimation() ->setSkin(_skinList[NG_SWORD_SKIN]); //Be careful with this, the define may not match up to the actual index
		_mainCharSword ->getSkeletonAnimation() ->bindSkeleton(_mainCharSword ->getMeshIndices(), _mainCharSword ->getMeshSizes(NG_VERTEX) / 3);
		_mainCharSword ->getSkeletonAnimation() ->animationSpeed = 8.0f;
		//_mainCharSword ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLightingAndShadows");
		_mainCharSword ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		//_mainCharSword ->setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vFragLighting");
		_mainCharSword ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");

		_mainCharInitialized = true;
	}	

	if (_currentLevel == NG_FOREST_LEVEL) //This part is kind of interesting. It loads everything in pieces during the intro cutscene
	{
		//Possible Enemy Spawns (On main ground)
		//1159.37, 0, 19.9809 - Right before water area
		//752.466, 0, -53.0175 - Next to water on the othjer side of the spawn loc
		//-176.116, 0, 311.122 - Middle of clearing (Big enemy)
		//213.145, 0, 1144.52 - Edge of clearing
		//-464.034, 0, 1160.66 - Edge of clearing
		//-752.48, 0, -601.161 - In front of houses
		//-999.214, 0, 298.558 - Middle of "forest"
		//-1103.82, 0, 1369.34 - Near beginning of jumping area

		//Possible Enemy Spawns (On elevated ground)
		//1141.9, 329.232, -1093.03 - Middle of big platform over water
		//-182.174, 365.598, 1634.19 - On "mountain range" area 1
		//650.24, 365.598, 1037.85 - On "mountain range" area 2

		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYSOLDIER_MODEL_INDEX], _textureList[_ENEMYSOLDIER_TEXTURE_INDEX], Vector3f(1160.0f, 0.0f, 20.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 150.0f, NG_MELEE); //Right before water area
		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYSOLDIER_MODEL_INDEX], _textureList[_ENEMYSOLDIER_TEXTURE_INDEX], Vector3f(755.0f, 0.0f, -55.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 150.0f, NG_MELEE); //Next to water on the othjer side of the spawn loc
		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYARCHER_MODEL_INDEX], _textureList[_ENEMYARCHER_TEXTURE_INDEX], Vector3f(215.0f, 0.0f, 1145.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 100.0f, NG_RANGED); //Edge of clearing
		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYHEAVY_MODEL_INDEX], _textureList[_ENEMYHEAVY_TEXTURE_INDEX], Vector3f(-175.0f, 0.0f, 310.0f), Vector3f(10.0f, 10.0f, 10.0f), 3.0f, 500.0f, NG_MELEE); //Middle of clearing (Big enemy)
		_enemyList[NG_FOREST_LEVEL][_enemyList[NG_FOREST_LEVEL].size() - 1] ->setHitSize(0.5f);
		
		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYARCHER_MODEL_INDEX], _textureList[_ENEMYARCHER_TEXTURE_INDEX], Vector3f(-465.0f, 0.0f, 1160.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 100.0f, NG_RANGED); //Edge of clearing
		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYSOLDIER_MODEL_INDEX], _textureList[_ENEMYSOLDIER_TEXTURE_INDEX], Vector3f(-750.0f, 0.0f, -600.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 150.0f, NG_MELEE); //In front of houses

		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYARCHER_MODEL_INDEX], _textureList[_ENEMYARCHER_TEXTURE_INDEX], Vector3f(-1000.0f, 0.0f, 300.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 100.0f, NG_RANGED); //Middle of forest
		createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMYSOLDIER_MODEL_INDEX], _textureList[_ENEMYSOLDIER_TEXTURE_INDEX], Vector3f(-1105.0f, 0, 1370.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 150.0f, NG_MELEE); //Near beginning of jumping area

		//createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMY_MODEL_INDEX], _textureList[_ENEMY_TEXTURE_INDEX], Vector3f(-1160.0f, 50.0f, -40.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 80.0f, NG_MELEE);
		//createNewEnemy(NG_FOREST_LEVEL, _modelList[_ENEMY_MODEL_INDEX], _textureList[_ENEMY_TEXTURE_INDEX], Vector3f(-740.0f, 50.0f, 470.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 80.0f, NG_RANGED);
			
		/*createNewEnemy(NG_DESERT_LEVEL, _modelList[_SNAKE_MODEL_INDEX], _textureList[_SNAKE_TEXTURE_INDEX], Vector3f(0.0f, 0.0f, -1000.0f), Vector3f(1.0f, 1.0f, 1.0f), 5.0f, 9001.0f, NG_MELEE);
		_enemyList[NG_DESERT_LEVEL][0] ->setAggroRange(9001); //HUGE AGGRO IS HUGE ITS GONNA KILL YOU OMG
		_enemyList[NG_DESERT_LEVEL][0] ->setSpeed(60.0f);
		_enemyList[NG_DESERT_LEVEL][0] ->setHitSize(0.1f); //His scale is too big so we lowering it like a boss*/

		createNewInteractable(NG_FOREST_LEVEL, _modelList[_LEAFSHARD_MODEL_INDEX], _textureList[_LEAFSHARD_TEXTURE_INDEX], Vector3f(910.0f, 235.0f, 1755.0f), Vector3f(2.0f, 2.0f, 2.0f)); //Ledge above spawn loc
		createNewInteractable(NG_FOREST_LEVEL, _modelList[_ICESHARD_MODEL_INDEX], _textureList[_ICESHARD_TEXTURE_INDEX], Vector3f(-815.0f, 55.0f, -745.0f), Vector3f(2.0f, 2.0f, 2.0f)); //On top of well
		createNewInteractable(NG_FOREST_LEVEL, _modelList[_LIGHTNINGSHARD_MODEL_INDEX], _textureList[_LIGHTNINGSHARD_TEXTURE_INDEX], Vector3f(360.0f, 30.0f, 1115.0f), Vector3f(2.0f, 2.0f, 2.0f)); //In between two cliff things
		createNewInteractable(NG_FOREST_LEVEL, _modelList[_SUNSHARD_MODEL_INDEX], _textureList[_SUNSHARD_TEXTURE_INDEX], Vector3f(485.0f, 990.0f, 470.0f), Vector3f(2.0f, 2.0f, 2.0f)); //Top of spire

		//Misc Locations for Shards
		//909.926, 203.97, 1756.73 - Ledge above spawn loc
		//1141.9, 329.232, -1093.03 - Middle of big platform over water
		//-1054.03, 0, -905.288 - Behind houses and rock
		//518.242, 0, 793.36 - In between two cliff things
		//483.031, 959.802, 468.915 - Top of spire
		//724.071, 654.441, 1769.87 - Top of inaccessable platform
	}
	else if (_currentLevel == NG_DESERT_LEVEL)
	{
		//createNewEnvironmental(NG_DESERT_LEVEL, _modelList[0], _textureList[0], Vector3f(0, 0, 0), Vector3f(1, 1, 1));
		//createNewInteractable(NG_DESERT_LEVEL, _modelList[0], _textureList[0], Vector3f(0, 0, 0));
		//createNewEnemy(NG_DESERT_LEVEL, _modelList[_ENEMY_MODEL_INDEX], _textureList[_ENEMY_TEXTURE_INDEX], Vector3f(1200.0f, 50.0f, 1300.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 100.0f);
	}
}

void Game::unloadLevel() //May need to restructure. Also don't know if I want to clean out char stuff.
{
	_environmentList[NG_FOREST_LEVEL].clear(); //Clears the model list
	_environmentList[NG_DESERT_LEVEL].clear(); //Clears the model list
	_interactableList[NG_FOREST_LEVEL].clear(); //Clears interactables
	_interactableList[NG_DESERT_LEVEL].clear(); //Clears interactables
	_enemyList[NG_FOREST_LEVEL].clear(); //Clears the enemy list
	_enemyList[NG_DESERT_LEVEL].clear(); //Clears the enemy list

	//_textList.clear(); //Clears text list
	//_lightList.clear(); //Clears lights

	_mainChar ->resetPlatformStuff();
}

void Game::keyDownHandler(unsigned char &keyPressed, int &x, int &y)
{
	_keyboard.update(keyPressed, 1);
	_keyboard.modifierKey = glutGetModifiers();

	switch (keyPressed)
	{
	case ('b'):
		/*if (_backfaceCulling == true)
		{
			_backfaceCulling = false;
		}
		else
		{
			_backfaceCulling = true;
		}*/
		break;
	case ('1'): //Melee attacks
	case ('6'): //Melee attacks
		if (_mode == NG_GAME)
		{
			if (_paused == false)
			{
				swordAttack();
			}
		}
		break;
	case ('2'): //Fireball
	case ('7'): //Fireball
		if (_mode == NG_GAME)
		{
			if (_paused == false)
			{
				fireAttack();
			}
		}
		break;
	case ('3'): //Quake
	case ('8'): //Quake
		if (_mode == NG_GAME)
		{
			if (_paused == false)
			{
				smashAttack();	
			}
		}
		break;
	case ('4'): //Ice
	case ('9'): //Ice
		if (_mode == NG_GAME)
		{
			if (_paused == false)
			{
				iceAttack();
			}
		}
		break;
	case ('5'): //Windscar
	case ('0'): //Windscar
		if (_mode == NG_GAME)
		{
			if (_paused == false)
			{
				windscarAttack();		
			}
		}
		break;
	case ('-'):
		break;
	case ('='): //TEMP
		/*if (_mode == NG_GAME)
		{
			if (_camera ->getMode() == NG_CAMERA_FREE)
			{
				_camera ->setMode(NG_CAMERA_THIRD_PERSON);
			}
			else //if (_camera ->getMode() == NG_CAMERA_THIRD_PERSON)
			{
				_camera ->setMode(NG_CAMERA_FIRST_PERSON);
			}
			else
			{
				_camera ->setMode(NG_CAMERA_FREE);
			}
		}*/
		break;
	case ('z'):
		if (_mode == NG_GAME)
		{
			if (_showHUD)
			{
				_showHUD = false;
			}
			else
			{
				_showHUD = true;
			}
		}
		break;
	case ('x'):
		if (_mode == NG_GAME)
		{
			if (_paused == false)
			{
				if (_mainChar ->getPromptData() >= 0
					&& _promptText ->getText() == "Press X to open the chest.") //CHESTS ONLY RIGHT NOW
				{
					_interactableList[_currentLevel].at(_mainChar ->getPromptData()) ->setActive(false); //Turn off chest
					int tempInt = (int) rand() % 6; //There are 6 attributes we have that we can boost

					_mainChar ->setBonus(tempInt);
				}
				else if (_promptText ->getText() == "Press X to activate the shards.")
				{
					_shardsActivated = true;
					_storyCollectableText ->setText("Defeat the army!");

					for (unsigned int i = 0; i < _interactableList[_currentLevel].size(); ++i) //Turns the jump pads inactive by making them grey
					{
						if (std::string::npos != _interactableList[_currentLevel][i] ->getModelName().find("Jump"))
						{
							_interactableList[_currentLevel][i] ->setTexture(0, &_textureList[_ROCK_TEXTURE_INDEX]);
						}
					}

					for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i)
					{
						if (_enemyList[_currentLevel][i] ->getScale().getX() != 10.0f) //Again, assumes big guy is only guy scaled 10. We don't want him.
						{
							_enemyList[_currentLevel][i] ->setActive(true); //Respawns if dead
							_enemyList[_currentLevel][i] ->setHealth(_enemyList[_currentLevel][i] ->getMaxHealth()); //Maxes HP				

							switch (i) //Spawns all the non big enemies to surround you, oh shit son.
							{
							case (0):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(1235.0f, 0.0f, 575.0f));
								break;
							case (1):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(1325.0f, 0.0f, 545.0f));
								break;
							case (2):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(1365.0f, 0.0f, 345.0f));
								break;
							case (3):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(1340.0f, 0.0f, 190.0f));
								break;
							case (4):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(1225.0f, 0.0f, 115.0f));
								break;
							case (5):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(1060.0f, 0.0f, 130.0f));
								break;
							case (6):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(980.0f, 0.0f, 325.0f));
								break;
							case (7):
								_enemyList[_currentLevel][i] ->setPosition(Vector3f(1000.0f, 0.0f, 520.0f));
								break;
							}

							_enemyList[_currentLevel][i] ->update(_deltaT);
							_enemyList[_currentLevel][i] ->getSpawnTimer() ->stop();
						}
					}

					//_mode == NG_GAME_CLEARED;
					//exit(2); //lol
				}
			}
		}
		break;
	case ('m'):
		//_mainChar ->getPosition().print();
		//createNewInteractable(NG_FOREST_LEVEL, _modelList[_SUNSHARD_MODEL_INDEX], _textureList[_SUNSHARD_TEXTURE_INDEX], _mainChar ->getPosition(), Vector3f(2.0f, 2.0f, 2.0f)); //Top of spire
		break;
	case ('p'):
		//generateDataFile();
		//createNewEnemy(_modelList[_ENEMY_MODEL_INDEX], _textureList[_ENEMY_TEXTURE_INDEX], Vector3f(1200.0f, 50.0f, 1300.0f), Vector3f(1.0f, 1.0f, 1.0f), 1.5f, 100.0f);
		//std::cout << _enemyList.size() << std::endl;

		if (_mode == NG_GAME)
		{
			if (_paused)
			{
				_paused = false;
				_spriteDrawList[NG_PAUSED_INDEX] ->setPosition(9001.0f, 9001.0f);
			}
			else
			{
				_paused = true;
				_spriteDrawList[NG_PAUSED_INDEX] ->setPosition(0.0f, 0.0f);
			}
		}
		break;
	case (27): //Esc
		exit(1); //Even though this is no longer consistent. Damnit.
		break;
	case (13): //Enter		
		if (_mode == NG_MAIN_MENU) //TESTING ONLY
		{
			//_mode = NG_LOADING;	//Skips intro cutscene from menu
		}
		else if (_mode == NG_INTRO_CUTSCENE)
		{
			_introDialogue[_cutsceneScene] ->stop(); //Stops the current dialogue piece

			if (_cutsceneScene < 4)
			{				
				++_cutsceneScene;
			}
			else
			{
				_introCutscene = false;
				_mode = NG_LOADING;
			}
		}
		else if (_mode == NG_GAME_FAILED) //Respawns you at the beginning of the level if you dieded
		{
			_mode = NG_GAME;
			_mainChar ->setHealth(_mainChar ->getMaxHealth() * 0.5); //Gives you half health only
			_mainChar ->setActive(true);
			_mainChar ->setRotate(Vector3f(0.0f, 180.0f, 0.0f)); //Sets it back to init rotate
			
			if (_currentLevel == NG_FOREST_LEVEL)
			{
				_mainChar ->setPosition(Vector3f(1245.0f, 0.0f, 1325.0f));
			}
			else if (_currentLevel == NG_DESERT_LEVEL)
			{
				_mainChar ->setPosition(Vector3f(0.0f, 0.0f, 0.0f));
			}

			/*for (unsigned int i = 0; i < _interactableList[NG_FOREST_LEVEL].size(); ++i)
			{
				if (_interactableList[NG_FOREST_LEVEL][i] ->getModelName() == _modelList[_STORYCOLLECTABLE_MODEL_INDEX].getModelName()) //If it's a story collectable
				{
					_interactableList[NG_FOREST_LEVEL][i] ->setActive(true); //Re initializes the story collectables
				}
			}*/

			/*for (unsigned int i = 0; i < _interactableList[NG_DESERT_LEVEL].size(); ++i)
			{
				if (_interactableList[NG_DESERT_LEVEL][i] ->getModelName() == _modelList[_STORYCOLLECTABLE_MODEL_INDEX].getModelName()) //If it's a story collectable
				{
					_interactableList[NG_DESERT_LEVEL][i] ->setActive(true); //Re initializes the story collectables
				}
			}*/

			if (_shardsActivated == false) //Only respawn if shards arent found
			{
				for (unsigned int i = 0; i < _enemyList[NG_FOREST_LEVEL].size(); ++i) //Respawns all the dead enemies. Yes. Even the giant one
				{
					if (_enemyList[NG_FOREST_LEVEL][i] ->getActive() == false) //If the enemy is dead
					{
						_enemyList[NG_FOREST_LEVEL][i] ->setHealth(_enemyList[_currentLevel][i] ->getMaxHealth());
						_enemyList[NG_FOREST_LEVEL][i] ->setActive(true); //Respawn
						_enemyList[NG_FOREST_LEVEL][i] ->setPosition(_enemyList[_currentLevel][i] ->getSpawnPoint()); //Back to the spawn point you go
					}
				}
			}

			//_enemyList[NG_DESERT_LEVEL][0] ->setPosition(_enemyList[NG_DESERT_LEVEL][0] ->getPosition()); //Sets the snake back to the beginning

			//_mainChar ->setStoryCount(0); //Resets the story counter
			//_storyCollectableText ->setText("Shards Found: " + Conversion::intToString(_mainChar ->getStoryCount())); //Resets the text too
		}
		break;
	case (' '):
		if (_mode == NG_GAME)
		{
			if (_paused == false)
			{
				if (_mainChar ->getPlatformIndex() != -1) //If not on a platform
				{
					_poppingSound ->play();
					_mainChar ->setVelocity(Vector3f(_mainChar ->getVelocity().getX(), _mainChar ->getSpeed() * 1.5, _mainChar ->getVelocity().getZ()));
				}
			}
		}
		break;
	}
}

void Game::keyUpHandler(unsigned char &keyReleased, int &x, int &y)
{
	_keyboard.update(keyReleased, 0);

	switch (keyReleased)
	{
	case ('1'):
	case ('2'):
	case ('3'):
	case ('4'):
	case ('5'):
	case ('6'):
	case ('7'):
	case ('8'):
	case ('9'):
	case ('0'):
		if (_mode == NG_GAME)
		{
			_keyboard.setAlreadyPressed(false);
		}
		break;
	case ('z'):
		_mainChar ->setGliding(false);
		break;
	}
}

void Game::specialKeyDownHandler(int &keyPressed, int &x, int &y)
{
	_keyboard.update(keyPressed, 1);
}

void Game::specialKeyUpHandler(int &keyReleased, int &x, int &y)
{
	_keyboard.update(keyReleased, 0);

	_keyboard.modifierKey = glutGetModifiers();
}

void Game::mouseClickHandler(int &mouseButton, int &state, int &x, int &y)
{
	switch (state)
	{
	case (GLUT_DOWN):
		switch (mouseButton)
		{
			case (GLUT_LEFT_BUTTON):
				_keyboard.modifierKey = glutGetModifiers(); //Gets the current key modifier
				_mouse.leftDown = true;
				if (_mode == NG_GAME)
				{	
					if (_keyboard.modifierKey == GLUT_ACTIVE_ALT) //Checks if alt key is down while left button is clicked
					{
						_camera ->setScrolling(NG_LEFT_MOUSE_BUTTON, true);
						_camera ->setReferenceAngle(_camera ->getRotationAngle());
						_mouse.referencePos = Vector3f(_mouse.currentPos.getX(), _mouse.currentPos.getY(), 0); //Sets reference position
					}
				}
				else if (_mode == NG_MAIN_MENU)
				{
					if (mouseHitTestSprite(*_spriteDrawList[1])) //Play game sprite
					{
						_introCutscene = true; //Do the intro cutscene
						_mode = NG_LOADING;
					}
					else if (mouseHitTestSprite(*_spriteDrawList[2])) //Exit game sprite
					{
						exit(1);
					}
				}
				break;
			case (GLUT_MIDDLE_BUTTON):	
				_keyboard.modifierKey = glutGetModifiers(); //Gets the current key modifier
				_mouse.middleDown = true;

				if (_mode == NG_GAME)
				{	
					if (_keyboard.modifierKey == GLUT_ACTIVE_ALT) //Checks if alt key is down while middle button is clicked
					{
						_camera ->setScrolling(NG_MIDDLE_MOUSE_BUTTON, true);
						_camera ->setReferencePosition(_camera ->getTranslation());
						_mouse.referencePos = Vector3f(_mouse.currentPos.getX(), _mouse.currentPos.getY(), 0); //Sets reference position
					}
				}
				break;
			case (GLUT_RIGHT_BUTTON):
				_keyboard.modifierKey = glutGetModifiers(); //Gets the current key modifier
				_mouse.rightDown = true;

				if (_mode == NG_GAME)
				{	
					if (_keyboard.modifierKey == GLUT_ACTIVE_ALT) //Checks if alt key is down while right button is clicked
					{
						
						_camera ->setScrolling(NG_RIGHT_MOUSE_BUTTON, true);
						_camera ->setReferencePosition(_camera ->getTranslation());
						_mouse.referencePos = Vector3f(_mouse.currentPos.getX(), _mouse.currentPos.getY(), 0); //Sets reference position
					}
				}
				break;
		}

		break;
	case (GLUT_UP):
		switch (mouseButton)
		{
			case (GLUT_LEFT_BUTTON):
				_mouse.leftDown = false;
				if (_mode == NG_GAME)
				{	
					_camera ->setScrolling(NG_LEFT_MOUSE_BUTTON, false);
				}
				break;
			case (GLUT_MIDDLE_BUTTON):
				_mouse.middleDown = false;
				if (_mode == NG_GAME)
				{	
					_camera ->setScrolling(NG_MIDDLE_MOUSE_BUTTON, false);
				}
				break;
			case (GLUT_RIGHT_BUTTON):
				_mouse.rightDown = false;
				if (_mode == NG_GAME)
				{	
					_camera ->setScrolling(NG_RIGHT_MOUSE_BUTTON, false);
				}
				break;
		}

		break;
	}
}

void Game::mouseMovementHandler(int &x, int &y)
{
	_mouse.currentPos = Vector3f((float) x, (float) y, 0.0f);

	_spriteDrawList[0] ->setPosition(x, 720 - y); //Why? BECAUSE I HATE YOU
	
	_camera ->scrollHandler(_mouse.currentPos.getX(), _mouse.currentPos.getY(), _mouse.referencePos.getX(), _mouse.referencePos.getY());
	Model::setEyePos(_camera ->getPosition().getVector());
}

void Game::enterFrame()
{
	keyHandler();

	if (_paused == false)
	{
		_skybox ->setRotate(Vector3f(0.0f, _skybox ->getRotate().getY() + 0.05f, 0.0f));
		_skybox ->update(_deltaT);

		_levelList[NG_FOREST_LEVEL][_WATER_MODEL_INDEX] ->setUVOffset(_levelList[NG_FOREST_LEVEL][_WATER_MODEL_INDEX] ->getUVOffset() + 0.0001f);

		/*for (unsigned int i = 0; i < _lightList.size(); ++i) //I need to update this so it gtfos
		{
			(_lightList)[i].update(_deltaT);
		}*/

		for (unsigned int i = 0; i < _critterList[_currentLevel].size(); ++i)
		{
			_critterList[_currentLevel][i] ->update(_deltaT);
		}
	}

	if (_mode == NG_GAME)
	{
		updateGame();
	}
	else if (_mode == NG_LOADING)
	{
		if (the2DQuad ->getCurrentTexture().getTextureName() == _textureList[_LOADING_QUAD_INDEX].getTextureName()) //Only load if the loading screen is up. I kind of hate this section btw. It's very inconsistent with the rest of the function
		{		
			if (_introCutscene == true)
			{
				initLevel();

				for (unsigned int i = 0; i < _textList.size(); ++i)
				{
					_textList[i] ->setText(""); //Clears out all the text
				}				

				_mode = NG_INTRO_CUTSCENE;

				//_spriteDrawList.clear(); //Clears the menu

				/*_camera ->setMode(NG_CAMERA_CMR);
				_camera ->path ->clearPath();
				_camera ->setFocus(_mainChar ->getPosition(), _mainChar ->getRotate());
				_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(-50.0f, 50.0f, -50.0f))); //Remember, CMR starts at point 2. So duplicate
				_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(-50.0f, 50.0f, -50.0f)));
				_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(50.0f, 50.0f, -50.0f)));
				_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(50.0f, 50.0f, 50.0f)));
				_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(-50.0f, 50.0f, 50.0f)));*/

				loadSprites();

				_timer ->getElapsedTime(); //Trying to restart timer
			}
			else
			{
				_mode = NG_GAME; //Now we're playing

				//Kinda hacky, but reset the text on the screen. It should naturally clear out again afterwards if needed anyways
				_healthText ->setText(Conversion::floatToString(_mainChar ->getHealth()) + " / " + Conversion::floatToString(_mainChar ->getMaxHealth()));
				_manaText ->setText(Conversion::floatToString(_mainChar ->getMana()) + " / " + Conversion::floatToString(_mainChar ->getMaxMana()));
				_levelText ->setText("Level " + Conversion::floatToString(_mainChar ->getLevel()));
				_promptText ->setText(""); //Text for prompts
				//_commonCollectableText ->setText("Common Collectables: " + Conversion::intToString(_mainChar ->getCommonCount())); //Number of common collectables
				//_storyCollectableText ->setText("Shards Found: " + Conversion::intToString(_mainChar ->getStoryCount())); //Number of story collectables
				_storyCollectableText ->setText("Well, it's ice here."); //Shard riddles
				//

				loadSprites();	
				_camera ->setTranslation(Vector3f(0.0f, 0.0f, 0.0f)); //Resets it's position
				_camera ->setMode(NG_CAMERA_THIRD_PERSON); //STOP CMRING
				_timer ->getElapsedTime(); //Trying to restart global timer	
			}
		}		
	}
	else if (_mode == NG_MAIN_MENU)
	{
		
	}
	else if (_mode == NG_INTRO_CUTSCENE)
	{
		updateCutscene();
	}
	else if (_mode == NG_GAME_FAILED)
	{

	}
	else if (_mode == NG_GAME_CLEARED)
	{
		if (!_desertMusic ->getIsPlaying())
		{
			_forestMusic ->stop();
			_rainSound ->stop();

			_desertMusic ->play();
			_desertMusic ->setVolume(0.5f);
		}

		if (_spriteDrawList[1] ->positionY < 720) //If not done scrolling..
		{
			_spriteDrawList[1] ->positionY += 2; //Moves the credits up slowly
		}
		else
		{
			exit(2);
		}
	}

	Sound::update();	
}

void Game::keyHandler() //Controls what key presses do. Mostly for movement. Called per frame, so smooth
{
	//Arrow keys
	if (_mode == NG_GAME)
	{
		if (_paused == false)
		{
			if (_mainChar ->getSliding() == false) //Sliding requires completely different controls
			{
				if ((_keyboard.getArrow(1) || _keyboard.getKey('a'))) //Left
				{			
					_mainChar ->setRotate(Vector3f(_mainChar ->getRotate().getX(), _mainChar ->getRotate().getY() + 5.0f, _mainChar ->getRotate().getZ()));

					if (_camera ->getMode() == NG_CAMERA_THIRD_PERSON || _camera ->getMode() == NG_CAMERA_FIRST_PERSON)
					{
						_camera ->setRotationAngle(_mainChar ->getRotate());
					}

					if (_walkingSound ->getIsPlaying() == false && _mainChar ->getPlatformIndex() != -1) //If the sound is not playing and the character is not in the air
					{
						_walkingSound ->play(); //Play it
					}
			
				}
				else if ((_keyboard.getArrow(3) || _keyboard.getKey('d'))) //Right
				{
					_mainChar ->setRotate(Vector3f(_mainChar ->getRotate().getX(), _mainChar ->getRotate().getY() - 5.0f, _mainChar ->getRotate().getZ()));
			
					if (_camera ->getMode() == NG_CAMERA_THIRD_PERSON || _camera ->getMode() == NG_CAMERA_FIRST_PERSON)
					{
						_camera ->setRotationAngle(_mainChar ->getRotate());
					}

					if (_walkingSound ->getIsPlaying() == false && _mainChar ->getPlatformIndex() != -1) //If the sound is not playing and the character is not in the air
					{
						_walkingSound ->play(); //Play it
					}
				}
				else
				{

				}

				if ((_keyboard.getArrow(0) || _keyboard.getKey('w') || (_mouse.leftDown == true && _mouse.rightDown == true))) //Up
				{				
					if (_keyboard.modifierKey != GLUT_ACTIVE_SHIFT) //If shift isnt held down
					{
						_mainChar ->setVelocity(Vector3f(sin(mDegToRad(_mainChar ->getRotate().getY())) * _mainChar ->getSpeed(), _mainChar ->getVelocity().getY(), cos(mDegToRad(_mainChar ->getRotate().getY())) * _mainChar ->getSpeed()));
					}
					else
					{
						_mainChar ->setVelocity(Vector3f(sin(mDegToRad(_mainChar ->getRotate().getY())) * _mainChar ->getSpeed() / 2, _mainChar ->getVelocity().getY(), cos(mDegToRad(_mainChar ->getRotate().getY())) * _mainChar ->getSpeed() / 2));
					}

					if (_walkingSound ->getIsPlaying() == false && _mainChar ->getPlatformIndex() != -1) //If the sound is not playing and the character is not in the air
					{
						_walkingSound ->play(); //Play it
					}
				}
				else if ((_keyboard.getArrow(2) || _keyboard.getKey('s'))) //Down
				{
					if (_keyboard.modifierKey != GLUT_ACTIVE_SHIFT) //If shift isnt held down
					{
						_mainChar ->setVelocity(Vector3f(sin(mDegToRad(_mainChar ->getRotate().getY())) * -_mainChar ->getSpeed(), _mainChar ->getVelocity().getY(), cos(mDegToRad(_mainChar ->getRotate().getY())) * -_mainChar ->getSpeed()));
					}
					else
					{
						_mainChar ->setVelocity(Vector3f(sin(mDegToRad(_mainChar ->getRotate().getY())) * -_mainChar ->getSpeed() / 2, _mainChar ->getVelocity().getY(), cos(mDegToRad(_mainChar ->getRotate().getY())) * -_mainChar ->getSpeed() / 2));
					}
			
					if (_walkingSound ->getIsPlaying() == false && _mainChar ->getPlatformIndex() != -1) //If the sound is not playing and the character is not in the air
					{
						_walkingSound ->play(); //Play it
					}
				}
				else //This else line is up here for a reason and there isnt one below for a reason
				{
					_mainChar ->setVelocity(Vector3f(0.0f, _mainChar ->getVelocity().getY(), 0.0f));

					if (_walkingSound ->getIsPlaying() == true) //If the sound is playing
					{
						_walkingSound ->stop(); //Stop it
					}
				}
			}
			else //SLIDING BRO
			{
				if ((_keyboard.getArrow(1) || _keyboard.getKey('a'))) //Left
				{			
					_mainChar ->setVelocity(_mainChar ->getVelocity().add(Vector3f(5.0f, 0.0f, 0.0f)));			
				}
				else if ((_keyboard.getArrow(3) || _keyboard.getKey('d'))) //Right
				{
					_mainChar ->setVelocity(_mainChar ->getVelocity().add(Vector3f(-5.0f, 0.0f, 0.0f)));
				}
				if ((_keyboard.getArrow(0) || _keyboard.getKey('w') || (_mouse.leftDown == true && _mouse.rightDown == true))) //Up
				{				
					//Do I want it so you could speed up?
				}
				else if ((_keyboard.getArrow(2) || _keyboard.getKey('s'))) //Down
				{
					//Do I want it so you could slow down?
				}
			}
		}

		/*if (_keyboard.getKey('q')) //Q, strafe left
		{
			_mainChar ->setVelocity(Vector3f(sin(mDegToRad(90 + _mainChar ->getRotate().getY())) * _mainChar ->getSpeed(), _mainChar ->getVelocity().getY(), cos(mDegToRad(90 + _mainChar ->getRotate().getY())) * _mainChar ->getSpeed()));
	
			if (_walkingSound ->getIsPlaying() == false) //If the sound is not playing
			{
				_walkingSound ->play(); //Play it
			}
		}
		else if (_keyboard.getKey('e')) //E, strafe right
		{
			_mainChar ->setVelocity(Vector3f(sin(mDegToRad(90 + _mainChar ->getRotate().getY())) * -_mainChar ->getSpeed(), _mainChar ->getVelocity().getY(), cos(mDegToRad(90 + _mainChar ->getRotate().getY())) * -_mainChar ->getSpeed()));
		
			if (_walkingSound ->getIsPlaying() == false) //If the sound is not playing
			{
				_walkingSound ->play(); //Play it
			}
		}*/
	}
}

void Game::loadModels() //Loads ALL the models
{
	_parser ->parseModels(_modelList, "ModelsSimple/");
	_parser ->parseModels(_levelList[NG_FOREST_LEVEL], "ModelsSimple/Level/Forest/");
	_parser ->parseModels(_levelList[NG_DESERT_LEVEL], "ModelsSimple/Level/Desert/");
	_parser ->parseModels(_environmentList[NG_FOREST_LEVEL], "ModelsSimple/Bounding Boxes/Forest/");
	_parser ->parseModels(_environmentList[NG_DESERT_LEVEL], "ModelsSimple/Bounding Boxes/Desert/");
	_parser ->parseModels(_interactableList[NG_FOREST_LEVEL], "ModelsSimple/Interactable/Forest/");
	_parser ->parseModels(_interactableList[NG_DESERT_LEVEL], "ModelsSimple/Interactable/Desert/");

	for (unsigned int i = 0; i < _modelList.size(); ++i)
	{
		if (_modelList[i].getModelName() == "jack.obj")
		//if (_modelList[i].getModelName() == "MAIN_CHARACTER_LOW_RES.obj")
		{
			_CHAR_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Level.obj")
		{
			_LEVEL_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Skybox.obj")
		{
			_SKY_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "healthbar.obj")
		{
			_HEALTHBAR_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Chest.obj")
		{
			_CHEST_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Enemy_Body.obj")
		{
			_ENEMYSOLDIER_MODEL_INDEX = i;			
		}
		else if (_modelList[i].getModelName() == "Enemy_Archer.obj")
		{
			_ENEMYARCHER_MODEL_INDEX = i;			
		}
		else if (_modelList[i].getModelName() == "Enemy_Heavy.obj")
		{
			_ENEMYHEAVY_MODEL_INDEX = i;			
		}
		else if (_modelList[i].getModelName() == "jumpPad.obj")
		{
			_JUMPPAD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "attackFireball.obj")
		{
			_FIREBALL_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "attackIce.obj")
		{
			_ICE_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "attackQuake.obj")
		{
			_QUAKE_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "attackWindscar.obj")
		{
			_WINDSCAR_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Potion.obj")
		{
			_POTION_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "plant1.obj")
		{
			_PLANT_MODEL_INDEX = i;
		}
		/*else if (_modelList[i].getModelName() == "Snake_Boss.obj")
		{
			_SNAKE_MODEL_INDEX = i;
		}*/
		else if (_modelList[i].getModelName() == "Sword zero Frozen.obj")
		{
			_SWORD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "StoryFire.obj")
		{
			_FIRESHARD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "StoryIce.obj")
		{
			_ICESHARD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "StoryLeaf.obj")
		{
			_LEAFSHARD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "StoryLightning.obj")
		{
			_LIGHTNINGSHARD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "StorySun.obj")
		{
			_SUNSHARD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Arrow_v3_TRIANGULATED.obj")
		{
			_ARROW_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Fish.obj")
		{
			_FISH_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Coral.obj")
		{
			_CORAL_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "BIRDIE.obj")
		{
			_BIRD_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Crossbow.obj")
		{
			_CROSSBOW_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "Club.obj")
		{
			_CLUB_MODEL_INDEX = i;
		}
		else if (_modelList[i].getModelName() == "E_Sword.obj")
		{
			_ENEMYSWORD_MODEL_INDEX = i;
		}
	}
}

std::vector<Enemy*>* Game::getEnemyList(unsigned int level) //Returns the enemy
{
	return &_enemyList[level];
}

void Game::addLightToDrawList(Model &model, Vector3f lightColor, Vector3f position)
{
	_lightList.push_back(model);
	Model::initLight(position, lightColor);
	_lightList[_lightList.size() - 1].setColor(lightColor.getX(), lightColor.getY(), lightColor.getZ(), 1);
	_lightList[_lightList.size() - 1].setPosition(position);
	_lightList[_lightList.size() - 1].setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vColor");
	_lightList[_lightList.size() - 1].setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fColor");
}

void Game::drawModels()
{	
	if (_mode != NG_GAME_FAILED && _mode != NG_GAME_CLEARED) //Dont draw anything if you dieded or won
	{
		/*for (unsigned int i = 0; i < _lightList.size(); ++i)
		{
			_lightList[i].draw(_backfaceCulling, _wireframe, _shaderOn);
		}*/

		for (unsigned int i = 0; i < _foliageList[_currentLevel].size(); ++i)
		{
			_foliageList[_currentLevel][i] ->setTexture(1, shadowQuad ->getTexture());
			_foliageList[_currentLevel][i] ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
		}

		for (unsigned int i = 0; i < _critterList[_currentLevel].size(); ++i)
		{
			_critterList[_currentLevel][i] ->setTexture(1, shadowQuad ->getTexture());
			_critterList[_currentLevel][i] ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
		}

		_skybox ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
	
		for (unsigned int i = 0; i < _levelList[_currentLevel].size(); ++i)
		{
			_levelList[_currentLevel][i] ->setTexture(1, shadowQuad ->getTexture());
			//_levelList[_currentLevel][i] ->setTexture(1, _textureList[0]);
			_levelList[_currentLevel][i] ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
		}

		for (unsigned int i = 0; i < _interactableList[_currentLevel].size(); ++i)
		{
			_interactableList[_currentLevel][i] ->setTexture(1, shadowQuad ->getTexture());
			_interactableList[_currentLevel][i] ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
		}		

		if (_mode == NG_GAME || _mode == NG_INTRO_CUTSCENE)
		{
			//std::cout << _currentLevel << std::endl;

			if (_mode != NG_INTRO_CUTSCENE) //Yea whatever. Don't draw this stuff during the cutscene. WHATEVER DUE.
			{
				_mainChar ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
				_mainCharSword ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);

				for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i)
				{
					_enemyList[_currentLevel][i] ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
					_healthbarList[_currentLevel][i] ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
					_enemyWeaponList[_currentLevel][i] ->draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
				}
			}

			//_mainChar ->getSkeletonAnimation() ->currentClip ->drawSkeleton();
			//_mainCharShadow ->draw(_backfaceCulling, _wireframe, _shaderOn);	
		
			for (unsigned int i = 0; i < _projectileList.size(); ++i)
			{
				_projectileList[i].draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
			}

			for (unsigned int i = 0; i < _enemyProjectileList.size(); ++i)
			{
				_enemyProjectileList[i].draw(NG_BACKFACE_CULLING, _wireframe, _shaderOn);
			}			
		}
	}
}

void Game::drawPreviewModel()
{
	_preview.draw(true, false, false);
}

void Game::setLightMatrices()
{
	/*for (unsigned int i = 0; i < _levelList[_currentLevel].size(); ++i)
	{
		_levelList[_currentLevel][i] ->setLightMatrix();
	}*/

	if (_mode == NG_GAME)
	{
		/*_mainChar ->setLightMatrix();
		_mainCharSword ->setLightMatrix();

		for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i)
		{
			_enemyList[_currentLevel][i] ->setLightMatrix();
		}*/

		Model::setLightMatrix();
	}
}

void Game::drawShadowModels()
{
	/*for (unsigned int i = 0; i < _levelList[_currentLevel].size(); ++i)
	{
		_levelList[_currentLevel][i] ->draw(_backfaceCulling, _wireframe, _shaderOn);
	}*/

	if (_mode == NG_GAME)
	{
		_mainChar ->draw(0, _wireframe, _shaderOn);
		_mainCharSword ->draw(0, _wireframe, _shaderOn);

		/*for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i)
		{
			_enemyList[_currentLevel][i] ->draw(0, _wireframe, _shaderOn);
		}*/
	}
}

void Game::drawParticles()
{
	for (unsigned int i = 0; i < _particleDrawList.size(); ++i) //Draws all the particles
	{
		if (_particleDrawList[i].getActive() == true)
		{
			_particleDrawList[i].update();
			_particleDrawList[i].draw();
		}
	}
}

void Game::spawnParticles(unsigned int num, unsigned int type, Vector3f position)
{
	if (type == NG_WEATHER_SNOW)
	{
		_tempParticle.setTexture(_textureList[_SNOW_PARTICLE_TEXTURE_INDEX]);
	}
	else if (type == NG_WEATHER_RAIN)
	{
		_tempParticle.setTexture(_textureList[_ICESHARD_TEXTURE_INDEX]);
	}
	else if (type == NG_PARTICLE_FIREBLAST)
	{
		_tempParticle.setTexture(_textureList[_FIREBALL_TEXTURE_INDEX]);
	}
	else if (type == NG_PARTICLE_ICEBLAST)
	{
		_tempParticle.setTexture(_textureList[_ICESHARD_TEXTURE_INDEX]);
	}
	else if (type == NG_PARTICLE_DEATH)
	{
		_tempParticle.setTexture(_textureList[_ROCK_TEXTURE_INDEX]);
	}
	else if (type == NG_PARTICLE_HIT)
	{
		_tempParticle.setTexture(_textureList[_STAR_PARTICLE_TEXTURE_INDEX]);
	}

	for (unsigned int i = 0; i < num; ++i)
	{		
		_tempParticle.initParticle(type, position);
		_particleDrawList.push_back(_tempParticle);
	}
}

void Game::loadTextures() //Loads ALL the textures
{
	_parser ->parseTextures(_textureList, "TexturesSimple/");

	for (unsigned int i = 0; i < _textureList.size(); ++i)
	{
		//if (_textureList[i].getTextureName() == "LevelGreen.jpg")
		if (_textureList[i].getTextureName() == "LevelGreenFUCKINSHADOWEDBITCH2.png")
		{
			_LEVEL_TEXTURE_INDEX = i;			
		}
		/*else if (_textureList[i].getTextureName() == "snowflake.png")
		{
			_SNOW_PARTICLE_TEXTURE_INDEX = i;			
		}*/
		else if (_textureList[i].getTextureName() == "Skybox_Day.jpg")
		{
			_SKY_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Temp Main Character Texture.png")
		//else if (_textureList[i].getTextureName() == "Main Character Texture.jpg")
		{
			_CHAR_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "red.jpg")
		{
			_HEALTHBAR_TEXTURE_INDEX = i;			
			_JUMPPAD_TEXTURE_INDEX = i;
			_CORAL_TEXTURE_INDEX = i;
			//_COMMONCOLLECTABLE_TEXTURE_INDEX = i;
			//_STORYCOLLECTABLE_TEXTURE_INDEX = i;
			//_SNAKE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Tree.png")
		{
			_TREE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Chest.png")
		{
			_CHEST_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Enemy_Soldier_Diffuse.png")
		{
			_ENEMYSOLDIER_TEXTURE_INDEX = i;			
		}
		else if (_textureList[i].getTextureName() == "Enemy_Archer.png")
		{
			_ENEMYARCHER_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Enemy_Heavy.png")
		{
			_ENEMYHEAVY_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "fireball.jpg")
		{
			_FIREBALL_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "ice.jpg")
		{
			_ICE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Quake.jpg")
		{
			_QUAKE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "windscar.jpg")
		{
			_WINDSCAR_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Loading.jpg")
		{
			_LOADING_QUAD_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "HP_Pot.jpg")
		{
			_HEALTHPOT_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "MP_Pot.jpg")
		{
			_MANAPOT_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "plant1.png")
		{
			_PLANT_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "water.png")
		{
			_WATER_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "House.jpg")
		{
			_HOUSE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Mountain.png")
		{			
			_MOUNTAIN_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "mountainEdit.png")
		{
			_LEVELWALL_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Well.png")
		{
			_WELL_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Ruin.png")
		{
			_RUIN_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Arch.png")
		{
			_ARCH_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Platform.png")
		{
			_PLATFORM_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Henge.png")
		{
			_HENGE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Grey.jpg")
		{
			_ROCK_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Wall.png")
		{
			_WALL_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Rachel's Sword Texture.png")
		{
			_SWORD_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Gem.png")
		{
			_GEM_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "StoryFire.png")
		{
			_FIRESHARD_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "StoryIce.png")
		{
			_ICESHARD_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "StoryLeaf.png")
		{
			_LEAFSHARD_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "StoryLightning.png")
		{
			_LIGHTNINGSHARD_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "StorySun.png")
		{
			_SUNSHARD_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "arrow.jpg")
		{
			_ARROW_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Fish.jpg")
		{
			_FISH_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Dove.jpg")
		{
			_BIRD_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "rain.png")
		{
			_RAIN_PARTICLE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Star.png")
		{
			_STAR_PARTICLE_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Tower3.jpg")
		{
			_TOWER_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "Sign.jpg")
		{
			_SIGN_TEXTURE_INDEX = i;
		}
		else if (_textureList[i].getTextureName() == "sword.jpg")
		{
			_ENEMYSWORD_TEXTURE_INDEX = i;
		}
	}
}

std::vector<Texture>* Game::getTextures()
{
	return &_textureList;
}

void Game::loadSprites() //Loads the sprites
{
	//_toolsWindow = new ToolsWindow(); //Auto calls the load sprites function

	//_parser ->parseSprites(_spriteList);

	_spriteDrawList.clear();

	loadSpriteAndAddToDrawList("cursor.png", 20, 21, 1, 10, 100, 100);

	if (_mode == NG_GAME)
	{				
		loadSpriteAndAddToDrawList("Health.png", 164, 22, 1, 1, 129, 720 - 25);
		loadSpriteAndAddToDrawList("Mana.png", 143, 22, 1, 1, 140, 720 - 55);
		loadSpriteAndAddToDrawList("Experience.png", 121, 8, 1, 1, 143, 720 - 71);
		loadSpriteAndAddToDrawList("HUDActive.png", 1280, 720, 1, 0, 0, 0);			
		
		loadSpriteAndAddToDrawList("Ice.png", 1280, 720, 1, 0, 9001, 9001);
		loadSpriteAndAddToDrawList("Lightning.png", 1280, 720, 1, 0, 9001, 9001);
		loadSpriteAndAddToDrawList("Fire.png", 1280, 720, 1, 0, 9001, 9001);
		loadSpriteAndAddToDrawList("CSun.png", 1280, 720, 1, 0, 9001, 9001);
		loadSpriteAndAddToDrawList("Leaf.png", 1280, 720, 1, 0, 9001, 9001);		
		
		loadSpriteAndAddToDrawList("Badges.png", 1280, 720, 1, 0, 0, 0);

		loadSpriteAndAddToDrawList("Paused.png", 1280, 720, 1, 0, 9001, 9001); //Starts this one off screen
		loadSpriteAndAddToDrawList("Damage.png", 1280, 720, 1, 0, 9001, 9001); //Starts this one off screen		
	}
	else if (_mode == NG_MAIN_MENU)
	{
		loadSpriteAndAddToDrawList("button_play.png", 400, 100, 1, 0, 1024 - 200, 420 - 50); //Hard coding 1280 * 0.8
		loadSpriteAndAddToDrawList("button_exit.png", 400, 100, 1, 0, 1024 - 200, 300 - 50); //Hard coding 1280 * 0.8
		loadSpriteAndAddToDrawList("SHFTed_logo.png", 512, 512, 1, 0, 100, 720 / 2 - 256); //Hard coding the location of this thing to hte middle of the screen
	}
	else if (_mode == NG_GAME_FAILED || _mode == NG_GAME_CLEARED)
	{
		loadSpriteAndAddToDrawList("Credits.png", 512, 2048, 1, 0, 640 - 256, -2048); //Hard coding window size		
	}
	else if (_mode == NG_INTRO_CUTSCENE)
	{
		loadSpriteAndAddToDrawList("Black.jpg", 1600, 900, 1, 0, 0, 0); //Loads in a giant black thing
		loadSpriteAndAddToDrawList("SHFT1.jpg", 1600, 848, 1, 0, 9001, 9001); //Starts off to the side
		loadSpriteAndAddToDrawList("SHFT2.jpg", 1600, 848, 1, 0, 9001, 9001); //Starts off to the side
	}
}

void Game::loadSpriteAndAddToDrawList(std::string spriteSheetFilename, int frameX, int frameY, int numOfAnimations, int layerIDValue, float posX, float posY) //This function is kinda dirty.
{
	Sprite* sprite = new Sprite(spriteSheetFilename, frameX, frameY, numOfAnimations, layerIDValue);
	sprite ->setInitPos(posX, posY);

	_spriteList.push_back(*sprite);
	_spriteDrawList.push_back(sprite);

	/*Sprite* temp;

	for (unsigned int i = 0; i < _spriteDrawList.size() - 1; ++i)
	{
		for (unsigned int a = i + 1; a < _spriteDrawList.size(); ++a)
		{
			if (_spriteDrawList[i] ->layerID > _spriteDrawList[a] ->layerID)
			{
				temp = _spriteDrawList[i];
				_spriteDrawList[i] = _spriteDrawList[a];
				_spriteDrawList[a] = _spriteDrawList[i];
			}
		}
	}*/
}

void Game::addSpriteToDrawList(Sprite* sprite)
{
	if (sprite) //Checks if sprite exists
	{
		this ->_spriteDrawList.push_back(sprite);
	}
}

std::vector<Sprite*>* Game::getSpriteDrawList()
{
	return &_spriteDrawList;
}

void Game::drawSprites() //Draws sprites using iterator
{
	if (_showHUD || _mode != NG_GAME)
	{
		glBindTexture(GL_TEXTURE_2D, 0);

		for (unsigned int i = 0; i < _spriteDrawList.size(); ++i)
		{
			_spriteDrawList[i] ->draw(); //Draws the non-tools window stuff
		}
	}
}

void Game::swordAttack()
{
	if (_keyboard.getAlreadyPressed() == false && _mainChar ->getAttacking() == false) //If you aren't attacking
	{
		_keyboard.setAlreadyPressed(true);
		_mainChar ->setAttacking(true);	
		_weaponSwingSound ->play(); //Plays the swing regardless of contact or not

		for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i)
		{
			if (_enemyList[_currentLevel][i] ->getActive() == true)
			{
				if (_mainChar ->meleeHit(_enemyList[_currentLevel][i] ->getPosition())) //FIX PLEASE
				{
					_weaponHitSound ->play(); //Damage sound goes here. Plays only when enemy is hit

					_enemyList[_currentLevel][i] ->damageTaken(_mainChar ->getMeleeDamage(), NG_MELEE); //Deals melee damage to enemy
					//spawnParticles(10, NG_PARTICLE_HIT, _enemyList[_currentLevel][i] ->getPosition());
				}
			}
		}

		//_mainChar ->setAttacking(false); //TEMP
	}
}

void Game::fireAttack()
{
	if (_keyboard.getAlreadyPressed() == false)
	{
		if (_mainChar ->getMana() >= 10) //10 is mana cost
		{
			_fireballSound ->play();
			_mainChar ->setMana(_mainChar ->getMana() - 10); //Deducts mana

			_projectileList.push_back(_modelList[_FIREBALL_MODEL_INDEX]);
			//_projectileList.push_back(new Model());
			_projectileList[_projectileList.size() - 1].setMesh(_modelList[_FIREBALL_MODEL_INDEX]);
			_projectileList[_projectileList.size() - 1].setTexture(0, &_textureList[_FIREBALL_TEXTURE_INDEX]);
			_projectileList[_projectileList.size() - 1].setSpawnPoint(_mainChar ->getPosition().add(Vector3f(0.0f, _mainChar ->getMaxSize().getY() / 2, 0.0f)));
			_projectileList[_projectileList.size() - 1].setVelocity(Vector3f(NG_RANGED_SPEED * sin(mDegToRad(_mainChar ->getRotate().getY())), 0, NG_RANGED_SPEED * cos(mDegToRad(_mainChar ->getRotate().getY())))); //Calculates a direction vector based on character rotation angle
			_projectileList[_projectileList.size() - 1].setRotate(_mainChar ->getRotate());
			_projectileList[_projectileList.size() - 1].setScale(Vector3f(2.0f, 2.0f, 2.0f));
			//_projectileList[_projectileList.size() - 1].setLightingCharacteristics( //BRANAN LOOK AT THIS AND THEN ALSO CASE 2 - 5

			_keyboard.setAlreadyPressed(true);
		}
		else
		{
			_oomSound ->stop();
			_oomSound ->play();
		}
	}
}

void Game::smashAttack()
{
	if (_keyboard.getAlreadyPressed() == false)
	{
		if (_mainChar ->getMana() >= 10) //10 is mana cost
		{
			_quakeSound ->play();
			_mainChar ->setMana(_mainChar ->getMana() - 10); //Deducts mana

			_projectileList.push_back(_modelList[_QUAKE_MODEL_INDEX]);
			//_projectileList.push_back(new Model());
			_projectileList[_projectileList.size() - 1].setColor(1.0f, 1.0f, 1.0f, 0.5f);
			_projectileList[_projectileList.size() - 1].setMesh(_modelList[_QUAKE_MODEL_INDEX]);
			_projectileList[_projectileList.size() - 1].setTexture(0, &_textureList[_QUAKE_TEXTURE_INDEX]);
			_projectileList[_projectileList.size() - 1].setSpawnPoint(_mainChar ->getPosition());
			_projectileList[_projectileList.size() - 1].setScale(Vector3f(1.0f, 1.0f, 1.0f));

			_keyboard.setAlreadyPressed(true);

			for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i)
			{
				if (_enemyList[_currentLevel][i] ->getPosition().calcDistance(_mainChar ->getPosition()) <= _mainChar ->getMeleeAttackRange() * 2) //Checks if the enemy is within 2 * your melee attack range
				{
					_enemyList[_currentLevel][i] ->damageTaken(_mainChar ->getMeleeDamage(), NG_MELEE); //This is going to be considered a melee attack
					_enemyList[_currentLevel][i] ->setStatusEffect(NG_STUN_STATUS); //Stun the enemy
				}
			}
		}
		else
		{
			_oomSound ->stop();
			_oomSound ->play();
		}
	}		
}

void Game::iceAttack()
{
	if (_keyboard.getAlreadyPressed() == false)
	{
		if (_mainChar ->getMana() >= 20) //20 is mana cost
		{
			_iceSound ->play();
			_mainChar ->setMana(_mainChar ->getMana() - 20); //Deducts mana

			for (unsigned int i = 0; i < 8; ++i)
			{
				_projectileList.push_back(_modelList[_ICE_MODEL_INDEX]);
				//_projectileList.push_back(new Model());
				_projectileList[_projectileList.size() - 1].setMesh(_modelList[_ICE_MODEL_INDEX]);
				_projectileList[_projectileList.size() - 1].setTexture(0, &_textureList[_ICE_TEXTURE_INDEX]);
				_projectileList[_projectileList.size() - 1].setSpawnPoint(_mainChar ->getPosition().add(Vector3f(0.0f, _mainChar ->getMaxSize().getY() / 2, 0.0f)));
				_projectileList[_projectileList.size() - 1].setVelocity(Vector3f(NG_RANGED_SPEED * sin(mDegToRad(_mainChar ->getRotate().getY() + i * 45)), 0, NG_RANGED_SPEED * cos(mDegToRad(_mainChar ->getRotate().getY() + i * 45)))); //Calculates a direction vector based on character rotation angle
				_projectileList[_projectileList.size() - 1].setRotate(Vector3f(0.0f, _mainChar ->getRotate().getY() + i * 45, 0.0f));
			}

			_keyboard.setAlreadyPressed(true);					
		}
		else
		{
			_oomSound ->stop();
			_oomSound ->play();
		}
	}			
}

void Game::windscarAttack()
{
	if (_keyboard.getAlreadyPressed() == false)
	{
		if (_mainChar ->getMana() >= 15) //15 is mana cost
		{
			_windscarSound ->play();
			_mainChar ->setMana(_mainChar ->getMana() - 15); //Deducts mana

			_projectileList.push_back(_modelList[_WINDSCAR_MODEL_INDEX]);
			//_projectileList.push_back(new Model());
			_projectileList[_projectileList.size() - 1].setMesh(_modelList[_WINDSCAR_MODEL_INDEX]);
			_projectileList[_projectileList.size() - 1].setTexture(0, &_textureList[_WINDSCAR_TEXTURE_INDEX]);
			_projectileList[_projectileList.size() - 1].setSpawnPoint(_mainChar ->getPosition().add(Vector3f(0.0f, _mainChar ->getMaxSize().getY() / 2, 0.0f)));
			_projectileList[_projectileList.size() - 1].setVelocity(Vector3f(NG_RANGED_SPEED * sin(mDegToRad(_mainChar ->getRotate().getY())), 0, NG_RANGED_SPEED * cos(mDegToRad(_mainChar ->getRotate().getY())))); //Calculates a direction vector based on character rotation angle
			_projectileList[_projectileList.size() - 1].setRotate(_mainChar ->getRotate());
			_projectileList[_projectileList.size() - 1].setScale(Vector3f(1.0f, 1.0f, 1.0f));

			_keyboard.setAlreadyPressed(true);
		}
		else
		{
			_oomSound ->stop();
			_oomSound ->play();
		}
	}	
}

void Game::loadSkeletons()
{
	_parser ->parseSkeletons(_skeletonList, "Skeletons/");
}

void Game::loadSkins()
{
	_parser ->parseSkins(_skinList, "Skin Weights/");
}

void Game::readLevelData()
{
	std::ifstream file;
	file.open("Data/Level.txt");

	std::string keyword;
	float tempX, tempY, tempZ;

	/*if (!file.fail())
	{
		while (file.good() && file >> keyword)
		{
			file >> tempX >> tempY >> tempZ; //Always has position immediately after

			if (keyword == "Chest")
			{				
				createNewInteractable(_modelList[_CHEST_MODEL_INDEX], _textureList[_CHEST_TEXTURE_INDEX], Vector3f(tempX, tempY, tempZ));
			}
			else if (keyword == "JPad")
			{
				createNewInteractable(_modelList[_JUMPPAD_MODEL_INDEX], _textureList[_JUMPPAD_TEXTURE_INDEX], Vector3f(tempX, tempY, tempZ));
			}
		}
	}*/

	file.close();
}

void Game::generateDataFile() //Spits out a data file. Most inefficient thing ever. However it's only run once pre-release, so.
{
	std::ofstream file("Data/Level.txt"); //Stores level data in that file

	/*if (!file.fail())
	{
		for (unsigned int i = 0; i < _interactableList.size(); ++i)
		{
			if (std::string::npos != _interactableList[i].getModelName().find("Chest"))
			{
				file << "Chest " << _interactableList[i].getAdjustedPosition().getX() << " " << _interactableList[i].getAdjustedPosition().getY() << " " << _interactableList[i].getAdjustedPosition().getZ() << std::endl;
			}
			else if (std::string::npos != _interactableList[i].getModelName().find("Jump"))
			{
				file << "JPad " << _interactableList[i].getAdjustedPosition().getX() << " " << _interactableList[i].getMinSize().getY()  << " " << _interactableList[i].getAdjustedPosition().getZ() << std::endl;
			}
		}
	}*/

	file.close();	
}

bool Game::mouseHitTestSprite(Sprite &sprite) //Checks if mouse is hitting the sprite sprite
{
	if (_mouse.currentPos.getX() >= sprite.positionX
		&& _mouse.currentPos.getX() <= sprite.positionX + sprite.sz.width
		&& 720 - _mouse.currentPos.getY() >= sprite.positionY //I hate this sprite loader. Writing my own next time. HARD CODING WINDOW SIZE
		&& 720 - _mouse.currentPos.getY() <= sprite.positionY + sprite.sz.height) //Why do you base your coordinates with origin at bottom left when opengl does it with top left?! HARD CODING WINDOW SIZE
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::createNewEnemy(unsigned int level, Model &model, Texture &texture, Vector3f spawnPos, Vector3f scale, float damage, float health, unsigned int type) //Creates a new enemy and it's healthbar
{
	std::cout << "Initializing new enemy." << std::endl;

	//_enemyList[level].push_back(_tempEnemy); //Temp Enemy
	_enemyList[level].push_back(new Enemy());
	_enemyList[level][_enemyList[level].size() - 1] ->setMesh(model);
	_enemyList[level][_enemyList[level].size() - 1] ->setType(type);
	_enemyList[level][_enemyList[level].size() - 1] ->initAI(this);
	_enemyList[level][_enemyList[level].size() - 1] ->setCharacter(_mainChar);
	_enemyList[level][_enemyList[level].size() - 1] ->setDamage(damage);
	_enemyList[level][_enemyList[level].size() - 1] ->setMaxHealth(health);
	_enemyList[level][_enemyList[level].size() - 1] ->setScale(scale);
	_enemyList[level][_enemyList[level].size() - 1] ->setEnvironmentList(level, _levelList[level]);
	_enemyList[level][_enemyList[level].size() - 1] ->setSpeed(60.0f);
	_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->animationSpeed = 2.0f;
	_enemyList[level][_enemyList[level].size() - 1] ->setSpawnPoint(spawnPos); //Starts in the air. Don't worry, it falls down.
	_enemyList[level][_enemyList[level].size() - 1] ->setAccel(Vector3f(0.0f, NG_GRAVITY * 60, 0.0f)); //If I want it to be affected by gravity..
	_enemyList[level][_enemyList[level].size() - 1] ->setTexture(0, &texture);
	_enemyList[level][_enemyList[level].size() - 1] ->setMeleeRange(25.0f); //Make it bigger cause you know

	if (model.getModelName() == _modelList[_ENEMYSOLDIER_MODEL_INDEX].getModelName()) //Skin the enemy only if it is the humanoid enemy
	{
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->setSkin(_skinList[NG_SOLDIER_SKIN]);
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->bindSkeleton(_enemyList[level][_enemyList[level].size() - 1] ->getMeshIndices(), _enemyList[level][_enemyList[level].size() - 1] ->getMeshSizes(NG_VERTEX) / 3);
		//_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLightingAndShadows");
		_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");

		//_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vFragLighting");
		//_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLighting");

		_enemyWeaponList[level].push_back(new Character());
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setMesh(_modelList[_ENEMYSWORD_MODEL_INDEX]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setTexture(0, &_textureList[_ENEMYSWORD_TEXTURE_INDEX]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setScale(scale);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->setSkin(_skinList[NG_ENEMYSWORD_SKIN]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->makeIntoSoldier(true);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->bindSkeleton(_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getMeshIndices(), _enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getMeshSizes(NG_VERTEX) / 3);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setActive(false); //TEMP
	}
	else if (model.getModelName() == _modelList[_ENEMYARCHER_MODEL_INDEX].getModelName()) //Skin the enemy only if it is the humanoid enemy
	{
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->setSkin(_skinList[NG_ARCHER_SKIN]);
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->makeIntoArcher(false);
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->bindSkeleton(_enemyList[level][_enemyList[level].size() - 1] ->getMeshIndices(), _enemyList[level][_enemyList[level].size() - 1] ->getMeshSizes(NG_VERTEX) / 3);
		//_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLightingAndShadows");
		_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		//_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vFragLighting");
		_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");

		_enemyWeaponList[level].push_back(new Character());
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setMesh(_modelList[_CROSSBOW_MODEL_INDEX]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setTexture(0, &_textureList[_ENEMYARCHER_TEXTURE_INDEX]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setScale(scale);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->setSkin(_skinList[NG_CROSSBOW_SKIN]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->makeIntoArcher(true);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->bindSkeleton(_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getMeshIndices(), _enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getMeshSizes(NG_VERTEX) / 3);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");
	}
	else if (model.getModelName() == _modelList[_ENEMYHEAVY_MODEL_INDEX].getModelName()) //Skin the enemy only if it is the humanoid enemy
	{
		_enemyList[level][_enemyList[level].size() - 1] ->setExperience(75); //Big guy gives a lot more exp
		_enemyList[level][_enemyList[level].size() - 1] ->setMeleeRange(100.0f); //Make it bigger cause you know
		_enemyList[level][_enemyList[level].size() - 1] ->setSpeed(30.0f);
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->setSkin(_skinList[NG_HEAVY_SKIN]);
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->makeIntoHeavy(false);
		_enemyList[level][_enemyList[level].size() - 1] ->getSkeletonAnimation() ->bindSkeleton(_enemyList[level][_enemyList[level].size() - 1] ->getMeshIndices(), _enemyList[level][_enemyList[level].size() - 1] ->getMeshSizes(NG_VERTEX) / 3);
		//_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLightingAndShadows");
		_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		//_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vFragLighting");
		_enemyList[level][_enemyList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");

		_enemyWeaponList[level].push_back(new Character()); //Blank weapon is blank.
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setMesh(_modelList[_CLUB_MODEL_INDEX]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setTexture(0, &_textureList[_ENEMYHEAVY_TEXTURE_INDEX]);
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setScale(scale);
		//_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->setSkin(_skinList[NG_CLUB_SKIN]);
		//_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->makeIntoHeavy(true);
		//_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getSkeletonAnimation() ->bindSkeleton(_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getMeshIndices(), _enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->getMeshSizes(NG_VERTEX) / 3);
		//_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "GPU_Skinning.cg", "skinMeshWithLighting");
		//_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_VERTEX_SHADER, "Vertex_Easy.cg", "vFragLighting");
		_enemyWeaponList[level][_enemyWeaponList[level].size() - 1] ->setShader(NG_FRAGMENT_SHADER, "Fragment_Easy.cg", "fLightingGooch");
	}

	//_healthbarList[level].push_back(_tempModel);
	_healthbarList[level].push_back(new Model());
	_healthbarList[level][_healthbarList[level].size() - 1] ->setMesh(_modelList[_HEALTHBAR_MODEL_INDEX]);
	//_healthbarList[_healthbarList.size() - 1].setLink(&_enemyList[_enemyList.size() - 1], NG_LINK_ABOVE); //Links the healthbar to the enemy
	_healthbarList[level][_healthbarList[level].size() - 1] ->setSpawnPoint(spawnPos); //Starts in same loc as model, but slightly higher up
	//_healthbarList[level][_healthbarList[level].size() - 1].setScale(Vector3f(3.0f, 1.0f, 2.0f));
	_healthbarList[level][_healthbarList[level].size() - 1] ->setTexture(0, &_textureList[_HEALTHBAR_TEXTURE_INDEX]);
}

void Game::createNewInteractable(unsigned int level, Model &model, Texture &texture, Vector3f spawnPos, Vector3f scale) //Creates a new interactable object like chests
{
	_interactableList[level].push_back(new Model());
	_interactableList[level][_interactableList[level].size() - 1] ->setMesh(model);
	_interactableList[level][_interactableList[level].size() - 1] ->setSpawnPoint(spawnPos);
	_interactableList[level][_interactableList[level].size() - 1] ->setTexture(0, &texture);
	_interactableList[level][_interactableList[level].size() - 1] ->setScale(scale);
	//_interactableList[level][_interactableList[level].size() - 1] ->setShader(1, "Fragment_Easy.cg", "fLightingGooch");
}

void Game::createNewEnvironmental(unsigned int level, Model &model, Texture &texture, Vector3f spawnPos, Vector3f scale) //Creates a new environmental object like trees and platforms
{
	//_environmentList[level].push_back(_tempModel);
	_environmentList[level].push_back(new Model());
	_environmentList[level][_environmentList[level].size() - 1] ->setMesh(model);
	_environmentList[level][_environmentList[level].size() - 1] ->setSpawnPoint(spawnPos);
	_environmentList[level][_environmentList[level].size() - 1] ->setScale(scale);
	_environmentList[level][_environmentList[level].size() - 1] ->setTexture(0, &texture);
}

void Game::updateGame()
{
	_deltaT = _timer ->getElapsedTime();	

	for (unsigned int i = 0; i < _lightList.size(); ++i)
	{
		Model::setLightPos(_mainChar ->getPosition().add(Vector3f(0.0f, _mainChar ->getMaxSize().getY(), 0.0f)), i);
	}

	/*for (unsigned int i = 0; i < _foliageList[_currentLevel].size(); ++i)
	{
		_foliageList[_currentLevel][i].update(_deltaT);
	}*/

	/*if (_weatherDrawList.size() < NG_MAX_WEATHER_PARTICLES)
	{
		spawnParticles(_weatherParticlesPerFrame, NG_SNOW);
	}*/

	/*for (unsigned int i = 0; i < _environmentList.size(); ++i)
	{
		(_environmentList)[i].update(_deltaT);
	}*/

	//Updates listener position for 3D sound
	//_waterSound ->setPosition(Vector3f(890.0f, 0.0f, -710.0f));
	//Sound::setListenerPos(_camera ->getPosition().getVector());
	//Sound::setListenerForward(_camera ->getFocusPosition().subtract(_camera ->getPosition().getVector())); //The direction vector is generally going to be focus - pos anyways
	//Sound::setListenerUp(Vector3f(0.0f, 1.0f, 0.0f));

	float distanceFromWater = 250 / sqrt((_camera ->getPosition().getX() - 725.0f) * (_camera ->getPosition().getX() - 725.0f)
									   + (_camera ->getPosition().getY() - 0.0f) * (_camera ->getPosition().getY() - 0.0f)
									   + (_camera ->getPosition().getZ() - -875.0f) * (_camera ->getPosition().getZ() - -875.0f));

	distanceFromWater *= distanceFromWater;

	_waterSound ->setVolume(distanceFromWater);

	if (_paused == false)
	{
		updateWeather();

		for (unsigned int i = 0; i < _interactableList[_currentLevel].size(); ++i)
		{
			(_interactableList)[_currentLevel][i] ->update(_deltaT);

			if (_interactableList[_currentLevel][i] ->getActive() == true) //Is it active?
			{
				if ((std::string::npos != _interactableList[_currentLevel][i] ->getModelName().find("Common")) //Is it any of these pick up ables?
					|| (std::string::npos != _interactableList[_currentLevel][i] ->getModelName().find("Story"))
					|| (std::string::npos != _interactableList[_currentLevel][i] ->getTextureName(0).find("HP"))
					|| (std::string::npos != _interactableList[_currentLevel][i] ->getTextureName(0).find("MP")))
				{
					_interactableList[_currentLevel][i] ->setRotate(_interactableList[_currentLevel][i] ->getRotate().add(Vector3f(0.0f, 10.0f, 0.0f))); //Rotates them
				}
			}
		}

		for (unsigned int i = 0; i < _projectileList.size(); ++i)
		{
			if (_projectileList[i].getActive() == true)
			{
				_projectileList[i].update(_deltaT);

				for (unsigned int a = 0; a < _enemyList[_currentLevel].size(); ++a)
				{
					if (_enemyList[_currentLevel][a] ->getActive() == true)
					{
						if (_projectileList[i].hitTest(*_enemyList[_currentLevel][a], NG_PILL_COLLISION) == NG_HIT) //If you hit an enemy
						{
							_projectileList[i].setActive(false); //Turns off

							if (_projectileList[i].getModelName() == _modelList[_FIREBALL_MODEL_INDEX].getModelName()) //Are you the fireball?
							{
								_enemyList[_currentLevel][a] ->damageTaken(_mainChar ->getRangedDamage(), NG_RANGED); //Deal standard damage
								_enemyList[_currentLevel][a] ->setStatusEffect(NG_BURN_STATUS); //Burn em.
								//spawnParticles(20, NG_PARTICLE_FIREBLAST, _enemyList[_currentLevel][a] ->getPosition());
							}
							/*else if (_projectileList[i].getModelName() == _modelList[_QUAKE_MODEL_INDEX].getModelName()) //Are you the smash attack?
							{
								_enemyList[_currentLevel][a] ->damageTaken(_mainChar ->getMeleeDamage(), NG_RANGED); //Deal standard damage
								_enemyList[_currentLevel][a] ->setStatusEffect(NG_STUN_STATUS); //Stun em.
							}*/
							else if (_projectileList[i].getModelName() == _modelList[_ICE_MODEL_INDEX].getModelName()) //Are you the ice attack?
							{
								_enemyList[_currentLevel][a] ->damageTaken(_mainChar ->getRangedDamage() * 0.5f, NG_RANGED); //Deals half as much damage cause its so awesome
								_enemyList[_currentLevel][a] ->setStatusEffect(NG_FREEZE_STATUS); //Freeze em.
								//spawnParticles(20, NG_PARTICLE_ICEBLAST, _enemyList[_currentLevel][a] ->getPosition());
							}
							else if (_projectileList[i].getModelName() == _modelList[_WINDSCAR_MODEL_INDEX].getModelName()) //Are you the wind scar?
							{
								_enemyList[_currentLevel][a] ->damageTaken(_mainChar ->getRangedDamage() * 2.5f, NG_RANGED); //Deals a ton of damage
							}

							//std::cout << "HIT" << std::endl;
						}
					}
				}

				if (_projectileList[i].getModelName() == _modelList[_FIREBALL_MODEL_INDEX].getModelName() //If fireball
					|| _projectileList[i].getModelName() == _modelList[_ICE_MODEL_INDEX].getModelName() //If ice
					|| _projectileList[i].getModelName() == _modelList[_WINDSCAR_MODEL_INDEX].getModelName()) //If windscar
				{
					if (_projectileList[i].getPosition().calcDistance(_mainChar ->getPosition()) >= NG_PROJECTILE_DESPAWN_DISTANCE) //If too far away from character
					{
						_projectileList[i].setActive(false);
					}
				}
				else if (_projectileList[i].getModelName() == _modelList[_QUAKE_MODEL_INDEX].getModelName()) //If quake
				{
					_projectileList[i].setRotate(_projectileList[i].getRotate().add(Vector3f(0.0f, 10.0f, 0.0f)));
					_projectileList[i].setScale(_projectileList[i].getScale().add(Vector3f(0.05f, 0.05f, 0.05f)));

					if (_projectileList[i].getScale().calcMagnitude() >= Vector3f(3.0f, 3.0f, 3.0f).calcMagnitude()) //Hacky I know
					{
						_projectileList[i].setActive(false);
					}
				}
			}
		}

		for (unsigned int i = 0; i < _enemyProjectileList.size(); ++i)
		{
			if (_enemyProjectileList[i].getActive() == true)
			{
				_enemyProjectileList[i].update(_deltaT);

				if (_mainChar ->getActive() == true)
				{
					if (_enemyProjectileList[i].hitTest(*_mainChar, NG_PILL_COLLISION) == NG_HIT) //If you hit an enemy
					{
						_enemyProjectileList[i].setActive(false); //Turns off
						_mainChar ->damageTaken(_enemyList[_currentLevel][0] ->getRangedDamage() * 5, NG_RANGED); //All the enemies deal the same damage anyways lewl

						_spriteDrawList[NG_DAMAGE_INDEX] ->setPosition(0.0f, 0.0f); //Put it on screen
						_damageTimer ->start();
					}
				}

				if (_enemyProjectileList[i].getModelName() == _modelList[_FIREBALL_MODEL_INDEX].getModelName()) //If fireball
				{
					if (_enemyProjectileList[i].getPosition().calcDistance(_mainChar ->getPosition()) >= NG_PROJECTILE_DESPAWN_DISTANCE) //If too far away from spawn
					{
						_enemyProjectileList[i].setActive(false);
					}
				}
			}
		}

		_enemyActiveCounter = 0; //Counts how many enemies are active

		for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i) //Enemy list
		{
			if (_enemyList[_currentLevel][i] ->getActive() == true) //Only update if alive
			{
				++_enemyActiveCounter;

				_enemyList[_currentLevel][i] ->update(_deltaT);
				_healthbarList[_currentLevel][i] ->update(_deltaT);			

				//This following section should be in the class. I HATE IT HERE
				_healthbarList[_currentLevel][i] ->setRotate(_mainChar ->getRotate()); //Links it with character so it's always facing us
				_healthbarList[_currentLevel][i] ->setActive(_enemyList[_currentLevel][i] ->getActive());

				if (_enemyList[_currentLevel][i] ->getScale().getX() != 10) //Like normal, assumes that the only thing scaled by 10 is the big guy
				{
					_healthbarList[_currentLevel][i] ->setScale(Vector3f(_enemyList[_currentLevel][i] ->getHealth() / _enemyList[_currentLevel][i] ->getMaxHealth(), 1.0f, _enemyList[_currentLevel][i] ->getHealth() / _enemyList[_currentLevel][i] ->getMaxHealth()));
					_healthbarList[_currentLevel][i] ->setSpawnPoint(_enemyList[_currentLevel][i] ->getPosition().add(Vector3f(0.0f, _enemyList[_currentLevel][i] ->getMaxSize().getY() + 5.0f, 0.0f))); //The 5 is a hardcoded displacement above model
				}
				else
				{
					_healthbarList[_currentLevel][i] ->setScale(Vector3f((_enemyList[_currentLevel][i] ->getHealth() / _enemyList[_currentLevel][i] ->getMaxHealth()) * 5, 2.0f, (_enemyList[_currentLevel][i] ->getHealth() / _enemyList[_currentLevel][i] ->getMaxHealth()) * 5)); //Scales more since big guy needs a more epic health bar
					_healthbarList[_currentLevel][i] ->setSpawnPoint(_enemyList[_currentLevel][i] ->getPosition().add(Vector3f(0.0f, _enemyList[_currentLevel][i] ->getMinSize().getY() + 15.0f, 0.0f))); //The 15 is a hardcoded displacement above model
				}

				_enemyWeaponList[_currentLevel][i] ->setRotate(_enemyList[_currentLevel][i] ->getRotate());				
				_enemyWeaponList[_currentLevel][i] ->setActive(_enemyList[_currentLevel][i] ->getActive());
				_enemyWeaponList[_currentLevel][i] ->setStatusEffect(_enemyList[_currentLevel][i] ->getStatusEffect());

				if (_enemyWeaponList[_currentLevel][i] ->getModelName() != _modelList[_CLUB_MODEL_INDEX].getModelName()) //Normal weapons are normal
				{
					_enemyWeaponList[_currentLevel][i] ->setPosition(_enemyList[_currentLevel][i] ->getPosition());
					_enemyWeaponList[_currentLevel][i] ->getSkeletonAnimation() ->setAnimation(_enemyList[_currentLevel][i] ->getSkeletonAnimation() ->getAnimation());
				}
				else //Clubs are hacked so theyre offscreen
				{
					_enemyWeaponList[_currentLevel][i] ->setPosition(Vector3f(9001.0f, 9001.0f, 9001.0f));
				}

				_enemyWeaponList[_currentLevel][i] ->update(_deltaT); //Dont likeee
				//End hate

				/*if (_enemyList[_currentLevel][i] ->getEnemyType() == NG_RANGED)
				{
					if (_enemyList[_currentLevel][i] ->getSkeletonAnimation() ->animState == ANIM_IDLE) //Hacky. But assumes that if any enemy is idle they are currently shooting you in the face
					{
						_enemyList[_currentLevel][i] ->setAttacking(true);
					}
					else
					{
						_enemyList[_currentLevel][i] ->setAttacking(false);
					}
				}*/				

				if (_enemyList[_currentLevel][i] ->getAttacking()) //Are you attacking?
				{
					if (_enemyList[_currentLevel][i] ->getPromptData() == NG_RANGED) //If you need to shoot a projectile
					{
						_arrowSound ->play();

						_enemyProjectileList.push_back(_modelList[_ARROW_MODEL_INDEX]);
						_enemyProjectileList[_enemyProjectileList.size() - 1].setMesh(_modelList[_ARROW_MODEL_INDEX]);
						_enemyProjectileList[_enemyProjectileList.size() - 1].setTexture(0, &_textureList[_ARROW_TEXTURE_INDEX]);
						_enemyProjectileList[_enemyProjectileList.size() - 1].setSpawnPoint(_enemyList[_currentLevel][i] ->getPosition().add(Vector3f(0.0f, _enemyList[_currentLevel][i] ->getMaxSize().getY() / 2, 0.0f)));
						_enemyProjectileList[_enemyProjectileList.size() - 1].setVelocity(Vector3f(NG_RANGED_SPEED * sin(mDegToRad(_enemyList[_currentLevel][i] ->getRotate().getY())), 0, NG_RANGED_SPEED * cos(mDegToRad(_enemyList[_currentLevel][i] ->getRotate().getY())))); //Calculates a direction vector based on character rotation angle
						_enemyProjectileList[_enemyProjectileList.size() - 1].setRotate(_enemyList[_currentLevel][i] ->getRotate().add(Vector3f(0.0f, 90.0f, 0.0f))); //Needs an additional 90 since it's modelled like that
						_enemyProjectileList[_enemyProjectileList.size() - 1].setScale(Vector3f(2.0f, 2.0f, 2.0f));
					}

					if (_enemyList[_currentLevel][i] ->getEnemyType() == NG_MELEE) //Must be a melee enemy
					{
						_mainChar ->damageTaken(_enemyList[_currentLevel][i] ->getMeleeDamage(), _enemyList[_currentLevel][i] ->getEnemyType()); //Take damage
						_spriteDrawList[NG_DAMAGE_INDEX] ->setPosition(0.0f, 0.0f); //Put it on screen
						_damageTimer ->start();
					}
				}

				if (_enemyList[_currentLevel][i] ->getActive() != false) //If enemy did not died this update
				{
					/*if (_mainChar ->hitTest(*_enemyList[_currentLevel][i], NG_CIRCLE_COLLISION) == NG_HIT) //Did an enemy hit you?
					{
						_mainChar ->damageTaken(_enemyList[_currentLevel][i] ->getMeleeDamage(), _enemyList[_currentLevel][i] ->getEnemyType()); //Take damage
						_spriteDrawList[NG_DAMAGE_INDEX] ->setPosition(0.0f, 0.0f); //Put it on screen
						_damageTimer ->start();
					}*/

					if /*(_enemyList[_currentLevel][i] ->getModelName() == _modelList[_SNAKE_MODEL_INDEX].getModelName() //If snake
						|| */(_enemyList[_currentLevel][i] ->getScale().getX() == 10) //Kinda hacky, but checks if you are the big soldier
					{
						if (_mainChar ->getPosition().calcDistance(_enemyList[_currentLevel][i] ->getPosition()) <= 500) //If you are less than 500 units away
						{
							the3DQuad ->shake(1, 3, 1 / (2 *_mainChar ->getPosition().calcDistance(_enemyList[_currentLevel][i] ->getPosition()))); //Shake! More intense the close you are
						}
					}
				}
				else //Clearly did die this update
				{
					if (!(_enemyList[_currentLevel][i] ->getScale().getX() == 10)) //Kinda hacky, but checks if you arent the big soldier
					{
						_enemyList[_currentLevel][i] ->getSpawnTimer() ->start(); //Starts the spawn timer
						_mainChar ->setExperience(_mainChar ->getExperience() + _enemyList[_currentLevel][i] ->getExperienceGiven()); //Give you exp
				
						int drop = rand() % 2; //Randomly figures out what youre supposed to get

						if (drop == 0) //Health at 0
						{
							createNewInteractable(_currentLevel, _modelList[_POTION_MODEL_INDEX], _textureList[_HEALTHPOT_TEXTURE_INDEX], _enemyList[_currentLevel][i] ->getPosition(), Vector3f(1.0f, 1.0f, 1.0f));
						}
						else //Mana at 1
						{
							createNewInteractable(_currentLevel, _modelList[_POTION_MODEL_INDEX], _textureList[_MANAPOT_TEXTURE_INDEX], _enemyList[_currentLevel][i] ->getPosition(), Vector3f(1.0f, 1.0f, 1.0f));
						}
					}
					else //You are the big soldier! It doesn't respawn and it drops a story collect
					{
						_mainChar ->setExperience(_mainChar ->getExperience() + _enemyList[_currentLevel][i] ->getExperienceGiven()); //Give you exp
						createNewInteractable(_currentLevel, _modelList[_FIRESHARD_MODEL_INDEX], _textureList[_FIRESHARD_TEXTURE_INDEX],  _enemyList[_currentLevel][i] ->getPosition().add(Vector3f(0.0f, 30.0f, 0.0f)), Vector3f(2.0f, 2.0f, 2.0f));
					}
				}
			}
			else //This enemy is dead!
			{
				if (_enemyList[_currentLevel][i] ->getSpawnTimer() ->isRunning()
					&& _enemyList[_currentLevel][i] ->getSpawnTimer() ->get(NG_TIMER_SECONDS) >= NG_RESPAWN_TIME
					&& _shardsActivated == false) //If you need to respawn
				{
					_enemyList[_currentLevel][i] ->setHealth(_enemyList[_currentLevel][i] ->getMaxHealth());
					_enemyList[_currentLevel][i] ->setActive(true); //Respawn
					_enemyList[_currentLevel][i] ->setPosition(_enemyList[_currentLevel][i] ->getSpawnPoint());
					_enemyList[_currentLevel][i] ->update(_deltaT);
					_enemyList[_currentLevel][i] ->getSpawnTimer() ->stop();
				}
			}
		}

		if (_shardsActivated == true) //Have you activated the shards and killed all the enemies?
		{
			for (unsigned int i = 0; i < _levelList[_currentLevel].size(); ++i)
			{
				if (std::string::npos != _levelList[_currentLevel][i] ->getModelName().find("Henge") //If you are a henge piece
					|| std::string::npos != _levelList[_currentLevel][i] ->getModelName().find("Arch")) //Or an arch piece
				{
					//_levelList[_currentLevel][i] ->setPosition(_levelList[_currentLevel][i] ->getPosition().add(Vector3f(0.0f, 5.0f, 0.0f))); //Make it go up. BRO.
					_levelList[_currentLevel][i] ->setVelocity(Vector3f(0.0f, 90.0f, 0.0f)); //MAKE IT GO UP.
					_levelList[_currentLevel][i] ->update(_deltaT);
				}
			}


			if (_enemyActiveCounter == 0)
			{
				if (Model::getGlobalLightIntensity() > 0) //Darken the world even more yo
				{
					Model::setGlobalLightIntensity(Model::getGlobalLightIntensity() - 0.01);
				}
				else
				{
					_mode = NG_GAME_CLEARED;
					loadSprites();
				}
			}
		}

		if (_mainChar ->getLowHP() == false) //If you are not low on health
		{
			if (_lowHPSound ->getIsPlaying() == true) //Stop playing this if its playing
			{
				_lowHPSound ->stop();
			}

			if (_damageTimer ->get(NG_TIMER_SECONDS) >= 3) //If the damage timer is on screen for more than 3 seconds
			{
				_damageTimer ->stop();			

				_spriteDrawList[NG_DAMAGE_INDEX] ->setPosition(9001, 9001); //Sets off screen
			}

			if (_shardsFoundDialogue ->getIsPlaying() == false) //we want to decrease the background music if you have all the shards
			{
				if (_currentLevel == NG_DESERT_LEVEL) //Changes background music to desert theme if desert level
				{
					if (_desertMusic ->getVolume() < 1.0f) //Makes music go to full volume if not already there
					{
						_desertMusic ->setVolume(_desertMusic ->getVolume() + 0.01f);
						_forestMusic ->setVolume(_forestMusic ->getVolume() - 0.01f);				
					}
				}
				else if (_currentLevel == NG_FOREST_LEVEL) //Changes background music to desert theme if desert level
				{
					if (_forestMusic ->getVolume() < 1.0f) //Makes music go to full volume if not already there
					{
						_forestMusic ->setVolume(_forestMusic ->getVolume() + 0.01f);
						_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
					}
				}
			}
		}
		else //You are low health!
		{
			_spriteDrawList[NG_DAMAGE_INDEX] ->setPosition(0, 0); //Sets on screen permanantly
		
			if (_currentLevel == NG_DESERT_LEVEL) //Changes background music to desert theme if desert level
			{
				if (_desertMusic ->getVolume() < 0.05f) //Caps sound volume to 0.5
				{
					_desertMusic ->setVolume(_desertMusic ->getVolume() + 0.01f);
					_forestMusic ->setVolume(_forestMusic ->getVolume() - 0.01f);				
				}
				else if (_desertMusic ->getVolume() > 0.05f) //Caps sound volume to 0.5
				{
					_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
					_forestMusic ->setVolume(_forestMusic ->getVolume() - 0.01f);
				}
			}
			else if (_currentLevel == NG_FOREST_LEVEL) //Changes background music to desert theme if desert level
			{
				if (_forestMusic ->getVolume() < 0.05f) //Caps sound volume to 0.5
				{
					_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
					_forestMusic ->setVolume(_forestMusic ->getVolume() + 0.01f);				
				}
				else if (_forestMusic ->getVolume() > 0.05f) //Caps sound volume to 0.5
				{
					_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
					_forestMusic ->setVolume(_forestMusic ->getVolume() - 0.01f);
				}
			}

			if (_lowHPSound ->getIsPlaying() == false)
			{
				_lowHPSound ->play(); //Play the Low HP sound if you are low HP
			}
		}

		for (unsigned int i = 0; i < 5; ++i)
		{
			if (_notificationTimer[i] ->isRunning())
			{
				if (_notificationTimer[i] ->get(NG_TIMER_SECONDS) >= 5) //5 seconds
				{					
					_notificationTimer[i] ->stop();
					_notificationTimer[i] ->reset();

					_notificationText[i] ->setText(" "); //BLANKEH
				}
			}
		}

		if (_mainChar ->getPromptData() == -1 
			&& _shardsFoundDialogue ->getIsPlaying() == false
			&& _promptText ->getText() != "Press X to activate the shards."
			|| _shardsActivated == true) //If prompt text is not needed..
		{
			_promptText ->setText(" "); //Clears out prompts for the frame
		}

		_mainChar ->update(_deltaT); //Dont likeee

		_mainCharSword ->setPosition(_mainChar ->getPosition());
		_mainCharSword ->setRotate(_mainChar ->getRotate());		

		_mainCharSword ->getSkeletonAnimation() ->setAnimation(_mainChar ->getSkeletonAnimation() ->getAnimation());

		/*if (_mainCharSword ->getSkeletonAnimation() == ANIM_ATTACK) //The sword needs to be hacked and rotated since it's not being rotated
		{
			_mainCharSword ->setRotate(_mainCharSword ->getRotate().add(Vector3f(0.0f, 0.0f, 90.0f)));
		}*/

		_mainCharSword ->update(_deltaT); //Dont likeee

		_spriteDrawList[1] ->setScale(Vector3f((_mainChar ->getHealth() / _mainChar ->getMaxHealth()), 1.0f, 1.0f)); //Scales bar based on health
		_spriteDrawList[2] ->setScale(Vector3f((_mainChar ->getMana() / _mainChar ->getMaxMana()), 1.0f, 1.0f)); //Scales bar based on mana
		_spriteDrawList[3] ->setScale(Vector3f((_mainChar ->getExperience() / _mainChar ->getMaxExperience()), 1.0f, 1.0f)); //Scales bar based on exp

		_healthText ->setText(Conversion::intToString((int) _mainChar ->getHealth()) + " / " + Conversion::floatToString(_mainChar ->getMaxHealth())); //Updates text
		_manaText ->setText(Conversion::intToString((int) _mainChar ->getMana()) + " / " + Conversion::floatToString(_mainChar ->getMaxMana()));
		//_expText ->setText(Conversion::floatToString(_mainChar ->getExperience()) + " / " + Conversion::floatToString(_mainChar ->getMaxExperience()));
		_levelText ->setText("Level " + Conversion::floatToString(_mainChar ->getLevel()));		

		/*float shadowPosY;

		if (_mainChar ->getPreviousPlatformIndex() != -1)
		{
			shadowPosY = _environmentList[_currentLevel][_mainChar ->getPreviousPlatformIndex()].getPosition().getY() + _environmentList[_currentLevel][_mainChar ->getPreviousPlatformIndex()].getMaxSize().getY() + 0.1;
			_mainCharShadow ->setPosition(Vector3f(_mainChar ->getPosition().getX(), shadowPosY, _mainChar ->getPosition().getZ())); //Don't like either.
			_mainCharShadow ->setColor(0.0f, 0.0f, 0.0f, (1 - (_mainChar ->getPosition().getY() - shadowPosY) / 90)); //Hard coding shadow threshold
		}
		else
		{
			_mainCharShadow ->setPosition(Vector3f(_mainChar ->getPosition().getX(), 0.1f, _mainChar ->getPosition().getZ())); //Don't like either.
		}

		_mainCharShadow ->setRotate(_mainChar ->getRotate());
		_mainCharShadow ->setScale(Vector3f(_mainChar ->getScale().getX(), 0.0f, _mainChar ->getScale().getZ()));
		_mainCharShadow ->update(_deltaT);*/

		if (_camera ->getMode() == NG_CAMERA_THIRD_PERSON || _camera ->getMode() == NG_CAMERA_FIRST_PERSON)
		{	
			_camera ->setFocus(_mainChar ->getPosition().add(Vector3f(0.0f, _mainChar ->getModelSize().getY() / 2, 0.0f)), _mainChar ->getRotate());

			if (_mainChar ->getSliding() == false) //Camera is translated further up if you are sliding, so you can actually see the slide
			{
				_camera ->setTranslation(Vector3f(_camera ->getInitTranslation().getX() + _mainChar ->getPosition().getX(), _camera ->getInitTranslation().getY(), _camera ->getInitTranslation().getZ() + _mainChar ->getPosition().getZ()));
			}
			else
			{
				_enemyList[NG_DESERT_LEVEL][0] ->setVelocity(Vector3f(0.0f, -sin(mDegToRad(30)) * _mainChar ->getSpeed() * 1.5, cos(mDegToRad(30)) * _mainChar ->getSpeed() * 1.5));
				_camera ->setTranslation(Vector3f(_camera ->getInitTranslation().getX() + _mainChar ->getPosition().getX(), _camera ->getInitTranslation().getY() + 25.0f, _camera ->getInitTranslation().getZ() + _mainChar ->getPosition().getZ()));

				if (_mainChar ->getPosition().getY() <= -4315) //Checks if below the slope threshold of (-606.333, -4313.9, 7644.57)
				{
					_camera ->setMode(NG_CAMERA_THIRD_PERSON_TARGET);
				}		
			}
		}
		else if (_camera ->getMode() == NG_CAMERA_THIRD_PERSON_TARGET)
		{
			_camera ->setFocus(_mainChar ->getPosition().add(Vector3f(0.0f, _mainChar ->getModelSize().getY() / 2, 0.0f)), _mainChar ->getRotate());

			if (_mainChar ->getVelocity().getY() < 0 && _currentLevel == NG_FOREST_LEVEL) //If you are done going up and still in forest
			{
				//unloadLevel();
				_currentLevel = NG_DESERT_LEVEL; //You are in the desert now
				Character::currentLevel = NG_DESERT_LEVEL;

				_mainChar ->setPosition(Vector3f(0.0f, _mainChar ->getPosition().getY(), 0.0f)); //Sets to above the origin
				_camera ->setMode(NG_CAMERA_THIRD_PERSON); //Back to regular

				//initLevel();				
			}
			else if (_currentLevel == NG_DESERT_LEVEL && _mainChar ->getPosition().getY() <= -4500) //If you are beyond a threshold in the desert level
			{
				_currentLevel = NG_FOREST_LEVEL;
				Character::currentLevel = NG_FOREST_LEVEL;
			
				_mainChar ->setPosition(_mainChar ->getSpawnPoint().add(Vector3f(0.0f, 250.0f, 0.0f))); //Sets to above spawn point
				_mainChar ->setVelocity(Vector3f(0.0f, 0.0f, 0.0f)); //Zeros velocity
				_mainChar ->setRotate(Vector3f(0.0f, 180.0f, 0.0f)); //Resets rotate
				_mainChar ->setSliding(false); //No longer sliding bro
				_camera ->setMode(NG_CAMERA_THIRD_PERSON); //Back to regular
			}
			/*else if (_mainChar ->getPosition().getY() <= _camera ->getPosition().getY() && _currentLevel == NG_DESERT_LEVEL) //If you have passed the camera on your way down into the desert
			{
			
			}*/
		}

		if (_mainChar ->getPlatformIndex() == -1) //Stops the walking sound if you are in the air
		{
			_walkingSound ->stop();
		}

		if (_mainChar ->getPromptData() != -1)
		{
			if (_mainChar ->getPromptData() == NG_PROMPT_JUMPPAD) //If you hit a regular jump pad
			{
				_boingSound ->play();
			}
			else if (_mainChar ->getPromptData() == NG_PROMPT_LARGEJUMPPAD) //If you hit a large jump pad
			{
				_boingSound ->play();
				_camera ->setMode(NG_CAMERA_THIRD_PERSON_TARGET);
			}
			else if (_mainChar ->getPromptData() == NG_PROMPT_COMMONCOLLECTABLE)
			{
				_tingSound ->play();
			}
			/*else if (_mainChar ->getPromptData() == NG_PROMPT_STORYCOLLECTABLE)
			{
				_tingSlashSound ->play();
			}*/
			else if (_mainChar ->getPromptData() == NG_PROMPT_ALLSHARDS)
			{
				_spriteDrawList[NG_ICE_INDEX] ->setPosition(0.0f, 0.0f);
				_spriteDrawList[NG_LIGHTNING_INDEX] ->setPosition(0.0f, 0.0f);
				_spriteDrawList[NG_FIRE_INDEX] ->setPosition(0.0f, 0.0f);
				_spriteDrawList[NG_SUN_INDEX] ->setPosition(0.0f, 0.0f);
				_spriteDrawList[NG_LEAF_INDEX] ->setPosition(0.0f, 0.0f);

				_tingSlashSound ->play(); //Extra ting for the final shard
				_shardsFoundDialogue ->play();
				_promptText ->setText("With all five shards found, Jack must now seek out the legendary alter to activate the ancient power.");
				_storyCollectableText ->setText("Find the alter!"); //Changes this
				_currentWeather = NG_RAINY_WEATHER; //It's now raining
				_weatherTimer ->start();
			}
			else if (_mainChar ->getPromptData() == NG_PROMPT_WATERDEATH)
			{
				_splashSound ->play();
			}
			else //Any other object must be a chest or shard
			{
				//if (_interactableList[_currentLevel][_mainChar ->getPromptData()] ->getModelName() != _modelList[_CHEST_MODEL_INDEX].getModelName()) //Checks if its not a chest, aka if its a shard
				if (_promptText ->getText() != "Press X to open the chest.") //Not a chest.
				{
					_tingSlashSound ->play();
					
					if (_interactableList[_currentLevel][_mainChar ->getPromptData()] ->getModelName() == _modelList[_ICESHARD_MODEL_INDEX].getModelName())
					{
						_spriteDrawList[NG_ICE_INDEX] ->setPosition(0.0f, 0.0f);

						if (_storyCollectableText ->getText() == "Well, it's ice here.")
						{
							if (_spriteDrawList[NG_LIGHTNING_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Lightning plain.");
							}
							else if (_spriteDrawList[NG_FIRE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Fire at his big feet!");
							}
							else if (_spriteDrawList[NG_SUN_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("The sun is sky high.");
							}
							else if (_spriteDrawList[NG_LEAF_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Leaf me on the ledge!");
							}
						}
					}
					else if (_interactableList[_currentLevel][_mainChar ->getPromptData()] ->getModelName() == _modelList[_LIGHTNINGSHARD_MODEL_INDEX].getModelName())
					{
						_spriteDrawList[NG_LIGHTNING_INDEX] ->setPosition(0.0f, 0.0f);
						
						if (_storyCollectableText ->getText() == "Lightning plain.")
						{
							if (_spriteDrawList[NG_ICE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Well, it's ice here.");
							}
							else if (_spriteDrawList[NG_FIRE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Fire at his big feet!");
							}
							else if (_spriteDrawList[NG_SUN_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("The sun is sky high.");
							}
							else if (_spriteDrawList[NG_LEAF_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Leaf me on the ledge!");
							}
						}
					}
					else if (_interactableList[_currentLevel][_mainChar ->getPromptData()] ->getModelName() == _modelList[_FIRESHARD_MODEL_INDEX].getModelName())
					{
						_spriteDrawList[NG_FIRE_INDEX] ->setPosition(0.0f, 0.0f);

						if (_storyCollectableText ->getText() == "Fire at his big feet!")
						{
							if (_spriteDrawList[NG_ICE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Well, it's ice here.");
							}
							else if (_spriteDrawList[NG_LIGHTNING_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Lightning plain.");
							}
							else if (_spriteDrawList[NG_SUN_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("The sun is sky high.");
							}
							else if (_spriteDrawList[NG_LEAF_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Leaf me on the ledge!");
							}
						}
					}
					else if (_interactableList[_currentLevel][_mainChar ->getPromptData()] ->getModelName() == _modelList[_SUNSHARD_MODEL_INDEX].getModelName())
					{
						_spriteDrawList[NG_SUN_INDEX] ->setPosition(0.0f, 0.0f);
						
						if (_storyCollectableText ->getText() == "The sun is sky high.")
						{
							if (_spriteDrawList[NG_ICE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Well, it's ice here.");
							}
							else if (_spriteDrawList[NG_LIGHTNING_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Lightning plain.");
							}
							else if (_spriteDrawList[NG_FIRE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Fire at his big feet!");
							}							
							else if (_spriteDrawList[NG_LEAF_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Leaf me on the ledge!");
							}
						}
					}
					else if (_interactableList[_currentLevel][_mainChar ->getPromptData()] ->getModelName() == _modelList[_LEAFSHARD_MODEL_INDEX].getModelName())
					{
						_spriteDrawList[NG_LEAF_INDEX] ->setPosition(0.0f, 0.0f);
						
						if (_storyCollectableText ->getText() == "Leaf me on the ledge!")
						{
							if (_spriteDrawList[NG_ICE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Well, it's ice here.");
							}
							else if (_spriteDrawList[NG_LIGHTNING_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Lightning plain.");
							}
							else if (_spriteDrawList[NG_FIRE_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("Fire at his big feet!");
							}
							else if (_spriteDrawList[NG_SUN_INDEX] ->positionX == 9001)
							{
								_storyCollectableText ->setText("The sun is sky high.");
							}							
						}
					}
				}
			}
		}

		if (_shardsFoundDialogue ->getIsPlaying()) //Sound playing?
		{
			if (_forestMusic ->getVolume() < 0.05f) //Caps sound volume to 0.2. ASSUMES THAT FOREST IS PLAYING
			{
				_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
				_forestMusic ->setVolume(_forestMusic ->getVolume() + 0.01f);				
			}
			else if (_forestMusic ->getVolume() > 0.05f) //Caps sound volume to 0.2. ASSUMES THAT FOREST IS PLAYING
			{
				_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
				_forestMusic ->setVolume(_forestMusic ->getVolume() - 0.01f);
			}

			if (_promptText ->getPrinting() == false && _cutsceneTimer ->isRunning() == false)
			{
				_cutsceneTimer ->start(); //Starts the timer after the text is done
				//++_cutsceneScene;
			}
	
			if (_cutsceneTimer ->isRunning())
			{
				if (_cutsceneTimer ->get(NG_TIMER_SECONDS) >= 2) //After two seconds stop and move on with the cutscene
				{
					_cutsceneTimer ->stop();
					_shardsFoundDialogue ->stop();					
				}
			}
		}

		if (_mainChar ->getActive() == false) //Did you die this update? Keep this last because crashing
		{
			_mode = NG_GAME_FAILED;
			_promptText ->setText("Press ENTER to retry.");
			//unloadLevel(); //Unload level
			//loadSprites(); //Reloads sprites
		}

		if (_mainChar ->getStoryCount() >= 5) //If you have all five story collects
		{
			if (abs(_mainChar ->getPosition().getX() - 1170.0f) <= 50 //If you are close enough to the alter
				&& abs(_mainChar ->getPosition().getZ() - 345.0f) <= 50
				//&& _shardsActivated == false)
				&& _promptText ->getText() != "Press X to activate the shards.")
			{
				//_mode == NG_GAME_CLEARED;
				_promptText ->setText("Press X to activate the shards.");
				//YOU ARE WINNER
			}
		}
	}
}

void Game::updateCutscene()
{
	if (_forestMusic ->getVolume() < 0.05f) //Caps sound volume to 0.2. ASSUMES THAT FOREST IS PLAYING
	{
		_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
		_forestMusic ->setVolume(_forestMusic ->getVolume() + 0.01f);				
	}
	else if (_forestMusic ->getVolume() > 0.05f) //Caps sound volume to 0.2. ASSUMES THAT FOREST IS PLAYING
	{
		_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.01f);
		_forestMusic ->setVolume(_forestMusic ->getVolume() - 0.01f);
	}

	if (_cutsceneScene == 0)
	{
		if (_introDialogue[0] ->getIsPlaying() == false) //This section is run only once really
		{		
			_spriteDrawList[1] ->setPosition(0.0f, 0.0f); //Moves the black to the beginning
			_spriteDrawList[2] ->setPosition(9001.0f, 9001.0f); //Moves the screens to the side
			_spriteDrawList[3] ->setPosition(9001.0f, 9001.0f); //Moves the screens to the side

			_promptText ->setText("It all started about five months ago.");
			_introDialogue[0] ->play();
		}

		if (_promptText ->getPrinting() == false && _cutsceneTimer ->isRunning() == false)
		{
			_cutsceneTimer ->start(); //Starts the timer after the text is done
			//++_cutsceneScene;
		}
	
		if (_cutsceneTimer ->isRunning())
		{
			if (_cutsceneTimer ->get(NG_TIMER_SECONDS) >= 2) //After two seconds stop and move on with the cutscene
			{
				_cutsceneTimer ->stop();
				++_cutsceneScene;
			}
		}
	}
	else if (_cutsceneScene == 1)
	{
		if (_introDialogue[1] ->getIsPlaying() == false) //This section is run only once really
		{
			_spriteDrawList[1] ->setPosition(9001.0f, 9001.0f); //Moves the black to the side
			_spriteDrawList[2] ->setPosition(0.0f, 0.0f); //Moves the screen to the origin
			_spriteDrawList[3] ->setPosition(9001.0f, 9001.0f); //Moves the screens to the side

			_promptText ->setText("A horde of enemies appeared seemingly out of nowhere.");
			_introDialogue[1] ->play();
		}

		_spriteDrawList[2] ->setPosition(_spriteDrawList[2] ->positionX - 0.1, _spriteDrawList[2] ->positionY - 0.1); //Scrolls it to the side

		if (_promptText ->getPrinting() == false && _cutsceneTimer ->isRunning() == false)
		{
			_cutsceneTimer ->start(); //Starts the timer after the text is done
			//++_cutsceneScene;
		}
	
		if (_cutsceneTimer ->isRunning())
		{
			if (_cutsceneTimer ->get(NG_TIMER_SECONDS) >= 2) //After two seconds stop and move on with the cutscene
			{
				_cutsceneTimer ->stop();
				++_cutsceneScene;
			}
		}
	}
	else if (_cutsceneScene == 2)
	{
		if (_introDialogue[2] ->getIsPlaying() == false) //This section is run only once really
		{
			_spriteDrawList[1] ->setPosition(9001.0f, 9001.0f); //Moves the black to the beginning
			_spriteDrawList[2] ->setPosition(9001.0f, 9001.0f); //Moves the screens to the side
			_spriteDrawList[3] ->setPosition(-320.0f, -128.0f); //Hard coded to the top right

			_promptText ->setText("Even Fantasyland's strongest heroes could not fend off the ruthless onslaught.");
			_introDialogue[2] ->play();
		}

		_spriteDrawList[3] ->setPosition(_spriteDrawList[3] ->positionX + 0.1, _spriteDrawList[3] ->positionY + 0.1); //Scrolls it to the side

		if (_promptText ->getPrinting() == false && _cutsceneTimer ->isRunning() == false)
		{
			_cutsceneTimer ->start(); //Starts the timer after the text is done
			//++_cutsceneScene;
		}
	
		if (_cutsceneTimer ->isRunning())
		{
			if (_cutsceneTimer ->get(NG_TIMER_SECONDS) >= 2) //After two seconds stop and move on with the cutscene
			{
				_cutsceneTimer ->stop();
				++_cutsceneScene;
			}
		}
	}
	else if (_cutsceneScene == 3)
	{
		if (_introDialogue[3] ->getIsPlaying() == false) //This section is run only once really
		{		
			_spriteDrawList[1] ->setPosition(0.0f, 0.0f); //Moves the black to the start
			_spriteDrawList[2] ->setPosition(9001.0f, 9001.0f); //Moves the screens to the side
			_spriteDrawList[3] ->setPosition(9001.0f, 9001.0f); //Moves the screens to the side

			_promptText ->setText("Eventually, they were overwhelmed.");
			_introDialogue[3] ->play();
		}

		if (_promptText ->getPrinting() == false && _cutsceneTimer ->isRunning() == false)
		{
			_cutsceneTimer ->start(); //Starts the timer after the text is done
			//++_cutsceneScene;
		}
	
		if (_cutsceneTimer ->isRunning())
		{
			if (_cutsceneTimer ->get(NG_TIMER_SECONDS) >= 2) //After two seconds stop and move on with the cutscene
			{
				_cutsceneTimer ->stop();
				++_cutsceneScene;
			}
		}
	}
	else if (_cutsceneScene == 4)
	{
		if (_introDialogue[4] ->getIsPlaying() == false) //This section is run only once really
		{
			_spriteDrawList[1] ->setPosition(9001.0f, 9001.0f); //Moves everything off screen
			_spriteDrawList[2] ->setPosition(9001.0f, 9001.0f); //Moves everything off screen
			_spriteDrawList[3] ->setPosition(9001.0f, 9001.0f); //Moves everything off screen

			/*for (unsigned int i = 0; i < _enemyList[_currentLevel].size(); ++i) //Updates enemies once to move them where they need ot be
			{
				if (_enemyList[_currentLevel][i].getActive() == true) //Only update if alive
				{
					_enemyList[_currentLevel][i].update(_deltaT);
					_healthbarList[_currentLevel][i].update(_deltaT);
				}
			}

			_mainChar ->update(_deltaT); //Same deal here
			_mainCharShadow ->update(_deltaT); //Same deal here*/

			_promptText ->setText("Legend has it that a powerful hero from ages past scattered and hid five magic shards in this area.");
			_introDialogue[4] ->play();
		}

		if (_promptText ->getPrinting() == false  //Make sure you arent printing
			&& _cutsceneTimer ->isRunning() == false //Make sure the timer is not running
			&& _promptText ->getText() == "Legend has it that a powerful hero from ages past scattered and hid five magic shards in this area.") //Oh God. This is so bad.
		{
			_cutsceneTimer ->start();

			//_promptText ->setText("It is up to Jack now to gather these pieces to restore order to the land.");
		}
		else if (_promptText ->getPrinting() == false  //Make sure you arent printing
				 && _cutsceneTimer ->get(NG_TIMER_SECONDS) >= 1 //Runs only after 1 seconds since this is supposed to be a delay in text thing, not delay in moving on
				 && _promptText ->getText() == "Legend has it that a powerful hero from ages past scattered and hid five magic shards in this area.") //Oh God. This is so bad.
		{
			 //Sets the camera rotation around Jack
			_camera ->setFocus(_mainChar ->getPosition(), _mainChar ->getRotate());
			_camera ->path ->clearPath();
			//_camera ->path ->setActive(true);
			//_camera ->path ->setType(NG_CAMERA_CMR);
			_camera ->path ->addNewPoint(_camera ->getPosition().getVector());
			_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(50.0f, 50.0f, 50.0f)));
			_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(50.0f, 50.0f, -50.0f)));
			_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(-50.0f, 50.0f, -50.0f)));
			_camera ->path ->addNewPoint(_mainChar ->getPosition().add(Vector3f(-50.0f, 50.0f, 50.0f)));

			_cutsceneTimer ->stop();
			_promptText ->setText("It is up to Jack now to gather these pieces to restore order to the land.");
		}
		else if (_promptText ->getPrinting() == false 
			&& _cutsceneTimer ->isRunning() == false
			&& _promptText ->getText() == "It is up to Jack now to gather these pieces to restore order to the land.") //I'm so sorry.
		{
			_cutsceneTimer ->start(); //Starts the timer after the text is done
			//++_cutsceneScene;
		}	
		else if (_promptText ->getPrinting() == false 
			     && _cutsceneTimer ->get(NG_TIMER_SECONDS) >= 2
				 && _promptText ->getText() == "It is up to Jack now to gather these pieces to restore order to the land.") //I'm so sorry.
		{
			_introCutscene = false; //Sets to false since this is the last one
			_cutsceneTimer ->stop();
			_mode = NG_LOADING; //Move ot loading screen again
		}		
	}
}

void Game::updateWeather() //Updates the weather related stuff
{
	if (_currentWeather == NG_RAINY_WEATHER) //If rainy, do stuff
	{
		if (_particleDrawList.size() < NG_MAX_WEATHER_PARTICLES) //Make it rain bro
		{
			spawnParticles(2, NG_WEATHER_RAIN, Vector3f(0.0f, 0.0f, 0.0f));
		}

		if (_skybox ->getColor(0) >= 0.2f)
		{
			_skybox ->setColor(_skybox ->getColor(0) - 0.01, _skybox ->getColor(1) - 0.01, _skybox ->getColor(2) - 0.01, 1.0f); //Darkens colour
			//Darken the light
		}

		if (Model::getGlobalLightIntensity() > 0.5f) //Darken the world
		{
			Model::setGlobalLightIntensity(Model::getGlobalLightIntensity() - 0.01);
		}

		if (_weatherTimer ->get(NG_TIMER_SECONDS) >= 10) //Every 10 seconds, see if thunder needs to be played
		{
			int weatherRand = rand() % 4; //25% chance

			if (weatherRand == 0)
			{
				_thunderSound ->play(); //THUNDER
			}

			_weatherTimer ->reset(); //Resets timer
		}

		if (_forestMusic ->getIsPlaying() && _forestMusic ->getVolume() > 0)
		{
			_forestMusic ->setVolume(_forestMusic ->getVolume() - 0.02); //0.02 because there should be a 0.01 somewhere else

			if (_forestMusic ->getVolume() <= 0.0f)
			{
				_forestMusic ->stop();
			}
		}

		if (_desertMusic ->getIsPlaying())
		{
			_desertMusic ->setVolume(_desertMusic ->getVolume() - 0.02); //0.02 because there should be a 0.01 somewhere else

			if (_desertMusic ->getVolume() <= 0.0f)
			{
				_desertMusic ->stop();
			}
		}

		if (_rainSound ->getIsPlaying() == false)
		{
			_rainSound ->setVolume(0.0f); //We want it to start at0 so we can fade it in
			_rainSound ->play();
		}
		else
		{
			if (_rainSound ->getVolume() < 1)
			{
				_rainSound ->setVolume(_rainSound ->getVolume() + 0.01); //Fades it in
			}
		}
	}
	else //If sunny, do other things
	{
		if (_skybox ->getColor(0) <= 1.0f)
		{
			_skybox ->setColor(_skybox ->getColor(0) + 0.01, _skybox ->getColor(1) + 0.01, _skybox ->getColor(2) + 0.01, 1.0f); //Brightens colour
			//Brighten the light
		}

		if (Model::getGlobalLightIntensity() < 1.0f) //Brighten the world
		{
			Model::setGlobalLightIntensity(Model::getGlobalLightIntensity() + 0.01);
		}

		if (_forestMusic ->getIsPlaying() == false)
		{
			_forestMusic ->play();
		}

		if (_forestMusic ->getIsPlaying() == false)
		{
			_desertMusic ->play();
		}

		if (_rainSound ->getIsPlaying())
		{
			_rainSound ->stop();
		}
	}
}

void Game::drawQuad(unsigned int type, Quad* quad) //Draws the quad. Controls which texture to use
{
	if (type == NG_QUAD)
	{
		if (_mode == NG_GAME)
		{
			quad ->draw(*the2DQuad ->getTexture(), *the3DQuad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_MAIN_MENU)
		{
			//theQuad ->draw(_textureList[27]);
			quad ->draw(*the2DQuad ->getTexture(), *the3DQuad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_LOADING)
		{
			quad ->draw(_textureList[_LOADING_QUAD_INDEX]);
		}
		else if (_mode == NG_GAME_FAILED)
		{
			//theQuad ->draw(_textureList[_FAILED_CUTSCENE_QUAD_INDEX]); //12
			quad ->draw(*the2DQuad ->getTexture(), *the3DQuad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_GAME_CLEARED)
		{
			//theQuad ->draw(_textureList[_SUCCESS_CUTSCENE_QUAD_INDEX]); //None atm
			quad ->draw(*the2DQuad ->getTexture(), *the3DQuad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_INTRO_CUTSCENE)
		{
			quad ->draw(*the2DQuad ->getTexture(), *the3DQuad ->getTexture()); //Gets the texture from the FBO
		}
	}
	else
	{
		if (_mode == NG_GAME)
		{
			quad ->draw(*quad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_MAIN_MENU)
		{
			//theQuad ->draw(_textureList[27]);
			quad ->draw(*quad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_LOADING)
		{
			quad ->draw(_textureList[_LOADING_QUAD_INDEX]);
		}
		else if (_mode == NG_GAME_FAILED)
		{
			//theQuad ->draw(_textureList[_FAILED_CUTSCENE_QUAD_INDEX]); //12
			quad ->draw(*quad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_GAME_CLEARED)
		{
			//theQuad ->draw(_textureList[_SUCCESS_CUTSCENE_QUAD_INDEX]); //None atm
			quad ->draw(*quad ->getTexture()); //Gets the texture from the FBO
		}
		else if (_mode == NG_INTRO_CUTSCENE)
		{
			quad ->draw(*quad ->getTexture()); //Gets the texture from the FBO
		}
	}

	/*if (_mode == NG_GAME)
	{
		theQuad ->draw(theQuad ->getTexture()); //Gets the texture from the FBO
	}
	else if (_mode == NG_MAIN_MENU)
	{
		//theQuad ->draw(_textureList[27]);
		theQuad ->draw(theQuad ->getTexture()); //Gets the texture from the FBO
	}
	else if (_mode == NG_LOADING)
	{
		theQuad ->draw(_textureList[_LOADING_QUAD_INDEX]);
	}
	else if (_mode == NG_GAME_FAILED)
	{
		//theQuad ->draw(_textureList[_FAILED_CUTSCENE_QUAD_INDEX]); //12
		theQuad ->draw(theQuad ->getTexture()); //Gets the texture from the FBO
	}
	else if (_mode == NG_GAME_CLEARED)
	{
		//theQuad ->draw(_textureList[_SUCCESS_CUTSCENE_QUAD_INDEX]); //None atm
		theQuad ->draw(theQuad ->getTexture()); //Gets the texture from the FBO
	}
	else if (_mode == NG_INTRO_CUTSCENE)
	{
		theQuad ->draw(theQuad ->getTexture()); //Gets the texture from the FBO
	}*/
}

Character* Game::getCharacter()
{
	return _mainChar;
}

Camera* Game::getCamera()
{
	return _camera;
}

Timer* Game::getTimer()
{
	return _timer;
}

unsigned int Game::getMode()
{
	return _mode;
}

void Game::displayWorldAxis() //Draws the axis
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); //Red for X
	glVertex3f(0, 0, 0);
	glVertex3f(200, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 1, 0); //Green for Y
	glVertex3f(0, 0, 0);
	glVertex3f(0, 200, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 1); //Blue for Z
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 200);
	glEnd();
	glPopMatrix();
}

void Game::drawText() //Draws all the text
{
	if (_mode != NG_GAME_CLEARED) //Dont draw text if on credits
	{
		if (_showHUD || _mode != NG_GAME) //Draw only if hud is shown
		{
			for (unsigned int i = 0; i < _textList.size(); ++i)
			{
				_textList[i] ->update();
				_textList[i] ->draw();
			}
		}
	}
}

void Game::loadImageMap(char* mapName)
{
	//24 bit bmp images are BGR and there flipped
	unsigned int x, y;

	//load map image in devil and create data pointer to image
	GLuint texture = ilutGLLoadImage(mapName); 
	ILubyte* data = ilGetData();
	ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
	ILint width = ilGetInteger(IL_IMAGE_WIDTH); 

	unsigned int mapData[512][512];

	int pixelCounter = 0;
	int sampleCounter = 0;
	int averageRed = 0;

	std::cout << "Height of image: "<< height << "\n";
	std::cout << "Width of image: " << width << "\n";

	unsigned char* pixel = data; 

    //Store pixel data
	for (y = 0; y < height; ++y)
	{
		for (x = 0; x < width; ++x, pixel += 3)
		{
			unsigned char red = pixel[0], green = pixel[1], blue = pixel[2];
			averageRed += int(blue);
			sampleCounter++;
			pixelCounter++;

			if (y == 0 && x == 0)
			{
				mapData[y][x] = averageRed / sampleCounter;
				averageRed = 0;
				sampleCounter = 0;
			}
		}
	}

	std::cout << "Pixels: " << pixelCounter << "\n";
}
