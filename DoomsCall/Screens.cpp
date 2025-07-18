#include "Screens.h"

int ScreenStack::size = 0;
std::vector<Screen*> ScreenStack::screens;

std::vector<sf::IntRect> Renderer::hudpart;
std::vector<sf::IntRect> Renderer::itemsrect;
sf::Sprite Renderer::hud;
sf::Sprite Renderer::items;
std::vector<sf::IntRect> Renderer::tilesrect;
sf::Sprite Renderer::tiles;
sf::Sprite Renderer::buttonsprite;
sf::Sprite Renderer::slidersprite;
sf::Sprite Renderer::background;

Renderer::Renderer() {
    hud.setTexture(Settings::getTexture(HUD));
    hudpart.push_back(sf::IntRect(32, 0, 40, 40));
    hudpart.push_back(sf::IntRect(72, 0, 40, 40));
    hudpart.push_back(sf::IntRect(0, 0, 32, 16));
    hudpart.push_back(sf::IntRect(0, 16, 32, 16));
    for (int i = 0; i < 2; i++)
    {
        itemsrect.push_back(sf::IntRect(32 * i, 0, 32, 32));
    }
    items.setTexture(Settings::getTexture(ITEMS));

    for (int i = 0; i < 2; i++)
    {
        tilesrect.push_back(sf::IntRect(32 * i, 0, 32, 32));
    }
    tiles.setTexture(Settings::getTexture(TILES));

    buttonsprite.setTexture(Settings::getTexture(BUTTONS));
    slidersprite.setTexture(Settings::getTexture(SLIDER));
    background.setTexture(Settings::getTexture(BACKGROUND));
}
void Renderer::RenderHUD(sf::RenderWindow& window, Player& player) {
    hud.setScale(1, 1);
    hud.setPosition(10, 10);
    for (int i = 0; i < 9; i++) {
        if (i == player.getInv().getSelection()) {
            hud.setTextureRect(hudpart[SELECTED]);
        }
        else {
            hud.setTextureRect(hudpart[UNSELECTED]);
        }
        window.draw(hud);
        if (player.getInv().getSlot(0,i).getItem()) {
            ItemType t = player.getInv().getSlot(0, i).getItem()->getType();
            items.setPosition(hud.getPosition() + sf::Vector2f(4, 4));
            items.setTextureRect(itemsrect[t]);
            window.draw(items);
        }
        hud.move(40, 0);
    }
    hud.setPosition(sf::Vector2f(15, 60));
    hud.setTextureRect(hudpart[EMPTYHP]);
    hud.setScale(6, 1);
    window.draw(hud);
    hud.setTextureRect(hudpart[FILLEDHP]);
    hud.setScale(6 * (static_cast<float>(player.getHP()) / player.getMaxHP()), 1);
    window.draw(hud);
}
void Renderer::RenderButton(sf::RenderWindow& window, Button& button) {
    buttonsprite.setTextureRect(sf::IntRect(32 * button.getType(), 32 * button.isHovered(), 32, 32));
    buttonsprite.setPosition(button.getPosition());
    buttonsprite.setScale(button.getScale());
    window.draw(buttonsprite);
}
void Renderer::RenderMap(sf::RenderWindow& window, Player& player, Map& map) {
    sf::Vector2f center = player.getCamera().getCenter();
    sf::Vector2f size = player.getCamera().getSize();
    sf::FloatRect camera(center.x - size.x / 2, center.y - size.y / 2, size.x, size.y);
    int left = std::max(std::floor(camera.left) / 32, 0.f);
    int top = std::max(std::floor(camera.top) / 32, 0.f);
    int right = std::min(std::ceil((camera.left + camera.width) / 32), static_cast<float>(map.getRow()));
    int bottom = std::min(std::ceil((camera.top + camera.height) / 32), static_cast<float>(map.getCol()));
    for (int i = top; i < bottom; i++) {
        for (int j = left; j < right; j++) {
            if (map.map[j][i]) {
                TileType t = map.map[j][i]->getType();
                tiles.setTextureRect(tilesrect[t]);
                tiles.setPosition(32 * j, 32 * i);
                window.draw(tiles);
            }
        }
    }
}
void Renderer::RenderSlider(sf::RenderWindow& window, Slider& slider) {
    slidersprite.setScale(slider.getScale(0));
    for (int i = 0; i < slider.getSections(); i++) {
        slidersprite.setPosition(slider.getPosition(i));
        slidersprite.setTextureRect(sf::IntRect(16 * (i == slider.getSelected()), 0, 16, 16));
        window.draw(slidersprite);
    }
}
void Renderer::RenderBackground(sf::RenderWindow& window) {
    window.draw(background);
}

