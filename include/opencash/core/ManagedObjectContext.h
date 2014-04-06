#ifndef __OC_CORE_MANAGEDOBJECTCONTAINER_H_
#define __OC_CORE_MANAGEDOBJECTCONTAINER_H_

#include "ManagedObject.h"
#include "definitions.h"

#include <set>

namespace opencash { namespace core {
  class Account;
  class Transaction;
  class Split;

  class ManagedObjectContext {
    public:
      IMPORT_ALIAS(Account);
      IMPORT_ALIAS(Transaction);
      IMPORT_ALIAS(Split);
      using Uuid = ManagedObject::Uuid;

    public:
      AccountPtr createAccount();
      const Accounts getAllAccounts() const;

      TransactionPtr createTransaction();
      const Transactions getAllTransactions() const;

      SplitPtr createSplit();
      const Splits getAllSplits() const;

      bool hasUuid(const Uuid & uuid) const;

    protected:
      void assignUuid(ManagedObject & mobj);
      Uuid generateUuid() const;

    private:
      std::set<Uuid> _uuids;
      Accounts _accounts;
      Transactions _transactions;
      Splits _splits;
  };

}}

#endif
