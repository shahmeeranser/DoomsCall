#include "Settings.h"

int Settings::length = 100;
int Settings::width = 100;
int Settings::maxFPS = 60;
int Settings::inputdelay = 0;
std::vector<sf::Texture> Settings::textures;
sf::Font Settings::font;

Settings::Settings() {
     if (!icon.loadFromFile("resources/no_texture.png")) {
          std::cerr << "FAIL";
     }
    length = 0;
    width = 0;
    maxFPS = 120;
    std::ifstream fin("resources/option.txt");
    if (!fin) {
        std::cerr << "Fail";
        return;
    }
    fin >> length;
    fin >> width;
    fin >> maxFPS;
    fin.close();
    //loading all the assets
    {
        sf::Texture image;
        if (!image.loadFromFile("resources/no_texture.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/title.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/icons/Buttons.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/icons/sliders.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/icons/toggle.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/icons/HUD.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/Tiles.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/Items.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/entities/Player.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!image.loadFromFile("resources/background.png")) {
            std::cerr << "FAIL";
        }
        textures.push_back(image);
        if (!font.loadFromFile("resources/fonts/yoster.ttf")) {
            std::cerr << "FAIL";
        }
    }
}
int Settings::getlength() {
    return length;
}
int Settings::getwidth() {
    return width;
}
int Settings::getmaxFPS() {
    return maxFPS;
}
int Settings::getDelay() {
    return inputdelay;
}
sf::Font& Settings::getFont() {
    return font;
}
void Settings::setDelay(int val) {
    inputdelay = val;
}
void Settings::updateDelay() {
    if (inputdelay > 0)inputdelay--;
}
const sf::Uint8* Settings::geticon() {
    return icon.getPixelsPtr();
}
sf::Texture& Settings::getTexture(TextureType type) {
    return textures[static_cast<int>(type)];
}

Button::Button(float x, float y, float scale, ButtonType type) :
    location(x ,y ,32 * scale ,32 * scale ){
    this->type = type;
    ishovered = false;
}
void Button::update(const sf::Vector2i& mousePos) {
    ishovered = location.contains(sf::Vector2f(mousePos.x,mousePos.y));
}
bool Button::isClicked(const sf::Event& event){
    return ishovered && event.type == sf::Event::MouseButtonPressed
        && event.mouseButton.button == sf::Mouse::Left;
}
ButtonType Button::getType() {
    return type;
}
bool Button::isHovered() {
    return ishovered;
}
sf::Vector2f Button::getPosition() {
    return sf::Vector2f(location.left, location.top);
}
sf::Vector2f Button::getScale() {
    return sf::Vector2f(location.width/32.f, location.height/32.f);
}

Slider::Slider(float x, float y, float scale, int section,int selection)
{
    sections = section;
    selected = selection;
    ishovered.resize(section);
    for (int i = 0; i < section; i++) {
        ishovered[i] = false;
    }
    locations.resize(section);
    for (int i = 0; i < section; i++) {
        locations[i] = sf::FloatRect(x + (scale * 16 * i), y,16 * scale,16 * scale);
    }
    isdragging = false;
}
void Slider::update(const sf::Vector2i& mousePos,sf::Event& event) {
    isdragging = false;
    for (int i = 0; i < sections; i++) {
        if (!isdragging) {
            isdragging = locations[i].contains(sf::Vector2f(mousePos.x, mousePos.y));
        }
    }
    if (isdragging && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        int index = (mousePos.x - locations[0].left) / locations[0].width;
        if (index >= 0 && index < sections) {
            selected = index;
        }
    }
}
int Slider::getSections() {
    return sections;
}
int Slider::getSelected() {
    return selected;
}
sf::Vector2f Slider::getPosition(int index) {
    return sf::Vector2f(locations[index].left, locations[index].top);
}
sf::Vector2f Slider::getScale(int index) {
    return sf::Vector2f(locations[index].width / 16.f, locations[index].height / 16.f);
}

ToggleButton::ToggleButton(float x, float y, float scale, bool state):
    location(x ,y ,24 * scale ,16 * scale ){
    this->state = state;
    ishovered = false;
}

void ToggleButton::Clicked(const sf::Event& event) {
    Settings::setDelay(Settings::getmaxFPS() / 6);
    if (ishovered && event.type == sf::Event::MouseButtonPressed
        && event.mouseButton.button == sf::Mouse::Left)state = !state;
}
void ToggleButton::update(const sf::Vector2i& mousePos) {
    ishovered = location.contains(sf::Vector2f(mousePos.x, mousePos.y));
}
bool ToggleButton::isHovered() {
    return ishovered;
}
sf::Vector2f ToggleButton::getPosition() {
    return sf::Vector2f(location.left, location.top);
}
sf::Vector2f ToggleButton::getScale() {
    return sf::Vector2f(location.width / 32.f, location.height / 32.f);
}
bool ToggleButton::isON() {
    return state;
}

Vector::Vector():value(0, 0) {}
Vector::Vector(float x, float y) : value(x, y) {}
void Vector::apply(sf::Vector2f& position, float delta) {
    position += value * delta;
}

TileType Grass::getType() {
    return GRASS;
}

TileType Spike::getType() {
    return SPIKE;
}

Map::Map(int row, int col) {
    this->row = row;
    this->col = col;
    map.resize(row);
    for (int i = 0; i < row; i++) {
        map[i].resize(col);
        for (int j = 0; j < col; j++) {
            if (i + j > col && j < i)
                map[i][j] = new Grass;
            else
                map[i][j] = nullptr;
        }
    }
}
int Map::getRow() {
    return row;
}
int Map::getCol() {
    return col;
}