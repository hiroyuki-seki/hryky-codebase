/**
  @file     basic_streambuf.h
  @brief    uses an arbitrary container for the buffer of ::std::basic_streambuf.
  @author   HRYKY
  @version  $Id: streambuf_container.h 368 2014-07-14 21:21:42Z hryky.private@gmail.com $
 */
#ifndef STREAMBUF_CONTAINER_H_20140108143916277
#define STREAMBUF_CONTAINER_H_20140108143916277
#include "hryky/std/std_streambuf.h"
#include "hryky/retention/retention_reference.h"
#include "hryky/with_stream_out.h"
#include "hryky/with_swap.h"
//------------------------------------------------------------------------------
// defines macros
//------------------------------------------------------------------------------
#define hryky_template_param \
	typename ContainerT, \
	typename CharT, \
	typename TraitsT, \
	template <typename> class RetainT
#define hryky_template_arg \
	ContainerT, CharT, TraitsT, RetainT
//------------------------------------------------------------------------------
// declares types
//------------------------------------------------------------------------------
namespace hryky
{
namespace streambuf
{
	/// uses an arbitrary container for the buffer of ::std::basic_streambuf.
	template <
		typename ContainerT,
		typename CharT = typename ContainerT::value_type,
		typename TraitsT = ::std::char_traits<CharT>,
		template <typename> class RetainT = retention::Reference
	>
	class Container;
}
} // namespace hryky
//------------------------------------------------------------------------------
// declares classes
//------------------------------------------------------------------------------
/**
  @brief uses an arbitrary container for the buffer of ::std::basic_streambuf.
 */
template <hryky_template_param>
class hryky::streambuf::Container :
	public ::std::basic_streambuf<CharT, TraitsT>,
	public WithStreamOut<Container<hryky_template_arg> >,
	public WithSwap<Container<hryky_template_arg> >,
	public RetainT<ContainerT>
{
public :

	typedef Container<hryky_template_arg>           this_type;
	typedef ::std::basic_streambuf<CharT, TraitsT>    base_type;
	typedef typename ContainerT::value_type         value_type;
	typedef typename ContainerT::reference          reference;
	typedef typename ContainerT::const_reference    const_reference;
	
	typedef typename base_type::int_type            int_type;
	typedef typename base_type::char_type           char_type;
	typedef typename base_type::off_type            off_type;
	typedef typename base_type::pos_type            pos_type;
	typedef ::std::ios_base::seekdir                  seekdir;
	typedef ::std::ios_base::openmode                 openmode;
	typedef ::std::streamsize                         streamsize;

	typedef RetainT<ContainerT>                     retain_type;
	typedef typename retain_type::initializer_type initializer_type;

	/// default constructor.
	Container();

	/// constructs with an initializer.
	Container(initializer_type initializer);

	/// copy constructor.
	Container(this_type const &);

	/// move constructor.
	Container(this_type &&);

	/// destructor.
	~Container();

	/// assignment operator.
	hryky_assign_op;

	/// move assignment operator.
	hryky_move_assign_op;

	/// releases the internal resources.
	void clear();

	/// decomposes the instance to primitive objects.
	template <typename StreamT>
	StreamT & write_to(StreamT & out) const;

	/// interchanges the each internal resources of two instances.
	void swap(this_type & src);

protected :

private :
	typedef typename ContainerT::size_type size_type;

	/// imbues a new locale.
	virtual void imbue(::std::locale const & loc);

	/// assigns a new buffer.
	virtual base_type * setbuf(char_type * s, streamsize n);

	/// alters the position of the buffer from the specific position.
	virtual pos_type seekoff(off_type off, seekdir way, openmode which);

	/// alters the position of the buffer.
	virtual pos_type seekpos(pos_type pos, openmode which);

	/// synchronizes the internal buffers.
	virtual int sync();

	/// retrieves the available characters in the rest of buffer.
	virtual streamsize showmanyc();

	/// reads characters from the controlled input sequence.
	virtual streamsize xsgetn(char_type * s, streamsize n);

	/// reads a character without changing the current position.
	virtual int_type underflow();

	/// reads a character with advancing the current position.
	virtual int_type uflow();

	/**
	  puts a character back to the controlled input sequence with changing
	  the current position backward.
	 */
	virtual int_type pbackfail(int_type c);

	/// writes characters to the controlled output sequence.
	virtual streamsize xsputn(char_type const * s, streamsize n);

	/**
	  writes a character to the internal outputbuffer without changing
	  the current position.
	 */
	virtual int_type overflow(int_type c);

	size_type input_;
	size_type output_;

};
//------------------------------------------------------------------------------
// specializes classes
//------------------------------------------------------------------------------
namespace hryky
{
} // namespace hryky
//------------------------------------------------------------------------------
// defines public member functions
//------------------------------------------------------------------------------
/**
  @brief default constructor.
 */
