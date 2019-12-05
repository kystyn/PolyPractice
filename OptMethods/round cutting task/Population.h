#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include "Encoder.h"

using namespace std;

class Population {
	vector<vector<pair<int, int>>> individes;
	int size;
public:
	Population(vector<pair<int, int>> &, int size);
	void mutation(vector<pair<int, int>> &);
	vector<pair<int, int>> crossbreeding(const vector<pair<int, int>>&, const vector < pair<int, int>>&);
	int extinction(const Encoder &encoder);
	int lifeCircle(const Encoder &encoder);
};
