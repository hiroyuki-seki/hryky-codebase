/**
  @file ip_v6.declaration.y
  @brief the 'declaration' part of KMYACC grammar file for parsing URI.
  @version $Id: http.declaration.y 125 2012-12-29 05:51:14Z hryky.private@gmail.com $
 */
/*******************************************************************************
  declarations
 ******************************************************************************/
%pure_parser
%token NUL
%start IPv6address
%{
#ifdef NDEBUG
#   define KMYACC_ip_v6_DEBUG    0
#else
#   define KMYACC_ip_v6_DEBUG    1
#endif

#define KMYACC_ip_v6_TOKEN hryky::Any<>
%}
%%
