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
#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
#include<istream>
#include<ostream>
#include<iostream>
#include<sstream>
#include<functional>
#include<tuple>
#include<memory>
#include<stack>
#include<vector>
#include<unordered_map>
#include<set>
#include<algorithm>
#include"boost/any.hpp"
#include"FTMP/append.hpp"
#include"FTMP/at.hpp"
#include"FTMP/cons.hpp"
#include"FTMP/eval.hpp"
#include"FTMP/filter.hpp"
#include"FTMP/foldr.hpp"
#include"FTMP/head.hpp"
#include"FTMP/id.hpp"
#include"FTMP/insert.hpp"
#include"FTMP/integral.hpp"
#include"FTMP/list.hpp"
#include"FTMP/lookup.hpp"
#include"FTMP/map.hpp"
#include"FTMP/size.hpp"
#include"FTMP/to_dict.hpp"
#include"FTMP/to_list.hpp"
#include"FTMP/to_set.hpp"
#include"FTMP/unique.hpp"
#define DECL_RULE_IDS_BEGIN(name) \
	enum class name : int \
	{ \
		parser_combinator_parser_decl_rule_ids_begin_dummy = -1 , \
		parser_combinator_parser_decl_rule_ids_begin = 0 ,
#define DECL_RULE_ID(name) \
	name ,
#define DECL_RULE_IDS_END \
		parser_combinator_parser_decl_rule_ids_end \
	} ;
#define DECL_TOP_RULE(T,id,name) \
	parser_combinator::parser::top_rule < T , decltype ( id ) , id > name { }
#define DECL_RULE(T,id,name) \
	parser_combinator::parser::rule < T , decltype ( id ) , id > name { }
#define DECL_TERMINAL(T,id,name) \
	parser_combinator::parser::terminal < T , decltype ( id ) , id > name { }
