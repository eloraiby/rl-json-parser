
#line 1 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
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

extern void*    parserAlloc(void *(*mallocProc)(size_t));
extern void     parserFree(void *p, void (*freeProc)(void*));
extern void     parser(void *yyp, int yymajor, token_t yyminor, json_parser_t* s);


#define ADVANCE(A, T)	if( parser_.error_code == 0) { \
                parser_.token_start	= ts; \
                parser_.token_end	= te; \
                parser_.token_line	= line; \
                copy_token(ts, te, tmp); \
                token_t tmpc = token_to_##A(tmp); \
                parser(yyparser, T, tmpc, &parser_); \
            } else cs	= scanner_error

#define ADVANCE_STRING(T) if( parser_.error_code == 0) { \
                parser_.token_start	= string_s; \
                parser_.token_end	= string_e; \
                parser_.token_line	= line; \
                token_t tmpc = token_to_string(string_s, string_e); \
                parser(yyparser, T, tmpc, &parser_); \
            } else cs	= scanner_error

#define ADVANCE_TOKEN(A)	if( parser_.error_code == 0) { token_t t; t.tok_type = A; parser(yyparser, A, t, &parser_); } else p = pe - 1

/* EOF char used to flush out that last token. This should be a whitespace
 * token. */

#define LAST_CHAR 0



#line 63 "/home/wael/projects/rl-json-parser/json-parser/lexer.c"
static const char _scanner_actions[] = {
	0, 1, 0, 1, 1, 1, 3, 1, 
	4, 1, 5, 1, 6, 1, 7, 1, 
	8, 1, 10, 1, 11, 1, 12, 1, 
	18, 1, 19, 1, 20, 1, 21, 1, 
	22, 1, 23, 1, 24, 1, 25, 1, 
	26, 1, 27, 1, 28, 1, 29, 1, 
	31, 1, 32, 1, 33, 1, 34, 1, 
	35, 1, 36, 1, 37, 2, 0, 30, 
	2, 2, 9, 2, 5, 13, 2, 5, 
	14, 2, 5, 15, 2, 5, 16, 2, 
	5, 17
};

static const unsigned char _scanner_key_offsets[] = {
	0, 0, 4, 6, 11, 12, 13, 14, 
	15, 16, 17, 18, 19, 20, 21, 22, 
	24, 27, 33, 39, 45, 51, 80, 82, 
	85, 95, 99, 101, 106, 115, 125, 127, 
	127, 132
};

static const char _scanner_trans_keys[] = {
	43, 45, 48, 57, 48, 57, 46, 69, 
	101, 48, 57, 10, 97, 108, 115, 101, 
	117, 108, 108, 114, 117, 101, 10, 42, 
	10, 42, 47, 48, 57, 65, 70, 97, 
	102, 48, 57, 65, 70, 97, 102, 48, 
	57, 65, 70, 97, 102, 48, 57, 65, 
	70, 97, 102, 10, 34, 39, 43, 44, 
	45, 47, 48, 58, 91, 92, 93, 94, 
	96, 102, 110, 116, 123, 125, 33, 46, 
	49, 57, 59, 64, 65, 122, 124, 126, 
	33, 126, 48, 49, 57, 46, 69, 95, 
	101, 48, 57, 65, 90, 97, 122, 69, 
	101, 48, 57, 48, 57, 95, 65, 90, 
	97, 122, 43, 45, 95, 48, 57, 65, 
	90, 97, 122, 46, 69, 95, 101, 48, 
	57, 65, 90, 97, 122, 42, 47, 34, 
	92, 127, 0, 31, 34, 47, 92, 98, 
	102, 110, 114, 116, 117, 0
};

static const char _scanner_single_lengths[] = {
	0, 2, 0, 3, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 2, 
	3, 0, 0, 0, 0, 19, 0, 1, 
	4, 2, 0, 1, 3, 4, 2, 0, 
	3, 9
};

static const char _scanner_range_lengths[] = {
	0, 1, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 3, 3, 3, 3, 5, 1, 1, 
	3, 1, 1, 2, 3, 3, 0, 0, 
	1, 0
};

static const unsigned char _scanner_index_offsets[] = {
	0, 0, 4, 6, 11, 13, 15, 17, 
	19, 21, 23, 25, 27, 29, 31, 33, 
	36, 40, 44, 48, 52, 56, 81, 83, 
	86, 94, 98, 100, 104, 111, 119, 122, 
	123, 128
};

