#include "BossDropConfiguration.h"

int BossDropConfiguration::GetThirdRareDrop(float fProbC)
{
	int itemId = 0;	

	switch (dice(1, 24)) {
	case  1: if (dice(1, (2 * fProbC)) == 2) itemId = 740; break; // BagOfGold-medium
	case  2: if (dice(1, (2 * fProbC)) == 2) itemId = 741; break; // BagOfGold-large
	case  3: if (dice(1, (2 * fProbC)) == 2) itemId = 742; break; // BagOfGold-largest
	case  4: if (dice(1, (2 * fProbC)) == 2) itemId = 868; break; // AcientTablet(LU)
	case  5:
	case  6:
	case  7: if (dice(1, (2 * fProbC)) == 2) itemId = 650; break; // ZemstoneOfSacrifice
	case  8:
	case  9: if (dice(1, (2 * fProbC)) == 2) itemId = 656; break; // StoneOfXelima
	case 10:
	case 11:
	case 12: if (dice(1, (2 * fProbC)) == 2) itemId = 657; break; // StoneOfMerien
	case 13: if (dice(1, (2 * fProbC)) == 2) itemId = 333; break; // PlatinumRing          
	case 14: if (dice(1, (2 * fProbC)) == 2) itemId = 334; break; // LuckyGoldRing         
	case 15: if (dice(1, (2 * fProbC)) == 2) itemId = 335; break; // EmeraldRing           
	case 16: if (dice(1, (2 * fProbC)) == 2) itemId = 336; break; // SapphireRing          
	case 17: if (dice(1, (2 * fProbC)) == 2) itemId = 337; break; // RubyRing              
	case 18: if (dice(1, (2 * fProbC)) == 2) itemId = 290; break; // Flameberge+3(LLF)
	case 19: if (dice(1, (2 * fProbC)) == 2) itemId = 292; break; // GoldenAxe(LLF)
	case 20: if (dice(1, (2 * fProbC)) == 2) itemId = 259; break; // MagicWand(M.Shield)
	case 21: if (dice(1, (2 * fProbC)) == 2) itemId = 300; break; // MagicNecklace(RM10)
	case 22: if (dice(1, (2 * fProbC)) == 2) itemId = 311; break; // MagicNecklace(DF+10)
	case 23: if (dice(1, (2 * fProbC)) == 2) itemId = 305; break; // MagicNecklace(DM+1)
	case 24: if (dice(1, (2 * fProbC)) == 2) itemId = 308; break; // MagicNecklace(MS10)
	}

	return itemId;
}

int BossDropConfiguration::GetAbaddonRareDrop(float fProbA, float fProbB)
{
	int itemId = 0;	

	switch (dice(1, 13)) {
	case 1: if (dice(1, (100 * fProbA)) == 3) itemId = 846; break; // The_Devastator
	case 2: if (dice(1, (100 * fProbA)) == 3) itemId = 847; break; // DarkExecutor            
	case 3: if (dice(1, (100 * fProbA)) == 3) itemId = 860; break; // NecklaceOfXelima
	case 4: if (dice(1, (100 * fProbA)) == 3) itemId = 865; break; // ResurWand(MS.20)
	case 5: if (dice(1, (100 * fProbA)) == 2) itemId = 631; break; // RingoftheAbaddon        	
	case 6: if (dice(1, (100 * fProbA)) == 2) itemId = 866; break; // ResurWand (MS.10)
	case 7: if (dice(1, (100 * fProbA)) == 2) itemId = 862; break; // BerserkWand(MS.20)
	case 8: if (dice(1, (100 * fProbA)) == 2) itemId = 861; break; // BerserkWand(MS.10)
	case 9: if (dice(1, (100 * fProbA)) == 2) itemId = 863; break; // KlonessWand(MS.20)
	case 10: if (dice(1, (100 * fProbA)) == 2) itemId = 864; break; // KlonessWand(MS.10)
	case 11: if (dice(1, (100 * fProbA)) == 2) itemId = 734; break; // RingofArchMage
	case 12: if (dice(1, (100 * fProbA)) == 2) itemId = 853; break; // E.S.W.Manual
	case 13: if (dice(1, (100 * fProbA)) == 2) itemId = 852; break; // CancelManual
	}

	if (itemId == 0)
	{
		switch (dice(1, 20)) {
		case  1: if (dice(1, (4 * fProbB)) == 3) itemId = 762; break; // GBattleHammer           
		case  2: if (dice(1, (4 * fProbB)) == 3) itemId = 490; break; // BloodSword              
		case  3: if (dice(1, (4 * fProbB)) == 3) itemId = 491; break; // BloodAxe                
		case  4: if (dice(1, (4 * fProbB)) == 3) itemId = 492; break; // BloodRapier             
		case  5: if (dice(1, (4 * fProbB)) == 3) itemId = 611; break; // XelimaAxe
		case  6: if (dice(1, (4 * fProbB)) == 3) itemId = 610; break; // XelimaBlade
		case  7: if (dice(1, (4 * fProbB)) == 3) itemId = 612; break; // XelimaRapier
		case 10: if (dice(1, (4 * fProbB)) == 3) itemId = 645; break; // KnecklaceOfEfreet       	
		case 11: if (dice(1, (4 * fProbB)) == 3) itemId = 638; break; // KnecklaceOfFirePro      			
		case 12: if (dice(1, (4 * fProbB)) == 3) itemId = 382; break; // BloodyShockW.Manual
		case 13: if (dice(1, (4 * fProbB)) == 3) itemId = 381; break; // MassFireStrikeManual  
		case 14: if (dice(1, (4 * fProbB)) == 3) itemId = 259; break; // MagicWand(M.Shield)
		case 15: if (dice(1, (4 * fProbB)) == 3) itemId = 291; break; // MagicWand(MS30-LLF)
		case 17: if (dice(1, (4 * fProbB)) == 3) itemId = 850; break; // Kloness Axe
		case 18: if (dice(1, (4 * fProbB)) == 3) itemId = 851; break; // Kloness Esterk
		case 19: if (dice(1, (4 * fProbB)) == 3) itemId = 859; break; // Kloness Neck
		case 20: if (dice(1, (4 * fProbB)) == 3) itemId = 854; break; // I.M.C.Manual
		}
	}

	return itemId;
}
             
