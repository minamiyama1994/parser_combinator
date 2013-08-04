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
		template < typename iterator_type >
		class lexer
		{
			using regex_type = boost::xpressive::basic_regex < iterator_type > ;
			using match_results_type = boost::xpressive::match_results < iterator_type > ;
			using regex_id_filter_predicate_type = boost::xpressive::regex_id_filter_predicate < iterator_type > ;
			using string_type = std::basic_string < typename std::iterator_traits < iterator_type >::value_type > ;
			using action_type = std::function < void ( const string_type & ) > ;
			using regex_id_type = decltype ( regex_type { }.regex_id ( ) ) ;
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
			auto operator ( ) ( const regex_type & regex , const action_type & action ) -> void ;
			auto operator ( ) ( ) -> void ;
		} ;
		template < typename iterator_type >
		lexer < iterator_type >::lexer ( iterator_type begin , iterator_type end )
			: begin_ { begin }
			, end_ { end }
		{
		}
		template < typename iterator_type >
		auto lexer < iterator_type >::operator ( ) ( const regex_type & regex , const action_type & action ) -> void
		{
			regex_type new_regex { boost::xpressive::bos >> regex } ;
			if ( ! regex_.regex_id ( ) )
			{
				regex_ = new_regex [ boost::xpressive::ref ( action ) ( boost::xpressive::as < string_type > ( boost::xpressive::_ ) ) ] ;
			}
			else
			{
				regex_type tmp_regex { regex_ | new_regex [ boost::xpressive::ref ( action ) ( boost::xpressive::as < string_type > ( boost::xpressive::_ ) ) ] } ;
				regex_ = tmp_regex ;
			}
		}
		template < typename iterator_type >
		auto lexer < iterator_type >::operator ( ) ( ) -> void
		try
		{
			regex_type new_regex { boost::xpressive::bos >> boost::xpressive::_ } ;
			action_type action { [ & ] ( const string_type & ) { std::cout << "Error." << std::endl ; } } ;
			regex_type tmp_regex { regex_ | new_regex [ boost::xpressive::ref ( action ) ( boost::xpressive::as < string_type > ( boost::xpressive::_ ) ) ] } ;
			regex_ = tmp_regex ;
			match_results_type result ;
			for ( ; boost::xpressive::regex_search ( begin_ , end_ , result , regex_ ) && ( begin_ != end_ ) ; )
			{
				begin_ = result [ 0 ].second ;
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
#endif
