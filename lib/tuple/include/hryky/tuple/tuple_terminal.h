/**
  @file     tuple_terminal.h
  @brief    terminates the inheritance of Tuple classes.
  @author   HRYKY
  @version  $Id: tuple_terminal.h 376 2014-07-29 10:46:52Z hryky.private@gmail.com $
 */
#ifndef TUPLE_TERMINAL_H_20131015231418634
#define TUPLE_TERMINAL_H_20131015231418634
#include "hryky/tmp/null.h"
#include "hryky/tuple/tuple_primal.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FirstT
#define hryky_template_arg \
	FirstT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief specialization of hryky::Tuple which has only one value.
 */
template <typename FirstT>
class Tuple<FirstT, hryky::Null > :
	public WithStreamOut<Tuple<FirstT, hryky::Null> >
{
public :

	typedef Tuple<FirstT>    this_type;
	typedef size_t                          size_type;
	typedef FirstT                          first_type;
	
	typedef typename AsParameter<first_type>::type first_param_type;

	static size_type const size_ = 1;

	/// default constructor.
	Tuple();

	/// constructs with a parameter.
	Tuple(first_param_type first);

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

	/// assigns other tuple having same size.
	template <typename TupleT>
	this_type & operator=(TupleT const & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// stringifies the terminal element.
	template <typename StreamT>
	StreamT & write_element_to(StreamT & out) const;

	/// retrieves the first element of tuple.
	first_param_type first() const;

	/// retrieves the mutable reference to the first element of tuple.
	first_type & first();

	/// retrieves the size of tuple.
	size_type size() const;

	/// retrieves the element in tuple.
	template <size_t Index>
	typename TupleAt<this_type, Index>::type::first_param_type
		at() const;

	/// retrieves the mutable reference to the value by index.
	template <size_t Index>
	typename TupleAt<this_type, Index>::type::first_type &
		at();

protected :

private :

	first_type  first_;

};
/**
  @brief specialization of hryky::Tuple which has no value.
 */
template <>
class Tuple<hryky::Null, hryky::Null>  :
	public WithStreamOut<Tuple<hryky::Null, hryky::Null> >
{
public :

	typedef hryky::Tuple<>  this_type;
	typedef size_t          size_type;

	static size_type const size_ = 0;

	/// default constructor.
	Tuple()
	{
	};

	/// copy constructor.
	Tuple(this_type const &)
	{
	}

	/// move constructor.
	Tuple(this_type &&)
	{
	}
	
	/// destructor.
	~Tuple()
	{
	};

	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear()
	{
	}

	/// interchanges the each internal resources of two instances.
	void swap(this_type &)
	{
	}

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		stream::array::Scope<StreamT> const array(out);
		return out;
	}

	/// retrieves the size of tuple.
	size_type size() const
	{
		return this_type::size_;
	}

	/// stringifies the terminal element.
	template <typename StreamT>
	StreamT & write_element_to(StreamT & out) const
	{
		return out;
	}

protected :

private :

};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions of Tuple<FirstT>
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <typename FirstT>
hryky::Tuple<FirstT>::Tuple()
	: first_()
{
}
/**
  @brief constructs with a parameter.
 */
template <typename FirstT>
hryky::Tuple<FirstT>::Tuple(first_param_type first)
	: first_(first)
{
}
/**
  @brief constructs with other tuple.
 */
template <typename FirstT>
template <typename TupleT>
hryky::Tuple<FirstT>::Tuple(TupleT const & rhs)
	: first_(rhs.first())
{
}
/**
  @brief copy constructor.
 */
template <typename FirstT>
hryky::Tuple<FirstT>::Tuple(this_type const & rhs)
	: hryky_copy_member(first)
{
}
/**
  @brief move constructor.
 */
template <typename FirstT>
hryky::Tuple<FirstT>::Tuple(this_type && rhs)
	: hryky_move_member(first)
{
}
/**
  @brief destructor.
 */
template <typename FirstT>
hryky::Tuple<FirstT>::~Tuple()
{
}
/**
  @brief assigns other tuple having same size.
 */
template <typename FirstT>
template <typename TupleT>
hryky::Tuple<FirstT> &
hryky::Tuple<FirstT>::operator=(TupleT const & rhs)
{
	this_type(rhs).swap(*this);
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <typename FirstT>
void hryky::Tuple<FirstT>::clear()
{
	hryky::clear(this->first_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <typename FirstT>
void hryky::Tuple<FirstT>::swap(this_type & src)
{
	hryky_swap_member(first);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <typename FirstT>
template <typename StreamT>
StreamT &
hryky::Tuple<FirstT>::write_to(
	StreamT & out) const
{
	stream::array::Scope<StreamT> const array(out);

	return this->write_element_to(out);
}
/**
  @brief stringifies the terminal element.
 */
template <typename FirstT>
template <typename StreamT>
StreamT &
hryky::Tuple<FirstT>::write_element_to(
	StreamT & out) const
{
	out << this->first();
	return out;
}
/**
  @brief retrieves the first element of tuple.
 */
template <typename FirstT>
typename hryky::Tuple<FirstT>::first_param_type 
hryky::Tuple<FirstT>::first() const
{
	return this->first_;
}
/**
  @brief retrieves the mutable reference to the first element of tuple.
 */
template <typename FirstT>
typename hryky::Tuple<FirstT>::first_type &
hryky::Tuple<FirstT>::first()
{
	return this->first_;
}
/**
  @brief retrieves the size of tuple.
 */
template <typename FirstT>
typename hryky::Tuple<FirstT>::size_type 
hryky::Tuple<FirstT>::size() const
{
	return this_type::size_;
}
/**
  @brief retrieves the element in tuple.
 */
template <typename FirstT>
template <size_t Index>
typename hryky::TupleAt<
	hryky::Tuple<FirstT>, Index>::type::first_param_type 
hryky::Tuple<FirstT>::at() const
{
	return static_cast<
		TupleAt<this_type, Index>::type const *>(this)->first();
}
/**
  @brief retrieves the mutable reference to the value by index.
 */
template <typename FirstT>
template <size_t Index>
typename hryky::TupleAt<
	hryky::Tuple<FirstT>, Index>::type::first_type & 
hryky::Tuple<FirstT>::at()
{
	return static_cast<
		TupleAt<this_type, Index>::type *>(this)->first();
}
//------------------------------------------------------------------------------
// defines public member functions of Tuple<>
//------------------------------------------------------------------------------
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
	/// creates an empty tuple.
	Tuple<> make_tuple();

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an empty tuple.
 */
inline hryky::Tuple<> hryky::make_tuple()
{
	return Tuple<>();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // TUPLE_TERMINAL_H_20131015231418634
// end of file