int BossDropConfiguration::GetWyvernRareDrop(float fProbA, float fProbB)
{
	int itemId = 0;	

	switch (dice(1, 4)) {
	case 1: if (dice(1, (6000 * fProbA)) == 3) itemId = 845; break; // StormBringer
	case 2: if (dice(1, (5000 * fProbA)) == 3) itemId = 848; break; // LightingBlade
	case 3: if (dice(1, (3000 * fProbA)) == 2) itemId = 614; break; // SwordofIceElemental
	case 4: if (dice(1, (4500 * fProbA)) == 3) itemId = 380; break; // IceStormManual
	}
	if (itemId == 0)
	{
		switch (dice(1, 6)) {
		case  1: if (dice(1, (500 * fProbB)) == 2) itemId = 642; break; // KnecklaceOfIcePro       
		case  2: if (dice(1, (2000 * fProbB)) == 2) itemId = 643; break; // KnecklaceOfIceEle
		case  3: if (dice(1, (1000 * fProbB)) == 3) itemId = 636; break; // RingofGrandMage         	
		case  4: if (dice(1, (1500 * fProbB)) == 3) itemId = 734; break; // RingOfArcmage           
		case  5: if (dice(1, (500 * fProbB)) == 3) itemId = 634; break; // RingofWizard            
		case  6: if (dice(1, (500 * fProbB)) == 2) itemId = 290; break; // Flameberge+3(LLF)
		}
	}

	return itemId;
}

int BossDropConfiguration::GetFireWyvernRareDrop(float fProbA, float fProbB)
{
	int itemId = 0;	

	switch (dice(1, 7)) {
	case  1: if (dice(1, (5000 * fProbA)) == 3) itemId = 847; break; // DarkExecutor            
	case  2: if (dice(1, (3000 * fProbA)) == 2) itemId = 630; break; // RingoftheXelima
	case  3: if (dice(1, (3000 * fProbA)) == 2) itemId = 860; break; // NecklaceOfXelima        
	case  4: if (dice(1, (3000 * fProbA)) == 2) itemId = 735; break; // RingOfDragonpower       
	case  5: if (dice(1, (3000 * fProbA)) == 2) itemId = 20; break; // Excaliber
	case  6: if (dice(1, (3000 * fProbA)) == 3) itemId = 382; break; // BloodyShockW.Manual
	case  7: if (dice(1, (3000 * fProbA)) == 3) itemId = 381; break; // MassFireStrikeManual  			
	}
	if (itemId == 0)
	{
		switch (dice(1, 9)) {
		case  1: if (dice(1, (1000 * fProbB)) == 2) itemId = 645; break; // KnecklaceOfEfreet       	
		case  2: if (dice(1, (500 * fProbB)) == 2) itemId = 638; break; // KnecklaceOfFirePro			
		case  3: if (dice(1, (1000 * fProbB)) == 3) itemId = 636; break; // RingofGrandMage	
		case  4: if (dice(1, (800 * fProbB)) == 3) itemId = 734; break; // RingOfArcmage           
		case  5: if (dice(1, (500 * fProbB)) == 3) itemId = 634; break; // RingofWizard            
		case  6: if (dice(1, (500 * fProbB)) == 2) itemId = 290; break; // Flameberge+3(LLF)
		case  7: if (dice(1, (500 * fProbB)) == 3) itemId = 490; break; // BloodSword              
		case  8: if (dice(1, (500 * fProbB)) == 3) itemId = 491; break; // BloodAxe              
		case  9: if (dice(1, (500 * fProbB)) == 3) itemId = 492; break; // BloodRapier
		}
	}

	return itemId;
}