MainScreen::MainScreen():
    start(Settings::getlength() / 2-64, Settings::getwidth() / 2-32, 2, PLAY),
    option(Settings::getlength() / 2, Settings::getwidth() / 2-32, 2, OPTIONS),
    exit(Settings::getlength() / 2-32, Settings::getwidth() / 2+32, 2, EXIT) {
    title = sf::Sprite(Settings::getTexture(TITLE));
    title.setPosition(Settings::getlength() / 2 - 190,40);
}
void MainScreen::input(sf::RenderWindow& window, sf::Event& event) {
    start.update(sf::Mouse::getPosition(window));
    option.update(sf::Mouse::getPosition(window));
    exit.update(sf::Mouse::getPosition(window));
    if (start.isClicked(event)) {
        ScreenStack::push_screen(new MapScreen(2048,2048));
    }
    if (option.isClicked(event)) {
        ScreenStack::push_screen(new SettingsScreen);
    }
    if (exit.isClicked(event)) {
        ScreenStack::pop_screen();
    }
}
void MainScreen::update(float deltatime) {
}
void MainScreen::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    window.draw(title);
    Renderer::RenderButton(window, start);
    Renderer::RenderButton(window, option);
    Renderer::RenderButton(window, exit);
}
bool MainScreen::isWorkThrough() {
    return false;
}
bool MainScreen::isUpdateThrough() {
    return false;
}
bool MainScreen::isSeeThrough() {
    return false;
}

SettingsScreen::SettingsScreen() :
    display(Settings::getlength() / 2 - 96, Settings::getwidth() / 2 - 32, 2, DISPLAY),
    sound(Settings::getlength() / 2 - 32, Settings::getwidth() / 2 - 32, 2, SOUND),
    controls(Settings::getlength() / 2 + 32, Settings::getwidth() / 2-32, 2, CONTROLS),
    exit(Settings::getlength() / 2 - 32, Settings::getwidth() / 2 + 32, 2, EXIT) {
}
void SettingsScreen::input(sf::RenderWindow& window, sf::Event& event) {
    display.update(sf::Mouse::getPosition(window));
    sound.update(sf::Mouse::getPosition(window));
    controls.update(sf::Mouse::getPosition(window));
    exit.update(sf::Mouse::getPosition(window));
    if (display.isClicked(event)) {
        ScreenStack::push_screen(new DisplaySettingsScreen);
    }
    if (sound.isClicked(event)) {
        ScreenStack::push_screen(new SoundSettingsScreen);
    }
    if (controls.isClicked(event)) {
        ScreenStack::push_screen(new ControlsSettingsScreen);
    }
    if (exit.isClicked(event)) {
        ScreenStack::pop_screen();
    }
}
void SettingsScreen::update(float deltatime) {
}
void SettingsScreen::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    Renderer::RenderButton(window, display);
    Renderer::RenderButton(window, sound);
    Renderer::RenderButton(window, controls);
    Renderer::RenderButton(window, exit);
}
bool SettingsScreen::isWorkThrough() {
    return false;
}
bool SettingsScreen::isUpdateThrough() {
    return false;
}
bool SettingsScreen::isSeeThrough() {
    return false;
}

DisplaySettingsScreen::DisplaySettingsScreen() :exit(Settings::getlength() / 2 - 32, Settings::getwidth() / 2 + 32, 2, EXIT) {
}
void DisplaySettingsScreen::input(sf::RenderWindow& window, sf::Event& event) {
    exit.update(sf::Mouse::getPosition(window));
    if (exit.isClicked(event)) {
        ScreenStack::pop_screen();
    }
}
void DisplaySettingsScreen::update(float deltatime) {
}
void DisplaySettingsScreen::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    Renderer::RenderButton(window, exit);
}
bool DisplaySettingsScreen::isWorkThrough() {
    return false;
}
bool DisplaySettingsScreen::isUpdateThrough() {
    return false;
}
bool DisplaySettingsScreen::isSeeThrough() {
    return false;
}

SoundSettingsScreen::SoundSettingsScreen() :
    master(Settings::getlength() / 2 - 160, Settings::getwidth() / 2 - 144, 1, 20,19),
    effect(Settings::getlength() / 2 - 160, Settings::getwidth() / 2 - 80, 1, 20,19),
    music(Settings::getlength() / 2 - 160, Settings::getwidth() / 2 - 16, 1, 20,19),
    ambiant(Settings::getlength() / 2 - 160, Settings::getwidth() / 2 + 48, 1,20,19),
    exit(Settings::getlength() / 2 - 32, Settings::getwidth() - 64, 2, EXIT) {
}
void SoundSettingsScreen::input(sf::RenderWindow& window, sf::Event& event) {
    master.update(sf::Mouse::getPosition(window),event);
    effect.update(sf::Mouse::getPosition(window),event);
    music.update(sf::Mouse::getPosition(window),event);
    ambiant.update(sf::Mouse::getPosition(window),event);
    exit.update(sf::Mouse::getPosition(window));
    if (exit.isClicked(event)) {
        ScreenStack::pop_screen();
    }
}
void SoundSettingsScreen::update(float deltatime) {
}
void SoundSettingsScreen::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    Renderer::RenderSlider(window, master);
    Renderer::RenderSlider(window, effect);
    Renderer::RenderSlider(window, music);
    Renderer::RenderSlider(window, ambiant);
    Renderer::RenderButton(window, exit);
}
bool SoundSettingsScreen::isWorkThrough() {
    return false;
}
bool SoundSettingsScreen::isUpdateThrough() {
    return false;
}
bool SoundSettingsScreen::isSeeThrough() {
    return false;
}

