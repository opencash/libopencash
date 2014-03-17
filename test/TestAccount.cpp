#include "opencash/core/Account.h"
#include "opencash/core/Split.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

IMPORT_ALIAS(Account);
IMPORT_ALIAS(Split);

using InSequence = ::testing::InSequence;

TEST(TestAccount, shouldAllowOneParent) {
  // given
  AccountPtr parentAcc(new Account());
  parentAcc->setName("parent");

  AccountPtr childAcc(new Account());
  childAcc->setName("child");

  // when
  childAcc->setParent(parentAcc);

  // then
  ASSERT_EQ(parentAcc, childAcc->getParent());
}

TEST(TestAccount, shouldAllowMultipleChildren) {
  // given
  AccountPtr parentAcc(new Account());
  parentAcc->setName("parent");

  AccountPtr childAcc1(new Account());
  childAcc1->setName("child1");

  AccountPtr childAcc2(new Account());
  childAcc2->setName("child2");

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);

  // then
  ASSERT_EQ(childAcc1, parentAcc->getChildren().at(0).lock());
  ASSERT_EQ(childAcc2, parentAcc->getChildren().at(1).lock());
  ASSERT_EQ(2, parentAcc->getChildren().size());
}

TEST(TestAccount, shouldRemoveChildFromParentWhenUnsettingParent) {
  // given
  AccountPtr parentAcc(new Account());
  parentAcc->setName("parent");

  AccountPtr childAcc1(new Account());
  childAcc1->setName("child1");

  AccountPtr childAcc2(new Account());
  childAcc2->setName("child2");

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);
  childAcc1->unsetParent();

  // then
  ASSERT_EQ(childAcc2, parentAcc->getChildren().at(0).lock());
  ASSERT_EQ(1, parentAcc->getChildren().size());
}

TEST(TestTransaction, shouldAddSplitIntoAccount) {
  //given
  AccountPtr account(new Account());
  SplitPtr split1(new Split());
  SplitPtr split2(new Split());

  //when
  account->addSplit(split1);
  account->addSplit(split2);

  //then
  const Splits& splits = account->getSplits();
  ASSERT_EQ(2, splits.size());
  ASSERT_EQ(split1, splits[0]);
  ASSERT_EQ(split2, splits[1]);
}

TEST(TestAccount, shouldNotTriggerParentChangedWhenSettingToSameParent) {
  // given
  AccountPtr parentAcc(new Account());
  AccountPtr parentAccRef(parentAcc);

  AccountPtr childAcc1(new Account());
  MockModelObserver childObs1(*childAcc1);

  {
    InSequence dummy;

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(childObs1, didChange("parent"));
  }

  // when
  childAcc1->setParent(parentAcc);
  childAcc1->setParent(parentAccRef);

  // then
  // mock expectations implicitly verified
}

TEST(TestAccount, shouldNotTriggerParentChangedWhenUnsettingParentIfAccountHasNoParent) {
  AccountPtr accountWithoutParent(new Account());
  MockModelObserver accountObserver(*accountWithoutParent);

  EXPECT_CALL(accountObserver, willChange("parent"))
		.Times(0);
  EXPECT_CALL(accountObserver, didChange("parent"))
		.Times(0);

  // when
  accountWithoutParent->unsetParent();

  // then
  // mock expectations implicitly verified
}
	
TEST(TestAccount, shouldTriggerMemberObserverEvents) {
  // given
  Account acc;
  MockModelObserver obs(acc);

  {
    InSequence dummy;

    EXPECT_CALL(obs, willChange("name"));
    EXPECT_CALL(obs, didChange("name"));

    EXPECT_CALL(obs, willChange("descr"));
    EXPECT_CALL(obs, didChange("descr"));

    EXPECT_CALL(obs, willChange("type"));
    EXPECT_CALL(obs, didChange("type"));
  }

  // when
  acc.setName("A name");
  acc.setDescr("A descr");
  acc.setType(Account::AccountType::Asset);

  // then
  // mock expectations implicitly verified
}

TEST(TestAccount, shouldTriggerParentChildrenObserverEvents) {
  // given
  AccountPtr parentAcc(new Account());
  MockModelObserver parentObs(*parentAcc);

  AccountPtr childAcc1(new Account());
  MockModelObserver childObs1(*childAcc1);

  AccountPtr childAcc2(new Account());
  MockModelObserver childObs2(*childAcc2);

  {
    using ChangeType = opencash::core::ObservableModel::ChangeType;

    InSequence dummy;

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 0, ChangeType::Insertion));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 0, ChangeType::Insertion));
    EXPECT_CALL(childObs1, didChange("parent"));

    EXPECT_CALL(childObs2, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 1, ChangeType::Insertion));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 1, ChangeType::Insertion));
    EXPECT_CALL(childObs2, didChange("parent"));

    EXPECT_CALL(childObs2, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 1, ChangeType::Removal));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 1, ChangeType::Removal));
    EXPECT_CALL(childObs2, didChange("parent"));

    EXPECT_CALL(childObs1, willChange("parent"));
    EXPECT_CALL(parentObs, willChangeAtIndex("children", 0, ChangeType::Removal));
    EXPECT_CALL(parentObs, didChangeAtIndex("children", 0, ChangeType::Removal));
    EXPECT_CALL(childObs1, didChange("parent"));
  }

  // when
  childAcc1->setParent(parentAcc);
  childAcc2->setParent(parentAcc);
  childAcc2->unsetParent();
  childAcc1->unsetParent();

  // then
  // mock expectations implicitly verified
}
