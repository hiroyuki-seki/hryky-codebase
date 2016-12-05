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
  @brief specialization of hryky::Tuple which has no value.
 */
template <>
class Tuple<hryky::Null, hryky::Null>  :
	public WithStreamOut<Tuple<hryky::Null, hryky::Null> >
{
public :

	typedef hryky::Tuple<>  this_type;
	typedef size_t          size_type;
	typedef hryky::Null     first_type;
	typedef hryky::Null     rest_type;

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

	/// retrieves the null as the first element.
	first_type first() const;

	/// retrieves the null as the rest elements.
	rest_type rest() const;

protected :

private :

};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines public member functions of Tuple<>
//------------------------------------------------------------------------------
/**
  @brief retrieves the null as the first element.
 */
inline
hryky::Tuple<hryky::Null, hryky::Null>::first_type 
hryky::Tuple<hryky::Null, hryky::Null>::first() const
{
	return first_type();
}
/**
  @brief retrieves the null as the rest elements.
 */
inline
hryky::Tuple<hryky::Null, hryky::Null>::rest_type 
hryky::Tuple<hryky::Null, hryky::Null>::rest() const
{
	return rest_type();
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
