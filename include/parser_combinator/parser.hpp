#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
#include<functional>
#include<tuple>
#include<memory>
#include<list>
#include"TMP/all.hpp"
#include"TMP/and.hpp"
#include"TMP/any.hpp"
#include"TMP/append.hpp"
#include"TMP/at.hpp"
#include"TMP/complement.hpp"
#include"TMP/composite.hpp"
#include"TMP/concat.hpp"
#include"TMP/cons.hpp"
#include"TMP/delete.hpp"
#include"TMP/dict.hpp"
#include"TMP/elem.hpp"
#include"TMP/empty.hpp"
#include"TMP/equal.hpp"
#include"TMP/eval.hpp"
#include"TMP/eval_if.hpp"
#include"TMP/eval_if_c.hpp"
#include"TMP/filter.hpp"
#include"TMP/find.hpp"
#include"TMP/foldl.hpp"
#include"TMP/foldr.hpp"
#include"TMP/head.hpp"
#include"TMP/id.hpp"
#include"TMP/if.hpp"
#include"TMP/if_c.hpp"
#include"TMP/init.hpp"
#include"TMP/insert.hpp"
#include"TMP/insert_dict.hpp"
#include"TMP/integral.hpp"
#include"TMP/intersection.hpp"
#include"TMP/lambda.hpp"
#include"TMP/last.hpp"
#include"TMP/list.hpp"
#include"TMP/lookup.hpp"
#include"TMP/map.hpp"
#include"TMP/nand.hpp"
#include"TMP/not.hpp"
#include"TMP/or.hpp"
#include"TMP/print.hpp"
#include"TMP/set.hpp"
#include"TMP/size.hpp"
#include"TMP/symmetric_difference.hpp"
#include"TMP/tail.hpp"
#include"TMP/to_dict.hpp"
#include"TMP/to_list.hpp"
#include"TMP/to_set.hpp"
#include"TMP/typed_map.hpp"
#include"TMP/union.hpp"
#include"TMP/unique.hpp"
#include"TMP/xor.hpp"
#include"TMP/zip.hpp"
#define DECL_RULE_IDS_BEGIN(name) \
	enum class name \
	{ \
		parser_combinator_parser_decl_rule_ids_begin ,
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
			current_read ( ) ;
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
		template < typename id_type >
		current_read < id_type >::current_read ( )
			: term < id_type > ( static_cast < id_type > ( - 1 ) )
		{
		}
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
		} ;
		template < typename first_type , typename second_type >
		first_only_tuple < first_type , second_type >::first_only_tuple ( const first_type & first )
			: std::tuple < first_type , second_type > { first , second_type { } }
		{
		}
		template < int index , typename type_tuple , typename ... args_type >
		struct make_rules ;
		template < int index , typename ... type_in_tuple >
		struct make_rules < index , tmp::list < type_in_tuple ... > >
		{
			using type = std::tuple < type_in_tuple ... > ;
		} ;
		template < int index , typename ... type_in_tuple , typename args_head , typename ... args_type >
		struct make_rules < index , tmp::list < type_in_tuple ... > , args_head , args_type ... >
			: make_rules < index + 1 , tmp::list < type_in_tuple ... , first_only_tuple < args_head , tmp::integral < int , index > > > , args_type ... >
		{
		} ;
		template < typename T >
		struct to_rule_list ;
		template < typename ... list >
		struct to_rule_list < std::tuple < list ... > >
			: tmp::list < typename to_rule_list < list >::type ... >
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
		struct to_list < tmp::list < list ... > >
			: tmp::list < typename to_list < list >::type ... >
		{
		} ;
		template < typename T1 , typename T2 >
		struct to_list < first_only_tuple < T1 , T2 > >
			: tmp::list < typename to_list < T1 >::type, T2 >
		{
		} ;
		template < typename T1 , typename T2 >
		struct to_list < assign_result < T1 , T2 > >
			: tmp::list < T1 , typename T2::type >
		{
		} ;
		template < typename T >
		struct is_top_rule
			: tmp::integral < bool , false >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_top_rule < top_rule < T , id_type , id > >
			: tmp::integral < bool , true >
		{
		} ;
		template < typename T >
		struct get_top_rules
			: tmp::filter
			<
				is_top_rule < tmp::arg < 0 > > ,
				typename tmp::map
				<
					tmp::eval < tmp::at
					<
						tmp::at < tmp::arg < 0 > , tmp::integral < int , 0 > > ,
						tmp::integral < int , 0 >
					> > ,
					typename tmp::to_set < typename to_list < T >::type >::type
				>::type
			>
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
			using head_type = typename tmp::at < typename assign_result < T1 , T2 >::type , tmp::integral < int , 0 > >::type ;
			using body_type = typename tmp::at < typename assign_result < T1 , T2 >::type , tmp::integral < int , 1 > >::type ;
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
		struct make_LR0_heper < tmp::list < T ... > >
		{
			static auto func ( ) -> std::list < typename tmp::head < tmp::list < decltype ( make_LR0_heper < T >::func ( ) ) ... > >::type >
			{
				return std::list < typename tmp::head < tmp::list < decltype ( make_LR0_heper < T >::func ( ) ) ... > >::type > { make_LR0_heper < T >::func ( ) ... } ;
			}
		} ;
		template < typename T >
		auto make_LR0 ( ) -> decltype ( make_LR0_heper < T >::func ( ) )
		{
			static_assert ( tmp::size < typename get_top_rules < T >::type >::value == 1 , "top_rule is duplication." ) ;
			using id_type = get_id
			<
				typename tmp::head
				<
					typename tmp::to_list
					<
						typename get_top_rules < T >::type
					>::type
				>::type
			> ;
			auto tmp_res = make_LR0_heper < T >::func ( ) ;
			tmp_res.emplace_front
			(
				std::make_pair
				(
					get_detail_top_rule < typename id_type::type , id_type::type::parser_combinator_parser_decl_rule_ids_begin > ( ) ,
					std::list < std::shared_ptr < term < typename id_type::type > > >
					{
						get_detail_rule < typename id_type::type , id_type::value > ( )
					}
				) ,
				0
			) ;
			decltype ( tmp_res ) res ;
			for ( auto & elem : tmp_res )
			{
				auto index = elem.second ;
				auto head = elem.first.first ;
				for ( auto iter = elem.first.second.begin ( ) ; iter != elem.first.second.end ( ) ; ++ iter )
				{
					auto pos = elem.first.second.insert ( iter , get_current_read < typename id_type::type > ( ) ) ;
					res.emplace_back ( std::make_pair ( head , elem.first.second ) , index ) ;
					elem.first.second.erase ( pos ) ;
				}
				elem.first.second.insert ( elem.first.second.end ( ) , get_current_read < typename id_type::type > ( ) ) ;
				res.emplace_back ( std::make_pair ( head , elem.first.second ) , index ) ;
			}
			return res ;
		}
		template < typename ... rules_type >
		class parser
		{
			using rules_type_ = typename make_rules
			<
				1 ,
				tmp::list < > ,
				rules_type ...
			>::type ;
			std::function < void ( ) > fun = [ ] ( )
			{
				auto value = make_LR0
				<
					typename to_rule_list < rules_type_ >::type
				> ( ) ;
			} ;
			rules_type_ rules_ ;
		public :
			parser ( ) = delete ;
			parser ( const parser & ) = delete ;
			parser ( parser && ) = default ;
			auto operator = ( const parser & ) -> parser & = delete ;
			auto operator = ( parser && ) -> parser & = default ;
			~ parser ( ) = default ;
			parser ( const rules_type & ... rules ) ;
			template < typename T , typename id_type >
			auto operator ( ) ( const T & value , id_type id ) -> parser & ;
		} ;
		template < typename head_type , typename ... tail_type >
		struct assign_to_function < tmp::list < head_type , tmp::list < tail_type ... > > >
		{
			using type = std::function < typename get_value_type < head_type >::type ( const typename get_value_type < tail_type >::type & ... ) > ;
			static type value ;
		} ;
		template < typename head_type , typename ... tail_type >
		typename assign_to_function < tmp::list < head_type , tmp::list < tail_type ... > > >::type assign_to_function < tmp::list < head_type , tmp::list < tail_type ... > > >::value = [ ] ( const typename get_value_type < tail_type >::type & ... ) { return typename get_value_type < head_type >::type { } ; } ;
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
			: tmp::list < rule_type < T , id_type , id > >
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
			using type = tmp::list < rule_type < T , id_type , id > , typename rule_to_list < rhs_type >::type > ;
			using function_type = typename assign_to_function < type >::type ;
			function_type value { assign_to_function < type >::value } ;
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
			: tmp::cons < lhs_type , typename shift_result < rhs_lhs_type , rhs_rhs_type >::type >
		{
		} ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_type >
		struct shift_result < shift_result < lhs_lhs_type , lhs_rhs_type > , rhs_type >
			: tmp::append < typename shift_result < lhs_lhs_type , lhs_rhs_type >::type , tmp::list < rhs_type > >
		{
		} ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < shift_result < lhs_lhs_type , lhs_rhs_type > , shift_result < rhs_lhs_type , rhs_rhs_type > >
			: tmp::append < typename shift_result < lhs_lhs_type , lhs_rhs_type >::type , typename shift_result < rhs_lhs_type , rhs_rhs_type >::type >
		{
		} ;
		template < typename lhs_type , typename rhs_type >
		struct shift_result
			: tmp::list < lhs_type , rhs_type >
		{
		} ;
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
		template < typename ... rules_type >
		parser < rules_type ... >::parser ( const rules_type & ... rules )
			: rules_ { rules ... }
		{
		}
		template < typename ... rules_type >
		template < typename T , typename id_type >
		auto parser < rules_type ... >::operator ( ) ( const T & value , id_type id ) -> parser &
		{
			return * this ;
		}
		template < typename ... rules_type >
		auto make_parser ( const rules_type & ... rules ) -> parser < rules_type ... >
		{
			return parser < rules_type ... > { rules ... } ;
		}
	}
}
#endif