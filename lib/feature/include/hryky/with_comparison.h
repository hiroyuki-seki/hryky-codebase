/**
  @file     with_comparison.h
  @brief    provides the functions to compare two containers.
  @author   HRYKY
  @version  $Id: with_comparison.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef WITH_COMPARISON_H_20130915235515663
#define WITH_COMPARISON_H_20130915235515663
#include "hryky/std/std_functional.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, typename ConstIteratorT
#define hryky_template_arg \
	ContainerT, ConstIteratorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// provides the functions to compare two containers.
	template <hryky_template_param>
	class WithComparison;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief provides the functions to compare two containers.

  This feature has to be derived with the WithIterator class.
 */
template <
	typename ContainerT,
	typename ConstIteratorT = typename ContainerT::const_iterator
>
class hryky::WithComparison
{
public :

	/// confirms the equality between two instances.
	bool operator==(ContainerT const & rhs) const;

	/// confirms the inequality between two instances.
	bool operator!=(ContainerT const & rhs) const;

	/// confirms whether this instance is less than an other.
	bool operator<(ContainerT const & rhs) const;

	/// confirms whether this instance is greater than an other.
	bool operator>(ContainerT const & rhs) const;

	/// confirms whether this instance is less than or equal to an other.
	bool operator<=(ContainerT const & rhs) const;

	/// confirms whether this instance is greater than or equal to an other.
	bool operator>=(ContainerT const & rhs) const;

protected :

private :

	/// retrieves the beginning iterator.
	ConstIterator begin() const;

	/// retrieves the end iterator.
	ConstIterator end() const;

	/// retrieves the size of the container.
	typename ContainerT::size_type size() const;

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
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool
hryky::WithComparison<hryky_template_arg>::operator==(
	ContainerT const & rhs) const
{
	return this->size() == rhs.size() &&
		::std::equal(this->begin(), this->end(), rhs.begin());
}
/**
  @brief confirms the inequality between two instances.
 */
template <hryky_template_param>
bool
hryky::WithComparison<hryky_template_arg>::operator!=(
	ContainerT const & rhs) const
{
	return !this->operator==(rhs);
}
/**
  @brief confirms whether this instance is less than an other.
 */
template <hryky_template_param>
bool
hryky::WithComparison<hryky_template_arg>::operator<(
	ContainerT const & rhs) const
{
	if (this->size() < rhs.size()) {
		ConstIteratorT lhs_itr = this->begin();
		ConstIteratorT rhs_itr = rhs.begin();
		ConstIteratorT const lhs_end = this->end();
		for (; lhs_end != lhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr < *rhs_itr) {
				return true;
			}
			else if (*lhs_itr > *rhs_itr) {
				return false;
			}
		}
		return true;
	}
	else {
		ConstIteratorT lhs_itr = this->begin();
		ConstIteratorT rhs_itr = rhs.begin();
		ConstIteratorT const rhs_end = rhs.end();
		for (; rhs_end != rhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr < *rhs_itr) {
				return true;
			}
			else if (*lhs_itr > *rhs_itr) {
				return false;
			}
		}
		return false;
	}
}
/**
  @brief confirms whether this instance is greater than an other.
 */
template <hryky_template_param>
bool
hryky::WithComparison<hryky_template_arg>::operator>(
	ContainerT const & rhs) const
{
	if (this->size() > rhs.size()) {
		ConstIteratorT lhs_itr = this->begin();
		ConstIteratorT rhs_itr = rhs.begin();
		ConstIteratorT const rhs_end = rhs.end();
		for (; rhs_end != rhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr > *rhs_itr) {
				return true;
			}
			else if (*lhs_itr < *rhs_itr) {
				return false;
			}
		}
		return true;
	}
	else {
		ConstIteratorT lhs_itr = this->begin();
		ConstIteratorT rhs_itr = rhs.begin();
		ConstIteratorT const lhs_end = this->end();
		for (; lhs_end != lhs_itr; ++lhs_itr, ++rhs_itr) {
			if (*lhs_itr > *rhs_itr) {
				return true;
			}
			else if (*lhs_itr < *rhs_itr) {
				return false;
			}
		}
		return false;
	}
}
/**
  @brief confirms whether this instance is less than or equal to an other.
 */
template <hryky_template_param>
bool
hryky::WithComparison<hryky_template_arg>::operator<=(
	ContainerT const & rhs) const
{
	return !this->operator>(rhs);
}
/**
  @brief confirms whether this instance is greater than or equal to an other.
 */
template <hryky_template_param>
bool
hryky::WithComparison<hryky_template_arg>::operator>=(
	ContainerT const & rhs) const
{
	return !this->operator<(rhs);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief retrieves the beginning iterator.
 */
template <hryky_template_param>
ConstIterator hryky::WithComparison<hryky_template_arg>::begin() const
{
	return this->container()->begin();
}
/**
  @brief retrieves the end iterator.
 */
template <hryky_template_param>
ConstIterator hryky::WithComparison<hryky_template_arg>::end() const
{
	return this->container()->end();
}
/**
  @brief retrieves the size of the container.
 */
template <hryky_template_param>
typename ContainerT::size_type 
hryky::WithComparison<hryky_template_arg>::size() const
{
	return this->container()->size();
}
/**
  @brief retrieves the immutable instance of the derived class.
 */
template <hryky_template_param>
ContainerT const * hryky::WithComparison<hryky_template_arg>::container() const
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
#endif // WITH_COMPARISON_H_20130915235515663
// end of file
