#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Player.h"

/* Class: Game
 * gets difficulty 1 <= x <= 3
 * manages players: 1 human, 1 AI
 */

class Game {
public:
	void play();

private:
	bool play_again();

	Player human;
	Player AI;
};

#endif