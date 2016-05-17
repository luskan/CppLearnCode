//
// Created by marci_000 on 27.04.2016.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "vec.h"
#include "cppprimer_ch13.h"

class DataPtr {
    std::string* ps;
    std::size_t* size;
public:
    DataPtr(const std::string &s="") : ps(new std::string(s)), size(new std::size_t(1)) {
        std::cout << "new caled\n";
    }
    DataPtr(const char* s) : ps(new std::string(s)), size(new std::size_t(1)) {
        std::cout << "new caled\n";
    }

    //DataPtr& operator=(DataPtr rop) {
    //    swap(*this, rop);
    //    std::cout << "op=\n";
    //    return *this;
    //}
    DataPtr& operator=(const DataPtr& rop) {
        if (this != &rop) {
            if (--*size == 0) {
                delete ps;
                delete size;
            }
            ps = rop.ps;
            size = rop.size;
            (*size)++;
        }
        return *this;
    }

    DataPtr(DataPtr&& rop) noexcept : ps(rop.ps), size(rop.size) {
        rop.ps = nullptr; rop.size = nullptr;
    }
    DataPtr& operator=(DataPtr&& rop) noexcept {
        if (&rop != this) {
            if (size && --*size == 0) {
                delete ps;
                delete size;
            }
            ps = rop.ps;
            size = rop.size;
            (*size)++;
        }
    }

    bool operator<(DataPtr& rhs) {
        return *this->ps < *rhs.ps;
    }

    DataPtr(const DataPtr& rhs) : ps(rhs.ps), size(rhs.size) {
        (*size)++;
        std::cout << "copy ctor\n";
    }
    ~DataPtr() {
        if (ps && --*size == 0) {
            delete ps;
            delete size;
            std::cout << "deleted\n";
        }
    }
//    friend void swap(DataPtr& op1, DataPtr& op2);
};
/*
void swap(DataPtr& op1, DataPtr& op2) {
    using std::swap;
    swap(op1.ps, op2.ps);
    swap(op1.size, op2.size);
}
 */

struct XRef {
    XRef(){

    }

    XRef(const XRef&) {
        std::cout << "const XRef&\n";
    }

    XRef(XRef&&) {
        std::cout << "XRef&&\n";
    }

    XRef& operator=(const XRef&) {
        std::cout << "operator=(const XRef&)\n";
        return *this;
    }

    ///*
    XRef& operator=(XRef&&) {
        std::cout << "operator=(XRef&&)\n";
        return *this;
    }
    // */

    void foo(const std::string& s) {
        std::cout << "const&" << s << "\n";
    }

    void foo(std::string&& s) {
        std::string s1 = std::move(s);
        std::cout << "&&" << s1 << "\n";
    }

    void foo(std::string& s) {
        std::cout << "&" << s << "\n";
    }

    void foo() const & {
        std::cout << "foo() &\n";
    }

    void foo() const && {
        std::cout << "foo() const\n";
    }

   // void foo() && {
    //    std::cout << "foo() &&\n";
    //}
};

class XB {};

void cppprimer_ch13::run() {

    std::vector<XB> vv;
    vv.push_back(XB());

    /*
    XRef x1;
    x1.foo();
    XRef().foo();
    std::move(x1).foo();
*/

    /*
    XRef x1;
    x1.foo("Alfa");
    x1.foo(std::string("Alfa2"));
    const std::string s1("Alfa3");
    x1.foo(s1);
    x1.foo(std::move(s1));
    */
    std::vector<std::string> svec = {"alpha", "beta", "gamma"};
    std::allocator<std::string> salloc;
    size_t siz = svec.size();
    auto pvec = salloc.allocate(siz);
    std::uninitialized_copy(std::make_move_iterator(svec.begin()), std::make_move_iterator(svec.end()), pvec);
    for (std::string* it = pvec; it != pvec+siz; ++it)
        std::cout << *it << ", ";

    /*
    XRef x1;
    XRef x2;

    x2 = x1;
    x2 = std::move(x1);
*/

    //DataPtr dp1;
    //DataPtr dp2;
    //dp1 = dp1;

    /*
    vec<std::string> vv;
    vv.push_back("alpha");
    vv.push_back("beta");
    for (size_t i = 0; i < vv.size(); ++i)
        std::cout << vv[i] << std::endl;
    vec<std::string> vv2 = vv;
    for (size_t i = 0; i < vv.size(); ++i)
        std::cout << vv[i] << std::endl;
     */

    // section 13.6
    /*
   // DataPtr dp1("test");
   // DataPtr dp2 = "Alpha";
    std::vector<DataPtr> dpv;
    for (int n = 0; n < 100; ++n) {
        std::ostringstream str;
        str << "as" << n;
        dpv.push_back(str.str());
    }
    DataPtr dp1("a");
    dpv.push_back(dp1);
    dpv.push_back(dp1);
    dpv.push_back(std::move(dp1));
    std::sort(dpv.begin(), dpv.end());
     */
}