#include "GameSystem.h"
#include "Map.h"
#include "Object.h"

vector<TextureHandler::TextureHandle*> TextureHandler::_textures = vector<TextureHandler::TextureHandle*>();
vector<TextureHandler::TextureHandle*> TextureHandler::_animation_textures = vector<TextureHandler::TextureHandle*>();
vector<TextureHandler::TextureHandle*> TextureHandler::_hud_textures = vector<TextureHandler::TextureHandle*>();

Mouse* GameHandle::_mouse = new Mouse;
Event* GameHandle::_event = new Event;

Vector2f GameHandle::_resize_ratio = Vector2f(1, 1);
RenderWindow* GameHandle::_window = nullptr;
Vector2u GameHandle::_original_window_size = Vector2u(0, 0);
vector<FontHandler::FontHandle*> FontHandler::_fonts = vector<FontHandler::FontHandle*>();
//default_random_engine* _Random_Generator = new default_random_engine(time(NULL));
uniform_real_distribution<double> Spell::_random_chance = uniform_real_distribution<double>(0, 1);
uniform_int_distribution<unsigned> Map::_randomMapSize = uniform_int_distribution<unsigned>(15, 30);


GameSystem::GameSystem(){
	//_RANDOM_GENERATOR = default_random_engine(time(NULL));
	initFonts();
	select_resolution();
	//_videoMode = new VideoMode(800, 600, BITS_PRER_PIXEL);
	if (_gameState == GAME_STATE::OK) {
		initTextures();
		

		_mainWindow = new RenderWindow(*_videoMode, "EOC Alpha",Style::Close);
		_mainWindow->setFramerateLimit(MAX_FPS);
		GameHandle::init(_mainWindow);

		_player = new Player(L"Forgon",new Warrior());
		_player_party = new PlayerParty(_player);
		_player_party->scale(1.3);
	}
}

GameSystem::~GameSystem()
{
	delete _mainWindow;
	delete _videoMode;
}

void GameSystem::run(){
	
	while (_gameState != GAME_STATE::END) {
		map();
		if (_gameState == GAME_STATE::GAME_OVER)_gameState = GAME_STATE::END;
	}





}

void GameSystem::map(){
	if (_gameState == GAME_STATE::END) return;
	//MapHandle map_handle(L"Test", Vector2u(1, 2), Vector2u(10, 5), 10);
	//string map;
	//map += "      s   /";
	//map += "       a  /";
	//map += "     s    /";
	//map += "      S   /";
	//map += "          /";

	//map_handle.setCharMapFromString(map);
	//map_handle.addDictionryEntry('a', new Tree(TreeType::Apple));

	//HostileParty* enemy_party = new HostileParty(new Skeleton(10, new Warrior()));
	//enemy_party->addMember(new Skeleton(25, new Warrior()));
	//enemy_party->addMember(new Slime(5));
	//enemy_party->addMember(new Skeleton(3, new Warrior()));
	//enemy_party->scale(1.5);
	//map_handle.addDictionryEntry('S', enemy_party);
	//map_handle.addDictionryEntry('s', (new Slime(50))->convertParty());
	//map_handle.setObjectsFromCharMap();


	Map map(Map_Type::FOREST, 1, _player_party);
	//Map test_map(&map_handle, _player_party);

#ifdef DEBUG
	Clock fps_counter_clock;
	uint16_t fps_counter = 0;
	Text fps_text(to_string(fps_counter), *FontHandler::getFont(L"arial"), 100);
	fps_text.setFillColor(Color::Black);
	fps_text.setPosition(0, 0);
#endif // DEBUG

	


	while (_mainWindow->isOpen() && _gameState == GAME_STATE::OK) {
		_mainWindow->clear(Color::White);

		while (GameHandle::pollEvent()) {
			switch (GameHandle::getEventType()) {
			case Event::Closed:
				_mainWindow->close();
				_gameState = GAME_STATE::END;
				return;
				break;
			case Event::Resized:
				map.resizeUpdate();
				break;
			case Event::KeyPressed:
				switch (GameHandle::getKeyPressed()) {
				case Keyboard::Escape:
					_mainWindow->close();
					_gameState = GAME_STATE::END;
					break;
				}

				break;
			}

			map.updateControl();

		}

		map.updateNoControl();

		if (map.gameOver()) {
			_gameState = GAME_STATE::GAME_OVER;
		}



		map.draw();
		//fps counter
#ifdef DEBUG

		if (fps_counter_clock.getElapsedTime().asSeconds() >= 1) {
			fps_text.setString(to_string(fps_counter));
			fps_counter = 0;
			fps_counter_clock.restart();
		}

		_mainWindow->setView(_mainWindow->getDefaultView());
		_mainWindow->draw(fps_text);
		_mainWindow->setView(*map.getView());
		fps_counter++;
#endif // DEBUG

		_mainWindow->display();

	}
}

