/**
  @file     shader_function_ptr.h
  @brief    retains a pointer to Function.
  @author   HRYKY
  @version  $Id: shader_function_ptr.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_FUNCTION_PTR_H_20140820100040083
#define SHADER_FUNCTION_PTR_H_20140820100040083
#include "hryky/intrusive_ptr.h"
#include "hryky/shader/shader_function.h"
#include "hryky/shader/shader_block_ptr.h"
#include "hryky/shader/shader_with_code.h"
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
	/// retains a pointer to Function.
	class FunctionPtr;

	typedef FunctionPtr function_type;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a pointer to Function.
 */
class hryky::shader::FunctionPtr :
	public BlockPtr<Function>,
	public WithCode<FunctionPtr>
{
public :

	typedef BlockPtr<Function> base_type;

	typedef FunctionPtr this_type;

	/// default constructor.
	FunctionPtr();

	/// creates an intance from pointer.
	FunctionPtr(pointer const ptr, bool const add_ref = true);

	/// copy constructor.
	FunctionPtr(this_type const &);

	/// move constructor.
	FunctionPtr(this_type &&);

	/// destructor.
	~FunctionPtr();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	template <typename RhsT>
	FunctionPtr & operator<<(TermPtr<RhsT> const & rhs)
	{
		(*this)->append(rhs);
		return *this;
	}

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
StreamT &
hryky::shader::FunctionPtr::write_to(StreamT & out) const
{
	if (hryky_is_null(*this)) {
		return this->base_type::write_to(out);
	}
	else {
		return (*this)->write_to(out);
	}
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
	/// creates a definition of function.
	template <size_t Size>
	FunctionPtr function(char const (&identifier)[Size]);

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates a definition of function.
 */
template <size_t Size>
hryky::shader::FunctionPtr
hryky::shader::function(
	char const (&identifier)[Size])
{
	allocator::Mempool<Function> allocator;
	return FunctionPtr(allocator::instantiate_by(allocator, identifier));
}
#endif // SHADER_FUNCTION_PTR_H_20140820100040083
// end of file
