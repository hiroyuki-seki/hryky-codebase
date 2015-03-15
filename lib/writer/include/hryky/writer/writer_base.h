/**
  @file         writer_base.h
  @brief        base class to write data polymorphically.
  @author       HRYKY
  @version      $Id: writer_base.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef WRITER_BASE_H_20130204182849436
#define WRITER_BASE_H_20130204182849436
#include "hryky/common.h"
#include "hryky/definition.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/without_new.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace writer
{
	/// base class to write data polymorphically.
	class Base;

} // namespace writer

typedef writer::Base writer_type;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class to write data polymorphically.
 */
class hryky::writer::Base :
	public WithStreamOut<Base>,
	public WithSwap<Base>,
	private WithoutNew
{
public :

	typedef Base this_type;

	/**
	  writes out an arbitrary data.
	 */
	virtual bool operator()(void const * data, size_t const size) = 0;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

	/// default constructor.
	Base();

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type &&);

	/// destructor.
	~Base();

	/// assignment operator.
	hryky_assign_op;

	/// releases the internal resources.
	void clear();

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace writer
{
} // namespace writer
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::writer::Base::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace writer
{
} // namespace writer
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // WRITER_BASE_H_20130204182849436
// end of file