void GameSystem::initTextures()
{
	TextureHandler::addHudTexture(L"entity_cursor", "Texture/entity_cursor.png");

	TextureHandler::addTexture(L"default_tree_texture", "Texture/default_tree_texture.png");
	TextureHandler::addAnimationTexture(L"default_tree_idle_animation", "Texture/Animation/default_tree_idle_animation.png");

	TextureHandler::addTexture(L"slime_default_texture", "Texture/slime_default_texture.png");
	TextureHandler::addAnimationTexture(L"slime_idle_animation","Texture/Animation/slime_idle_animation.png");

	TextureHandler::addTexture(L"skeleton_default_texture", "Texture/skeleton_default_texture.png");
	TextureHandler::addAnimationTexture(L"skeleton_idle_animation", "Texture/Animation/skeleton_idle_animation.png");

	TextureHandler::addTexture(L"player_default_texture", "Texture/player_default_texture.png");

	TextureHandler::addAnimationTexture(L"player_breathing_animation", "Texture/Animation/player_breathing_animation.png");
	TextureHandler::addAnimationTexture(L"player_blinking_animation", "Texture/Animation/player_blinking_animation.png");
	TextureHandler::addAnimationTexture(L"player_moving_right_animation", "Texture/Animation/player_moving_right_animation.png");
	TextureHandler::addAnimationTexture(L"player_moving_left_animation", "Texture/Animation/player_moving_left_animation.png");
	TextureHandler::addAnimationTexture(L"player_moving_down_animation", "Texture/Animation/player_moving_down_animation.png");
	TextureHandler::addAnimationTexture(L"player_moving_up_animation", "Texture/Animation/player_moving_up_animation.png");

}

void GameSystem::initFonts()
{
	
	FontHandler::addFont(L"arial", "Fonts/Arial.ttf");
	FontHandler::addFont(L"unispace", "Fonts/unispace rg.ttf");
	FontHandler::addFont(L"basis33", "Fonts/basis33.ttf");
}

void GameSystem::select_resolution()
{
	//select resolution
	RenderWindow* res_window = new RenderWindow(VideoMode(400, 500), "Select resolution",Style::Close);
	
	GameHandle::init(res_window);

	ButtonMenu resolutionMenu(10, 10, 380, 480, 100);
	resolutionMenu.addButton(L"800 x 600", FontHandler::getFont(L"arial"));
	resolutionMenu.addButton(L"1024 x 768", FontHandler::getFont(L"arial"));
	resolutionMenu.addButton(L"1280 x 720", FontHandler::getFont(L"arial"));
	resolutionMenu.addButton(L"1600 x 900", FontHandler::getFont(L"arial"));
	resolutionMenu.addButton(L"1920 x 1080", FontHandler::getFont(L"arial"));
	while (res_window->isOpen()) {
		res_window->clear(Color::White);

		while (GameHandle::pollEvent()) {
			if (GameHandle::getEventType() == Event::Closed) {
				_gameState = GAME_STATE::END;
				res_window->close();
			}
			resolutionMenu.update();

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

