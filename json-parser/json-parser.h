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
#ifndef JSON_PARSER__H
#define JSON_PARSER__H

#ifndef __cplusplus
#	ifndef bool
#		define bool char
#	endif

#	ifndef false
#		define false 0
#	endif

#	ifndef true
#		define	true (!false)
#	endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	JSON_STRING,
	JSON_NUMBER,
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_BOOLEAN,
	JSON_NONE
} JSON_TYPE;

typedef struct {
	char*				key;
	char*				value;
} json_pair_t;

typedef struct json_value_s {
	JSON_TYPE			tag;

	union {
		char*				string;
		double				number;
		json_pair_t			pair;
		json_pair_t*		members;
		struct json_value_s*	array;
	} value;
} json_value_t;

#ifdef __cplusplus
}
#endif

#endif // JSON_PARSER__H

