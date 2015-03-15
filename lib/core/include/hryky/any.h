/**
  @file         any.h
  @brief        arbitrary typed value without polymorphism.
  @author       HRYKY
  @version      $Id: any.h 373 2014-07-27 04:20:16Z hryky.private@gmail.com $
 */
#ifndef ANY_H_20121211170650379
#define ANY_H_20121211170650379
#include "hryky/allocator/allocator_instantiate.h"
#include "hryky/allocator/allocator_mempool.h"
#include "hryky/clear.h"
#include "hryky/intrusive_ptr.h"
#include "hryky/json/json_writer.h"
#include "hryky/kind.h"
#include "hryky/nullptr.h"
#include "hryky/pragma.h"
#include "hryky/type.h"
#include "hryky/type_traits/enable_if.h"
#include "hryky/type_traits/is_arithmetic.h"
#include "hryky/type_traits/is_enum.h"
#include "hryky/type_traits/is_floating_point.h"
#include "hryky/type_traits/is_signed.h"
#include "hryky/type_traits/is_unsigned.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/is_null.h"
#include "hryky/with_is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
#pragma hryky_pragma_disable_warning_virtual_destructor
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AllocatorT
#define hryky_template_arg \
	AllocatorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// arbitrary typed value without polymorphism.
	template <
		typename AllocatorT = allocator::Mempool<int>
	>
	class Any;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief arbitrary typed value without polymorphism.
 */
