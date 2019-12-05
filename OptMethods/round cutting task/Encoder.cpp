#include "Encoder.h"

bool Encoder::checkIntersection
(const const vector<circle>& objs, const circle& obj) const
{
	if (obj.y + obj.r > W || obj.y - obj.r < 0 || obj.x - obj.r < 0) return false;

	for (auto it = objs.begin(); it != objs.end(); it++) {
		if (((it->x - obj.x) * (it->x - obj.x)
			+ (it->y - obj.y) * (it->y - obj.y))
			< ((it->r - obj.r) * (it->r - obj.r)) + 10) return false;
	}
	return true;
}

void Encoder::shiftObject
(const vector<circle>& puttedObjs, circle& currentObj, bool down) const
{
	double r, alpha, add;
	int count = 0;


	r = currentObj.r + puttedObjs[puttedObjs.size() - 1].r;

	alpha = PI / 2;
	add = PI / 16;
	while (checkIntersection(puttedObjs, currentObj) == false) {
		if (down) {
			alpha -= add;
			currentObj.x = r * cos(alpha);
			currentObj.y = r * sin(alpha);
		}
		else {
			alpha += add;
			currentObj.x = r * cos(alpha);
			currentObj.y = r * sin(alpha);
		}
		count++;
		if (count > 15) break;
	}
	count = 0;
	while (checkIntersection(puttedObjs, currentObj) == true) {
		if (down) {
			alpha += add;
			currentObj.x = r * cos(alpha);
			currentObj.y = r * sin(alpha);
		}
		else {
			alpha -= add;
			currentObj.x = r * cos(alpha);
			currentObj.y = r * sin(alpha);
		}
		count++;
		if (count > 15) break;
	}
	count = 0;
	while (checkIntersection(puttedObjs, currentObj) == false) {
		if (down) {
			alpha -= add;
			currentObj.x = r * cos(alpha) + 1;
			currentObj.y = r * sin(alpha) + 1;
		}
		else {
			alpha += add;
			currentObj.x = r * cos(alpha) + 1;
			currentObj.y = r * sin(alpha) - 1;
		}
		count++;
		if (count > 15) break;
	}
}

int Encoder::getMax(const vector<circle>& objs) const
{
	int max = 0;
	for (auto it = objs.begin(); it != objs.end(); it++) {
		if (it->x + it->r > max) max = it->x + it->r;
	}
	return max;
}

int Encoder::encode(const vector<pair<int, int>>& objs) const
{
	circle prevObj, currentObj;

	vector<circle> puttedObjs;
	puttedObjs.reserve(objs.size());
	puttedObjs.push_back(circle(objs[0].second, objs[0].second, objs[0].second));
	bool down;

	if (objs[0].second * 2 > W) down = false;
	else down = true;

	double alpha, r;
	bool intersectBottom, intersectTop;
	for (int i = 1; i < objs.size(); i++) {
		prevObj = *(puttedObjs.end() - 1);
		currentObj.r = objs[i].second;
		currentObj.x = prevObj.x;
		if (down == true) {
			currentObj.y = prevObj.y + prevObj.r + currentObj.r;
		}
		else {
			currentObj.y = prevObj.y - prevObj.r - currentObj.r;
		}

		if (currentObj.y + currentObj.r > W) intersectBottom = true;
		else intersectBottom = false;
		if (currentObj.y - currentObj.r < 0) intersectTop = true;
		else intersectTop = false;

		shiftObject(puttedObjs, currentObj, down);
		puttedObjs.push_back(currentObj);

		if (intersectTop == true) down = true;
		if (intersectBottom == true) down = false;
	}

	return getMax(puttedObjs);
}
