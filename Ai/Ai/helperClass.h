#pragma once
#include <string>
#include "tile.h"
#include <fstream>
#include <iostream>
using namespace std;

class helperClass {
public:
	tile* testMap[10][10];
	std::string filePath = "Map/test.txt";

	void loadTestMap() {
		ifstream file;
		int count = 0;
		int x = 0, y = 0;

		file.open(filePath);
		if (!file)
			std::cout << "CANNOT OPEN FILE!";

		while (file) {
			char temp = ' ';
			file >> temp;

			switch (temp) {
			case '1':
				testMap[x][y] = (new tile(x, y, false));
				break;
			case '0':
				testMap[x][y] = (new tile(x, y, true));
				break;
			default:
				cout << "ERROR on " << count << endl;
			}

			x++;
			count++;


			if (y > 9) {
				file.close();
				std::cout << "FILE LOADED" << endl;
				break;
			}
			if(x > 9){
				x = 0;
				y++;
			}
		}
	}
};