#include "opencash/api/Api.h"
#include "opencash/datastore/OpenCashWriter.h"
#include "opencash/core/definitions.h"
#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

using Api = opencash::api::Api;
using OpenCashWriter = opencash::datastore::OpenCashWriter;
IMPORT_ALIAS(ManagedObjectContext);
IMPORT_ALIAS(Account);

class MockOpenCashWriter : public OpenCashWriter {
  public:
    MOCK_CONST_METHOD1(write, void(const ManagedObjectContext&));
};

class MockApi : public Api {
  public:
    MOCK_CONST_METHOD0(createSampleManagedObjectContext, ManagedObjectContextPtr());

  protected:
    virtual const OpenCashWriter& getOpenCashWriter() const override {
      return _mockOpenCashWriter;
    }

  public:
    MockOpenCashWriter _mockOpenCashWriter;
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
  MockApi api;
  ManagedObjectContextPtr mocPtr(new ManagedObjectContext());

  // expect
  EXPECT_CALL(api, createSampleManagedObjectContext())
    .WillOnce(Return(mocPtr));
  EXPECT_CALL(api._mockOpenCashWriter, write(Ref(*mocPtr)));

  // when
  api.createSampleFile("test.opencash");
}
