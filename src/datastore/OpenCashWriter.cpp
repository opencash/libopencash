#include "opencash/datastore/OpenCashWriter.h"
#include "opencash/core/ManagedObjectContext.h"

#include "opencash/core/Account.h"
#include "../core/generated/Account-odb.hxx"
#include "opencash/core/Transaction.h"
#include "../core/generated/Transaction-odb.hxx"
#include "opencash/core/Split.h"
#include "../core/generated/Split-odb.hxx"

#include <odb/database.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/schema-catalog.hxx>
#include <odb/transaction.hxx>

namespace opencash { namespace datastore {

  OpenCashWriter::OpenCashWriter() {}
  OpenCashWriter::~OpenCashWriter() {}

  void OpenCashWriter::write(const core::ManagedObjectContext& moc) const {
    // TODO: implement me
  }

  void OpenCashWriter::write(const core::ManagedObjectContext& moc,
      const std::string& fileName) const
  {
    IMPORT_ALIAS(Account);
    IMPORT_ALIAS(Transactions);
    IMPORT_ALIAS(Split);
    using namespace ::odb::core;

    std::unique_ptr<database> db
        (new odb::sqlite::database(fileName,
          SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

    {
      transaction tx(db->begin());
      schema_catalog::create_schema(*db);

      Accounts accounts = moc.getAllAccounts();
      for(auto it = accounts.begin(); it != accounts.end(); ++it) {
        db->persist(*it);
      }

      Transactions transactions = moc.getAllTransactions();
      for(auto it = transactions.begin(); it != transactions.end(); ++it) {
        db->persist(*it);
      }

      Splits splits = moc.getAllSplits();
      for(auto it = splits.begin(); it != splits.end(); ++it) {
        db->persist(*it);
      }

      tx.commit();
    }
  }

}}
