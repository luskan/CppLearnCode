//
// Created by marci_000 on 17.03.2016.
//

#include "cppprimer_ch12.h"
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
#include <cassert>

#include<type_traits>
#include<boost/type_traits.hpp>

namespace cppprimier_ch12 {

class PimplTestImpl {

};

PimplTest::PimplTest() : pimpl(new PimplTestImpl) {
}

PimplTest::~PimplTest() {

}

template<typename T>
class has_not_equal {
  template<typename U>
  struct null_value {
    static U &value;
  };

  template<typename U>
  static std::true_type test(U *, decltype(null_value<U>::value != null_value<U>::value) * = 0);
  static std::false_type test(void *);

 public:
  typedef decltype(test(static_cast<T *>(0))) type;
  static const bool value = type::value;
};

struct sample1 {
  bool operator!=(const sample1 &) { return true; }
};

struct sample2 {
};

#include <algorithm>
//#include <experimental/>
#include <iostream>
#include <iterator>

#include <memory>

class StrBlob {
 public:
  typedef std::vector<std::string>::size_type size_type;

  StrBlob();
  StrBlob(std::initializer_list<std::string> il);

};

struct TestMe {

  int value;
  virtual ~TestMe() { }
  //TestMe() {
  //    std::cout << "TestMe::TestMe" << std::endl;
  //}
};

int foo(int p) {
    return 0;
}

class X {
 public:
  X() { }
  X(X *) { }
  std::shared_ptr<X> iterator() const {
      auto iter = std::make_shared<X>(new X);
      return iter;
  }
};

void freeMeDeallocator(int *p) {
    std::cout << "freeMeDeallocator" << std::endl;
}

template<typename T, size_t N>
std::string ArrToStr(T (&t)[N]) {
    return std::string(std::cbegin(t), std::cend(t));
}

int main2() {

    // std::string str2 = ARR_TO_STR("2+\0+2");
    std::string str2 = ArrToStr("2+2\0+2");
    //for (auto c : str2)
    std::cout << "2+2\0+2" << std::endl;
    std::cout << str2 << std::endl;
}


struct QueryResult {
  std::vector<std::pair<int, std::shared_ptr<std::string>>> lines;
};

class TextQuery {
  std::vector<std::shared_ptr<std::string>> lines;
  std::map<std::string, std::set<int>> index;
 public:
  TextQuery(std::ifstream &&inf) {
      std::string line;
      while (std::getline(inf, line)) {
          lines.push_back(std::make_shared<std::string>(line));
          std::stringstream str(line);
          std::string word;
          while (str >> word) {
              index[word].insert(lines.size() - 1);
          }
      }
  }

