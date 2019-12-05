#include <iostream>
#include <time.h>
#include "Population.h"
#include "Encoder.h"

int main() {
	srand(time(0));

	vector<pair<int, int>> objects;
	objects.push_back(pair<int, int>(1, 115));
	objects.push_back(pair<int, int>(2, 60));
	objects.push_back(pair<int, int>(3, 30));
	objects.push_back(pair<int, int>(4, 45));
	objects.push_back(pair<int, int>(5, 80));
	objects.push_back(pair<int, int>(6, 35));
	objects.push_back(pair<int, int>(7, 74));
	objects.push_back(pair<int, int>(8, 88));
	Population pop(objects, 6);
	Encoder encoder(300);
	for (int i = 0; i < 15; i++) {
		cout << pop.lifeCircle(encoder) << endl;
	}
	return 0;
}