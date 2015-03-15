/**
  @file         type_info.h
  @brief        retains the information of type.
  @author       HRYKY
  @version      $Id: type_info.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef TYPE_INFO_H_20121216182814436
#define TYPE_INFO_H_20121216182814436
#include "hryky/type/type_common.h"
#include "hryky/type/type_id.h"
#include "hryky/type/type_name.h"
#include "hryky/literal_string.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
#pragma hryky_pragma_disable_warning_unthreadsafe_instance
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
	/// retains the information of type.
	class Info;

	typedef Info info_type;

} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains the information of type.
 */
class hryky::type::Info :
	public WithStreamOut<Info>,
	public WithSwap<Info>
{
public :

	typedef Info this_type;

	/// default constructor.
	Info();

	/// copy constructor.
	Info(this_type const &);

	/// move constructor.
	Info(this_type && rhs);

	/// constructor with parameters.
	Info(id_type const id, name_type const & name);

	/// destructor.
	~Info();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// compares each type.
	bool operator==(this_type const & rhs) const;

	/// compares whether both types are not equal.
	bool operator!=(this_type const & rhs) const;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the name of type.
	name_type const & name() const;

	/// retrieves the ID of type.
	id_type id() const;

protected :

private :

	static Info const instance;

	id_type     id_;
	name_type   name_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace type
{
} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename StreamT>
StreamT &
hryky::type::Info::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(id);
	hryky_write_member(name);
	
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
namespace type
{
	/// retrieves the arbitrary type::Info.
	template <typename ValueT>
	Info const & info(ValueT const &);

	/// retrieves the arbitrary type::Info by the template argument.
	template <typename ValueT>
	Info const & info();

} // namespace type
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the arbitrary type::Info.
 */
template <typename ValueT>
hryky::type::Info const &
hryky::type::info(ValueT const &)
{
	static Info const info(
		Id<ValueT>::value, Name<ValueT>::value);
	
	return info;
}
/**
  @brief retrieves the arbitrary type::Info by the template argument.
 */
template <typename ValueT>
hryky::type::Info const &
hryky::type::info()
{
	static Info const info(
		Id<ValueT>::value, Name<ValueT>::value);
	
	return info;
}
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // TYPE_INFO_H_20121216182814436
// end of file
