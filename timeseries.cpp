#include "timeseries.h"

using namespace std;
// Used from fluentcpp.com inorder to parse the string
vector<string> split(const string& s, char deli) {
   vector<string> tokens;
   string token;
   std::stringstream ss(s);
   while(getline(ss, token, deli)) {
       tokens.push_back(token);
   }
   return tokens;
}


TimeSeries::TimeSeries(const char* CSVfileName) {
    ifstream CSVFile(CSVfileName);
    if(!(CSVFile.is_open())) {
        throw "File could not be opened";
    }   
    string str;
    getline(CSVFile, str, '\n');  

    _featureVec = split(str, ',');
    _numberOfFeatures = _featureVec.size();
    
    vector<string> strValueVec;

    int _numberOfFeatures = _featureVec.size();
    float CSVValue;
    
    while(getline(CSVFile, str, '\n')) {
        strValueVec = split(str, ',');
        for(int i = 0; i < _numberOfFeatures; i++) {
            CSVValue = stof(strValueVec[i]);
            _map[_featureVec[i]].push_back(CSVValue);
        }
    }
    CSVFile.close();
}

