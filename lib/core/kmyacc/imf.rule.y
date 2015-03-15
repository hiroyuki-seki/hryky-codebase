/**
  @file imf.rule.y
  @brief the 'rule' part of KMYACC grammar file for Internet Message Format.
  @version $Id: imf.rule.y 150 2013-02-10 10:08:03Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc5322/
 */
/**
  RFC5322, 3.2.1. Quoted characters.
 */
imf_quoted_pair :
	'\\' VCHAR
	| '\\' WSP;

/**
  RFC5322, 3.2.2. Folding White Space and Comments.
 */
imf_FWS :
	WSPs
	| CRLF WSPs
	| WSPs CRLF WSPs;
imf_FWS_or_empty :
	| imf_FWS;
imf_ctext :
	'\041' /* %d33 */ | '\042' /* %d34 */ | '\043' /* %d35 */ | '\044' /* %d36 */
	| '\045' /* %d37 */ | '\046' /* %d38 */ | '\047' /* %d39 */ | '\052' /* %d42 */
	| '\053' /* %d43 */ | '\054' /* %d44 */ | '\055' /* %d45 */ | '\056' /* %d46 */
	| '\057' /* %d47 */ | '\060' /* %d48 */ | '\061' /* %d49 */ | '\062' /* %d50 */
	| '\063' /* %d51 */ | '\064' /* %d52 */ | '\065' /* %d53 */ | '\066' /* %d54 */
	| '\067' /* %d55 */ | '\070' /* %d56 */ | '\071' /* %d57 */ | '\072' /* %d58 */
	| '\073' /* %d59 */ | '\074' /* %d60 */ | '\075' /* %d61 */ | '\076' /* %d62 */
	| '\077' /* %d63 */ | '\100' /* %d64 */ | '\101' /* %d65 */ | '\102' /* %d66 */
	| '\103' /* %d67 */ | '\104' /* %d68 */ | '\105' /* %d69 */ | '\106' /* %d70 */
	| '\107' /* %d71 */ | '\110' /* %d72 */ | '\111' /* %d73 */ | '\112' /* %d74 */
	| '\113' /* %d75 */ | '\114' /* %d76 */ | '\115' /* %d77 */ | '\116' /* %d78 */
	| '\117' /* %d79 */ | '\120' /* %d80 */ | '\121' /* %d81 */ | '\122' /* %d82 */
	| '\123' /* %d83 */ | '\124' /* %d84 */ | '\125' /* %d85 */ | '\126' /* %d86 */
	| '\127' /* %d87 */ | '\130' /* %d88 */ | '\131' /* %d89 */ | '\132' /* %d90 */
	| '\133' /* %d91 */ | '\135' /* %d93 */ | '\136' /* %d94 */ | '\137' /* %d95 */
	| '\140' /* %d96 */ | '\141' /* %d97 */ | '\142' /* %d98 */ | '\143' /* %d99 */
	| '\144' /* %d100 */ | '\145' /* %d101 */ | '\146' /* %d102 */ | '\147' /* %d103 */
	| '\150' /* %d104 */ | '\151' /* %d105 */ | '\152' /* %d106 */ | '\153' /* %d107 */
	| '\154' /* %d108 */ | '\155' /* %d109 */ | '\156' /* %d110 */ | '\157' /* %d111 */
	| '\160' /* %d112 */ | '\161' /* %d113 */ | '\162' /* %d114 */ | '\163' /* %d115 */
	| '\164' /* %d116 */ | '\165' /* %d117 */ | '\166' /* %d118 */ | '\167' /* %d119 */
	| '\170' /* %d120 */ | '\171' /* %d121 */ | '\172' /* %d122 */ | '\173' /* %d123 */
	| '\174' /* %d124 */ | '\175' /* %d125 */ | '\176' /* %d126 */
	;
imf_ccontent :
	imf_ctext
	| imf_quoted_pair
	| imf_comment
	;
imf_comment :
	'(' imf_FWS_or_empty ')'
	| '(' imf_comment_entity imf_FWS_or_empty ')'
	;
imf_comment_entity :
	imf_FWS_or_empty imf_ccontent
	| imf_comment_entity imf_FWS_or_empty imf_ccontent
	;
imf_CFWS :
	imf_FWS
	| imf_CFWS_entity
	| imf_CFWS_entity imf_FWS
	;
imf_CFWS_entity :
	imf_FWS imf_comment
	| imf_comment
	| imf_CFWS_entity imf_comment
	| imf_CFWS_entity imf_FWS imf_comment
	;
imf_CFWS_or_empty :
	| imf_CFWS;

/**
  RFC5322, 3.2.3. Atom.
 */
imf_atext :
	ALPHA | DIGIT | '!' | '#' | '$' | '%' | '&' | '\'' | '*' | '+' | '-' | '/'
	| '=' | '?' | '^' | '_' | '`' | '{' | '|' | '}' | '~';
