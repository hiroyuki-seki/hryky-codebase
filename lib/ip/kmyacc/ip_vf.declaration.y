/**
  @file ip_vf.declaration.y
  @brief the 'declaration' part of KMYACC grammar file for parsing future IP Address.
  @version $Id: http.declaration.y 125 2012-12-29 05:51:14Z hryky.private@gmail.com $
 */
/*******************************************************************************
  declarations
 ******************************************************************************/
%pure_parser
%token NUL
%start IPvFuture
%{
#ifdef NDEBUG
#   define KMYACC_ip_vf_DEBUG    0
#else
#   define KMYACC_ip_vf_DEBUG    1
#endif

#define KMYACC_ip_vf_TOKEN hryky::Any<>
%}
%%
