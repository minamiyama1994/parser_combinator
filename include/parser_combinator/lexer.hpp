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
			template < typename ... args_type >
			lexer ( iterator_type begin , iterator_type end , const args_type & ... args ) ;
			auto operator ( ) ( ) -> void ;
		} ;
		template < typename iterator_type , typename regex_expression_type >
		auto make_regex_helper ( const regex_expression_type & expression ) -> bx::basic_regex < iterator_type >
		{
			return expression | ( bx::bos >> bx::_ ) ;
		}
		template < typename iterator_type , typename regex_expression_type , typename regex_type , typename action_type , typename ... args_type >
		auto make_regex_helper ( const regex_expression_type & expression , const regex_type & regex , const action_type & action , const args_type & ... args ) -> bx::basic_regex < iterator_type >
		{
			return make_regex_helper < iterator_type >  ( expression | ( bx::bos >> regex ) [ bx::ref ( action ) ( bx::_ ) ] , args ... ) ;
		}
		template < typename iterator_type , typename regex_type , typename action_type , typename ... args_type >
		auto make_regex ( const regex_type & regex , const action_type & action , const args_type & ... args ) -> bx::basic_regex < iterator_type >
		{
			return make_regex_helper < iterator_type > ( ( bx::bos >> regex ) [ bx::ref ( action ) ( bx::_ ) ] , args ... ) ;
		}
		template < typename iterator_type >
		template < typename ... args_type >
		lexer < iterator_type >::lexer ( iterator_type begin , iterator_type end , const args_type & ... args )
			: begin_ { begin }
			, end_ { end }
			, regex_ ( make_regex < iterator_type > ( args ... ) )
		{
		}
		template < typename iterator_type >
		auto lexer < iterator_type >::operator ( ) ( ) -> void
		try
		{
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
		template < typename iterator_type , typename ... args_type >
		auto make_lexer ( iterator_type begin , iterator_type end , const args_type & ... args ) -> lexer < iterator_type >
		{
			return lexer < iterator_type > { begin , end , args ... } ;
		}
	}
}
#endif
