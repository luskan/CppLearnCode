//
// Created by marci_000 on 24.06.2016.
//

#include "cppprimer_ch15.h"
#include "Query.h"
#include <iostream>


void cppprimer_ch15::run() {

  A<int> a;
  a.foo();

  std::ifstream file("C:\\Users\\marci_000\\ClionProjects\\TestCpp1\\test.txt");
  runTestMain(file);
  file.close();
}

