/**
  @file     tuple_primal.h
  @brief    retains the instances of different types in the chain of inheritance.
  @author   HRYKY
  @version  $Id: tuple_primal.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TUPLE_PRIMAL_H_20131015232011639
#define TUPLE_PRIMAL_H_20131015232011639
#include "hryky/clear.h"
#include "hryky/tuple/tuple_at.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/tmp/tmp_list.h"
#include "hryky/tmp/null.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FirstT, typename RestT
#define hryky_template_arg \
	FirstT, RestT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retains multiple arbitrary values.
	template <
		typename FirstT = hryky::Null,
		typename RestT = hryky::Null >
	class Tuple;
	
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains multiple arbitrary values.
 */
template <hryky_template_param>
class hryky::Tuple :
	public RestT,
	public WithStreamOut<Tuple<hryky_template_arg> >,
	public WithSwap<Tuple<hryky_template_arg> >
{
public :
	typedef Tuple<hryky_template_arg>   this_type;
	typedef size_t                      size_type;
	typedef FirstT                      first_type;
	typedef RestT                       rest_type;
	
	typedef typename AsParameter<first_type>::type  first_param_type;

	static size_t const size_ = 1 + rest_type::size_;

	/// default constructor.
	Tuple();

	/// constructs with parameters.
	Tuple(first_param_type first, rest_type const & rest);

	/// constructs with other tuple.
	template <typename TupleT>
	Tuple(TupleT const & rhs);

	/// copy constructor.
	Tuple(this_type const & rhs);

	/// move constructor.
	Tuple(this_type && rhs);

	/// destructor.
	~Tuple();

	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assigns an other tuple having the same size.
	template <typename TupleT>
	this_type & operator=(TupleT const & rhs);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// outputs each element to stream.
	template <typename StreamT>
	StreamT & write_element_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// retrieves the value by index.
	template <size_t Index>
	typename hryky::TupleAt<this_type, Index>::type::first_param_type
		at() const;

	/// retrieves the mutable reference to the value by index.
	template <size_t Index>
	typename hryky::TupleAt<this_type, Index>::type::first_type &
		at();

	/// retrieves the first element of tuple.
	first_param_type first() const;

	/// retrieves the mutable reference to the first element of tuple.
	first_type & first();

	/// retrieves the rest elements of tuple.
	rest_type const & rest() const;

	/// retrieves the rest elements of tuple as mutable.
	rest_type & rest();

	/// retrieves the size of tuple.
	size_type size() const;

protected :

private :

	first_type  first_;

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
hryky::Tuple<hryky_template_arg>::Tuple()
	: rest_type()
	  , first_()
{
}
/**
  @brief constructs with parameters.
 */
template <hryky_template_param>
hryky::Tuple<hryky_template_arg>::Tuple(
	first_param_type first, rest_type const & rest)
	: rest_type(rest)
	  , first_(first)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Tuple<hryky_template_arg>::Tuple(this_type const & rhs)
	: rest_type(static_cast<rest_type const &>(rhs))
	  , hryky_copy_member(first)
{
}
/**
  @brief constructs with other tuple.
 */
template <hryky_template_param>
template <typename TupleT>
hryky::Tuple<hryky_template_arg>::Tuple(TupleT const & rhs)
	: rest_type(rhs.rest())
	  , first_(rhs.first())
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Tuple<hryky_template_arg>::Tuple(this_type && rhs)
	: rest_type(::std::move(rhs.rest()))
	  , hryky_move_member(first)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Tuple<hryky_template_arg>::~Tuple()
{
}
/**
  @brief assigns an other tuple having the same size.
 */
template <hryky_template_param>
template <typename TupleT>
hryky::Tuple<hryky_template_arg> & 
hryky::Tuple<hryky_template_arg>::operator=(
	TupleT const & rhs)
{
	this_type(rhs).swap(*this);
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Tuple<hryky_template_arg>::clear()
{
	hryky::clear(this->first_);
	this->rest_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Tuple<hryky_template_arg>::swap(this_type & src)
{
	this->rest_type::swap(src);
	hryky_swap_member(first);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Tuple<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::array::Scope<StreamT> const array(out);

	return this->write_element_to(out);
}
/**
  @brief stringifies elements of tuple.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::Tuple<hryky_template_arg>::write_element_to(
	StreamT & out) const
{
	out << this->first();
	return this->rest().write_element_to(out);
}
/**
  @brief retrieves the value by index.
 */
template <hryky_template_param>
template <size_t Index>
typename hryky::TupleAt<
	hryky::Tuple<hryky_template_arg>, Index>::type::first_param_type
hryky::Tuple<hryky_template_arg>::at() const
{
	return static_cast<
		typename TupleAt<this_type, Index>::type const *>(this)->first();
}
/**
  @brief retrieves the mutable reference to the value by index.
 */
template <hryky_template_param>
template <size_t Index>
typename hryky::TupleAt<
	hryky::Tuple<hryky_template_arg>, Index>::type::first_type & 
hryky::Tuple<hryky_template_arg>::at()
{
	return static_cast<
		typename TupleAt<this_type, Index>::type *>(this)->first();
}
/**
  @brief retrieves the first element of tuple.
 */
template <hryky_template_param>
typename hryky::Tuple<hryky_template_arg>::first_param_type 
hryky::Tuple<hryky_template_arg>::first() const
{
	return this->first_;
}
/**
  @brief retrieves the mutable reference to the first element of tuple.
 */
template <hryky_template_param>
typename hryky::Tuple<hryky_template_arg>::first_type & 
hryky::Tuple<hryky_template_arg>::first()
{
	return this->first_;
}
/**
  @brief retrieves the rest elements of tuple.
 */
template <hryky_template_param>
typename hryky::Tuple<hryky_template_arg>::rest_type const & 
hryky::Tuple<hryky_template_arg>::rest() const
{
	return *static_cast<rest_type const *>(this);
}
/**
  @brief retrieves the rest elements of tuple as mutable.
 */
template <hryky_template_param>
typename hryky::Tuple<hryky_template_arg>::rest_type & 
hryky::Tuple<hryky_template_arg>::rest()
{
	return *static_cast<rest_type *>(this);
}
/**
  @brief retrieves the size of tuple.
 */
template <hryky_template_param>
typename hryky::Tuple<hryky_template_arg>::size_type 
hryky::Tuple<hryky_template_arg>::size() const
{
	return this_type::size_;
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
// overload in std namespace
//------------------------------------------------------------------------------
namespace std
{
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TUPLE_PRIMAL_H_20131015232011639
// end of file

#include "hryky/tuple/tuple_terminal.h"

