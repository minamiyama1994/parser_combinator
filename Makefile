commit:
	./.listup
listup_header:
	find ../TMP/include/TMP/*.hpp | sed -e s'|^\.\./TMP/include/|#include"|' | sed -e s'/$$/"/'
test_:
	g++ -g -I/local/include/boost-1_54/ -I./include/ -I../TMP/include/ -DBOOST_RESULT_OF_USE_DECLTYPE -ftemplate-backtrace-limit=0 -Wall -Wextra -Werror --save-temps -std=c++11 -fexec-charset=cp932 test.cpp -o test