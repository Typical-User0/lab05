//! Mock test `Transaction` class

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mock.h"


/// Test `Transaction::Make()`
TEST(TransactionTest, Make) {
    MockTransaction transaction;

    // set fee
    EXPECT_CALL(transaction, set_fee(10));
    transaction.set_fee(10);

    EXPECT_CALL(transaction, fee()).WillOnce(testing::Return(10));

    EXPECT_EQ(transaction.fee(), 10);

    // make transaction
    MockAccount from(1, 200);
    MockAccount to(2, 100);

    EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 100)).WillOnce(testing::Return(true));

    EXPECT_TRUE(transaction.Make(from, to, 100));


    EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(100));
    EXPECT_EQ(from.GetBalance(), 100);

    EXPECT_CALL(to, GetBalance()).WillOnce(testing::Return(200));
    EXPECT_EQ(to.GetBalance(), 200);


}


/// Test `Transaction::Make()` with exception too small sum (sum < 100)
TEST(TransactionTest, MakeExceptionTooSmallSum) {
    MockTransaction transaction;

    MockAccount from(1, 200);
    MockAccount to(2, 100);

    EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 10)).WillOnce(testing::Throw(std::runtime_error("too small")));
    EXPECT_THROW(transaction.Make(from, to, 10), std::runtime_error);
}


/// Test `Transaction::Make()` when there is not enough money on the account (will return false)
TEST(TransactionTest, MakeNotEnoughMoney) {
    MockTransaction transaction;

    MockAccount from(1, 200);
    MockAccount to(2, 100);

    EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 300)).WillOnce(testing::Return(false));
    EXPECT_FALSE(transaction.Make(from, to, 300));
}


/// Test `Transaction::Make()` with exception of sum being negative
TEST(TransactionTest, MakeExceptionNegativeSum) {
    MockTransaction transaction;

    MockAccount from(1, 200);
    MockAccount to(2, 100);

    EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), -100)).WillOnce(testing::Throw(std::runtime_error("sum can't be negative")));
    EXPECT_THROW(transaction.Make(from, to, -100), std::runtime_error);
}


/// Test `Transaction::Make()` when sum < 2 * fee (will return false)
TEST(TransactionTest, MakeExceptionSumLessThanFee) {
    MockTransaction transaction;

    MockAccount from(1, 200);
    MockAccount to(2, 100);

    EXPECT_CALL(transaction, set_fee(10));
    transaction.set_fee(10);

    EXPECT_CALL(transaction, fee()).WillOnce(testing::Return(10));
    EXPECT_EQ(transaction.fee(), 10);

    EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 20)).WillOnce(testing::Return(false));
    EXPECT_FALSE(transaction.Make(from, to, 20));

}


/// Test `Transaction::set_fee()`
TEST(TransactionTest, SetFee) {
    MockTransaction transaction;
    EXPECT_CALL(transaction, set_fee(10));
    transaction.set_fee(10);
}

/// Test `Transaction::fee()`
TEST(TransactionTest, Fee) {
    MockTransaction transaction;
    EXPECT_CALL(transaction, fee()).WillOnce(testing::Return(10));
    EXPECT_EQ(transaction.fee(), 10);
}
