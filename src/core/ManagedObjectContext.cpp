#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"
#include "opencash/core/Split.h"

#include <poco/UUID.h>
#include <poco/UUIDGenerator.h>

namespace opencash { namespace core {

  IMPORT_ALIAS(Account);
  IMPORT_ALIAS(Split);
  using Uuid = ManagedObjectContext::Uuid;

  // public

  AccountPtr ManagedObjectContext::createAccount() {
    AccountPtr account(new Account);
    assignUuid(*account);
    _accounts.push_back(account);
    return account;
  }

  const Accounts ManagedObjectContext::getAllAccounts() const {
    return _accounts;
  }

  SplitPtr ManagedObjectContext::createSplit() {
    SplitPtr split(new Split);
    assignUuid(*split);
    _splits.push_back(split);
    return split;
  }

  const Splits ManagedObjectContext::getAllSplits() const {
    return _splits;
  }

  bool ManagedObjectContext::hasUuid(const Uuid & uuid) const {
    return _uuids.find(uuid) != _uuids.end();
  }

  // protected

  void ManagedObjectContext::assignUuid(ManagedObject & mobj) {
    Uuid uuid(generateUuid());
    mobj.setUuid(uuid);
    _uuids.insert(uuid);
  }

  Uuid ManagedObjectContext::generateUuid() const {
    return Poco::UUIDGenerator::defaultGenerator().createOne().toString();
  }

} }
