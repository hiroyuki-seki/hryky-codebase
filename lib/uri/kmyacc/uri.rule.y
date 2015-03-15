/**
  @file uri.rule.y
  @brief the 'rule' part of KMYACC grammar file for URI.
  @version $Id: uri.rule.y 359 2014-07-01 11:21:44Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc3986/

 */

/**
  RFC3986, 3. Syntax Components.
 */
URI :
	uri_scheme hier_part
	{
		uri_type uri(this->mempool());
		uri.scheme(*$1.cast<uri::scheme_type>());
		uri.hierarchy(*$2.cast<uri::hierarchy_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_scheme hier_part uri_query
	{
		uri_type uri(this->mempool());
		uri.scheme(*$1.cast<uri::scheme_type>());
		uri.hierarchy(*$2.cast<uri::hierarchy_type>());
		uri.query(*$3.cast<uri::query_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_scheme hier_part uri_fragment
	{
		uri_type uri(this->mempool());
		uri.scheme(*$1.cast<uri::scheme_type>());
		uri.hierarchy(*$2.cast<uri::hierarchy_type>());
		uri.fragment(*$3.cast<uri::fragment_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_scheme hier_part uri_query uri_fragment
	{
		uri_type uri(this->mempool());
		uri.scheme(*$1.cast<uri::scheme_type>());
		uri.hierarchy(*$2.cast<uri::hierarchy_type>());
		uri.query(*$3.cast<uri::query_type>());
		uri.fragment(*$4.cast<uri::fragment_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
hier_part :
	'/' '/' authority path_abempty
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.authority(*$3.cast<uri::authority_type>());
		hierarchy.path(*$4.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_absolute
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.path(*$1.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_rootless
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.path(*$1.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_empty
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.path(*$1.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC3986, 3.1. Scheme.
  @note
  - suppresses reduce/reduce conflict with uri_unreserved.
 */
uri_scheme :
	uri_scheme_octets
	{
		octets_type * octets = $1.cast<octets_type>();
		uri::scheme_type const scheme(octets->begin(), octets->end() - 1);

		if (hryky_is_null($$ = token_type(scheme, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
uri_scheme_octets :
	ALPHA ':'
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA uri_scheme_rest ':'
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		octets_type * rest = $2.cast<octets_type>();
		
		if (!octets.insert(octets.end(), rest->begin(), rest->end())) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
uri_scheme_rest :
	uri_scheme_rest_char
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_scheme_rest uri_scheme_rest_char
	{
		octets_type * octets = $1.cast<octets_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		
		$$ = $1;
	}
	;
uri_scheme_rest_char :
	ALPHA
	| DIGIT
	| '+'
	| '-'
	| '.'
	;

/**
  RFC3986, 3.3. Path.
 */
path :
	path_abempty
	| path_absolute
	| path_noscheme
	| path_rootless
	| path_empty
	;
path_abempty :
	| '/' segment
	{
		uri::path_type path = uri::path_type(this->mempool());
		if (!path.append(*$2.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_abempty '/' segment
	{
		uri::path_type & path = *$1.cast<uri::path_type>();
		if (!path.append(*$3.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
path_absolute :
	'/' segment_nz path_absolute_segment
	{
		uri::path_type path(this->mempool());
		if (!path.append(*$2.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}
		if (!path.append(*$3.cast<uri::path_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| '/' segment_nz
	{
		uri::path_type path(this->mempool());
		if (!path.append(*$2.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| '/'
	{
		uri::path_type path(this->mempool());

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
path_absolute_segment :
	'/' segment
	{
		uri::path_type path(this->mempool());
		if (!path.append(*$1.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_absolute_segment '/' segment
	{
		uri::path_type & path = *$1.cast<uri::path_type>();
		if (!path.append(*$3.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
path_noscheme :
	segment_nz_nc
	{
		uri::path_type path(this->mempool());
		if (!path.append(*$1.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_noscheme '/' segment
	{
		uri::path_type & path = *$1.cast<uri::path_type>();
		if (!path.append(*$3.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
path_rootless :
	segment_nz
	{
		uri::path_type path(this->mempool());
		if (!path.append(*$1.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_rootless '/' segment
	{
		uri::path_type & path = *$1.cast<uri::path_type>();
		if (!path.append(*$3.cast<uri::segment_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
path_empty :
	{
		if (hryky_is_null($$ = token_type(
			uri::path_type(this->mempool()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
segment :
	{
		if (hryky_is_null($$ = token_type(
			uri::segment_type(this->mempool()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_pchar
	{
		uri::segment_type segment(this->mempool());
		if (!segment.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(segment, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| segment uri_pchar
	{
		uri::segment_type & segment = *$1.cast<uri::segment_type>();
		if (!segment.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
segment_nz :
	uri_pchar
	{
		uri::segment_type segment(this->mempool());
		if (!segment.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(segment, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| segment_nz uri_pchar
	{
		uri::segment_type & segment = *$1.cast<uri::segment_type>();
		if (!segment.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
segment_nz_nc :
	segment_nz_nc_char
	{
		uri::segment_type segment(this->mempool());
		if (!segment.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(segment, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| segment_nz_nc segment_nz_nc_char
	{
		uri::segment_type & segment = *$1.cast<uri::segment_type>();
		if (!segment.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
segment_nz_nc_char :
	uri_unreserved
	| pct_encoded
	| uri_sub_delims
	| '@'
	;
uri_pchar :
	uri_unreserved
	| pct_encoded
	| uri_sub_delims
	| ':'
	| '@'
	;

/**
  RFC3986, 3.4. Query.
 */
uri_query :
	'?'
	{
		if (hryky_is_null($$ = token_type(
			uri::query_type(this->mempool()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| '?' uri_query_octets
	{
		if (hryky_is_null($$ = token_type(
			uri::query_type(*$2.cast<octets_type>()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
uri_query_octets :
	uri_query_char
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_query_octets uri_query_char
	{
		octets_type * octets = $1.cast<octets_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;
uri_query_char :
	uri_pchar
	| '/'
	| '?'
	;

/**
  RFC3986, 3.5. Fragment.
 */
uri_fragment :
	'#'
	{
		if (hryky_is_null($$ = token_type(
			uri::fragment_type(this->mempool()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| '#' uri_fragment_octets
	{
		if (hryky_is_null($$ = token_type(
			uri::fragment_type(*$2.cast<octets_type>()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
uri_fragment_octets :
	uri_fragment_char
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_fragment_octets uri_fragment_char
	{
		octets_type * octets = $1.cast<octets_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;
uri_fragment_char :
	uri_pchar
	| '/'
	| '?'
	;

/**
  RFC3986, 4.1. URI Reference.
 */
URI_Reference :
	URI
	| relative_ref
	;

/**
  RFC3986, 4.2. Relative Reference.
 */
relative_ref :
	uri_relative_part
	| uri_relative_part uri_query
	{
		uri_type uri(this->mempool());
		uri.hierarchy(*$1.cast<uri::hierarchy_type>());
		uri.query(*$2.cast<uri::query_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_relative_part uri_fragment
	{
		uri_type uri(this->mempool());
		uri.hierarchy(*$1.cast<uri::hierarchy_type>());
		uri.fragment(*$2.cast<uri::fragment_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_relative_part uri_query uri_fragment
	{
		uri_type uri(this->mempool());
		uri.hierarchy(*$1.cast<uri::hierarchy_type>());
		uri.query(*$2.cast<uri::query_type>());
		uri.fragment(*$3.cast<uri::fragment_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
uri_relative_part :
	'/' '/' authority path_abempty
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.authority(*$3.cast<uri::authority_type>());
		hierarchy.path(*$4.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_absolute
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.path(*$1.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_noscheme
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.path(*$1.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| path_empty
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.path(*$1.cast<uri::path_type>());

		if (hryky_is_null($$ = token_type(hierarchy, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC3986, 4.3. Absolute URI.
 */
absolute_URI :
	uri_scheme hier_part
	{
		uri_type uri(this->mempool());
		uri.scheme(*$1.cast<uri::scheme_type>());
		uri.hierarchy(*$2.cast<uri::hierarchy_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| uri_scheme hier_part uri_query
	{
		uri_type uri(this->mempool());
		uri.scheme(*$1.cast<uri::scheme_type>());
		uri.hierarchy(*$2.cast<uri::hierarchy_type>());
		uri.query(*$3.cast<uri::query_type>());

		if (hryky_is_null($$ = token_type(uri, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
