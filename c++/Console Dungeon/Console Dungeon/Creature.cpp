#include "stdafx.h"
#include "Creature.h"

Creature::Creature() {
	this->state.alive = true;
	this->state.incapacitated = false;
	this->state.stunned = false;
	this->hp.current = this->hp.max = 100;
}

float Creature::doDamage(DamageType t) {
	srand(GetTickCount());
	if( t == SPELL ) {
		return rand() % (int)this->power.spell/2 + this->power.spell/2;
	} else if( t == PHYSICAL ) {
		return rand() % (int)this->power.attack/2 + this->power.attack/2;
	}
	return 0;
}

void Creature::takeDamage(float dmg,DamageType t) {
	srand(GetTickCount());
	if( t == SPELL ) {
		this->hp.current -= ( dmg - rand() % (int)(this->resistence) );
	} else if( t == PHYSICAL ) {
		this->hp.current -= ( dmg - rand() % (int)(this->armor) );
	}
	if( this->hp.current <= 0 )
		this->die();
}

void Creature::die() {
	this->state.alive = false;
}

bool Creature::levelUp() {
	if( this->xp / (this->level * 100) < 1 ) 
		return false;
	this->xp -= this->level * 100;
	this->level++;

	this->levelUp();
	return true;
}

void Creature::heal(float hp) {
	if( hp <= 0 ) return;
	this->hp.current += hp;
	if( this->hp.current > this->hp.max ) this->hp.current = this->hp.max;
}



int Creature::getLevel() const {
	return this->level;
}

int Creature::getXp() const {
	return this->xp;
}

float Creature::getHp() const{
	return this->hp.current;
}

float Creature::getMaxHp() const{
	return this->hp.max;
}

float Creature::getArmor() const{
	return this->armor;
}

float Creature::getResistence() const{
	return this->resistence;
}

float Creature::getVisualRange() const{
	return this->range.visual;
}

float Creature::getHearingRange() const{
	return this->range.hearing;
}

float Creature::getAttackPower() const{
	return this->power.attack;
}

float Creature::getSpellPower() const{
	return this->power.spell;
}

float Creature::getCritChance() const{
	return this->critical.chance;
}

float Creature::getCritMultiplier() const{
	return this->critical.multiplier;
}

float Creature::getAttackCooldown() const{
	return this->attackCooldown;
}
