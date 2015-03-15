/**
  @file     singleton_trait.h
  @brief    confers the feature which behaves as a singleton.
  @author   HRYKY
  @version  $Id: singleton_trait.h 375 2014-07-29 04:27:53Z hryky.private@gmail.com $
 */
#ifndef SINGLETON_TRAIT_H_20140622182345433
#define SINGLETON_TRAIT_H_20140622182345433
#include "hryky/singleton_ptr.h"
#include "hryky/tmp/null.h"
#include "hryky/exclusion/exclusion_variable.h"
#include "hryky/with_stream_out.h"
#include "hryky/is_null.h"
#include "hryky/log/log_definition.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT, typename LockableT, typename AlignedT
#define hryky_template_arg \
	DerivedT, LockableT, AlignedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// confers the feature which behaves as a singleton.
	template <
		typename DerivedT,
		typename LockableT = Null,
		typename AlignedT = size_t
	>
	class SingletonTrait;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief confers the feature which behaves as a singleton.
 */
template <hryky_template_param>
class hryky::SingletonTrait :
	public WithStreamOut<SingletonTrait<hryky_template_arg> >
{
public :

	typedef SingletonTrait<hryky_template_arg> this_type;
	typedef SingletonPtr<DerivedT> instance_type;

	/// retrieves the singleton.
	static instance_type instance();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// increments the reference counter.
	void add_ref();

	/// decrements the reference counter.
	void release();

protected :

	/// default constructor.
	SingletonTrait();
	
	/// destructor.
	~SingletonTrait();

private :
	hryky_delete_this_copy_constructor(SingletonTrait);
	hryky_delete_copy_assign_op(this_type);

	typedef exclusion::Variable<DerivedT *, LockableT>
		singleton_type;

	static singleton_type singleton_;

	size_t counter_;
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
  @brief retrieves the singleton.
 */
template <hryky_template_param>
typename hryky::SingletonTrait<hryky_template_arg>::instance_type 
hryky::SingletonTrait<hryky_template_arg>::instance()
{
	/**
	   The second invocation right after the first invocation may
	  release the singleton instance before the first invocation
	  returns the instance.
	   Therefore, the reference counter is incremented in this
	  exclusion control.
	 */
	return instance_type(
		this_type::singleton_.update([](DerivedT * const singleton) {
			if (!hryky_is_null(singleton)) {
				++singleton->counter_;
				return singleton;
			}

			union Buffer
			{
				uint8_t buffer_[sizeof(DerivedT)];
				AlignedT aligned_;
			};
			static Buffer buffer;

			DerivedT * const instance = new (&buffer.buffer_) DerivedT();
			++instance->counter_;

			return instance;
		}), false);
}
/**
  @brief increments the reference counter.
 */
template <hryky_template_param>
void hryky::SingletonTrait<hryky_template_arg>::add_ref()
{
	hryky_log_info("add_ref()");
	this_type::singleton_.exclude([](this_type * const singleton) {
		++singleton->counter_;
	});
}
/**
  @brief decrements the reference counter.
 */
template <hryky_template_param>
void hryky::SingletonTrait<hryky_template_arg>::release()
{
	this_type::singleton_.update([](DerivedT * const singleton) {
		if (0u == singleton->counter_) {
			hryky_log_alert(
				"The invalid reference counter.");
			return reinterpret_cast<DerivedT *>(hryky_nullptr);
		}
		if (0u < --singleton->counter_) {
			return singleton;
		}
		singleton->~DerivedT();
		return reinterpret_cast<DerivedT *>(hryky_nullptr);
	});
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::SingletonTrait<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	this_type::singleton_.exclude([&out](DerivedT * const singleton) {
		out << "counter" << singleton->counter_;
	});
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::SingletonTrait<hryky_template_arg>::SingletonTrait()
	: counter_()
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::SingletonTrait<hryky_template_arg>::~SingletonTrait()
{
}
//------------------------------------------------------------------------------
// defines private member variable
//------------------------------------------------------------------------------
/**
  The pointer to the singleton.
 */
template <hryky_template_param>
typename hryky::SingletonTrait<hryky_template_arg>::singleton_type
hryky::SingletonTrait<hryky_template_arg>::singleton_;
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
	/// increments the refernece counter of SingletonTrait.
	template <hryky_template_param>
	void intrusive_ptr_add_ref(
		SingletonTrait<hryky_template_arg> * const ptr);

	/// decrements the reference counter of SingletonTrait.
	template <hryky_template_param>
	void intrusive_ptr_release(
		SingletonTrait<hryky_template_arg> * const ptr);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief increments the refernece counter of SingletonTrait.
 */
template <hryky_template_param>
void hryky::intrusive_ptr_add_ref(
	SingletonTrait<hryky_template_arg> * const ptr)
{
	if (hryky_is_null(ptr)) {
		return;
	}
	ptr->add_ref();
}
/**
  @brief decrements the reference counter of SingletonTrait.
 */
template <hryky_template_param>
void hryky::intrusive_ptr_release(
	SingletonTrait<hryky_template_arg> * const ptr)
{
	if (hryky_is_null(ptr)) {
		return;
	}
	ptr->release();
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SINGLETON_TRAIT_H_20140622182345433
// end of file
