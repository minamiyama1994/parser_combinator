#ifndef PARSER_COMBINATOR_LEXER_HPP
#define PARSER_COMBINATOR_LEXER_HPP
#include<iostream>
#include<string>
#include"boost/xpressive/basic_regex.hpp"
#include"boost/xpressive/regex_algorithms.hpp"
#include"boost/xpressive/regex_primitives.hpp"
#include"boost/xpressive/regex_actions.hpp"
namespace parser_combinator
{
	namespace lexer
	{
		namespace bx = boost::xpressive ;
		template < typename iterator_type >
		class lexer
		{
			using regex_type = bx::basic_regex < iterator_type > ;
			using match_results_type = bx::match_results < iterator_type > ;
			using regex_id_filter_predicate_type = bx::regex_id_filter_predicate < iterator_type > ;
			using string_type = std::basic_string < typename std::iterator_traits < iterator_type >::value_type > ;
			using action_type = std::function < void ( const string_type & ) > ;
			iterator_type begin_ ;
			iterator_type end_ ;
			regex_type regex_ ;
		public :
			lexer ( ) = delete ;
			lexer ( const lexer & ) = delete ;
			lexer ( lexer && ) = default ;
			auto operator = ( const lexer & ) -> lexer & = delete ;
			auto operator = ( lexer && ) -> lexer & = default ;
			~ lexer ( ) = default ;
			lexer ( iterator_type begin , iterator_type end ) ;
			auto operator ( ) ( const string_type & string , const action_type & action ) -> void ;
			auto operator ( ) ( const typename string_type::value_type * const string , const action_type & action ) -> void ;
			template < typename expression_type >
			auto operator ( ) ( const expression_type & expr , const action_type & action ) -> void ;
			auto operator ( ) ( ) -> void ;
		} ;
		template < typename iterator_type >
		lexer < iterator_type >::lexer ( iterator_type begin , iterator_type end )
			: begin_ { begin }
			, end_ { end }
		{
		}
		template < typename iterator_type >
		auto lexer < iterator_type >::operator ( ) ( const string_type & string , const action_type & action ) -> void
		{
			( * this ) ( bx::as_xpr ( string ) , action ) ;
		}
		template < typename iterator_type >
		auto lexer < iterator_type >::operator ( ) ( const typename string_type::value_type * const string , const action_type & action ) -> void
		{
			( * this ) ( string_type { string } , action ) ;
		}
		template < typename iterator_type >
		template < typename expression_type >
		auto lexer < iterator_type >::operator ( ) ( const expression_type & expr , const action_type & action ) -> void
		{
			regex_type new_regex { ( bx::bos >> expr ) [ bx::ref ( action ) ( bx::as < string_type > ( bx::_ ) ) ] } ;
			if ( ! regex_.regex_id ( ) )
			{
				regex_ = new_regex ;
			}
			else
			{
				regex_type tmp_regex { regex_ } ;
				regex_ = tmp_regex | new_regex ;
			}
		}
		template < typename iterator_type >
		auto lexer < iterator_type >::operator ( ) ( ) -> void
		try
		{
			regex_type new_regex { bx::bos >> bx::_ } ;
			auto action = [ & ] ( const string_type & str )
			{
				std::cout << "Error : " << str << std::endl ;
			} ;
			regex_type tmp_regex { regex_ } ;
			regex_ = tmp_regex | new_regex [ bx::ref ( action ) ( bx::as < string_type > ( bx::_ ) ) ] ;
			match_results_type result ;
			for ( ; bx::regex_search ( begin_ , end_ , result , regex_ ) && ( begin_ != end_ ) ; begin_ = result [ 0 ].second )
			{
			}
			if ( begin_ != end_ )
			{
				throw std::runtime_error { "" } ;
			}
		}
		catch ( ... )
		{
			begin_ = end_ ;
			throw ;
		}
		template < typename iterator_type >
		auto make_lexer ( iterator_type begin , iterator_type end ) -> lexer < iterator_type >
		{
			return lexer < iterator_type > { begin , end } ;
		}
	}
}
/*
// main.cpp
#include"parser_combinator/lexer.hpp"
auto main ( ) -> int
{
	std::string input { std::istreambuf_iterator < char > { std::cin } , std::istreambuf_iterator < char > { } } ;
	auto lexer = parser_combinator::lexer::make_lexer ( input.begin ( ) , input.end ( ) ) ;
	lexer ( "instance" , [ & ] ( const std::string & str )
	{
		std::cout << str << std::endl ;
	} ) ;
	lexer ( + boost::xpressive::range ( '0' , '9' ) , [ & ] ( const std::string & str )
	{
		std::cout << "number : " << str << std::endl ;
	} ) ;
	lexer ( + ( boost::xpressive::range ( 'a' , 'z' ) | boost::xpressive::range ( 'A' , 'Z' ) ) , [ & ] ( const std::string & str )
	{
		std::cout << "word : " << str << std::endl ;
	} ) ;
	lexer ( + ( boost::xpressive::set = ' ' , '\t' , '\r' , '\n' ) , [ & ] ( const std::string & )
	{
		std::cout << "space" << std::endl ;
	} ) ;
	lexer ( ) ;
}

//input
instanceof
instance

//output
instance
word : of
space
instance
space

*/
#endif
