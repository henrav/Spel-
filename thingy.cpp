#include <string>

//
// Created by Henrik Ravnborg on 2025-07-21.
//
enum class Aim{
    TARGET = 1,
    AREA = 2,
    VECTOR = 3
};

struct Spell{
    std::string id;
    bool alive = true;
    Aim aim = Aim::TARGET;
    bool piercesSpellImmune = false;

    [[nodiscard]] bool getAlive() const {return alive;}
    [[nodiscard]] enum Aim getAim() const{return aim;}
    [[nodiscard]] bool getPiercesSpellImmune() const {return piercesSpellImmune;}

    virtual void castSpell() = 0;
    virtual void update() = 0;
    ~Spell()= default;
};

struct ProjectileTrait{
    float speed = 0.f;
    float dmg = 0.f;
    float size = 0.f;
protected:
    void launchProjectile(int caster, int target, float speed, float dmg, float size){}
};

struct MoveDebuff : public Spell,
                    public ProjectileTrait{

};