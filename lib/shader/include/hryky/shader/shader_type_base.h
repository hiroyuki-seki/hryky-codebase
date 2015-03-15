/**
  @file     shader_type_base.h
  @brief    The base class for type of variable.
  @author   HRYKY
  @version  $Id: shader_type_base.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_TYPE_BASE_H_20140830155653331
#define SHADER_TYPE_BASE_H_20140830155653331
#include "hryky/shader/shader_dispatchee.h"
#include "hryky/retention/retention_value.h"
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
namespace type
{
	/// The base class for type of variable.
	class Base;

} // namespace type
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief The base class for type of variable.
 */
class hryky::shader::type::Base :
	public Dispatchee<Base>,
	private retention::Value<String<> >
{
public :

	typedef Base this_type;
	typedef Dispatchee<this_type> base_type;
	typedef String<> name_type;

	/// default constructor.
	Base();

	/// creates an instance with a name of this type.
	Base(name_type const & name);

	/// copy constructor.
	Base(this_type const &);

	/// move constructor.
	Base(this_type &&);

	/// destructor.
	~Base();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to_impl(StreamT & out) const;

	/// retrieves the name of type.
	name_type const & name() const;

	/// writes the declaration of type.
	Coder & declare_impl(Coder & coder) const;

protected :

private :
	typedef retention::Value<String<> > retain_type;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
namespace type
{
} // namespace type
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT & hryky::shader::type::Base::write_to(
	StreamT & out) const
{
	return this->base_type::write_to(out);
}
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::type::Base::write_to_impl(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("name") << this->name();
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
namespace shader
{
namespace type
{
} // namespace type
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_TYPE_BASE_H_20140830155653331
// end of file
