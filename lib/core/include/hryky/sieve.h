/**
  @file         sieve.h
  @brief        narrows down candidates by sequence of values.
  @author       HRYKY
  @version      $Id: sieve.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef SIEVE_H_20120922201005507
#define SIEVE_H_20120922201005507
#include "hryky/fixed_vector.h"
#include "hryky/foreach.h"
#include "hryky/range.h"
#include "hryky/type_traits/value_type_of.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ResultT, size_t Size
#define hryky_template_arg \
	ResultT, Size
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// narrows down candidates by sequence of values.
	template <hryky_template_param>
	class Sieve;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief narrows down candidates by sequence of values.

  struct Kind
  {
    struct Raw
    {
        foo,
        bar,
        foofoo,
        foobar,
        num,
    };
  };

  char const * const tokens[] = {
    "foo", "bar", "foofoo", "fobar",
  };

  Sieve<Kind> sieve;
  ::std::cout << sieve.candidates(); // => [foo, bar, foofoo, fobar]
  sieve('f', tokens);
  ::std::cout << sieve.candidates(); // => [foo, foofoo, fobar]
  sieve('o', tokens);
  ::std::cout << sieve.candidates(); // => [foo, foofoo, fobar]
  sieve('o', tokens);
  ::std::cout << sieve.candidates(); // => [foo, foofoo]
  sieve('f', tokens);
  ::std::cout << sieve.candidates(); // => [foofoo]
 */
