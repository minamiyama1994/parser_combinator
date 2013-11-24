# parser combinator library

## Motivation

There is a boost::split the famous parser EDSL, but this is a LL parser, it is not possible to perform the analysis of the LR grammar.

In addition, it is too complicated To use easily.

Therefore, we decided to also serve the purpose of learning about LR parsing algorithm, and make your own.

## Sample

```cpp:test.cpp
#include"parser_combinator/parser.hpp"
namespace pp = parser_combinator::parser ;
DECL_RULE_IDS_BEGIN ( id )
	DECL_RULE_ID ( exprs_id )
	DECL_RULE_ID ( expr_id )
	DECL_RULE_ID ( term_id )
	DECL_RULE_ID ( fact_id )
	DECL_RULE_ID ( plus_operation_id )
	DECL_RULE_ID ( minus_operation_id )
	DECL_RULE_ID ( mul_operation_id )
	DECL_RULE_ID ( div_operation_id )
	DECL_RULE_ID ( lp_id )
	DECL_RULE_ID ( rp_id )
	DECL_RULE_ID ( number_id )
	DECL_RULE_ID ( ln_id )
DECL_RULE_IDS_END
auto main ( ) -> int
try
{
	DECL_TOP_RULE ( void * , id::exprs_id , exprs ) ;
	DECL_RULE ( double , id::expr_id , expr ) ;
	DECL_RULE ( double , id::term_id , term ) ;
	DECL_RULE ( double , id::fact_id , fact ) ;
	DECL_TERMINAL ( void * , id::plus_operation_id , plus_operation ) ;
	DECL_TERMINAL ( void * , id::minus_operation_id , minus_operation ) ;
	DECL_TERMINAL ( void * , id::mul_operation_id , mul_operation ) ;
	DECL_TERMINAL ( void * , id::div_operation_id , div_operation ) ;
	DECL_TERMINAL ( void * , id::lp_id , lp ) ;
	DECL_TERMINAL ( void * , id::rp_id , rp ) ;
	DECL_TERMINAL ( double , id::number_id , number ) ;
	DECL_TERMINAL ( void * , id::ln_id , ln ) ;
	auto psr = pp::make_parser
	(
		( exprs = ln ) ( [ ] ( void * ) -> void *
		{
			std::cout << "> " ;
			return nullptr ;
		} ) ,
		( exprs = expr >> ln ) ( [ ] ( double val , void * ) -> void *
		{
			std::cout << val << std::endl ;
			std::cout << "> " ;
			return nullptr ;
		} ) ,
		( exprs = exprs >> ln ) ( [ ] ( void * , void * ) -> void *
		{
			std::cout << "> " ;
			return nullptr ;
		} ) ,
		( exprs = exprs >> expr >> ln ) ( [ ] ( void * , double val , void * ) -> void *
		{
			std::cout << val << std::endl ;
			std::cout << "> " ;
			return nullptr ;
		} ) ,
		( expr = term ) ( [ ] ( double arg )
		{
			return arg ;
		} ) ,
		( expr = expr >> plus_operation >> term ) ( [ ] ( double arg1 , void * , double arg2 )
		{
			return arg1 + arg2 ;
		} ) ,
		( expr = expr >> minus_operation >> term ) ( [ ] ( double arg1 , void * , double arg2 )
		{
			return arg1 - arg2 ;
		} ) ,
		( term = fact ) ( [ ] ( double arg )
		{
			return arg ;
		} ) ,
		( term = term >> mul_operation >> fact ) ( [ ] ( double arg1 , void * , double arg2 )
		{
			return arg1 * arg2 ;
		} ) ,
		( term = term >> div_operation >> fact ) ( [ ] ( double arg1 , void * , double arg2 )
		{
			return arg1 / arg2 ;
		} ) ,
		( fact = lp >> expr >> rp ) ( [ ] ( void * , double arg , void * )
		{
			return arg ;
		} ) ,
		( fact = number ) ( [ ] ( double arg )
		{
			return arg ;
		} )
	) ;
	std::string str ;
	for ( std::cout << "> " , std::getline ( std::cin , str ) ; std::cin ; std::getline ( std::cin , str ) )
	{
		for ( auto iter = str.begin ( ) ; iter != str.end ( ) ; ++ iter )
		{
			if ( * iter == '+' )
			{
				psr ( nullptr , tmp::integral < id , id::plus_operation_id > { } ) ;
			}
			else if ( * iter == '-' )
			{
				psr ( nullptr , tmp::integral < id , id::minus_operation_id > { } ) ;
			}
			else if ( * iter == '*' )
			{
				psr ( nullptr , tmp::integral < id , id::mul_operation_id > { } ) ;
			}
			else if ( * iter == '/' )
			{
				psr ( nullptr , tmp::integral < id , id::div_operation_id > { } ) ;
			}
			else if ( * iter == '(' )
			{
				psr ( nullptr , tmp::integral < id , id::lp_id > { } ) ;
			}
			else if ( * iter == ')' )
			{
				psr ( nullptr , tmp::integral < id , id::rp_id > { } ) ;
			}
			else if ( std::string { "0123456789." }.find ( * iter ) != std::string::npos )
			{
				std::string tmp_str { * iter } ;
				for ( ++ iter ; ( iter != str.end ( ) ) && ( std::string { "0123456789." }.find ( * iter ) != std::string::npos ) ; ++ iter )
				{
					tmp_str += * iter ;
				}
				-- iter ;
				std::istringstream num_stream { tmp_str } ;
				double x ;
				num_stream >> x ;
				psr ( x , tmp::integral < id , id::number_id > { } ) ;
			}
		}
		psr ( nullptr , tmp::integral < id , id::ln_id > { } ) ;
	}
	psr.end ( ) ;
}
catch ( const std::exception & e )
{
	std::cerr << e.what ( ) << std::endl ;
}
```
