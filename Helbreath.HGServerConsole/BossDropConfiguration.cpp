#include "BossDropConfiguration.h"



int BossDropConfiguration::GetTigerwormRareDrop()
{
	int diceResult;
	int itemId;

	diceResult = dice(1, 10000);
	if ((diceResult >= 1) && (diceResult <= 7349)) {
		if (dice(1, 2) == 1) {
			itemId = 311; // MagicNecklace(DF+10)
		}
		else {
			itemId = 305; // MagicNecklace(DM+1)
		}
	}
	else if ((diceResult > 7350) && (diceResult <= 7499))  itemId = 614;  // SwordofIceElemental	
	else if ((diceResult > 7500) && (diceResult <= 8749))  itemId = 290;  // Flameberge+3(LLF)
	else if ((diceResult > 8750) && (diceResult <= 9374))  itemId = 633;  // RingofDemonpower
	else if ((diceResult > 9375) && (diceResult <= 9687))  itemId = 492;  // BloodRapier		
	else if ((diceResult > 9688) && (diceResult <= 9843))  itemId = 490;  // BloodSword		
	else if ((diceResult > 9844) && (diceResult <= 9921))  itemId = 491;  // BloodAxe		
	else if ((diceResult > 9922) && (diceResult <= 9960))  itemId = 291;  // MagicWand(MS30-LLF)	
	else if ((diceResult > 9961) && (diceResult <= 9980))  itemId = 630;  // RingoftheXelima	
	else if ((diceResult > 9981) && (diceResult <= 9990))  itemId = 612;  // XelimaRapier	
	else if ((diceResult > 9991) && (diceResult <= 9996))  itemId = 610;  // XelimaBlade	
	else if ((diceResult > 9996) && (diceResult <= 9998))  itemId = 611;  // XelimaAxe	
	else if ((diceResult > 9999) && (diceResult <= 10000)) itemId = 631;  // RingoftheAbaddon

	return itemId;
}

int BossDropConfiguration::GetHellclawRareDrop()
{
	int diceResult;
	int itemId;

	diceResult = dice(1, 20000);

	if ((diceResult >= 1) && (diceResult <= 5000)) itemId = 308;		    // MagicNecklace(MS10)
	else if ((diceResult > 5000) && (diceResult <= 10000)) itemId = 259;	// MagicWand(M.Shield)
	else if ((diceResult > 10000) && (diceResult <= 13000))  itemId = 337;  // RubyRing
	else if ((diceResult > 13000) && (diceResult <= 15000))  itemId = 335;  // EmeraldRing
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
