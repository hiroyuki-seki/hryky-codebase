/**
  @file     shader_layout.h
  @brief    specifies the layout of a variable.
  @author   HRYKY
  @version  $Id: shader_layout.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_LAYOUT_H_20140821212218557
#define SHADER_LAYOUT_H_20140821212218557
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
	/// specifies the layout of a variable.
	class Layout;

	typedef Layout layout_type;

	class Coder;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief specifies the layout of a variable.
 */
class hryky::shader::Layout :
	public WithCode<Layout>,
	public WithStreamOut<Layout>
{
public :

	typedef Layout this_type;

	/// default constructor.
	Layout();

	/// copy constructor.
	Layout(this_type const &);

	/// move constructor.
	Layout(this_type &&);

	/// destructor.
	~Layout();

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

	/// writes out the Layout Qualifier.
	Coder & code(Coder & coder) const;

protected :

private :

	union Value
	{
		Value()
		{
			this->local_size_.x_ = 0u;
			this->local_size_.y_ = 0u;
			this->local_size_.z_ = 0u;
		}

		struct Location
		{
			size_t index_;
			bool available_;
		} location_;

		// for Compute Shader.
		struct LocalSize
		{
			size_t x_;
			size_t y_;
			size_t z_;
		} local_size_;
		
	} value_;
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
hryky::shader::Layout::write_to(StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("location");
	{
		stream::map::Scope<StreamT> const map(out);
		(out
		 << stream::denote("index")
		 << this->value_.location_.index_
		 << stream::denote("available")
		 << this->value_.location_.available_);
	}
	out << stream::denote("local_size");
	{
		stream::map::Scope<StreamT> const map(out);
		(out
		 << stream::denote("x")
		 << this->value_.local_size_.x_
		 << stream::denote("y")
		 << this->value_.local_size_.y_
		 << stream::denote("z")
		 << this->value_.local_size_.z_);
	}
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
namespace shader
{
} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
#endif // SHADER_LAYOUT_H_20140821212218557
// end of file
