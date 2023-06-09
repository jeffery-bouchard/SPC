#include <iostream>
#include <string>
#include "../include/analyzer.h"
#include "../include/parser.h"

using namespace std;

//main method
int main(int argc, char* argv[]) {

    if (argc == 1) {
        cout << "No data files provided" << endl;
        return 0;
    } else {

        //declare variables
        analyzer vddAnalyzer, gndAnalyzer, voAnalyzer;
        bool limits = false;

        //loop over file list
        for (int i = 1; i < argc; i++) {

            //parse file
            string f = argv[i];
            parser file(',', f);
            file.readFile();

            //get Vdd data
            datapoint vdd = file.getData("Vdd");
            if (!limits) {
                double usl = vdd.usl;
                double lsl = vdd.lsl;
                vddAnalyzer.setLimits(usl, lsl);
            }
            double data = vdd.value;
            vddAnalyzer.insertData(data);

            //get GND data
            datapoint gnd = file.getData("gnd");
            if (!limits) {
                double usl = gnd.usl;
                double lsl = gnd.lsl;
                gndAnalyzer.setLimits(usl, lsl);
            }
            data = gnd.value;
            gndAnalyzer.insertData(data);

            //get Vout data
            datapoint vo = file.getData("Vout");
            if (!limits) {
                double usl = vo.usl;
                double lsl = vo.lsl;
                voAnalyzer.setLimits(usl, lsl);
            }
            data = vo.value;
            voAnalyzer.insertData(data);

            limits = true;   //set limits with first file only
        }

        //calculate Vdd SPC
        double vddCp = vddAnalyzer.calcCp();
        double vddCpk = vddAnalyzer.calcCpk();
        std::cout << "Vdd Cp = " << vddCp << endl;
        std::cout << "Vdd Cpk = " << vddCpk << endl;

        //calculate Vout SPC
        double voCp = voAnalyzer.calcCp();
        double voCpk = voAnalyzer.calcCpk();
        std::cout << "Vout Cp = " << voCp << endl;
        std::cout << "Vout Cpk = " << voCpk << endl;

        //calculate GND SPC
        double gndCp = gndAnalyzer.calcCp();
        double gndCpk = gndAnalyzer.calcCpk();
        std::cout << "Gnd Cp = " << gndCp << endl;
        std::cout << "Gnd Cpk = " << gndCpk << endl;

        return 0;
    }
}