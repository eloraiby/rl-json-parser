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
#ifndef JSON_PRIVATE_H
#define JSON_PRIVATE_H

#include "../json-parser.h"

typedef struct {
	const char*		token_start;
	const char*		token_end;
	int			token_line;
	int			error_code;	/* 0 : no error */

	json_value_t*	root;
} json_parser_t;


json_pair_t		json_pair		(char* key, json_value_t* value);
json_value_t*		json_add_pair		(json_pair_t, json_value_t* /* object */);
json_value_t*		json_add_element	(json_value_t* /* value */, json_value_t* /* array */);

json_value_t*		json_object		();
json_value_t*		json_array		();
json_value_t*		json_boolean		(bool);
json_value_t*		json_number		(double);
json_value_t*		json_string		(char*);
json_value_t*		json_none		();

#endif // JSON_PRIVATE_H

