#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"
#include "opencash/core/Split.h"

#include <gtest/gtest.h>

using ManagedObjectContext = opencash::core::ManagedObjectContext;

IMPORT_ALIAS(Account);
IMPORT_ALIAS(Split);


TEST(ManagedObjectContext, shouldCreateAccount) {
  // given
  ManagedObjectContext moc;

  // when
  AccountPtr account = moc.createAccount();

  // then
  ASSERT_TRUE(account != NULL);
  ASSERT_FALSE(account->getUuid().empty());
  ASSERT_TRUE(moc.hasUuid(account->getUuid()));
}

TEST(ManagedObjectContext, shouldGetAllAccounts) {
  // given
  ManagedObjectContext moc;
  moc.createAccount();
  moc.createAccount();

  // when
  Accounts accounts = moc.getAllAccounts();

  // then
  ASSERT_EQ(2, accounts.size());
}

TEST(ManagedObjectContext, shouldCreateSplit) {
  // given
  ManagedObjectContext moc;

  // when
  SplitPtr split = moc.createSplit();

  // then
  ASSERT_TRUE(split != NULL);
  ASSERT_FALSE(split->getUuid().empty());
  ASSERT_TRUE(moc.hasUuid(split->getUuid()));
}

TEST(ManagedObjectContext, shouldGetAllSplits) {
  // given
  ManagedObjectContext moc;
  moc.createSplit();
  moc.createSplit();

  // when
  Splits splits = moc.getAllSplits();

  // then
  ASSERT_EQ(2, splits.size());
}
