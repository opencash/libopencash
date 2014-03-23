#ifndef __OC_CORE_API_H_
#define __OC_CORE_API_H_

#include <string>

namespace opencash { namespace core {

  class Api {
    public:
      Api();
      virtual ~Api();

      virtual void createSampleFile(const std::string& outputFileName) const;
  };

}}

#endif