template <hryky_template_param>
hryky::streambuf::Container<hryky_template_arg>::Container()
	: base_type()
	  , retain_type()
	  , input_()
	  , output_()
{
}
/**
  @brief constructs with an initializer.
 */
template <hryky_template_param>
hryky::streambuf::Container<hryky_template_arg>::Container(
	initializer_type const initializer)
	: base_type()
	  , retain_type(initializer)
	  , input_()
	  , output_()
{
}
/**
  @brief copy constructor.
 */
template <hryky_template_param>
hryky::streambuf::Container<hryky_template_arg>::Container(
	this_type const & rhs)
	: base_type(rhs)
	  , retain_type(rhs)
	  , hryky_copy_member(input)
	  , hryky_copy_member(output)
{
}
/**
  @brief move constructor.
 */
template <hryky_template_param>
hryky::streambuf::Container<hryky_template_arg>::Container(
	this_type && rhs)
	: base_type(::std::move(rhs))
	  , retain_type(::std::move(rhs))
	  , hryky_move_member(input)
	  , hryky_move_member(output)
{
}
/**
  @brief destructor.
 */
template <hryky_template_param>
hryky::streambuf::Container<hryky_template_arg>::~Container()
{
}
/**
  @brief releases the internal resources.
 */
template <hryky_template_param>
void hryky::streambuf::Container<hryky_template_arg>::clear()
{
	hryky::clear(this->output_);
	hryky::clear(this->input_);
	this->retain_type::clear();
}
/**
  @brief decomposes the instance to primitive objects.
 */
template <hryky_template_param>
template <typename StreamT>
StreamT &
hryky::streambuf::Container<hryky_template_arg>::write_to(
	StreamT & out) const
{
	stream::map::Scope<StreamT> const map(out);
	out << stream::denote("retention")
		<< static_cast<retain_type const>(*this);
	hryky_write_member(input);
	hryky_write_member(output);

	return out;
}
/**
  @brief interchanges the each internal resources of two instances.
 */
template <hryky_template_param>
void hryky::streambuf::Container<hryky_template_arg>::swap(this_type & src)
{
	swap(
		static_cast<base_type &>(*this),
		static_cast<base_type &>(src));
	this->retain_type::swap(src);
	hryky_swap_member(input);
	hryky_swap_member(output);
}
//------------------------------------------------------------------------------
// defines protected member functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// defines private member functions
//------------------------------------------------------------------------------
/**
  @brief imbues a new locale.
 */
template <hryky_template_param>
void hryky::streambuf::Container<hryky_template_arg>::imbue(
	::std::locale const & loc)
{
	this->base_type::imbue(loc);
}
/**
  @brief assigns a new buffer.
 */
template <hryky_template_param>
typename hryky::streambuf::Container<hryky_template_arg>::base_type * 
hryky::streambuf::Container<hryky_template_arg>::setbuf(
	char_type * s, streamsize n)
{
	this->get()->assign(s, s + n);
	this->input_ = 0u;
	this->output_ = static_cast<size_type>(n);
	return this;
}
/**
  @brief alters the position of the buffer from the specific position.
 */
template <hryky_template_param>
typename hryky::streambuf::Container<hryky_template_arg>::pos_type 
hryky::streambuf::Container<hryky_template_arg>::seekoff(
	off_type off, seekdir way, openmode which)
{
	switch (way) {
	case ::std::ios_base::beg:
		return this->seekpos(pos_type(off), which);
		
	case ::std::ios_base::cur:
		if (openmode() != (::std::ios_base::in & which)) {
			this->input_ += off;
		}
		
		if (openmode() != (::std::ios_base::out & which)) {
			this->output_ +=off;
		}
		break;
		
	case ::std::ios_base::end:
		if (openmode() != (::std::ios_base::in & which)) {
			this->input_ = this->get()->size() - off;
		}
		
		if (openmode() != (::std::ios_base::out & which)) {
			this->output_ = this->get()->size() - off;
		}
		break;
	default:
		break;
	}
	return pos_type(off_type(-1));
}
/**
  @brief alters the position of the buffer.
 */
