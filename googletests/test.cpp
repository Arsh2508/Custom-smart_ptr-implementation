#include <gtest/gtest.h>
#include "ControlBlock.hpp"
#include "Shared_ptr.hpp"
#include "Unique_ptr.hpp"
#include "Weak_ptr.hpp"

TEST(UniquePointer, Value){
    Unique_ptr<int> unique(new int(5));

    EXPECT_EQ(*unique, 5);
}

TEST(Shared_ptr, Value){
    Shared_ptr<double> shared(new double(6));

    EXPECT_EQ(*shared, 6);
}