static const char _scanner_indicies[] = {
	1, 1, 2, 0, 2, 0, 4, 6, 
	6, 5, 3, 9, 8, 10, 11, 12, 
	11, 13, 11, 14, 11, 15, 11, 16, 
	11, 17, 11, 18, 11, 19, 11, 20, 
	11, 22, 23, 21, 22, 23, 24, 21, 
	26, 26, 26, 25, 27, 27, 27, 25, 
	28, 28, 28, 25, 29, 29, 29, 25, 
	31, 33, 11, 34, 35, 34, 36, 37, 
	39, 40, 32, 41, 32, 32, 42, 43, 
	44, 45, 46, 32, 38, 32, 11, 32, 
	30, 0, 30, 37, 38, 47, 4, 50, 
	49, 50, 5, 49, 49, 48, 6, 6, 
	4, 51, 2, 51, 49, 49, 49, 52, 
	1, 1, 49, 2, 49, 49, 52, 4, 
	50, 49, 50, 38, 49, 49, 48, 53, 
	8, 47, 11, 56, 57, 55, 55, 54, 
	59, 59, 59, 59, 59, 59, 59, 59, 
	60, 58, 0
};

static const char _scanner_trans_targs[] = {
	21, 2, 26, 21, 25, 3, 1, 21, 
	4, 21, 6, 0, 7, 8, 21, 10, 
	11, 21, 13, 14, 21, 15, 15, 16, 
	31, 32, 18, 19, 20, 32, 22, 22, 
	21, 21, 23, 21, 30, 24, 29, 21, 
	21, 21, 5, 9, 12, 21, 21, 21, 
	21, 27, 28, 21, 21, 21, 32, 32, 
	32, 33, 32, 32, 17
};

static const char _scanner_trans_actions[] = {
	59, 0, 0, 55, 73, 0, 0, 57, 
	0, 61, 0, 0, 0, 0, 25, 0, 
	0, 27, 0, 0, 23, 0, 1, 0, 
	3, 21, 0, 0, 0, 13, 79, 76, 
	43, 29, 0, 41, 9, 67, 0, 39, 
	35, 37, 0, 0, 0, 31, 33, 53, 
	47, 0, 70, 51, 49, 45, 17, 15, 
	64, 9, 19, 11, 0
};

static const char _scanner_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 5, 
	0, 0, 0, 0, 0, 5, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	5, 0
};

static const char _scanner_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 7, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	7, 0
};

static const unsigned char _scanner_eof_trans[] = {
	0, 1, 1, 4, 8, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 26, 26, 26, 26, 0, 1, 48, 
	49, 52, 52, 53, 53, 49, 48, 0, 
	0, 59
};

static const int scanner_start = 21;
static const int scanner_error = 0;

static const int scanner_en_c_comment = 15;
static const int scanner_en_j_string = 32;
static const int scanner_en_main = 21;


#line 126 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"


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

    yyparser	= parserAlloc(malloc);

    memset(tmp, 0, sizeof(tmp));

    
#line 298 "/home/wael/projects/rl-json-parser/json-parser/lexer.c"
	{
	cs = scanner_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 217 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"

    
#line 309 "/home/wael/projects/rl-json-parser/json-parser/lexer.c"
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
	case 4:
#line 1 "NONE"
	{ts = p;}
	break;
#line 330 "/home/wael/projects/rl-json-parser/json-parser/lexer.c"
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
#line 67 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{ ++line; }
	break;
	case 1:
#line 69 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{ {cs = 21;goto _again;} }
	break;
	case 2:
#line 80 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{ string_e = ts; ADVANCE_STRING(JSON_TOK_STRING); string_s = NULL; string_e = NULL; {cs = 21;goto _again;} }
	break;
	case 5:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 6:
#line 74 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ }}
	break;
	case 7:
#line 75 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ }}
	break;
	case 8:
#line 76 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{
                                        ret.status = JSON_INVALID_STRING;
                                        cs = scanner_error;
                                    }}
	break;
	case 9:
#line 80 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;}
	break;
	case 10:
#line 85 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ }}
	break;
	case 11:
