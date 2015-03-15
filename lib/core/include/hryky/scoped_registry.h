/**
  @file         scoped_registry.h
  @brief        enregisters a shared instance in the scope of the definition.
  @author       HRYKY
  @version      $Id: scoped_registry.h 359 2014-07-01 11:21:44Z hryky.private@gmail.com $
 */
#ifndef SCOPED_REGISTRY_H_20130212160225335
#define SCOPED_REGISTRY_H_20130212160225335
#include "hryky/common.h"
#include "hryky/definition.h"
#include "hryky/without_copy.h"
#include "hryky/without_new.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename Pointer
#define hryky_template_arg \
	ValueT, Pointer
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// enregisters a shared instance in the scope of the definition.
	template <typename ValueT, typename Pointer = ValueT *>
	class ScopedRegistry;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief enregisters a shared instance in the scope of the definition.
 */
template <hryky_template_param>
class hryky::ScopedRegistry :
	private WithoutCopy,
	private WithoutNew
{
public :

	typedef ScopedRegistry<hryky_template_arg> this_type;

	/// constructor with the shared instance.
	ScopedRegistry(Pointer instance);

	/// move constructor.
	ScopedRegistry(this_type && rhs);

	/// destructor.
	~ScopedRegistry();

	/// move assignment operator.
	hryky_move_assign_op;

	/// retrieves the current shared instance.
	static Pointer instance();

protected :

private :

	hryky_delete_default_constructor(ScopedRegistry);
	hryky_delete_this_copy_constructor(ScopedRegistry);
	hryky_delete_this_copy_assign_op(ScopedRegistry);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	static Pointer instance_;

	Pointer prev_;
	bool disable_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief constructor with the shared instance.
 */
template <hryky_template_param>
hryky::ScopedRegistry<hryky_template_arg>::ScopedRegistry(Pointer instance)
	: prev_(this_type::instance_)
	  , disable_()
{
	this_type::instance_ = instance;
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ScopedRegistry<hryky_template_arg>::ScopedRegistry(this_type && rhs)
	: hryky_move_member(prev)
	  , hryky_move_member(disable)
{
	rhs.disable_ = true;
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ScopedRegistry<hryky_template_arg>::~ScopedRegistry()
{
	if (!this->disable_) {
		this_type::instance_ = this->prev_;
	}
	this->disable_ = true;
}
/**
  @brief retrieves the current shared instance.
 */
template <hryky_template_param>
Pointer hryky::ScopedRegistry<hryky_template_arg>::instance()
{
	return this_type::instance_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
template <hryky_template_param>
Pointer hryky::ScopedRegistry<hryky_template_arg>::instance_ = Pointer();
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// facilitates the instantiation of ScopedRegistry.
	template <typename ValueT>
	ScopedRegistry<ValueT> scoped_registry(ValueT * const ptr);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief facilitates the instantiation of ScopedRegistry.
 */
template <typename ValueT>
hryky::ScopedRegistry<ValueT> hryky::scoped_registry(ValueT * const ptr)
{
	return ScopedRegistry<ValueT>(ptr);
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SCOPED_REGISTRY_H_20130212160225335
// end of file
