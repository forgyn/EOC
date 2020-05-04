#include "GameSystem.h"
#include "Map.h"
#include "Object.h"

vector<TextureHandle*> TextureHandler::_textures = vector<TextureHandle*>();

GameSystem::GameSystem(){
	_mouse = new Mouse;
	_event = new Event;
	_font = new Font;
	_font->loadFromFile("Fonts/Arial.ttf");
	select_resolution();
	//_videoMode = new VideoMode(800, 600, BITS_PRER_PIXEL);
	if (_gameState == GAME_STATE::OK) {
		//_texture_handler = new TextureHandler();
		initTextures();
		//Object::setTextureHandler(_texture_handler);


		_mainWindow = new RenderWindow(*_videoMode, "EOC Alpha");
		_mainWindow->setFramerateLimit(MAX_FPS);
		_gameHandle.window = _mainWindow;
		_gameHandle.mouse = _mouse;
		_gameHandle.evnt = _event;
		_gameHandle.font = _font;

		_player = new Player(L"Test",new Warrior(), &_gameHandle);
		_player_party = new PlayerParty(_player, &_gameHandle);
		_player_party->addMember(new Skeleton(10, new Warrior, &_gameHandle));
		_player_party->addMember(new Skeleton(10, new Warrior, &_gameHandle));
		_player_party->addMember(new Skeleton(10, new Warrior, &_gameHandle));
		_player_party->addMember(new Slime(10, &_gameHandle));
		_player_party->scale(1.3);
	}
}

GameSystem::~GameSystem()
{
	delete _mainWindow;
	delete _videoMode;
	delete _mouse;
	delete _event;
	delete _font;
}

bool GameSystem::run(){
	if (_gameState == GAME_STATE::END) return false;
	MapHandle map_handle(L"Test", Vector2u(1, 2), Vector2u(10, 5), 10);
	string map;
	map += "      s   /";
	map += "       a  /";
	map += "     s    /";
	map += "      S   /";
	map += "          /";

	map_handle.setCharMapFromString(map);
	map_handle.addDictionryEntry('a', new Tree(L"Apple Tree", TreeType::Apple, 100, 150, &_gameHandle));
	Object* skeleton = new Skeleton(10, new Warrior(), &_gameHandle);
	skeleton->scale(1.5);
	map_handle.addDictionryEntry('S', skeleton);
	map_handle.addDictionryEntry('s', new Slime(10, &_gameHandle));
	map_handle.setObjectsFromCharMap();
	map_handle.showCharMap();


	//Map test_map(Map_Type::FOREST,1,_player,&_gameHandle
	Map test_map(&map_handle, _player_party, &_gameHandle);

	Clock fps_counter_clock;
	uint16_t fps_counter = 0;
	Text fps_text(to_string(fps_counter), *_gameHandle.font, 100);
	fps_text.setFillColor(Color::Black);
	fps_text.setPosition(0, 0);

	Clock map_mouse_update_limit_clock;
	float map_mouse_update_limit = 30;

	Clock map_tile_update_limit_clock;
	float map_update_limit = 50;

	while (_mainWindow->isOpen()) {
		_mainWindow->clear(Color::White);

		while (_mainWindow->pollEvent(*_event)) {
			switch (_event->type) {
			case Event::Closed:
				_mainWindow->close();
				_gameState = GAME_STATE::END;
				break;
			case Event::Resized:
				test_map.resizeUpdate();
				break;
			}
			test_map.updateRelativeMouse();

			if (test_map.playerInCombat()) {
				test_map.combatControlUpdate();
			}
			else {
				if (map_mouse_update_limit_clock.getElapsedTime().asMilliseconds() >= map_mouse_update_limit) {
					test_map.updateMouse();
					map_mouse_update_limit_clock.restart();
				}
				test_map.updatePlayerControl();
				test_map.updateView();
			}


		}
		
		test_map.combatUpdate();

		if (!test_map.playerInCombat()) {
			test_map.updateObjects();
			if (map_tile_update_limit_clock.getElapsedTime().asMilliseconds() >= map_update_limit) {
				test_map.updateTiles();
				map_tile_update_limit_clock.restart();
			}
		}

		if (fps_counter_clock.getElapsedTime().asSeconds() >= 1) {
			fps_text.setString(to_string(fps_counter));
			fps_counter = 0;
			fps_counter_clock.restart();
		}
		
		test_map.draw();
		_mainWindow->setView(_mainWindow->getDefaultView());
		_mainWindow->draw(fps_text);
		_mainWindow->setView(*test_map.getView());

		_mainWindow->display();
		fps_counter++;	
	}

	if (_gameState == GAME_STATE::END)return false;
	else return true;
}

void GameSystem::initTextures()
{
	
	TextureHandler::addTexture(L"appletree_idle_animation", "Texture/Animation/appletree_idle_animation.png");

	TextureHandler::addTexture(L"slime_default_texture", "Texture/slime_default_texture.png");
	TextureHandler::addTexture(L"slime_idle_animation","Texture/Animation/slime_idle_animation.png");

	TextureHandler::addTexture(L"skeleton_default_texture", "Texture/skeleton_default_texture.png");
	TextureHandler::addTexture(L"skeleton_idle_animation", "Texture/Animation/skeleton_idle_animation.png");

	TextureHandler::addTexture(L"player_breathing_animation", "Texture/Animation/player_breathing_animation.png");
	TextureHandler::addTexture(L"player_blinking_animation", "Texture/Animation/player_blinking_animation.png");
	TextureHandler::addTexture(L"player_default_texture", "Texture/player_default_texture.png");
	TextureHandler::addTexture(L"player_moving_right_animation", "Texture/Animation/player_moving_right_animation.png");
	TextureHandler::addTexture(L"player_moving_left_animation", "Texture/Animation/player_moving_left_animation.png");
	TextureHandler::addTexture(L"player_moving_down_animation", "Texture/Animation/player_moving_down_animation.png");

}

void GameSystem::select_resolution()
{
	//select resolution
	RenderWindow* res_window = new RenderWindow(VideoMode(400, 500), "Select resolution");

	ButtonMenu resolutionMenu(10, 10, 380, 480, 100, res_window);
	resolutionMenu.addButton(L"800 x 600", _font);
	resolutionMenu.addButton(L"1024 x 768", _font);
	resolutionMenu.addButton(L"1280 x 720", _font);
	resolutionMenu.addButton(L"1600 x 900", _font);
	resolutionMenu.addButton(L"1920 x 1080", _font);
	while (res_window->isOpen()) {
		res_window->clear(Color::White);

		while (res_window->pollEvent(*_event)) {
			if (_event->type == Event::Closed) {
				_gameState = GAME_STATE::END;
				res_window->close();
			}
			resolutionMenu.update(_event, _mouse);

		}

		LOOP(resolutionMenu.getSize()) {
			if (resolutionMenu[i]->isPressed(true)) {
				switch (i) {
				case 0:
					_videoMode = new VideoMode(800, 600,BITS_PRER_PIXEL);
					break;
				case 1:
					_videoMode = new VideoMode(1024, 768, BITS_PRER_PIXEL);
					break;
				case 2:
					_videoMode = new VideoMode(1280, 720, BITS_PRER_PIXEL);
					break;
				case 3:
					_videoMode = new VideoMode(1600, 900, BITS_PRER_PIXEL);
					break;
				case 4:
					_videoMode = new VideoMode(1920, 1080, BITS_PRER_PIXEL);
					break;
				}

				res_window->close();
				_gameState = GAME_STATE::OK;
			}

		}
	
		resolutionMenu.draw();
		res_window->display();
	}


	delete res_window;
}

