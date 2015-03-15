/**
  @file     singleton_ptr.h
  @brief    creates and retains the singleton instance.
  @author   HRYKY
  @version  $Id: singleton_ptr.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef SINGLETON_PTR_H_20140622191308467
#define SINGLETON_PTR_H_20140622191308467
#include "hryky/intrusive_ptr.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT
#define hryky_template_arg \
	ValueT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// creates and retains the singleton instance.
	template <typename ValueT>
	class SingletonPtr;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates and retains the singleton instance.
 */
template <hryky_template_param>
class hryky::SingletonPtr :
	public IntrusivePtr<ValueT>
{
public :

	typedef SingletonPtr<hryky_template_arg>    this_type;
	typedef IntrusivePtr<ValueT>                base_type;

	/// default constructor.
	SingletonPtr();

	/// creates an instance with the raw pointer.
	SingletonPtr(pointer const ptr, bool const add_ref);

	/// copy constructor.
	SingletonPtr(this_type const &);

	/// move constructor.
	SingletonPtr(this_type &&);

	/// destructor.
	~SingletonPtr();

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

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  specializes hryky::RemovePointer
 */
template <hryky_template_param>
class RemovePointer<SingletonPtr<hryky_template_arg> >
{
public :

	typedef ValueT                              type;
	typedef SingletonPtr<hryky_template_arg>    pointer;
	typedef typename pointer::reference         result_type;

	RemovePointer(pointer ptr)
		: ptr_(ptr)
	{}

	result_type operator()() const
	{
		return *this->ptr_;
	}

private :
	pointer     ptr_;

};
/**
  specializes hryky::IsPointer.
 */
template <hryky_template_param>
class IsPointer<SingletonPtr<hryky_template_arg> >
{
public :
	typedef true_type type;
};
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::SingletonPtr<hryky_template_arg>::SingletonPtr()
	: base_type(ValueT::instance())
{
}
/**
  @brief creates an instance with the raw pointer.
 */
template <hryky_template_param>
hryky::SingletonPtr<hryky_template_arg>::SingletonPtr(
	pointer const ptr, bool const add_ref)
	: base_type(ptr, add_ref)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::SingletonPtr<hryky_template_arg>::SingletonPtr(this_type const & rhs)
	: base_type(rhs)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::SingletonPtr<hryky_template_arg>::SingletonPtr(this_type && rhs)
	: base_type(::std::move(rhs))
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::SingletonPtr<hryky_template_arg>::~SingletonPtr()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::SingletonPtr<hryky_template_arg>::clear()
{
	this->base_type::clear();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::SingletonPtr<hryky_template_arg>::swap(this_type & src)
{
	this->base_type::swap(src);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::SingletonPtr<hryky_template_arg>::write_to(StreamT & out) const
{
	return this->base_type::write_to(out);
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
#endif // SINGLETON_PTR_H_20140622191308467
// end of file
