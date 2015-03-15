/**
  @file     json_writer.h
  @brief    creates a document formatted by JSON.
  @author   HRYKY
  @version  $Id: json_writer.h 381 2015-03-14 00:09:09Z hryky.private@gmail.com $
 */
#ifndef JSON_WRITER_H_20140208221720595
#define JSON_WRITER_H_20140208221720595
#include "hryky/bitsize_of.h"
#include "hryky/definition.h"
#include "hryky/literal_string.h"
#include "hryky/log/log_definition.h"
#include "hryky/nullptr.h"
#include "hryky/stdint.h"
#include "hryky/stream/ostream_string.h"
#include "hryky/stream/stream_array_begin.h"
#include "hryky/stream/stream_array_end.h"
#include "hryky/stream/stream_denote.h"
#include "hryky/stream/stream_map_begin.h"
#include "hryky/stream/stream_map_end.h"
#include "hryky/stream/stream_hex.h"
#include "hryky/string.h"
#include "hryky/type_traits/enable_if.h"
#include "hryky/vector.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
#include "hryky/type_traits/is_base_of.h"
#include "hryky/type_traits/conditional.h"
#include "hryky/is_null.h"
//------------------------------------------------------------------------------
// disables warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_push_warning
#pragma hryky_pragma_disable_warning_padded
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename StreamT
#define hryky_template_arg \
	StreamT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace json
{
	/// creates a document formatted by JSON.
	template <
		typename StreamT = ostream::String<String<> >
	>
	class Writer;

	LiteralString<> const g_literal_null("null");
	LiteralString<> const g_literal_true("true");
	LiteralString<> const g_literal_false("false");

namespace detail
{
} // namespace detail
} // namespace json
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief creates a document formatted by JSON.
 */
