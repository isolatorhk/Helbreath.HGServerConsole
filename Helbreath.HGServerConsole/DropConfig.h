#pragma once

class DropConfig {
public:
	static const double DROP_RATE_BONUS_MULTIPLIER;
	static const int GOLD_DROP_CHANCE_MODIFIER = 6000; // 0-10000 (default=6000). 0: never drop gold. instead, drop something else. 10000: always drop gold, drop nothing else.
	static const int NORMAL_ITEM_DROP_CHANCE_MODIFIER = 5000; // 0-10000 (default=7500). 0: never drop normal item (potions), only drop special item (mob-specific).
};
