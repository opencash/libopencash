#include "opencash/datastore/OpenCashWriter.h"
#include "opencash/core/ManagedObjectContext.h"
#include "opencash/core/Account.h"
#include "../core/generated/Account-odb.hxx"

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

    std::unique_ptr<odb::database> db
        (new odb::sqlite::database(fileName,
          SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE));

    odb::transaction tx(db->begin());
    odb::schema_catalog::create_schema(*db);

    Accounts accounts = moc.getAllAccounts();
    for(auto it = accounts.begin(); it != accounts.end(); ++it) {
      db->persist(*it);
    }

    tx.commit();
  }

}}
