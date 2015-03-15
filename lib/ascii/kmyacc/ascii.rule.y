/**
  @file ascii.rule.y
  @brief the 'rule' part of KMYACC grammar file for parsing ASCII.
  @version $Id: http.rule.y 126 2013-01-01 09:41:58Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc2616/

 */
UPALPHA :
	'A'|'B'|'C'|'D'|'E'|'F'|'G'|'H'|'I'|'J'|'K'|'L'|'M'|'N'|'O'|'P'|'Q'
	|'R'|'S'|'T'|'U'|'V'|'W'|'X'|'Y'|'Z'
	;
LOALPHA :
	'a'|'b'|'c'|'d'|'e'|'f'|'g'|'h'|'i'|'j'|'k'|'l'|'m'|'n'|'o'|'p'|'q'
	|'r'|'s'|'t'|'u'|'v'|'w'|'x'|'y'|'z';
ALPHA :
	LOALPHA | UPALPHA;
DIGIT :
	'0'|'1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9';
HEX :
	DIGIT | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'a' | 'b' | 'c'
	| 'd' | 'e' | 'f';
CTL :
	HT | CR | LF | ctl_no_ht_cr_lf;
ctl_no_ht_cr_lf :
	NUL | SOH | STX | ETX | EOT | ENQ | ACK | BEL | BS | VT | FF
	| SO | SI | DLE | DC1 | DC2 | DC3 | DC4 | NAK | SYN | ETB | CAN | EM
	| SUB | ESC | FS | GS | RS | US | DEL;
SOH : '\001';
STX : '\002';
ETX : '\003';
EOT : '\004';
ENQ : '\005';
ACK : '\006';
BEL : '\007';
BS : '\010';
HT : '\011';
LF : '\012';
VT : '\013';
FF : '\014';
CR : '\015';
SO : '\016';
SI : '\017';
DLE : '\020';
DC1 : '\021';
DC2 : '\022';
DC3 : '\023';
DC4 : '\024';
NAK : '\025';
SYN : '\026';
ETB : '\027';
CAN : '\030';
EM : '\031';
SUB : '\032';
ESC : '\033';
FS : '\034';
GS : '\035';
RS : '\036';
US : '\037';
DEL : '\177';
SP : '\040';

printable_symbol_no_sp :
	'('
	| ')'
	| printable_symbol_no_sp_parenthesis
	;
printable_symbol_no_sp_parenthesis :
	'"'
	| printable_symbol_no_sp_parenthesis_dquote
	;
printable_symbol_no_sp_parenthesis_dquote :
	'!' | '#' | '$' | '%' | '&' | '\''
	| '*' | '+' | ',' | '-' | '.' | '/' | ':' | ';' | '<' | '='
	| '>' | '?' | '@' | '[' | '\\' | ']' | '^' | '_' | '`' | '{' | '|' | '}'
	| '~'
	;
printable_symbol :
	SP
	| printable_symbol_no_sp
	;

no_ascii :
	'\200' | '\201' | '\202' | '\203' | '\204' | '\205' | '\206'
	| '\207' | '\210' | '\211' | '\212' | '\213' | '\214' | '\215' | '\216'
	| '\217' | '\220' | '\221' | '\222' | '\223' | '\224' | '\225' | '\226'
	| '\227' | '\230' | '\231' | '\232' | '\233' | '\234' | '\235' | '\236'
	| '\237' | '\240' | '\241' | '\242' | '\243' | '\244' | '\245' | '\246'
	| '\247' | '\250' | '\251' | '\252' | '\253' | '\254' | '\255' | '\256'
	| '\257' | '\260' | '\261' | '\262' | '\263' | '\264' | '\265' | '\266'
	| '\267' | '\270' | '\271' | '\272' | '\273' | '\274' | '\275' | '\276'
	| '\277' | '\300' | '\301' | '\302' | '\303' | '\304' | '\305' | '\306'
	| '\307' | '\310' | '\311' | '\312' | '\313' | '\314' | '\315' | '\316'
	| '\317' | '\320' | '\321' | '\322' | '\323' | '\324' | '\325' | '\326'
	| '\327' | '\330' | '\331' | '\332' | '\333' | '\334' | '\335' | '\336'
	| '\337' | '\340' | '\341' | '\342' | '\343' | '\344' | '\345' | '\346'
	| '\347' | '\350' | '\351' | '\352' | '\353' | '\354' | '\355' | '\356'
	| '\357' | '\360' | '\361' | '\362' | '\363' | '\364' | '\365' | '\366'
	| '\367' | '\370' | '\371' | '\372' | '\373' | '\374' | '\375' | '\376'
	| '\377'
	;

digits :
	DIGIT
	{
		$$ = token_type(ascii::to_digit($1.cast<octet_type>()));
	}
	| digits DIGIT
	{
		$$ = token_type(
			$1.cast<uint64_t>() * 10
			+ ascii::to_digit($2.cast<octet_type>()));
	}
	;
digits4 :
	DIGIT DIGIT DIGIT DIGIT
	{
		$$ = token_type(
			ascii::to_digit($1.cast<octet_type>()) * 1000
			+ ascii::to_digit($2.cast<octet_type>()) * 100
			+ ascii::to_digit($3.cast<octet_type>()) * 10
			+ ascii::to_digit($4.cast<octet_type>()));
	}
	;
digits2 :
	DIGIT DIGIT
	{
		$$ = token_type(
			ascii::to_digit($1.cast<octet_type>()) * 10
			+ ascii::to_digit($2.cast<octet_type>()));
	}
	;
digits1_3 :
	DIGIT
	{
		$$ = token_type(ascii::to_digit($1.cast<octet_type>()));
	}
	| DIGIT DIGIT
	{
		$$ = token_type(
			ascii::to_digit($1.cast<octet_type>()) * 10
			+ ascii::to_digit($2.cast<octet_type>()));
	}
	| DIGIT DIGIT DIGIT
	{
		$$ = token_type(
			ascii::to_digit($1.cast<octet_type>()) * 100
			+ ascii::to_digit($2.cast<octet_type>()) * 10
			+ ascii::to_digit($3.cast<octet_type>()));
	}
	;
digits3 :
	DIGIT DIGIT DIGIT
	{
		$$ = token_type(
			ascii::to_digit($1.cast<octet_type>()) * 100
			+ ascii::to_digit($2.cast<octet_type>()) * 10
			+ ascii::to_digit($3.cast<octet_type>()));
	}
	;
