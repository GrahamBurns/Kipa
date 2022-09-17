#pragma once
#include <vector>
#include "helperClass.h"

class Ai {
public:

	int beginX = 0, beginY = 0;	// should be assigned by a different class
	int destX = 9, destY = 9;	// should be assigned by a different class
	helperClass map;
	vector<tile*> nearbyTiles;
	vector<tile*> bestTiles;

	Ai() {
		map.loadTestMap();
	}

	vector<tile*> bestTilesVector() {
		return bestTiles;
	}

	void nearestTile(int startX, int startY) {			//preload with all tiles 
		//find closest avaivable tile
		nearbyTiles.clear();

		int tempX = map.testMap[startX][startY]->x;
		int tempY = map.testMap[startX][startY]->y;

		for (int y = -1; y < 2; y++) {
			for (int x = -1; x < 2; x++) {
				if (tempX + x > -1 && tempX + x < 10 && tempY + y > -1 && tempY + y < 10) {

					int tempX = map.testMap[startX][startY]->x + x;
					int tempY = map.testMap[startX][startY]->y + y;

					if (map.testMap[tempX][tempY]->walkable && !map.testMap[tempX][tempY]->failedPath) {
						nearbyTiles.push_back(map.testMap[tempX][tempY]);
					}
				}
			}
		}

	}

	// CURRENT BUG CANNOT SEE BLOCK TO LEFT <

	void findPath() {
		bool pathFound = false;		// set pathFound to false
		bool pathError = false;		// path that doesnt reach its obj
		bool pathFailure = false;

		while (!pathFound) {		// need to plan for a dest with no path

			if (bestTiles.empty()) {
				nearestTile(beginX, beginY);
			}
			else {
				nearestTile(bestTiles[bestTiles.size() - 1]->x, bestTiles[bestTiles.size() - 1]->y);
			}

			tile* best = nearbyTiles[0];
			best->calculateValues(destX, destY);
			best->checked = true;

			pathFailure = true;
			for (int i = 0; i < nearbyTiles.size(); i++) {
				nearbyTiles[i]->calculateValues(destX, destY);

				if (best->Tvalue() > nearbyTiles[i]->Tvalue() && nearbyTiles[i]->walkable && !nearbyTiles[i]->failedPath && (!nearbyTiles[i]->checked || pathFailure)) {
					best = nearbyTiles[i];
				}
			}
			if (bestTiles.size() > 1 && best->x == bestTiles[bestTiles.size() - 1]->x && best->y == bestTiles[bestTiles.size() - 1]->y) {
				pathFailure = true;
			}
			else {
				pathFailure = false;
			}

			if (!pathFailure) {
				bestTiles.push_back(best);
				best->checked = true;
			}

			//checks
			if (!bestTiles.empty()) {
				if (destX == bestTiles[bestTiles.size() - 1]->x && destY == bestTiles[bestTiles.size() - 1]->y) {
					pathFound = true;
				}
				else if (pathFailure) {
					bestTiles[bestTiles.size() - 1]->failedPath = true;
					bestTiles.pop_back();
				}
			}
			else if (pathError) {
				pathFound = true;
				std::cout << "No Path Coould Be Found!" << endl;
			}
		}
	}