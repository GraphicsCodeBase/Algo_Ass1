#include <gtest/gtest.h>
#include <iostream>
#include <chrono>
#include "../src/algo.hpp"

//the class will inhherit from the test framework of GTest.
class AlgoTest : public ::testing::Test{

protected :
    Algo algo;

    void SetUp() override
    {
        // This runs before each test
        //this will set every station to not faulty.(false)
        //algo.initialize_stations();
    }

     void TearDown() override {
        // This runs after each test (optional here)
        //thinking if i need to call the desctructor or not.
    }
};

