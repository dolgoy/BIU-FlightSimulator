#include "SimpleAnomalyDetector.h"

float maxRowPeasron(const TimeSeries& ts, int i) {
	float maxPears = 0;
	int featureVecSize = ts.getFeatureVec().size();
	const int valueVecSize = ts.getMap()[ts.getFeatureVec()[0]].size();
	for(int j = 1 + i; j < featureVecSize; j++) {
		maxPears = max(maxPears, fabs(pearson(&(ts.getMap()[ts.getFeatureVec()[i]][0]), &(ts.getMap()[ts.getFeatureVec()[j]][0]), valueVecSize)));
		} return maxPears;
}
void lin_regInit(Point** pointArr, correlatedFeatures& x,const TimeSeries& ts, int size, int i, int j) {
	for(int k = 0; k < size; k++) {
		pointArr[k] = new Point(ts.getMap()[ts.getFeatureVec()[i]][k], ts.getMap()[ts.getFeatureVec()[j]][k]);
	} x.lin_reg = linear_reg(pointArr, size);
}
void thresholdInit(Point** pointArr, correlatedFeatures& x, int size) {
	float threshold = 0;
	for(int k = 0; k < size; k++) {
		threshold = max(threshold, fabs(dev(*pointArr[k], x.lin_reg)));
	} x.threshold = threshold;
}
void destroyPointArr(Point** pointArr, int size) {
		for(int k = 0; k < size; k++) {
		delete(pointArr[k]);
	}
}
void correlatedFeatureStructInit(correlatedFeatures& x, float pears, int i, int j,int size, const TimeSeries& ts) {
	x.feature1 = ts.getFeatureVec()[i];
	x.feature2 = ts.getFeatureVec()[j];
	x.corrlation = pears;
	Point* pointArr[size];
	lin_regInit(pointArr, x, ts, size, i, j);
	thresholdInit(pointArr, x, size);
	destroyPointArr(pointArr, size);
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
	vector<string> featureVec = ts.getFeatureVec();
	int featureVecSize = featureVec.size();
	int valueVecSize = ts.getMap()[featureVec[0]].size();
	struct correlatedFeatures correlatedFeaturesStruct;
	for(int i = 0; i < featureVecSize - 1; i++) {
		float maxRowPears = maxRowPeasron(ts, i);
		for(int j = i + 1; j < featureVecSize; j++) {
			float pears = pearson(&(ts.getMap()[featureVec[i]][0]), &(ts.getMap()[featureVec[j]][0]), valueVecSize);
			if((fabs(pears) == maxRowPears) && (fabs(pears) > 0.9)) {
				correlatedFeatureStructInit(correlatedFeaturesStruct, pears, i, j, featureVecSize, ts);
				cf.push_back(correlatedFeaturesStruct);
			}
		}
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	return vector<AnomalyReport>();
}
