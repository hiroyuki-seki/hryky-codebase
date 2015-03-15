/**
  @file         bitfield.h
  @brief        initializes and clears bitfields.
  @author       HRYKY
  @version      $Id: bitfield.h 326 2014-02-11 06:30:44Z hryky.private@gmail.com $
 */
#ifndef BITFIELD_H_20130209161723345
#define BITFIELD_H_20130209161723345
#include "hryky/integer/unsigned_enough.h"
#include "hryky/clear.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename BitsT
#define hryky_template_arg \
	BitsT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// initializes and clears bitfields.
	template <hryky_template_param>
	class Bitfield;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief initializes and clears bitfields.
 */
template <hryky_template_param>
class hryky::Bitfield :
	public WithStreamOut<Bitfield<hryky_template_arg> >,
	public WithSwap<Bitfield<hryky_template_arg> >
{
public :

	typedef Bitfield<hryky_template_arg> this_type;

	/// default constructor.
	Bitfield();

	/// copy constructor.
	Bitfield(this_type const &);

	/// move constructor.
	Bitfield(this_type &&);

	/// destructor.
	~Bitfield();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the mutable bitfields.
	BitsT & bits();

	/// retrieves the immutable bitfields.
	BitsT const & bits() const;

protected :

private :

	typedef typename UnsignedEnoughBytes<sizeof(BitsT)>::type
		binary_type;

	union Value
	{
		typedef Value this_type;
		
		Value()
			: binary_()
		{
		}

		Value(this_type const & rhs)
			: hryky_copy_member(binary)
		{
		}
		
		Value(this_type && rhs)
			: hryky_move_member(binary)
		{
		}
		
		hryky_assign_op;

		/// move assignment operator.
		hryky_move_assign_op;
		
		void clear()
		{
			hryky::clear(this->binary_);
		}

		template <typename StreamT>
		StreamT & write_to(StreamT & out) const
		{
			stream::map::Scope<StreamT> const map(out);
			hryky_write_member(binary);
			return out;
		}

		void swap(this_type & src)
		{
			hryky_swap_member(binary);
		}
		
		binary_type binary_;
		BitsT bits_;
	} value_;

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
  @brief default constructor.
 */
template <hryky_template_param>
hryky::Bitfield<hryky_template_arg>::Bitfield()
{
	hryky::clear(this->value_);
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Bitfield<hryky_template_arg>::Bitfield(this_type const & rhs)
	: hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Bitfield<hryky_template_arg>::Bitfield(this_type && rhs)
	: hryky_move_member(value)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Bitfield<hryky_template_arg>::~Bitfield()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Bitfield<hryky_template_arg>::clear()
{
	hryky::clear(this->value_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Bitfield<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->value_.write_to(out);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Bitfield<hryky_template_arg>::swap(this_type & src)
{
	this->value_.swap(src.value_);
}
/**
  @brief retrieves the mutable bitfields.
 */
template <hryky_template_param>
BitsT & hryky::Bitfield<hryky_template_arg>::bits()
{
	return this->value_.bits_;
}
/**
  @brief retrieves the immutable bitfields.
 */
template <hryky_template_param>
BitsT const & hryky::Bitfield<hryky_template_arg>::bits() const
{
	return this->value_.bits_;
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

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // BITFIELD_H_20130209161723345
// end of file
