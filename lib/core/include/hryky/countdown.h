/**
  @file     countdown.h
  @brief    counts integral numbers in descending order.
  @author   HRYKY
  @version  $Id: countdown.h 350 2014-04-24 10:10:31Z hryky.private@gmail.com $
 */
#ifndef COUNTDOWN_H_20131214140019250
#define COUNTDOWN_H_20131214140019250
#include "hryky/integer/unsigned_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename IndexT
#define hryky_template_arg \
	IndexT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// counts integral numbers in descending order.
	template <typename IndexT = size_t>
	class Countdown;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief counts integral numbers in descending order.
 */
template <hryky_template_param>
class hryky::Countdown :
	public WithStreamOut<Countdown<hryky_template_arg> >,
	public WithSwap<Countdown<hryky_template_arg> >
{
public :

	typedef Countdown<hryky_template_arg> this_type;
	typedef typename UnsignedOf<IndexT>::type size_type;

	/// copy constructor.
	Countdown(this_type const &);

	/// move constructor.
	Countdown(this_type && rhs);

	/// constructor with the end of the range.
	Countdown(IndexT end);

	/// constructor with the range.
	Countdown(IndexT begin, IndexT end);

	/// destructor.
	~Countdown();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/**
	  pre-"de"crements the index of the range.
	 */
	this_type & operator++();

	/**
	  post-"de"crements the index of the range.
	 */
	this_type operator++(int);

	/// retrieves the index as a value.
	IndexT operator*() const;

	/// releases the internal resources.
	void clear();

	/// retrieves the size of the range.
	size_type size() const;

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// calls an arbitrary function without each element.
	template <typename FunctorT>
	void foreach(FunctorT const & functor) const;

	/**
	  calls an arbitrary function without each element until the function
	  fails.
	 */
	template <typename FunctorT>
	bool every(FunctorT const & functor) const;

	/**
	  calls an arbitrary function without each element until the function
	  succeeds.
	 */
	template <typename FunctorT>
	bool some(FunctorT const & functor) const;

	/// calls an arbitrary function with each element.
	template <typename FunctorT>
	void foreach_at(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  fails.
	 */
	template <typename FunctorT>
	bool every_at(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  succeeds.
	 */
	template <typename FunctorT>
	bool some_at(FunctorT const & functor) const;

protected :

private :

	hryky_delete_default_constructor(Countdown);

	/// retrieves the beginning of the range.
	IndexT begin() const;

	/// retrieves the end of the range.
	IndexT end() const;

	/// retrieves the current index.
	IndexT itr() const;

	/// confirms whether the index reached to the end of the range.
	bool valid() const;

	/// retrieves the index from iterator.
	IndexT index_of(IndexT const itr) const;

	IndexT begin_;
	IndexT end_;
	IndexT itr_;

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
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Countdown<hryky_template_arg>::Countdown(this_type const & rhs)
	: hryky_copy_member(begin)
	  , hryky_copy_member(end)
	  , hryky_copy_member(itr)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Countdown<hryky_template_arg>::Countdown(this_type && rhs)
	: hryky_move_member(begin)
	  , hryky_move_member(end)
	  , hryky_move_member(itr)
{
}
/**
  @brief constructor with the end of the range.
 */
template <hryky_template_param>
hryky::Countdown<hryky_template_arg>::Countdown(IndexT end)
	: begin_()
	  , end_(end)
	  , itr_()
{
	return;
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Countdown<hryky_template_arg>::~Countdown()
{
}
/**
  @brief constructor with the range.
 */
template <hryky_template_param>
hryky::Countdown<hryky_template_arg>::Countdown(IndexT begin, IndexT end)
	: begin_(begin)
	  , end_(end)
	  , itr_(begin)
{
	return;
}
/**
  @brief pre-"de"crements the index of the range.
 */
template <hryky_template_param>
hryky::Countdown<hryky_template_arg> &
hryky::Countdown<hryky_template_arg>::operator++()
{
	++this->itr_;
	return *this;
}
/**
  @brief post-"de"crements the index of the range.
 */
template <hryky_template_param>
hryky::Countdown<hryky_template_arg>
hryky::Countdown<hryky_template_arg>::operator++(int)
{
	this_type const result(*this);

	++(*this);

	return result;
}
/**
  @brief retrieves the index as a value.
 */
template <hryky_template_param>
IndexT hryky::Countdown<hryky_template_arg>::operator*() const
{
	return this->index_of(this->itr());
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Countdown<hryky_template_arg>::clear()
{
	hryky::clear(this->itr_);
	hryky::clear(this->end_);
	hryky::clear(this->begin_);
}
/**
  @brief retrieves the size of the range.
 */
template <hryky_template_param>
typename hryky::Countdown<hryky_template_arg>::size_type
hryky::Countdown<hryky_template_arg>::size() const
{
	return this->end() - this->begin();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Countdown<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(begin);
	hryky_write_member(end);
	hryky_write_member(itr);
	
	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Countdown<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(begin);
	hryky_swap_member(end);
	hryky_swap_member(itr);
}
/**
  @brief calls an arbitrary function without each element.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::Countdown<hryky_template_arg>::foreach(
	FunctorT const & functor) const
{
	IndexT itr = this->begin();
	IndexT const end = this->end();
	for (; end != itr; ++itr) {
		functor();
	}
}
/**
  @brief calls an arbitrary function without each element until
    the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Countdown<hryky_template_arg>::every(
	FunctorT const & functor) const
{
	IndexT itr = this->begin();
	IndexT const end = this->end();
	for (; end != itr; ++itr) {
		if (!functor()) {
			return false;
		}
	}
	return true;
}
/**
  @brief calls an arbitrary function without each element until
    the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Countdown<hryky_template_arg>::some(
	FunctorT const & functor) const
{
	IndexT itr = this->begin();
	IndexT const end = this->end();
	for (; end != itr; ++itr) {
		if (functor()) {
			return true;
		}
	}
	return false;
}
/**
  @brief calls an arbitrary function with each element.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::Countdown<hryky_template_arg>::foreach_at(
	FunctorT const & functor) const
{
	IndexT itr = this->begin();
	IndexT const end = this->end();
	for (; end != itr; ++itr) {
		functor(this->index_of(itr));
	}
}
/**
  @brief calls an arbitrary function with each element until
    the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Countdown<hryky_template_arg>::every_at(
	FunctorT const & functor) const
{
	IndexT itr = this->begin();
	IndexT const end = this->end();
	for (; end != itr; ++itr) {
		if (!functor(this->index_of(itr))) {
			return false;
		}
	}
	return true;
}
/**
  @brief calls an arbitrary function with each element until
    the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::Countdown<hryky_template_arg>::some_at(
	FunctorT const & functor) const
{
	IndexT itr = this->begin();
	IndexT const end = this->end();
	for (; end != itr; ++itr) {
		if (functor(this->index_of(itr))) {
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the beginning of the range.
 */
template <hryky_template_param>
IndexT hryky::Countdown<hryky_template_arg>::begin() const
{
	return this->begin_;
}
/**
  @brief retrieves the end of the range.
 */
template <hryky_template_param>
IndexT hryky::Countdown<hryky_template_arg>::end() const
{
	return this->end_;
}
/**
  @brief retrieves the current index.
 */
template <hryky_template_param>
IndexT hryky::Countdown<hryky_template_arg>::itr() const
{
	return this->itr_;
}
/**
  @brief confirms whether the index reached to the end of the range.
 */
template <hryky_template_param>
bool hryky::Countdown<hryky_template_arg>::valid() const
{
	return this->end() != this->itr_;
}
/**
  @brief retrieves the index from iterator.
 */
template <hryky_template_param>
IndexT hryky::Countdown<hryky_template_arg>::index_of(IndexT const itr) const
{
	return this->begin() + this->end() - itr - 1u;
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{

	/// instantiates Countdown class by number.
	template <typename IndexT>
	Countdown<IndexT> countdown(IndexT const num);

	/// instantiates Countdown class by the range of integers.
	template <typename IndexT>
	Countdown<IndexT> countdown(IndexT const begin, IndexT const end);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates Countdown class by number.
 */
template <typename IndexT>
hryky::Countdown<IndexT>
hryky::countdown(IndexT const num)
{
	return Countdown<IndexT>(num);
}
/**
  @brief instantiates Countdown class by the range of integers.
 */
template <typename IndexT>
hryky::Countdown<IndexT>
hryky::countdown(IndexT const begin, IndexT const end)
{
	return Countdown<IndexT>(begin, end);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // COUNTDOWN_H_20131214140019250
// end of file
