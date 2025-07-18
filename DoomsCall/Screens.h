#pragma once

#include "DoomsCall.h"

enum HUDType { SELECTED, UNSELECTED, FILLEDHP, EMPTYHP };

class Renderer {
    static std::vector<sf::IntRect> hudpart;
    static std::vector<sf::IntRect> itemsrect;
    static sf::Sprite hud;
    static sf::Sprite items;
    static std::vector<sf::IntRect> tilesrect;
    static sf::Sprite tiles;
    static sf::Sprite buttonsprite;
    static sf::Sprite slidersprite;
    static sf::Sprite background;
public:
    Renderer();
    static void RenderHUD(sf::RenderWindow& window, Player& player);
    static void RenderMap(sf::RenderWindow& window, Player& player, Map& map);
    static void RenderButton(sf::RenderWindow& window, Button& button);
    static void RenderSlider(sf::RenderWindow& window, Slider& slider);
    static void RenderBackground(sf::RenderWindow& window);
};

class Screen {
public:
    virtual void input(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isWorkThrough() = 0;
    virtual bool isUpdateThrough() = 0;
    virtual bool isSeeThrough() = 0;
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
    bool isWorkThrough();
    bool isUpdateThrough();
    bool isSeeThrough();
};
class SettingsScreen:public Screen {
    Button display;
    Button sound;
    Button controls;
    Button exit;
public:
    SettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
    bool isWorkThrough();
    bool isUpdateThrough();
    bool isSeeThrough();
};
class DisplaySettingsScreen:public Screen {
    Button exit;
public:
    DisplaySettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
    bool isWorkThrough();
    bool isUpdateThrough();
    bool isSeeThrough();
};
class SoundSettingsScreen :public Screen {
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
    bool isWorkThrough();
    bool isUpdateThrough();
    bool isSeeThrough();
};
class ControlsSettingsScreen :public Screen {
    Button exit;
public:
    ControlsSettingsScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
    bool isWorkThrough();
    bool isUpdateThrough();
    bool isSeeThrough();
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
    bool isWorkThrough();
    bool isUpdateThrough();
    bool isSeeThrough();
};
class PauseScreen:public Screen {
    Button start;
    sf::RectangleShape shade;
public:
    PauseScreen();
    void input(sf::RenderWindow& window, sf::Event& event);
    void update(float deltatime);
    void render(sf::RenderWindow& window);
    bool isWorkThrough();
    bool isUpdateThrough();
    bool isSeeThrough();
};

class ScreenStack {
    static std::vector<Screen*> screens;
    static int size;
public:
    static int getsize();
    static void push_screen(Screen* screen);
    static void pop_screen();
    static void input(sf::RenderWindow& window, sf::Event& event,int point);
    static void update(float deltatime, int point);
    static void render(sf::RenderWindow& window, int point);
};
class Game {
    Settings settings;
    Renderer renderer;
public:
    void run();
};