#ifndef __OC_API_APIEXCEPTIONS_H_
#define __OC_API_APIEXCEPTIONS_H_

#include <exception>
#include <string>

namespace opencash { namespace api {

  class ApiException : public std::exception {
    public:
      virtual const char* what () const throw () = 0;
  };

  class FileAlreadyExists : public ApiException {
    public:
      FileAlreadyExists(const std::string& fileName);
      virtual const char* what () const throw ();

    protected:
      const std::string& _fileName;
  };

}}

#endif
