#include "opencash/core/Api.h"
#include "opencash/core/definitions.h"
#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

using Api = opencash::core::Api;
IMPORT_ALIAS(ManagedObjectContext);
IMPORT_ALIAS(Account);

class PartialMockApi : public Api {
  public:
    MOCK_CONST_METHOD0(createSampleManagedObjectContext, ManagedObjectContextPtr());
};

TEST(Api, shouldCreateSampleManagedObjectContext) {
  // given
  Api api;
  ManagedObjectContextPtr moc;

  // when
  moc = api.createSampleManagedObjectContext();

  // then
  Accounts accounts = moc->getAllAccounts();
  ASSERT_EQ(3, accounts.size());
  ASSERT_EQ(Account::AccountType::Root, accounts[0]->getType());
  ASSERT_EQ(accounts[0], accounts[1]->getParent());
  ASSERT_EQ(accounts[0], accounts[2]->getParent());
}

TEST(Api, shouldInvokeCreateSampleMocWhenCreateSampleFile) {
  // given
  PartialMockApi api;
  Api _proxy;

  // expect
  EXPECT_CALL(api, createSampleManagedObjectContext())
    .WillOnce(Invoke(&_proxy, &Api::createSampleManagedObjectContext));

  // when
  api.createSampleFile("test.opencash");
}
