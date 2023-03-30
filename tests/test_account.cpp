//! Mock test `Account` class

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mock.h"



/// Test `Account::GetBalance()`
TEST(AccountTest, GetBalance) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, GetBalance()).WillOnce(testing::Return(100));
    EXPECT_EQ(account.GetBalance(), 100);
}


/// Test `Account::ChangeBalance()`
/// Should throw exception because account is not locked
TEST(AccountTest, ChangeBalanceException) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, ChangeBalance(100)).WillOnce(testing::Throw(std::runtime_error("at first lock the account")));
    EXPECT_THROW(account.ChangeBalance(100), std::runtime_error);
}

/// Test `Account::ChangeBalance()`
/// But first lock the account
TEST(AccountTest, ChangeBalance) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, Lock());
    account.Lock();
    EXPECT_CALL(account, ChangeBalance(100));
    account.ChangeBalance(100);

    EXPECT_CALL(account, GetBalance()).WillOnce(testing::Return(200));
    EXPECT_EQ(account.GetBalance(), 200);
}


/// Test `Account::Lock()`
TEST(AccountTest, Lock) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, Lock());
    account.Lock();
}

/// Test throwing exception from `Account::Lock()` if account is already locked
TEST(AccountTest, LockException) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, Lock()).WillOnce(testing::Throw(std::runtime_error("already locked")));
    EXPECT_THROW(account.Lock(), std::runtime_error);
}

/// Test `Account::Unlock()`
TEST(AccountTest, Unlock) {
    MockAccount account(1, 100);
    EXPECT_CALL(account, Unlock());
    account.Unlock();
}