template <hryky_template_param>
class hryky::json::Writer :
	public WithStreamOut<Writer<hryky_template_arg> >,
	public WithSwap<Writer<hryky_template_arg> >
{
public :
	typedef Writer<hryky_template_arg> this_type;
	typedef char char_type;

	/// default constructor.
	Writer();

	/// copy constructor.
	Writer(this_type const &);

	/// move constructor.
	Writer(this_type &&);

	/// constructs with a output stream.
	Writer(StreamT const & stream);

	/// constructs with the output stream as rvalue.
	Writer(StreamT && stream);

	/// destructor.
	~Writer();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// outputs the information through stream.
	template <typename OtherStreamT>
	OtherStreamT & write_to(OtherStreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

	/// outputs an arbitrary value.
	template <typename RhsT>
	this_type & operator<<(RhsT const & rhs);

	/// starts an associative array.
	this_type & operator<<(stream::map::Begin const & rhs);

	/// ends the current associative array.
	this_type & operator<<(stream::map::End const & rhs);

	/// starts an array.
	this_type & operator<<(stream::array::Begin const & rhs);

	/// ends the current array.
	this_type & operator<<(stream::array::End const & rhs);

	/// appends a string which denominates the following element.
	template <typename DenoteStringT>
	this_type & operator<<(stream::Denote<DenoteStringT> const & rhs);

	/// outputs characters.
	this_type & write(char_type const * const str, size_t const size);

protected :

private :

	struct State
	{
		enum Raw
		{
			open,
			key,
			value,
			separated,
		};
	};
	typedef typename State::Raw state_type;
	
	struct Group
	{
		enum Raw
		{
			invalid,
			map,
			array,
			num,
		};
	};
	typedef typename Group::Raw group_type;

	template <typename RhsT>
	struct HasWriteTo
	{
		typedef uint16_t yes;
		typedef uint8_t no;

		template <typename TargetT, Writer & (TargetT::*)(Writer &) const>
		struct Test;

		template <typename TargetT>
		static yes test(Test<TargetT, &TargetT::write_to> *);

		template <typename>
		static no test(...);

		typedef IntegralConstant<
			bool,
			IsBaseOf<WithStreamOut<RhsT>, RhsT>::value
			|| sizeof(test<RhsT>(0)) == sizeof(yes)
		> type;
		static typename type::value_type const value = type::value;
	};

	class StringWrapper :
		public WithStreamOut<StringWrapper>
	{
	public :
		typedef StringWrapper this_type;
		
		StringWrapper(
			char_type const * const str, size_t const size)
			: str_(str), size_(size)
		{
		}

		Writer & write_to(Writer & writer) const
		{
			writer.write_string(
				this->str_, this->str_ + this->size_);
			return writer;
		}

		template <typename StreamT>
		StreamT & write_to(StreamT & out) const
		{
			out.write(this->str_, this->size_);
			return out;
		}
	private :
		hryky_delete_this_copy_constructor(StringWrapper);
		hryky_delete_this_copy_assign_op(StringWrapper);

		char_type const * const str_;
		size_t const size_;
	};

	class Dump :
		public WithStreamOut<Dump>
	{
	public :
		typedef Dump this_type;
		
		Dump(Writer const & writer)
			: writer_(writer)
		{
		}

		template <typename StreamT>
		StreamT & write_to(StreamT & out) const
		{
			stream::map::Scope<StreamT> const map(out);
			out << stream::denote("state") << this->writer_.state_;
			out << stream::denote("hierarchy") << this->writer_.hierarchy_;
			out << stream::denote("stream") << this->writer_.stream_;
			return out;
		}
	private :
		hryky_delete_this_copy_constructor(Dump);
		hryky_delete_this_copy_assign_op(Dump);

		Writer const & writer_;
	};

	class Hierarchy :
		public WithStreamOut<Hierarchy>,
		public WithSwap<Hierarchy>
	{
	public :
		typedef Hierarchy this_type;

		Hierarchy()
			: elements_()
			  , depth_()
		{
		}

		Hierarchy(Hierarchy const & rhs)
			: hryky_copy_member(elements)
			  , hryky_copy_member(depth)
		{
		}

		Hierarchy(Hierarchy && rhs)
			: hryky_move_member(elements)
			  , hryky_move_member(depth)
		{
		}

		void swap(Hierarchy & src)
		{
			hryky_swap_member(elements);
			hryky_swap_member(depth);
		}

		template <typename StreamT>
		StreamT & write_to(StreamT & out) const
		{
			stream::map::Scope<StreamT> const map(out);
			hryky_write_member(elements);
			hryky_write_member(depth);
			return out;
		}

		/// appends a new group.
		bool push(group_type const group);

		/// removes the last group.
		group_type pop();

		/// retrieves the current group.
		group_type group() const;

	private :
		typedef uint64_t                            element_type;
		typedef Vector<element_type>                elements_type;
		typedef typename elements_type::size_type   index_type;
		typedef uint8_t                             bitpos_type;
		typedef size_t                              depth_type;

		static index_type const depth_to_index =
			BitsEnoughUnsigned<BitsizeOf<element_type>::value - 1>::value;
		static bitpos_type const depth_to_bitpos =
			static_cast<bitpos_type>((1u << depth_to_index) - 1);

		/// retrieves the current index of hierarchy.
		index_type index() const;

		/// retrieves the current bit-position of hierarchy.
		bitpos_type bitpos() const;

		elements_type   elements_;
		depth_type      depth_;
	};
	typedef Hierarchy hierarchy_type;

	struct SelectManip;
	struct SelectNone;

	static char const comma = ',';
	static char const quotation = '\"';
	static char const reverse_solidus = '\\';
	static char const left_brace = '{';
	static char const right_brace = '}';
	static char const left_bracket = '[';
	static char const right_bracket = ']';
	static char const colon = ':';

	/// enters into a new group.
	void descend(group_type const group);

	/// ends the current group.
	void ascend(group_type const group);

	/// outputs a manipulator.
	template <typename RhsT>
	this_type & write(
		RhsT const & rhs, SelectManip *);

	/// outputs an arbitrary value.
	template <typename RhsT>
	this_type & write(
		RhsT const & rhs, SelectNone *);

	/// outputs an instance as key.
	template <typename RhsT>
	void write_key(RhsT const & rhs);

	/// outputs an instance as value.
	template <typename RhsT>
	void write_value(
		RhsT const & rhs,
		typename DisableIf<HasWriteTo<RhsT> >::type * = hryky_nullptr);

	/// outputs an instance on the user-defined behavior.
	template <typename RhsT>
	void write_value(
		RhsT const & rhs,
		typename EnableIf<HasWriteTo<RhsT> >::type * = hryky_nullptr);

	/// outputs an immutable null-terminated string.
	void write_value(char_type const * const c_str);

	/// outputs a mutable null-terminated string.
	void write_value(char_type * const c_str);

	/// outpus a boolean value.
	void write_value(bool const value);

	/// outputs characters in accordance with the specification.
	template <typename InputIteratorT>
	void write_string(
		InputIteratorT const begin, InputIteratorT const end);

	StreamT         stream_;
	hierarchy_type  hierarchy_;
	state_type      state_;
};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
namespace json
{
namespace detail
{
} // namespace detail
} // namespace json
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg>::Writer()
	: stream_()
	  , hierarchy_()
	  , state_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg>::Writer(
	this_type const & rhs)
	: hryky_copy_member(stream)
	  , hryky_copy_member(hierarchy)
	  , hryky_copy_member(state)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg>::Writer(
	this_type && rhs)
	: hryky_move_member(stream)
	  , hryky_move_member(hierarchy)
	  , hryky_move_member(state)
{
}
/**
  @brief constructs with a output stream.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg>::Writer(
	StreamT const & stream)
	: stream_(stream)
	  , hierarchy_()
	  , state_()
{
}
/**
  @brief constructs with the output stream as rvalue.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg>::Writer(
	StreamT && stream)
	: stream_(::std::move(stream))
	  , hierarchy_()
	  , state_()
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg>::~Writer()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::json::Writer<hryky_template_arg>::clear()
{
	hryky::clear(this->state_);
	hryky::clear(this->hierarchy_);
	hryky::clear(this->stream_);
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::json::Writer<hryky_template_arg>::swap(
	this_type & src)
{
	hryky_swap_member(stream);
	hryky_swap_member(hierarchy);
	hryky_swap_member(state);
}
/**
  @brief outputs the information through stream.
 */
template <hryky_template_param>
template <typename OtherStreamT>
OtherStreamT &
hryky::json::Writer<hryky_template_arg>::write_to(
	OtherStreamT & out) const
{
	stream::map::Scope<OtherStreamT> const map(out);
	out << this->stream_;
	return out;
}
/**
  @brief outputs an arbitrary value.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::operator<<(
	RhsT const & rhs)
{
	return this->write(
		rhs,
		reinterpret_cast<Conditional<
			IsBaseOf<stream::Manip, RhsT>,
			SelectManip,
			SelectNone
		>::type *>(hryky_nullptr));
}
/**
  @brief starts an associative array.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::operator<<(
	stream::map::Begin const &)
{
	this->descend(Group::map);
	return *this;
}
/**
  @brief ends the current associative array.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::operator<<(
	stream::map::End const &)
{
	this->ascend(Group::map);
	return *this;
}
/**
  @brief starts an array.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::operator<<(
	stream::array::Begin const &)
{
	this->descend(Group::array);
	return *this;
}
/**
  @brief ends the current array.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::operator<<(
	stream::array::End const &)
{
	this->ascend(Group::array);
	return *this;
}
/**
  @brief appends a string which denominates the following element.
 */
template <hryky_template_param>
template <typename DenoteStringT>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::operator<<(
	stream::Denote<DenoteStringT> const & rhs)
{
	if (Group::map != this->hierarchy_.group()) {
		hryky_log_err(
			"The current context is not in JSON object:"
			<< rhs);
		return *this;
	}

	switch (this->state_) {
	case State::open: {
		break;
	}
	case State::key: {
		this->stream_ << json::g_literal_null;
		this->stream_ << this_type::comma;
		break;
	}
	case State::value: {
		this->stream_ << this_type::comma;
		break;
	}
	default: {
		hryky_log_err(
			"invalid state:{state:"
			<< this->state_
			<< ",rhs:" << rhs
			<< "}");
		return *this;
	}
	}

	this->write_key(rhs.get());
	this->state_ = State::key;
	
	return *this;
}
/**
  @brief outputs characters.
 */
template <hryky_template_param>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::write(
	char_type const * const str, size_t const size)
{
	return *this << StringWrapper(str, size);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief begins a new group.
 */
template <hryky_template_param>
void hryky::json::Writer<hryky_template_arg>::descend(
	group_type const group)
{
	switch (this->state_) {
	case State::open: {
		break;
	}
	case State::key: {
		break;
	}
	case State::value: {
		group_type const prev_group = this->hierarchy_.group();
		switch (prev_group) {
		case Group::array: {
			this->stream_ << this_type::comma;
			break;
		}
		case Group::map: {
			hryky_log_err(
				"Any value has to be denominated in Object:{"
				"dump:" << Dump(*this) << "}");
			return;
		}
		default: {
			hryky_log_err(
				"invalid group:{request:" << prev_group
				<< ",dump:" << Dump(*this) << "}");
			return;
		}
		}
		break;
	}
	case State::separated: {
		break;
	}
	default: {
		hryky_log_err("invlaid state: " << this->state_);
		return;
	}
	}

	this->state_ = State::open;

	switch (group) {
	case Group::map: {
		this->stream_ << this_type::left_brace;
		this->hierarchy_.push(group); 
		break;
	}
	case Group::array: {
		this->stream_ << this_type::left_bracket;
		this->hierarchy_.push(group);
		break;
	}
	default : {
		hryky_log_err(
			"invlaid group:{request:" << group
			<< ",dump:" << Dump(*this) << "}");
		return;
	}
	}
}
/**
  @brief ends the current group.
 */
template <hryky_template_param>
void hryky::json::Writer<hryky_template_arg>::ascend(
	group_type const group)
{
	switch (this->state_) {
	case State::open: {
		break;
	}
	case State::key: {
		this->stream_ << json::g_literal_null;
		break;
	}
	case State::value: {
		break;
	}
	default: {
		hryky_log_err(
			"invalid state:{state:" << this->state_
			<< ",dump:" << Dump(*this) << "}");
		return;
	}
	}

	this->state_ = State::value;

	group_type const current_group = this->hierarchy_.pop();
	if (current_group != group) {
		hryky_log_err(
			"invalid group:{current:" << current_group
			<< ",request:" << group
			<< ",dump:" << Dump(*this) << "}");
		return;
	}
	
	switch (group) {
	case Group::map: {
		this->stream_ << this_type::right_brace;
		break;
	}
	case Group::array: {
		this->stream_ << this_type::right_bracket;
		break;
	}
	default: {
		hryky_log_err(
			"invalid group:{request:" << group
			<< ",dump:" << Dump(*this) << "}");
		return;
	}
	}
}
/**
  @brief output an manipulator.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::write(
	RhsT const & rhs, SelectManip *)
{
	this->stream_ << rhs;
	return *this;
}
/**
  @brief output an arbitrary value.
 */
template <hryky_template_param>
template <typename RhsT>
hryky::json::Writer<hryky_template_arg> & 
hryky::json::Writer<hryky_template_arg>::write(
	RhsT const & rhs, SelectNone *)
{
	switch (this->hierarchy_.group()) {
	case Group::map: {
		switch (this->state_) {
		case State::open: {
			this->write_key(rhs);
			this->state_ = State::key;
			break;
		}
		case State::key: {
			this->write_value(rhs);
			this->state_ = State::value;
			break;
		}
		case State::value: {
			this->stream_ << this_type::comma;
			this->state_ = State::separated;
			this->write_key(rhs);
			this->state_ = State::key;
			break;
		}
		case State::separated: {
			// The operator<< is called again in write_key.
			this->write_key(rhs);
			break;
		}
		default: {
			hryky_log_err("invalid state: " << this->state_);
			return *this;
		}
		}
		break;
	}
	case Group::array: {
		switch (this->state_) {
		case State::open: {
			this->write_value(rhs);
			this->state_ = State::value;
			break;
		}
		case State::value: {
			this->stream_ << this_type::comma;
			this->state_ = State::separated;
			this->write_value(rhs);
			this->state_ = State::value;
			break;
		}
		case State::separated: {
			// The operator<< is called again in write_key.
			this->write_value(rhs);
			break;
		}
		default: {
			hryky_log_err("invalid state: " << this->state_);
			return *this;
		}
		}
		break;
	}
	default: {
		hryky_log_err("invalid group");
		return *this;
	}
	}
	return *this;
}
/**
  @brief outputs an instance as key.
 */
template <hryky_template_param>
template <typename RhsT>
void hryky::json::Writer<hryky_template_arg>::write_key(
	RhsT const & rhs)
{
	{
		ostream::String<String<> > os;
		os << rhs;
		this->write_string(os.str().begin(), os.str().end());
	}
	this->stream_ << this_type::colon;
}
/**
  @brief outputs an instance on the user-defined behavior.
 */
template <hryky_template_param>
template <typename RhsT>
void hryky::json::Writer<hryky_template_arg>::write_value(
	RhsT const & rhs,
	typename EnableIf<HasWriteTo<RhsT> >::type *)
{
	rhs.write_to(*this);
}
/**
  @brief outputs an instance as value.
 */
template <hryky_template_param>
template <typename RhsT>
void hryky::json::Writer<hryky_template_arg>::write_value(
	RhsT const & rhs,
	typename DisableIf<HasWriteTo<RhsT> >::type *)
{
	this->stream_ << rhs;
}
/**
  @brief outpus a boolean value.
 */
template <hryky_template_param>
void hryky::json::Writer<hryky_template_arg>::write_value(
	bool const value)
{
	this->stream_
		<< (value ? json::g_literal_true : json::g_literal_false);
}
/**
  @brief outputs an immutable null-terminated string.
 */
template <hryky_template_param>
void hryky::json::Writer<hryky_template_arg>::write_value(
	char_type const * const c_str)
{
	if (hryky_is_null(c_str)) {
		this->stream_ << json::g_literal_null;
		return;
	}
	
	size_t const size = ::std::strlen(c_str);

	this->write_string(c_str, c_str + size);
}
/**
  @brief outputs a mutable null-terminated string.
 */
template <hryky_template_param>
void hryky::json::Writer<hryky_template_arg>::write_value(
	char_type * const c_str)
{
	char_type const * const immutable = c_str;
	this->write_value(immutable);
}
/**
  @brief outputs characters in accordance with the specification.
 */
template <hryky_template_param>
template <typename InputIteratorT>
void hryky::json::Writer<hryky_template_arg>::write_string(
	InputIteratorT const begin, InputIteratorT const end)
{
	this->stream_ << this_type::quotation;
	InputIteratorT itr = begin;
	while (end != itr) {
		char_type const chara = *itr;
		if (this_type::quotation == chara) {
			this->stream_ << this_type::reverse_solidus;
		}
		this->stream_ << chara;
		++itr;
	}
	this->stream_ << this_type::quotation;
}
//------------------------------------------------------------------------------
// declares public member functions of Hierarchy
//------------------------------------------------------------------------------
/**
  @brief appends a new group.
 */
template <hryky_template_param>
bool 
hryky::json::Writer<hryky_template_arg>::Hierarchy::push(
	group_type const group)
{
	++this->depth_;
	
	switch (group) {
	case Group::map: {
		/**
		  Bit 0 indicates Group::map.
		  The expansion of hierarchy is deferred until any Group::array
		  appears.
		 */
		index_type const index = this->index();
		if (this->elements_.size() > index) {
			bitpos_type const bitpos = this->bitpos();
			this->elements_[index] &= ~(
				static_cast<element_type>(1u) << bitpos);
		}
		break;
	}
	case Group::array: {
		index_type const index = this->index();
		while (this->elements_.size() <= index) {
			if (!this->elements_.push_back(element_type())) {
				hryky_log_err("failed to allocate memory.");
				return false;
			}
		}
		bitpos_type const bitpos = this->bitpos();
		this->elements_[index]
			|= (static_cast<element_type>(1u) << bitpos);
		break;
	}
	default: {
		hryky_log_err("invalid group:{group:" << group << "}");
		return false;
	}
	}
	
	return true;
}
/**
  @brief removes the last group.
 */
template <hryky_template_param>
typename hryky::json::Writer<hryky_template_arg>::group_type 
hryky::json::Writer<hryky_template_arg>::Hierarchy::pop()
{
	if (0u == this->depth_) {
		hryky_log_err("There is no group:" << *this);
		return Group::invalid;
	}

	group_type const group = this->group();

	--this->depth_;

	return group;
}
/**
  @brief retrieves the current group.
 */
template <hryky_template_param>
typename hryky::json::Writer<hryky_template_arg>::group_type 
hryky::json::Writer<hryky_template_arg>::Hierarchy::group() const
{
	index_type const index = this->index();
	bitpos_type const bitpos = this->bitpos();

	if (this->elements_.size() <= index) {
		/**
		  Group::map might not expand the hierarchy.
		 */
		return Group::map;
	}
	
	return ((0x1u == ((this->elements_[index] >> bitpos) & 0x1u))
			? Group::array
			: Group::map);
}
//------------------------------------------------------------------------------
// declares private member functions of Hierarchy
//------------------------------------------------------------------------------
/**
  @brief retrieves the current index of hierarchy.
 */
template <hryky_template_param>
typename hryky::json::Writer<hryky_template_arg>::Hierarchy::index_type
hryky::json::Writer<hryky_template_arg>::Hierarchy::index() const
{
	if (0u == this->depth_) {
		return 0u;
	}
	
	return (this->depth_ - 1) >> this_type::depth_to_index;
}
/**
  @brief retrieves the current bit-position of hierarchy.
 */
template <hryky_template_param>
typename hryky::json::Writer<hryky_template_arg>::Hierarchy::bitpos_type
hryky::json::Writer<hryky_template_arg>::Hierarchy::bitpos() const
{
	if (0u == this->depth_) {
		return 0u;
	}

	return static_cast<bitpos_type>(
		(this->depth_ - 1) & this_type::depth_to_bitpos);
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace json
{
	/// creates the default JSON writer.
	Writer<> writer();

} // namespace json
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
/**
  @brief creates the default JSON writer.
 */
inline
hryky::json::Writer<>
hryky::json::writer()
{
	return Writer<>();
}
//------------------------------------------------------------------------------
// revokes macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
//------------------------------------------------------------------------------
// restores warnings
//------------------------------------------------------------------------------
#pragma hryky_pragma_pop_warning
#endif // JSON_WRITER_H_20140208221720595
// end of file
