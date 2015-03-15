/**
  @file     shader_coder.h
  @brief    writes out the source to be compiled as shader.
  @author   HRYKY
  @version  $Id: shader_coder.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_CODER_H_20140820180731421
#define SHADER_CODER_H_20140820180731421
#include "hryky/shader/shader_with_code.h"
#include "hryky/stream/ostream_string.h"
#include "hryky/stream/stream_indent_begin.h"
#include "hryky/stream/stream_indent_end.h"
#include "hryky/tmp/tmp_not.h"
#include "hryky/tmp/tmp_or.h"
#include "hryky/type_traits/is_base_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/indenter.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// writes out the source to be compiled as shader.
	class Coder;

	class Node;
	class NodePtr;

namespace detail
{
	/// confirms whether the type can be written as it is.
	template <typename ValueT>
	class IsCodeAsIs;
} // namespace detail
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief writes out the source to be compiled as shader.
 */
class hryky::shader::Coder :
	public WithStreamOut<Coder>,
	public WithSwap<Coder>
{
public :

	typedef Coder this_type;

	/// default constructor.
	Coder();

	/// copy constructor.
	Coder(this_type const &);

	/// move constructor.
	Coder(this_type &&);

	/// destructor.
	~Coder();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// writes out a string.
	template <typename RhsT>
	this_type & operator<<(RhsT const & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// writes out a character.
	template <typename SrcT>
	void code_as_is(SrcT const & src);

protected :

private :
	typedef Indenter<ostream::String<String<> > > stream_type;

	stream_type stream_;
};
/**
  @brief confirms whether the type can be written as it is.
 */
template <typename ValueT>
class hryky::shader::detail::IsCodeAsIs
{
public :
	typedef typename IntegralConstantOf<
		tmp::Not<IsBaseOf<WithCode<ValueT>, ValueT> >
	>::type type;
	static typename type::value_type const value = type::value;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::shader::Coder::write_to(StreamT & out) const
{
	return this->stream_.write_to(out);
}
/**
  @brief writes out characters.
 */
template <typename SrcT>
void hryky::shader::Coder::code_as_is(SrcT const & src)
{
	this->stream_ << src;
}
/**
  @brief writes out an array of characters.
 */
template <typename RhsT>
hryky::shader::Coder &
hryky::shader::Coder::operator<<(RhsT const & rhs)
{
	return detail::code(*this, rhs);
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
namespace shader
{
namespace detail
{
	/// writes out the instance as code.
	template <typename RhsT>
	Coder & code(
		Coder & lhs,
		RhsT const & rhs,
		typename EnableIf<IsCodeAsIs<RhsT> >::type *
		= hryky_nullptr);

	/// writes out the instance by code() function.
	template <typename RhsT>
	Coder & code(
		Coder & lhs,
		RhsT const & rhs,
		typename DisableIf<IsCodeAsIs<RhsT> >::type *
		= hryky_nullptr);

} // namespace detail
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief writes out the instance as code.
 */
template <typename RhsT>
hryky::shader::Coder &
hryky::shader::detail::code(
	Coder & lhs,
	RhsT const & rhs,
	typename EnableIf<IsCodeAsIs<RhsT> >::type *)
{
	lhs.code_as_is(rhs);
	return lhs;
}
/**
  @brief writes out the instance by code() function.
 */
template <typename RhsT>
hryky::shader::Coder &
hryky::shader::detail::code(
	Coder & lhs,
	RhsT const & rhs,
	typename DisableIf<IsCodeAsIs<RhsT> >::type *)
{
	return rhs.code(lhs);
}
#endif // SHADER_CODER_H_20140820180731421
// end of file