int BossDropConfiguration::GetTigerwormRareDrop()
{
	int diceResult = 0;
	int itemId = 0;

	diceResult = dice(1, 10000);
	if ((diceResult >= 1) && (diceResult <= 7349)) {
		int result = dice(1, 5);
		if (result == 1) {
			itemId = 311; // MagicNecklace(DF+10)
		}
		else if (result == 2) {
			itemId = 305; // MagicNecklace(DM+1)
		}
		else if (result == 3) {
			itemId = 308; // MagicNecklace(MS10)
		}
		else if (result == 4) {
			itemId = 300; //MagicNecklace(RM10)
		}		
		else {
			itemId = 337; //RubyRing
		}
	}
	else if ((diceResult > 7350) && (diceResult <= 7500))  itemId = 20;  // Excalibur
	else if ((diceResult > 7500) && (diceResult <= 8750))  itemId = 290;  // Flameberge+3(LLF)
	else if ((diceResult > 8750) && (diceResult <= 9000))  itemId = 633;  // RingofDemonpower
	else if ((diceResult > 9000) && (diceResult <= 9100))  itemId = 644;  // neck of air elemental
	else if ((diceResult > 9101) && (diceResult <= 9249))  itemId = 642;  // neck of ice protection
	else if ((diceResult > 9250) && (diceResult <= 9374))  itemId = 645;  // neck of efreet
	else if ((diceResult > 9375) && (diceResult <= 9687))  itemId = 492;  // BloodRapier		
	else if ((diceResult > 9688) && (diceResult <= 9843))  itemId = 490;  // BloodSword		
	else if ((diceResult > 9844) && (diceResult <= 9921))  itemId = 491;  // BloodAxe		
	else if ((diceResult > 9922) && (diceResult <= 9960))  itemId = 291;  // MagicWand(MS30-LLF)	
	else if ((diceResult > 9961) && (diceResult <= 9980))  itemId = 630;  // RingoftheXelima	
	else if ((diceResult > 9981) && (diceResult <= 9990))  itemId = 612;  // XelimaRapier	
	else if ((diceResult > 9991) && (diceResult <= 9996))  itemId = 610;  // XelimaBlade	
	else if ((diceResult > 9996) && (diceResult <= 9998))  itemId = 611;  // XelimaAxe	
	else if ((diceResult > 9999) && (diceResult <= 10000))  itemId = 614;  // SwordofIceElemental	
	return itemId;
}

int BossDropConfiguration::GetHellclawRareDrop()
{
	int diceResult = 0;
	int itemId = 0;

	diceResult = dice(1, 20000);

	if ((diceResult >= 1) && (diceResult <= 7349)) {
		int result = dice(1, 5);
		if (result == 1) {
			itemId = 311; // MagicNecklace(DF+10)
		}
		else if (result == 2) {
			itemId = 305; // MagicNecklace(DM+1)
		}
		else if (result == 3) {
			itemId = 308; // MagicNecklace(MS10)
		}
		else if (result == 4) {
			itemId = 300; //MagicNecklace(RM10)
		}
		else {
			itemId = 337; //RubyRing
		}
	}
	else if ((diceResult > 5000) && (diceResult <= 10000)) itemId = 259;	// MagicWand(M.Shield)
	else if ((diceResult > 10000) && (diceResult <= 13000))  itemId = 337;  // RubyRing
	else if ((diceResult > 13000) && (diceResult <= 14000))  itemId = 1138;  // Scan
	else if ((diceResult > 14000) && (diceResult <= 15000))  itemId = 335;  // EmeraldRing
	else if ((diceResult > 15000) && (diceResult <= 17500))  itemId = 300;  // MagicNecklace(RM10)
	else if ((diceResult > 17500) && (diceResult <= 18750))  itemId = 311;  // MagicNecklace(DF+10)
	else if ((diceResult > 18750) && (diceResult <= 19000))  itemId = 305;  // MagicNecklace(DM+1)
	else if ((diceResult > 19000) && (diceResult <= 19700))  itemId = 634;  // RingofWizard
	else if ((diceResult > 19700) && (diceResult <= 19844))  itemId = 635;  // RingofMage
	else if ((diceResult > 19844) && (diceResult <= 19922))  itemId = 643;  // KnecklaceOfIceEle	
	else if ((diceResult > 19922) && (diceResult <= 19961))  itemId = 640;  // KnecklaceOfSufferent
	else if ((diceResult > 19961) && (diceResult <= 19981))  itemId = 637;  // KnecklaceOfLightPro
	else if ((diceResult > 19981) && (diceResult <= 19991))  itemId = 620;  // MerienShield	
	else if ((diceResult > 19991) && (diceResult <= 19996))  itemId = 644;  // KnecklaceOfAirEle	
	else if ((diceResult > 19996) && (diceResult <= 19999))  itemId = 614;  // SwordofIceElemental	
	else if ((diceResult > 19999) && (diceResult <= 20000))  itemId = 636;	// RingofGrandMage

	return itemId;
}

BossDropConfiguration::BossDropConfiguration()
{
}


BossDropConfiguration::~BossDropConfiguration()
{
}
