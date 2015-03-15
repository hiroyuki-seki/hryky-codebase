/**
  @file         writer_adapter.h
  @brief        mediates the interface of writer::Base.
  @author       HRYKY
  @version      $Id: writer_adapter.h 331 2014-03-09 06:44:48Z hryky.private@gmail.com $
 */
#ifndef WRITER_ADAPTER_H_20130204223004604
#define WRITER_ADAPTER_H_20130204223004604
#include "hryky/adapter.h"
#include "hryky/writer/writer_base.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace writer
{
	/// mediates the interface of writer::Base.
	template <typename ClientT>
	class Adapter;

} // namespace writer
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief mediates the interface of writer::Base.
 */
template <typename ClientT>
class hryky::writer::Adapter
	: public hryky::Adapter<writer::Base, ClientT>
{
public :

	typedef hryky::Adapter<writer::Base, ClientT> base_type;

	typedef Adapter<ClientT> this_type;

	/// writes out an arbitrary data.
	virtual bool operator()(void const * data, size_t const size);

protected :

private :

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace writer
{
} // namespace writer
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief writes out an arbitrary data.
 */
template <typename ClientT>
bool hryky::writer::Adapter<ClientT>::operator()(
	void const * data, size_t const size)
{
	return this->get()(data, size);
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
namespace writer
{
} // namespace writer
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // WRITER_ADAPTER_H_20130204223004604
// end of file
