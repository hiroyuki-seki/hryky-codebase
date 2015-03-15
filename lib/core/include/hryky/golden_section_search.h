/**
  @file     golden_section_search.h
  @brief    finds the minimum of an unimodal function between the specified range.
  @author   HRYKY
  @version  $Id: golden_section_search.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef GOLDEN_SECTION_SEARCH_H_20140111162405350
#define GOLDEN_SECTION_SEARCH_H_20140111162405350
#include "hryky/golden_ratio.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename FunctionT
#define hryky_template_arg \
	FunctionT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// finds the minimum of an unimodal function between the specified range.
	template <hryky_template_param>
	class GoldenSectionSearch;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief finds the minimum of an unimodal function between the specified range.
 */
template <typename FunctionT>
class hryky::GoldenSectionSearch
{
public :

	typedef GoldenSectionSearch<hryky_template_arg> this_type;

	/// default constructor.
	GoldenSectionSearch();

	/// copy constructor.
	GoldenSectionSearch(this_type const &);

	/// move constructor.
	GoldenSectionSearch(this_type &&);

	/// destructor.
	~GoldenSectionSearch();

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

protected :

private :

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

	/// finds the minimum of an unimodal function between the specified range.
	template <
		typename DomainT,
		typename FunctorT,
		typename TerminatorT
	>
	void golden_section_search(
		DomainT first,
		DomainT last,
		FunctorT const & functor,
		TerminatorT const & terminator);

	/// finds the minimum of an unimodal function between the specified range.
	template <
		typename DomainT,
		typename CodomainT,
		typename FunctorT,
		typename TerminatorT
	>
	void golden_section_search(
		DomainT first,
		CodomainT first_y,
		DomainT last,
		CodomainT last_y,
		FunctorT const & functor,
		TerminatorT const & terminator);

} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief finds the minimum of an unimodal function between the specified range.
 */
template <
	typename DomainT,
	typename FunctorT,
	typename TerminatorT
>
void hryky::golden_section_search(
	DomainT first,
	DomainT last,
	FunctorT const & functor,
	TerminatorT const & terminator)
{
	golden_section_search(
		first, functor(first), last, functor(last), functor, terminator);
}
/**
  @brief finds the minimum of an unimodal function between the specified range.
 */
template <
	typename DomainT,
	typename CodomainT,
	typename FunctorT,
	typename TerminatorT
>
void hryky::golden_section_search(
	DomainT first,
	CodomainT first_y,
	DomainT last,
	CodomainT last_y,
	FunctorT const & functor,
	TerminatorT const & terminator)
{
	if (terminator(first, first_y, last, last_y)) {
		return;
	}
	
	typedef decltype(functor(DomainT())) result_type;

	DomainT const third = hryky::golden_ratio(first, last);

	result_type const third_y = functor(third);

	DomainT const second = first + (last - third);

	result_type const second_y = functor(second);

	if (second_y < third_y) {
		golden_section_search(
			first, first_y, third, third_y, functor, terminator);
	}
	else {
		golden_section_search(
			second, second_y, last, last_y, functor, terminator);
	}

}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // GOLDEN_SECTION_SEARCH_H_20140111162405350
// end of file
