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

class MockOpenCashWriter : public OpenCashWriter {
  public:
    MOCK_CONST_METHOD2(write, void(const ManagedObjectContext&, const std::string&));
};

class MockApi : public Api {
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

    MockApi _mockApi;
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
  // given
  ASSERT_FALSE(Poco::File("test.opencash").exists());

  // when
  _realApi.createSampleFile("test.opencash");

  // then
  ASSERT_TRUE(Poco::File("test.opencash").exists());

  // cleanup
  Poco::File("test.opencash").remove();
}
