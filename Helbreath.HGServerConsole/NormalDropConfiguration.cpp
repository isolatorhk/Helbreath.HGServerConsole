#include "NormalDropConfiguration.h"



int NormalDropConfiguration::GetAncientStonePiece()
{
	int itemId = 0;
	switch (dice(1, 6)) {
	case 1:
		itemId = 868; // AncientTable LU
		break;
	case 2:
		itemId = 869;
		break;
	case 3:
		itemId = 870;
		break;
	case 4:
		itemId = 871;
		break;
	}
	return itemId;
}

int NormalDropConfiguration::WeaponDropByGenerationLevel(int generationLevel)
{
	int iGenLevel = generationLevel;
	int itemId = 0;

	switch (iGenLevel) {
	case 1: // Slime, Giant-Ant, Amphis, Rabbit, Cat							
		switch (dice(1, 3)) {
		case 1: {
			itemId = 1;// Dagger
		}
				break;
		case 2: itemId = 8;  break; // ShortSword
		case 3: itemId = 59; break; // LightAxe
		}
		break;

	case 2: // Skeleton, Orc, Orc-Mage, Scorpion, Zombie
		switch (dice(1, 6)) {
		case 1: itemId = 12;  break; // MainGauche
		case 2: itemId = 15;  break; // Gradius
		case 3: itemId = 65;  break; // SexonAxe
		case 4: itemId = 62;  break; // Tomahoc
		case 5: itemId = 23;  break; // Sabre
		case 6: itemId = 31;  break; // Esterk
		}
		break;

	case 3: // Stone-Golem, Clay-Golem
		switch (dice(1, 4)) {
		case 1: itemId = 17;  break; // LongSword
		case 2: itemId = 68;  break; // DoubleAxe
		case 3: itemId = 23;  break; // Sabre
		case 4: itemId = 31;  break; // Esterk
		}
		break;

	case 4: // Hellbound, Rudolph
		switch (dice(1, 5)) {
		case 1: itemId = 23;  break; // Sabre
		case 2: itemId = 25;  break; // Scimitar
		case 3: itemId = 28;  break; // Falchion
		case 4: itemId = 31;  break; // Esterk
		case 5: itemId = 34;  break; // Rapier
		}
		break;

	case 5: // Cyclops, Troll, Beholder, Cannibal-Plant, DireBoar
		switch (dice(1, 3)) {
		case 1: itemId = 31;  break; // Esterk
		case 2: itemId = 34;  break; // Rapier
		case 3: itemId = 71;  break; // WarAxe							
		}
		break;

	case 6: // Orge, WereWolf, Stalker, Dark-Elf, Ice-Golem
		switch (dice(1, 6)) {
		case 1: itemId = 50;  break; // GreatSword
		case 2: itemId = 54;  break; // Flameberge
		case 3: itemId = 46;  break; // Claymore
		case 4: itemId = 31;  break; // Esterk
		case 5: itemId = 34;  break; // Rapier
		}
		break;

	case 7: // Liche, Frost
		switch (dice(1, 4)) {
		case 1: itemId = 50;  break; // GreatSword
		case 2: itemId = 54;  break; // Flameberge
		case 3: itemId = 31;  break; // Esterk
		case 4: itemId = 34;  break; // Rapier
		}
		break;

	case 8: // Demon, Unicorn, Hellclaw, Tigerworm, Gagoyle
		switch (dice(1, 7)) {
		case 1: itemId = 50;  break; // GreatSword
		case 2: itemId = 54;  break; // Flameberge
		case 3: itemId = 560; break; // BattleAxe
		case 4: itemId = 31;  break; // Esterk
		case 5: itemId = 34;  break; // Rapier
		case 6: itemId = 55;  break; // Flameberge+1
		case 7: itemId = 615; break; // GiantSword
		}
		break;

	case 9: // MountainGiant
		switch (dice(1, 6)) {
		case 1: itemId = 23;  break; // Sabre
		case 2: itemId = 25;  break; // Scimitar
		case 3: itemId = 28;  break; // Falchion
		case 4: itemId = 31;  break; // Esterk
		case 5: itemId = 34;  break; // Rapier
		case 6: itemId = 760; break; // Hammer
		}
		break;

	case 10: // Ettin
		switch (dice(1, 5)) {
		case 1: itemId = 46;  break; // Claymore
		case 2: itemId = 31;  break; // Esterk
		case 3: itemId = 34;  break; // Rapier
		case 4: itemId = 760; break; // Hammer
		case 5: itemId = 761; break; // GiantHammer
		}
		break;
	}

	return itemId;
}

