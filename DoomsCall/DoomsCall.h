#pragma once

#include <chrono>

#include "Settings.h"

class Item;
class Inventory;
class Object;
class DynamicObject;
class Player;

enum ItemType { MEDKIT,BANDAGE};

class Item {
protected:
    int maxcount;
    ItemType type;
    bool isreduced;
public:
    virtual void whenHeld(Player& player) = 0;
    virtual void whenUsed(Player& player) = 0;
    ItemType getType();
    int getMaxCount();
    bool isReducedWhenUsed();
    ~Item();
};
class Medkit :public Item {
public:
    Medkit();
    void whenHeld(Player& player);
    void whenUsed(Player& player);
};
class Bandage :public Item {
public:
    Bandage();
    void whenHeld(Player& player);
    void whenUsed(Player& player);
};

class InvSlot {
    Item* item;
    int count;
public:
    InvSlot();
    bool addItem(Item* item);
    void useItem(Player& player);
    void removeItem();
    Item* getItem();
    ~InvSlot();
};
class Inv {
    int selection;
    std::vector<std::vector<InvSlot>> inv;
public:
    Inv();
    void setSelection(int select);
    int getSelection();
    bool addItem(Item* item);
    InvSlot& getSlot(int row, int col);
};

class Object {
protected:
    sf::Sprite shape;
public:
    Object(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window) const;
    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
};
class DynamicObject:public Object {
protected:
    Vector velocity;
    Vector acceleration;
    bool grounded;
    bool hitceiling;
public:
    DynamicObject(const sf::Vector2f& position);
    void simulateMovement(Map& game, float deltatime);
};
class ItemDrop :public DynamicObject {
    ItemType item;
    bool ispicked;
    int lifetime;
public:
    ItemDrop(ItemType item, sf::Vector2f location);
    Item* getItem();
    void update(Player& player);
    bool getLifetime();
    bool getpicked();
};
class DropsPile {
    std::vector<ItemDrop> items;
public:
    void addItem(ItemType item,sf::Vector2f location);
    void update(Player& player, Map& map,float deltatime);
    void draw(sf::RenderWindow& window);
};
class Player : public DynamicObject {
private:
    sf::View camera;
    int maxHP;
    int HP;
    float speed;
    Inv inv;
public:
    Player();
    void heal(int amount);
    int getHP();
    int getMaxHP();
    Inv& getInv();
    void handleInput();
    void setCameraPosition();
    void focus(sf::RenderWindow& window);
    sf::View& getCamera();
};