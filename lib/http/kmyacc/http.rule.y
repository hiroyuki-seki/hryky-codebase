/**
  @file http.rule.y
  @brief the 'rule' part of KMYACC grammar file for parsing HTTP Message.
  @version $Id: http.rule.y 359 2014-07-01 11:21:44Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc2616/

 */
/*
  RFC2616, in 2.2 Basic Rules

  ASCII characters are defined in ascii.rule.y.
 */
OCTET :
	octet_no_ws | SP | HT | CR | LF;
octet_no_ws :
	char_no_ws | no_ascii;
CHAR :
	char_no_ws | SP | HT;
char_no_ws :
	printable_symbol_no_sp | ctl_no_ht_cr_lf | ALPHA | DIGIT;
SPs :
	SP
	| SPs SP;
HTs :
	HT
	| HTs HT;
SP_HT :
	SP
	| HT;
SP_HTs :
	SP_HT
	| SP_HTs SP_HT;
CRLF :
	CR LF;
LWS :
	CRLF SP_HTs
	{
		$$ = token_type(static_cast<octet_type>(' '));
	}
	| SP_HTs
	{
		$$ = token_type(static_cast<octet_type>(' '));
	}
	;
LWSs :
	| LWSs_nz;
LWSs_nz :
	LWS
	{
		$$ = $1;
	}
	| LWS LWSs_nz
	{
		$$ = $1;
	}
	;
TEXT :
	printable_symbol_no_sp | ALPHA | DIGIT | LWS;
