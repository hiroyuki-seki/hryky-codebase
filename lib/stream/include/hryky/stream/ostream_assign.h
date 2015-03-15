/**
  @file     ostream_assign.h
  @brief    assigns the LHS value through output stream.
  @author   HRYKY
  @version  $Id: ostream_assign.h 365 2014-07-13 07:58:50Z hryky.private@gmail.com $
 */
#ifndef OSTREAM_ASSIGN_H_20140712214035569
#define OSTREAM_ASSIGN_H_20140712214035569
#include "hryky/retention/retention_pointer.h"
#include "hryky/with_swap.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename OutputStreamT, template <typename> class RetainT
#define hryky_template_arg \
	OutputStreamT, RetainT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
	/// assigns the LHS value through output stream.
	template <
		typename OutputStreamT,
		template <typename> class RetainT = retention::Pointer
	>
	class Assign;

} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief assigns the LHS value through output stream.
 */
template <hryky_template_param>
class hryky::ostream::Assign :
	public RetainT<OutputStreamT>,
	public WithStreamOut<Assign<hryky_template_arg> >,
	public WithSwap<Assign<hryky_template_arg> >
{
public :

	typedef Assign<hryky_template_arg>      this_type;
	typedef RetainT<OutputStreamT>          retain_type;
	typedef typename retain_type::reference reference;

	/// default constructor.
	Assign();

	/// creates an instance with the retained value.
	Assign(reference src);

	/// copy constructor.
	Assign(this_type const &);

	/// move constructor.
	Assign(this_type &&);

	/// destructor.
	~Assign();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns an arbitrary value.
	template <typename RhsT>
	this_type & operator<<(RhsT const & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace ostream
{
} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::ostream::Assign<hryky_template_arg>::Assign()
	: retain_type()
{
}
/**
  @brief creates an instance with the retained value.
 */
template <hryky_template_param>
hryky::ostream::Assign<hryky_template_arg>::Assign(
	reference ref)
	: retain_type(ref)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::ostream::Assign<hryky_template_arg>::Assign(
	this_type const & rhs)
	: retain_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::ostream::Assign<hryky_template_arg>::Assign(
	this_type && rhs)
	: retain_type(::std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::ostream::Assign<hryky_template_arg>::~Assign()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::ostream::Assign<hryky_template_arg>::clear()
{
	this->retain_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::ostream::Assign<hryky_template_arg>::swap(
	this_type & src)
{
	this->retain_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::ostream::Assign<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return this->retain_type::write_to(out);
}
/**
  @brief assigns an arbitrary value.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::ostream::Assign<hryky_template_arg> & 
hryky::ostream::Assign<hryky_template_arg>::operator<<(
	RhsT const & rhs)
{
	pointer const ptr = this->get();
	if (!hryky_is_null(ptr)) {
		*ptr = rhs;
	}
	return *this;
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
namespace ostream
{
	/// creates an instance of Assign.
	template <typename OutputStreamT>
	Assign<OutputStreamT> assign(OutputStreamT & dest);

} // namespace ostream
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an instance of Assign.
 */
template <typename OutputStreamT>
hryky::ostream::Assign<OutputStreamT>
hryky::ostream::assign(OutputStreamT & dest)
{
	return Assign<OutputStreamT>(dest);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // OSTREAM_ASSIGN_H_20140712214035569
// end of file
