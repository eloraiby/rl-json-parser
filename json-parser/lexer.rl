/*
** json-parser Copyright 2015(c) Wael El Oraiby. All Rights Reserved
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** Under Section 7 of GPL version 3, you are granted additional
** permissions described in the GCC Runtime Library Exception, version
** 3.1, as published by the Free Software Foundation.
**
** You should have received a copy of the GNU General Public License and
** a copy of the GCC Runtime Library Exception along with this program;
** see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
** <http://www.gnu.org/licenses/>.
**
*/
/*
 grammar parser: using Lemon, not YACC nor BISON
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "private/private.h"

extern void*	parser_alloc(void *(*mallocProc)(size_t));
extern void	parser_free(void *p, void (*freeProc)(void*));
extern void	parser_advance(void *yyp, int yymajor, token_t yyminor, json_parser_t* s);


#define ADVANCE(A, T)	if( parser_.error_code == 0) { \
				parser_.token_start	= ts; \
				parser_.token_end	= te; \
				parser_.token_line	= line; \
				copy_token(ts, te, tmp); \
				token_t tmpc = token_to_##A(tmp); \
				parser_advance(yyparser, T, tmpc, &parser_); \
			} else cs	= scanner_error

#define ADVANCE_STRING(T) if( parser_.error_code == 0) { \
				parser_.token_start	= string_s; \
				parser_.token_end	= string_e; \
				parser_.token_line	= line; \
				token_t tmpc = token_to_string(string_s, string_e); \
				parser_advance(yyparser, T, tmpc, &parser_); \
			} else cs	= scanner_error

#define ADVANCE_TOKEN(A)	if( parser_.error_code == 0) { token_t t; t.tok_type = A; parser_advance(yyparser, A, t, &parser_); } else p = pe - 1

/* EOF char used to flush out that last token. This should be a whitespace
 * token. */

#define LAST_CHAR 0


%%{
	machine scanner;
	write data nofinal;

	# Floating literals.
	fract_const	= ([0] | digit+) '.' digit+ | digit+ '.';
	exponent	= [eE] [+\-]? digit+;

	action inc_line { ++line; }

	c_comment	:= (any | '\n'@inc_line)* :>> '*/' @{ fgoto main; };

	ju		= [0-9a-fA-F];

	j_string	:= |*
		('\\' ('"' | '\\' | '/' | 'b' | 'f' | 'n' | 'r' | 't'))	{ };
		('\\u' ju ju ju ju)					{ };
		(cntrl)							{
										ret.status = JSON_INVALID_STRING;
										cs = scanner_error;
									};
		'"'							@{ string_e = ts; ADVANCE_STRING(JSON_TOK_STRING); string_s = NULL; string_e = NULL; fgoto main; };
		'\n' | '\\'						{
										ret.status = JSON_INVALID_STRING;
										cs = scanner_error;
									};
		any							{ };
	*|;

	main := |*
		'true'						{ ADVANCE( boolean, JSON_TOK_BOOLEAN );};
		'false'						{ ADVANCE( boolean, JSON_TOK_BOOLEAN );};
		'null'						{ ADVANCE( none,    JSON_TOK_NONE    );};

		# string.
		'"'						{ string_s = te; fgoto j_string; };


		# Integer decimal. Leading part buffered by float.
		( [+\-]? ( '0' | [1-9] [0-9]* ) )		{ ADVANCE( number, JSON_TOK_NUMBER ); };

		( [+\-]? ( '0' | [1-9] [0-9]* ) [a-zA-Z_]+ )	{
									ret.status	= JSON_INVALID_NUMBER;
									cs	= scanner_error;
								};

		# Floating literals.
		( [+\-]? fract_const exponent? | [+\-]? digit+ exponent ) 	{ ADVANCE( number, JSON_TOK_NUMBER );};

		# Only buffer the second item, first buffered by symbol. */
		'{'						{ ADVANCE_TOKEN( JSON_TOK_LBRACK );};
		'}'						{ ADVANCE_TOKEN( JSON_TOK_RBRACK );};
		'['						{ ADVANCE_TOKEN( JSON_TOK_LSQB   );};
		']'						{ ADVANCE_TOKEN( JSON_TOK_RSQB   );};
		':'						{ ADVANCE_TOKEN( JSON_TOK_COL    );};
		','						{ ADVANCE_TOKEN( JSON_TOK_COMMA  );};

		'\n'						{ ++line; };

		# Single char symbols.
		( punct - [_"'] )				{ ret.status = JSON_INVALID_CHARACTER; cs = scanner_error; };

		# Comments and whitespace.
		'/*'						{ fgoto c_comment; };
		'//' [^\n]* '\n'@inc_line;
		( any - 33..126 )+;
	*|;
}%%

static int
copy_token(const char* ts, const char *te, char* dst) {
	int	index	= 0;
	while( ts < te ) {
		dst[index++]	= *ts;
		++ts;
	}
	dst[index] = '\0';
	return index;
}

static token_t
token_to_boolean(const char* b) {
	token_t	t;
	t.tok_type	= JSON_TOK_BOOLEAN;
	if( !strcmp(b, "true") ) {
		t.boolean	= true;
	} else {
		t.boolean	= false;
	}
	return t;
}

static token_t
token_to_number(const char* r) {
	token_t	t;
	double	v	= 0.0;
	t.tok_type	= JSON_TOK_NUMBER;
	sscanf(r, "%lf", &v);
	/* TODO: check limit */
	t.number	= v;
	return t;
}

static token_t
token_to_none(const char* str) {
	token_t	t;
	t.tok_type	= JSON_TOK_NONE;
	return t;
}

static token_t
token_to_string(const char* ts, const char* te) {
	token_t	t;
	t.tok_type	= JSON_TOK_STRING;
	t.string.start	= ts;
	t.string.len	= te - ts;
	return t;
}


json_return_t
json_parse(const char* str)
{
	json_parser_t		parser_;
	json_return_t		ret;
	ret.status	= JSON_INVALID_INPUT;
	ret.value	= NULL;

	void*		yyparser;
	size_t		line	= 1;
	const char*	ts	= str;
	const char*	te	= str;
	const char*	i	= NULL;
	const char*	string_s	= NULL;
	const char*	string_e	= NULL;

	const char*	p	= str;
	const char*	pe	= p + strlen(str) + 1;
	const char*	eof	= NULL;

	int		act	= 0;
	int		cs	= 0;
	char		tmp[4096];

	token_t		dummy;
	dummy.tok_type	= 0;

	parser_.root		= NULL;
	parser_.error_code	= 0;
	parser_.token_start	= ts;
	parser_.token_end	= te;
	parser_.token_line	= line;

	yyparser	= parser_alloc(malloc);

	memset(tmp, 0, sizeof(tmp));

	%% write init;

	%% write exec;

	/* Check if we failed. */
	if ( cs == scanner_error ) {
		/* Machine failed before finding a token. */
		parser_.error_code = 1;
	}

	parser_advance(yyparser, 0, dummy, &parser_);

	if( parser_.error_code == 1 ) {
		while( parser_.error_code == 1 )
			parser_advance(yyparser, 0, dummy, &parser_);
	}

	if( parser_.error_code != 0 ) {
		ret.status	= JSON_ERROR_SYNTAX_ERROR;

		parser_free(yyparser, free);

		if( parser_.root ) {
			json_free(parser_.root);
		}

		return ret;
	}

	parser_free(yyparser, free);
	ret.status	= JSON_SUCCESS;
	ret.value	= parser_.root;
	return ret;
}

