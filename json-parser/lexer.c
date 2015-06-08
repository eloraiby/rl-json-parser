
#line 1 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
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

#include "private/private.h"
#include "parser.h"

extern void*	parser_alloc(void *(*mallocProc)(size_t));
extern void		parser_free(void *p, void (*freeProc)(void*));
extern void		parser_advance(void *yyp, int yymajor, json_value_t* yyminor, json_parser_t* s);

#define ADVANCE(A)	parser_.token_start	= ts; \
			parser_.token_end	= te; \
			parser_.token_line	= line; \
			copy_token(ts, te, tmp); \
			json_value_t* tmpc = token_to_##A(tmp); \
			parser_advance(yyparser, tmpc->tag, tmpc, &parser_)

#define ADVANCE_OP(A, T)	parser_.token_start	= ts; \
			parser_.token_end	= te; \
			parser_.token_line	= line; \
			copy_token(ts, te, tmp); \
			json_value_t* tmpc = token_to_##A(tmp); \
			parser_advance(yyparser, T, tmpc, &parser_)

#define ADVANCE_TOKEN(A)	parser_advance(yyparser, A, NULL, &parser_)

#define PUSH_TE()	const char* tmp_te = te
#define POP_TE()	te	= tmp_te
#define PUSH_TS()	const char* tmp_ts = ts
#define POP_TS()	ts	= tmp_ts

/* EOF char used to flush out that last token. This should be a whitespace
 * token. */

#define LAST_CHAR 0



#line 65 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.c"
static const char _scanner_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 10, 1, 11, 1, 
	12, 1, 13, 1, 14, 1, 15, 1, 
	16, 1, 17, 1, 18, 1, 19, 1, 
	20, 1, 21, 1, 23, 1, 24, 1, 
	25, 1, 26, 1, 27, 1, 28, 1, 
	29, 2, 0, 22, 2, 4, 5, 2, 
	4, 6, 2, 4, 7, 2, 4, 8, 
	2, 4, 9
};

static const char _scanner_key_offsets[] = {
	0, 0, 3, 3, 7, 9, 14, 15, 
	16, 17, 18, 19, 20, 21, 22, 23, 
	24, 25, 27, 30, 59, 61, 64, 74, 
	78, 80, 85, 94, 104, 106
};

static const char _scanner_trans_keys[] = {
	10, 34, 92, 43, 45, 48, 57, 48, 
	57, 46, 69, 101, 48, 57, 10, 97, 
	108, 115, 101, 111, 110, 101, 114, 117, 
	101, 10, 42, 10, 42, 47, 10, 34, 
	39, 43, 44, 45, 47, 48, 58, 91, 
	92, 93, 94, 96, 102, 110, 116, 123, 
	125, 33, 46, 49, 57, 59, 64, 65, 
	122, 124, 126, 33, 126, 48, 49, 57, 
	46, 69, 95, 101, 48, 57, 65, 90, 
	97, 122, 69, 101, 48, 57, 48, 57, 
	95, 65, 90, 97, 122, 43, 45, 95, 
	48, 57, 65, 90, 97, 122, 46, 69, 
	95, 101, 48, 57, 65, 90, 97, 122, 
	42, 47, 0
};

static const char _scanner_single_lengths[] = {
	0, 3, 0, 2, 0, 3, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 2, 3, 19, 0, 1, 4, 2, 
	0, 1, 3, 4, 2, 0
};

static const char _scanner_range_lengths[] = {
	0, 0, 0, 1, 1, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 5, 1, 1, 3, 1, 
	1, 2, 3, 3, 0, 0
};

static const unsigned char _scanner_index_offsets[] = {
	0, 0, 4, 5, 9, 11, 16, 18, 
	20, 22, 24, 26, 28, 30, 32, 34, 
	36, 38, 41, 45, 70, 72, 75, 83, 
	87, 89, 93, 100, 108, 111
};

static const char _scanner_indicies[] = {
	1, 2, 3, 0, 0, 5, 5, 6, 
	4, 6, 4, 8, 10, 10, 9, 7, 
	13, 12, 14, 1, 15, 1, 16, 1, 
	17, 1, 18, 1, 19, 1, 20, 1, 
	21, 1, 22, 1, 23, 1, 25, 26, 
	24, 25, 26, 27, 24, 29, 0, 1, 
	31, 32, 31, 33, 34, 36, 37, 30, 
	38, 30, 30, 39, 40, 41, 42, 43, 
	30, 35, 30, 1, 30, 28, 4, 28, 
	34, 35, 44, 8, 47, 46, 47, 9, 
	46, 46, 45, 10, 10, 8, 48, 6, 
	48, 46, 46, 46, 49, 5, 5, 46, 
	6, 46, 46, 49, 8, 47, 46, 47, 
	35, 46, 46, 45, 50, 12, 44, 1, 
	0
};

static const char _scanner_trans_targs[] = {
	1, 0, 19, 2, 19, 4, 24, 19, 
	23, 5, 3, 19, 6, 19, 8, 9, 
	10, 19, 12, 13, 19, 15, 16, 19, 
	17, 17, 18, 29, 20, 20, 19, 21, 
	19, 28, 22, 27, 19, 19, 19, 7, 
	11, 14, 19, 19, 19, 19, 25, 26, 
	19, 19, 19
};

static const char _scanner_trans_actions[] = {
	0, 0, 17, 0, 47, 0, 0, 43, 
	58, 0, 0, 45, 0, 49, 0, 0, 
	0, 13, 0, 0, 15, 0, 0, 11, 
	0, 1, 0, 3, 64, 61, 31, 0, 
	29, 9, 52, 0, 27, 23, 25, 0, 
	0, 0, 19, 21, 41, 35, 0, 55, 
	39, 37, 33
};

