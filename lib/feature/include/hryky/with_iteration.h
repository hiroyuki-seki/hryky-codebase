/**
  @file     with_iteration.h
  @brief    provides the functions to iterate a container.
  @author   HRYKY
  @version  $Id: with_iteration.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef WITH_ITERATION_H_20130518152338308
#define WITH_ITERATION_H_20130518152338308
#include "hryky/stream/stream_array_scope.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename IteratorT, \
	typename ConstIteratorT
#define hryky_template_arg \
	ContainerT, IteratorT, ConstIteratorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// provides the functions to iterate a container.
	template <hryky_template_param>
	class WithIteration;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief provides the functions to iterate a container.
 */
template <
	typename ContainerT,
	typename IteratorT = typename ContainerT::iterator,
	typename ConstIteratorT = typename ContainerT::const_iterator
>
class hryky::WithIteration
{
public :

	/// calls an arbitrary function with each element.
	template <typename FunctorT>
	void foreach(FunctorT const & functor);

	/// calls an arbitrary function with each immutable element.
	template <typename FunctorT>
	void foreach(FunctorT const & functor) const;

	/// calls an arbitrary function with each element and the index.
	template <typename FunctorT>
	void foreach_at(FunctorT const & functor);

	/// calls an arbitrary function with each immutable element and the index.
	template <typename FunctorT>
	void foreach_at(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  fails.
	 */
	template <typename FunctorT>
	bool every(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element until
	  the function fails.
	 */
	template <typename FunctorT>
	bool every(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element and the index until
	  the function fails.
	 */
	template <typename FunctorT>
	bool every_at(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element and the
	  index until the function fails.
	 */
	template <typename FunctorT>
	bool every_at(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element until the function
	  succeeds.
	 */
	template <typename FunctorT>
	bool some(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element until
	  the function succeeds.
	 */
	template <typename FunctorT>
	bool some(FunctorT const & functor) const;

	/**
	  calls an arbitrary function with each element and the index until
	  the function succeeds.
	 */
	template <typename FunctorT>
	bool some_at(FunctorT const & functor);

	/**
	  calls an arbitrary function with each immutable element and the
	  index until the function succeeds.
	 */
	template <typename FunctorT>
	bool some_at(FunctorT const & functor) const;

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	/// retrieves the instance of the derived class.
	ContainerT * container();

	/// retrieves the immutable instance of the derived class.
	ContainerT const * container() const;

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
  @brief calls an arbitrary function with each element.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::WithIteration<hryky_template_arg>::foreach(
	FunctorT const & functor)
{
	IteratorT itr = this->container()->begin();
	IteratorT const end = this->container()->end();
	for (; end != itr; ++itr) {
		functor(*itr);
	}
}
/**
  @brief calls an arbitrary function with each immutable element.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::WithIteration<hryky_template_arg>::foreach(
	FunctorT const & functor) const
{
	ConstIteratorT itr = this->container()->begin();
	ConstIteratorT const end = this->container()->end();
	for (; end != itr; ++itr) {
		functor(*itr);
	}
}
/**
  @brief calls an arbitrary function with each element and the index.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::WithIteration<hryky_template_arg>::foreach_at(
	FunctorT const & functor)
{
	IteratorT itr = this->container()->begin();
	IteratorT const end = this->container()->end();
	typename ContainerT::size_type index = 0;
	for (; end != itr; ++itr, ++index) {
		functor(*itr, index);
	}
}
/**
  @brief calls an arbitrary function with each immutable element
    and the index.
 */
template <hryky_template_param>
template <typename FunctorT>
void hryky::WithIteration<hryky_template_arg>::foreach_at(
	FunctorT const & functor) const
{
	ConstIteratorT itr = this->container()->begin();
	ConstIteratorT const end = this->container()->end();
	typename ContainerT::size_type index = 0;
	for (; end != itr; ++itr, ++index) {
		functor(*itr, index);
	}
}
/**
  @brief calls an arbitrary function with each element until
    the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::WithIteration<hryky_template_arg>::every(
	FunctorT const & functor)
{
	IteratorT itr = this->container()->begin();
	IteratorT const end = this->container()->end();
	for (; end != itr; ++itr) {
		if (!functor(*itr)) {
			return false;
		}
	}
	return true;
}
/**
  @brief calls an arbitrary function with each immutable element until
    the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::WithIteration<hryky_template_arg>::every(
	FunctorT const & functor) const
{
	ConstIteratorT itr = this->container()->begin();
	ConstIteratorT const end = this->container()->end();
	for (; end != itr; ++itr) {
		if (!functor(*itr)) {
			return false;
		}
	}
	return true;
}
/**
  @brief calls an arbitrary function with each element and the index
    until the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::WithIteration<hryky_template_arg>::every_at(
	FunctorT const & functor)
{
	IteratorT itr = this->container()->begin();
	IteratorT const end = this->container()->end();
	typename ContainerT::size_type index = 0;
	for (; end != itr; ++itr, ++index) {
		if (!functor(*itr, index)) {
			return false;
		}
	}
	return true;
}
/**
  @brief calls an arbitrary function with each immutableelement and
    the index until the function fails.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::WithIteration<hryky_template_arg>::every_at(
	FunctorT const & functor) const
{
	ConstIteratorT itr = this->container()->begin();
	ConstIteratorT const end = this->container()->end();
	typename ContainerT::size_type index = 0;
	for (; end != itr; ++itr, ++index) {
		if (!functor(*itr, index)) {
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
bool hryky::WithIteration<hryky_template_arg>::some(
	FunctorT const & functor)
{
	IteratorT itr = this->container()->begin();
	IteratorT const end = this->container()->end();
	for (; end != itr; ++itr) {
		if (functor(*itr)) {
			return true;
		}
	}
	return false;
}
/**
  @brief calls an arbitrary function with each immutable element until
    the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::WithIteration<hryky_template_arg>::some(
	FunctorT const & functor) const
{
	ConstIteratorT itr = this->container()->begin();
	ConstIteratorT const end = this->container()->end();
	for (; end != itr; ++itr) {
		if (functor(*itr)) {
			return true;
		}
	}
	return false;
}
/**
  @brief calls an arbitrary function with each element
    and the index until the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::WithIteration<hryky_template_arg>::some_at(
	FunctorT const & functor)
{
	IteratorT itr = this->container()->begin();
	IteratorT const end = this->container()->end();
	typename ContainerT::size_type index = 0;
	for (; end != itr; ++itr, ++index) {
		if (functor(*itr, index)) {
			return true;
		}
	}
	return false;
}
/**
  @brief calls an arbitrary function with each immutable element
    and the index until the function succeeds.
 */
template <hryky_template_param>
template <typename FunctorT>
bool hryky::WithIteration<hryky_template_arg>::some_at(
	FunctorT const & functor) const
{
	ConstIteratorT itr = this->container()->begin();
	ConstIteratorT const end = this->container()->end();
	typename ContainerT::size_type index = 0;
	for (; end != itr; ++itr, ++index) {
		if (functor(*itr, index)) {
			return true;
		}
	}
	return false;
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::WithIteration<hryky_template_arg>::write_to(
	StreamT & out) const
{
	out << stream::denote("elements");
	stream::array::Scope<StreamT> const array(out);

	ConstIteratorT itr = this->container()->begin();
	ConstIteratorT const end = this->container()->end();
	for (; end != itr; ++itr) {
		out << *itr;
	}
	
	return out;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the instance of the derived class.
 */
template <hryky_template_param>
ContainerT * hryky::WithIteration<hryky_template_arg>::container()
{
	return static_cast<ContainerT *>(this);
}
/**
  @brief retrieves the immutable instance of the derived class.
 */
template <hryky_template_param>
ContainerT const * hryky::WithIteration<hryky_template_arg>::container() const
{
	return static_cast<ContainerT const *>(this);
}
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
#endif // WITH_ITERATION_H_20130518152338308
// end of file
