/**
  @file     rtiow_segment.h
  @brief    retains a segment.
  @author   HRYKY
  @version  $Id: hryky-template.l 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef RTIOW_SEGMENT_H_20160717151849304
#define RTIOW_SEGMENT_H_20160717151849304
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename VectorT
#define hryky_template_arg \
	VectorT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
	/// retains a segment.
	template <hryky_template_param>
	class Segment;

} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a segment.
 */
template <typename VectorT = hryky::rtiow::Vec3<> >
class hryky::rtiow::Segment
{
public :

	typedef Segment<hryky_template_arg> this_type;
	typedef VectorT vector_type;

	/// default constructor.
	Segment();

	/// constructor.
	Segment(VectorT const & origin, VectorT const & direction);

	/// copy constructor.
	Segment(this_type const &);

	/// move constructor.
	Segment(this_type &&);

	/// destructor.
	~Segment();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information through stream.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// retrieves the origin of this directional segment.
	VectorT const & origin() const;

	/// retrieves the direction of this directional segment.
	VectorT const & direction() const;

	/// confirms whether an rate is valid.
	template <typename RateT>
	bool verify(RateT const & rate) const;

	/// retrieves the point on the line.
	template <typename RateT>
	vector_type point(RateT rate) const;

protected :

private :

	VectorT origin_;
	VectorT direction_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::rtiow::Segment<hryky_template_arg>::Segment()
{
}
/**
  @brief constructor.
 */
template <hryky_template_param>
hryky::rtiow::Segment<hryky_template_arg>::Segment(
	VectorT const & origin, VectorT const & direction)
	: origin_(origin)
	  , direction_(direction)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::rtiow::Segment<hryky_template_arg>::Segment(this_type const & rhs)
	: hryky_copy_member(origin)
	  , hryky_copy_member(direction)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::rtiow::Segment<hryky_template_arg>::Segment(this_type && rhs)
	: hryky_move_member(origin)
	  , hryky_move_member(direction)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::rtiow::Segment<hryky_template_arg>::~Segment()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::rtiow::Segment<hryky_template_arg>::clear()
{
	hryky::clear(direction);
	hryky::clear(origin);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::rtiow::Segment<hryky_template_arg>::swap(this_type & src)
{
	hryky_swap_member(origin);
	hryky_swap_member(direction);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & hryky::rtiow::Segment<hryky_template_arg>::write_to(
	StreamT & out) const
{
	return out;
}
/**
  @brief retrieves the origin of this directional segment.
 */
template <hryky_template_param>
typename hryky::rtiow::Segment<hryky_template_arg>::vector_type const &
hryky::rtiow::Segment<hryky_template_arg>::origin() const
{
	return this->origin_;
}
/**
  @brief retrieves the direction of this directional segment.
 */
template <hryky_template_param>
typename hryky::rtiow::Segment<hryky_template_arg>::vector_type const &
hryky::rtiow::Segment<hryky_template_arg>::direction() const
{
	return this->direction_;
}
/**
  @brief retrieves the point on the line.
 */
template <hryky_template_param>
template <typename RateT>
typename hryky::rtiow::Segment<hryky_template_arg>::vector_type 
hryky::rtiow::Segment<hryky_template_arg>::point(RateT rate) const
{
	return this->origin() + rate * this->direction();
}
/**
  @brief confirms whether an rate is valid.
 */
template <hryky_template_param>
template <typename RateT>
bool hryky::rtiow::Segment<hryky_template_arg>::verify(
	RateT const & rate) const
{
	return 0.0f < rate && 1.0f > rate;
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
namespace rtiow
{
} // namespace rtiow
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RTIOW_SEGMENT_H_20160717151849304
// end of file
