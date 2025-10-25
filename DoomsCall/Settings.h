#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

#define TILE_SIZE 16

enum TextureType {EMPTY,TITLE,BUTTONS,SLIDER,TOGGLEBUTTONS, HUD, TILES, ITEMS ,PLAYER,BACKGROUND};
enum ButtonType {PLAY,OPTIONS,EXIT,DISPLAY,SOUND,CONTROLS,DEBUG};

class Settings {
    sf::Image icon;
    static int inputdelay;
    static int length;
    static int width;
    static int maxFPS;
    static std::vector<sf::Texture> textures;
    static sf::Font font;
public:
    Settings();
    static int getlength();
    static int getwidth();
    static int getmaxFPS();
    static int getDelay();
    static sf::Font& getFont();
    static void setDelay(int val);
    static void updateDelay();
    const sf::Uint8* geticon();
    static sf::Texture& getTexture(TextureType type);
};
class Button {
private:
    sf::FloatRect location;
    ButtonType type;
    bool ishovered;
public:
    Button(float x, float y, float scale, ButtonType type);
    void update(const sf::Vector2i& mousePos);
    bool isClicked(const sf::Event& event);
    ButtonType getType();
    bool isHovered();
    sf::Vector2f getPosition();
    sf::Vector2f getScale();
};
class Slider {
    std::vector<sf::FloatRect> locations;
    std::vector<bool> ishovered;
    bool isdragging;
    int sections;
    int selected;
public:
    Slider(float x,float y,float scale,int sections,int selected);
    void update(const sf::Vector2i& mousePos, sf::Event& event);
    int getSections();
    int getSelected();
    sf::Vector2f getPosition(int index);
    sf::Vector2f getScale(int index);
};
class ToggleButton {
    sf::FloatRect location;
    bool state;
    bool ishovered;
public:
    ToggleButton(float x, float y, float scale, bool state);
    void update(const sf::Vector2i& mousePos);
    void Clicked(const sf::Event& event);
    bool isHovered();
    sf::Vector2f getPosition();
    sf::Vector2f getScale();
    bool isON();
};

struct Vector {
    sf::Vector2f value;
    Vector();
    Vector(float x, float y);
    void apply(sf::Vector2f& position, float delta);
};

enum TileType { GRASS, SPIKE };
class Tile {
public:
    virtual TileType getType() = 0;
};
class Grass :public Tile {
    TileType getType();
};
class Spike :public Tile {
    TileType getType();
};
class Map {
private:
    int row;
    int col;
public:
    std::vector<std::vector<Tile*>> map;
    Map(int row, int col);
    int getRow();
    int getCol();
};