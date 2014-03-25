#include "opencash/core/Api.h"
#include "opencash/core/definitions.h"
#include "opencash/core/ManagedObjectContext.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

using Api = opencash::core::Api;
IMPORT_ALIAS(ManagedObjectContext);

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
  ASSERT_EQ(3, moc->getAllAccounts().size());
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
