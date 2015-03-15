/**
  @file     shader_storage.h
  @brief    qualifies a variable as interface between GPU and CPU.
  @author   HRYKY
  @version  $Id: shader_storage.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_STORAGE_H_20140821163734359
#define SHADER_STORAGE_H_20140821163734359
#include "hryky/kind.h"
#include "hryky/shader/shader_with_code.h"
#include "hryky/with_stream_out.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// qualifies a variable as interface between GPU and CPU.
	class Storage;

	typedef Storage storage_type;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief qualifies a variable as interface between GPU and CPU.
 */
class hryky::shader::Storage :
	public WithCode<Storage>,
	public WithStreamOut<Storage>
{
public :
	
	struct Kind
	{
		enum Raw
		{
			none,
			in,
			out,
			uniform,
			num,
		};
		static LiteralString<> const tokens[Kind::num];
	};
	typedef hryky::Kind<
		Kind, Kind::none, Kind::num, LiteralString<>, Kind::tokens>
			kind_type;

	typedef Storage this_type;

	/// default constructor.
	Storage();

	/// creates an instance with the kind.
	Storage(Kind::Raw const & kind);

	/// copy constructor.
	Storage(this_type const &);

	/// move constructor.
	Storage(this_type &&);

	/// destructor.
	~Storage();

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

	/// writes out the Storage Qualifier.
	Coder & code(Coder & coder) const;
	
protected :

private :

	kind_type kind_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief outputs the information through stream.
 */
template <typename StreamT>
StreamT &
hryky::shader::Storage::write_to(StreamT & out) const
{
	return out << this->kind_;
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
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_STORAGE_H_20140821163734359
// end of file
