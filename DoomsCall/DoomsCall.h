#pragma once

#include <chrono>
#include <cmath>
#include "Settings.h"

class Item;
class Inventory;
class Object;
class DynamicObject;
class Player;

enum ItemType { MEDKIT,BANDAGE};
enum EntityType {CHICKEN};

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
    int getCount();
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

class Obj {
    sf::FloatRect shape;
public:
    Obj();
    void setPosition(float x, float y);
    void setSize(float x,float y);
    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
};
class DynamicObj :public Obj {
protected:
    Vector velocity;
    Vector acceleration;
    bool grounded;
    bool hitceiling;
public:
    DynamicObj();
    void simulateMovement(Map& game, float deltatime);
};

class ItemDrop :public DynamicObj {
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
    std::vector<ItemDrop>& getPile();
};
class Player : public DynamicObj {
private:
    int HP;
    int maxHP;
    sf::View camera;
    float speed;
    Inv inv;
public:
    Player();
    int getHP();
    int getMaxHP();
    void heal(int amount);
    Inv& getInv();
    void handleInput();
    void setCameraPosition();
    void focus(sf::RenderWindow& window);
    sf::View& getCamera();
};
class Entity :public DynamicObj {
protected:
    int HP;
    int maxHP;
    EntityType type;
public:
    int getHP();
    int getMaxHP();
    EntityType getType();
    virtual void handleAI() = 0;
};
class Chicken :public Entity {
public:
    Chicken(float x,float y);
    void handleAI();
};