#line 81 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p;p--;{
                                        ret.status = JSON_INVALID_STRING;
                                        cs = scanner_error;
                                    }}
	break;
	case 12:
#line 81 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{{p = ((te))-1;}{
                                        ret.status = JSON_INVALID_STRING;
                                        cs = scanner_error;
                                    }}
	break;
	case 13:
#line 98 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{act = 11;}
	break;
	case 14:
#line 100 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{act = 12;}
	break;
	case 15:
#line 106 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{act = 13;}
	break;
	case 16:
#line 116 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{act = 20;}
	break;
	case 17:
#line 124 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{act = 24;}
	break;
	case 18:
#line 89 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE( boolean, JSON_TOK_BOOLEAN );}}
	break;
	case 19:
#line 90 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE( boolean, JSON_TOK_BOOLEAN );}}
	break;
	case 20:
#line 91 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE( none,    JSON_TOK_NONE    );}}
	break;
	case 21:
#line 94 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ string_s = te; {cs = 32;goto _again;} }}
	break;
	case 22:
#line 109 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_LBRACK );}}
	break;
	case 23:
#line 110 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_RBRACK );}}
	break;
	case 24:
#line 111 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_LSQB   );}}
	break;
	case 25:
#line 112 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_RSQB   );}}
	break;
	case 26:
#line 113 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_COL    );}}
	break;
	case 27:
#line 114 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ADVANCE_TOKEN( JSON_TOK_COMMA  );}}
	break;
	case 28:
#line 119 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ ret.status = JSON_INVALID_CHARACTER; cs = scanner_error; }}
	break;
	case 29:
#line 122 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;{ {cs = 15;goto _again;} }}
	break;
	case 30:
#line 123 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p+1;}
	break;
	case 31:
#line 98 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p;p--;{ ADVANCE( number, JSON_TOK_NUMBER ); }}
	break;
	case 32:
#line 100 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p;p--;{
                                    ret.status	= JSON_INVALID_NUMBER;
                                    cs	= scanner_error;
                                }}
	break;
	case 33:
#line 106 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p;p--;{ ADVANCE( number, JSON_TOK_NUMBER );}}
	break;
	case 34:
#line 119 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{te = p;p--;{ ret.status = JSON_INVALID_CHARACTER; cs = scanner_error; }}
	break;
	case 35:
#line 98 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{{p = ((te))-1;}{ ADVANCE( number, JSON_TOK_NUMBER ); }}
	break;
	case 36:
#line 119 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"
	{{p = ((te))-1;}{ ret.status = JSON_INVALID_CHARACTER; cs = scanner_error; }}
	break;
	case 37:
#line 1 "NONE"
	{	switch( act ) {
	case 11:
	{{p = ((te))-1;} ADVANCE( number, JSON_TOK_NUMBER ); }
	break;
	case 12:
	{{p = ((te))-1;}
                                    ret.status	= JSON_INVALID_NUMBER;
                                    cs	= scanner_error;
                                }
	break;
	case 13:
	{{p = ((te))-1;} ADVANCE( number, JSON_TOK_NUMBER );}
	break;
	case 20:
	{{p = ((te))-1;} ++line; }
	break;
	default:
	{{p = ((te))-1;}}
	break;
	}
	}
	break;
#line 572 "/home/wael/projects/rl-json-parser/json-parser/lexer.c"
		}
	}

_again:
	_acts = _scanner_actions + _scanner_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 3:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 585 "/home/wael/projects/rl-json-parser/json-parser/lexer.c"
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

#line 219 "/home/wael/projects/rl-json-parser/json-parser/lexer.rl"

    /* Check if we failed. */
    if ( cs == scanner_error ) {
        /* Machine failed before finding a token. */
        parser_.error_code = 1;
    }

    parser(yyparser, 0, dummy, &parser_);

    if( parser_.error_code == 1 ) {
        while( parser_.error_code == 1 )
            parser(yyparser, 0, dummy, &parser_);
    }

    if( parser_.error_code != 0 ) {
        ret.status	= JSON_ERROR_SYNTAX_ERROR;

        parserFree(yyparser, free);

        if( parser_.root ) {
            json_free(parser_.root);
        }

        return ret;
    }

    parserFree(yyparser, free);
    ret.status	= JSON_SUCCESS;
    ret.value	= parser_.root;
    return ret;
}

