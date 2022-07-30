#include <iostream>
#include "Game.h"
//#include "Player.h"

using namespace std;

void Game::play() {
	bool playing = true;

	while (playing) {
		human = Player(false);
		AI = Player(true);
		while (!human.defeated() && !AI.defeated()) {
			if (!human.defeated())
				human.take_turn(AI);

			if (!AI.defeated())
				AI.take_turn(human);

		}

		if (human.defeated()) {
			cout << "You have lost...\n";
		}
		else if (AI.defeated()) {
			cout << "You have won!...\n";
		}

		playing = play_again();
	}
}

bool Game::play_again() {
	string play;
	do {
		cout << "Play again? (y/n) ";
		cin >> play;
	} while (play != "y" && play != "n" && play != "Y" && play != "N");

	return play == "y" || play == "Y";
}