imf_atom :
	imf_CFWS_or_empty imf_atexts
	| imf_CFWS_or_empty imf_atexts imf_CFWS
	;
imf_atexts :
	imf_atext
	| imf_atexts imf_atext;
imf_dot_atom_text :
	imf_atexts
	| imf_dot_atom_text '.' imf_atexts;
imf_dot_atom :
	imf_CFWS_or_empty imf_dot_atom_text
	| imf_CFWS_or_empty imf_dot_atom_text imf_CFWS;
imf_specials :
	'(' | ')' | '<' | '>' | '[' | ']' | ':' | ';' | '@' | '\\' | ',' | '.' | '"';

/**
  RFC5322, 3.2.4. Quoted Strings.
*/
imf_qtext :
	'\041' /* %d33 */ | '\043' /* %d35 */ | '\044' /* %d36 */ | '\045' /* %d37 */
	| '\046' /* %d38 */ | '\047' /* %d39 */ | '\050' /* %d40 */ | '\051' /* %d41 */
	| '\052' /* %d42 */ | '\053' /* %d43 */ | '\054' /* %d44 */ | '\055' /* %d45 */
	| '\056' /* %d46 */ | '\057' /* %d47 */ | '\060' /* %d48 */ | '\061' /* %d49 */
	| '\062' /* %d50 */ | '\063' /* %d51 */ | '\064' /* %d52 */ | '\065' /* %d53 */
	| '\066' /* %d54 */ | '\067' /* %d55 */ | '\070' /* %d56 */ | '\071' /* %d57 */
	| '\072' /* %d58 */ | '\073' /* %d59 */ | '\074' /* %d60 */ | '\075' /* %d61 */
	| '\076' /* %d62 */ | '\077' /* %d63 */ | '\100' /* %d64 */ | '\101' /* %d65 */
	| '\102' /* %d66 */ | '\103' /* %d67 */ | '\104' /* %d68 */ | '\105' /* %d69 */
	| '\106' /* %d70 */ | '\107' /* %d71 */ | '\110' /* %d72 */ | '\111' /* %d73 */
	| '\112' /* %d74 */ | '\113' /* %d75 */ | '\114' /* %d76 */ | '\115' /* %d77 */
	| '\116' /* %d78 */ | '\117' /* %d79 */ | '\120' /* %d80 */ | '\121' /* %d81 */
	| '\122' /* %d82 */ | '\123' /* %d83 */ | '\124' /* %d84 */ | '\125' /* %d85 */
	| '\126' /* %d86 */ | '\127' /* %d87 */ | '\130' /* %d88 */ | '\131' /* %d89 */
	| '\132' /* %d90 */ | '\133' /* %d91 */ | '\135' /* %d93 */ | '\136' /* %d94 */
	| '\137' /* %d95 */ | '\140' /* %d96 */ | '\141' /* %d97 */ | '\142' /* %d98 */
	| '\143' /* %d99 */ | '\144' /* %d100 */ | '\145' /* %d101 */ | '\146' /* %d102 */
	| '\147' /* %d103 */ | '\150' /* %d104 */ | '\151' /* %d105 */ | '\152' /* %d106 */
	| '\153' /* %d107 */ | '\154' /* %d108 */ | '\155' /* %d109 */ | '\156' /* %d110 */
	| '\157' /* %d111 */ | '\160' /* %d112 */ | '\161' /* %d113 */ | '\162' /* %d114 */
	| '\163' /* %d115 */ | '\164' /* %d116 */ | '\165' /* %d117 */ | '\166' /* %d118 */
	| '\167' /* %d119 */ | '\170' /* %d120 */ | '\171' /* %d121 */ | '\172' /* %d122 */
	| '\173' /* %d123 */ | '\174' /* %d124 */ | '\175' /* %d125 */ | '\176' /* %d126 */;
imf_qcontent :
	imf_qtext
	| imf_quoted_pair;
imf_quoted_string :
	imf_CFWS_or_empty '"' imf_FWS_or_empty '"' imf_CFWS_or_empty;
	| imf_CFWS_or_empty '"' imf_quoted_string_entity imf_FWS_or_empty '"' imf_CFWS_or_empty;
imf_quoted_string_entity :
	imf_FWS_or_empty imf_qcontent
	| imf_quoted_string_entity imf_FWS_or_empty imf_qcontent;

/**
  RFC5322, 3.2.5. Miscellaneous Tokens.
 */
imf_word :
	imf_atom
	| imf_quoted_string
	;
imf_phrase :
	imf_word
	| imf_phrase imf_word
	;
imf_unstructured :
	WSPs
	| imf_unstructured_entity
	| imf_unstructured_entity WSPs;
