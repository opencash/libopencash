// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef SPLIT_ODB_HXX
#define SPLIT_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20300UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include <opencash/core/Split.h>

#include "Account-odb.hxx"
#include "ManagedObject-odb.hxx"
#include "Transaction-odb.hxx"

#include <memory>
#include <cstddef>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/session.hxx>
#include <odb/cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/simple-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // Split
  //
  template <>
  struct class_traits< ::opencash::core::Split >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::opencash::core::Split >
  {
    public:
    typedef ::opencash::core::Split object_type;
    typedef ::std::shared_ptr< ::opencash::core::Split > pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef object_traits< ::opencash::core::ManagedObject >::id_type id_type;

    static const bool auto_id = object_traits< ::opencash::core::ManagedObject >::auto_id;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    odb::pointer_cache_traits<
      pointer_type,
      odb::session >
    pointer_cache_traits;

    typedef
    odb::reference_cache_traits<
      object_type,
      odb::session >
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/binding.hxx>
#include <odb/sqlite/sqlite-types.hxx>
#include <odb/sqlite/query.hxx>

namespace odb
{
  // Split
  //
  template <typename A>
  struct pointer_query_columns< ::opencash::core::Split, id_sqlite, A >:
    pointer_query_columns< ::opencash::core::ManagedObject, id_sqlite, A >
  {
    // ManagedObject
    //
    typedef pointer_query_columns< ::opencash::core::ManagedObject, id_sqlite, A > ManagedObject;

    // transaction
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::opencash::core::ManagedObject::Uuid,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    transaction_type_;

    static const transaction_type_ transaction;

    // account
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::opencash::core::ManagedObject::Uuid,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    account_type_;

    static const account_type_ account;

    // memo
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    memo_type_;

    static const memo_type_ memo;

    // action
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    action_type_;

    static const action_type_ action;

    // value
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        double,
        sqlite::id_real >::query_type,
      sqlite::id_real >
    value_type_;

    static const value_type_ value;
  };

  template <typename A>
  const typename pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::transaction_type_
  pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::
  transaction (A::table_name, "\"transaction\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::account_type_
  pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::
  account (A::table_name, "\"account\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::memo_type_
  pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::
  memo (A::table_name, "\"memo\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::action_type_
  pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::
  action (A::table_name, "\"action\"", 0);

  template <typename A>
  const typename pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::value_type_
  pointer_query_columns< ::opencash::core::Split, id_sqlite, A >::
  value (A::table_name, "\"value\"", 0);

  template <>
  class access::object_traits_impl< ::opencash::core::Split, id_sqlite >:
    public access::object_traits< ::opencash::core::Split >
  {
    public:
    typedef object_traits_impl< ::opencash::core::ManagedObject, id_sqlite >::id_image_type id_image_type;

    struct image_type: object_traits_impl< ::opencash::core::ManagedObject, id_sqlite >::image_type
    {
      // _transaction
      //
      details::buffer _transaction_value;
      std::size_t _transaction_size;
      bool _transaction_null;

      // _account
      //
      details::buffer _account_value;
      std::size_t _account_size;
      bool _account_null;

      // _memo
      //
      details::buffer _memo_value;
      std::size_t _memo_size;
      bool _memo_null;

      // _action
      //
      details::buffer _action_value;
      std::size_t _action_size;
      bool _action_null;

      // _value
      //
      double _value_value;
      bool _value_null;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    struct transaction_tag;
    struct account_tag;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (sqlite::bind*,
          image_type&,
          sqlite::statement_kind);

    static void
    bind (sqlite::bind*, id_image_type&);

    static bool
    init (image_type&,
          const object_type&,
          sqlite::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef sqlite::object_statements<object_type> statements_type;

    typedef sqlite::query_base query_base_type;

    static const std::size_t column_count = 6UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  template <>
  class access::object_traits_impl< ::opencash::core::Split, id_common >:
    public access::object_traits_impl< ::opencash::core::Split, id_sqlite >
  {
  };

  // Split
  //
  template <>
  struct alias_traits<
    ::opencash::core::Transaction,
    id_sqlite,
    access::object_traits_impl< ::opencash::core::Split, id_sqlite >::transaction_tag>
  {
    static const char table_name[];
  };

  template <>
  struct alias_traits<
    ::opencash::core::Account,
    id_sqlite,
    access::object_traits_impl< ::opencash::core::Split, id_sqlite >::account_tag>
  {
    static const char table_name[];
  };

  template <>
  struct query_columns_base< ::opencash::core::Split, id_sqlite >
  {
    // transaction
    //
    typedef
    odb::alias_traits<
      ::opencash::core::Transaction,
      id_sqlite,
      access::object_traits_impl< ::opencash::core::Split, id_sqlite >::transaction_tag>
    transaction_alias_;

    // account
    //
    typedef
    odb::alias_traits<
      ::opencash::core::Account,
      id_sqlite,
      access::object_traits_impl< ::opencash::core::Split, id_sqlite >::account_tag>
    account_alias_;
  };

  template <typename A>
  struct query_columns< ::opencash::core::Split, id_sqlite, A >:
    query_columns_base< ::opencash::core::Split, id_sqlite >,
    query_columns< ::opencash::core::ManagedObject, id_sqlite, A >
  {
    // ManagedObject
    //
    typedef query_columns< ::opencash::core::ManagedObject, id_sqlite, A > ManagedObject;

    // transaction
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::opencash::core::ManagedObject::Uuid,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    transaction_column_type_;

    typedef
    odb::query_pointer<
      odb::pointer_query_columns<
        ::opencash::core::Transaction,
        id_sqlite,
        transaction_alias_ > >
    transaction_pointer_type_;

    struct transaction_type_: transaction_pointer_type_, transaction_column_type_
    {
      transaction_type_ (const char* t, const char* c, const char* conv)
        : transaction_column_type_ (t, c, conv)
      {
      }
    };

    static const transaction_type_ transaction;

    // account
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::opencash::core::ManagedObject::Uuid,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    account_column_type_;

    typedef
    odb::query_pointer<
      odb::pointer_query_columns<
        ::opencash::core::Account,
        id_sqlite,
        account_alias_ > >
    account_pointer_type_;

    struct account_type_: account_pointer_type_, account_column_type_
    {
      account_type_ (const char* t, const char* c, const char* conv)
        : account_column_type_ (t, c, conv)
      {
      }
    };

    static const account_type_ account;

    // memo
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    memo_type_;

    static const memo_type_ memo;

    // action
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    action_type_;

    static const action_type_ action;

    // value
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        double,
        sqlite::id_real >::query_type,
      sqlite::id_real >
    value_type_;

    static const value_type_ value;
  };

  template <typename A>
  const typename query_columns< ::opencash::core::Split, id_sqlite, A >::transaction_type_
  query_columns< ::opencash::core::Split, id_sqlite, A >::
  transaction (A::table_name, "\"transaction\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::core::Split, id_sqlite, A >::account_type_
  query_columns< ::opencash::core::Split, id_sqlite, A >::
  account (A::table_name, "\"account\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::core::Split, id_sqlite, A >::memo_type_
  query_columns< ::opencash::core::Split, id_sqlite, A >::
  memo (A::table_name, "\"memo\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::core::Split, id_sqlite, A >::action_type_
  query_columns< ::opencash::core::Split, id_sqlite, A >::
  action (A::table_name, "\"action\"", 0);

  template <typename A>
  const typename query_columns< ::opencash::core::Split, id_sqlite, A >::value_type_
  query_columns< ::opencash::core::Split, id_sqlite, A >::
  value (A::table_name, "\"value\"", 0);
}

#include <Split-odb.ixx>

#include <odb/post.hxx>

#endif // SPLIT_ODB_HXX
