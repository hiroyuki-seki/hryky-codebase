/**
  @file     container_constructor_none.h
  @brief    skips construction and destruction for elements in container.
  @author   HRYKY
  @version  $Id: container_constructor_none.h 331 2014-03-09 06:44:48Z hryky.private@gmail.com $
 */
#ifndef CONTAINER_CONSTRUCTOR_NONE_H_20140302182128431
#define CONTAINER_CONSTRUCTOR_NONE_H_20140302182128431
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace container
{
namespace constructor
{
	/// skips construction and destruction for elements in container.
	class None;

} // namespace constructor
} // namespace container
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief skips construction and destruction for elements in container.
 */
class hryky::container::constructor::None
{
public :

	/// skips the construction of elements.
	void construct(...);

	/// skipes the destruction of elements.
	void destroy(...);

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace container
{
namespace constructor
{
} // namespace constructor
} // namespace container
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief skips the construction of elements.
 */
inline
void hryky::container::constructor::None::construct(...)
{
}
/**
  @brief skipes the destruction of elements.
 */
inline
void hryky::container::constructor::None::destroy(...)
{
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
namespace container
{
namespace constructor
{
} // namespace constructor
} // namespace container
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // CONTAINER_CONSTRUCTOR_NONE_H_20140302182128431
// end of file
