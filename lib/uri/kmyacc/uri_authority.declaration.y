/**
  @file uri_authority.declaration.y
  @brief the 'declaration' part of KMYACC grammar file for parsing the authority part of URI.
  @version $Id: http.declaration.y 125 2012-12-29 05:51:14Z hryky.private@gmail.com $
 */
/*******************************************************************************
  declarations
 ******************************************************************************/
%pure_parser
%token NUL
%start authority
%{
#ifdef NDEBUG
#   define KMYACC_uri_authority_DEBUG    0
#else
#   define KMYACC_uri_authority_DEBUG    1
#endif

#define KMYACC_uri_authority_PRIVATE \
	typedef hryky::Vector<octet_type> octets_type; \
	hryky::mempool_type mempool() const { \
		return this->derived()->mempool();\
	}
	
#define KMYACC_uri_authority_TOKEN hryky::Any<>
%}
%%
