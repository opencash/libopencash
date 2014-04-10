#include "opencash/api/Api.h"
#include "opencash/api/ApiExceptions.h"
#include "opencash/datastore/OpenCashWriter.h"
#include "opencash/core/definitions.h"
#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"

#include <Poco/File.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

using Api = opencash::api::Api;
using OpenCashWriter = opencash::datastore::OpenCashWriter;
IMPORT_ALIAS(ManagedObjectContext);
IMPORT_ALIAS(Account);
IMPORT_ALIAS(Transaction);
IMPORT_ALIAS(Split);

class MockOpenCashWriter : public OpenCashWriter {
  public:
    MOCK_CONST_METHOD2(write, void(const ManagedObjectContext&, const std::string&));
};

class PartialMockApi : public Api {
  public:
    MOCK_CONST_METHOD0(createSampleManagedObjectContext, ManagedObjectContextPtr());
    MOCK_CONST_METHOD1(fileExists, bool(const std::string&));

  protected:
    virtual const OpenCashWriter& getOpenCashWriter() const override {
      return _mockOpenCashWriter;
    }

  public:
    MockOpenCashWriter _mockOpenCashWriter;
};

class ApiTest : public ::testing::Test {
  protected:
    ApiTest() {
      ON_CALL(_mockApi, createSampleManagedObjectContext())
        .WillByDefault(Invoke(&_realApi, &Api::createSampleManagedObjectContext));
    }

    PartialMockApi _mockApi;
    Api _realApi;
};

TEST_F(ApiTest, shouldCreateSampleManagedObjectContext) {
  // when
  ManagedObjectContextPtr moc = _realApi.createSampleManagedObjectContext();

  // then
  Accounts accounts = moc->getAllAccounts();
  EXPECT_EQ(3, accounts.size());
  EXPECT_EQ(Account::AccountType::Root, accounts[0]->getType());
  EXPECT_EQ(accounts[0], accounts[1]->getParent());
  EXPECT_EQ(accounts[0], accounts[2]->getParent());

  Transactions transactions = moc->getAllTransactions();
  EXPECT_EQ(1, transactions.size());

  Splits splits = moc->getAllSplits();
  EXPECT_EQ(2, splits.size());
}

TEST_F(ApiTest, createSampleFileShouldInvokeCreateSampleManagedObjectContext) {
  // given
  ManagedObjectContextPtr mocPtr(new ManagedObjectContext());

  // expect
  EXPECT_CALL(_mockApi, createSampleManagedObjectContext())
    .WillOnce(Return(mocPtr));
  EXPECT_CALL(_mockApi, fileExists(_)).WillRepeatedly(Return(false));
  EXPECT_CALL(_mockApi._mockOpenCashWriter, write(Ref(*mocPtr), "test.opencash"));

  // when
  _mockApi.createSampleFile("test.opencash");
}

TEST_F(ApiTest, createSampleFileShouldThrowWhenFileExists) {
  // given
  EXPECT_CALL(_mockApi, fileExists(_)).WillOnce(Return(true));

  // then
  EXPECT_THROW(_mockApi.createSampleFile("test.opencash"),
      opencash::api::FileAlreadyExists);
}

TEST_F(ApiTest, createSampleFileShouldCreateAFile) {
  // prepare
  Poco::File f("test.opencash");
  if (f.exists()) f.remove();

  // given
  ASSERT_FALSE(f.exists());

  // when
  _realApi.createSampleFile("test.opencash");

  // then
  ASSERT_TRUE(f.exists());
}
