/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
 #include <iostream>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <vector>
 #include <memory>

 using namespace std;

 #include "njs.h"
 using namespace NECTAR;
 
/*** $ERROR ***/
function<__NJS_VAR (__NJS_VAR _var)>* __DOLLAR_TEST_ERROR = new function<__NJS_VAR (__NJS_VAR _var)>([&](__NJS_VAR _var){ __NJS_Log_Console(_var); exit(1); return 0; });
__NJS_VAR __NJS_DOLLAR_ERROR = __NJS_VAR(NJS::Enum::Type::FUNCTION, __DOLLAR_TEST_ERROR);
/* end $ERROR */
 
 {INCLUDE}
 
 {DECL}

int main(int argc, char* argv[])
{
	{INIT}

	{CODE}
	return 0;
}
