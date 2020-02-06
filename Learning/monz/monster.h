#pragma once

class Monster {
    public:
        enum Type {GOBLIN, DRAGON, SPIDER, KNIGHT};

    private:
        Type monsterType;
        char* roar;
        int health; 
    
    public:
        Monster(Monster::Type, char*, int);
        void Roar() const;
};
