/**
  @file     without_placement_new.h
  @brief    prevents a user from using placement new.
  @author   HRYKY
  @version  $Id: without_placement_new.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef WITHOUT_PLACEMENT_NEW_H_20140310085216036
#define WITHOUT_PLACEMENT_NEW_H_20140310085216036
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
	/// prevents a user from using placement new.
	class WithoutPlacementNew;

} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief prevents a user from using placement new.
 */
class hryky::WithoutPlacementNew
{
private :
	static void * operator new(::std::size_t, void *);
	static void * operator new[](::std::size_t, void *);

	static void operator delete(void *, void *);
	static void operator delete[](void *, void *);
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
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // WITHOUT_PLACEMENT_NEW_H_20140310085216036
// end of file
