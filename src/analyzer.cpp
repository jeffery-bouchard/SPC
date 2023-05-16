#include <vector>
#include <numeric>
#include <cmath>
#include "../include/analyzer.h"

using namespace std;

//constructor
analyzer::analyzer() {
}

//parameterized constructor
analyzer::analyzer(double upperLimit, double lowerLimit) {
    _upperLimit = upperLimit;
    _lowerLimit = lowerLimit;
}

void analyzer::setLimits(double upperLimit, double lowerLimit) {
    _upperLimit = upperLimit;
    _lowerLimit = lowerLimit;
}

//append data to dataset
void analyzer::insertData(double data) {
    _data.push_back(data);
}

//calculate mean (used in Cp/Cpk calcs)
double analyzer::calcMean() {
    double sum = accumulate(_data.begin(), _data.end(), 0.0);
    int sampleSize = _data.size();
    double mean = sum / sampleSize;
    return mean;
}

//calculate sigma for dataset (used in Cp/Cpk calcs)
double analyzer::calcSigma() {
    double mean = calcMean();
    int sampleSize = _data.size();
    double numerator = 0.0;

    for (unsigned int i = 0; i < sampleSize; i++) {
        double base = _data[i] - mean; 
        double addend = pow(base, 2);
        numerator = numerator + addend;
    }

    double quotient = numerator / sampleSize;
    double stdev = sqrt(quotient);

    return stdev;
}

//calculate Cp for dataset
double analyzer::calcCp() {
    double sigma = calcSigma();
    double numerator = _upperLimit - _lowerLimit;
    double denominator = 6 * sigma;
    double cp = numerator / denominator;
    return cp;
}

//calculate Cpk for dataset
double analyzer::calcCpk() {
    double mean = calcMean();
    double sigma = calcSigma();
    double sigma3x = sigma * 3;
    double cpku = (_upperLimit - mean) / sigma3x;
    double cpkl = (mean - _lowerLimit) / sigma3x;
    double cpk = min(cpku, cpkl);
    return cpk;
}