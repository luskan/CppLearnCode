//
// Created by marci_000 on 24.06.2016.
//

#include "Query.h"
#include <sstream>
#include <algorithm>
#include <iostream>

TextQuery::TextQuery(std::ifstream &is) {
  std::string text;
  file.reset(new std::vector<std::string>);
  while(std::getline(is, text)) {
    file->push_back(text);
    int n = file->size()-1;
    std::istringstream line(text);
    std::string word;
    while(line >> word) {

      auto trim_beg = std::find_if(word.cbegin(), word.cend(), isalnum);
      auto trim_rend = std::find_if(word.crbegin(), word.crend(), isalnum);
      decltype(trim_beg) trim_end;
      if ( trim_rend == word.crend() )
        trim_end = trim_beg;
      else
        trim_end = trim_rend.base();
       word = std::string(trim_beg, trim_end);

      auto &lines = wm[word];
      if (!lines)
        lines.reset(new std::set<line_no>);
      lines->insert(n);
    }
  }
}

std::string make_plural(size_t ctr, const std::string &word, const std::string &ending) {
  return (ctr > 1) ? word + ending : word;
}

std::ostream& print(std::ostream& os, const QueryResult& qr) {
  os << qr.sought << " occurs " << qr.lines->size() << " "
      << make_plural(qr.lines->size(), "time", "s") << std::endl;
  for (auto num : *qr.lines)
    os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
  return os;
}

QueryResult TextQuery::query(const std::string &sought) const {
  static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
  auto loc = wm.find(sought);
  if (loc == wm.end())
    return QueryResult(sought, nodata, file);
  else
    return QueryResult(sought, loc->second, file);
}

QueryResult AndQuery::eval(const TextQuery& text) const {
  auto left = lhs.eval(text);
  auto right = rhs.eval(text);
  std::shared_ptr<std::set<line_no>> new_set(new std::set<line_no>());
  std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*new_set, new_set->begin()));
  return QueryResult(rep(), new_set, left.get_file());
}

QueryResult OrQuery::eval(const TextQuery& text) const {
  auto left = lhs.eval(text);
  auto right = rhs.eval(text);
  std::shared_ptr<std::set<line_no>> new_set(new std::set<line_no>(left.begin(), left.end()));
  //std::copy(right.begin(), right.end(), std::inserter(*new_set, new_set->begin()));
  new_set->insert(right.begin(), right.end());
  return QueryResult(rep(), new_set, left.get_file());
}

inline
Query::Query(const std::string &s) : q(new WordQuery(s)) {
}

QueryResult NotQuery::eval(const TextQuery& text) const {
  auto res = query.eval(text);
  std::shared_ptr<std::set<line_no>> not_set(new std::set<line_no>);
  auto beg = res.begin(), end = res.end();
  auto sz = res.get_file()->size();
  for (size_t i = 0; i < sz; ++i) {
    if ( beg == end || *beg != i )
      not_set->insert(i);
    else
      if (beg != end)
        ++beg;
  }
  return QueryResult(rep(), not_set, res.get_file());
}

void runTestMain(std::ifstream& infile) {
  TextQuery tq(infile);

  /*
  while(true) {
    std::cout << "enter word to look for, or q to quit: ";
    std::string s;
    if (!(std::cin >> s) || s == "q") break;
    print(std::cout, tq.query(s)) << std::endl;
  }
   */

  Query q = Query("fiery") & Query("bird") | Query("wind") ;
  print(std::cout, q.eval(tq)) << std::endl;
}

template<typename T>
void A<T>::foo() {
}

template class A<int>;
