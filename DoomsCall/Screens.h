#pragma once

#include "DoomsCall.h"

enum HUDType { SELECTED, UNSELECTED, FILLEDHP, EMPTYHP };

class Animater {
    static sf::Sprite player;
    static int playerx;
    static int playery;
    static sf::Sprite buttonsprite;
    static sf::Sprite togglebuttonsprite;
public:
    Animater();
    static sf::Sprite& HandleButtonAnimation(Button& button);
    static sf::Sprite& HandleToggleButtonAnimation(ToggleButton& button);
    static sf::Sprite& HandlePlayerAnimation(Player& player);
};

class Renderer {
    static std::vector<sf::IntRect> hudpart;
    static std::vector<sf::IntRect> itemsrect;
    static sf::Sprite hud;
    static sf::Sprite items;
    static std::vector<sf::IntRect> tilesrect;
    static sf::Sprite tiles;
    static sf::Sprite slidersprite;
    static sf::Sprite background;
    static sf::Text text;
public:
    Renderer();
    static void RenderHUD(sf::RenderWindow& window, Player& player);
    static void RenderTile(sf::RenderWindow& window,TileType type,int i, int j);
    static void RenderMap(sf::RenderWindow& window, Player& player, Map& map);
    static void RenderButton(sf::RenderWindow& window, Button& button);
    static void RenderSlider(sf::RenderWindow& window, Slider& slider);
    static void RenderToggleButton(sf::RenderWindow& window, ToggleButton& button);
    static void RenderBackground(sf::RenderWindow& window);
    static void RenderPlayer(sf::RenderWindow& window,Player& player);
    static void RenderDropsPile(sf::RenderWindow& window, std::vector<ItemDrop>& pile);
};

class Screen {
protected:
    bool isinputthrough;
    bool isupdatethrough;
    bool isrenderthrough;
public:
    virtual void input(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    bool isInputThrough();
    bool isUpdateThrough();
    bool isRenderThrough();
};
class MainScreen :public Screen {
    sf::Sprite title;
    Button start;
    Button option;
    Button exit;
public:
    MainScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};
class SettingsScreen:public Screen {
    Button display;
    Button sound;
    Button controls;
    Button debug;
    Button exit;
public:
    SettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};
class DisplaySettingsScreen:public Screen {
    Button exit;
public:
    DisplaySettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};
class SoundSettingsScreen:public Screen {
    Slider master;
    Slider effect;
    Slider music;
    Slider ambiant;
    Button exit;
public:
    SoundSettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};
class DebugSettingsScreen:public Screen {
    ToggleButton showFPS;
    Button exit;
public:
    DebugSettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};
class ControlsSettingsScreen :public Screen {
    Button exit;
public:
    ControlsSettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};
class MapScreen :public Screen {
    Player player;
    Map map;
    DropsPile drops;
public:
    MapScreen(int row, int col);
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};
class PauseScreen:public Screen {
    Button start;
    Button option;
    Button exit;
public:
    PauseScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
};

class ScreenStack {
    static std::vector<Screen*> screens;
    static int size;
public:
    static int getsize();
    static void push_screen(Screen* screen);
    static void pop_screen();
    static void reset();
    static void input(sf::RenderWindow& window, sf::Event& event,int point);
    static void update(float deltatime, int point);
    static void render(sf::RenderWindow& window, int point);
};
class Game {
    Settings settings;
    Animater animater;
    Renderer renderer;
public:
    void run();
};