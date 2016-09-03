//
// Created by marci_000 on 24.06.2016.
//

#ifndef TESTCPP1_QUERY_H
#define TESTCPP1_QUERY_H

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <set>
#include <map>

class QueryResult {
  using line_no = std::vector<std::string>::size_type;
  friend std::ostream& print(std::ostream&, const QueryResult&);
 public:
  QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) :
      sought(s), lines(p), file(f) {}
  std::set<line_no>::const_iterator begin() const { return lines->cbegin(); }
  std::set<line_no>::const_iterator end() const { return lines->cend(); }
  auto get_file() { return file; }
 private:
  std::string sought;
  std::shared_ptr<std::set<line_no>> lines;
  std::shared_ptr<std::vector<std::string>> file;
};

class TextQuery {
 public:
  using line_no = std::vector<std::string>::size_type;
  TextQuery(std::ifstream&);
  QueryResult query(const std::string&) const;
 private:
  std::shared_ptr<std::vector<std::string>> file;
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class Query_base {
  friend class Query;
 protected:
  using line_no = TextQuery::line_no;
 private:
  virtual QueryResult eval(const TextQuery&) const = 0;
  virtual std::string rep() const = 0;
};

class Query {
  friend Query operator~(const Query&);
  friend Query operator|(const Query&, const Query&);
  friend Query operator&(const Query&, const Query&);
 public:

  Query(const std::string&);
  QueryResult eval(const TextQuery &t) const { return q->eval(t);}
  std::string rep() const { return q->rep();}
 private:
  Query(std::shared_ptr<Query_base> query) : q(query) {  }
  std::shared_ptr<Query_base> q;
};

static std::ostream& operator<<(std::ostream& os, const Query &query) {
  return os << query.rep();
}

class WordQuery : public Query_base {
  friend class Query;

  WordQuery(const std::string &s) : query_word(s) { }

  QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
  std::string rep() const { return query_word; }
  std::string query_word;
};

class NotQuery : public Query_base {
  friend Query operator~(const Query&);
  NotQuery(const Query &q) : query(q){}

  std::string rep() const { return "~(" + query.rep() + ")";}

  QueryResult eval(const TextQuery&) const;
  Query query;
};

inline
Query operator~(const Query &operand) {
  return std::shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery: public Query_base {
 protected:
  BinaryQuery(const Query &l, const Query &r, std::string s) :
      lhs(l), rhs(r), opSym(s) {}
  std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
  Query lhs, rhs;
  std::string opSym;
};

class AndQuery: public BinaryQuery {
  friend Query operator&(const Query&, const Query&);
  AndQuery(const Query &left, const Query &right): BinaryQuery(left, right, "&") {}
  QueryResult eval(const TextQuery&) const;
};
inline
Query operator&(const Query& lhs, const Query& rhs) {
  return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery: public BinaryQuery {
  friend Query operator|(const Query&, const Query&);
  OrQuery(const Query &left, const Query &right): BinaryQuery(left, right, "|") {}
  QueryResult eval(const TextQuery&) const;
};
inline
Query operator|(const Query& lhs, const Query& rhs) {
  return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

void runTestMain(std::ifstream&);

template<typename T>
class A {
 public:
  void foo();
};

#endif //TESTCPP1_QUERY_H
