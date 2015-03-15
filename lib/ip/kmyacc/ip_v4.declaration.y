/**
  @file ip_v4.declaration.y
  @brief the 'declaration' part of KMYACC grammar file for parsing URI.
  @version $Id: http.declaration.y 125 2012-12-29 05:51:14Z hryky.private@gmail.com $
 */
/*******************************************************************************
  declarations
 ******************************************************************************/
%pure_parser
%token NUL
%start IPv4address
%{
#ifdef NDEBUG
#   define KMYACC_ip_v4_DEBUG    0
#else
#   define KMYACC_ip_v4_DEBUG    1
#endif
	typedef hryky::Vector<octet_type> octets_type;
	
#define KMYACC_ip_v4_TOKEN hryky::Any<>
%}
%%
