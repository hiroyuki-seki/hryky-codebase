/**
  @file         definition.h
  @brief        utilities for the definition of class.
  @author       HRYKY
  @version      $Id: definition.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef DEFINITION_H_20130317183829443
#define DEFINITION_H_20130317183829443
#if HRYKY_USE_CONFIG_H
#   include "hryky/config.h"
#endif
#include "hryky/std/std_utility.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#if defined(__GNUC__)
#   define hryky_gcc_version \
	    ((__GNUC__ * 10000) + (__GNUC_MINOR__ * 100) + (__GNUC_PATCHLEVEL__))
#else
#   define hryky_gcc_version (0)
#endif

#if defined(_MSC_VER)
#   if _MSC_VER == 1900
#       define hryky_msvs_ver (2015)
#       define hryky_msvc_ver (14)
#   elif _MSC_VER == 1800
#       define hryky_msvs_ver (2013)
#       define hryky_msvc_ver (12)
#   elif _MSC_VER == 1700
#       define hryky_msvs_ver (2012)
#       define hryky_msvc_ver (11)
#   elif _MSC_VER == 1600
#       define hryky_msvs_ver (2010)
#       define hryky_msvc_ver (10)
#   else
#       define hryky_msvs_ver (0)
#       define hryky_msvc_ver (0)
#   endif
#else
#   define hryky_msvs_ver (0)
#   define hryky_msvc_ver (0)
#endif

#if 199711L < __cplusplus \
	|| defined(__GXX_EXPERIMENTAL_CXX0X__) \
	|| 2010 <= hryky_msvs_ver
#   define hryky_cpp11  (1)
#else
#   define hryky_cpp11  (0)
#endif

#if (2015 > hryky_msvs_ver) && (0 == (hryky_gcc_version))
#   define hryky_distinct_int_and_int32 (1)
#else
#   define hryky_distinct_int_and_int32 (0)
#endif

#if HRYKY_SUPPORT_DELETED_FUNCTION
#   define hryky_deleted_function =delete
#else
#   define hryky_deleted_function
#endif

#define hryky_assign_op \
	this_type & operator=(this_type const & rhs) \
	{ \
		if (this == &rhs) { \
			return *this; \
		} \
		this_type(rhs).swap(*this); \
		return *this; \
	}

/**
  inserts the definition of move assignment operator.
 */
#define hryky_move_assign_op \
	this_type & operator=(this_type && rhs) \
	{ \
		if (this == &rhs) { \
			return *this; \
		} \
		this->swap(rhs); \
		return *this; \
	}

#if defined(_MSC_VER)
#   define hryky_aligned(bytes, exp)\
	__declspec(align(bytes)) exp
#else
#   define hryky_aligned(bytes, exp)\
	__attribute__((aligned(bytes))) exp
#endif

#define hryky_member(name) name##_

#define hryky_copy_member(name) \
	hryky_member(name)(rhs.hryky_member(name))

#define hryky_move_member(name) \
	hryky_member(name)(::std::move(rhs.hryky_member(name)))

#define hryky_delete_default_constructor(name) \
	name() hryky_deleted_function
/**
  deletes copy constructor.
  This format should not be used in Template Class.
 */
#define hryky_delete_copy_constructor(name) \
	name(name const &) hryky_deleted_function

/**
  deletes assignment operator.
  This format should not be used in Template Class.
 */
#define hryky_delete_copy_assign_op(name) \
	name & operator=(name const &) hryky_deleted_function

/**
  deletes copy constructor.
  The definition of this_type is required.
 */
#define hryky_delete_this_copy_constructor(name) \
	name(this_type const &) hryky_deleted_function

/**
  deletes assignment operator.
  The definition of this_type is required.
 */
#define hryky_delete_this_copy_assign_op(name) \
	this_type & operator=(this_type const &) hryky_deleted_function

//--------------------------------------
// define built-in type accessor of class member
//--------------------------------------
/**
  @internal
  @brief        inserts the definition of function which retrieves
                @a basename_ member of type @a _type.
  @endinternal
 */
#define hryky_getter(_type, basename) \
	_type basename() const\
	{\
		return this->hryky_member(basename);\
	}
/**
  @internal
  @brief        inserts the definition of function which assigns
                @a basename_ member of type @a _type.
  @endinternal
 */
#define hryky_setter(_type, basename) \
	void basename(AsParameter<_type>::type src)\
	{\
		this->hryky_member(basename) = src;\
	}
/**
  @internal
  @brief        inserts the definition of function which assigns
                @a basename_ member of type @a _type.

  - The returned type of the function is the type of class itself.
    This function can be used to call the other member function sequentially.
  @endinternal
 */
#define hryky_setter_row(member_type, basename) \
	this_type & basename(AsParameter< member_type >::type src) \
	{\
		this->hryky_member(basename) = src;\
		return *this;\
	}\

/**
  @internal
  @brief        inserts the definitions of fucntion which retrieve and assign
                member function @a basename_ of type @a type
  @endinternal
 */
#define hryky_accessor_func(_type, basename) \
	hryky_getter(_type, basename);\
	hryky_setter(_type, basename);\

/**
  @internal
  @brief        inserts the definitions of fucntion which retrieve and assign
                member function @a basename_ of type @a type.

  - The function for assigning the member variable returns the reference
    of class instance itself.
  @endinternal
 */
#define hryky_accessor_row_func(type, basename) \
	hryky_getter(type, basename);\
	hryky_setter_row(type, basename);\

/**
  @brief    inserts the definition to read and write the member variable.
  @param    type is type of the member variable.
  @param    basename is the variable name without suffix '_'.
 */
#define hryky_accessor(type, basename) \
	public :\
		hryky_accessor_func(type, basename);\
	protected :\
		type hryky_member(basename);\

/**
  @brief    inserts the definition to read and write the member variable.
  @param    type is type of the member variable.
  @param    basename is the variable name without suffix '_'.

  - The function for assigning the variable returns the reference of
    class instance itself.
 */
#define hryky_accessor_row(type, basename) \
	public :\
		hryky_accessor_row_func(type, basename);\
	protected :\
		type hryky_member(basename);\

/**
  @brief    inserts the definition to read the member variable.
  @param    type is type of the member variable.
  @param    basename is the variable name without suffix '_'.
 */
#define hryky_accessor_read(type, basename) \
	public :\
		hryky_getter(type, basename);\
	protected :\
		type hryky_member(basename);\

/**
  @brief    inserts the definition to write the member variable.
  @param    type is type of the member variable.
  @param    basename is the variable name without suffix '_'.
 */
#define hryky_accessor_write(type, basename) \
	public :\
		hryky_setter(type, basename);\
	protected :\
		type hryky_member(basename);\

/**
  @brief    inserts the definition to write the member variable.
  @param    type is type of the member variable.
  @param    basename is the variable name without suffix '_'.

  - The function for assigning the variable returns the reference of
    class instance itself.
 */
#define hryky_accessor_row_write(type, basename) \
	public :\
		hryky_setter_row(type, basename);\
	protected :\
		type hryky_member(basename);\

//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// struct declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// declares classes
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
#endif // DEFINITION_H_20130317183829443
// end of file
