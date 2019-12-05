#pragma once

#include <utility>
#include <vector>
#include <math.h>

constexpr auto PI = 3.14;

using namespace std;

struct circle {
	circle(int x, int y, int r) : x(x), y(y), r(r) {}
	circle() {}
	int x;
	int y;
	int r;
};

class Encoder {
	int W;
	bool checkIntersection(const vector<circle>&, const circle&) const;
	void shiftObject(const vector<circle>&, circle&, bool) const;
	int getMax(const vector<circle>&) const;
public:
	Encoder(int W) : W(W) {}
	int encode(const vector<pair<int, int>>&) const;
};

