#ifndef __OC_API_API_H_
#define __OC_API_API_H_

#include "../core/definitions.h"
#include "../datastore/OpenCashWriter.h"

#include <string>

namespace opencash { namespace core {
  class ManagedObjectContext;
  IMPORT_ALIAS(ManagedObjectContext);
}}

namespace opencash { namespace api {

  class Api {
    public:
      Api();
      virtual ~Api();

      virtual core::ManagedObjectContextPtr createSampleManagedObjectContext() const;
      virtual void createSampleFile(const std::string& outputFileName) const;

    protected:
      virtual const datastore::OpenCashWriter& getOpenCashWriter() const;

    private:
      datastore::OpenCashWriter _openCashWriter;
  };

}}

#endif
