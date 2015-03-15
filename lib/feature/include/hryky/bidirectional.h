/**
  @file         bidirectional.h
  @brief        base class which behaves as a bidirectional node.
  @author       HRYKY
  @version      $Id: bidirectional.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef BIDIRECTIONAL_H_20130309183544441
#define BIDIRECTIONAL_H_20130309183544441
#include "hryky/type_traits/as_parameter.h"
#include "hryky/type_traits/is_base_of.h"
#include "hryky/nullptr.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename PointerT
#define hryky_template_arg \
	PointerT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// base class which behaves as a bidirectional node.
	template <hryky_template_param>
	class Bidirectional;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief base class which behaves as a bidirectional node.
 */
template <hryky_template_param>
class hryky::Bidirectional :
	public WithStreamOut<Bidirectional<hryky_template_arg> >,
	public WithSwap<Bidirectional<hryky_template_arg> >
{
public :

	typedef Bidirectional<hryky_template_arg> this_type;

	typedef PointerT pointer;
	typedef typename AsParameter<pointer>::type pointer_param_type;

	/// default constructor.
	Bidirectional();

	/// copy constructor.
	Bidirectional(this_type const &);

	/// move constructor.
	Bidirectional(this_type &&);

	/// destructor.
	~Bidirectional();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// disconnect the links both previous and next.
	void secede();

	/// retrieves the previous pointer.
	pointer_param_type prev() const;

	/// retrieves the next pointer.
	pointer_param_type next() const;

	/// assigns a new previous pointer.
	void prev(pointer_param_type src);

	/// assigns a new next pointer.
	void next(pointer_param_type src);

protected :

private :

	PointerT prev_;
	PointerT next_;

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
hryky::Bidirectional<hryky_template_arg>::Bidirectional()
	: prev_()
	  , next_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Bidirectional<hryky_template_arg>::Bidirectional(this_type const & rhs)
	: hryky_copy_member(prev)
	  , hryky_copy_member(next)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Bidirectional<hryky_template_arg>::Bidirectional(this_type && rhs)
	: hryky_move_member(prev)
	  , hryky_move_member(next)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Bidirectional<hryky_template_arg>::~Bidirectional()
{
	this->secede();
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Bidirectional<hryky_template_arg>::clear()
{
	this->secede();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Bidirectional<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(prev);
	hryky_write_member(next);
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Bidirectional<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(prev);
	hryky_swap_member(next);
}
/**
  @brief disconnect the links both previous and next.
 */
template <hryky_template_param>
void hryky::Bidirectional<hryky_template_arg>::secede()
{
	if (PointerT() != this->next_) {
		this->next_->prev(this->prev_);
	}
	if (PointerT() != this->prev_) {
		this->prev_->next(this->next_);
	}
	this->next_ = PointerT();
	this->prev_ = PointerT();
}
/**
  @brief retrieves the previous pointer.
 */
template <hryky_template_param>
typename hryky::Bidirectional<hryky_template_arg>::pointer_param_type
hryky::Bidirectional<hryky_template_arg>::prev() const
{
	return this->prev_;
}
/**
  @brief retrieves the next pointer.
 */
template <hryky_template_param>
typename hryky::Bidirectional<hryky_template_arg>::pointer_param_type
hryky::Bidirectional<hryky_template_arg>::next() const
{
	return this->next_;
}
/**
  @brief assigns a new previous pointer.
 */
template <hryky_template_param>
void hryky::Bidirectional<hryky_template_arg>::prev(pointer_param_type src)
{
	this->prev_ = src;
}
/**
  @brief assigns a new next pointer.
 */
template <hryky_template_param>
void hryky::Bidirectional<hryky_template_arg>::next(pointer_param_type src)
{
	this->next_ = src;
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

	/// inserts a node before the other node.
	template <hryky_template_param>
	void insert_before(
		PointerT const & lhs,
		PointerT const & rhs,
	typename EnableIf<
		IsBaseOf<
			Bidirectional<hryky_template_arg>,
			typename RemovePointer<hryky_template_arg>::type
		>
	>::type * = hryky_nullptr);
	
	/// inserts a node after the other node.
	template <hryky_template_param>
	void insert_after(
		PointerT const & lhs,
		PointerT const & rhs,
	typename EnableIf<
		IsBaseOf<
			Bidirectional<hryky_template_arg>,
			typename RemovePointer<hryky_template_arg>::type
		>
	>::type * = hryky_nullptr);
	
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief inserts a node before the other node.
 */
template <hryky_template_param>
void hryky::insert_before(
	PointerT const & lhs,
	PointerT const & rhs,
	typename EnableIf<
		IsBaseOf<
			Bidirectional<hryky_template_arg>,
			typename RemovePointer<hryky_template_arg>::type
		>
	>::type *)
{
	lhs->secede();

	// connects the previous node of the target node with lhs node.
	PointerT const rhs_prev = rhs->prev();
	if (PointerT() != rhs_prev) {
		rhs_prev->next(lhs);
	}
	lhs->prev(rhs_prev);

	// connects lhs node with the target node.
	lhs->next(rhs);
	rhs->prev(lhs);
}
/**
  @brief inserts a node after the other node.
 */
template <hryky_template_param>
void hryky::insert_after(
	PointerT const & lhs,
	PointerT const & rhs,
	typename EnableIf<
		IsBaseOf<
			Bidirectional<hryky_template_arg>,
			typename RemovePointer<hryky_template_arg>::type
		>
	>::type *)
{
	lhs->secede();

	// connects the previous node of the target node with lhs node.
	PointerT const rhs_next = rhs->next();
	if (PointerT() != rhs_next) {
		rhs_next->prev(lhs);
	}
	lhs->next(rhs_next);

	// connects lhs node with the target node.
	lhs->prev(rhs);
	rhs->next(lhs);
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // BIDIRECTIONAL_H_20130309183544441
// end of file
