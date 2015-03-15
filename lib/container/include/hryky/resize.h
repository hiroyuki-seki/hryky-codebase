/**
  @file     resize.h
  @brief    retrieves the resized container at compile-time.
  @author   HRYKY
  @version  $Id: resize.h 324 2014-02-09 04:38:38Z hryky.private@gmail.com $
 */
#ifndef RESIZE_H_20131104161420343
#define RESIZE_H_20131104161420343
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename TargetT, size_t NewSize
#define hryky_template_arg \
	TargetT, NewSize
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// retrieves the resized container at compile-time.
	template <hryky_template_param>
	class Resize;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retrieves the resized container at compile-time.
 */
template <typename TargetT, size_t NewSize>
class hryky::Resize
{
public :
	typedef typename Resize<typename TargetT::base_type, NewSize>::type type;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
/**
  @brief retrieves new type of built-in array.
 */
template <typename ValueT, size_t OldSize, size_t NewSize>
class Resize<ValueT[OldSize], NewSize>
{
public :
	typedef ValueT type[NewSize];
};
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // RESIZE_H_20131104161420343
// end of file
