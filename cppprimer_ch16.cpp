//
// Created by marci_000 on 23.07.2016.
//

#include "cppprimer_ch16.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

namespace mlib {

  template<typename T>
  class shared_ptr {
    typedef T elemet_type;
    T* ptr;
    std::function<void(T*)> delFunc;
   public:
    shared_ptr() : ptr(nullptr), delFunc(nullptr) {}

    template<typename Y>
    explicit shared_ptr(Y* p) : ptr(p), delFunc(nullptr) {}

    template<typename Y, typename D>
    shared_ptr(Y* p, D d) : ptr(p), delFunc(d) {}

    ~shared_ptr() {
      if(delFunc) {
        delFunc(ptr);
      }
      else
        delete ptr;
    }
  };

}

template<typename T>
struct TD;

template<typename T>
std::string debug_rep(const T& t) {
  std::ostringstream str;
  str << t;
  return str.str();
}

template<typename T>
std::string debug_rep(T* p) {
  std::ostringstream str;
  str << p;
  if (p)
    str << " = " << *p;
  return str.str();
}

std::string debug_rep(const char* p) {
  std::ostringstream str;
  str << static_cast<const void*>(p);
  if (p)
    str << " = " << p;
  return str.str();
}

template<typename T>
void print(std::ostream& os, const T& arg) {
  os << arg;
}

template<typename T, typename... Args>
void print(std::ostream& os, const T& arg, const Args&... args) {
  os  << arg << ", ";
  print(os, args...);
}

template<typename... Args>
void debug_print(std::ostream& os, const Args&... args) {
  print(os, debug_rep(args)...);
}

struct Xch16 {
  Xch16(){}
  Xch16(std::string&& r){}
};

template<typename T, typename ...Args>
void createAndPrint(Args&&... args) {
  T t(std::forward<Args>(args)...);
  //T t(args...);
  //std::cout << t;
}

struct S
{

  S() = default;

  std::vector<int> v{0};

};

template<typename T>
void foo(const T& f) {
  std::cout << "foo(const T& f)\n";
}

template<typename T, size_t N>
void foo(const T (&arr)[N]) {
  std::cout << "foo(const T (&arr)[N])\n";
}

template<>
void foo(const char* const& f) {
  std::cout << "foo(const char* const& f)\n";
}


/*
namespace std {
  template<typename T>
  class hash;
}
*/

template<typename T> struct hash;

struct MyData {
  MyData() {}
  MyData(int d1, int d2) : data1(d1), data2(d2) {}
  bool operator==(const MyData& rop) const {
    return rop.data1 == data1 && rop.data2 == data2;
  }

  friend struct std::hash<MyData>;
 private:
  int data1;
  int data2;
};

namespace std {
  template<>
  struct hash<MyData> {
    typedef MyData argument_type;
    typedef size_t result_type;
    size_t operator()(const argument_type& data) const noexcept;
  };

  size_t hash<MyData>::operator()(const argument_type& data) const noexcept {
    return hash<unsigned>()(data.data1) ^ hash<unsigned>()(data.data2);
  }
}

template<typename T>
class FooX {
 public:
  void doWork(){ std::cout <<"org\n";}
};

template<typename T>
class FooX<T*> {
 public:
  void doWork(){ std::cout <<"second\n";}
};

template<typename T>
int sumOccurrences(const std::vector<T>& vec, T val) {
  return std::count_if(vec.begin(), vec.end(), [&](auto& v) { if (v == val) ; else return false;});
}

template<typename T>
void debugRep2(T const& t) {
  std::cout << "debugRep(const T& t)\n";
}

template<>
void debugRep2<const char*>(const char* const& t) {
  std::cout << "const char*& t\n";
}

void cppprimer_ch16::run() {
  std::cout << "cppprimer_ch16\n";

  std::vector<int> vv = {0,1,4,3,4,5};
  std::cout << sumOccurrences(vv, 4);

  int n;
  int *pn = &n;
  debugRep2(n);
  debugRep2(pn);

  /*
  foo(1);
  foo("hellp");
  const char* pp = "aaa";
  foo(pp);
*/

  //std::unordered_map<std::string, std::string> mm;
  //mm["23"] = "ds";

  std::unordered_map<MyData, std::string> mm;
  mm[MyData(1,1)] = "test1";
  mm[MyData(2,2)] = "test1";

  /*
  print(std::cout, "apha", "beta", 1, 2, 3);
   */

  /*
  int val = 123;
  const char* s = "hell";
  std::string str = "Wrong word!";
  std::cout << debug_rep(str) << "\n";
  std::cout << debug_rep(&val) << "\n";
  std::cout << debug_rep(s) << "\n";
   */

  /*
  mlib::shared_ptr<std::string> pp;
  mlib::shared_ptr<std::string> pp2(new std::string("23"),
                                    [](auto p) {
                                      delete p;
                                    }
  );
   */
}
