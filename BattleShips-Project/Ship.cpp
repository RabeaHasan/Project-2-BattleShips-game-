#include <iostream>
#include "Ship.h"

using namespace std;

Ship::Ship() {
	sunk = false;
	vert = false;
	len = 0;
	hp = len;
}

Ship::Ship(bool is_vert, int length) {
	sunk = false;
	vert = is_vert;
	len = length;
	hp = len;
}

void Ship::hit() {
	hp--;
	sunk = (hp == 0);
}
void Ship::place_ship(int new_row, int new_col) {
	row = new_row;
	col = new_col;
}