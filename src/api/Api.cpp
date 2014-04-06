#include "opencash/api/Api.h"
#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"
#include "opencash/core/Split.h"

#include <Poco/File.h>

namespace opencash { namespace api {
  IMPORT_ALIAS(ManagedObjectContext);

  Api::Api() {}
  Api::~Api() {}

  ManagedObjectContextPtr Api::createSampleManagedObjectContext() const {
    IMPORT_ALIAS(Account);
    IMPORT_ALIAS(Transaction);
    IMPORT_ALIAS(Split);

    ManagedObjectContextPtr moc(new ManagedObjectContext);

    AccountPtr rootAccount = moc->createAccount();
    rootAccount->setType(Account::AccountType::Root);
    rootAccount->setName("Root");
    rootAccount->setDescr("The root of all accounts");

    AccountPtr account1 = moc->createAccount();
    account1->setParent(rootAccount);
    account1->setType(Account::AccountType::Asset);
    account1->setName("Cash");
    account1->setDescr("Cash in my wallet");

    AccountPtr account2 = moc->createAccount();
    account2->setParent(rootAccount);
    account2->setType(Account::AccountType::Expense);
    account2->setName("Groceries");
    account2->setDescr("Household groceries");

    TransactionPtr transaction = moc->createTransaction();
    transaction->setDescription("Local market");

    SplitPtr split1 = moc->createSplit();
    split1->setTransaction(transaction);
    split1->setAccount(account1);
    split1->setValue(20);

    SplitPtr split2 = moc->createSplit();
    split2->setTransaction(transaction);
    split2->setAccount(account2);
    split2->setValue(-20);

    return moc;
  }

  void Api::createSampleFile(const std::string& outputFileName) const throw (FileAlreadyExists) {
    if (fileExists(outputFileName)) {
      throw FileAlreadyExists(outputFileName);
    }

    ManagedObjectContextPtr moc(createSampleManagedObjectContext());
    getOpenCashWriter().write(*moc, outputFileName);
  }

  bool Api::fileExists(const std::string& fileName) const {
    return Poco::File(fileName).exists();
  }

  const datastore::OpenCashWriter& Api::getOpenCashWriter() const {
    return _openCashWriter;
  }

}}
