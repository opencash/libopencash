#include "opencash/core/Api.h"
#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"

namespace opencash { namespace core {
  IMPORT_ALIAS(Account);

  Api::Api() {}
  Api::~Api() {}

  ManagedObjectContextPtr Api::createSampleManagedObjectContext() const {
    ManagedObjectContextPtr moc(new ManagedObjectContext);
    for (int i = 0; i < 3; i++) {
      moc->createAccount();
    }
    return moc;
  }

  void Api::createSampleFile(const std::string& outputFileName) const {
    ManagedObjectContextPtr moc(createSampleManagedObjectContext());
  }

} }
