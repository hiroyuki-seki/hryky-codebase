/**
  @file date.declaration.y
  @brief the 'declaration' part of KMYACC grammar file for parsing Date.
  @version $Id: http.declaration.y 206 2013-04-02 08:48:34Z hryky.private@gmail.com $
 */
/*******************************************************************************
  declarations
 ******************************************************************************/
%pure_parser
%token NUL
%start date
%{
#ifdef NDEBUG
#   define KMYACC_date_DEBUG    0
#else
#   define KMYACC_date_DEBUG    1
#endif

#define KMYACC_date_PRIVATE \
	hryky::mempool_type mempool() const { \
		return this->derived()->mempool();\
	}

#define KMYACC_date_TOKEN hryky::Any<>
	
%}
%%
