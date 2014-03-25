#ifndef __OC_CORE_API_H_
#define __OC_CORE_API_H_

#include "definitions.h"

#include <string>

namespace opencash { namespace core {
  class ManagedObjectContext;
  IMPORT_ALIAS(ManagedObjectContext);

  class Api {
    public:
      Api();
      virtual ~Api();

      virtual ManagedObjectContextPtr createSampleManagedObjectContext() const;
      virtual void createSampleFile(const std::string& outputFileName) const;
  };

}}

#endif
