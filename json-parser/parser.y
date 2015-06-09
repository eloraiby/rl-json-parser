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

/* the grammar is based on json.org */

%name parser

/*%token_type	{ void* }*/
%extra_argument { json_parser_t* pret }

%include {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"
#include "private/private.h"
}

%syntax_error {
/*	int i = 0;
	int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
	for ( i = 0; i < n; ++i) {
		int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
		if (a < YYNSTATE + YYNRULE) {
			printf("possible token: %s\n", yyTokenName[i]);
		}
	}
*/
fprintf(stderr, "error starting @: %s", pret->token_start);
}

%type pair	{ json_pair_t* }
%type memnbers	{ json_members_t* }
%type elements	{ json_elements_t* }
%type object	{ json_value_t* }
%type value	{ json_value_t* }

%start_symbol root

/* a json file is either an object or an array */
root		::= object(B).			{ pret->root = B; }
root		::= array(B).			{ pret->root = B; }

/* literals */
string(A)	::= JSON_TOK_STRING(B).		{ A = B; }
number(A)	::= JSON_TOK_NUMBER(B).		{ A = B; }
boolean(A)	::= JSON_TOK_BOOLEAN(B).	{ A = B; }
none(A)		::= JSON_TOK_NONE(B).		{ A = B; }

pair(A)		::= string(B) JSON_TOK_COL value(C).	{ A = json_make_pair(B, C); free(B); }

members(A)	::= pair(B).				{ A = json_make_members(B, NULL); }
members(A)	::= members(B) JSON_TOK_COMMA pair(C).	{ A = json_make_members(C, B); }

object(A)	::= JSON_TOK_LBRACK JSON_TOK_RBRACK.	{ A = json_make_object(NULL);	}
object(A)	::= JSON_TOK_LBRACK members(B) JSON_TOK_RBRACK.	{ A = json_make_object(B); json_free_members(B); }

array(A)	::= JSON_TOK_LSQB JSON_TOK_RSQB.	{ A = json_make_array(NULL);	}
array(A)	::= JSON_TOK_LSQB elements(B) JSON_TOK_RSQB.	{ A = json_make_array(B); json_free_elements(B); }

elements(A)	::= value(B).				{ A = json_make_elements(B, NULL); }
elements(A)	::= elements(B) JSON_TOK_COMMA value(C).{ A = json_make_elements(C, B); }

value(A)	::= string(B).				{ A = B; }
value(A)	::= number(B).				{ A = B; }
value(A)	::= boolean(B).				{ A = B; }
value(A)	::= none(B).				{ A = B; }
value(A)	::= object(B).				{ A = B; }
value(A)	::= array(B).				{ A = B; }

