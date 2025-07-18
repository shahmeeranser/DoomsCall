#include "DoomsCall.h"

Vector gravity(0, 800.f);

Item::~Item() {
    
}
int Item::getMaxCount() {
    return maxcount;
}
ItemType Item::getType() {
    return type;
}
bool Item::isReducedWhenUsed() {
    return isreduced;
}

Medkit::Medkit() {
    type = MEDKIT;
    maxcount = 16;
    isreduced = true;
}
void Medkit::whenHeld(Player& player) {
}
void Medkit::whenUsed(Player& player) {
    player.heal(150);
}

Bandage::Bandage() {
    type = BANDAGE;
    maxcount = 128;
    isreduced = true;
}
void Bandage::whenHeld(Player& player) {
}
void Bandage::whenUsed(Player& player) {
    player.heal(25);
}

InvSlot::InvSlot() {
    item = nullptr;
    count = 0;
}
bool InvSlot::addItem(Item* item) {
    if (this->item == nullptr) {
        this->item = item;
        count = 1;
        return true;
    }
    else if (this->item->getType() == item->getType() && count < item ->getMaxCount()) {
        count++;
        return true;
    }
    return false;
}
void InvSlot::useItem(Player& player) {
    if (item == nullptr) return;
    item->whenUsed(player);
    if (item->isReducedWhenUsed()) {
        count--;
        if (count < 1) {
            removeItem();
        }
    }
}
void InvSlot::removeItem(){
    delete item;
    item = nullptr;
}
Item* InvSlot::getItem() {
    return item;
}
InvSlot::~InvSlot() {
    delete item;
}

Inv::Inv() {
    selection = 0;
    inv.resize(4);
    for (int i = 0; i < 3; i++) {
        inv[i].resize(9);
    }
}
void Inv::setSelection(int select) {
    selection = select;
}
int Inv::getSelection() {
    return selection;
}
bool Inv::addItem(Item* item) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            if (inv[i][j].addItem(item)) {
                return true;
            }
        }
    }
    return false;
}
InvSlot& Inv::getSlot(int row = 0,int col = -1) {
    if (col == -1) {
        return inv[0][selection];
    }
    return inv[row][col];
}

Obj::Obj() {
    shape = sf::FloatRect(0, 0, 0, 0);
}
void Obj::setPosition(float x, float y) {
    shape.left = x;
    shape.top = y;
}
void Obj::setSize(float x, float y) {
    shape.width = x;
    shape.height = y;
}
sf::Vector2f Obj::getPosition(){
    return sf::Vector2f(shape.left, shape.top);
}
sf::FloatRect Obj::getBounds(){
    return shape;
}

DynamicObj::DynamicObj() {
    velocity = Vector(0, 0);
    acceleration = Vector(0, 0);
    grounded = true;
    hitceiling = false;
}
void DynamicObj::simulateMovement(Map& game, float deltatime) {
    if (grounded || hitceiling) {
        velocity = Vector(velocity.value.x, 0);
    }
    else {
        gravity.apply(velocity.value, deltatime);
    }

    sf::Vector2f center = getPosition();
    sf::FloatRect bounds(center.x - 256 / 2.f, center.y - 256 / 2.f, 256.f, 256.f);

    int left = std::max(static_cast<int>(std::floor(bounds.left / 32)), 0);
    int top = std::max(static_cast<int>(std::floor(bounds.top / 32)), 0);
    int right = std::min(static_cast<int>(std::ceil((bounds.left + bounds.width) / 32)), game.getCol());
    int bottom = std::min(static_cast<int>(std::ceil((bounds.top + bounds.height) / 32)), game.getRow());

    grounded = false;
    hitceiling = false;

    sf::Vector2f movement = velocity.value * deltatime;
    sf::FloatRect futureBounds = getBounds();

    // Horizontal Movement
    if (movement.x != 0.f) {
        futureBounds.left += movement.x;
        for (int i = top; i < bottom; ++i) {
            for (int j = left; j < right; ++j) {
                if (futureBounds.intersects(sf::FloatRect(32 * j, 32 * i, 32, 32)) && game.map[i][j]) {
                    movement.x = 0.f;
                    break;
                }
            }
        }

        sf::Vector2f pos = getPosition();
        setPosition(pos.x + movement.x, pos.y);
    }

    // Vertical Movement
    if (movement.y != 0.f) {
        futureBounds = getBounds(); // Recalculate after horizontal move
        futureBounds.top += movement.y;
        for (int i = top; i < bottom; ++i) {
            for (int j = left; j < right; ++j) {
                if (futureBounds.intersects(sf::FloatRect(32 * j, 32 * i, 32, 32)) && game.map[i][j]) {
                    if (movement.y < 0.f) {
                        hitceiling = true;
                    }
                    else {
                        grounded = true;
                    }
                    movement.y = 0.f;
                    break;
                }
            }
        }

        sf::Vector2f pos = getPosition();
        setPosition(pos.x, pos.y + movement.y);
    }
}

ItemDrop::ItemDrop(ItemType item, sf::Vector2f location){
    setPosition(location.x, location.y);
    setSize(32.f, 32.f);
    this->item = item;
    ispicked = false;
    lifetime = 1200;
}
Item* ItemDrop::getItem() {
    switch (item) {
    case MEDKIT:
        return new Medkit;
        break;
    case BANDAGE:
        return new Bandage;
        break;
    }
}
void ItemDrop::update(Player& player) {
    if (!ispicked && lifetime > 0) {
        lifetime--;
        if(player.getBounds().intersects(getBounds())) {
            ispicked = true;
        }
    }
}
bool ItemDrop::getLifetime() {
    return lifetime;
}
bool ItemDrop::getpicked() {
    return ispicked;
}

void DropsPile::addItem(ItemType item, sf::Vector2f location) {
    items.push_back(ItemDrop(item,location));
}
void DropsPile::update(Player& player, Map& map, float deltatime) {
    for (int i = 0; i < items.size(); i++) {
        items[i].simulateMovement(map, deltatime);
        items[i].update(player);
        if (!items[i].getLifetime()) {
            items.erase(items.begin() - i);
            i--;
            continue;
        }
        if (items[i].getpicked()) {
            if (player.getInv().addItem(items[i].getItem())) {
                items.erase(items.begin() - i);
                i--;
            }
        }
    }
}
std::vector<ItemDrop>& DropsPile::getPile() {
    return items;
}

Player::Player(){
    setSize(32.f, 64.f);
    setPosition(375.f, -300.f);
    inv.addItem(new Medkit());
    maxHP = 200;
    HP = 0;
    speed = 500.f;
    camera = sf::View(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
}
void Player::heal(int amount) {
    HP += amount;
    if (HP > maxHP) {
        HP = maxHP;
    }
}
int Player::getHP() {
    return HP;
}
int Player::getMaxHP() {
    return maxHP;
}
Inv& Player::getInv() {
    return inv;
}
void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))inv.setSelection(0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))inv.setSelection(1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))inv.setSelection(2);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))inv.setSelection(3);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))inv.setSelection(4);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))inv.setSelection(5);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))inv.setSelection(6);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))inv.setSelection(7);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))inv.setSelection(8);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        inv.getSlot().useItem(*this);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.value.x = -speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.value.x = speed;
    else
        velocity.value.x = 0.f; 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded && !hitceiling) {
        velocity.value.y = -speed;  
        grounded = false;
    }
}
void Player::setCameraPosition() {
    camera.setCenter(this->getPosition());
}
void Player::focus(sf::RenderWindow& window) {
    window.setView(camera);
}
sf::View& Player::getCamera() {
    return camera;
}