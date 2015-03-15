/**
  @file     aligned_buffer.h
  @brief    retains a buffer aligned on the specified boundary.
  @author   HRYKY
  @version  $Id: aligned_buffer.h 371 2014-07-22 15:08:20Z hryky.private@gmail.com $
 */
#ifndef ALIGNED_BUFFER_H_20140722183307439
#define ALIGNED_BUFFER_H_20140722183307439
#include "hryky/aligned_on.h"
#include "hryky/tmp/tmp_binary_logarithm.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	size_t Size, size_t AlignedExponent
#define hryky_template_arg \
	Size, AlignedExponent
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retains a buffer aligned on the specified boundary.
	template <
		size_t Size,
		size_t AlignedExponent = tmp::BinaryLogarithmC<sizeof(size_t)>::value
	>
	class AlignedBuffer;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a buffer aligned on the specified boundary.
  This class should be POD.
 */
template <hryky_template_param>
class hryky::AlignedBuffer
{
public :

	typedef AlignedBuffer<hryky_template_arg> this_type;

	typedef uint8_t buffer_type[Size];
	
	/// retrieves the mutable buffer.
	void * get();

	/// retrieves the immutable buffer.
	void const * get() const;

	union
	{
		buffer_type buffer_;
		typename AlignedOn<AlignedExponent>::type aligned_;
	};
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
  @brief retrieves the mutable buffer.
 */
template <hryky_template_param>
void * hryky::AlignedBuffer<hryky_template_arg>::get()
{
	return &this->buffer_[0];
}
/**
  @brief retrieves the immutable buffer.
 */
template <hryky_template_param>
void const * hryky::AlignedBuffer<hryky_template_arg>::get() const
{
	return &this->buffer_[0];
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
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // ALIGNED_BUFFER_H_20140722183307439
// end of file