int NormalDropConfiguration::ArmorDropByGenerationLevel(int generationLevel)
{
	int iGenLevel = generationLevel;
	int itemId = 0;

	// 1.4% chance Valuable Drop 40% that drop is an Armor/Shield
	switch (iGenLevel) {

	case 1: // Slime, Giant-Ant, Amphis, Rabbit, Cat
	case 2: // Skeleton, Orc, Orc-Mage, Scorpion, Zombie
		switch (dice(1, 2)) {
		case 1: itemId = 79;  break; // WoodShield
		case 2: itemId = 81;  break; // TargeShield
		}
		break;

	case 3: // Stone-Golem, Clay-Golem
		itemId = 81; // TargeShield
		itemId = 79; // TargeShield
		break;

	case 4: // Hellbound, Rudolph
		switch (dice(1, 5)) {
		case 1: itemId = 454; break; // Hauberk(M)
		case 2: itemId = 472; break; // Hauberk(W)
		case 3: itemId = 461; break; // ChainHose(M)
		case 4: itemId = 482; break; // ChainHose(W)
		case 5: itemId = 83;  break; // BlondeShield
		}
		break;

	case 5: // Cyclops, Troll, Beholder, Cannibal-Plant, DireBoar
		switch (dice(1, 9)) {
		case 1: itemId = 455; break; // LeatherArmor(M)
		case 2: itemId = 475; break; // LeatherArmor(W)
		case 3: itemId = 84;  break; // IronShield
		case 4: itemId = 454; break; // Hauberk(M)
		case 5: itemId = 472; break; // Hauberk(W)
		case 6: itemId = 461; break; // ChainHose(M)
		case 7: itemId = 482; break; // ChainHose(W)
		case 8: itemId = 601; break; // Full-Helm(M)
		case 9: itemId = 603; break; // Full-Helm(W)
		}
		break;

	case 6: // Orge, WereWolf, Stalker, Dark-Elf, Ice-Golem
		switch (dice(1, 6)) {
		case 1: switch (dice(1, 2)) {
		case 1: itemId = 456; break; // ChainMail(M)
		case 2: itemId = 476; break; // ChainMail(W)
		}
				break;
		case 2: switch (dice(1, 2)) {
		case 1: itemId = 458; break; // PlateMail(M)
		case 2: itemId = 478; break; // PlateMail(W)
		}
				break;
		case 3: itemId = 85; break; // LagiShield
		case 4: switch (dice(1, 8)) {
		case 1: itemId = 750; break; // Horned-Helm(M)
		case 2: itemId = 751; break; // Wings-Helm(M)
		case 3: itemId = 754; break; // Horned-Helm(W)
		case 4: itemId = 755; break; // Wings-Helm(W)
		case 5: itemId = 752; break; // Wizard-Cap(M) 
		case 6: itemId = 753; break; // Wizard-Hat(M)
		case 7: itemId = 756; break; // Wizard-Cap(W) 
		case 8: itemId = 757; break; // Wizard-Hat(W) 
		}
				break;
		case 5: switch (dice(1, 2)) {
		case 1: itemId = 454; break; // Hauberk(M)
		case 2: itemId = 472; break; // Hauberk(W)
		}
				break;
		case 6: switch (dice(1, 2)) {
		case 1: itemId = 461; break; // ChainHose(M)
		case 2: itemId = 482; break; // ChainHose(W)
		}
				break;
		}
		break;


	case 7: // Liche, Frost
		switch (dice(1, 6)) {
		case 1:
			switch (dice(1, 2)) {
			case 1: itemId = 457; break; // ScaleMail(M)
			case 2: itemId = 477; break; // ScaleMail(W)
			}
			break;
		case 2:
			switch (dice(1, 2)) {
			case 1: itemId = 458; break; // PlateMail(M)
			case 2: itemId = 478; break; // PlateMail(W)
			}
			break;
		case 3: itemId = 86; break; // KnightShield
		case 4: itemId = 87; break; // TowerShield
		case 5:
			switch (dice(1, 2)) {
			case 1: itemId = 600; break; // Helm(M)
			case 2: itemId = 602; break; // Helm(M)
			}
			break;
		case 6:
			switch (dice(1, 2)) {
			case 1: itemId = 601; break; // Full-Helm(M)
			case 2: itemId = 603; break; // Full-Helm(M)
			}
			break;
		}
		break;

	case 8: // Demon, Unicorn, Hellclaw, Tigerworm, Gagoyle
		switch (dice(1, 6)) {
		case 1:
			switch (dice(1, 3)) {
			case 1: itemId = 85; break;    // LagiShield
			case 2: itemId = 86; break;    // KnightShield
			case 3: itemId = 87; break;    // TowerShield
			}
			break;
		case 2:
			switch (dice(1, 3)) {
			case 1: itemId = 402; break;   // Cape
			case 2: if (dice(1, 10) == 3) itemId = 462; break;  // PlateLeggings(M)
			case 3: if (dice(1, 10) == 3) itemId = 483; break;  // PlateLeggings(W)
			}
			break;
		case 3:
			switch (dice(1, 4)) {
			case 1: itemId = 454; break;  // Hauberk(M)
			case 2: itemId = 472; break;  // Hauberk(W)
			case 3: itemId = 461; break;  // ChainHose(M)
			case 4: itemId = 482; break;  // ChainHose(W)
			}
			break;
		case 4:
			switch (dice(1, 4)) {
			case 1: itemId = 750; break;   // Horned-Helm(M)								
			case 2: itemId = 754; break;   // Horned-Helm(W)
			case 3: itemId = 751; break;   // Wings-Helm(M)
			case 4: itemId = 755; break;   // Wings-Helm(W)
			}
			break;
		case 5:
			switch (dice(1, 10)) {
			case 1: itemId = 752; break;   // Wizard-Cap(M)	
			case 2: itemId = 756; break;   // Wizard-Cap(W)
			case 3: itemId = 753; break;   // Wizard-Hat(M)
			case 4: itemId = 757; break;   // Wizard-Hat(W)
			case 5: itemId = 685; break;   // WizardRobe(M)
			case 6: itemId = 686; break;   // WizardRobe(W)
			case 7: itemId = 601; break;   // Full-Helm(M)
			case 8: itemId = 603; break;   // Full-Helm(W)
			case 9: itemId = 600; break;   // Helm(M)
			case 10: itemId = 602; break;  // Helm(W)
			}
			break;
		case 6:
			switch (dice(1, 5)) {
			case 1: itemId = 458; break;  // PlateMail(M)
			case 2: itemId = 478; break;  // PlateMail(W)
			case 3: itemId = 456; break;  // ChainMail(M)
			case 4: itemId = 476; break;  // ChainMail(W)
			case 5: itemId = 402; break;  // Cape
			}
			break;
		}
		break;

	case 9: // Mount-Giant
		switch (dice(1, 6)) {
		case 1:
			switch (dice(1, 3)) {
			case 1: itemId = 85; break;    // LagiShield
			case 2: itemId = 86; break;    // KnightShield
			case 3: itemId = 87; break;    // TowerShield
			}
			break;
		case 2:
			switch (dice(1, 3)) {
			case 1: itemId = 402; break;   // Cape
			case 2: if (dice(1, 10) == 3) itemId = 462; break;  // PlateLeggings(M)
			case 3: if (dice(1, 10) == 3) itemId = 483; break;  // PlateLeggings(W)
			}
			break;
		case 3:
			switch (dice(1, 4)) {
			case 1: itemId = 454; break;  // Hauberk(M)
			case 2: itemId = 472; break;  // Hauberk(W)
			case 3: itemId = 461; break;  // ChainHose(M)
			case 4: itemId = 482; break;  // ChainHose(W)
			}
			break;
		case 4:
			switch (dice(1, 4)) {
			case 1: itemId = 750; break;   // Horned-Helm(M)								
			case 2: itemId = 754; break;   // Horned-Helm(W)
			case 3: itemId = 751; break;   // Wings-Helm(M)
			case 4: itemId = 755; break;   // Wings-Helm(W)
			}
			break;
		case 5:
			switch (dice(1, 10)) {
			case 1: itemId = 752; break;   // Wizard-Cap(M)	
			case 2: itemId = 756; break;   // Wizard-Cap(W)
			case 3: itemId = 753; break;   // Wizard-Hat(M)
			case 4: itemId = 757; break;   // Wizard-Hat(W)
			case 5: itemId = 685; break;   // WizardRobe(M)
			case 6: itemId = 686; break;   // WizardRobe(W)
			case 7: itemId = 601; break;   // Full-Helm(M)
			case 8: itemId = 603; break;   // Full-Helm(W)
			case 9: itemId = 600; break;   // Helm(M)
			case 10: itemId = 602; break;  // Helm(W)
			}
			break;
		case 6:
			switch (dice(1, 5)) {
			case 1: itemId = 458; break;  // PlateMail(M)
			case 2: itemId = 478; break;  // PlateMail(W)
			case 3: itemId = 456; break;  // ChainMail(M)
			case 4: itemId = 476; break;  // ChainMail(W)
			case 5: itemId = 402; break;  // Cape
			}
			break;
		}
		break;
	case 10:  //MasterMage-Orc, Ettin, Lizzard
		switch (dice(1, 6)) {
		case 1:
			switch (dice(1, 3)) {
			case 1: itemId = 85; break;    // LagiShield
			case 2: itemId = 86; break;    // KnightShield
			case 3: itemId = 87; break;    // TowerShield
			}
			break;
		case 2:
			switch (dice(1, 3)) {
			case 1: itemId = 402; break;   // Cape
			case 2: if (dice(1, 10) == 3) itemId = 462; break;  // PlateLeggings(M)
			case 3: if (dice(1, 10) == 3) itemId = 483; break;  // PlateLeggings(W)
			}
			break;
		case 3:
			switch (dice(1, 4)) {
			case 1: itemId = 454; break;  // Hauberk(M)
			case 2: itemId = 472; break;  // Hauberk(W)
			case 3: itemId = 461; break;  // ChainHose(M)
			case 4: itemId = 482; break;  // ChainHose(W)
			}
			break;
		case 4:
			switch (dice(1, 4)) {
			case 1: itemId = 750; break;   // Horned-Helm(M)								
			case 2: itemId = 754; break;   // Horned-Helm(W)
			case 3: itemId = 751; break;   // Wings-Helm(M)
			case 4: itemId = 755; break;   // Wings-Helm(W)
			}
			break;
		case 5:
			switch (dice(1, 10)) {
			case 1: itemId = 752; break;   // Wizard-Cap(M)	
			case 2: itemId = 756; break;   // Wizard-Cap(W)
			case 3: itemId = 753; break;   // Wizard-Hat(M)
			case 4: itemId = 757; break;   // Wizard-Hat(W)
			case 5: itemId = 685; break;   // WizardRobe(M)
			case 6: itemId = 686; break;   // WizardRobe(W)
			case 7: itemId = 601; break;   // Full-Helm(M)
			case 8: itemId = 603; break;   // Full-Helm(W)
			case 9: itemId = 600; break;   // Helm(M)
			case 10: itemId = 602; break;  // Helm(W)
			}
			break;
		case 6:
			switch (dice(1, 5)) {
			case 1: itemId = 458; break;  // PlateMail(M)
			case 2: itemId = 478; break;  // PlateMail(W)
			case 3: itemId = 456; break;  // ChainMail(M)
			case 4: itemId = 476; break;  // ChainMail(W)
			case 5: itemId = 402; break;  // Cape
			}
			break;
		}
		break;
	}

	return itemId;
}

NormalDropConfiguration::NormalDropConfiguration()
{
}


NormalDropConfiguration::~NormalDropConfiguration()
{
}