imf_unstructured_entity :
	imf_FWS_or_empty VCHAR
	| imf_unstructured_entity imf_FWS_or_empty VCHAR;

/**
  RFC5322, 3.4. Address Specification.
 */
imf_address :
	imf_mailbox
	| imf_group;
imf_mailbox :
	imf_name_addr
	| imf_addr_spec
	;
imf_name_addr :
	imf_display_name
	| imf_display_name imf_angle_addr
	;
imf_angle_addr :
	imf_CFWS_or_empty '<' imf_addr_spec '>' imf_CFWS_or_empty;
imf_group :
	imf_display_name ':' ';' imf_CFWS_or_empty
	| imf_display_name ':' imf_group_list ';' imf_CFWS_or_empty;
imf_display_name :
	imf_phrase;
imf_mailbox_list :
	imf_mailbox
	| imf_mailbox_list ',' imf_mailbox;
imf_address_list :
	imf_address
	| imf_address_list ',' imf_address;
imf_group_list :
	imf_mailbox_list
	| imf_CFWS;

/**
  RFC5322, 3.4.1. Addr-Spec Specification.
 */
imf_addr_spec :
	imf_local_part '@' imf_domain;
imf_local_part :
	imf_dot_atom
	| imf_quoted_string;
imf_domain :
	imf_dot_atom
	| imf_domain_literal;
imf_domain_literal :
	imf_CFWS_or_empty '[' imf_FWS_or_empty ']' imf_CFWS_or_empty
	| imf_CFWS_or_empty '[' imf_domain_literal_entity imf_FWS_or_empty ']' imf_CFWS_or_empty;
imf_domain_literal_entity :
	imf_FWS_or_empty imf_dtext
	| imf_domain_literal_entity imf_FWS_or_empty imf_dtext;
imf_dtext :
	| '\041' /* %d33 */ | '\042' /* %d34 */ | '\043' /* %d35 */ | '\044' /* %d36 */
	| '\045' /* %d37 */ | '\046' /* %d38 */ | '\047' /* %d39 */ | '\050' /* %d40 */
	| '\051' /* %d41 */ | '\052' /* %d42 */ | '\053' /* %d43 */ | '\054' /* %d44 */
	| '\055' /* %d45 */ | '\056' /* %d46 */ | '\057' /* %d47 */ | '\060' /* %d48 */
	| '\061' /* %d49 */ | '\062' /* %d50 */ | '\063' /* %d51 */ | '\064' /* %d52 */
	| '\065' /* %d53 */ | '\066' /* %d54 */ | '\067' /* %d55 */ | '\070' /* %d56 */
	| '\071' /* %d57 */ | '\072' /* %d58 */ | '\073' /* %d59 */ | '\074' /* %d60 */
	| '\075' /* %d61 */ | '\076' /* %d62 */ | '\077' /* %d63 */ | '\100' /* %d64 */
	| '\101' /* %d65 */ | '\102' /* %d66 */ | '\103' /* %d67 */ | '\104' /* %d68 */
	| '\105' /* %d69 */ | '\106' /* %d70 */ | '\107' /* %d71 */ | '\110' /* %d72 */
	| '\111' /* %d73 */ | '\112' /* %d74 */ | '\113' /* %d75 */ | '\114' /* %d76 */
	| '\115' /* %d77 */ | '\116' /* %d78 */ | '\117' /* %d79 */ | '\120' /* %d80 */
	| '\121' /* %d81 */ | '\122' /* %d82 */ | '\123' /* %d83 */ | '\124' /* %d84 */
	| '\125' /* %d85 */ | '\126' /* %d86 */ | '\127' /* %d87 */ | '\130' /* %d88 */
	| '\131' /* %d89 */ | '\132' /* %d90 */ | '\136' /* %d94 */ | '\137' /* %d95 */
	| '\140' /* %d96 */ | '\141' /* %d97 */ | '\142' /* %d98 */ | '\143' /* %d99 */
	| '\144' /* %d100 */ | '\145' /* %d101 */ | '\146' /* %d102 */ | '\147' /* %d103 */
	| '\150' /* %d104 */ | '\151' /* %d105 */ | '\152' /* %d106 */ | '\153' /* %d107 */
	| '\154' /* %d108 */ | '\155' /* %d109 */ | '\156' /* %d110 */ | '\157' /* %d111 */
	| '\160' /* %d112 */ | '\161' /* %d113 */ | '\162' /* %d114 */ | '\163' /* %d115 */
	| '\164' /* %d116 */ | '\165' /* %d117 */ | '\166' /* %d118 */ | '\167' /* %d119 */
	| '\170' /* %d120 */ | '\171' /* %d121 */ | '\172' /* %d122 */ | '\173' /* %d123 */
	| '\174' /* %d124 */ | '\175' /* %d125 */ | '\176' /* %d126 */;