namespace parser_combinator
{
	namespace parser
	{
		namespace detail
		{
			template < typename T >
			struct internal_id_tag
			{
				using type = void ;
			} ;
		}
		template < typename lhs_type , typename rhs_type >
		struct assign_result ;
		template < typename lhs_type , typename rhs_type >
		struct shift_result ;
		template < typename T , typename id_type , id_type id >
		struct top_rule
		{
			using type = top_rule ;
			static constexpr id_type value = id ;
			top_rule ( ) = default ;
			top_rule ( const top_rule & ) = default ;
			top_rule ( top_rule && ) = default ;
			auto operator = ( const top_rule & ) -> top_rule & = default ;
			auto operator = ( top_rule && ) -> top_rule & = default ;
			~ top_rule ( ) = default ;
			template < typename rhs_type >
			auto operator = ( const rhs_type & ) -> assign_result < top_rule , rhs_type > ;
		} ;
		template < typename T , typename id_type , id_type id >
		struct rule
		{
			using type = rule ;
			static constexpr id_type value = id ;
			rule ( ) = default ;
			rule ( const rule & ) = default ;
			rule ( rule && ) = default ;
			auto operator = ( const rule & ) -> rule & = default ;
			auto operator = ( rule && ) -> rule & = default ;
			~ rule ( ) = default ;
			template < typename rhs_type >
			auto operator = ( const rhs_type & ) -> assign_result < rule , rhs_type > ;
		} ;
		template < typename T , typename id_type , id_type id >
		struct terminal
		{
			using type = terminal ;
			static constexpr id_type value = id ;
			terminal ( ) = default ;
			terminal ( const terminal & ) = default ;
			terminal ( terminal && ) = default ;
			auto operator = ( const terminal & ) -> terminal & = default ;
			auto operator = ( terminal && ) -> terminal & = default ;
			~ terminal ( ) = default ;
		} ;
		template < typename id_type >
		class term
		{
			id_type id_ ;
		public :
			using type = id_type ;
			term ( ) = delete ;
			term ( const term & ) = default ;
			term ( term && ) = default ;
			auto operator = ( const term & ) -> term & = default ;
			auto operator = ( term && ) -> term & = default ;
			term ( id_type id )
				: id_ ( id )
			{
			}
			virtual ~ term ( )
			{
			}
			virtual auto is_top_rule ( ) -> bool
			{
				return false ;
			}
			virtual auto is_rule ( ) -> bool
			{
				return false ;
			}
			virtual auto is_terminal ( ) -> bool
			{
				return false ;
			}
			virtual auto is_current_read ( ) -> bool
			{
				return false ;
			}
			auto get ( ) const -> id_type
			{
				return id_ ;
			}
		} ;
		template < typename id_type >
		class detail_top_rule
			: public term < id_type >
		{
		public :
			detail_top_rule ( ) = delete ;
			detail_top_rule ( const detail_top_rule & ) = default ;
			detail_top_rule ( detail_top_rule && ) = default ;
			auto operator = ( const detail_top_rule & ) -> detail_top_rule & = default ;
			auto operator = ( detail_top_rule && ) -> detail_top_rule & = default ;
			~ detail_top_rule ( ) = default ;
			using term < id_type >::term ;
			auto is_top_rule ( ) -> bool override
			{
				return true ;
			}
		} ;
		template < typename id_type >
		class detail_rule
			: public term < id_type >
		{
		public :
			detail_rule ( ) = delete ;
			detail_rule ( const detail_rule & ) = default ;
			detail_rule ( detail_rule && ) = default ;
			auto operator = ( const detail_rule & ) -> detail_rule & = default ;
			auto operator = ( detail_rule && ) -> detail_rule & = default ;
			~ detail_rule ( ) = default ;
			using term < id_type >::term ;
			auto is_rule ( ) -> bool override
			{
				return true ;
			}
		} ;
		template < typename id_type >
		class detail_terminal
			: public term < id_type >
		{
		public :
			detail_terminal ( ) = delete ;
			detail_terminal ( const detail_terminal & ) = default ;
			detail_terminal ( detail_terminal && ) = default ;
			auto operator = ( const detail_terminal & ) -> detail_terminal & = default ;
			auto operator = ( detail_terminal && ) -> detail_terminal & = default ;
			~ detail_terminal ( ) = default ;
			using term < id_type >::term ;
			auto is_terminal ( ) -> bool override
			{
				return true ;
			}
		} ;
		template < typename id_type >
		class current_read
			: public term < id_type >
		{
		public :
			current_read ( )
				: term < id_type > ( id_type::parser_combinator_parser_decl_rule_ids_begin_dummy )
			{
			}
			current_read ( const current_read & ) = default ;
			current_read ( current_read && ) = default ;
			auto operator = ( const current_read & ) -> current_read & = default ;
			auto operator = ( current_read && ) -> current_read & = default ;
			~ current_read ( ) = default ;
			auto is_current_read ( ) -> bool override
			{
				return true ;
			}
		} ;
		template < typename T , typename id_type >
		using end_read = terminal < T , id_type , id_type::parser_combinator_parser_decl_rule_ids_end > ;
		template < typename T >
		struct assign_to_function ;
		template < typename rule_type >
		struct get_value_type ;
		template < typename rule_type >
		struct get_id ;
		template < typename first_type , typename second_type >
		class first_only_tuple
			: public std::tuple < first_type , second_type >
		{
		public :
			first_only_tuple ( ) = default ;
			first_only_tuple ( const first_only_tuple & ) = default ;
			first_only_tuple ( first_only_tuple && ) = default ;
			auto operator = ( const first_only_tuple & ) -> first_only_tuple & = default ;
			auto operator = ( first_only_tuple && ) -> first_only_tuple & = default ;
			~ first_only_tuple ( ) = default ;
			first_only_tuple ( const first_type & first ) ;
			template < typename T >
			first_only_tuple ( const T & ) ;
		} ;
		template < typename first_type , typename second_type >
		first_only_tuple < first_type , second_type >::first_only_tuple ( const first_type & first )
			: std::tuple < first_type , second_type > { first , second_type { } }
		{
		}
		template < typename first_type , typename second_type >
		template < typename T >
		first_only_tuple < first_type , second_type >::first_only_tuple ( const T & )
			: std::tuple < first_type , second_type > { first_type { } , second_type { } }
		{
		}
		template < int index , typename type_tuple , typename ... args_type >
		struct make_rules_helper ;
		template < int index , typename ... type_in_tuple >
		struct make_rules_helper < index , ftmp::list < type_in_tuple ... > >
		{
			using type = std::tuple < type_in_tuple ... > ;
		} ;
		template < int index , typename ... type_in_tuple , typename args_head , typename ... args_type >
		struct make_rules_helper < index , ftmp::list < type_in_tuple ... > , args_head , args_type ... >
			: make_rules_helper < index + 1 , ftmp::list < type_in_tuple ... , first_only_tuple < args_head , ftmp::integral < int , index > > > , args_type ... >
		{
		} ;
		template < typename T >
		struct to_rule_list ;
		template < typename ... list >
		struct to_rule_list < std::tuple < list ... > >
			: ftmp::list < typename to_rule_list < list >::type ... >
		{
		} ;
		template < typename T1 , typename T2 >
		struct to_rule_list < first_only_tuple < T1 , T2 > >
		{
			using type = first_only_tuple < T1 , T2 > ;
		} ;
		template < typename T1 , typename T2 >
		struct to_rule_list < assign_result < T1 , T2 > >
		{
			using type = assign_result < T1 , T2 > ;
		} ;
		template < typename T >
		struct to_list ;
		template < typename ... list >
		struct to_list < ftmp::list < list ... > >
			: ftmp::list < typename to_list < list >::type ... >
		{
		} ;
		template < typename T1 , typename T2 >
		struct to_list < first_only_tuple < T1 , T2 > >
			: ftmp::list < typename to_list < T1 >::type , T2 >
		{
		} ;
		template < typename T1 , typename T2 >
		struct to_list < assign_result < T1 , T2 > >
			: assign_result < T1 , T2 >
		{
		} ;
		template < typename T >
		struct is_top_rule
			: ftmp::integral < bool , false >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_top_rule < top_rule < T , id_type , id > >
			: ftmp::integral < bool , true >
		{
		} ;
		template < typename T >
		struct get_top_rule
			: ftmp::head
			<
				typename ftmp::to_list
				<
					typename ftmp::filter
					<
						is_top_rule < ftmp::arg < 0 > > ,
						typename ftmp::map
						<
							ftmp::eval < ftmp::at
							<
								ftmp::at < ftmp::arg < 0 > , ftmp::integral < int , 0 > > ,
								ftmp::integral < int , 0 >
							> > ,
							typename ftmp::to_set < typename to_list < T >::type >::type
						>::type
					>::type
				>::type
			>::type
		{
			static_assert ( ftmp::size
			<
				typename ftmp::to_list
				<
					typename ftmp::filter
					<
						is_top_rule < ftmp::arg < 0 > > ,
						typename ftmp::map
						<
							ftmp::eval < ftmp::at
							<
								ftmp::at < ftmp::arg < 0 > , ftmp::integral < int , 0 > > ,
								ftmp::integral < int , 0 >
							> > ,
							typename ftmp::to_set < typename to_list < T >::type >::type
						>::type
					>::type
				>::type
			>::value == 1 , "top_rule is duplication." ) ;
		} ;
		template < typename T , typename type_tuple >
		struct make_rules_impl_helper ;
		template < typename T , typename id_type , id_type id , typename ... type_tuple >
		struct make_rules_impl_helper < top_rule < T , id_type , id > , std::tuple < type_tuple ... > >
		{
			using type = std::tuple
			<
				first_only_tuple
				<
					assign_result
					<
						top_rule < T , id_type , id_type::parser_combinator_parser_decl_rule_ids_begin > ,
						rule < T , id_type , id >
					> ,
					ftmp::integral < int , 0 >
				> ,
				type_tuple ...
			> ;
		} ;
		template < typename T >
		struct make_rules_impl ;
		template < typename ... T >
		struct make_rules_impl < std::tuple < T ... > >
			: make_rules_impl_helper
			<
				typename get_top_rule
				<
					typename to_rule_list < std::tuple < T ... > >::type
				>::type ,
				std::tuple < T ... >
			>
		{
		} ;
		template < int index , typename type_tuple , typename ... args_type >
		struct make_rules
			: make_rules_impl < typename make_rules_helper < index , type_tuple , args_type ... >::type >
		{
		} ;
		template < typename id_type , id_type id >
		auto get_detail_top_rule ( ) -> std::shared_ptr < detail_top_rule < id_type > >
		{
			static auto value = std::make_shared < detail_top_rule < id_type > > ( id ) ;
			return value ;
		}
		template < typename id_type , id_type id >
		auto get_detail_rule ( ) -> std::shared_ptr < detail_rule < id_type > >
		{
			static auto value = std::make_shared < detail_rule < id_type > > ( id ) ;
			return value ;
		}
		template < typename id_type , id_type id >
		auto get_detail_terminal ( ) -> std::shared_ptr < detail_terminal < id_type > >
		{
			static auto value = std::make_shared < detail_terminal < id_type > > ( id ) ;
			return value ;
		}
		template < typename id_type >
		auto get_current_read ( ) -> std::shared_ptr < current_read < id_type > >
		{
			static auto value = std::make_shared < current_read < id_type > > ( ) ;
			return value ;
		}
		template < typename T >
		struct make_LR0_heper ;
		template < typename T , typename id_type >
		struct make_LR0_heper < top_rule < T , id_type , id_type::parser_combinator_parser_decl_rule_ids_begin > >
		{
			static auto func ( ) -> std::shared_ptr < term < id_type > >
			{
				return get_detail_top_rule < id_type , id_type::parser_combinator_parser_decl_rule_ids_begin > ( ) ;
			}
		} ;
		template < typename T , typename id_type , id_type id >
		struct make_LR0_heper < top_rule < T , id_type , id > >
		{
			static auto func ( ) -> std::shared_ptr < term < id_type > >
			{
				return get_detail_rule < id_type , id > ( ) ;
			}
		} ;
		template < typename T , typename id_type , id_type id >
		struct make_LR0_heper < rule < T , id_type , id > >
		{
			static auto func ( ) -> std::shared_ptr < term < id_type > >
			{
				return get_detail_rule < id_type , id > ( ) ;
			}
		} ;
		template < typename T , typename id_type , id_type id >
		struct make_LR0_heper < terminal < T , id_type , id > >
		{
			static auto func ( ) -> std::shared_ptr < term < id_type > >
			{
				return get_detail_terminal < id_type , id > ( ) ;
			}
		} ;
		template < typename T1 , typename T2 >
		struct make_LR0_heper < assign_result < T1 , T2 > >
		{
			using head_type = typename ftmp::at < typename assign_result < T1 , T2 >::type , ftmp::integral < int , 0 > >::type ;
			using body_type = typename ftmp::at < typename assign_result < T1 , T2 >::type , ftmp::integral < int , 1 > >::type ;
			static auto func ( ) -> decltype ( std::make_pair ( make_LR0_heper < head_type >::func ( ) , make_LR0_heper < body_type >::func ( ) ) )
			{
				return std::make_pair ( make_LR0_heper < head_type >::func ( ) , make_LR0_heper < body_type >::func ( ) ) ;
			}
		} ;
		template < typename T1 , typename T2 >
		struct make_LR0_heper < first_only_tuple < T1 , T2 > >
		{
			static auto func ( ) -> decltype ( std::make_pair ( make_LR0_heper < T1 >::func ( ) , T2::value ) )
			{
				return std::make_pair ( make_LR0_heper < T1 >::func ( ) , T2::value ) ;
			}
		} ;
		template < typename ... T >
		struct make_LR0_heper < ftmp::list < T ... > >
		{
			static auto func ( ) -> std::vector < typename ftmp::head < ftmp::list < decltype ( make_LR0_heper < T >::func ( ) ) ... > >::type >
			{
				return std::vector < typename ftmp::head < ftmp::list < decltype ( make_LR0_heper < T >::func ( ) ) ... > >::type > { make_LR0_heper < T >::func ( ) ... } ;
			}
		} ;
		template < typename T >
		auto make_LR0 ( ) -> decltype ( make_LR0_heper < T >::func ( ) )
		{
			using id_type = typename decltype ( make_LR0_heper < T >::func ( ) )::value_type::first_type::first_type::element_type::type ;
			auto tmp_res = make_LR0_heper < T >::func ( ) ;
			decltype ( tmp_res ) res ;
			for ( auto & elem : tmp_res )
			{
				auto index = elem.second ;
				auto head = elem.first.first ;
				for ( auto iter = elem.first.second.begin ( ) ; iter != elem.first.second.end ( ) ; ++ iter )
				{
					auto pos = elem.first.second.insert ( iter , get_current_read < id_type > ( ) ) ;
					res.emplace_back ( std::make_pair ( head , elem.first.second ) , index ) ;
					iter = elem.first.second.erase ( pos ) ;
				}
				elem.first.second.insert ( elem.first.second.end ( ) , get_current_read < id_type > ( ) ) ;
				res.emplace_back ( std::make_pair ( head , elem.first.second ) , index ) ;
			}
			return res ;
		}
		template < typename id_type >
		using element_type = std::pair
		<
			std::pair
			<
				std::shared_ptr < term < id_type > > ,
				std::vector < std::shared_ptr < term < id_type > > >
			> ,
			int
		> ;
		template < typename id_type >
		auto make_closure ( const std::set < element_type < id_type > > & I , const std::vector < element_type < id_type > > & env ) -> std::set < element_type < id_type > >
		{
			std::set < element_type < id_type > > res = I ;
			for ( auto & elem : I )
			{
				auto body = elem.first.second ;
				auto iter = std::find ( body.begin ( ) , body.end ( ) , get_current_read < id_type > ( ) );
				if ( iter != body.end ( ) && ++ iter != body.end ( ) )
				{
					for ( auto & env_elem : env )
					{
						if ( env_elem.first.first == * iter && * env_elem.first.second.begin ( ) == get_current_read < id_type > ( ) )
						{
							res.insert ( env_elem ) ;
						}
					}
				}
			}
			if ( res == I )
			{
				return res ;
			}
			return make_closure ( res , env ) ;
		}
		template < typename id_type >
		auto make_goto ( const std::set < element_type < id_type > > & I , std::shared_ptr < term < id_type > > X , const std::vector < element_type < id_type > > & env ) -> std::set < element_type < id_type > >
		{
			std::set < element_type < id_type > > res ;
			for ( auto & elem : I )
			{
				auto body = elem.first.second ;
				auto iter = std::find ( body.begin ( ) , body.end ( ) , get_current_read < id_type > ( ) );
				if ( iter != body.end ( ) && ++ iter != body.end ( ) && * iter == X )
				{
					auto tmp_iter = iter ;
					-- tmp_iter ;
					std::swap ( * iter , * tmp_iter ) ;
					res.insert ( std::make_pair ( std::make_pair ( elem.first.first , body ) , elem.second ) ) ;
				}
			}
			return make_closure ( res , env ) ;
		}
		template < typename id_type >
		auto make_first_helper ( const std::vector < std::shared_ptr < term < id_type > > > & a , std::set < std::shared_ptr < term < id_type > > > already , const std::vector < element_type < id_type > > & env ) -> std::set < std::shared_ptr < term < id_type > > >
		{
			if ( a.size ( ) == 1 && ( * a.begin ( ) )->is_terminal ( ) )
			{
				return { * a.begin ( ) } ;
			}
			else if ( a.size ( ) == 1 )
			{
				if ( already.find ( * a.begin ( ) ) != already.end ( ) )
				{
					return { } ;
				}
				std::set < std::shared_ptr < term < id_type > > > res ;
				already.insert ( * a.begin ( ) ) ;
				for ( auto & elem : env )
				{
					if ( * a.begin ( ) == elem.first.first )
					{
						auto tmp = make_first_helper ( elem.first.second , already , env ) ;
						res.insert ( tmp.begin ( ) , tmp.end ( ) ) ;
					}
				}
				return res ;
			}
			else
			{
				return make_first_helper ( { * a.begin ( ) } , already , env ) ;
			}
		}
		template < typename id_type >
		auto make_first ( const std::vector < std::shared_ptr < term < id_type > > > & a , const std::vector < element_type < id_type > > & env ) -> std::set < std::shared_ptr < term < id_type > > >
		{
			return make_first_helper ( a , { } , env ) ;
		}
		template < typename id_type >
		auto make_follow_helper ( std::shared_ptr < term < id_type > > A , const std::set < std::shared_ptr < term < id_type > > > & already , const std::vector < element_type < id_type > > & env ) -> std::set < std::shared_ptr < term < id_type > > >
		{
			if ( already.find ( A ) != already.end ( ) )
			{
				return { } ;
			}
			auto next_alread = already ;
			next_alread.insert ( A ) ;
			std::set < std::shared_ptr < term < id_type > > > res ;
			for ( auto & elem : env )
			{
				std::vector < typename std::vector < std::shared_ptr < term < id_type > > >::const_iterator > iters ;
				for ( auto iter = elem.first.second.begin ( ) ; iter != elem.first.second.end ( ) ; ++ iter )
				{
					if ( A == * iter )
					{
						iters.push_back ( iter ) ;
					}
				}
				if ( elem.first.first->is_top_rule ( ) && elem.first.second.size ( ) == 1 && iters.size ( ) == 1 )
				{
					res.insert ( get_detail_terminal < id_type , id_type::parser_combinator_parser_decl_rule_ids_end > ( ) ) ;
				}
				for ( auto iter : iters )
				{
					++ iter ;
					if ( iter == elem.first.second.end ( ) )
					{
						auto tmp = make_follow_helper ( elem.first.first , next_alread , env ) ;
						res.insert ( tmp.begin ( ) , tmp.end ( ) ) ;
					}
					else
					{
						auto tmp = make_first ( std::vector < std::shared_ptr < term < id_type > > > ( iter , elem.first.second.end ( ) ) , env ) ;
						res.insert ( tmp.begin ( ) , tmp.end ( ) ) ;
					}
				}
			}
			return res ;
		}
		template < typename id_type >
		auto make_follow ( const std::vector < std::shared_ptr < term < id_type > > > & A , const std::vector < element_type < id_type > > & env ) -> std::set < std::shared_ptr < term < id_type > > >
		{
			return make_follow_helper ( * A.begin ( ) , { } , env ) ;
		}
		template < typename id_type >
		auto make_closures_helper ( const std::vector < std::set < element_type < id_type > > > & already , const std::set < std::set < element_type < id_type > > > & new_closures , const std::vector < element_type < id_type > > & env ) -> std::vector < std::set < element_type < id_type > > >
		{
			std::vector < std::set < element_type < id_type > > > next_already = already ;
			std::set < std::set < element_type < id_type > > > include_already ;
			for ( auto & elem : new_closures )
			{
				if ( std::find ( already.begin ( ) , already.end ( ) , elem ) == already.end ( ) )
				{
					next_already.push_back ( elem ) ;
					include_already.insert ( elem ) ;
				}
			}
			if ( include_already.empty ( ) )
			{
				next_already.erase ( std::remove ( next_already.begin ( ) , next_already.end ( ) , std::set < element_type < id_type > > { } ) , next_already.end ( ) ) ;
				return next_already ;
			}
			std::set < std::set < element_type < id_type > > > next_new_closures ;
			for ( auto & elem : include_already )
			{
				for ( auto & rule : elem )
				{
					auto iter = std::find ( rule.first.second.begin ( ) , rule.first.second.end ( ) , get_current_read < id_type > ( ) ) ;
					++ iter ;
					if ( iter != rule.first.second.end ( ) )
					{
						next_new_closures.insert ( make_goto ( elem , * iter , env ) ) ;
					}
				}
			}
			return make_closures_helper ( next_already , next_new_closures , env ) ;
		}
		template < typename id_type >
		auto make_closures ( const std::vector < element_type < id_type > > & env ) -> std::vector < std::set < element_type < id_type > > >
		{
			return make_closures_helper ( { } , { make_closure ( { * env.begin ( ) } , env ) } , env ) ;
		}
		class detail_action_base
		{
		public :
			detail_action_base ( ) = default ;
			detail_action_base ( const detail_action_base & ) = default ;
			detail_action_base ( detail_action_base && ) = default ;
			auto operator = ( const detail_action_base & ) -> detail_action_base & = default ;
			auto operator = ( detail_action_base && ) -> detail_action_base & = default ;
			virtual auto get ( ) -> int = 0 ;
			virtual auto is_error ( ) -> bool
			{
				return false ;
			}
			virtual auto is_shift ( ) -> bool
			{
				return false ;
			}
			virtual auto is_reduce ( ) -> bool
			{
				return false ;
			}
			virtual auto is_accept ( ) -> bool
			{
				return false ;
			}
			virtual ~ detail_action_base ( )
			{
			}
		} ;
		class detail_shift
			: public detail_action_base
		{
			int i_ ;
		public :
			detail_shift ( ) = delete ;
			detail_shift ( const detail_shift & ) = default ;
			detail_shift ( detail_shift && ) = default ;
			auto operator = ( const detail_shift & ) -> detail_shift & = default ;
			auto operator = ( detail_shift && ) -> detail_shift & = default ;
			~ detail_shift ( ) = default ;
			detail_shift ( int i )
				: i_ ( i )
			{
			}
			auto is_shift ( ) -> bool override
			{
				return true ;
			}
			auto get ( ) -> int override
			{
				return i_ ;
			}
		} ;
		class detail_reduce
			: public detail_action_base
		{
			int i_ ;
		public :
			detail_reduce ( ) = delete ;
			detail_reduce ( const detail_reduce & ) = default ;
			detail_reduce ( detail_reduce && ) = default ;
			auto operator = ( const detail_reduce & ) -> detail_reduce & = default ;
			auto operator = ( detail_reduce && ) -> detail_reduce & = default ;
			~ detail_reduce ( ) = default ;
			detail_reduce ( int i )
				: i_ ( i )
			{
			}
			auto is_reduce ( ) -> bool override
			{
				return true ;
			}
			auto get ( ) -> int override
			{
				return i_ ;
			}
		} ;
		class detail_accept
			: public detail_action_base
		{
		public :
			auto is_accept ( ) -> bool override
			{
				return true ;
			}
			auto get ( ) -> int override
			{
				return - 1 ;
			}
		} ;
		class conflict_error
			: public std::runtime_error
		{
		public :
			using std::runtime_error::runtime_error ;
		} ;
		template < typename id_type >
		auto make_shift_table ( const std::vector < std::set < element_type < id_type > > > & closures , const std::vector < std::shared_ptr < term < id_type > > > & components , const std::vector < element_type < id_type > > & env ) -> std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > >
		{
			std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > res ;
			for ( auto closure_iter = closures.begin ( ) ; closure_iter != closures.end ( ) ; ++ closure_iter )
			{
				for ( auto component_iter = components.begin ( ) ; component_iter != components.end ( ) ; ++ component_iter )
				{
					auto goto_ = make_goto ( * closure_iter , * component_iter , env ) ;
					res [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( ( * component_iter )->get ( ) ) ] = goto_.empty ( ) ? nullptr : std::make_shared < detail_shift > ( ( std::find ( closures.begin ( ) , closures.end ( ) , goto_ ) - closures.begin ( ) ) ) ;
				}
			}
			return res ;
		}
		template < typename id_type >
		auto make_reduce_table ( const std::vector < std::set < element_type < id_type > > > & closures , const std::vector < std::shared_ptr < term < id_type > > > & components , const std::vector < element_type < id_type > > & env ) -> std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > >
		{
			std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > res ;
			for ( auto closure_iter = closures.begin ( ) ; closure_iter != closures.end ( ) ; ++ closure_iter )
			{
				for ( auto component_iter = components.begin ( ) ; component_iter != components.end ( ) ; ++ component_iter )
				{
					auto goto_ = make_goto ( * closure_iter , * component_iter , env ) ;
					res [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( ( * component_iter )->get ( ) ) ] = nullptr ;
				}
			}
			auto tmp_env = env ;
			for ( auto & elem : tmp_env )
			{
				elem.first.second.erase ( std::find ( elem.first.second.begin ( ) , elem.first.second.end ( ) , get_current_read < id_type > ( ) ) ) ;
			}
			std::sort ( tmp_env.begin ( ) , tmp_env.end ( ) ) ;
			tmp_env.erase ( std::unique ( tmp_env.begin ( ) , tmp_env.end ( ) ) , tmp_env.end ( ) ) ;
			std::unique ( tmp_env.begin ( ) , tmp_env.end ( ) ) ;
			for ( auto closure_iter = closures.begin ( ) ; closure_iter != closures.end ( ) ; ++ closure_iter )
			{
				for ( auto rule_iter = closure_iter->begin ( ) ; rule_iter != closure_iter->end ( ) ; ++ rule_iter )
				{
					if ( rule_iter->first.second.back ( )->is_current_read ( ) )
					{
						for ( auto & elem : make_follow ( { rule_iter->first.first } , tmp_env ) )
						{
							auto & elm = res [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( elem->get ( ) ) ] ;
							if ( elm )
							{
								std::ostringstream stream ;
								stream << "reduce/reduce conflict." << std::endl << "    rule:" << elm->get ( ) << std::endl << "    rule:" << rule_iter->second << std::endl ;
								throw conflict_error { stream.str ( ) } ;
							}
							elm = std::make_shared < detail_reduce > ( rule_iter->second ) ;
						}
					}
				}
			}
			return res ;
		}
		template < typename id_type >
		auto make_accept_table ( const std::vector < std::set < element_type < id_type > > > & closures , const std::vector < std::shared_ptr < term < id_type > > > & components , const std::vector < element_type < id_type > > & env ) -> std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > >
		{
			std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > res ;
			for ( auto closure_iter = closures.begin ( ) ; closure_iter != closures.end ( ) ; ++ closure_iter )
			{
				for ( auto component_iter = components.begin ( ) ; component_iter != components.end ( ) ; ++ component_iter )
				{
					auto goto_ = make_goto ( * closure_iter , * component_iter , env ) ;
					res [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( ( * component_iter )->get ( ) ) ] = nullptr ;
				}
			}
			for ( auto closure_iter = closures.begin ( ) ; closure_iter != closures.end ( ) ; ++ closure_iter )
			{
				for ( auto rule_iter = closure_iter->begin ( ) ; rule_iter != closure_iter->end ( ) ; ++ rule_iter )
				{
					if ( rule_iter->first.first->is_top_rule ( ) && rule_iter->first.second.back ( )->is_current_read ( ) )
					{
						res [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( components.back ( )->get ( ) ) ] = std::make_shared < detail_accept > ( ) ;
					}
				}
			}
			return res ;
		}
		template < typename id_type >
		auto make_table ( const std::vector < std::set < element_type < id_type > > > & closures , const std::vector < std::shared_ptr < term < id_type > > > & components , const std::vector < element_type < id_type > > & env ) -> std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > >
		{
			auto shift_table = make_shift_table ( closures , components , env ) ;
			auto reduce_table = make_reduce_table ( closures , components , env ) ;
			auto accept_table = make_accept_table ( closures , components , env ) ;
			std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > res ;
			for ( auto closure_iter = closures.begin ( ) ; closure_iter != closures.end ( ) ; ++ closure_iter )
			{
				for ( auto component_iter = components.begin ( ) ; component_iter != components.end ( ) ; ++ component_iter )
				{
					auto shift_ = shift_table [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( ( * component_iter )->get ( ) ) ] ;
					auto reduce_ = reduce_table [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( ( * component_iter )->get ( ) ) ] ;
					auto accept_ = accept_table [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( ( * component_iter )->get ( ) ) ] ;
					if ( shift_ && ( reduce_ || accept_ ) )
					{
						std::ostringstream stream ;
						stream << "shift/reduce conflict." << std::endl ;
						std::set < int > rule_nums ;
						for ( auto & elem : * closure_iter )
						{
							rule_nums.insert ( elem.second ) ;
						}
						rule_nums.insert ( reduce_ ? reduce_->get ( ) : accept_->get ( ) ) ;
						for ( auto & elem : rule_nums )
						{
							stream << "    rule:" << elem << std::endl ;
						}
						throw conflict_error { stream.str ( ) } ;
					}
					res [ closure_iter - closures.begin ( ) ] [ static_cast < int > ( ( * component_iter )->get ( ) ) ] = shift_ ? shift_ : reduce_ ? reduce_ : accept_ ;
				}
			}
			return res ;
		}
		template < typename T >
		struct get_id_type ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct get_id_type < rule_type < T , id_type , id > >
			: ftmp::integral < id_type , id >
		{
		} ;
		template < typename T >
		struct get_type ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct get_type < rule_type < T , id_type , id > >
			: ftmp::id < T >
		{
		} ;
		template < typename ... rules_type >
		class parser
		{
			using rules_type_ = typename make_rules
			<
				1 ,
				ftmp::list < > ,
				rules_type ...
			>::type ;
			using id_type = typename get_id
			<
				typename ftmp::head
				<
					typename ftmp::head
					<
						typename ftmp::head
						<
							typename to_list
							<
								typename to_rule_list < rules_type_ >::type
							>::type
						>::type
					>::type
				>::type
			>::type ;
			using type_id_map = typename ftmp::insert
			<
				typename get_id_type < end_read < void * , id_type > >::type ,
				void * ,
				typename ftmp::to_dict
				<
					typename ftmp::foldr
					<
						ftmp::eval < ftmp::cons
						<
							ftmp::eval < ftmp::list
							<
								get_id_type < ftmp::arg < 0 > > ,
								get_type < ftmp::arg < 0 > >
							> > ,
							ftmp::id < ftmp::arg < 1 > >
						> > ,
						ftmp::list < > ,
						typename ftmp::foldr
						<
							ftmp::eval < ftmp::unique
							<
								ftmp::append < ftmp::arg < 0 > , ftmp::arg < 1 > >
							> > ,
							ftmp::list < > ,
							typename ftmp::map
							<
								ftmp::eval < ftmp::cons
								<
									ftmp::at < ftmp::arg < 0 > , ftmp::integral < int , 0 > > ,
									ftmp::at < ftmp::arg < 0 > , ftmp::integral < int , 1 > >
								> > ,
								typename ftmp::map
								<
									ftmp::head < ftmp::arg < 0 > > ,
									typename to_list
									<
										typename to_rule_list < rules_type_ >::type
									>::type
								>::type
							>::type
						>::type
					>::type
				>::type
			>::type ;
			std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > table_ = [ ] ( ) -> std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > >
			{
				const auto LR0s = make_LR0
				<
					typename to_rule_list < rules_type_ >::type
				> ( ) ;
				using id_type_ = typename decltype ( LR0s )::value_type::first_type::first_type::element_type::type ;
				std::set < std::shared_ptr < term < id_type_ > > > pre_components ;
				for ( auto & elem : LR0s )
				{
					if ( ! elem.first.first->is_current_read ( ) )
					{
						pre_components.insert ( elem.first.first ) ;
					}
					for ( auto & elm : elem.first.second )
					{
						if ( ! elm->is_current_read ( ) )
						{
							pre_components.insert ( elm ) ;
						}
					}
				}
				std::vector < std::shared_ptr < term < id_type_ > > > components ( pre_components.begin ( ) , pre_components.end ( ) ) ;
				components.push_back ( get_detail_terminal < id_type_ , id_type_::parser_combinator_parser_decl_rule_ids_end > ( ) ) ;
				auto closures = make_closures ( LR0s ) ;
				return make_table ( closures , components , LR0s ) ;
			} ( ) ;
			rules_type_ rules_ ;
			std::stack < std::tuple < int , std::shared_ptr < term < id_type > > , boost::any > > stack_ { { std::make_tuple ( 0 , nullptr , boost::any { } ) } } ;
			int state_ { 0 } ;
		public :
			parser ( ) = delete ;
			parser ( const parser & ) = delete ;
			parser ( parser && ) = default ;
			auto operator = ( const parser & ) -> parser & = delete ;
			auto operator = ( parser && ) -> parser & = default ;
			~ parser ( ) = default ;
			parser ( const rules_type & ... rules ) ;
			template < typename id_type_ , id_type_ id >
			auto operator ( ) ( const typename ftmp::lookup < ftmp::integral < id_type_ , id > , type_id_map >::type & value , ftmp::integral < id_type_ , id > id_ ) -> parser & ;
			auto end ( ) -> parser & ;
		} ;
		template < typename head_type , typename ... tail_type >
		struct assign_to_function < ftmp::list < head_type , ftmp::list < tail_type ... > > >
		{
			using type = std::function < typename get_value_type < head_type >::type ( const typename get_value_type < tail_type >::type & ... ) > ;
			static type value ;
		} ;
		template < typename head_type , typename ... tail_type >
		typename assign_to_function < ftmp::list < head_type , ftmp::list < tail_type ... > > >::type assign_to_function < ftmp::list < head_type , ftmp::list < tail_type ... > > >::value = [ ] ( const typename get_value_type < tail_type >::type & ... ) { return typename get_value_type < head_type >::type { } ; } ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct get_value_type < rule_type < T , id_type , id > >
		{
			using type = T ;
		} ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct get_id < rule_type < T , id_type , id > >
		{
			using type = id_type ;
			static constexpr id_type value = id ;
		} ;
		template < typename T >
		struct rule_to_list ;
		template < template < typename T , typename id_type , id_type id > class rule_type , typename T , typename id_type , id_type id >
		struct rule_to_list < rule_type < T , id_type , id > >
			: ftmp::list < rule_type < T , id_type , id > >
		{
		} ;
		template < typename lhs_type , typename rhs_type >
		struct rule_to_list < shift_result < lhs_type , rhs_type > >
			: shift_result < lhs_type , rhs_type >
		{
		} ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct assign_result < lhs_type , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		struct assign_result < terminal < T , id_type , id > , rhs_type > ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id , typename rhs_type >
		struct assign_result < rule_type < T , id_type , id > , rhs_type >
		{
			using type = ftmp::list < rule_type < T , id_type , id > , typename rule_to_list < rhs_type >::type > ;
			using function_type = typename assign_to_function < type >::type ;
			function_type value { assign_to_function < type >::value } ;
			assign_result ( ) = default ;
			assign_result ( const assign_result & ) = default ;
			assign_result ( assign_result && ) = default ;
			auto operator = ( const assign_result & ) -> assign_result & = default ;
			auto operator = ( assign_result && ) -> assign_result & = default ;
			~ assign_result ( ) = default ;
			auto operator ( ) ( const function_type & function ) -> assign_result & ;
		} ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id , typename rhs_type >
		auto assign_result < rule_type < T , id_type , id > , rhs_type >::operator ( ) ( const function_type & function ) -> assign_result &
		{
			value = function ;
			return * this ;
		}
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_type >
		struct shift_result < assign_result < lhs_lhs_type , lhs_rhs_type > , rhs_type > ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < lhs_type , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < assign_result < lhs_lhs_type , lhs_rhs_type > , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < lhs_type , shift_result < rhs_lhs_type , rhs_rhs_type > >
			: ftmp::cons < lhs_type , typename shift_result < rhs_lhs_type , rhs_rhs_type >::type >
		{
		} ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_type >
		struct shift_result < shift_result < lhs_lhs_type , lhs_rhs_type > , rhs_type >
			: ftmp::append < typename shift_result < lhs_lhs_type , lhs_rhs_type >::type , ftmp::list < rhs_type > >
		{
		} ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < shift_result < lhs_lhs_type , lhs_rhs_type > , shift_result < rhs_lhs_type , rhs_rhs_type > >
			: ftmp::append < typename shift_result < lhs_lhs_type , lhs_rhs_type >::type , typename shift_result < rhs_lhs_type , rhs_rhs_type >::type >
		{
		} ;
		template < typename lhs_type , typename rhs_type >
		struct shift_result
			: ftmp::list < lhs_type , rhs_type >
		{
		} ;
		struct dummy_type { } ;
		template < typename lhs_type , typename rhs_type >
		auto operator >> ( const lhs_type & , const rhs_type & ) -> shift_result < lhs_type , rhs_type >
		{
			return shift_result < lhs_type , rhs_type > { } ;
		}
		template < typename T , typename id_type , id_type id >
		template < typename rhs_type >
		auto top_rule < T , id_type , id >::operator = ( const rhs_type & ) -> assign_result < top_rule , rhs_type >
		{
			return assign_result < top_rule , rhs_type > { } ;
		} ;
		template < typename T , typename id_type , id_type id >
		template < typename rhs_type >
		auto rule < T , id_type , id >::operator = ( const rhs_type & ) -> assign_result < rule , rhs_type >
		{
			return assign_result < rule , rhs_type > { } ;
		} ;
		class parse_error
			: public std::runtime_error
		{
		public :
			using std::runtime_error::runtime_error ;
		} ;
		template < int ... N >
		struct index_tuple ;
		template < int N1 , typename it >
		struct make_index_tuple_helper ;
		template < int N1 , int ... Ns >
		struct make_index_tuple_helper < N1 , index_tuple < Ns ... > >
		{
			using type = index_tuple < N1 , Ns ... > ;
		} ;
		template < int N1 , int N2 >
		struct make_index_tuple
			: make_index_tuple_helper < N1 , typename make_index_tuple < N1 + 1 , N2 >::type >
		{
		} ;
		template < int N1 >
		struct make_index_tuple < N1 , N1 >
		{
			using type = index_tuple < > ;
		} ;
		template < typename it , typename tuple >
		struct tuple_tail_impl ;
		template < int ... N , typename T1 , typename ... T >
		struct tuple_tail_impl < index_tuple < N ... > , std::tuple < T1 , T ... > >
		{
			static auto func ( const std::tuple < T1 , T ... > & tuple ) -> std::tuple < T ... >
			{
				return std::tie ( std::get < N > ( tuple ) ... ) ;
			}
		} ;
		template < typename T1 , typename ... T >
		auto tuple_tail ( const std::tuple < T1 , T ... > & tuple ) -> std::tuple < T ... >
		{
			return tuple_tail_impl < typename make_index_tuple < 1 , sizeof ... ( T ) + 1 >::type , std::tuple < T1 , T ... > >::func ( tuple ) ;
		}
		template < typename it , typename F , typename ... T >
		struct tuple_apply_helper ;
		template < int ... N , typename R , typename T1 , typename ... T , typename T1_ , typename ... T_ >
		struct tuple_apply_helper < index_tuple < N ... > , std::function < R ( T1 , T ... ) > , T1_ , T_ ... >
		{
			static auto func ( std::function < R ( T1 , T ... ) > fun , const T1_ & t1 , const std::tuple < T_ ... > & t ) -> R
			{
				return fun ( t1 , std::get < N > ( t ) ... ) ;
			}
		} ;
		template < typename R , typename T1 , typename ... T , typename T1_ , typename ... T_ >
		auto tuple_apply ( std::function < R ( T1 , T ... ) > fun , const T1_ & t1 , const std::tuple < T_ ... > & t ) -> R
		{
			return tuple_apply_helper < typename make_index_tuple < 0 , sizeof ... ( T_ ) >::type , std::function < R ( T1 , T ... ) > , T1_ , T_ ... >::func ( fun , t1 , t ) ;
		}
		template < typename id_type , typename R , typename T1 , typename ... T >
		struct apply_impl ;
		template < typename id_type , typename R , typename T1 , typename ... T >
		struct apply_impl
		{
			static auto func ( std::function < R ( T1 , T ... ) > fun , std::stack < std::tuple < int , std::shared_ptr < term < id_type > > , boost::any > > & stack ) -> R
			{
				auto new_fun = [ & ] ( const T & ... t )
				{
					auto ts = std::tie ( t ... ) ;
					return [ & , ts ] ( const T1 & t1 )
					{
						return tuple_apply ( fun , t1 , ts ) ;
					} ;
				} ;
				auto f = apply_impl < id_type , std::function < R ( T1 ) > , T ... >::func ( new_fun , stack ) ;
				auto res = f ( boost::any_cast < T1 > ( std::get < 2 > ( stack.top ( ) ) ) ) ;
				stack.pop ( ) ;
				return res ;
			}
		} ;
		template < typename id_type , typename R , typename T >
		struct apply_impl < id_type , R , T >
		{
			static auto func ( std::function < R ( T ) > fun , std::stack < std::tuple < int , std::shared_ptr < term < id_type > > , boost::any > > & stack ) -> R
			{
				auto res = fun ( boost::any_cast < T > ( std::get < 2 > ( stack.top ( ) ) ) ) ;
				stack.pop ( ) ;
				return res ;
			}
		} ;
		template < typename id_type , typename R , typename ... T >
		auto apply ( std::function < R ( T ... ) > fun , std::stack < std::tuple < int , std::shared_ptr < term < id_type > > , boost::any > > & stack ) -> R
		{
			return apply_impl < id_type , R , T ... >::func ( fun , stack ) ;
		}
		template < typename id_type , typename rule_list >
		struct do_reduce_impl ;
		template < typename id_type , typename T , int N , typename ... rule_list >
		struct do_reduce_impl < id_type , std::tuple < first_only_tuple < T , ftmp::integral < int , N > > , rule_list ... > >
		{
			static auto func ( const std::tuple < first_only_tuple < T , ftmp::integral < int , N > > , rule_list ... > & rules , std::stack < std::tuple < int , std::shared_ptr < term < id_type > > , boost::any > > & stack , std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > & table , int n ) -> int
			{
				if ( n == N )
				{
					auto push_value = apply < id_type > ( std::get < 0 > ( std::get < 0 > ( rules ) ).value , stack ) ;
					auto state = std::get < 0 > ( stack.top ( ) ) ;
					using rule_id = typename get_id_type < typename ftmp::head < typename T::type >::type >::type ;
					auto goto_ = table [ state ] [ static_cast < int > ( rule_id::value ) ] ;
					if ( ! goto_ )
					{
						throw parse_error { "parse error" } ;
					}
					stack.push ( std::make_tuple ( goto_->get ( ) , make_LR0_heper < top_rule < void * , id_type , rule_id::value > >::func ( ) , push_value ) ) ;
					state = goto_->get ( ) ;
					return state ;
				}
				else
				{
					return do_reduce_impl < id_type , std::tuple < rule_list ... > >::func ( tuple_tail ( rules ) , stack , table , n ) ;
				}
			}
		} ;
		template < typename id_type >
		struct do_reduce_impl < id_type , std::tuple < > >
		{
			static auto func ( const std::tuple < > & , std::stack < std::tuple < int , std::shared_ptr < term < id_type > > , boost::any > > & , std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > & , int ) -> int
			{
				throw parse_error { "parse error" } ;
			}
		} ;
		template < typename id_type , typename ... T >
		auto do_reduce ( const std::tuple < T ... > & rules , std::stack < std::tuple < int , std::shared_ptr < term < id_type > > , boost::any > > & stack , std::unordered_map < int , std::unordered_map < int , std::shared_ptr < detail_action_base > > > & table , int n ) -> int
		{
			return do_reduce_impl < id_type , std::tuple < T ... > >::func ( rules , stack , table , n ) ;
		}
		template < typename ... rules_type >
		parser < rules_type ... >::parser ( const rules_type & ... rules )
			: rules_ { dummy_type { } , rules ... }
		{
		}
		template < typename ... rules_type >
		template < typename id_type_ , id_type_ id >
		auto parser < rules_type ... >::operator ( ) ( const typename ftmp::lookup < ftmp::integral < id_type_ , id > , type_id_map >::type & value , ftmp::integral < id_type_ , id > id_ ) -> parser &
		{
			auto & elm = table_ [ state_ ] [ static_cast < int > ( id ) ] ;
			if ( ! elm )
			{
				throw parse_error { "parse error" } ;
			}
			else if ( elm->is_shift ( ) )
			{
				stack_.push ( std::make_tuple ( elm->get ( ) , make_LR0_heper < top_rule < void * , id_type , id > >::func ( ) , value ) ) ;
				state_ = elm->get ( ) ;
			}
			else if ( elm->is_reduce ( ) )
			{
				state_ = do_reduce < id_type > ( rules_ , stack_ ,table_ , elm->get ( ) ) ;
				return ( * this ) ( value , id_ ) ;
			}
			return * this ;
		}
		template < typename ... rules_type >
		auto parser < rules_type ... >::end ( ) -> parser &
		{
			return ( * this ) ( nullptr , ftmp::integral < id_type , id_type::parser_combinator_parser_decl_rule_ids_end > { } ) ;
		}
		template < typename ... rules_type >
		auto make_parser ( const rules_type & ... rules ) -> parser < rules_type ... >
		{
			return parser < rules_type ... > { rules ... } ;
		}
	}
}
#endif