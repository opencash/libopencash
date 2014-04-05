#include "opencash/api/ApiExceptions.h"

namespace opencash { namespace api {

  FileAlreadyExists::FileAlreadyExists(const std::string& fileName) :
    _fileName(fileName) { }

  const char* FileAlreadyExists::what() const throw () {
    return ("file already exists '" + _fileName + "'").c_str();
  }

}}
