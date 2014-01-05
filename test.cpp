/*  Parser combinator Library
 *  Copyright (C) 2013  Masakazu Minamiyama
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include"parser_combinator/parser.hpp"
namespace pp = parser_combinator::parser ;

// The declaration of the ID for identifying the elements that make up the BNF.
// By following this type as before.
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
	// Declaration of the elements that make up the BNF.
	// DECL_TOP_RULE is exactly one.
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
	
	// Construction of BNF.
	// I want to format "(rule) (semantic action)" of always.
	// When performing the abbreviation of semantic action, operation can not be guaranteed.
	// I specify a function object to semantic action.
	// 
	// TODO:
	// I want to change the design to use to force the addition of semantic action in the future.
	MAKE_PARSER_BEGIN ( psr , SHIFT_REDUCE_CONFLICT_CONCEPT_ERROR , REDUCE_REDUCE_CONFLICT_CONCEPT_ERROR )
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
	MAKE_PARSER_END
	
	// I do it manually now lexical analysis part because it is not implemented yet.
	// 
	// TODO:
	// Implementation of lexical analysis.
	std::string str ;
	for ( std::cout << "> " , std::getline ( std::cin , str ) ; std::cin ; std::getline ( std::cin , str ) )
	{
		for ( auto iter = str.begin ( ) ; iter != str.end ( ) ; ++ iter )
		{
			if ( * iter == '+' )
			{
				
				// I want to specify that this must be input to the parser.
				// Plan to provide, such as macros for simplicity in the future.
				// 
				// TODO:
				// Implementation, such as macros for Optional.
				psr ( nullptr , ftmp::integral < id , id::plus_operation_id > { } ) ;
			}
			else if ( * iter == '-' )
			{
				psr ( nullptr , ftmp::integral < id , id::minus_operation_id > { } ) ;
			}
			else if ( * iter == '*' )
			{
				psr ( nullptr , ftmp::integral < id , id::mul_operation_id > { } ) ;
			}
			else if ( * iter == '/' )
			{
				psr ( nullptr , ftmp::integral < id , id::div_operation_id > { } ) ;
			}
			else if ( * iter == '(' )
			{
				psr ( nullptr , ftmp::integral < id , id::lp_id > { } ) ;
			}
			else if ( * iter == ')' )
			{
				psr ( nullptr , ftmp::integral < id , id::rp_id > { } ) ;
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
				psr ( x , ftmp::integral < id , id::number_id > { } ) ;
			}
			else if ( std::string { " \t\r\n" }.find ( * iter ) != std::string::npos )
			{
			}
			else
			{
				throw std::runtime_error { "parse error." } ;
			}
		}
		psr ( nullptr , ftmp::integral < id , id::ln_id > { } ) ;
	}
	
	// I want to specify that this is the end of the input.
	psr.end ( ) ;
}
catch ( const std::exception & e )
{
	std::cerr << e.what ( ) << std::endl ;
}