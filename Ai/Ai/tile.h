#pragma once
#include <cstdlib>

struct tile
{
	int x, y;			// there is a problem if i dont remember what this is for
	bool checked;		// if this tile has been checked by ai
	bool walkable;		// is wall??????
	float cValue;		// added x and y so if we at 1,5 then xyvalue is 6
	float dValue;		// distants from target x and y so if we at 0,0 and target is at 5,5 dvalue is 5 since its 5 diagnol tiles away


	tile(int x, int y, bool walkable) {
		this->x = x;
		this->y = y;
		this->walkable = walkable;
		checked = false;
	}

	// we want our end value to be zero
	float Tvalue() {return cValue + dValue;}

	void calculateValues(int targetX, int targetY) {
		cValue = (abs(targetX - x) + abs(targetY - y));


		int tempX = 0, tempY = 0, tempValue = 0;
		while (tempX != targetX && tempY != targetY) {
			bool movedX = false , movedY = false;

			if (targetX > tempX) {
				tempX++;
				movedX = true;
			}
			else if (targetX < tempX) {
				tempX--;
				movedX = true;
			}

			if (targetY > tempY) {
				tempY++;
				movedY = true;
			}
			else if (targetY < tempY) {
				tempY--;
				movedY = true;
			}

			if (movedX && movedY)
				tempValue += .5;

			tempValue++;
		}

		dValue = tempValue;
	}

};