static const char _scanner_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 5, 0, 5, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const char _scanner_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 7, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const unsigned char _scanner_eof_trans[] = {
	0, 0, 0, 5, 5, 8, 12, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 5, 45, 46, 49, 
	49, 50, 50, 46, 45, 0
};

static const int scanner_start = 19;
static const int scanner_error = 0;

static const int scanner_en_c_comment = 17;
static const int scanner_en_main = 19;


#line 123 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"


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

static json_value_t*
token_to_boolean(const char* b) {
	if( !strcmp(b, "true") ) {
		return json_boolean(true);
	} else {
		return json_boolean(false);
	}
}

static json_value_t*
token_to_number(const char* r) {
	double	v	= 0.0;
	sscanf(r, "%lf", &v);
	/* TODO: check limit */
	return json_number(v);
}

static json_value_t*
token_to_string(const char* str) {
	return json_string(str);
}

static json_value_t*
token_to_none(const char* str) {
	return json_none();
}


json_value_t*
parse(const char* str)
{
	json_parser_t		parser_;

	void*		yyparser;
	size_t		line	= 1;
	const char*	ts	= str;
	const char*	te	= str;
	const char*	i	= NULL;

	const char*	p	= str;
	const char*	pe	= p + strlen(str) + 1;
	const char*	eof	= NULL;

	int		act	= 0;
	int		cs	= 0;
	char		tmp[4096];

	parser_.root	= NULL;

	yyparser	= parser_alloc(malloc);

	memset(tmp, 0, sizeof(tmp));

	
#line 257 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.c"
	{
	cs = scanner_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 190 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"

	
#line 268 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_acts = _scanner_actions + _scanner_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 3:
#line 1 "NONE"
	{ts = p;}
	break;
#line 289 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.c"
		}
	}

	_keys = _scanner_trans_keys + _scanner_key_offsets[cs];
	_trans = _scanner_index_offsets[cs];

	_klen = _scanner_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _scanner_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _scanner_indicies[_trans];
_eof_trans:
	cs = _scanner_trans_targs[_trans];

	if ( _scanner_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _scanner_actions + _scanner_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 69 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{ ++line; }
	break;
	case 1:
#line 71 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{ {cs = 19; goto _again;} }
	break;
	case 4:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 5:
#line 90 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{act = 5;}
	break;
	case 6:
#line 92 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{act = 6;}
	break;
	case 7:
#line 103 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{act = 7;}
	break;
	case 8:
#line 113 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{act = 14;}
	break;
	case 9:
#line 121 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{act = 18;}
	break;
	case 10:
#line 74 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE( boolean );}}
	break;
	case 11:
#line 75 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE( boolean );}}
	break;
	case 12:
#line 76 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE( none ); }}
	break;
	case 13:
#line 79 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{
									PUSH_TE();
									PUSH_TS();
									++ts; --te;
									ADVANCE( string );
									POP_TS();
									POP_TE();
								}}
	break;
	case 14:
#line 106 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_LBRACK );}}
	break;
	case 15:
#line 107 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_RBRACK );}}
	break;
	case 16:
#line 108 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_LSQB );}}
	break;
	case 17:
#line 109 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_RSQB );}}
	break;
	case 18:
#line 110 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_COL );}}
	break;
	case 19:
#line 111 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_COMMA );}}
	break;
	case 20:
#line 116 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ printf("unexpected character %c\n", *ts); }}
	break;
	case 21:
#line 119 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;{ {cs = 17; goto _again;} }}
	break;
	case 22:
#line 120 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p+1;}
	break;
	case 23:
#line 90 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p;p--;{ ADVANCE( number ); }}
	break;
	case 24:
#line 92 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p;p--;{
									fprintf(stderr, "Error: invalid number:\n    ");

									for( i = ts; i < te; ++i ) {
										fprintf(stderr, "%c", *i);
									}
									fprintf(stderr, "\n");
									cs	= scanner_error;
								}}
	break;
	case 25:
#line 103 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p;p--;{ ADVANCE( number );}}
	break;
	case 26:
#line 116 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{te = p;p--;{ printf("unexpected character %c\n", *ts); }}
	break;
	case 27:
#line 90 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{{p = ((te))-1;}{ ADVANCE( number ); }}
	break;
	case 28:
#line 116 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"
	{{p = ((te))-1;}{ printf("unexpected character %c\n", *ts); }}
	break;
	case 29:
#line 1 "NONE"
	{	switch( act ) {
	case 5:
	{{p = ((te))-1;} ADVANCE( number ); }
	break;
	case 6:
	{{p = ((te))-1;}
									fprintf(stderr, "Error: invalid number:\n    ");

									for( i = ts; i < te; ++i ) {
										fprintf(stderr, "%c", *i);
									}
									fprintf(stderr, "\n");
									cs	= scanner_error;
								}
	break;
	case 7:
	{{p = ((te))-1;} ADVANCE( number );}
	break;
	case 14:
	{{p = ((te))-1;} ++line; }
	break;
	default:
	{{p = ((te))-1;}}
	break;
	}
	}
	break;
#line 507 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.c"
		}
	}

_again:
	_acts = _scanner_actions + _scanner_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 2:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 520 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.c"
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _scanner_eof_trans[cs] > 0 ) {
		_trans = _scanner_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	_out: {}
	}

#line 192 "C:/Users/Wael/Projects/json-parser/json-parser/lexer.rl"

	/* Check if we failed. */
	if ( cs == scanner_error ) {
		/* Machine failed before finding a token. */
		printf("PARSE ERROR\n");
		exit(1);
	}

	parser_advance(yyparser, 0, NULL, &parser_);

	parser_free(yyparser, free);
	return parser_.root;
}
