-- CALCULATES ATTRIBUTES FOR PLAYER

maxHealth = getConstitution() * 100
--Convert.ToInt32(100 * Math.Pow(1.17, level - 1));
--if (level < 35)
--            this.baseMaxHealth = Convert.ToInt32((vitality * 10) + Math.Pow(level, 2) * 4);
--        else if (level > 125)
--            this.baseMaxHealth = Convert.ToInt32((vitality * 100) + Math.Pow(level, 2) * 4);
--        else
--            this.baseMaxHealth = Convert.ToInt32((vitality * (level - 25)) + Math.Pow(level, 2) * 4);
minDamage = 25

maxDamage = 28

speed = 1

attack = 20

defense = 30

protection = 50

block = 10

parry = 10

setAttributes(maxHealth, minDamage, maxDamage, speed, attack, defense, protection, block, parry)