template <hryky_template_param>
class hryky::Any :
	public WithStreamOut<Any<hryky_template_arg> >,
	public WithSwap<Any<hryky_template_arg> >,
	public WithIsNull<Any<hryky_template_arg> >
{
public :

	typedef Any<hryky_template_arg> this_type;
	typedef AllocatorT      allocator_type;
	typedef uint64_t        uint_type;
	typedef int64_t         sint_type;
	typedef double          float_type;

	/// default constructor.
	Any();

	/// copy constructor.
	Any(this_type const &);

	/// move constructor.
	Any(this_type && rhs);

	/// constructor with an unsigned integer value.
	template <typename ValueT>
	Any(ValueT const rhs,
		typename EnableIf<IsUnsigned<ValueT> >::type * = hryky_nullptr);

	/// constructs with a signed integer value.
	template <typename ValueT>
	Any(ValueT const rhs,
		typename EnableIf<IsSigned<ValueT> >::type * = hryky_nullptr);

	/// constructs with a floating point value.
	template <typename ValueT>
	Any(ValueT const rhs,
		typename EnableIf<IsFloatingPoint<ValueT> >::type * = hryky_nullptr);

	/// constructs with an enumeratable value.
	template <typename ValueT>
	Any(ValueT const rhs,
		typename EnableIf<IsEnum<ValueT> >::type * = hryky_nullptr);

	/// constructor with an arbitrary type of value.
	template < typename ValueT >
	Any(ValueT const & obj,
		allocator_type const & allocator);

	/// destructor.
	~Any();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// assignment operator for arbitrary type.
	template < typename ValueT >
	this_type & operator=(ValueT const & rhs);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// casts the internal value to a numeric value.
	template <typename ValueT>
	ValueT cast(
		typename EnableIf<
			IsArithmetic<ValueT> >::type * = hryky_nullptr) const;

	/// casts the internal value to an enumeratable value.
	template <typename ValueT>
	ValueT cast(
		typename EnableIf<
			IsEnum<ValueT> >::type * = hryky_nullptr) const;

	/// casts to an arbitrary type.
	template < typename ValueT >
	ValueT * cast(
		typename DisableIf<tmp::Or<
			IsArithmetic<ValueT>,
			IsEnum<ValueT>
		> >::type * = hryky_nullptr);

	/// casts to an arbitrary immutable type.
	template < typename ValueT >
	ValueT const * cast(
		typename DisableIf<tmp::Or<
			IsArithmetic<ValueT>,
			IsEnum<ValueT>
		> >::type * = hryky_nullptr) const;

	/// retrieves the information of the internal type.
	type::info_type const & type_info() const;

	/// confirms whether the internal holder is null.
	bool is_null() const;

protected :

private :

	class HolderBase
	{
	public :
		virtual HolderBase * clone(allocator_type const & allocator) = 0;
		
		virtual void release(allocator_type const & allocator) = 0;
		
		virtual type::info_type const & info() const = 0;

	protected :
		HolderBase()
		{
		}

		~HolderBase()
		{
		}
	};

	template <typename ValueT>
	class Holder : public HolderBase
	{
	public :
		typedef ValueT value_type;
		typedef ValueT const & const_reference;
		typedef ValueT & reference;
		typedef Holder<ValueT> this_type;
		
		Holder(const_reference ref)
			: value_(ref)
		{
		}
		
		Holder(this_type const & rhs)
			: hryky_copy_member(value)
		{
		}

		~Holder()
		{
			this->clear();
		}

		virtual Holder * clone(allocator_type const & allocator)
		{
			typename allocator_type::template rebind<this_type>::other
				holder_allocator(allocator);
			
			return allocator::instantiate_by(
				holder_allocator, this_type(this->value_));
		}
		
		virtual void release(allocator_type const & allocator)
		{
			typename allocator_type::template rebind<this_type>::other
				holder_allocator(allocator);
			
			allocator::release_by(holder_allocator, this);
		}

		virtual type::info_type const & info() const
		{
			return type::info(this->value_);
		}
		
		reference value()
		{
			return this->value_;
		}

		const_reference value() const
		{
			return this->value_;
		}
		
	private :
		void clear()
		{
			hryky::clear(this->value_);
		}
		
		ValueT value_;
	};

	struct BuiltinKind
	{
		enum Raw
		{
			empty,
			uint_value,
			sint_value,
			float_value,
			holder,
			enum_value,
			num,
		};
	};
	typedef hryky::Kind<BuiltinKind> builtin_kind_type;

	allocator_type allocator_;
	
	union
	{
		uint_type       uint_;
		sint_type       sint_;
		float_type      float_;
		sint_type       enum_;
		HolderBase *    holder_;
		void *          value_;
	};

	builtin_kind_type builtin_kind_;

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
hryky::Any<hryky_template_arg>::Any()
	: allocator_()
	  , value_()
	  , builtin_kind_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Any<hryky_template_arg>::Any(this_type const & rhs)
	: hryky_copy_member(allocator)
	  , hryky_copy_member(value)
	  , hryky_copy_member(builtin_kind)
{
	if (BuiltinKind::holder == rhs.builtin_kind_
		&& hryky_nullptr != rhs.holder_) {
		this->holder_ = rhs.holder_->clone(this->allocator_);
	}
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Any<hryky_template_arg>::Any(this_type && rhs)
	: hryky_move_member(allocator)
	  , hryky_move_member(value)
	  , hryky_move_member(builtin_kind)
{
	hryky::clear(rhs.value_);
	hryky::clear(rhs.builtin_kind_);
}
/**
  @brief constructs with an unsigned integer value.
 */
template <hryky_template_param>
template <typename ValueT>
hryky::Any<hryky_template_arg>::Any(
	ValueT const rhs, typename EnableIf<IsUnsigned<ValueT> >::type *)
	: allocator_()
	  , uint_(rhs)
	  , builtin_kind_(BuiltinKind::uint_value)
{
}
/**
  @brief constructs with a signed integer value.
 */
template <hryky_template_param>
template <typename ValueT>
hryky::Any<hryky_template_arg>::Any(
	ValueT const rhs, typename EnableIf<IsSigned<ValueT> >::type *)
	: allocator_()
	  , sint_(rhs)
	  , builtin_kind_(BuiltinKind::sint_value)
{
}
/**
  @brief constructs with a floating point value.
 */
template <hryky_template_param>
template <typename ValueT>
hryky::Any<hryky_template_arg>::Any(
	ValueT const rhs, typename EnableIf<IsFloatingPoint<ValueT> >::type *)
	: allocator_()
	  , float_(rhs)
	  , builtin_kind_(BuiltinKind::float_value)
{
}
/**
  @brief constructs with an enumeratable value.
 */
template <hryky_template_param>
template <typename ValueT>
hryky::Any<hryky_template_arg>::Any(
	ValueT const rhs, typename EnableIf<IsEnum<ValueT> >::type *)
	: allocator_()
	  , enum_(rhs)
	  , builtin_kind_(BuiltinKind::enum_value)
{
}
/**
  @brief constructor with an arbitrary type of value.
 */
template <hryky_template_param>
template < typename ValueT >
hryky::Any<hryky_template_arg>::Any(
	ValueT const & obj,
	allocator_type const & allocator)
	: allocator_(allocator)
	  , value_()
	  , builtin_kind_(BuiltinKind::holder)
{
	typename allocator_type::template rebind<Holder<ValueT> >::other
		holder_allocator(allocator);
	
	this->holder_ = allocator::instantiate_by(
		holder_allocator, Holder<ValueT>(obj));
	if (hryky_is_null(this->holder_)) {
		hryky_log_err("failed to instantiate.");
	}
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Any<hryky_template_arg>::~Any()
{
	this->clear();
}
/**
  @brief assignment operator for arbitrary type.
 */
template <hryky_template_param>
template < typename ValueT >
hryky::Any<hryky_template_arg> &
hryky::Any<hryky_template_arg>::operator=(ValueT const & rhs)
{
	this_type(rhs).swap(*this);

	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Any<hryky_template_arg>::clear()
{
	if (BuiltinKind::holder == this->builtin_kind_
		&& hryky_nullptr != this->holder_) {
		this->holder_->release(this->allocator_);
	}

	hryky::clear(this->builtin_kind_);
	hryky::clear(this->value_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Any<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(builtin_kind);

	switch (this->builtin_kind_) {
	case BuiltinKind::empty:
		break;
	case BuiltinKind::uint_value:
		hryky_write_member(uint);
		break;
	case BuiltinKind::sint_value:
		hryky_write_member(sint);
		break;
	case BuiltinKind::float_value:
		hryky_write_member(float);
		break;
	case BuiltinKind::holder:
		hryky_write_pointer_member(holder);
		break;
	default:
		hryky_log_err("invlaid builtin kind");
		break;
	}
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Any<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(allocator);
	hryky_swap_member(value);
	hryky_swap_member(builtin_kind);
}
/**
  @brief casts the internal value to a numeric value.
 */
template <hryky_template_param>
template <typename ValueT>
ValueT hryky::Any<hryky_template_arg>::cast(
	typename EnableIf<IsArithmetic<ValueT> >::type *) const
{
	switch (this->builtin_kind_) {
	case BuiltinKind::uint_value:
		return static_cast<ValueT>(this->uint_);
	case BuiltinKind::sint_value:
		return static_cast<ValueT>(this->sint_);
	case BuiltinKind::float_value:
		return static_cast<ValueT>(this->float_);
	default:
		hryky_log_err(
			"invlaid builtin kind for casting to a numeric value.");
		return static_cast<ValueT>(0u);
	}
}
/**
  @brief casts the internal value to an enumeratable value.
 */
template <hryky_template_param>
template <typename ValueT>
ValueT hryky::Any<hryky_template_arg>::cast(
	typename EnableIf<IsEnum<ValueT> >::type *) const
{
	switch (this->builtin_kind_) {
	case BuiltinKind::enum_value:
		return static_cast<ValueT>(this->enum_);
	default:
		hryky_log_err(
			"invlaid builtin kind for casting to an enum value.");
		return static_cast<ValueT>(0u);
	}
}
/**
  @brief casts to an arbitrary mutable type.
 */
template <hryky_template_param>
template < typename ValueT >
ValueT * hryky::Any<hryky_template_arg>::cast(
	typename DisableIf<tmp::Or<
		IsArithmetic<ValueT>,
		IsEnum<ValueT>
	> >::type *)
{
	switch (this->builtin_kind_) {
	case BuiltinKind::holder:
		{
			if (hryky_is_null(this->holder_)) {
				hryky_log_err("The internal instance is null.");
				return hryky_nullptr;
			}
			type::info_type const lhs_info = this->holder_->info();
			type::info_type const rhs_info = type::info<ValueT>();
			if (lhs_info != rhs_info) {
				hryky_log_err(
					"invalid kind for casting to arbitrary type."
					<< (json::writer()
						<< stream::denote("lhs") << lhs_info
						<< stream::denote("rhs") << rhs_info));
				return hryky_nullptr;
			}
			return &(static_cast<Holder<ValueT> *>(
				this->holder_)->value());
		}
	default :
		hryky_log_err(
			"invalid kind for casting to arbitrary type"
			<< (json::writer()
				<< *this
				<< stream::denote("cast_to") << type::info<ValueT>()));
		return hryky_nullptr;
	}
}
/**
  @brief casts to an arbitrary immutable type.
 */
template <hryky_template_param>
template < typename ValueT >
ValueT const * hryky::Any<hryky_template_arg>::cast(
	typename DisableIf<tmp::Or<
		IsArithmetic<ValueT>,
		IsEnum<ValueT>
	> >::type *) const
{
	switch (this->builtin_kind_) {
	case BuiltinKind::holder: {
		if (hryky_is_null(this->holder_)) {
			hryky_log_err("The internal instance is null.");
			return hryky_nullptr;
		}
		type::info_type const lhs_info = this->holder_->info();
		type::info_type const rhs_info = type::info<ValueT>();
		if (lhs_info != rhs_info) {
			hryky_log_err(
				"invalid kind for casting to arbitrary type."
				<< (json::writer()
					<< stream::denote("lhs") << lhs_info
					<< stream::denote("rhs") << rhs_info));
			return hryky_nullptr;
		}
		return &(static_cast<Holder<ValueT> const *>(
			this->holder_)->value());
	}
	default : {
		hryky_log_err(
			"invalid kind for casting to arbitrary type"
			<< (json::writer()
				<< *this
				<< stream::denote("cast_to") << type::info<ValueT>()));
		return hryky_nullptr;
	}
	}
}
/**
  @brief retrieves the information of the internal type.
 */
template <hryky_template_param>
hryky::type::info_type const &
hryky::Any<hryky_template_arg>::type_info() const
{
	switch (this->builtin_kind_) {
	case BuiltinKind::uint_value:
		return type::info(this->uint_);
	case BuiltinKind::sint_value:
	case BuiltinKind::enum_value:
		return type::info(this->sint_);
	case BuiltinKind::float_value:
		return type::info(this->float_);
	case BuiltinKind::holder: {
		if (hryky_is_null(this->holder_)) {
			hryky_log_err("The internal instance is null.");
			return type::info(hryky::Null);
		}
		return this->holder_->info();
	}
	default:
		hryky_log_err(
			"invalid kind for retrieving the information of type.");
		return type::info(hryky::Null);
	}
}
/**
  @brief confirms whether the internal holder is null.
 */
template <hryky_template_param>
bool hryky::Any<hryky_template_arg>::is_null() const
{
	return BuiltinKind::holder == this->builtin_kind_ &&
		hryky::is_null(this->holder_);
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
// revokes macro definitions
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores the warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // ANY_H_20121211170650379
// end of file
