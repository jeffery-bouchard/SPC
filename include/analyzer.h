#pragma once
#include <vector>

using namespace std;

// cp - cpk analyzer class
class analyzer {

    private:
        //attributes
        double _upperLimit;
        double _lowerLimit;
        vector<double> _data;

        //methods
        double calcMean();
        double calcSigma();

    public:
        //methods
        analyzer();
        analyzer(double upperLimit, double lowerLimit);
        void setLimits(double upperLimit, double lowerLimit);
        void insertData(double data);
        double calcCp();
        double calcCpk();
};