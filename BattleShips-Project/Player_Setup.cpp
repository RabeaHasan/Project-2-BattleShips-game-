#include <iostream>
#include "Player.h"

using namespace std;

Player::Player() {
	comp_player = false;
	is_defeated = false;
	srand(time(NULL));
}

Player::Player(bool is_AI) {
	comp_player = is_AI;
	is_defeated = false;
	ship_list.resize(NUM_SHIPS);
	srand(time(NULL));

	init_game_board();
	if (comp_player)
		init_prob_board();

	populate_ships();
}

void Player::populate_ships() {
	print_boards();
	for (int ship = 0; ship < NUM_SHIPS; ship++) {
		set_ship(ship);
		update_board(ship);

		if (!comp_player) print_boards();
	}
}

void Player::update_board(int ship) {
	Ship new_ship = ship_list[ship];
	bool vert = new_ship.is_vert();
	int row = new_ship.get_row();
	int col = new_ship.get_col();

	string name = get_ship_name(ship);
	char marker = name[0];

	if (vert) {
		for (int i = 0; i < new_ship.get_len(); i++)
			board[row + i][col] = marker;
	}
	else {
		for (int i = 0; i < new_ship.get_len(); i++)
			board[row][col + i] = marker;
	}
}

void Player::set_ship(int cur_ship) {
	string ship_name = get_ship_name(cur_ship);
	if (!comp_player) cout << "Setting the " << ship_name << ":\n";
	bool vert;
	int row, col;
	do {
		vert = ship_vertical();
		row = get_ship_row();
		col = get_ship_col();
		if (!is_valid_placement(cur_ship, vert, row, col) &&
			!comp_player)
			cout << "\nINVALID PLACEMENT\n\n";
	} while (!is_valid_placement(cur_ship, vert, row, col));

	int len, list_index;
	switch (cur_ship) {
	case DESTROYER:
		len = DESTROYER_LEN;
		list_index = DESTROYER;
		break;

	case BATTLESHIP:
		len = BATTLESHIP_LEN;
		list_index = BATTLESHIP;
		break;
	case SUBMARINE:
		len = SUBMARINE_LEN;
		list_index = SUBMARINE;
		break;
	case AIRCRAFT_CAR:
		len = AIRCRAFT_CAR_LEN;
		list_index = AIRCRAFT_CAR;
		break;
	case PATROL_BOAT:
		len = PATROL_BOAT_LEN;
		list_index = PATROL_BOAT;
		break;

	}

	Ship new_ship = Ship(vert, len);
	new_ship.place_ship(row, col);
	ship_list[list_index] = new_ship;
}


void Player::init_game_board() {
	for (int i = 0; i < BOARD_DIM; i++) {
		for (int q = 0; q < BOARD_DIM; q++) {
			board[i][q] = EMPTY_POS;
			guess_board[i][q] = EMPTY_POS;
		}
	}
}


int Player::get_ship(char marker) {
	switch (marker) {
	case 'd':
		return DESTROYER;
	case 'b':
		return BATTLESHIP;
	case 's':
		return SUBMARINE;
	case 'a':
		return AIRCRAFT_CAR;
	case 'p':
		return PATROL_BOAT;
	default:
		return -1;
	}
}


string Player::get_ship_name(int ship) {
	switch (ship) {
	case DESTROYER:
		return "destroyer";
	case BATTLESHIP:
		return "battleship";
	case SUBMARINE:
		return "submarine";
	case AIRCRAFT_CAR:
		return "aircraft carrier";
	case PATROL_BOAT:
		return "patrol boat";
	default:
		return "";
	}
}

int Player::get_ship_row() {
	if (!comp_player) {
		int row;
		do {
			cout << "Row: ";
			cin >> row;
		} while (row < 1 || row >= BOARD_DIM + 1);

		return row - 1;
	}
	else return rand() % BOARD_DIM;
}

int Player::get_ship_col() {
	if (!comp_player) {
		int col;
		do {
			cout << "Col: ";
			cin >> col;
		} while (col < 1 || col >= BOARD_DIM + 1);

		return col - 1;
	}
	else return rand() % BOARD_DIM;
}

char Player::get_marker(int row, int col) {
	return board[row][col];
}

bool Player::ship_vertical() {
	if (!comp_player) {
		string response;
		do {
			cout << "Is this ship  placed vertically?\n";
			cout << "    ('v' for vertical, 'h' for horizontal)\n";
			cin >> response;
		} while (response != "v" && response != "h");

		return response == "v";
	}
	else return (rand() % 100) < 50; // 50/50 chance
}

bool Player::is_valid_placement(int ship, bool vert, int row, int col) {
	if (!in_bounds(row, col)) return false;

	int modifier;
	switch (ship) {
	case DESTROYER:
		modifier = DESTROYER_LEN;
		break;
	case BATTLESHIP:
		modifier = BATTLESHIP_LEN;
		break;
	case SUBMARINE:
		modifier = SUBMARINE_LEN;
		break;
	case AIRCRAFT_CAR:
		modifier = AIRCRAFT_CAR_LEN;
		break;
	case PATROL_BOAT:
		modifier = PATROL_BOAT_LEN;
		break;
	default:
		return false;
	}

	// these are modifier-1 to account for the way ships take up space
	if (vert && !in_bounds(row + modifier - 1, col)) return false;
	else if (!vert && !in_bounds(row, col + modifier - 1)) return false;

	for (int i = 0; i < modifier; i++) {
		if (vert && board[row + i][col] != EMPTY_POS) return false;
		else if (!vert && board[row][col + i] != EMPTY_POS) return false;
	}

	return true;
}

bool Player::in_bounds(int row, int col) {
	return row >= 0 && row < BOARD_DIM&&
		col >= 0 && col < BOARD_DIM;
}

void Player::print_boards() {
	for (int i = 0; i < 100; i++) cout << "\n";
	cout << "\nYour own board:";
	cout << "\n  ";
	for (int i = 0; i < BOARD_DIM; i++)
		cout << i + 1;
	cout << "\n";
	for (int i = 0; i < BOARD_DIM; i++) {
		if (i + 1 < 10) cout << i + 1 << " ";
		else cout << i + 1;
		for (int q = 0; q < BOARD_DIM; q++) {
			cout << board[i][q];
		}
		cout << endl;
	}

	cout << "\nYour guesses:";
	cout << "\n  ";
	for (int i = 0; i < BOARD_DIM; i++)
		cout << i + 1;
	cout << "\n";
	for (int i = 0; i < BOARD_DIM; i++) {
		if (i + 1 < 10) cout << i + 1 << " ";
		else cout << i + 1;
		for (int q = 0; q < BOARD_DIM; q++) {
			cout << guess_board[i][q];
		}
		cout << endl;
	}
}