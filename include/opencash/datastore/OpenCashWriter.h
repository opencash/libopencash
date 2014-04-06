#ifndef __OC_DATASTORE_OPENCASHWRITER_H_
#define __OC_DATASTORE_OPENCASHWRITER_H_

#include "WriterInterface.h"

#include <string>

namespace opencash { namespace core {
  class ManagedObjectContext;
}}

namespace opencash { namespace datastore {

  class OpenCashWriter : public WriterInterface {
    public:
      OpenCashWriter();
      virtual ~OpenCashWriter();

      virtual void write(const core::ManagedObjectContext& moc) const override;
      virtual void write(const core::ManagedObjectContext& moc,
          const std::string& fileName) const;
  };

}}

#endif
