#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "../include/parser.h"

using namespace std;

//constructor
parser::parser(char delim, string file) {
    _delim = delim;
    _file = file;
}

//read csv file
void parser::readFile() {
    ifstream file;
    file.open(_file);
    string line, word, name, temp;
    getline(file, temp);   //ignore first line (header row)
    while (getline(file, line)) {
        stringstream str_strm(line);
        getline(str_strm, name, _delim);
        getline(str_strm, temp, _delim);
        _dataset[name].value = stof(temp);
        getline(str_strm, _dataset[name].units, _delim);
        getline(str_strm, temp, _delim);
        _dataset[name].lsl = stof(temp);
        getline(str_strm, temp, _delim);
        _dataset[name].usl = stof(temp);
        getline(str_strm, _dataset[name].status, _delim);
    }
}

//get datapoint
datapoint parser::getData(string name) {
    return _dataset[name];
}