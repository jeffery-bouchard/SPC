#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

//structure for datapoint, corresponds to one csv line
struct datapoint {
    float value;
    string units;
    float lsl;
    float usl;
    string status;
};

//csv parser class
class parser {
    private:
        //attributes
        char _delim;
        string _file;
        unordered_map<string, datapoint> _dataset;

    public:
        //methods
        parser(char delim, string file);
        void readFile();
        datapoint getData(string name);
};