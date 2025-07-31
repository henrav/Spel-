//
// Created by Henrik Ravnborg on 2025-07-23.
//

#include "BaseSpell.h"

bool BaseSpell::isPiercesSpellImmunity() const {
    return piercesSpellImmunity;
}

void BaseSpell::setPiercesSpellImmunity(bool piercesSpellImmunity) {
    BaseSpell::piercesSpellImmunity = piercesSpellImmunity;
}

float BaseSpell::getCastRange() const {
    return castRange;
}

void BaseSpell::setCastRange(float castRange) {
    BaseSpell::castRange = castRange;
}

float BaseSpell::getCooldown() const {
    return cooldown;
}

void BaseSpell::setCooldown(float cooldown) {
    BaseSpell::cooldown = cooldown;
}

float BaseSpell::getManaCost() const {
    return manaCost;
}

void BaseSpell::setManaCost(float manaCost) {
    BaseSpell::manaCost = manaCost;
}

float BaseSpell::getDamage() const {
    return damage;
}

void BaseSpell::setDamage(float damage) {
    BaseSpell::damage = damage;
}