  QueryResult query(std::string &s) {
      QueryResult qr;
      const auto &lineInd = index[s];
      for (auto num : lineInd)
          qr.lines.push_back(std::make_pair(num, lines[num]));
      return qr;
  }
};

static std::ostream &print(std::ostream &os, const QueryResult &res) {
    for (auto ln : res.lines) {
        os << ln.first + 1 << ": " << ln.second->c_str() << "\n";
    }
    return os;
}

namespace Nam {

inline void fooBar() { }
}

void runQueries(std::ifstream &&infile) {
    TextQuery tq(std::move(infile));
    while (true) {
        std::cout << "enter word to look for, or q to quit:\n";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
    }
}

void cppprimer_ch12::run() {
    runQueries(std::ifstream("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt"));
    return;

    {
        std::vector<std::string> vec = {"ALF", "B"};
        std::string toSearch = "Alf";
        auto itr = std::find_if(vec.begin(), vec.end(),
                                [&](auto &s) {
                                  if (s.size() != toSearch.size())
                                      return false;
                                  for (size_t i = 0; i < s.size(); ++i)
                                      if (::tolower(s[i]) == ::tolower(toSearch[i]))
                                          return true;
                                  return false;
                                }
        );
        if (itr != vec.end()) {
            std::cout << *itr << std::endl;
        }
    }
    main2();

    int *pInt1 = new int;
    int *pInt2 = new int();
    std::cout << *pInt1 << std::endl;
    std::cout << *pInt2 << std::endl;

    std::cout << "Default initialization of class type with default c-tor" << std::endl;
    std::cout << (new TestMe)->value << std::endl;  // value is uninitialized
    std::cout << (new TestMe())->value << std::endl;// value is value initialized.

    const int *pi = new const int(1);
    //*pi = 123;

    std::shared_ptr<int> pref(new int);

    const X x;
    auto i = x.iterator();
    i->iterator();

    //12.6
    int *p1 = new int(6);
    std::unique_ptr<int> ptr1(p1);
    std::unique_ptr<int> ptr2;
    //ptr2 = ptr1;

    {
        int ix = 1024, *pi = &ix, *pi2 = new int(1024);
        typedef std::unique_ptr<int> IntP;
        //IntP p0(ix);
        //IntP p1(pi);
        IntP p2(pi2);
        //IntP p3(&ix);
        //IntP p4(pi);
    }

    // Write test data
    std::vector<bool> bit;
    bit.push_back(0);
    bit.push_back(0);
    bit.push_back(0);
    for (int n = 0; n < 8 * 13; ++n)
        bit.push_back((n / 8 % 2) == 0);

    std::ofstream ofs("p:\\test.data", std::ifstream::binary);
    for (auto it = bit.begin(); it != bit.end();) {
        char toWrite = 0;
        for (int n = 7; it != bit.end() && n >= 0; --n, ++it) toWrite |= *it << n;
        ofs.write(&toWrite, 1);
    }
    ofs.close();

    // Read data
    std::vector<bool> bit2;
    union S {
      struct {
        unsigned short pad : 5;
        unsigned short dat : 8;
        unsigned short oth : 3;
      };
      char bytes[2];
    } data;
    bit2.push_back(0); // First three bits are padding
    bit2.push_back(0);
    bit2.push_back(0);
    std::ifstream ifs("p:\\test.data", std::ifstream::binary);
    while (ifs.read(data.bytes, sizeof(data.bytes))) {
        std::swap(data.bytes[0], data.bytes[1]);
        std::cout << data.dat << std::endl;
        for (int n = 7; n >= 0; --n) bit2.push_back(data.dat & (1 << n));
        ifs.seekg(-1, ifs.cur);
    }
    assert(bit == bit2);

    /*

struct S {unsigned short pad : 3; unsigned short dat : 8; unsigned short oth : 5;};

!!! is for: pad
^^^ is for: data
### is for: oth

reading from file bytes 1 and 2 into above struct

File data     012345670123456701234567012345670123456701234567
Real data        012345670123456701234567012345670123456701234
              !!!^^^^^^^^#####

reading from file bytes 2 and 3 into above struct

File data     012345670123456701234567012345670123456701234567
Real data        012345670123456701234567012345670123456701234
                      !!!^^^^^^^^#####

reading from file bytes 3 and 4 into above struct

File data     012345670123456701234567012345670123456701234567
Real data        012345670123456701234567012345670123456701234
                              !!!^^^^^^^^#####

reading from file bytes 4 and 4 into above struct

File data     012345670123456701234567012345670123456701234567
Real data        012345670123456701234567012345670123456701234
                                      !!!^^^^^^^^#####


    */
    struct

        std::shared_ptr<int> spInt(new int(134), [](int *p) { std::cout << "free !" << std::endl; });

    std::unique_ptr<int, decltype(freeMeDeallocator) * > upInt(new int(123), freeMeDeallocator);

    //
    std::vector<std::unique_ptr<int>> vec;
    vec.push_back(std::unique_ptr<int>(new int(0)));
    vec.push_back(std::unique_ptr<int>(new int(1)));
    vec.push_back(std::unique_ptr<int>(new int(2)));
    vec.push_back(std::unique_ptr<int>(new int(3)));
    vec.push_back(std::unique_ptr<int>(new int(4)));
    vec.erase(vec.begin());
}

} // namespace cppprimier_ch12 {