ControlsSettingsScreen::ControlsSettingsScreen() :exit(Settings::getlength() / 2 - 32, Settings::getwidth() / 2 + 32, 2, EXIT) {
}
void ControlsSettingsScreen::input(sf::RenderWindow& window, sf::Event& event) {
    exit.update(sf::Mouse::getPosition(window));
    if (exit.isClicked(event)) {
        ScreenStack::pop_screen();
    }
}
void ControlsSettingsScreen::update(float deltatime) {
}
void ControlsSettingsScreen::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    Renderer::RenderButton(window, exit);
}
bool ControlsSettingsScreen::isWorkThrough() {
    return false;
}
bool ControlsSettingsScreen::isUpdateThrough() {
    return false;
}
bool ControlsSettingsScreen::isSeeThrough() {
    return false;
}

MapScreen::MapScreen(int row, int col) :map(row, col) {
    player.setPosition({ 375.f * 0, -64.f});
    drops.addItem(BANDAGE,sf::Vector2f(100,-32));
}
void MapScreen::input(sf::RenderWindow& window, sf::Event& event) {
    static bool uWasPressed = false;
    bool uIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::U);
    if (uIsPressed && !uWasPressed) {
        ScreenStack::push_screen(new PauseScreen());
    }
    uWasPressed = uIsPressed;
    player.handleInput();
}
void MapScreen::update(float deltatime) {
    player.simulateMovement(map, deltatime);
    drops.update(player, map, deltatime);
}
void MapScreen::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    Renderer::RenderBackground(window);
    player.setCameraPosition();
    player.focus(window);
    Renderer::RenderMap(window, player, map);
    window.setView(window.getDefaultView());

    Renderer::RenderHUD(window, player);
}
bool MapScreen::isWorkThrough() {
    return false;
}
bool MapScreen::isUpdateThrough() {
    return false;
}
bool MapScreen::isSeeThrough() {
    return false;
}

PauseScreen::PauseScreen() :start(Settings::getlength() / 2, Settings::getwidth() / 2 , 2, PLAY) {
    shade.setSize(sf::Vector2f(Settings::getlength(),Settings::getwidth()));
}
void PauseScreen::input(sf::RenderWindow& window, sf::Event& event) {
    start.update(sf::Mouse::getPosition(window));
    static bool uWasPressed = false;
    bool uIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::U);
    if (uIsPressed && !uWasPressed) {
        ScreenStack::pop_screen();
    }
    uWasPressed = uIsPressed;
    if (start.isClicked(event)) {
        ScreenStack::pop_screen();
    }
}
void PauseScreen::update(float deltatime) {
    
}
void PauseScreen::render(sf::RenderWindow& window) {
    window.setView(window.getDefaultView());
    start.update(sf::Mouse::getPosition(window));
    Renderer::RenderButton(window, start);
}
bool PauseScreen::isWorkThrough() {
    return false;
}
bool PauseScreen::isUpdateThrough() {
    return false;
}
bool PauseScreen::isSeeThrough() {
    return true;
}

int ScreenStack::getsize() {
    return size;
}
void ScreenStack::push_screen(Screen* screen) {
    Settings::setDelay(Settings::getmaxFPS() / 6);
    screens.push_back(screen);
    size++;
}
void ScreenStack::pop_screen() {
    Settings::setDelay(Settings::getmaxFPS() / 6);
    screens.pop_back();
    size--;
}
void ScreenStack::input(sf::RenderWindow& window, sf::Event& event, int point) {
    if (!size||Settings::getDelay())return;
    if (screens[point]->isWorkThrough()) {
        input(window,event,point - 1);
    }
    screens[point]->input(window,event);
}
void ScreenStack::update(float deltatime,int point) {
    if (!size)return;
    if (screens[point]->isUpdateThrough()) {
        update(deltatime,point - 1);
    }
    screens[point]->update(deltatime);
}
void ScreenStack::render(sf::RenderWindow& window, int point) {
    if (!size)return;
    if (screens[point]->isSeeThrough()) {
        render(window,point - 1);
    }
    screens[point]->render(window);
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "DOOMSCALL");
    window.setFramerateLimit(Settings::getmaxFPS());
    sf::Clock clock;
    window.setIcon(32, 32, settings.geticon());
    ScreenStack::push_screen(new MainScreen);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || !ScreenStack::getsize())
                window.close();
        }
        float delta = clock.restart().asSeconds();
        window.clear(sf::Color::Black);
        ScreenStack::input(window, event, ScreenStack::getsize() - 1);
        ScreenStack::update(delta, ScreenStack::getsize() - 1);
        ScreenStack::render(window, ScreenStack::getsize() - 1);
        window.display();
        Settings::updateDelay();
        //std::cout << 1 / delta << "FPS" << std::endl;
    }
}