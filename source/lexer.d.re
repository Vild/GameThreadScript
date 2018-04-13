module lexer;

import std.range;
import std.variant : Algebraic;
import std.conv : to;

enum Keyword {
	package_,
	class_
}

enum Attribute {
	property,
	override_
}

enum Type {
	void_,
	char_,
	byte_,
	short_,
	int_,
	long_,
	ubyte_,
	ushort_,
	uint_,
	ulong_,
	float_,
	double_,
}

struct Symbol {
	string symbol;
}

struct String {
	string value;
}

struct Integer {
	long value;
}

struct FloatingNumber {
	double val;
}

struct EndOfFile {
}

struct ErrorToken {
	char errorChar;
}

alias Token = Algebraic!(ErrorToken, EndOfFile, dchar, Keyword, Attribute, Type, Symbol, Symbol, String, Integer, FloatingNumber);
static Token getToken(ref string YYCURSOR) {
	string r = YYCURSOR;
	string marker;
	string ctxMarker;

	scope (failure) {
		return r.length ? Token(ErrorToken(r[0])) : Token(EndOfFile());
	}

	alias YYCTYPE = dchar;
	alias YYPEEK() = { assert(!YYCURSOR.empty); return YYCURSOR.front; };
	alias YYSKIP() = { YYCURSOR.popFront; };
	alias YYBACKUP() = { marker = YYCURSOR.save(); };
	alias YYBACKUPCTX() = { ctxMarker = YYCURSOR.save(); };
	alias YYRESTORE() = { YYCURSOR = marker; };
	alias YYRESTORECTX() = { YYCURSOR = ctxMarker; };

	/*void YYRESTORETAG(ref string t) { YYCURSOR = t; }
	alias YYLESSTHAN(n) = { return YYCURSOR.length < n; };
	void YYSTAGP(ref string t) { t = YYCURSOR; }
	void YYSTAGN(ref string t) { t = null; }*/

	/*!re2c
		re2c:yyfill:enable = 0;

		end       = "\x00";
		attribute = '@';

		"__EOF__" { return Token(EndOfFile()); }

		[ \r\n\t]+   { return getToken(YYCURSOR); }
		//";"        { return Token(Keyword.endOfLine); }

		// Keywords
		"package" { return Token(Keyword.package_); }
		"class"   { return Token(Keyword.class_); }

		// Attributes
		attribute "property" { return Token(Attribute.property); }
		attribute "override" { return Token(Attribute.override_); }

		// Types
		"void"   { return Token(Type.void_); }
		"char"   { return Token(Type.char_); }
		"byte"   { return Token(Type.byte_); }
		"short"  { return Token(Type.short_); }
		"int"    { return Token(Type.int_); }
		"long"   { return Token(Type.long_); }
		"ubyte"  { return Token(Type.ubyte_); }
		"ushort" { return Token(Type.ushort_); }
		"uint"   { return Token(Type.uint_); }
		"ulong"  { return Token(Type.ulong_); }
		"float"  { return Token(Type.float_); }
		"double" { return Token(Type.double_); }

		// Symbol
		[a-zA-Z] [a-zA-Z_0-9]+ { return Token(Symbol(r[0 .. r.length - YYCURSOR.length])); }

		// Value constants
		"\"" [^"]* "\""    { return Token(String(r[1 .. r.length - YYCURSOR.length - 1])); }
		[0-9]+             { return Token(Integer(r[0 .. r.length - YYCURSOR.length].to!long)); }
		[0-9]* "." [0-9]+
		| [0-9]+ "."       { return Token(FloatingNumber(r[0 .. r.length - YYCURSOR.length].to!double)); }

		* { return Token(cast(dchar)r[0]); }
	*/

}
