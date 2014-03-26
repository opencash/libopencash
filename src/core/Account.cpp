#include "opencash/core/Account.h"
#include "opencash/core/Split.h"

namespace opencash { namespace core {

  IMPORT_ALIAS(Account);

  IMPL_COMPARATORS(Account);

  Account::Account() {
    _type = AccountType::None;
  }

  std::string Account::getName() const
  {
    return _name;
  }

  void Account::setName(std::string name)
  {
    willChange("name");
    _name = name;
    didChange("name");
  }

  std::string Account::getDescr() const
  {
    return _descr;
  }

  void Account::setDescr(std::string descr)
  {
    willChange("descr");
    _descr = descr;
    didChange("descr");
  }

  Account::AccountType Account::getType() const
  {
    return _type;
  }

  void Account::setType(Account::AccountType type)
  {
    willChange("type");
    _type = type;
    didChange("type");
  }

  AccountPtr Account::getParent() const
  {
    return _parent;
  }

  void Account::unregisterFromCurrentParent()
  {
	  if (_parent) {
		  auto index = std::numeric_limits<std::size_t>::max();

		  WeakAccounts & children = _parent->_children;
		  auto child = std::find_if(children.begin(), children.end(),
				  [this](AccountWeakPtr item) {
				  return (item.lock().get() == this);
				  });
		  if (child != children.end()) {
			  index = distance(children.begin(), child);

			  _parent->willChangeAtIndex("children", index, ChangeType::Removal);
			  children.erase(child);
			  _parent->didChangeAtIndex("children", index, ChangeType::Removal);
		  }
	  }
  }

  void Account::unsetParent()
  {
	if (!_parent) { return; }

	willChange("parent");

	unregisterFromCurrentParent();

	didChange("parent");
  }

  void Account::registerWithParent(AccountPtr parent)
  {
	  if (parent)
	  {
		  auto index = parent->_children.size();

		  parent->willChangeAtIndex("children", index, ChangeType::Insertion);
		  parent->_children.push_back(shared_from_this());
		  parent->didChangeAtIndex("children", index, ChangeType::Insertion);
	  }

	  _parent = parent;
  }

  void Account::setParent(AccountPtr parent)
  {
	  if (parent == _parent) { return; }

	  willChange("parent");

	  unregisterFromCurrentParent();
	  registerWithParent(parent);

	  didChange("parent");
  }

  const WeakAccounts & Account::getChildren() const
  {
    return _children;
  }

  void Account::addSplit(SplitPtr split) {
    auto it = std::find(_splits.begin(), _splits.end(), split);

    if(it == _splits.end()) {
      size_t index = _splits.size();

      willChangeAtIndex("splits", index, ChangeType::Insertion);
      _splits.push_back(split);
      didChangeAtIndex("splits", index, ChangeType::Insertion);

      split->setAccount(shared_from_this());
    }
  }

  void Account::removeSplit(SplitPtr split) {
    auto it = std::find(_splits.begin(), _splits.end(), split);

    if(it != _splits.end()) {
      size_t index = std::distance(_splits.begin(), it);

      willChangeAtIndex("splits", index, ChangeType::Removal);
      _splits.erase(it);
      didChangeAtIndex("splits", index, ChangeType::Removal);

      if(split)
        split->setAccount(AccountPtr());
    }
  }

  const Splits& Account::getSplits() const {
    return _splits;
  }
}}
