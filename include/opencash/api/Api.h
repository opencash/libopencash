#ifndef __OC_API_API_H_
#define __OC_API_API_H_

#include "../core/definitions.h"
#include "../datastore/OpenCashWriter.h"
#include "ApiExceptions.h"

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
      virtual void createSampleFile(const std::string& outputFileName)
        const throw (FileAlreadyExists);

    protected:
      virtual bool fileExists(const std::string& fileName) const;
      virtual const datastore::OpenCashWriter& getOpenCashWriter() const;

    private:
      datastore::OpenCashWriter _openCashWriter;
  };

}}

#endif
