#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"
#include "opencash/core/Split.h"

#include <gtest/gtest.h>

using ManagedObjectContext = opencash::core::ManagedObjectContext;

IMPORT_ALIAS(Account);
IMPORT_ALIAS(Split);

class TestManagedObjectContext : public ::testing::Test {
  protected:
    ManagedObjectContext _moc;
};

TEST_F(TestManagedObjectContext, shouldCreateAccount) {
  // given

  // when
  AccountPtr account = _moc.createAccount();

  // then
  ASSERT_TRUE(account != NULL);
  ASSERT_FALSE(account->getUuid().empty());
  ASSERT_TRUE(_moc.hasUuid(account->getUuid()));
}

TEST_F(TestManagedObjectContext, shouldCreateSplit) {
  // given

  // when
  SplitPtr split = _moc.createSplit();

  // then
  ASSERT_TRUE(split != NULL);
  ASSERT_FALSE(split->getUuid().empty());
  ASSERT_TRUE(_moc.hasUuid(split->getUuid()));
}