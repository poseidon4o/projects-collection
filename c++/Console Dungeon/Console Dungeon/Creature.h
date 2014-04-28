#pragma once
enum DamageType : char { SPELL, PHYSICAL };
class Creature
{
public:
	Creature();
	float doDamage(DamageType);
	void takeDamage(float,DamageType);
	bool levelUp();
	void heal(float);
	void die();

	int getLevel() const;
	int getXp() const;
	float getHp() const;
	float getMaxHp() const;
	float getArmor() const;
	float getResistence() const;
	float getVisualRange() const;
	float getHearingRange() const;
	float getAttackPower() const;
	float getSpellPower() const;
	float getCritChance() const;
	float getCritMultiplier() const;
	float getAttackCooldown() const;

protected:
	
	int level;
	int xp;

	float armor;
	float resistence;
	struct {float visual,hearing;} range;
	struct {float attack,spell;} power;
	struct {float chance,multiplier;} critical;
	float attackCooldown;
	struct {float current,max;} hp;
	struct {bool alive,stunned,incapacitated;} state;
};

