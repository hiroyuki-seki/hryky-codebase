/**
  @file     shader_declaration_of.h
  @brief    writes a adaptee as the declaration.
  @author   HRYKY
  @version  $Id: shader_declaration_of.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef SHADER_DECLARATION_OF_H_20140904222653602
#define SHADER_DECLARATION_OF_H_20140904222653602
#include "hryky/shader/shader_with_code.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename AdapteeT
#define hryky_template_arg \
	AdapteeT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace shader
{
	/// writes a adaptee as the declaration.
	template <typename AdapteeT>
	class DeclarationOf;

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief writes a adaptee as the declaration.
 */
template <hryky_template_param>
class hryky::shader::DeclarationOf :
	public WithCode<DeclarationOf<hryky_template_arg> >
{
public :

	typedef DeclarationOf<hryky_template_arg> this_type;

	/// creates an instance with the written adaptee.
	DeclarationOf(AdapteeT const & adaptee);

	/// copy constructor.
	DeclarationOf(this_type const &);

	/// move constructor.
	DeclarationOf(this_type &&);

	/// destructor.
	~DeclarationOf();

	/// writes the declaration of the adaptee.
	Coder & code(Coder & coder) const;

protected :

private :
	hryky_delete_default_constructor(DeclarationOf);
	hryky_delete_this_copy_assign_op(DeclarationOf);

	AdapteeT const & adaptee_;

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
  @brief creates an instance with the written adaptee.
 */
template <hryky_template_param>
hryky::shader::DeclarationOf<hryky_template_arg>::DeclarationOf(
	AdapteeT const & adaptee)
	: adaptee_(adaptee)
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::shader::DeclarationOf<hryky_template_arg>::DeclarationOf(
	this_type const & rhs)
	: hryky_copy_member(adaptee)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::shader::DeclarationOf<hryky_template_arg>::DeclarationOf(
	this_type && rhs)
	: hryky_move_member(rhs)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::shader::DeclarationOf<hryky_template_arg>::~DeclarationOf()
{
}
/**
  @brief writes the declaration of the adaptee.
 */
template <hryky_template_param>
hryky::shader::Coder &
hryky::shader::DeclarationOf<hryky_template_arg>::code(
	Coder & coder) const
{
	return this->adaptee_.declare(coder);
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
	/// creates an instance of DeclarationOf.
	template <hryky_template_param>
	DeclarationOf<AdapteeT> declaration_of(AdapteeT const & adaptee);

} // namespace shader
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates an instance of DeclarationOf.
 */
template <hryky_template_param>
hryky::shader::DeclarationOf<AdapteeT>
hryky::shader::declaration_of(AdapteeT const & adaptee)
{
	return DeclarationOf<AdapteeT>(adaptee);
}
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // SHADER_DECLARATION_OF_H_20140904222653602
// end of file
