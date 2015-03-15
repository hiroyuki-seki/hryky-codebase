/**
  @file         log_level_entity.h
  @brief        the level of logging depending on the severity and purpose.
  @author       HRYKY
  @version      $Id: log_level_entity.h 337 2014-03-23 14:12:33Z hryky.private@gmail.com $
 */
#ifndef LOG_LEVEL_ENTITY_H_20120121111702136
#define LOG_LEVEL_ENTITY_H_20120121111702136
#include "hryky/literal_string.h"
#include "hryky/log/log_level_common.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace log
{
namespace level
{
	/// the level of logging depending on the severity and purpose.
	class Entity;

} // namespace level

typedef level::Entity level_type;

} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief the level of logging depending on the severity and purpose.
 */
class hryky::log::level::Entity :
	public WithStreamOut<Entity>
{
public :

	/// self.
	typedef hryky::log::level::Entity this_type;

	/// default constructor.
	Entity();

	/// constructor with a level.
	explicit Entity(Kind::Raw const kind);

	/// copy constructor.
	explicit Entity(Entity const &);

	/// move constructor.
	Entity(this_type && rhs);

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// destructor.
	~Entity();

	/// retrieves the null terminated string which represents the log level.
	LiteralString<> const & str() const;

	/// confirms that this level is less than the other level.
	bool operator<(this_type const & rhs) const;

	/// confirms that this level is more than the other level.
	bool operator>(this_type const & rhs) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs the information of log::level::Entity.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

protected :

private :

	kind_type   kind_;

};
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information of log::level::Entity.
 */
template <typename StreamT>
StreamT &
hryky::log::level::Entity::write_to(StreamT & out) const
{
	out << this->kind_ << " : ";
	
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
namespace log
{
namespace level
{
} // namespace level
} // namespace log
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // LOG_LEVEL_ENTITY_H_20120121111702136
// end of file
