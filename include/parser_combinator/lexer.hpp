#ifndef PARSER_COMBINATOR_LEXER_HPP
#define PARSER_COMBINATOR_LEXER_HPP
#include<string>
#include<unordered_map>
#include"boost/xpressive/basic_regex.hpp"
#include"boost/xpressive/regex_algorithms.hpp"
#include"boost/xpressive/regex_primitives.hpp"
namespace parser_combinator
{
	namespace lexer
	{
		template < typename iterator_type >
		class lexer
		{
			using regex_type = boost::xpressive::basic_regex < iterator_type > ;
			using match_results_type = boost::xpressive::match_results < iterator_type > ;
			using string_type = std::basic_string < typename std::iterator_traits < iterator_type >::value_type > ;
			using action_type = std::function < std::string ( const string_type & ) > ;
			iterator_type begin_ ;
			iterator_type end_ ;
			regex_type regex_ { boost::xpressive::_ } ;
			std::unordered_map < decltype ( regex_type { }.regex_id ( ) ) , action_type > action_list_ ;
		public :
			lexer ( ) = delete ;
			lexer ( const lexer & ) = delete ;
			lexer ( lexer && ) = delete ;
			auto operator = ( const lexer & ) -> lexer & = delete ;
			auto operator = ( lexer && ) -> lexer & = delete ;
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
			regex_ = ( boost::xpressive::bos >> regex ) | regex_ ;
			action_list_.emplace ( regex.regex_id ( ) , action ) ;
		}
		template < typename iterator_type >
		auto lexer < iterator_type >::operator ( ) ( ) -> void
		try
		{
			match_results_type result ;
			for ( ; boost::xpressive::regex_search ( begin_ , end_ , result , regex_ ) && ( begin_ != end_ ) ; )
			{
				action_list_.at ( result.regex_id ( ) ) ( result.str ( ) ) ;
				begin_ = result.suffix ( ).first ;
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
		template class lexer < std::string::const_iterator > ;
	}
}
#endif
