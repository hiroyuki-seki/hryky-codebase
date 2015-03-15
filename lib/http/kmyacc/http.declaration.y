/**
  @file http.declaration.y
  @brief the 'declaration' part of KMYACC grammar file for parsing HTTP Message.
  @version $Id: http.declaration.y 330 2014-03-01 03:40:15Z hryky.private@gmail.com $
 */
/*******************************************************************************
  declarations
 ******************************************************************************/
%pure_parser
%token NUL
%start HTTP_message
%{
#ifdef NDEBUG
#   define KMYACC_http_header_DEBUG    0
#else
#   define KMYACC_http_header_DEBUG    1
#endif

#define KMYACC_http_header_PRIVATE \
	typedef hryky::Vector<octet_type>\
		octets_type;\
	typedef hryky::SharedPtr<hryky::http::header::field_type, Null>\
		field_ptr_type;\
	typedef hryky::SharedPtr<hryky::http::header::cache::directive_type, Null>\
			cache_directive_ptr_type;\
	typedef hryky::Vector<hryky::http::header::field::kind_type>\
			field_kinds_type;\
	typedef hryky::SharedPtr<hryky::http::header::product_comment::Base, Null>\
		product_comment_ptr_type;\
	typedef hryky::Vector<product_comment_ptr_type>\
		product_comment_ptrs_type;\
	typedef hryky::Vector<header::accept::content_type>\
		accept_contents_type;\
	typedef hryky::Vector<header::content::coding_type>\
		content_codings_type;\
	typedef hryky::Vector<header::accept::encoding::content_type>\
		accept_encoding_contents_type;\
	typedef hryky::Vector<header::accept::language::content_type>\
		accept_language_contents_type;\
	typedef hryky::Vector<header::accept::charset::content_type>\
		accept_charset_contents_type;\
	typedef hryky::Vector<header::field::extension::content_type>\
		field_extension_contents_type;\
	hryky::mempool_type mempool() const { \
		return this->derived()->mempool(); \
	}
	
#define KMYACC_http_header_TOKEN hryky::Any<>
%}
%%