http_token :
	http_token_char
	{
		header::token_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| http_token http_token_char
	{
		header::token_type * octets = $1.cast<header::token_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;
http_token_no_digits :
	http_token_no_digit
	{
		header::token_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| http_token_no_digits http_token_char
	{
		header::token_type * octets = $1.cast<header::token_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;
http_token_char :
	'*' | http_token_no_asterisk_char
	;
http_token_no_asterisk_char :
	'!' | '#' | '$' | '%' | '&' | '\'' | '+' | '-' | '.' | DIGIT | ALPHA
	| '^' | '_' | '`' | '|' | '~'
	;
http_token_no_digit :
	'*' | '!' | '#' | '$' | '%' | '&' | '\'' | '+' | '-' | '.' | ALPHA
	| '^' | '_' | '`' | '|' | '~'
	;
separators :
	'(' | ')' | '<' | '>' | '@' | ',' | ';' | ':' | '\\' | '"' | '/' | '['
	| ']' | '?' | '=' | '{' | '}' | SP | HT
	;
comment :
	'(' comment_sequence ')'
	{
		$$ = $2;
	}
	| '(' ')'
	{
		if (hryky_is_null($$ = token_type(
			comment::sequence_type(this->mempool()), this->mempool()))) {
			KMYACC_ABORT;
		};
	}
	;
comment_sequence :
	comment_sequence comment_string
	{
		comment::sequence_type & sequence =
			*$1.cast<comment::sequence_type>();
		if (!sequence.append(*$2.cast<comment::string_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	| comment_sequence comment
	{
		comment::sequence_type & sequence =
			*$1.cast<comment::sequence_type>();
		if (!sequence.append(*$2.cast<comment::sequence_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	| comment_string
	{
		comment::sequence_type sequence(this->mempool());
		if (!sequence.append(*$1.cast<comment::string_type>())) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = token_type(sequence, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| comment
	{
		comment::sequence_type sequence(this->mempool());
		if (!sequence.append(*$1.cast<comment::sequence_type>())) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = token_type(sequence, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
comment_string :
	comment_string_char
	{
		comment::string_type string(this->mempool());
		if (!string.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(string, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| comment_string comment_string_char
	{
		comment::string_type & string =
			*$1.cast<comment::string_type>();
		if (!string.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
comment_string_char :
	ctext
	| quoted_pair
	;
ctext :
	printable_symbol_no_sp_parenthesis | ALPHA | DIGIT | LWS;
quoted_string :
	'"' quoted_string_entity '"'
	{
		$$ = $2;
	}
	| '"' '"'
	{
		if (hryky_is_null($$ = token_type(
			quoted_string_type(this->mempool()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
quoted_string_entity :
	quoted_string_entity_char
	{
		quoted_string_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| quoted_string_entity quoted_string_entity_char
	{
		quoted_string_type & octets =
			*$1.cast<quoted_string_type>();
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
quoted_string_entity_char :
	qdtext
	| quoted_pair
	;
qdtext :
	'(' | ')' | printable_symbol_no_sp_parenthesis_dquote;
quoted_pair :
	'\\' CHAR
	{
		$$ = $2;
	}
	;

/**
  RFC2616, 3.1 HTTP Version.
 */
HTTP_Version :
	'H' 'T' 'T' 'P' '/' digits '.' digits
	{
		if (hryky_is_null($$ = token_type(
			version_type(
				$6.cast<version_type::major_type>(),
				$8.cast<version_type::minor_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 3.2.2 http URL.

  This syntax is described in the RFC2616 but not referred by other syntax.
 */
http_URL :
	'h' 't' 't' 'p' ':' '/' '/' uri_host
	| 'h' 't' 't' 'p' ':' '/' '/' uri_host uri_port
	| 'h' 't' 't' 'p' ':' '/' '/' uri_host path_absolute
	| 'h' 't' 't' 'p' ':' '/' '/' uri_host path_absolute uri_query
	| 'h' 't' 't' 'p' ':' '/' '/' uri_host uri_port path_absolute uri_query
	;

/**
  RFC2616, 3.3.1 Full Date.
 */
HTTP_date :
	date
	{
		date_type http_date;
		http_date.date(*$1.cast<hryky::date_type>());
		
		if (hryky_is_null($$ = token_type(http_date, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 3.3.2 Delta Seconds.
 */
delta_seconds :
	DIGIT
	{
		if (hryky_is_null($$ = token_type(
			chrono::seconds(ascii::to_digit($1.cast<octet_type>())),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| delta_seconds DIGIT
	{
		chrono::seconds & seconds = *$1.cast<chrono::seconds>();
		seconds = chrono::seconds(
			seconds.count() * 10
			+ ascii::to_digit($2.cast<octet_type>()));
		$$ = $1;
	}
	;
/**
  RFC2616, 3.6 Transfer Codings.
 */
transfer_coding :
	'c' 'h' 'u' 'n' 'k' 'e' 'd'
	| token_parameters
	;

/**
  RFC2616, 3.6.1 Chunked Transfer Coding.
 */
Chunked_Body :
	last_chunk trailer CRLF
	| chunks last_chunk trailer CRLF
chunks :
	chunk
	| chunks chunk;
chunk :
	chunk_size CRLF chunk_data CRLF
	| chunk_size chunk_extension CRLF chunk_data CRLF;
chunk_size :
	HEX
	| chunk_size HEX;
last_chunk :
	zeros CRLF
	| zeros chunk_extension CRLF;
chunk_extension :
	':' chunk_ext_name
	| ':' chunk_ext_name '=' chunk_ext_val
	| chunk_extension ':' chunk_ext_name
	| chunk_extension ':' chunk_ext_name '=' chunk_ext_val;
chunk_ext_name :
	http_token;
chunk_ext_val :
	http_token
	| quoted_string;
chunk_data :
	octets;
trailer :
	| entity_header CRLF
	| trailer entity_header CRLF
	;

/**
  RFC2616, 3.7 Media Types.
 */
media_type :
	http_token '/' http_token
	{
		media_type_type media_type(this->mempool());
		media_type.type_name(*$1.cast<octets_type>());
		media_type.subtype_name(*$3.cast<octets_type>());

		if (hryky_is_null($$ = token_type(media_type, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| media_type ';' LWSs http_token
	{
		media_type_type & media_type =
			*$1.cast<media_type_type>();
		if (!media_type.append(*$4.cast<parameter_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	| media_type ';' LWSs token_parameters
	{
		media_type_type & media_type =
			*$1.cast<media_type_type>();
		if (!media_type.append(*$4.cast<parameter_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;

/**
  RFC2616, 3.8 Product Tokens.
 */
product :
	http_token
	{
		if (hryky_is_null($$ = token_type(
			product_type(*$1.cast<header::token_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| http_token '/' product_version
	{
		if (hryky_is_null($$ = token_type(
			product_type(
				*$1.cast<header::token_type>(),
				*$3.cast<header::token_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
product_version :
	http_token;

/**
  RFC2616, 3.9 Quality Values.
 */
qvalue :
	'0'
	{
		$$ = token_type(0.0f);
	}
	| '1'
	{
		$$ = token_type(1.0f);
	}
	| '0' '.'
	{
		$$ = token_type(0.0f);
	}
	| '0' '.' digits1_3
	{
		octet_type const octet = $3.cast<octet_type>();
		if (10 > octet) {
			$$ = token_type(0.1f * octet);
		}
		else if (100 > octet) {
			$$ = token_type(0.01f * octet);
		}
		else {
			$$ = token_type(0.001f * octet);
		}
	}
	| '1' '.'
	{
		$$ = token_type(1.0f);
	}
	| '1' '.' zeros1_3
	{
		$$ = token_type(1.0f);
	}
	;

/**
  RFC2616, 3.10 Language Tags.
 */
language_tag :
	primary_tag
	| language_tag '-' subtag;
primary_tag :
	alphas1_8;
subtag :
	alphas1_8;

/**
  RFC2616, 3.11 Entity Tag.
 */
entity_tag :
	opaque_tag
	| weak opaque_tag;
weak :
	'W' '/';
opaque_tag :
	quoted_string;

/**
  RFC2616, 3.12 Range Units.
 */
range_unit :
	bytes_unit
	| other_range_unit;
bytes_unit :
	'b' 'y' 't' 'e' 's';
other_range_unit :
	http_token;

/**
  RFC2616, 4.1 HTTP Types.
 */
HTTP_message :
	Request
	| Response
	;
generic_message :
	start_line CRLF
	| start_line message_header_CRLFs CRLF
	| start_line CRLF message_body
	| start_line message_header_CRLFs CRLF message_body;
message_header_CRLFs :
	message_header
	| message_header_CRLFs message_header;
start_line :
	Request_Line
	| Status_Line;

/**
  RFC2616, 4.2 Message Headers.
 */
message_header :
	field_sequence CRLF
	{
		$$ = $1;
	}
	;
field_sequence :
	http_token ':'
	{
		octets_type const & name = *$1.cast<octets_type>();
		field::kind_type const kind(
			name.begin(), name.end(), [](
				octet_type const lhs, octet_type const rhs) {
				return lhs == ascii::to_lower(rhs);
			});
		
		if (hryky_is_null($$ = token_type(
			field::entity_type(kind, name), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| field_sequence LWS field_content
	{
		field::entity_type & field = *$1.cast<field::entity_type>();
		if (!field.append(*$3.cast<octets_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;
/**
  @note
  - suppresses the reduce/reduce conflict with LWS.
 */
field_content :
	octet_no_ws
	{
		octets_type content(this->mempool());
		if (!content.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(content, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| field_content field_content_char
	{
		octets_type & content = *$1.cast<octets_type>();
		if (!content.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
field_content_char :
	octet_no_ws | SP | HT;



/**
  RFC2616, 4.3 Message Body.
 */
message_body :
	entity_body;

/**
  RFC2616, 4.5 General Header Fields.
 */
general_header :
	message_header
// 	Cache_Control /* Section 14.9 */
// 	| Connection /* Section 14.10 */
// 	| Date /* Section 14.18 */
// 	| Pragma /* Section 14.32 */
// 	| Trailer /* Section 14.40 */
// 	| Transfer_Encoding /* Section 14.41 */
// 	| Upgrade /* Section 14.42 */
// 	| Via /* Section 14.45 */
// 	| Warning /* Section 14.46 */
	;

/**
  RFC2616, 5 Request.
  @note
  - includes CRLF for the end of line to the definition of each header.
  - The message body is read outside this parser.
 */
Request :
	Request_Line CRLF
	{
		// @todo request_type * request = $1.cast<request_type>();
		$$ = $1;
	}
	| Request_Line request_headers CRLF
	{
		// request_type * request = $1.cast<request_type>();
		// @todo request->header(*$2.cast<Entity>());
		$$ = $1;
	}
	;
request_headers :
	request_headers_field
	{
		$$ = $1;
	}
	| request_headers request_headers_field
	{
		$$ = $1;
	}
	;
/**
  RFC2616, 4.5 General Header Fields.
  RFC2616, 5.3 Request Header Fields.
  RFC2616, 7.1 Entity Header Fields.
 */
request_headers_field :
	message_header
// 	Cache_Control /* Section 14.9 */
// 	| Connection /* Section 14.10 */
// 	| Date /* Section 14.18 */
// 	| Pragma /* Section 14.32 */
// 	| Trailer /* Section 14.40 */
// 	| Transfer_Encoding /* Section 14.41 */
// 	| Upgrade /* Section 14.42 */
// 	| Via /* Section 14.45 */
// 	| Warning /* Section 14.46 */
// 	| Accept /* Section 14.1 */
// 	// | Accept_Charset /* Section 14.2 */ same as Accept-Encoding
// 	| Accept_Encoding /* Section 14.3 */
// 	| Accept_Language /* Section 14.4 */
// 	| Authorization /* Section 14.8 */
// 	| Expect /* Section 14.20 */
// 	| From /* Section 14.22 */
// 	| Host /* Section 14.23 */
// 	| If_Match /* Section 14.24 */
// 	// | If_Modified_Since /* Section 14.25 */ same as Date
// 	// | If_None_Match /* Section 14.26 */ same as If-Match
// 	| If_Range /* Section 14.27 */
// 	// | If_Unmodified_Since /* Section 14.28 */ same as Date
// 	// | Max_Forwards /* Section 14.31 */ same as Content-Length
// 	// | Proxy_Authorization /* Section 14.34 */ same as Authorization
// 	| Range /* Section 14.35 */
// 	// | Referer /* Section 14.36 */ same as Content-Length
// 	| TE /* Section 14.39 */
// 	| User_Agent /* Section 14.43 */
// 	| Allow /* Section 14.7 */
// 	| Content_Encoding /* Section 14.11 */
// 	| Content_Language /* Section 14.12 */
// 	| Content_Length /* Section 14.13 */
// 	| Content_Location /* Section 14.14 */
// 	| Content_MD5 /* Section 14.15 */
// 	| Content_Range /* Section 14.16 */
// 	| Content_Type /* Section 14.17 */
// 	// | Expires /* Section 14.21 */ same as Date
// 	// | Last_Modified /* Section 14.29 */ same as Date
// 	| field_one_token
	;

/**
  RFC2616, 5.1 Request-Line.
 */
Request_Line :
	Method SP Request_URI SP HTTP_Version CRLF
	{
		if (hryky_is_null($$ = token_type(
			request::line_type(
				*$1.cast<method_type>(),
				*$3.cast<uri_type>(),
				*$5.cast<version_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 5.1.1 Method.
 */
Method :
	http_token
	{
		octets_type const & octets = *$1.cast<octets_type>();
		method::kind_type const kind(
			octets.begin(), octets.end(), [](
				octet_type const lhs, octet_type const rhs) {
				return lhs == ascii::to_lower(rhs);
			});

		if (hryky_is_null($$ = token_type(
			method_type(kind), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
extension_method :
	http_token;

/**
  RFC2616, 5.1.2 Request-URI.

  @note
  - If Request_URI is '*', the http_token is seemed to be reg_name.
  - The expression for default action is distinguished out of this parser.
 */
Request_URI :
	absolute_URI
	| path_absolute
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.path(*$1.cast<uri::path_type>());
		uri_type path(this->mempool());
		path.hierarchy(hierarchy);

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| authority
	{
		uri::hierarchy_type hierarchy(this->mempool());
		hierarchy.authority(*$1.cast<uri::authority_type>());
		uri_type path(this->mempool());
		path.hierarchy(hierarchy);

		if (hryky_is_null($$ = token_type(path, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 4.5 General Header Fields.
  RFC2616, 6 Response
  RFC2616, 6.2 Response Header Fields.
  RFC2616, 7.1 Entity Header Fields.
  @note
  - includes CRLF for the end of line to the definition of each header.
  - The message body is read outside this parser.
 */
Response :
	Status_Line CRLF
	| Status_Line response_headers CRLF
	;
response_headers :
	response_headers_field
	| response_headers response_headers_field
	;
response_headers_field :
	message_header
// 	Cache_Control /* Section 14.9 */
// 	| Connection /* Section 14.10 */
// 	| Date /* Section 14.18 */
// 	| Pragma /* Section 14.32 */
// 	| Trailer /* Section 14.40 */
// 	| Transfer_Encoding /* Section 14.41 */
// 	| Upgrade /* Section 14.42 */
// 	| Via /* Section 14.45 */
// 	| Warning /* Section 14.46 */
// 	| Accept_Ranges /* Section 14.5 */
// 	| Age /* Section 14.6 */
// 	| ETag /* Section 14.19 */
// 	| Location /* Section 14.30 */
// 	| Proxy_Authenticate /* Section 14.33 */
// 	| Retry_After /* Section 14.37 */
// 	| Server /* Section 14.38 */
// 	| Vary /* Section 14.44 */
// 	| WWW_Authenticate /* Section 14.47 */
// 	| Allow /* Section 14.7 */
// 	| Content_Encoding /* Section 14.11 */
// 	| Content_Language /* Section 14.12 */
// 	| Content_Length /* Section 14.13 */
// 	| Content_Location /* Section 14.14 */
// 	| Content_MD5 /* Section 14.15 */
// 	| Content_Range /* Section 14.16 */
// 	| Content_Type /* Section 14.17 */
// 	// | Expires /* Section 14.21 */ same as Date
// 	// | Last_Modified /* Section 14.29 */ same as Date
// 	| field_one_token
	;

/**
  RFC2616, 6.1 Status-Line.
 */
Status_Line :
	HTTP_Version SP Status_Code SP Reason_Phrase CRLF
	| HTTP_Version SP Status_Code SP CRLF
	;

/**
  RFC2616, 6.1.1 Status Code and Reason Phrase.
  
  Section 10.1.1:  100  Continue
  Section 10.1.2:  101  Switching Protocols
  Section 10.2.1:  200  OK
  Section 10.2.2:  201  Created
  Section 10.2.3:  202  Accepted
  Section 10.2.4:  203  Non-Authoritative Information
  Section 10.2.5:  204  No Content
  Section 10.2.6:  205  Reset Content
  Section 10.2.7:  206  Partial Content
  Section 10.3.1:  300  Multiple Choices
  Section 10.3.2:  301  Moved Permanently
  Section 10.3.3:  302  Found
  Section 10.3.4:  303  See Other
  Section 10.3.5:  304  Not Modified
  Section 10.3.6:  305  Use Proxy
  Section 10.3.8:  307  Temporary Redirect
  Section 10.4.1:  400  Bad Request
  Section 10.4.2:  401  Unauthorized
  Section 10.4.3:  402  Payment Required
  Section 10.4.4:  403  Forbidden
  Section 10.4.5:  404  Not Found
  Section 10.4.6:  405  Method Not Allowed
  Section 10.4.7:  406  Not Acceptable
  Section 10.4.8:  407  Proxy Authentication Required
  Section 10.4.9:  408  Request Time-out
  Section 10.4.10: 409  Conflict
  Section 10.4.11: 410  Gone
  Section 10.4.12: 411  Length Required
  Section 10.4.13: 412  Precondition Failed
  Section 10.4.14: 413  Request Entity Too Large
  Section 10.4.15: 414  Request-URI Too Large
  Section 10.4.16: 415  Unsupported Media Type
  Section 10.4.17: 416  Requested range not satisfiable
  Section 10.4.18: 417  Expectation Failed
  Section 10.5.1:  500  Internal Server Error
  Section 10.5.2:  501  Not Implemented
  Section 10.5.3:  502  Bad Gateway
  Section 10.5.4:  503  Service Unavailable
  Section 10.5.5:  504  Gateway Time-out
  Section 10.5.6:  505  HTTP Version not supported

  and extension code.
 */
Status_Code :
	| digits3
	;
Reason_Phrase :
	Reason_Phrase_char
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| Reason_Phrase Reason_Phrase_char
	{
		octets_type & octets = *$1.cast<octets_type>();
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
Reason_Phrase_char :
	printable_symbol | ALPHA | DIGIT | HT;

/**
  RFC2616, 7.1 Entity Header Fields.
 */
entity_header :
	message_header
// 	Allow /* Section 14.7 */
// 	| Content_Encoding /* Section 14.11 */
// 	| Content_Language /* Section 14.12 */
// 	| Content_Length /* Section 14.13 */
// 	| Content_Location /* Section 14.14 */
// 	| Content_MD5 /* Section 14.15 */
// 	| Content_Range /* Section 14.16 */
// 	| Content_Type /* Section 14.17 */
// 	// | Expires /* Section 14.21 */ same as Date
// 	// | Last_Modified /* Section 14.29 */ same as Date
// 	| Date
// 	| field_one_token
	;
extension_header :
	message_header
	;

/**
  RFC2616, 7.2 Entity Body.
 */
entity_body :
	octets;

field_name :
	http_token
	{
		octets_type const & name = *$1.cast<octets_type>();
		field::kind_type const kind(
			name.begin(), name.end(), [](
				octet_type const lhs, octet_type const rhs) {
				return lhs == ascii::to_lower(rhs);
			});
		
		if (hryky_is_null($$ = token_type(
			field::entity_type(kind, name), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.1 Accept.
 */
Accept :
	field_name ':' Accept_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::accept) {
			KMYACC_ABORT;
		}
	}
	;
Accept_value :
	LWSs CRLF
	{
		if (hryky_is_null($$ = this->derived()->create_field_token(
			accept_type(this->mempool())))) {
			KMYACC_ABORT;
		}
	}
	| LWSs media_range_accept_params_LWS CRLF
	{
		accept_type accept(this->mempool());
		accept_contents_type & contents =
			*$2.cast<accept_contents_type>();

		Foreach<accept_contents_type> foreach(contents);
		for (; foreach.valid(); ++foreach) {
			if (!accept.append(*foreach)) {
				KMYACC_ABORT;
			}
		}
		
		if (hryky_is_null($$ = this->derived()->create_field_token(accept))) {
			KMYACC_ABORT;
		}
	}
	;
media_range_accept_params_LWS :
	media_range_accept_param
	{
		accept_contents_type contents(this->mempool());
		if (!contents.push_back(*$1.cast<accept::content_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(contents, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| media_range_accept_params_LWS LWSs ',' LWSs media_range_accept_param
	{
		accept_contents_type & contents =
			*$1.cast<accept_contents_type>();
		if (!contents.push_back(*$5.cast<accept::content_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
media_range_accept_param :
	media_range
	{
		accept::content_type content(this->mempool());
		content.media_range(*$1.cast<media_type_type>());

		if (hryky_is_null($$ = token_type(content, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| media_range accept_params
	{
		accept::content_type content(this->mempool());
		content.media_range(*$1.cast<media_type_type>());
		content.params(*$2.cast<accept::params_type>());

		if (hryky_is_null($$ = token_type(content, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
/**
  @note
  - suppresses the reduce/reduce conflict with '*'.
 */
media_range :
	'*' '/' '*'
	{
		media_type_type range(this->mempool());

		if (hryky_is_null($$ = token_type(range, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| http_token '/' '*'
	{
		media_type_type range(this->mempool());
		range.type_name(*$1.cast<octets_type>());

		if (hryky_is_null($$ = token_type(range, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| '*' '/' http_token
	{
		media_type_type range(this->mempool());
		range.subtype_name(*$3.cast<octets_type>());

		if (hryky_is_null($$ = token_type(range, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| http_token '/' http_token
	{
		media_type_type range(this->mempool());
		range.type_name(*$1.cast<octets_type>());
		range.subtype_name(*$3.cast<octets_type>());

		if (hryky_is_null($$ = token_type(range, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| media_range ';' token_parameters
	{
		media_type_type & range =
			*$1.cast<media_type_type>();
		if (!range.append(*$3.cast<parameter_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	| media_range ';' http_token
	{
		media_type_type & range =
			*$1.cast<media_type_type>();
		if (!range.append(*$3.cast<parameter_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
accept_params :
	';' 'q' '=' qvalue
	{
		accept::params_type params(this->mempool());
		params.qvalue($4.cast<qvalue_type>());
		
		if (hryky_is_null($$ = token_type(params, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| accept_params accept_extension
	{
		accept::params_type & params =
			*$1.cast<accept::params_type>();
		if (!params.append(*$2.cast<accept::extension_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;
accept_extension :
	';' http_token
	{
		if (hryky_is_null($$ = token_type(
			accept::extension_type(
				*$2.cast<accept::extension::key_type>(),
				accept::extension::value_type(this->mempool())),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ';' http_token '=' http_token
	{
		if (hryky_is_null($$ = token_type(
			accept::extension_type(
				*$2.cast<accept::extension::key_type>(),
				*$4.cast<accept::extension::value_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ';' http_token '=' quoted_string
	{
		if (hryky_is_null($$ = token_type(
			accept::extension_type(
				*$2.cast<accept::extension::key_type>(),
				*$4.cast<accept::extension::value_type>()),
			this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.3 Accept-Encoding.
  RFC2616, 14.2 Accept-Charset.
  @todo create common class which retain combinations of token and qvalue.
 */
Accept_Encoding :
	field_name ':' LWSs accept_encoding_values_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::accept_encoding &&
			name.kind() != field::Kind::accept_charset) {
			KMYACC_ABORT;
		}
		
		accept::encoding_type encoding(this->mempool());
		accept_encoding_contents_type & contents =
			*$4.cast<accept_encoding_contents_type>();

		Foreach<accept_encoding_contents_type> foreach(contents);
		for (; foreach.valid(); ++foreach) {
			if (!encoding.append(*foreach)) {
				KMYACC_ABORT;
			}
		}
		
		if (hryky_is_null($$ = this->derived()->create_field_token(encoding))) {
			KMYACC_ABORT;
		}
	}
	;
accept_encoding_values_LWS :
	accept_encoding_qvalue
	{
		accept_encoding_contents_type contents(this->mempool());
		if (!contents.push_back(*$1.cast<accept::encoding::content_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(contents, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| accept_encoding_values_LWS LWSs ',' LWSs accept_encoding_value
	{
		accept_encoding_contents_type & contents =
			*$1.cast<accept_encoding_contents_type>();
		if (!contents.push_back(*$5.cast<accept::encoding::content_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
accept_encoding_value :
	http_token
	{
		accept::encoding::content_type content(this->mempool());
		content.coding(*$1.cast<octets_type>());

		if (hryky_is_null($$ = token_type(content, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| accept_encoding_qvalue
	;
accept_encoding_qvalue :
	http_token ';' 'q' '=' qvalue
	{
		accept::encoding::content_type content(this->mempool());
		content.coding(*$1.cast<octets_type>());
		content.qvalue($5.cast<qvalue_type>());

		if (hryky_is_null($$ = token_type(content, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
	


/**
  RFC2616, 14.4 Accept-Language.
 */
Accept_Language :
	field_name ':' LWSs accept_language_values_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::accept_language) {
			KMYACC_ABORT;
		}
		
		accept::language_type language(this->mempool());
		accept_language_contents_type & contents =
			*$4.cast<accept_language_contents_type>();

		Foreach<accept_language_contents_type> foreach(contents);
		for (; foreach.valid(); ++foreach) {
			if (!language.append(*foreach)) {
				KMYACC_ABORT;
			}
		}

		if (hryky_is_null($$ = this->derived()->create_field_token(language))) {
			KMYACC_ABORT;
		}
	}
	;
accept_language_values_LWS :
	accept_language_value
	{
		accept_language_contents_type contents(this->mempool());
		if (!contents.push_back(*$1.cast<accept::language::content_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(contents, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| accept_language_values_LWS LWSs ',' LWSs accept_language_value
	{
		accept_language_contents_type & contents =
			*$1.cast<accept_language_contents_type>();
		if (!contents.push_back(*$5.cast<accept::language::content_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
accept_language_value :
	language_range
	{
		accept::language::content_type content(this->mempool());
		content.language(*$1.cast<language_type>());

		if (hryky_is_null($$ = token_type(content, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| language_range ';' 'q' '=' qvalue
	{
		accept::language::content_type content(this->mempool());
		content.language(*$1.cast<language_type>());
		content.qvalue($5.cast<qvalue_type>());

		if (hryky_is_null($$ = token_type(content, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
language_range :
	language_range_alpha
	| '*'
	{
		language_type language(this->mempool());

		if (hryky_is_null($$ = token_type(language, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
language_range_alpha :
	alphas1_8
	{
		language_type language(this->mempool());
		language.primary(*$1.cast<language::tag_type>());

		if (hryky_is_null($$ = token_type(language, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| language_range_alpha '-' alphas1_8
	{
		language_type & language =
			*$1.cast<language_type>();
		if (!language.append(*$3.cast<language::tag_type>())) {
			KMYACC_ABORT;
		}
		
		$$ = $1;
	}
	;

/**
  RFC2616, 14.5 Accept-Ranges.
 */
Accept_Ranges :
	field_name ':' Accept_Ranges_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::accept_ranges) {
			KMYACC_ABORT;
		}
	}
	;
Accept_Ranges_value :
	LWSs range_units_LWS CRLF
	| LWSs 'n' 'o' 'n' 'e' CRLF
	;
range_units_LWS :
	range_unit
	| range_units_LWS LWSs ',' LWSs range_unit;

/**
  RFC2616, 14.6 Age.
 */
Age :
	field_name ':' LWSs age_value CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::age) {
			KMYACC_ABORT;
		}
	}
	;
age_value :
	delta_seconds;

/**
  RFC2616, 14.7 Allow.
 */
Allow :
	field_name ':' Allow_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::allow) {
			KMYACC_ABORT;
		}
	}
	;
Allow_value :
	LWSs CRLF
	| LWSs Methods_LWS CRLF
	;
Methods_LWS :
	Method
	| Methods_LWS LWSs ',' LWSs Method
	;

/**
  RFC2616, 14.8 Authorization.
  RFC2616, 14.34 Proxy-Authorization.
 */
Authorization :
	field_name ':' LWSs credentials CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::authorization &&
			name.kind() != field::Kind::proxy_authorization) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.9 Cache-Control.
 */
Cache_Control :
	field_name ':' LWSs cache_directives_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::cache_control) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = this->derived()->create_field_token(
			*$4.cast<cache::control_type>()))) {
			KMYACC_ABORT;
		}
	}
	;
cache_directives_LWS :
	cache_directive
	{
		cache::control_type control(
			this->mempool());
		cache_directive_ptr_type & directive =
			*$1.cast<cache_directive_ptr_type>();
		cache::directive::dispatcher::Apply apply(control);
		directive->dispatch(apply);

		if (hryky_is_null($$ = token_type(control, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| cache_directives_LWS LWSs ',' LWSs cache_directive
	{
		cache::control_type & control =
			*$1.cast<cache::control_type>();
		cache_directive_ptr_type & directive =
			*$5.cast<cache_directive_ptr_type>();
		cache::directive::dispatcher::Apply apply(control);
		directive->dispatch(apply);

		$$ = $1;
	}
	;
cache_directive :
	cache_directive_name_only
	| cache_directive_delta
	| cache_directive_field_names
	| cache_directive_token
	| cache_directive_quoted_string
	;
cache_directive_name_only :
	cache_directive_name
	{
		cache::directive::field_type const & field = *$1.cast<
			cache::directive::field_type>();

		switch (field.kind().raw()) {
		case cache::directive::Kind::min_fresh:
		case cache::directive::Kind::s_maxage:
		case cache::directive::Kind::max_age:
			KMYACC_ABORT;
		default:
			break;
		}
		
		$$ = $1;
	}
	;
cache_directive_delta :
	cache_directive_name '=' delta_seconds
	{
		cache::directive::field_type const & field = *$1.cast<
			cache::directive::field_type>();

		switch (field.kind().raw()) {
		case cache::directive::Kind::extention:
		case cache::directive::Kind::max_stale:
		case cache::directive::Kind::min_fresh:
		case cache::directive::Kind::s_maxage:
		case cache::directive::Kind::max_age:
			break;
		default:
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = this->derived()->create_cache_directive_token(
			cache::directive::seconds_type(
				field.kind(),
				*$3.cast<cache::seconds_type>())))) {
			KMYACC_ABORT;
		}
	}
	;
cache_directive_field_names :
	cache_directive_name '=' '"' field_names_LWS '"'
	{
		cache::directive::field_type const & field = *$1.cast<
			cache::directive::field_type>();

		switch (field.kind().raw()) {
		case cache::directive::Kind::as_private:
		case cache::directive::Kind::no_cache:
			break;
		default:
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = this->derived()->create_cache_directive_token(
			cache::directive::field_type(
				cache::directive::Kind::as_private,
				*$4.cast<field_kinds_type>())))) {
			KMYACC_ABORT;
		}
	}
	;
cache_directive_token :
	cache_directive_name '=' http_token_no_digits
	{
		$$ = $1;
	}
	;
cache_directive_quoted_string :
	cache_directive_name '=' quoted_string
	{
		$$ = $1;
	}
	;
cache_directive_name :
	http_token
	{
		octets_type const & octets = *$1.cast<octets_type>();
		cache::directive::kind_type const kind(
			octets.begin(), octets.end(), [](
				octet_type const lhs, octet_type const rhs) {
				return lhs == ascii::to_lower(rhs);
			});
		if (hryky_is_null($$ = token_type(
			cache::directive::Field(kind, this->mempool()), this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.10 Connection.
 */
Connection :
	field_name ':' LWSs connection_tokens_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::connection) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = this->derived()->create_field_token(
			*$4.cast<connection_type>()))) {
			KMYACC_ABORT;
		}
	}
	;
connection_tokens_LWS :
	connection_token
	{
		connection_type connection;
		if (!connection.append(*$1.cast<connection_type::token_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(connection, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| connection_tokens_LWS LWSs ',' LWSs connection_token
	{
		connection_type & connection =
			*$1.cast<connection_type>();
		if (!connection.append(*$5.cast<connection_type::token_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
connection_token :
	http_token
	;

/**
  RFC2616, 14.11 Content-Encoding.
 */
Content_Encoding :
	field_name ':' LWSs content_codings_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_encoding) {
			KMYACC_ABORT;
		}
	}
	;
content_codings_LWS :
	http_token ',' LWSs http_token
	| content_codings_LWS LWSs ',' LWSs http_token
	;

/**
  RFC2616, 14.11 Content-Encoding.
  RFC2616, 14.3 Accept-Encoding.
  RFC2616, 14.41 Transfer-Encoding.
  RFC2616, 14.39 TE.
 */
field_one_token :
	field_name ':' LWSs http_token CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_encoding &&
			name.kind() != field::Kind::accept_encoding &&
			name.kind() != field::Kind::transfer_encoding &&
			name.kind() != field::Kind::te) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.12 Content-Language.
 */
Content_Language :
	field_name ':' LWSs language_tags_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_language) {
			KMYACC_ABORT;
		}
	}
	;
language_tags_LWS :
	language_tag
	| language_tags_LWS LWSs ',' LWSs language_tag
	;

/**
  RFC2616, 14.13 Content-Length.
  RFC2616, 14.31 Max-Forwards.
 */
Content_Length :
	field_name ':' LWSs digits CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_length &&
			name.kind() != field::Kind::max_forwards) {
			KMYACC_ABORT;
		}
		
		content::length_type const length(
			$4.cast<content::length_type::value_type>());

		if (hryky_is_null($$ = this->derived()->create_field_token(length))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.14 Content-Location.
  RFC2616, 14.36 Referer.
 */
Content_Location :
	field_name ':' LWSs relativeURI CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_location &&
			name.kind() != field::Kind::referer) {
			KMYACC_ABORT;
		}
	}
	;

relativeURI :
	uri_relative_part
	| uri_relative_part uri_query
	;

/**
  RFC2616, 14.15 Content-MD5.
 */
Content_MD5 :
	field_name ':' LWSs md5_digest CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_md5) {
			KMYACC_ABORT;
		}
	}
	;
md5_digest :
	base64_alpha_npad base64_alpha_npad base64_alpha_npad base64_alpha_npad
	base64_alpha_npad base64_alpha_npad base64_alpha_npad base64_alpha_npad
	base64_alpha_npad base64_alpha_npad base64_alpha_npad base64_alpha_npad
	base64_alpha_npad base64_alpha_npad base64_alpha_npad base64_alpha_npad
	base64_alpha_npad base64_alpha_npad base64_alpha_npad base64_alpha_npad
	base64_alpha_npad base64_alpha_npad base64_alpha_pad base64_alpha_pad;

/**
  RFC2616, 14.16 Content-Range.
 */
Content_Range :
	field_name ':' LWSs content_range_spec CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_range) {
			KMYACC_ABORT;
		}
	}
	;
content_range_spec :
	byte_content_range_spec;
byte_content_range_spec :
	bytes_unit SP byte_range_resp_spec '/' instance_length
	| bytes_unit SP byte_range_resp_spec '/' '*';
byte_range_resp_spec :
	'*'
	| first_byte_pos '-' last_byte_pos;
instance_length :
	digits;

/**
  RFC2616, 14.17 Content-Type.
 */
Content_Type :
	field_name ':' LWSs media_type CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::content_type) {
			KMYACC_ABORT;
		}
		
		content::type_type type(this->mempool());
		type.media_type(*$4.cast<media_type_type>());

		if (hryky_is_null($$ = this->derived()->create_field_token(type))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.18 Date.
  RFC2616, 14.21 Expires.
  RFC2616, 14.29 Last-Modified.
  RFC2616, 14.37 Retry-After.
  RFC2616, 14.25 If-Modified-Since.
  RFC2616, 14.27 If-Range.
  RFC2616, 14.28 If-Unmodified-Since.
 */
Date :
	field_name ':' LWSs HTTP_date CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::date &&
			name.kind() != field::Kind::expires &&
			name.kind() != field::Kind::last_modified &&
			name.kind() != field::Kind::retry_after &&
			name.kind() != field::Kind::if_modified_since &&
			name.kind() != field::Kind::if_range &&
			name.kind() != field::Kind::if_unmodified_since) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = this->derived()->create_field_token(
			*$4.cast<date_type>()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.19 ETag.
 */
ETag :
	field_name ':' LWSs entity_tag CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::etag) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.20 Expect.
 */
Expect :
	field_name ':' LWSs expectations_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::expect) {
			KMYACC_ABORT;
		}
	}
	;
expectations_LWS :
	expectation
	| expectations_LWS LWSs ',' LWSs expectation
	;
expectation :
	'1' '0' '0' '-' 'c' 'o' 'n' 't' 'i' 'n' 'u' 'e'
	| token_parameters
	;

token_parameter :
	http_token
	| http_token_equal_token
	| http_token_equal_quoated_string
	;

/**
  http_token must not be at the beginning.
 */
token_parameters :
	token_parameters ';' token_parameter
	| http_token_equal_token
	| http_token_equal_quoated_string
	;
http_token_equal_token :
	http_token '=' http_token
	;
http_token_equal_quoated_string :
	http_token '=' quoted_string
	;

/**
  RFC2616,  14.20 Expect.
            14.32 Pragma
 */
Expect_Pragma :
	field_name ':' LWSs token_parameter CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::expect &&
			name.kind() != field::Kind::pragma) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.22 From.
 */
From :
	field_name ':' LWSs imf_mailbox CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::from) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.23 Host.
 */
Host :
	field_name ':' Host_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::host) {
			KMYACC_ABORT;
		}
	}
	;
Host_value :
	LWSs uri_host CRLF
	{
		host_type host(this->mempool());
		host.host(*$2.cast<uri::host_type>());
		
		if (hryky_is_null($$ = this->derived()->create_field_token(host))) {
			KMYACC_ABORT;
		}
	}
	| LWSs uri_host uri_port CRLF
	{
		host_type host(this->mempool());
		host.host(*$2.cast<uri::host_type>());
		host.port(*$3.cast<uri::port_type>());
		
		if (hryky_is_null($$ = this->derived()->create_field_token(host))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.24 If-Match.
  RFC2616, 14.26 If-None-Match.
 */
If_Match :
	field_name ':' If_Match_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::if_match &&
			name.kind() != field::Kind::if_none_match) {
			KMYACC_ABORT;
		}
	}
	;
If_Match_value :
	LWSs '*' CRLF
	| LWSs entity_tags_LWS CRLF
	;
entity_tags_LWS :
	entity_tag
	| entity_tags_LWS LWSs ',' LWSs entity_tag;

/**
  RFC2616, 14.27 If-Range.
 */
If_Range :
	field_name ':' If_Range_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::if_range) {
			KMYACC_ABORT;
		}
	}
	;
If_Range_value :
	LWSs entity_tag CRLF
	;

/**
  RFC2616, 14.30 Location.
  RFC2616, 14.14 Content-Location.
  RFC2616, 14.36 Referer.
 */
Location :
	field_name ':' LWSs absolute_URI CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::location &&
			name.kind() != field::Kind::content_location &&
			name.kind() != field::Kind::referer) {
			KMYACC_ABORT;
		}
		
		location_type location(this->mempool());
		location.uri(*$4.cast<uri_type>());

		if (hryky_is_null($$ = this->derived()->create_field_token(location))) {
			KMYACC_ABORT;
		}
	}
	;


/**
  RFC2616, 14.32 Pragma.
 */
Pragma :
	field_name ':' LWSs pragma_directives_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::pragma) {
			KMYACC_ABORT;
		}
	}
	;
pragma_directives_LWS :
	no_cache
	| pragma_directives_LWS LWSs ',' LWSs no_cache
	| pragma_directives_LWS LWSs ',' LWSs token_parameter
	;

no_cache :
	'n' 'o' '-' 'c' 'a' 'c' 'h' 'e';

/**
  RFC2616, 14.33 Proxy-Authenticate.
 */
Proxy_Authenticate :
	field_name ':' LWSs challenge CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::proxy_authenticate) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.35 Range.
 */
Range :
	field_name ':' LWSs ranges_specifier CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::range) {
			KMYACC_ABORT;
		}
	}
	;
ranges_specifier :
	byte_range_specifier;
byte_range_specifier :
	bytes_unit '=' byte_range_set;
byte_range_set :
	LWSs byte_range_set_element
	| byte_range_set LWSs ',' LWSs byte_range_set_element;
byte_range_set_element :
	byte_range_spec
	| suffix_byte_range_spec;
byte_range_spec :
	first_byte_pos '-'
	| first_byte_pos '-' last_byte_pos;
first_byte_pos :
	digits;
last_byte_pos :
	digits;
suffix_byte_range_spec :
	'-' suffix_length;
suffix_length :
	digits;

/**
  RFC2616, 14.37 Retry-After.
 */
Retry_After :
	field_name ':' LWSs delta_seconds CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::retry_after) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.38 Server.
 */
Server :
	field_name ':' LWSs product_comments_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::server) {
			KMYACC_ABORT;
		}
		
		server_type server(this->mempool());
		product_comment_ptrs_type const & product_comments =
			*$4.cast<product_comment_ptrs_type>();
		product_comment::dispatcher::Apply<server_type>
			apply(server);

		Foreach<product_comment_ptrs_type const> foreach(product_comments);
		for (; foreach.valid(); ++foreach) {
			product_comment_ptr_type const & product_comment = *foreach;
			product_comment->dispatch(apply);
		}

		if (hryky_is_null($$ = this->derived()->create_field_token(server))) {
			KMYACC_ABORT;
		}
	}
	;
product_comments_LWS :
	product_comment
	{
		product_comment_ptrs_type product_comments(this->mempool());
		if (!product_comments.push_back(*$1.cast<product_comment_ptr_type>())) {
			KMYACC_ABORT;
		}

		if (hryky_is_null($$ = token_type(product_comments, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| product_comments_LWS LWS product_comment
	{
		product_comment_ptrs_type & product_comments =
			*$1.cast<product_comment_ptrs_type>();
		if (!product_comments.push_back(*$3.cast<product_comment_ptr_type>())) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
product_comment :
	product
	{
		if (hryky_is_null($$ = this->derived()->create_adapter_token<
				product_comment::Adapter>(
					*$1.cast<product_type>()))) {
			KMYACC_ABORT;
		}
	}
	| comment
	{
		if (hryky_is_null($$ = this->derived()->create_adapter_token<
				product_comment::Adapter>(
					*$1.cast<comment::sequence_type>()))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.39 TE.
 */
TE :
	field_name ':' TE_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::te) {
			KMYACC_ABORT;
		}
	}
	;
TE_value :
	LWSs CRLF
	| LWSs t_codings_LWS CRLF
	;
t_codings_LWS :
	t_codings
	| t_codings_LWS LWSs ',' LWSs t_codings;
t_codings :
	't' 'r' 'a' 'i' 'l' 'e' 'r' 's'
	| token_parameters
	;

/**
  RFC2616, 14.40 Trailer.
 */
Trailer :
	field_name ':' LWSs field_names_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::trailer) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.41 Transfer-Encoding.
 */
Transfer_Encoding :
	field_name ':' LWSs transfer_codings_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::transfer_encoding) {
			KMYACC_ABORT;
		}
	}
	;
transfer_codings_LWS :
	transfer_coding
	| transfer_codings_LWS LWSs ',' LWSs transfer_coding
	;

/**
  RFC2616, 14.42 Upgrade.
 */
Upgrade :
	field_name ':' LWSs products_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::upgrade) {
			KMYACC_ABORT;
		}
	}
	;
products_LWS :
	product
	| products_LWS LWSs ',' LWSs product
	;

/**
  RFC2616, 14.43 User-Agent.
 */
User_Agent :
	field_name ':' LWSs product_comments_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::user_agent) {
			KMYACC_ABORT;
		}
		
		user_agent_type user_agent(this->mempool());
		product_comment_ptrs_type const & product_comments =
			*$4.cast<product_comment_ptrs_type>();
		product_comment::dispatcher::Apply<user_agent_type>
			apply(user_agent);

		Foreach<product_comment_ptrs_type const> foreach(product_comments);
		for (; foreach.valid(); ++foreach) {
			product_comment_ptr_type const & product_comment = *foreach;
			product_comment->dispatch(apply);
		}

		if (hryky_is_null($$ = this->derived()->create_field_token(user_agent))) {
			KMYACC_ABORT;
		}
	}
	;

/**
  RFC2616, 14.44 Vary.
 */
Vary :
	field_name ':' Vary_value
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::vary) {
			KMYACC_ABORT;
		}
	}
	;
Vary_value :
	LWSs '*' CRLF
	| LWSs field_names_LWS CRLF
	;

/**
  RFC2616, 14.45 Via.
 */
Via :
	field_name ':' LWSs via_entity_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::via) {
			KMYACC_ABORT;
		}
	}
	;
via_entity_LWS :
	via_entity
	| via_entity_LWS LWSs ',' LWSs via_entity;
via_entity :
	received_protocol received_by
	| received_protocol received_by comment;
received_protocol :
	protocol_version
	| protocol_name '/' protocol_version;
protocol_name :
	http_token;
protocol_version :
	http_token;
received_by :
	uri_host_with_pseudonym
	| uri_host uri_port
	;
/**
  To avoid the reduce/reduce conflict with reg_name, pseudonym must include
  one or more character which does not be included in reg_name.
 */
pseudonym :
	pseudonym_char
	| http_token pseudonym_char
	| pseudonym http_token
	;
pseudonym_char :
	'^' | '|' | '`'
	;
/**
  @note
  - The determination between IPv4address and reg_name is not supported.
 */
uri_host_with_pseudonym :
	uri_host
	| reg_name_with_pseudonym
	{
		uri::host_type host(this->mempool());
		host.regname(
			uri::regname_type(*$1.cast<octets_type>()));
		
		if (hryky_is_null($$ = token_type(host, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
reg_name_with_pseudonym :
	pseudonym_char
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| reg_name pseudonym_char
	{
		octets_type * const octets = $1.cast<octets_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	| reg_name_with_pseudonym reg_name
	{
		octets_type * const first = $1.cast<octets_type>();
		octets_type * const second = $2.cast<octets_type>();
		if (!first->insert(first->end(), second->begin(), second->end())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	| reg_name_with_pseudonym pseudonym_char
	{
		octets_type * const octets = $1.cast<octets_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;


/**
  RFC2616, 14.46 Warning.
 */
Warning :
	field_name ':' LWSs warning_values_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::warning) {
			KMYACC_ABORT;
		}
	}
	;
warning_values_LWS :
	warning_value
	| warning_values_LWS LWSs ',' LWSs warning_value
	;
warning_value :
	warn_code SP warn_agent SP warn_text
	| warn_code SP warn_agent SP warn_text SP warn_data
	;
warn_code :
	digits3;
warn_agent :
	uri_host_with_pseudonym
	| uri_host uri_port
	;
warn_text :
	quoted_string
	;
warn_data :
	'"' HTTP_date '"'
	;

/**
  RFC2616, 14.79 WWW-Authenticate.
 */
WWW_Authenticate :
	field_name ':' LWSs challenges_LWS CRLF
	{
		field::Entity const & name = *$1.cast<field::Entity>();
		if (name.kind() != field::Kind::www_authenticate) {
			KMYACC_ABORT;
		}
	}
	;
challenges_LWS :
	challenge
	| challenges_LWS LWSs '.' LWSs challenge
	;


/**
  RFC2617, 1.2 Access Authentication Framework.
 */
auth_scheme :
	http_token;
auth_param :
	http_token '=' http_token
	| http_token '=' quoted_string
	;
/**
  @note
  - SP between auth_scheme and auth_params_LWS is substituted with LWS.
 */
challenge :
	auth_scheme auth_params_LWS
	;
auth_params_LWS :
	LWSs auth_param
	| auth_params_LWS LWSs ',' LWSs auth_param
	;
realm :
	'r' 'e' 'a' 'l' 'm' '=' realm_value
	;
realm_value :
	quoted_string
	;
credentials :
	auth_scheme
	| auth_scheme auth_params_LWS
	;

/**
  internal components for HTTP Message.
 */
zeros :
	'0'
	| zeros '0';
zeros1_3 :
	'0'
	| '0' '0'
	| '0' '0' '0'
	;
octets :
	OCTET
	{
		octets_type octets(this->mempool());
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| octets OCTET
	{
		octets_type * octets = $1.cast<octets_type>();
		if (!octets->push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		$$ = $1;
	}
	;
alphas1_8 :
	ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA ALPHA ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($3.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA ALPHA ALPHA ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($3.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($4.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA ALPHA ALPHA ALPHA ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($3.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($4.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($5.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA ALPHA ALPHA ALPHA ALPHA ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($3.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($4.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($5.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($6.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA ALPHA ALPHA ALPHA ALPHA ALPHA ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($3.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($4.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($5.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($6.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($7.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| ALPHA ALPHA ALPHA ALPHA ALPHA ALPHA ALPHA ALPHA
	{
		language::tag_type octets;
		if (!octets.push_back($1.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($2.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($3.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($4.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($5.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($6.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($7.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (!octets.push_back($8.cast<octet_type>())) {
			KMYACC_ABORT;
		}
		if (hryky_is_null($$ = token_type(octets, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	;
field_names_LWS :
	LWSs field_name
	{
		field_kinds_type field_kinds(this->mempool());
		octets_type const & octets = *$2.cast<octets_type>();
		if (!field_kinds.push_back(field::kind_type(
			octets.begin(), octets.end()))) {
			KMYACC_ABORT;
		}
		
		if (hryky_is_null($$ = token_type(field_kinds, this->mempool()))) {
			KMYACC_ABORT;
		}
	}
	| field_names_LWS LWSs ',' LWSs field_name
	{
		field_kinds_type & field_kinds = *$1.cast<field_kinds_type>();
		octets_type const & octets = *$5.cast<octets_type>();
		if (!field_kinds.push_back(field::kind_type(
			octets.begin(), octets.end()))) {
			KMYACC_ABORT;
		}

		$$ = $1;
	}
	;
