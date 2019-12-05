#include "Population.h"


Population::Population(vector<pair<int, int>> &obj, int size) : size(size) {
	individes.reserve(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < obj.size(); ++j) swap(obj[j], obj[rand() % obj.size()]);
		individes.push_back(vector<pair<int, int>>(obj));
	}
}

inline void Population::mutation(vector<pair<int, int>> &individ)
{
	swap(individ[rand() % individ.size()], individ[rand() % individ.size()]);
}

vector<pair<int, int>> Population::crossbreeding(const vector<pair<int, int>> &ma, const vector < pair<int, int>> &pa) {
	int p = rand();
	vector<pair<int, int>> child(ma.size());
	vector<pair<int, int>>::iterator it;
	for (int i = 0; i < ma.size() / 2; i++) {
		child[i] = ma[(p + i) %  ma.size()];
	}

	for (int i = 0; i < pa.size(); i++) {
		it = find(child.begin(), child.end(), pa[i]);
		if (it != child.end()) child.push_back(pa[i]);
	}

	return child;
}

int Population::extinction(const Encoder &encoder) {
	vector<pair<int, int>> values;
	for (int i = 0; i < individes.size(); i++) {
		values.push_back(pair<int, int>(i, encoder.encode(individes[i])));
	}

	sort(values.begin(), values.end(),
		[](const pair<int, int>& a, const pair<int, int>& b) -> bool
		{ return a.second < b.second; });

	vector<vector<pair<int, int>>> buf;
	for (int i = values.size() / 2 - 1; i < values.size(); i++) {
		buf.push_back(individes[values[i].first]);
	}

	individes.clear();
	individes.resize(0);
	for (auto it = buf.begin(); it != buf.end(); it++)
		individes.push_back(*it);

	return (values.end() - 1)->second;
}

int Population::lifeCircle(const Encoder& encoder) {
	int bestValue = extinction(encoder);

	for (int i = individes.size(), j = 0; i < this->size; i += 2, j++) {
		mutation(individes[j]);
		mutation(individes[j + 1]);
		individes.push_back(crossbreeding(individes[j], individes[j + 1]));
		individes.push_back(crossbreeding(individes[j + 1], individes[j]));
	}
	return bestValue;
}
