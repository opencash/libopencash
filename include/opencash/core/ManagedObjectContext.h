#ifndef __OC_CORE_MANAGEDOBJECTCONTAINER_H_
#define __OC_CORE_MANAGEDOBJECTCONTAINER_H_

#include "ManagedObject.h"
#include "definitions.h"

#include <set>

namespace opencash { namespace core {
  class Account;
  class Split;

  class ManagedObjectContext {
    public:
      IMPORT_ALIAS(Account);
      IMPORT_ALIAS(Split);
      using Uuid = ManagedObject::Uuid;

    public:
      AccountPtr createAccount();
      const Accounts getAllAccounts() const;

      SplitPtr createSplit();
      const Splits getAllSplits() const;

      bool hasUuid(const Uuid & uuid) const;

    protected:
      void assignUuid(ManagedObject & mobj);
      Uuid generateUuid() const;

    private:
      std::set<Uuid> _uuids;
      Accounts _accounts;
      Splits _splits;
  };

}}

#endif
