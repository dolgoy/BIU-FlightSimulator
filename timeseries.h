#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>


#ifndef TIMESERIES_H_
#define TIMESERIES_H_


using namespace std;

class TimeSeries{
private:
	vector<string> _featureVec;
	map<string, vector<float>> _map;
	int _numberOfFeatures;
public:
	TimeSeries(const char*);
	map<string, vector<float>> getMap() const {
		return _map;
	}
	vector<string> getFeatureVec() const {
		return _featureVec;
	}
	vector<float>& getValueVec(string s) const {
		return getMap()[s];
	}
};



#endif /* TIMESERIES_H_ */
