//
// Created by marci_000 on 13.02.2016.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

void cppprimer_ch8() {
    std::fstream fout("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test1.txt", std::fstream::out|std::fstream::app );
    fout.seekp(0, std::ios_base::end);
    fout << "line 1" << std::endl;
    fout << "line 2" << std::endl;
    fout << "line 3" << std::endl;
    fout.close();

    std::stringstream str;
    std::ifstream fin("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt\\test1.txt");
    std::string line;
    while(std::getline(fin, line)) {
        str << line << std::endl;
    }

    fin.close();

    std::ofstream fouts("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt\\test1.txt", std::ofstream::ate | std::ofstream::out);
    fouts << str.str();

    fouts.close();
}