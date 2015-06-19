# json-parser

A small, lightweight C99 Ragel/Lemon json parser, easy to use and customize.

Dependencies
------------
On windows, download:

![ragel](https://github.com/eloraiby/ragel-windows) as Lexer generator

![lemon](https://github.com/eloraiby/lemon-windows) as Parser generator

Both should be in your system path.


On *Nix based system both can be downloaded using the default package manager or can be built from source.

For simplicity, I use qmake/Qt Creator as the cross platform build system/IDE. The code can be easily ported to other systems.


Usage
-----
Just include ```json-parser.h``` and call:

```C
json_return_t	json_parse(const char* str);
```
where
```C
typedef struct {
	JSON_STATUS	status;
	json_value_t*	value;
} json_return_t;
```

In case of error, ```value``` will be ```NULL```, otherwise you'll have the json object/array.

To free, just call:
```C
void		json_free(json_value_t*);
```

For the structure details, look at ```json-parser.h``` file.

Important Note
--------------
The string parameter you pass to ```json_parse``` **SHOULD NOT** be freed untill ```json_free``` is called. The **json-parser** will not create or copy any string and will only reference the substrings within the passed string. This was done to improve performance and reduce the stress on memory!

License
-------
```
 json-parser Copyright 2015(c) Wael El Oraiby. All Rights Reserved

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 Under Section 7 of GPL version 3, you are granted additional
 permissions described in the GCC Runtime Library Exception, version
 3.1, as published by the Free Software Foundation.

 You should have received a copy of the GNU General Public License and
 a copy of the GCC Runtime Library Exception along with this program;
 see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
 <http://www.gnu.org/licenses/>.
```

Roughly speaking: it means that you can statically link with the code but you are obliged to make open your bug fixes and/or enhancement to the json-parser code.

Tests come from JsonChecker and nativejson-benchmark. They are copyrighted to their respective authors.

