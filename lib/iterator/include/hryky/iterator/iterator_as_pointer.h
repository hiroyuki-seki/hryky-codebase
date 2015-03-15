/**
  @file     iterator_as_pointer.h
  @brief    dereference as a pointer.
  @author   HRYKY
  @version  $Id: iterator_as_pointer.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef ITERATOR_AS_POINTER_H_20130331104050111
#define ITERATOR_AS_POINTER_H_20130331104050111
#include "hryky/definition.h"
#include "hryky/clear.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ClientT
#define hryky_template_arg \
	ClientT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
	/// dereference as a pointer.
	template <hryky_template_param>
	class AsPointer;

} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief dereference as a pointer.
 */
template <hryky_template_param>
class hryky::iterator::AsPointer :
	public ::std::iterator<
		::std::random_access_iterator_tag,
		typename ClientT::value_type,
		typename ClientT::difference_type,
		typename ClientT::pointer,
		typename ClientT::pointer>,
	public WithStreamOut<AsPointer<hryky_template_arg> >,
	public WithSwap<AsPointer<hryky_template_arg> >
{
public :

	typedef AsPointer<hryky_template_arg> this_type;

	/// default constructor.
	AsPointer();

	/// constructor the value of client.
	AsPointer(ClientT const & client);

	/// copy constructor.
	AsPointer(this_type const &);

	/// move constructor.
	AsPointer(this_type &&);

	/// destructor.
	~AsPointer();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// confirms the equality between two instances.
	bool operator==(this_type const & rhs) const;

	/// confirms the inequality between two instances.
	bool operator!=(this_type const & rhs) const;

	/// confirms whether this is less than the other.
	bool operator<(this_type const & rhs) const;

	/// confirms whether this is greater than the other.
	bool operator>(this_type const & rhs) const;

	/// confirms whether this is less than or equal to the other.
	bool operator<=(this_type const & rhs) const;

	/// confirms whether this is greater than or equal to the other.
	bool operator>=(this_type const & rhs) const;

	/// dereferences the client as a pointer.
	pointer operator->() const;

	/// dereferences the client as a pointer anomaly.
	reference operator*() const;

	/// pre-increments the client.
	this_type & operator++();

	/// post-increments the client.
	this_type operator++(int);

	/// pre-decrements the client.
	this_type & operator--();

	/// post-decrements the client.
	this_type operator--(int);

	/// retrieves a new forwarded iterator.
	this_type operator+(difference_type const rhs) const;

	/// retrieves a new rewound iterator.
	this_type operator-(difference_type const rhs) const;

	/// measures the distance between two iterators.
	difference_type operator-(this_type const & rhs) const;

	/// forwards the client.
	this_type & operator+=(difference_type const rhs);

	/// rewinds the client.
	this_type & operator-=(difference_type const rhs);

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	ClientT client_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace iterator
{
} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg>::AsPointer()
	: client_()
{
}
/**
  @brief constructor the value of client.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg>::AsPointer(ClientT const & client)
	: client_(client)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg>::AsPointer(this_type const & rhs)
	: hryky_copy_member(client)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg>::AsPointer(this_type && rhs)
	: hryky_move_member(client)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg>::~AsPointer()
{
}
/**
  @brief confirms the equality between two instances.
 */
template <hryky_template_param>
bool hryky::iterator::AsPointer<hryky_template_arg>::operator==(
	this_type const & rhs) const
{
	return this->client_ == rhs.client_;
}
/**
  @brief confirms the inequality between two instances.
 */
template <hryky_template_param>
bool hryky::iterator::AsPointer<hryky_template_arg>::operator!=(
	this_type const & rhs) const
{
	return this->client_ != rhs.client_;
}
/**
  @brief confirms whether this is less than the other.
 */
template <hryky_template_param>
bool hryky::iterator::AsPointer<hryky_template_arg>::operator<(
	this_type const & rhs) const
{
	return this->client_ < rhs.client_;
}
/**
  @brief confirms whether this is greater than the other.
 */
template <hryky_template_param>
bool hryky::iterator::AsPointer<hryky_template_arg>::operator>(
	this_type const & rhs) const
{
	return this->client_ > rhs.client_;
}
/**
  @brief confirms whether this is less than or equal to the other.
 */
template <hryky_template_param>
bool hryky::iterator::AsPointer<hryky_template_arg>::operator<=(
	this_type const & rhs) const
{
	return this->client_ <= rhs.client_;
}
/**
  @brief confirms whether this is greater than or equal to the other.
 */
template <hryky_template_param>
bool hryky::iterator::AsPointer<hryky_template_arg>::operator>=(
	this_type const & rhs) const
{
	return this->client_ <= rhs.client_;
}
/**
  @brief dereferences the client as a pointer.
 */
template <hryky_template_param>
typename hryky::iterator::AsPointer<hryky_template_arg>::pointer 
hryky::iterator::AsPointer<hryky_template_arg>::operator->() const
{
	return this->client_.operator->();
}
/**
  @brief dereferences the client as a pointer anomaly.
 */
template <hryky_template_param>
typename hryky::iterator::AsPointer<hryky_template_arg>::reference
hryky::iterator::AsPointer<hryky_template_arg>::operator*() const
{
	return this->client_.operator->();
}
/**
  @brief pre-increments the client.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg> & 
hryky::iterator::AsPointer<hryky_template_arg>::operator++()
{
	++this->client_;
	return *this;
}
/**
  @brief post-increments the client.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg>
hryky::iterator::AsPointer<hryky_template_arg>::operator++(int)
{
	this_type const ret(*this);
	++this->client_;
	return ret;
}
/**
  @brief pre-decrements the client.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg> & 
hryky::iterator::AsPointer<hryky_template_arg>::operator--()
{
	--this->client_;
	return *this;
}
/**
  @brief post-decrements the client.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg>
hryky::iterator::AsPointer<hryky_template_arg>::operator--(int)
{
	this_type const ret(*this);
	--this->client_;
	return ret;
}
/**
  @brief retrieves a new forwarded iterator.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg> 
hryky::iterator::AsPointer<hryky_template_arg>::operator+(
	difference_type const rhs) const
{
	return this_type(this->client_ + rhs);
}
/**
  @brief retrieves a new rewound iterator.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg> 
hryky::iterator::AsPointer<hryky_template_arg>::operator-(
	difference_type const rhs) const
{
	return this_type(this->client_ - rhs);
}
/**
  @brief measures the distance between two iterators.
 */
template <hryky_template_param>
typename hryky::iterator::AsPointer<hryky_template_arg>::difference_type
hryky::iterator::AsPointer<hryky_template_arg>::operator-(
	this_type const & rhs) const
{
	return this->client_ - rhs.client_;
}
/**
  @brief forwards the client.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg> & 
hryky::iterator::AsPointer<hryky_template_arg>::operator+=(
	difference_type const rhs)
{
	this->client_ += rhs;
	return *this;
}
/**
  @brief rewinds the client.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg> & 
hryky::iterator::AsPointer<hryky_template_arg>::operator-=(
	difference_type const rhs)
{
	this->client_ -= rhs;
	return *this;
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::iterator::AsPointer<hryky_template_arg>::clear()
{
	hryky::clear(this->client_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::iterator::AsPointer<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(client);

	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::iterator::AsPointer<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(client);
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
namespace iterator
{

	/// instantiates a new iterator to dereference the other iterator as pointer.
	template <hryky_template_param>
	AsPointer<hryky_template_arg> as_pointer(ClientT const & client);

} // namespace iterator
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief instantiates a new iterator to dereference the other iterator as pointer.
 */
template <hryky_template_param>
hryky::iterator::AsPointer<hryky_template_arg> hryky::iterator::as_pointer(
	ClientT const & client)
{
	return AsPointer<hryky_template_arg>(client);
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ITERATOR_AS_POINTER_H_20130331104050111
// end of file
