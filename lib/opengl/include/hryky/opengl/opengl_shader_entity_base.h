/**
  @file     opengl_shader_entity_base.h
  @brief    retains a shader object.
  @author   HRYKY
  @version  $Id: opengl_shader_entity_base.h 377 2014-08-15 02:49:04Z hryky.private@gmail.com $
 */
#ifndef OPENGL_SHADER_ENTITY_BASE_H_20140109225027618
#define OPENGL_SHADER_ENTITY_BASE_H_20140109225027618
#include "hryky/scoped_registry.h"
#include "hryky/opengl/opengl_common.h"
#include "hryky/opengl/opengl_raw_common.h"
#include "hryky/is_null.h"
#include "hryky/with_is_null.h"
#include "hryky/log.h"
#include "hryky/stream/stream_endl.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename DerivedT
#define hryky_template_arg \
	DerivedT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace shader
{
	class Module;
	
namespace entity
{
	/// retains a shader object.
	template <hryky_template_param>
	class Base;

} // namespace entity
} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief retains a shader object.
 */
template <hryky_template_param>
class hryky::opengl::shader::entity::Base :
	public WithIsNull<Base<hryky_template_arg> >
{
public :
	typedef Base<hryky_template_arg> this_type;
	typedef Module const * module_type;

	/// confirms the shader object is not acquired.
	bool is_null() const;

protected :

	/// constructs with the shader module.
	Base(module_type const module);

	/// move constructor.
	Base(this_type &&);

	/// destructor.
	~Base();

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

private :
	hryky_delete_default_constructor(Base);
	hryky_delete_this_copy_constructor(Base);
	hryky_delete_this_copy_assign_op(Base);

	typedef raw::shader_type raw_type;

	/// creates a new shader object.
	bool reset();

	/// retrieves this mutable instance as the derived class.
	DerivedT & derived();

	/// retrieves this immutable instance as the derived class.
	DerivedT const & derived() const;

	module_type     module_;
	raw_type        raw_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace shader
{
namespace entity
{
} // namespace entity
} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief confirms the shader object is not acquired.
 */
template <hryky_template_param>
bool
hryky::opengl::shader::entity::Base<hryky_template_arg>::is_null() const
{
	return opengl::raw::g_invalid_shader == this->raw_;
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
/**
  @brief constructs with the shader module.
 */
template <hryky_template_param>
hryky::opengl::shader::entity::Base<hryky_template_arg>::Base(
	module_type const module)
	: module_(module)
	  , raw_()
{
	if (!this->reset()) {
		hryky_log_err("failed to create OpenGL Shader Object.");
		return;
	}
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::opengl::shader::entity::Base<hryky_template_arg>::Base(
	this_type && rhs)
	: hryky_move_member(module)
	  , hryky_move_member(raw)
{
	rhs.raw_ = raw::g_invalid_shader;
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::opengl::shader::entity::Base<hryky_template_arg>::~Base()
{
	this->clear();
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void
hryky::opengl::shader::entity::Base<hryky_template_arg>::clear()
{
	if (!hryky_is_null(this->module_)) {
		this->module_->delete_raw_shader(this->raw_);
	}
	hryky::clear(this->raw_);
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT & 
hryky::opengl::shader::entity::Base<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	hryky_write_member(module);
	hryky_write_member(raw);

	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::opengl::shader::entity::Base<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(module);
	hryky_swap_member(raw);
}
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief creates a new shader object.
 */
template <hryky_template_param>
bool hryky::opengl::shader::entity::Base<hryky_template_arg>::reset()
{
	if (hryky_is_null(this->module_)) {
		return false;
	}

	raw_type const raw =
		this->module_->new_raw_shader(DerivedT::raw_kind);

	if (opengl::raw::g_invalid_shader == raw) {
		return false;
	}

	this->clear();
	
	this->raw_ = raw;
	
	return true;
}
/**
  @brief retrieves this mutable instance as the derived class.
 */
template <hryky_template_param>
DerivedT &
hryky::opengl::shader::entity::Base<hryky_template_arg>::derived()
{
	return *static_cast<DerivedT *>(this);
}
/**
  @brief retrieves this immutable instance as the derived class.
 */
template <hryky_template_param>
DerivedT const & 
hryky::opengl::shader::entity::Base<hryky_template_arg>::derived() const
{
	return *static_cast<DerivedT const *>(this);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace opengl
{
namespace shader
{
namespace entity
{
} // namespace entity
} // namespace shader
} // namespace opengl
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // OPENGL_SHADER_ENTITY_BASE_H_20140109225027618
// end of file