template <hryky_template_param>
typename hryky::streambuf::Container<hryky_template_arg>::pos_type 
hryky::streambuf::Container<hryky_template_arg>::seekpos(
	pos_type pos, openmode which)
{
	if (openmode() != (::std::ios_base::in & which)) {
		this->input_ = static_cast<size_type>(pos);
	}

	if (openmode() != (::std::ios_base::out & which)) {
		this->output_ = static_cast<size_type>(pos);
	}
	
	return pos_type(off_type(-1));
}
/**
  @brief synchronizes the internal buffers.
 */
template <hryky_template_param>
int hryky::streambuf::Container<hryky_template_arg>::sync()
{
	return this->base_type::sync();
}
/**
  @brief retrieves the available characters in the rest of buffer.
 */
template <hryky_template_param>
::std::streamsize
hryky::streambuf::Container<hryky_template_arg>::showmanyc()
{
	return static_cast< ::std::streamsize>(
		this->get()->size() - this->input_);
}
/**
  @brief reads characters from the controlled input sequence.
 */
template <hryky_template_param>
::std::streamsize
hryky::streambuf::Container<hryky_template_arg>::xsgetn(
	char_type * s, streamsize n)
{
	size_type const ret = static_cast<size_type>(
		(::std::min)(n, this->showmanyc()));
	if (0u != ret) {
		hryky::memcpy(
			s,
			&(*this->get())[this->input_],
			sizeof(value_type) * ret);
	}
	this->input_ += ret;
	
	return static_cast< ::std::streamsize>(ret);
}
/**
  @brief reads a character without changing the current position.
 */
template <hryky_template_param>
typename hryky::streambuf::Container<hryky_template_arg>::int_type 
hryky::streambuf::Container<hryky_template_arg>::underflow()
{
	if (this->get()->size() <= this->input_) {
		return traits_type::eof();
	}

	return static_cast<int_type>((*this->get())[this->input_]);
}
/**
  @brief reads a character with advancing the current position.
 */
template <hryky_template_param>
typename hryky::streambuf::Container<hryky_template_arg>::int_type 
hryky::streambuf::Container<hryky_template_arg>::uflow()
{
	if (this->get()->size() <= this->input_) {
		return traits_type::eof();
	}

	int_type const ret =
		static_cast<int_type>((*this->get())[this->input_]);
	++this->input_;
	
	return ret;
}
/**
  @brief puts a character back to the controlled input sequence after
    changing the position backward.
 */
template <hryky_template_param>
typename hryky::streambuf::Container<hryky_template_arg>::int_type 
hryky::streambuf::Container<hryky_template_arg>::pbackfail(
	int_type c)
{
	if (size_type() == this->input_) {
		return traits_type::eof();
	}

	--this->input_;
	
	(*this->get())[this->input_] = static_cast<value_type>(c);
	
	return c;
}
/**
  @brief writes characters to the controlled output sequence.
 */
template <hryky_template_param>
::std::streamsize
hryky::streambuf::Container<hryky_template_arg>::xsputn(
	char_type const * s, streamsize n)
{
	size_type const post_size = this->output_ + n;
	
	if (this->get()->size() < post_size) {
		this->get()->resize(post_size);
	}

	size_type const ret = (::std::min)(
		static_cast<size_type>(n),
		this->get()->size() - this->output_);

	if (0u != ret) {
		hryky::memcpy(
			&(*this->get())[this->output_],
			s,
			sizeof(value_type) * ret);
	}
	this->output_ += ret;
	
	return static_cast< ::std::streamsize>(ret);
}
/**
  @brief writes a character to the controlled output sequence without changing
    the current position.
 */
template <hryky_template_param>
typename hryky::streambuf::Container<hryky_template_arg>::int_type 
hryky::streambuf::Container<hryky_template_arg>::overflow(
	int_type c)
{
	size_type const post_size = this->output_ + 1u;
	
	if (this->get()->size() < post_size) {
		this->get()->push_back(value_type());

		if (this->get()->size() < post_size) {
			return traits_type::eof();
		}
	}

	value_type const ret = static_cast<value_type>(c);

	(*this->get())[this->output_] = ret;
	
	return ret;
}
//------------------------------------------------------------------------------
// declares global functions
//------------------------------------------------------------------------------
namespace hryky
{
namespace streambuf
{
} // namespace streambuf
} // namespace hryky
//------------------------------------------------------------------------------
// defines global functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// revokes the temporary macros
//------------------------------------------------------------------------------
#undef hryky_template_param
#undef hryky_template_arg
#endif // STREAMBUF_CONTAINER_H_20140108143916277
// end of file
