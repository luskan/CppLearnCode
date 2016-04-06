#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include <numeric>
//#include <list>
#include <iterator>
#include <algorithm>
#include <fstream>
//#include <functional>
#include <locale>
#include <list>
#include "cppprimer_ch9.h"

struct csv_reader: std::ctype<char> {
    csv_reader(): std::ctype<char>(get_table()) {}
    static std::ctype_base::mask const* get_table() {
        static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());

        rc[','] = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;
        rc[' '] = std::ctype_base::space;
        return &rc[0];
    }
};

void line_up(std::string tpos[15], std::string lineup[15], std::string roster[15]){
    std::cout << tpos[0];

}

void cppprimer_ch9() {

    std::list<int> ai = {1, 2, 3, 4, 5};
    std::list<int> ai2 = {100, 200, 300, 400, 500};

    std::ostream_iterator<int> oit(std::cout, ", ");

    auto it = std::find(ai.begin(), ai.end(), 2);
    ai.splice(it, ai2);
    std::copy(ai.begin(), ai.end(), oit);


    /*
    std::vector<int> all_ints = {1,2,3,4,5,6,7,8};
    std::vector<int> only_odds;
    std::remove_copy_if(all_ints.begin(), all_ints.end(), std::back_inserter(only_odds), [](int i){return i % 2 == 0;});
    std::copy(only_odds.begin(), only_odds.end(), std::ostream_iterator<int>(std::cout, " "));
*/
    /*
    std::fstream fs("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt");
    fs.imbue(std::locale(std::locale(), new csv_reader()));
    std::istream_iterator<std::string> is(fs);
    std::cout << *is++ << std::endl;
    std::cout << *is++ << std::endl;
    std::cout << *is++ << std::endl;
    */

    /*
    std::fstream fs("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt");
    std::string line;
    while(std::getline(fs, line)) {
        std::stringstream str(line);
        std::istream_iterator<int> begin(str), end;
        std::vector<int> vec(begin, end);
        std::cout << *std::max_element(vec.begin(), vec.end()) << std::endl;
    }
     */

    //X xa;
    //xa.func();
    //auto fc = []() mutable {};

    //std::vector<std::string> vec = {"Alfred", "Gregory", "Mainfield"};
    //std::for_each(vec.begin(), vec.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, "Name: "));

    //std::istream_iterator<int> ins(std::cin), eof;
    //std::copy(ins, eof, std::inserter(vec, vec.begin()));
    //std::list<int> vec(ins, eof);
    //int sum = 9;//std::accumulate(ins, eof, 0);
    //std::cout << "sum: " << sum << std::endl;

    /*
    std::istream_iterator<data_item> item_beg(std::cin), item_end;
    std::vector<data_item> data_vec(item_beg, item_end);
    std::ostream_iterator<data_item> item_out_beg(std::cout), item_out_end();
    std::copy(data_vec.begin(), data_vec.end(), item_out_beg);
*/

    /*
    std::ostream_iterator<int> out(std::cout, ";");
    out = 98;
    std::vector<int> vec = {0, 1, 2,3,4};
    std::copy(vec.begin(), vec.end(),out);*/

    /*
    std::ifstream ifs(R"(C:\Users\marci_000\ClionProjects\TestCpp1\test.txt)");
    std::istream_iterator<std::string> itr_beg(ifs), itr_end;
    std::vector<std::string> vec(itr_beg, itr_end);
    for (auto it : vec) {
        std::cout << it << ";";
    }
    */

    /*
    std::istream_iterator<int> ibeg(std::cin), iend;
    std::vector<int> vec(ibeg, iend);
    std::sort(vec.begin(), vec.end());
    std::vector<int> uvec;
    std::unique_copy(vec.cbegin(), vec.cend(), std::back_inserter(uvec));
    std::ostream_iterator<int> obeg(std::cout, ";");
    std::copy(uvec.cbegin(), uvec.cend(), obeg);
     */

    /*
    std::ifstream ifs(R"(C:\Users\marci_000\ClionProjects\TestCpp1\test.txt)");
    std::ofstream ofs_odd(R"(C:\Users\marci_000\ClionProjects\TestCpp1\test_odd.txt)", std::fstream::ate|std::fstream::trunc);
    std::ofstream ofs_even(R"(C:\Users\marci_000\ClionProjects\TestCpp1\test_even.txt)", std::fstream::ate|std::fstream::trunc);
    std::ostream_iterator<int> odd_out(ofs_odd, " ");
    std::ostream_iterator<int> even_out(ofs_even, " ");
    std::istream_iterator<int> inf(ifs), end;
    while(inf != end) {
        int val = *inf++;
        if ( val & 1)
            odd_out = val;
        else
            even_out = val;
    }
    */

    /*
    std::list<int> ivec = {0,1,2,3,4,5};
    ivec.sort();
    //std::sort(ivec.rbegin(), ivec.rend());
    for (auto it : ivec) {
        std::cout << it << ", ";
    }
     */

    /*
    std::vector<int> ivec = {0,1,1,2,3,4,5};
    auto end = std::unique(ivec.begin(), ivec.end());
    std::ostream_iterator<int> oi(std::cout, ";");
    std::copy(ivec.begin(), end, oi);
*/
    /*
    auto ritr = std::find(ivec.crbegin(), ivec.crend(), 2);
    std::cout << *ritr << std::endl;
    auto itr= ritr.base();
    std::cout << *itr << std::endl;
     */


}

void DataTest::foo() {

}