template < typename ResultT, size_t Size = ResultT::num >
class hryky::Sieve :
	public WithStreamOut<Sieve<hryky_template_arg> >,
	public WithSwap<Sieve<hryky_template_arg> >
{
public :

	typedef Sieve<hryky_template_arg>   this_type;
	typedef typename ResultT::raw_type  raw_type;
	typedef FixedVector<raw_type, Size> candidates_type;
	typedef ResultT                     result_type;

	/// default constructor.
	Sieve();

	/// copy constructor.
	Sieve(this_type const &);

	/// move constructor.
	Sieve(this_type && rhs);

	/// destructor.
	~Sieve();

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

	/**
	  @brief narrows down candidates by a value.
	  @param src    is a value of sequence.
	  @param tokens is the container of compared tokens.
	  @param equal  is the predicate confirming the equality.
	  @return       the number of candidates narrowed down by @a src.

	  TokensT must have operator[] to retrieve a value compared to src.
	 */
	template <typename ValueT, typename TokensT, typename EqualT>
	size_t operator()(
		ValueT const src, TokensT const & tokens, EqualT const & equal);

	/**
	  @brief narrows down candidates with operator== as a predicate.
	 */
	template <typename ValueT, typename TokensT>
	size_t operator()(
		ValueT const src, TokensT const & tokens);

	/**
	  @brief narrows down candidates by the range of values.
	 */
	template <typename InputIteratorT, typename TokensT, typename EqualT>
	size_t operator()(
		InputIteratorT begin,
		InputIteratorT end,
		TokensT const & tokens,
		EqualT const & equal);

	/**
	  @brief narrows down candidates with operator== as a predicate.
	 */
	template <typename InputIteratorT, typename TokensT>
	size_t operator()(
		InputIteratorT begin,
		InputIteratorT end,
		TokensT const & tokens);

	/// retrieves the result of narrowing.
	result_type result() const;

	/// retrieves the current length of read values.
	size_t length() const;

	/// retrieves the current candidates.
	candidates_type const & candidates();

	/// confirmes whether there is one candicate.
	bool determined() const;

protected :

private :

	/// resets the container of candidates.
	void clear_candidates();

	candidates_type candidates_;
	result_type     result_;
	size_t          length_;

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
hryky::Sieve<hryky_template_arg>::Sieve()
	: candidates_()
	  , result_()
	  , length_()
{
	this->clear_candidates();
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::Sieve<hryky_template_arg>::Sieve(this_type const & rhs)
	: hryky_copy_member(candidates)
	  , hryky_copy_member(result)
	  , hryky_copy_member(length)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::Sieve<hryky_template_arg>::Sieve(this_type && rhs)
	: hryky_move_member(candidates)
	  , hryky_move_member(result)
	  , hryky_move_member(length)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::Sieve<hryky_template_arg>::~Sieve()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::Sieve<hryky_template_arg>::clear()
{
	hryky::clear(this->length_);
	hryky::clear(this->result_);

	this->clear_candidates();
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::Sieve<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(candidates);
	hryky_swap_member(result);
	hryky_swap_member(length);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::Sieve<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(result);
	hryky_write_member(length);
	hryky_write_member(candidates);
	
	return out;
}
/**
  @brief narrows down candidates by a value.
 */
template <hryky_template_param>
template <typename ValueT, typename TokensT>
hryky::size_t
hryky::Sieve<hryky_template_arg>::operator()(
	ValueT const src, TokensT const & tokens)
{
	return this->operator()(src, tokens, [](
		ValueT const lhs, ValueT const rhs) {
		return lhs == rhs;
	});
}
/**
  @brief narrows down candidates with a predicate confirming equality.
 */
template <hryky_template_param>
template < typename ValueT, typename TokensT, typename EqualT >
hryky::size_t
hryky::Sieve<hryky_template_arg>::operator()(
	ValueT const src,
	TokensT const & tokens,
	EqualT const & equal)
{
	candidates_type::size_type candidates_size = 0;
	result_type result;
	this->candidates_.foreach(
		[&candidates_size, &result, &tokens, &src, this, &equal](
			raw_type const kind) {
			LiteralString<> const & token = tokens[kind];

			if (token.size() <= this->length_) {
				return;
			}

			if (!equal(src, static_cast<ValueT>(token[this->length_]))) {
				return;
			}

			// overwrites the iterating container.
			this->candidates_[candidates_size++] = kind;

			if (this->length_ + 1 == token.size()) {
				result = kind;
			}
		});

	++this->length_;

	this->result_ = result;

	this->candidates_.resize(candidates_size);
	
	return candidates_size;
}
/**
  @brief narrows down candidates by the range of values with a predicate.
 */
template <hryky_template_param>
template < typename InputIteratorT, typename TokensT, typename EqualT >
hryky::size_t hryky::Sieve<hryky_template_arg>::operator()(
	InputIteratorT begin,
	InputIteratorT end,
	TokensT const & tokens,
	EqualT const & equal)
{
	typedef typename ::std::iterator_traits<InputIteratorT>::reference
		reference;
	
	hryky::range(begin, end).foreach([this, &tokens, &equal](
		reference ref) {
		(*this)(ref, tokens, equal);
	});

	return this->candidates().size();
}
/**
  @brief narrows down candidates by the range of values.
 */
template <hryky_template_param>
template < typename InputIteratorT, typename TokensT >
hryky::size_t hryky::Sieve<hryky_template_arg>::operator()(
	InputIteratorT begin, InputIteratorT end, TokensT const & tokens)
{
	typedef typename ::std::iterator_traits<InputIteratorT>::reference
		reference;
	
	hryky::range(begin, end).foreach([this, &tokens](
		reference ref) {
		(*this)(ref, tokens);
	});
	return this->candidates().size();
}
/**
  @brief retrieves the result of narrowing.
 */
template <hryky_template_param>
ResultT hryky::Sieve<hryky_template_arg>::result() const
{
	return this->result_;
}
/**
  @brief retrieves the current length of read values.
 */
template <hryky_template_param>
hryky::size_t hryky::Sieve<hryky_template_arg>::length() const
{
	return this->length_;
}
/**
  @brief retrieves the current candidates.
 */
template <hryky_template_param>
typename hryky::Sieve<hryky_template_arg>::candidates_type const & 
hryky::Sieve<hryky_template_arg>::candidates()
{
	return this->candidates_;
}
/**
  @brief confirmes whether there is one candicate.
 */
template <hryky_template_param>
bool hryky::Sieve<hryky_template_arg>::determined() const
{
	return 1u == this->candidates().size();
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief resets the container of candidates.
 */
template <hryky_template_param>
void hryky::Sieve<hryky_template_arg>::clear_candidates()
{
	this->candidates_.resize(Size);
	this->candidates_.foreach_at([](
		candidates_type::reference candidate,
		candidates_type::size_type const index) {
		candidate = static_cast<raw_type>(index);
	});
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
// defines macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SIEVE_H_20120922201005507
// end of file
