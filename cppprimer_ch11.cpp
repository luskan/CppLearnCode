//
// Created by marci_000 on 17.03.2016.
//

#include "cppprimer_ch11.h"
#include <set>
#include <map>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
#include <typeinfo>

#include <algorithm>
//#include <experimental/>
#include <iostream>
#include <iterator>

#include <memory>

template<typename T> class TD;

void wordTransform() {
    std::ifstream ifdict("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt");
    std::map<std::string, std::string> map;
    std::string word, to, line;
    while(ifdict >> word && std::getline(ifdict, to)) {
        map.insert({word, to.substr(1)});
    }

    std::ifstream ifwords("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test1.txt");
    while(std::getline(ifwords, line)) {
        std::istringstream linestr(line);
        while (linestr >> word) {
            auto itr = map.find(word);
            if (itr != map.end()) {
                std::cout << itr->second;
            }
            else {
                std::cout << word;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void cppprimer_ch11::run() {

    const char* szName = "my name is ok";
    static const std::string name(szName);

    std::cout << (void*)szName << std::endl;
    std::cout << (void*)name.c_str() << std::endl;

    std::unordered_multimap<std::string, int> umap = {{"alf",1}, {"alf",2}, {"john",2}};
    for(auto it = umap.begin(); it != umap.end(); ++it) {
        std::cout << it->first << " - " << it->second << std::endl;
    }
    std::cout << "count = " << umap.count("alf") << std::endl;

    //wordTransform();

    //std::istream_iterator<std::string> in(std::cin), end;
    //std::set<std::string> m(in, end);
    //for(auto s : m) std::cout << s << ", ";

    /*
    // Three ways to scan multimap:

    std::multimap<std::string, std::string> work;
    work.insert({"Tom", "IBM"});
    work.insert({"Tom", "Google"});
    work.insert({"Tom", "MS"});
    std::cout << work.count("Tom") << "\n";

    // First with count
    int count = work.count("Tom");
    auto itr = work.find("Tom");
    for ( int k = 0; k < count; ++k, ++itr) {
        std::cout << k << ": " << itr->second << "\n";
    }

    // With lower/upper bound
    int ik = 0;
    for (auto beg = work.lower_bound("Tom"), end = work.upper_bound("Tom"); beg != end; ++beg, ++ik) {
        std::cout << ik << ": " << beg->second << "\n";
    }

    // With equal_range
    ik = 0;
    for (auto pos = work.equal_range("Tom"); pos.first != pos.second; ++pos.first, ++ik) {
        std::cout << ik << ": " << pos.first->second << "\n";
    }
    */


    /*
    typedef std::vector<std::pair<int,int> > vec_type; std::array<vec_type, 100> arr;
    {
        std::ifstream reader("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt");
        std::string line;
        std::string name;
        std::map<std::string, int> arr;
        int np = 5;
        for (int i = 0; i < np; i++) {
            getline(reader, line);
            line = line + "\r";

            auto cr_pos = line.rfind('\r');
            if ( cr_pos != std::string::npos )
                line = line.substr(0, cr_pos);
            name = "\"" + line + "\"";

            std::cout << name << std::endl;
        }
    }
    */

    /*
    std::vector<unsigned char> v{1, 2, 3};
    std::stringstream str;
    std::transform(v.begin(), v.end(), std::ostream_iterator<std::string>(str), [&](auto c) {
        return (str.rdbuf()->in_avail() ? "-" : "") + std::to_string(c);
    });
    std::cout << str.str() << std::endl;

    std::list<double> x{1, 2, 3, 4, 5, 6};
    std::stringstream sstr;
    std::transform(v.begin(), v.end(), std::ostream_iterator<std::string>(sstr), [&](auto c) {
        return (sstr.rdbuf()->in_avail() ? "," : "") + std::to_string(c);
    });
    std::cout << sstr.str() << std::endl;

    return;
    */

    /*
    std::fstream fin(R"(C:\Users\marci_000\ClionProjects\TestCpp1\test.txt)");
    std::string line;
    std::map<std::string, std::vector<int>> wordToLineMap;
    int lineNum = 0;
    while (std::getline(fin, line)) {
        lineNum++;
        std::stringstream str(line);
        std::string word;
        while (str >> word) {
            std::string alpha_word;
            std::copy_if(word.begin(), word.end(), std::back_inserter(alpha_word), [](char c) { return isalnum(c); });
            wordToLineMap[alpha_word].push_back(lineNum);
        }
    }

    std::vector<decltype(wordToLineMap)::iterator> ivec;
    auto ins = std::back_inserter(ivec);
    for (auto it = wordToLineMap.begin(); it != wordToLineMap.end(); ++it)
        *ins = it;
    std::sort(ivec.rbegin(), ivec.rend(),
              [](decltype(wordToLineMap)::const_iterator itr1, decltype(wordToLineMap)::const_iterator itr2) {
                  return itr1->second.size() < itr2->second.size();
              }
    );


    std::ostream_iterator<int> ios(std::cout, ", ");
    for (auto it = ivec.begin(); it != ivec.end(); ++it) {
        std::cout << (*it)->first << " - ";
        auto &ivec = (*it)->second;
        auto uit = std::unique(ivec.begin(), ivec.end());
        std::copy(ivec.begin(), uit, ios);
        std::cout << std::endl;
    }
    */

    /*
    std::ostream_iterator<int> ios(std::cout, ", ");
    for (auto it = wordToLineMap.begin(); it != wordToLineMap.end(); ++it){
        std::cout << it->first << " - ";
        auto& ivec = it->second;
        auto uit = std::unique(ivec.begin(), ivec.end());
        std::copy(ivec.begin(), uit, ios);
        std::cout << std::endl;
    }
     */

    /*
    std::set<int> s = {0, 1, 2, 3};
    std::ostream_iterator<int> os(std::cout, ":");
    std::copy(s.begin(), s.end(), os);

    TestStr ts;
    std::map<std::string, int> m = {
            {ts, 123},
            {"Merry", 124},
            {"Merry", 124},
            {"Merry", 124},
            {"Kris", 125},
            {"Arnold", 126}
    };
    for (auto item : m) {
        std::cout << item.first << " - " << item.second << std::endl;
    }
     */

}
