/**
  @file     indenter.h
  @brief    inserts indents in stream.
  @author   HRYKY
  @version  $Id: indenter.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef INDENTER_H_20140825075616997
#define INDENTER_H_20140825075616997
#include "hryky/retention/retention_value.h"
#include "hryky/indent.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ImplT, template <typename> class RetainT, typename IndentT
#define hryky_template_arg \
	ImplT, RetainT, IndentT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// inserts indents in stream.
	template <
		typename ImplT,
		template <typename> class RetainT = retention::Value,
		typename IndentT = Indent<>
	>
	class Indenter;

	class Endl;

namespace stream
{
namespace indent
{
	class Begin;
	class End;
} // namespace indent
} // namespace stream

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief inserts indents in stream.
 */
template <hryky_template_param>
class hryky::Indenter :
	public RetainT<ImplT>,
	public WithStreamOut<Indenter<hryky_template_arg> >,
	public WithSwap<Indenter<hryky_template_arg> >
{
public :

	typedef Indenter<hryky_template_arg> this_type;
	typedef RetainT<ImplT> retain_type;

	/// default constructor.
	Indenter();

	/// copy constructor.
	Indenter(this_type const &);

	/// move constructor.
	Indenter(this_type &&);

	/// destructor.
	~Indenter();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// writes an arbitrary value through stream.
	template <typename RhsT>
	this_type & operator<<(RhsT const & rhs);

	/// specifies the beginning of indent.
	this_type & operator<<(stream::indent::Begin const &);

	/// specifies the end of indent.
	this_type & operator<<(stream::indent::End const &);

	/// breaks a line.
	this_type & operator<<(Endl const & rhs);

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	IndentT indent_;
	bool disabled_;

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
hryky::Indenter<hryky_template_arg>::Indenter()
	: retain_type()
	  , indent_()
	  , disabled_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Indenter<hryky_template_arg>::Indenter(
	this_type const & rhs)
	: retain_type(rhs)
	  , hryky_copy_member(indent)
	  , hryky_copy_member(disabled)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Indenter<hryky_template_arg>::Indenter(
	this_type && rhs)
	: retain_type(std::move(rhs))
	  , hryky_move_member(indent)
	  , hryky_move_member(disabled)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Indenter<hryky_template_arg>::~Indenter()
{
}
/**
  @brief writes an arbitrary value through stream.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::Indenter<hryky_template_arg> & 
hryky::Indenter<hryky_template_arg>::operator<<(
	RhsT const & rhs)
{
	ImplT & impl = *this->get();
	
	if (!this->disabled_) {
		impl << this->indent_;
		this->disabled_ = true;
	}
	impl << rhs;
	return *this;
}
/**
  @brief specifies the beginning of indent.
 */
template <hryky_template_param>
hryky::Indenter<hryky_template_arg> &
hryky::Indenter<hryky_template_arg>::operator<<(
	stream::indent::Begin const &)
{
	++this->indent_;
	return *this;
}
/**
  @brief specifies the end of indent.
 */
template <hryky_template_param>
hryky::Indenter<hryky_template_arg> &
hryky::Indenter<hryky_template_arg>::operator<<(
	stream::indent::End const &)
{
	--this->indent_;
	return *this;
}
/**
  @brief breaks a line.
 */
template <hryky_template_param>
hryky::Indenter<hryky_template_arg> &
hryky::Indenter<hryky_template_arg>::operator<<(
	Endl const & rhs)
{
	*this->get() << rhs;
	this->disabled_ = false;
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Indenter<hryky_template_arg>::clear()
{
	hryky::clear(this->indent_);
	hryky::clear(this->disabled_);
	this->retain_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Indenter<hryky_template_arg>::swap(this_type & src)
{
	this->retain_type::swap(src);
	hryky_swap_member(indent);
	hryky_swap_member(disabled);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Indenter<hryky_template_arg>::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(indent);
	hryky_write_member(disabled);
	out << stream::denote("impl");
	this->retain_type::write_to(out);
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // INDENTER_H_20140825075616997
// end of file
