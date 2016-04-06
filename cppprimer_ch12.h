//
// Created by marci_000 on 17.03.2016.
//

#ifndef TESTCPP1_CPPPRIMER_CH12_H
#define TESTCPP1_CPPPRIMER_CH12_H

#include <memory>

class PimplTestImpl;

class PimplTest {

    PimplTest();

    // Cannot be declared and defined here as it will use unique_ptr destructor which requires sizeof PimplTestImpl to be defined.
    //~PimplTest(){}

    ~PimplTest();

private:
    std::unique_ptr<PimplTestImpl> pimpl;
};

class cppprimer_ch12 {
public:
    void run();
};


#endif //TESTCPP1_CPPPRIMER_CH12_H
