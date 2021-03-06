#pragma once
#include <string>
#include <iostream>

using namespace std;
static const char* tokenTypeList[] =
{
	"NUMBER",					//����
	"DOUBLE_NUMBER",			//������
	"CHARACTER",				//�ַ�
	"IDENTIFIER",				//��ʶ��
	"COMMENT",					//ע�� "//"

	"UNDERSCORE",				//"_"
	"ABSTRACT",					//"abstract"
	"ALIGNOF",					//"alignof"
	"AS",						//"as"
	"BECOME",					//"become"
	"BOX",						//"box"
	"BREAK",					//"break"
	"CONST",					//"const"
	"CONTINUE",					//"continue"
	"CRATE",					//"crate"
	"DO",						//"do"
	"ELSE",						//"else"
	"ENUM",						//"enum"
	"EXTREN",					//"extern"
	"FALSE",					//"false"
	"FINAL",					//"final"
	"FN",						//"fn"
	"FOR",						//"for"
	"IF",						//"if"
	"IMPL",						//"impl"
	"IN",						//"in"
	"LET",						//"let"
	"LOOP",						//"loop"
	"MACRO",					//"macro"
	"MATCH",					//"match"
	"MOD",						//"mod"
	"MOVE",						//"move"
	"MUT",						//"mut"
	"OFFSETOF",					//"offsetof"
	"OVERRIDE",					//"override"
	"PRIV",						//"priv"
	"PROC",						//"proc"
	"PUB",						//"pub"
	"PURE",						//"pure"
	"REF",						//"ref"
	"RETURN",					//"return"
	"_SELF",					//"Self"
	"SELF",						//"self"
	"SIZEOF",					//"sizeof"
	"STATIC",					//"static"
	"STRUCT",					//"struct"
	"SUPER",					//"super"
	"TRAIT",					//"trait"
	"TRUE",						//"true"
	"TYPE",						//"type"
	"TYPEOF",					//"typeof"
	"UNSAFE",					//"unsafe"
	"UNSIZED",					//"unsized"
	"USE",						//"use"
	"VIRTUAL",					//"virtual"
	"WHERE",					//"where"
	"WHILE",					//"while"
	"YIELD",					//"yield"

	"DOUBLE_POINT",				// ..

	"SET",						// =
	"EQUALITY",					// ==

	"PLUS",						// +
	"MINUS",					// -
	"STAR",						// *
	"SLASH",					// /
	"MOD",						// %
	"MODEQUAL",					// %=
	"PLUSEQUAL",				// +=
	"MINUSEQUAL",				// -=
	"STAREQUAL",				// *=
	"SLASHEQUAL",				// /=

	"LPAR",						// (
	"RPAR",						// )
	"LBRACE",					// {
	"RBRACE",					// }

	"QUOTES",					// "
	"SINGLEQUOTES",				// '
	"COMMA",					// ,
	"SEMICOLON",				// ;

	"MORE",						// >
	"LESS",						// <
	"OR",						// |
	"AND",						// &
	"MOREEQUAL",				// >=
	"LESSEQUAL",				// <=
	"OREQUAL",					// |=
	"ANDEQUAL",					// &=
	"RSHIFT",					// >>
	"RSHIFTEQUAL",				// >>=
	"LSHIFT",					// <<
	"LSHIFTEQUAL",				// <<
	"LOGICOR",					// ||
	"LOGICAND",					// &&
	"RETURNTYPE",				// ->
	"NOT",						// !
	"NOTEQUAL",					// !=
	"XOR",						// ^
	"XOREQUAL",					// ^=
	"COLON",					// :
	"I16",
	"U16",
	"F32",
	"BOOL",
	"CHAR",
	"PRINTLN",
};
enum class token_type {
	NUMBER,					//����
	DOUBLE_NUMBER,			//������
	CHARACTER,          //�ַ�
	IDENTIFIER,				//��ʶ��
	COMMENT,				//ע�� "//"

	UNDERSCORE,				//"_"
	ABSTRACT,				//"abstract"
	ALIGNOF,				//"alignof"
	AS,						//"as"
	BECOME,					//"become"
	BOX,					//"box"
	BREAK,					//"break"
	CONST,					//"const"
	CONTINUE,				//"continue"
	CRATE,					//"crate"
	DO,						//"do"
	ELSE,					//"else"
	ENUM,					//"enum"
	EXTREN,					//"extern"
	FALSE,					//"false"
	FINAL,					//"final"
	FN,						//"fn"
	FOR,					//"for"
	IF,						//"if"
	IMPL,					//"impl"
	IN,						//"in"
	LET,					//"let"
	LOOP,					//"loop"
	MACRO,					//"macro"
	MATCH,					//"match"
	MOD,					//"mod"
	MOVE,					//"move"
	MUT,					//"mut"
	OFFSETOF,				//"offsetof"
	OVERRIDE,				//"override"
	PRIV,					//"priv"
	PROC,					//"proc"
	PUB,					//"pub"
	PURE,					//"pure"
	REF,					//"ref"
	RETURN,					//"return"
	_SELF,					//"Self"
	SELF,					//"self"
	SIZEOF,					//"sizeof"
	STATIC,					//"static"
	STRUCT,					//"struct"
	SUPER,					//"super"
	TRAIT,					//"trait"
	TRUE,					//"true"
	TYPE,					//"type"
	TYPEOF,					//"typeof"
	UNSAFE,					//"unsafe"
	UNSIZED,				//"unsized"
	USE,					//"use"
	VIRTUAL,				//"virtual"
	WHERE,					//"where"
	WHILE,					//"while"
	YIELD,					//"yield"

	DOUBLE_POINT,			// ..

	SET, // =
	EQUALITY, // ==

	PLUS,			// +
	MINUS,			// -
	STAR,			// *
	SLASH,			// /
	PERCENT,			// %
	PERCENTEQUAL,		// %=
	PLUSEQUAL,		// +=
	MINUSEQUAL,		// -=
	STAREQUAL,		// *=
	SLASHEQUAL,		// /=

	LPAR,    // (
	RPAR,    // )
	LBRACE,  // {
	RBRACE,  // }

	QUOTES,  // "
	SINGLEQUOTES,	// '
	COMMA,   // ,
	SEMICOLON, // ;

	MORE,			// >
	LESS,			// <
	OR,				// |
	AND,			// &
	MOREEQUAL,		// >=
	LESSEQUAL,		// <=
	OREQUAL,		// |=
	ANDEQUAL,		// &=
	RSHIFT,			// >>
	RSHIFTEQUAL,	// >>=
	LSHIFT,			// <<
	LSHIFTEQUAL,	// <<=
	LOGICOR,		// ||
	LOGICAND,		// &&
	RETURNTYPE,		// ->
	NOT,			// !
	NOTEQUAL,		// !=
	XOR,			// ^
	XOREQUAL,		// ^=
	COLON,			// :
	I16,
	U16,
	F32,
	BOOL,
	CHAR,
	PRINTLN,
};

class Token
{
public:
	string lexeme;
	token_type type;
	unsigned int col;
	unsigned int row;
public:
	Token(const string& lexeme);
	Token(const string& lexeme,unsigned row,unsigned col);

	token_type get_type();
	string get_lexeme();
	void add_lexeme(const string& lexeme);

	bool is_integer(const string& lexeme);
	bool is_double(const string& lexeme);
	bool is_correct_identifier(const string& lexeme);
};