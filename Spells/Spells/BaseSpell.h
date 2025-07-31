//
// Created by Henrik Ravnborg on 2025-07-23.
//

#ifndef UNTITLED13_BASESPELL_H
#define UNTITLED13_BASESPELL_H


class BaseSpell {
private:
    bool piercesSpellImmunity = false;
    float castRange = 100;
    float cooldown = 10;
    float manaCost = 10;
    float damage = 10;
public:
    bool isPiercesSpellImmunity() const;

    void setPiercesSpellImmunity(bool piercesSpellImmunity);

    float getCastRange() const;

    void setCastRange(float castRange);

    float getCooldown() const;

    void setCooldown(float cooldown);

    float getManaCost() const;

    void setManaCost(float manaCost);

    float getDamage() const;

    void setDamage(float damage);



};


#endif //UNTITLED13_BASESPELL_H
