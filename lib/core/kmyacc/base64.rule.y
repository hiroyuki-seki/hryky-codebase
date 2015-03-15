/**
  @file base64.rule.y
  @brief the 'rule' part of KMYACC grammar file for Base64(Base16, Base32) Encoding.
  @version $Id: base64.rule.y 150 2013-02-10 10:08:03Z hryky.private@gmail.com $

  @sa http://datatracker.ietf.org/doc/rfc4648/

 */
/**
  RFC4648, 4. Base 64 Encoding.
 */
base64_alpha :
	base64_alpha_npad
	| base64_alpha_pad;
base64_alpha_npad :
	ALPHA
	| DIGIT
	| '+'
	| '-';
base64_alpha_pad :
	'=';

