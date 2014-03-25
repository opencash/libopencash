#include "opencash/core/Transaction.h"
#include "opencash/core/Split.h"
#include "mock/MockModelObserver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

IMPORT_ALIAS(Transaction);
IMPORT_ALIAS(Split);

using namespace testing;

TEST(Transaction, shouldAddSplitIntoTransaction) {
  //given
  TransactionPtr transaction(new Transaction());
  SplitPtr split1(new Split());
  SplitPtr split2(new Split());

  //when
  transaction->addSplit(split1);
  transaction->addSplit(split2);

  //then
  const Splits& splits = transaction->getSplits();
  ASSERT_EQ(2, splits.size());
  ASSERT_EQ(split1, splits[0]);
  ASSERT_EQ(split2, splits[1]);
}

TEST(Transaction, shouldRemoveSplitFromTransaction) {
  //given
  TransactionPtr transaction(new Transaction());
  SplitPtr split1(new Split());
  SplitPtr split2(new Split());
  transaction->addSplit(split1);
  transaction->addSplit(split2);

  //when
  transaction->removeSplit(split2);

  //then
  const Splits& splits = transaction->getSplits();
  ASSERT_EQ(1, splits.size());
  ASSERT_EQ(split1, splits[0]);
  // ASSERT_EQ(split2, splits[1]);
}

TEST(Transaction, shouldSetTransactionInSplitWhenAddingSplit) {
  //given
  TransactionPtr transaction(new Transaction());
  SplitPtr split1(new Split());

  //when
  transaction->addSplit(split1);

  //then
  ASSERT_EQ(transaction, split1->getTransaction().lock());
}

TEST(Transaction, shouldTriggerMemberObserverEvents) {
  // given
  TransactionPtr transaction(new Transaction());
  SplitPtr split1(new Split());
  SplitPtr split2(new Split());
  MockModelObserver obs(*transaction);

  {
    InSequence dummy;

    EXPECT_CALL(obs, willChangeAtIndex("splits", 0, ObservableModel::ChangeType::Insertion));
    EXPECT_CALL(obs, didChangeAtIndex("splits", 0, ObservableModel::ChangeType::Insertion));

    EXPECT_CALL(obs, willChange("description"));
    EXPECT_CALL(obs, didChange("description"));

    EXPECT_CALL(obs, willChangeAtIndex("splits", 1, ObservableModel::ChangeType::Insertion));
    EXPECT_CALL(obs, didChangeAtIndex("splits", 1, ObservableModel::ChangeType::Insertion));

    EXPECT_CALL(obs, willChangeAtIndex("splits", 0, ObservableModel::ChangeType::Removal));
    EXPECT_CALL(obs, didChangeAtIndex("splits", 0, ObservableModel::ChangeType::Removal));
  }

  // when
  transaction->addSplit(split1);
  transaction->setDescription("desc");
  transaction->addSplit(split2);
  transaction->removeSplit(split1);

  // then
  // mock expectations implicitly verified
}

