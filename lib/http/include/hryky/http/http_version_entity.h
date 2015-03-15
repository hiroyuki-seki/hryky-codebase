/**
  @file         http_version_entity.h
  @brief        retains HTTP-Version.
  @author       HRYKY
  @version      $Id: http_version_entity.h 325 2014-02-09 12:37:53Z hryky.private@gmail.com $
 */
#ifndef HTTP_VERSION_ENTITY_H_20120722220318585
#define HTTP_VERSION_ENTITY_H_20120722220318585
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace version
{
	/// retains HTTP-Version.
	class Entity;

} // namespace version

typedef version::Entity version_type;

} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains HTTP-Version.
 */
class hryky::http::version::Entity :
	public WithStreamOut<Entity>,
	public WithSwap<Entity>
{
public :

	typedef Entity      this_type;
	typedef uint16_t    major_type;
	typedef uint16_t    minor_type;
	
	/// default constructor.
	Entity();

	/// constructor with version number.
	Entity(major_type const major, minor_type const minor);

	/// releases the internal resources.
	void clear();

	/// reinitializes the instance.
	void assign(major_type const major, minor_type const minor);

	/// retrieves the major number of HTTP-Version.
	major_type major() const;

	/// retrieves the minor number of HTTP-Version.
	minor_type minor() const;

	/// format the information of http::version::Entity as string.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :

	major_type  major_;
	minor_type  minor_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace http
{
namespace version
{
} // namespace version
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief format the information of http::version::Entity as string.
 */
template <typename StreamT>
StreamT &
hryky::http::version::Entity::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);

	hryky_write_member(major);
	hryky_write_member(minor);
	
	return out;
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
namespace http
{
namespace version
{
} // namespace version
} // namespace http
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // HTTP_VERSION_ENTITY_H_20120722220319585
// end of file
