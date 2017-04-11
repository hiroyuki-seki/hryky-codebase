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
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retains multiple arbitrary values.
	template <typename DerivedT>
	class Tuple;
	
namespace tuple
{
namespace detail
{
	
} // namespace detail
} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains multiple arbitrary values.
 */
template <
	typename DerivedT
>
class hryky::Tuple :
	public WithStreamOut<Tuple<hryky_template_arg> >,
	public WithSwap<Tuple<hryky_template_arg> >
{
public :
	typedef Tuple<hryky_template_arg>   this_type;
	typedef size_t                      size_type;
	
	/// retrieves the value by index.
	template <size_t Index>
	typename AsParameter<
		typename hryky::tuple::At<DerivedT, Index>::type::first_type>::type
		at() const;

	/// retrieves the mutable reference to the value by index.
	template <size_t Index>
	typename hryky::tuple::At<DerivedT, Index>::type::first_type &
		at();

	template <typename StreamT>
	StreamT & write_to(StreamT & out) const
	{
		return static_cast<DerivedT const *>(this)->write_to(out);
	}

protected :
	
	Tuple()
	{
	}

private :

	template <size_t Index, typename DummyT = Null>
	class At
	{
	};
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace tuple
{
namespace detail
{
} // namespace detail
template <typename DerivedT>
template <typename DummyT>
class Tuple<DerivedT>::At<0, DummyT>
{
	friend class Tuple<DerivedT>;
	
	static typename AsParameter<
		typename tuple::At<DerivedT, 0>::type::first_type>::type
			arg(DerivedT const & derived)
	{
		return derived.arg1_;
	}
	static typename tuple::At<DerivedT, 0>::type::first_type &
		arg(DerivedT & derived)
	{
		return derived.arg1_;
	}
};
template <typename DerivedT>
template <typename DummyT>
class Tuple<DerivedT>::At<1, DummyT>
{
	friend class Tuple<DerivedT>;
	
	static typename AsParameter<
		typename tuple::At<DerivedT, 1>::type::first_type>::type
			arg(DerivedT const & derived)
	{
		return derived.arg2_;
	}
	static typename tuple::At<DerivedT, 1>::type::first_type &
		arg(DerivedT & derived)
	{
		return derived.arg2_;
	}
};
template <typename DerivedT>
template <typename DummyT>
class Tuple<DerivedT>::At<2, DummyT>
{
	friend class Tuple<DerivedT>;
	
	static typename AsParameter<
		typename tuple::At<DerivedT, 2>::type::first_type>::type
			arg(DerivedT const & derived)
	{
		return derived.arg3_;
	}
	static typename tuple::At<DerivedT, 2>::type::first_type &
		arg(DerivedT & derived)
	{
		return derived.arg3_;
	}
};
} // namespace tuple
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the value by index.
 */
template <hryky_template_param>
template <size_t Index>
typename hryky::AsParameter<
	typename hryky::tuple::At<DerivedT, Index>::type::first_type>::type
hryky::Tuple<hryky_template_arg>::at() const
{
	return At<Index>::arg(static_cast<DerivedT const &>(*this));
}
/**
  @brief retrieves the mutable reference to the value by index.
 */
template <hryky_template_param>
template <size_t Index>
typename hryky::tuple::At<DerivedT, Index>::type::first_type & 
hryky::Tuple<hryky_template_arg>::at()
{
	return At<Index>::arg(static_cast<DerivedT &>(*this));
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

