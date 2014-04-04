#ifndef __OC_DATASTORE_WRITERINTERFACE_H_
#define __OC_DATASTORE_WRITERINTERFACE_H_

namespace opencash { namespace core {
  class ManagedObjectContext;
}}

namespace opencash { namespace datastore {

  class WriterInterface {
    public:
      virtual ~WriterInterface() {}

      virtual void write(const core::ManagedObjectContext& moc) const = 0;
  };

}}

#endif
