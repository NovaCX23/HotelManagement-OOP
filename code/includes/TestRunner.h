#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include "Hotel.h"
#include <string>
class TestRunner {

public:
    static void RunTestsFromFile(const std::string& filename, Hotel& hotel);
};

#endif //TESTRUNNER_H
