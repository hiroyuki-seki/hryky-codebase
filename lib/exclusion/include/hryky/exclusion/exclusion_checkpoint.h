/**
  @file     exclusion_checkpoint.h
  @brief    waits until the result is determined.
  @author   HRYKY
  @version  $Id: exclusion_checkpoint.h 370 2014-07-21 16:00:02Z hryky.private@gmail.com $
 */
#ifndef EXCLUSION_CHECKPOINT_H_20140315123553191
#define EXCLUSION_CHECKPOINT_H_20140315123553191
#include "hryky/exclusion/exclusion_boolean.h"
#include "hryky/type_traits/as_parameter.h"
#include "hryky/with_stream_out.h"
#include "hryky/without_copy.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ValueT, typename LockableT
#define hryky_template_arg \
	ValueT, LockableT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
	/// waits until the result is determined.
	template <
		typename ValueT,
		typename LockableT = exclusion::Mutex
	>
	class Checkpoint;

} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief waits until the result is determined.
 */
template <hryky_template_param>
class hryky::exclusion::Checkpoint :
	public WithStreamOut<Checkpoint<hryky_template_arg> >
{
public :

	typedef Checkpoint<hryky_template_arg>      this_type;
	typedef typename AsParameter<ValueT>::type  parameter_type;

	/// default constructor.
	Checkpoint();

	/// copy constructor.
	Checkpoint(this_type const &);

	/// move constructor.
	Checkpoint(this_type &&);

	/// instantiates with an arbitrary parameter.
	template <typename RhsT>
	explicit Checkpoint(RhsT rhs);

	/// destructor.
	~Checkpoint();

	/// assigns a new value.
	template <typename RhsT>
	this_type & operator=(RhsT rhs);

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// waits until the result is determined.
	template <typename FunctorT>
	void join(FunctorT const & functor);

	/**
	  @brief    waits until the result is determined or the specified
	            duration expires.
	 */
	template <typename FunctorT, typename DurationT>
	bool join(FunctorT const & functor, DurationT const & duration);

protected :

private :
	typedef Boolean<LockableT> boolean_type;

	hryky_delete_this_copy_assign_op(Checkpoint);

	boolean_type    updated_;
	ValueT          value_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace exclusion
{
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::exclusion::Checkpoint<hryky_template_arg>::Checkpoint()
	: updated_()
	  , value_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::exclusion::Checkpoint<hryky_template_arg>::Checkpoint(
	this_type const & rhs)
	: hryky_copy_member(updated)
	  , hryky_copy_member(value)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::exclusion::Checkpoint<hryky_template_arg>::Checkpoint(
	this_type && rhs)
	: hryky_move_member(updated)
	  , hryky_move_member(value)
{
}
/**
  @brief instantiates with an arbitrary parameter.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::exclusion::Checkpoint<hryky_template_arg>::Checkpoint(RhsT rhs)
	: updated_()
	  , value_(rhs)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::exclusion::Checkpoint<hryky_template_arg>::~Checkpoint()
{
	this->clear();
}
/**
  @brief assigns a new value.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::exclusion::Checkpoint<hryky_template_arg> & 
hryky::exclusion::Checkpoint<hryky_template_arg>::operator=(RhsT rhs)
{
	this->value_ = rhs;

	this->updated_.enable();
	
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::exclusion::Checkpoint<hryky_template_arg>::clear()
{
	hryky::clear(this->value_);
	hryky::clear(this->updated_);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::exclusion::Checkpoint<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(updated);
	hryky_write_member(value);
	return out;
}
/**
  @brief waits until the result is determined.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::exclusion::Checkpoint<hryky_template_arg>::join(
	FunctorT const & functor)
{
	this->updated_.wait_true();
	
	functor(this->value_);
}
/**
  @brief waits until the result is determined or the specified duration expires.
 */
template <hryky_template_param>
template <typename FunctorT, typename DurationT>
bool hryky::exclusion::Checkpoint<hryky_template_arg>::join(
	FunctorT const & functor, DurationT const & duration)
{
	if (!this->updated_.wait_true(duration)) {
		return false;
	}

	functor(this->value_);
	
	return true;
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
namespace exclusion
{
} // namespace exclusion
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // EXCLUSION_CHECKPOINT_H_20140315123553191
// end of file
