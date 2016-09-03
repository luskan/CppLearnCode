//
// Created by marci_000 on 07.08.2016.
//

#include "cppprimer_ch17.h"

#include <tuple>
#include <iostream>
#include <functional>
#include <bitset>

#include <regex>

std::tuple<std::string, int, int> foo() {
  return std::tuple<std::string, int, int>("hellp", 1, 2);
}

template<int Ind, int Max, typename... Args>
struct PrintTuple {
  static void print(std::ostream& os, const std::tuple<Args...>& arg) {
    os << (Ind == 0 ? "" : ", ") << std::get<Ind>(arg);
    PrintTuple<Ind + 1, Max, Args...>::print(os, arg);
  }
};

template<int Max, typename... Args>
struct PrintTuple<Max, Max, Args...> {
  static void print(std::ostream& os, const std::tuple<Args...>& arg) {
  }
};

template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
  os << "[";
  PrintTuple<0, sizeof...(Args), Args...>::print(os, t);
  os << "]";
  return os;
}

void BitSetsAndTuples() {
  std::bitset<8> bs("1011");
  bs.flip(1);
  std::cout << bs.to_ullong() << " = " << bs.to_string();

  auto tp = std::make_tuple("Hello","World",2015);
  std::cout << tp << "\n";

  std::tuple<std::string, int, int> res = foo();
  std::get<0>(res) = 6;
  std::cout << std::get<0>(res) << ", " << std::get<1>(res) << ", " << std::get<2>(res) << std::endl;



  std::string ss = "";
  auto res2 = std::make_tuple(std::ref(ss), 1, 2);
  std::get<0>(res2) = "123";
  std::cout << ss << ", " << std::get<0>(res2) << std::endl;

  std::string ss2;
  int ii;
  std::make_tuple(std::ref(ss2), ii, ii) = res2;
  std::cout << ss2 << std::endl;

  std::string ss3;
  std::tie(ss3, std::ignore, std::ignore) = res2;
  std::cout << ss3 << std::endl;

  //
  auto tt = std::tuple_cat(std::make_tuple("1", "2"), std::make_tuple(1,2));
  std::cout << "size of " << std::tuple_size<decltype(res2)>::value << std::endl;
}

void RegExps() {
  std::regex r(R"((\d)+-(\d)+)");
  std::string text = "1-4 8-6 10-123";
  std::string text2 = "1-4";
  for (std::sregex_iterator it(text.begin(), text.end(), r), end; it!=end; ++it) {
    std::cout << it->str() << "\n";
  }

  std::smatch sm;
  if ( std::regex_match(text2, sm, r)) {
    std::cout << "Found : " << sm.str() << "\n";
  }
}

void cppprimer_ch17::run() {
  //BitSetsAndTuples();
  RegExps();
}
