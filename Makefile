#   Parser combinator Library
#   Copyright (C) 2013  Masakazu Minamiyama
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
commit:
	./.listup
listup_header:
	find ../TMP/include/FTMP/*.hpp | sed -e s'|^\.\./FTMP/include/|#include"|' | sed -e s'/$$/"/'
DEBUG_OPTIONS=-fprofile-arcs -ftest-coverage
test_:
	$(CXX) -pg $(DEBUG_OPTIONS) -I/local/include/boost-1_54/ -I./include/ -I../FTMP/include/ -DBOOST_RESULT_OF_USE_DECLTYPE -ftemplate-backtrace-limit=0 -Wall -Wextra -Werror --save-temps -std=c++11 test.cpp -o test
run:
	./test < script
prof:run
	gprof test.exe gmon.out > prof.txt
gcov:run
	gcov -b *.gcda
	lcov -directory ./ --capture --output coverage.info
	genhtml -o ./coverage coverage.info