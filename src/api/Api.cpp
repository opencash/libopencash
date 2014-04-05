#include "opencash/api/Api.h"
#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"
#include "opencash/api/ApiExceptions.h"

#include <Poco/File.h>

namespace opencash { namespace api {
  IMPORT_ALIAS(Account);
  IMPORT_ALIAS(ManagedObjectContext);

  Api::Api() {}
  Api::~Api() {}

  ManagedObjectContextPtr Api::createSampleManagedObjectContext() const {
    ManagedObjectContextPtr moc(new ManagedObjectContext);

    AccountPtr rootAccount = moc->createAccount();
    rootAccount->setType(Account::AccountType::Root);

    for (int i = 0; i < 2; i++) {
      AccountPtr account = moc->createAccount();
      account->setParent(rootAccount);
    }
    return moc;
  }

  void Api::createSampleFile(const std::string& outputFileName) const {
    if (fileExists(outputFileName)) {
      throw FileAlreadyExists(outputFileName);
    }

    ManagedObjectContextPtr moc(createSampleManagedObjectContext());
    getOpenCashWriter().write(*moc);
  }

  bool Api::fileExists(const std::string& fileName) const {
    return Poco::File(fileName).exists();
  }

  const datastore::OpenCashWriter& Api::getOpenCashWriter() const {
    return _openCashWriter;
  }

}}
