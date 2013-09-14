#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
#include"TMP/all.hpp"
#include"TMP/and.hpp"
#include"TMP/any.hpp"
#include"TMP/append.hpp"
#include"TMP/at.hpp"
#include"TMP/complement.hpp"
#include"TMP/composite.hpp"
#include"TMP/concat.hpp"
#include"TMP/cons.hpp"
#include"TMP/elem.hpp"
#include"TMP/empty.hpp"
#include"TMP/equal.hpp"
#include"TMP/eval_if.hpp"
#include"TMP/eval_if_c.hpp"
#include"TMP/filter.hpp"
#include"TMP/foldl.hpp"
#include"TMP/foldr.hpp"
#include"TMP/head.hpp"
#include"TMP/id.hpp"
#include"TMP/if.hpp"
#include"TMP/if_c.hpp"
#include"TMP/insert.hpp"
#include"TMP/integral.hpp"
#include"TMP/intersection.hpp"
#include"TMP/lambda.hpp"
#include"TMP/list.hpp"
#include"TMP/list_to_set.hpp"
#include"TMP/map.hpp"
#include"TMP/nand.hpp"
#include"TMP/not.hpp"
#include"TMP/or.hpp"
#include"TMP/print.hpp"
#include"TMP/set.hpp"
#include"TMP/set_to_list.hpp"
#include"TMP/size.hpp"
#include"TMP/symmetric_difference.hpp"
#include"TMP/tail.hpp"
#include"TMP/union.hpp"
#include"TMP/unique.hpp"
#include"TMP/xor.hpp"
#include"TMP/zip.hpp"
namespace parser_combinator
{
	namespace parser
	{
		struct current_read
		{
			using type = current_read ;
		} ;
		struct end_read
		{
			using type = end_read ;
		} ;
		template < typename lhs_type , typename rhs_type >
		struct assign_result ;
		template < typename lhs_type , typename rhs_type >
		struct shift_result ;
		template < typename rule_type , typename result_type , typename ... args_type >
		struct assign_to_function ;
		template < typename rule_type >
		struct get_value_type ;
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
			auto operator = ( const rhs_type & ) -> assign_result < top_rule , typename rhs_type::type > ;
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
			auto operator = ( const rhs_type & ) -> assign_result < rule , typename rhs_type::type > ;
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
		struct make_rules < index , std::tuple < type_in_tuple ... > >
		{
			using type = std::tuple < type_in_tuple ... > ;
		} ;
		template < int index , typename ... type_in_tuple , typename args_head , typename ... args_type >
		struct make_rules < index , std::tuple < type_in_tuple ... > , args_head , args_type ... >
			: make_rules < index + 1 , std::tuple < type_in_tuple ... , first_only_tuple < args_head , tmp::integral < unsigned int , index > > > , args_type ... >
		{
		} ;
		template < typename T >
		struct shift_to_list ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct shift_to_list < rule_type < T , id_type , id > >
		{
			using type = tmp::list < rule_type < T , id_type , id > > ;
		} ;
		template < typename lhs_type , typename rhs_type >
		struct shift_to_list < shift_result < lhs_type , rhs_type > >
			: tmp::concat
			<
				tmp::list
				<
					typename shift_to_list < lhs_type >::type ,
					tmp::list < rhs_type >
				>
			>
		{
		} ;
		template < typename T1 , typename T2 >
		struct list_to_LR0 ;
		template < typename ... T1 , typename T2 , typename  ... T2s >
		struct list_to_LR0 < tmp::list < T1 ... > , tmp::list < T2 , T2s ... > >
			: tmp::cons
			<
				tmp::list < T1 ... , current_read , T2 , T2s ... > ,
				typename list_to_LR0
				<
					tmp::list < T1 ... , T2 > ,
					tmp::list < T2s ... >
				>::type
			>
		{
		} ;
		template < typename ... T1 >
		struct list_to_LR0 < tmp::list < T1 ... > , tmp::list < > >
			: tmp::list < tmp::list < T1 ... , current_read > >
		{
		} ;
		template < typename T >
		struct assign_to_list ;
		template < typename lhs_type , typename rhs_type >
		struct assign_to_list < assign_result < lhs_type , rhs_type > >
			: tmp::map
			<
				tmp::list < lhs_type , tmp::arg < 0 > > ,
				typename list_to_LR0
				<
					tmp::list < > ,
					typename shift_to_list < rhs_type >::type
				>::type
			>
		{
		} ;
		template < typename T >
		struct make_LR0 ;
		template < >
		struct make_LR0 < std::tuple < > >
		{
			using type = tmp::set < > ;
		} ;
		template < typename lhs_type , typename rhs_type >
		struct make_LR0 < assign_result < lhs_type , rhs_type > >
			: tmp::list_to_set
			<
				typename assign_to_list
				<
					assign_result < lhs_type , rhs_type >
				>::type
			>
		{
		} ;
		template < typename T1 , typename T2 >
		struct make_LR0 < first_only_tuple < T1 , T2 > >
			: tmp::map
			<
				tmp::list < tmp::arg < 0 > , T2 > ,
				typename tmp::set_to_list < typename make_LR0 < T1 >::type >::type
			>
		{
		} ;
		template < typename T1 , typename ... T_ >
		struct make_LR0 < std::tuple < T1 , T_ ... > >
			: tmp::list_to_set
			<
				typename tmp::concat
				<
					tmp::list
					<
						typename make_LR0 < T1 >::type ,
						typename tmp::set_to_list
						<
							typename make_LR0 < std::tuple < T_ ... > >::type
						>::type
					>
				>::type
			>
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
		struct get_rule_head
			: tmp::at
			<
				typename tmp::at < T , tmp::integral < unsigned int , 0 > >::type ,
				tmp::integral < unsigned int , 0 >
			>
		{
		} ;
		template < typename T >
		struct eval_is_top_rule
			: is_top_rule < typename get_rule_head < T >::type >
		{
		} ;
		template < typename T >
		struct is_not_terminal ;
		template < typename T , typename id_type , id_type id >
		struct is_not_terminal < top_rule < T , id_type , id > >
			: tmp::integral < bool , true >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_not_terminal < rule < T , id_type , id > >
			: tmp::integral < bool , true >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_not_terminal < terminal < T , id_type , id > >
			: tmp::integral < bool , false >
		{
		} ;
		template < typename T , typename set >
		struct eval_elem
			: tmp::elem
			<
				typename T::type ,
				typename set::type
			>
		{
		} ;
		template < typename T >
		struct get_rule_body
			: tmp::at
			<
				typename tmp::at < T , tmp::integral < unsigned int , 0 > >::type ,
				tmp::integral < unsigned int , 1 >
			>
		{
		} ;
		template < typename T , int N >
		struct at_rule_body
			: tmp::at
			<
				typename get_rule_body < T >::type ,
				tmp::integral < unsigned int , N >
			>
		{
		} ;
		template < typename LR0s >
		struct get_top_rules_helper
			: tmp::filter
			<
				eval_is_top_rule < tmp::arg < 0 > > ,
				LR0s
			>
		{
		} ;
		template < typename T >
		struct is_non_read
			: tmp::equal < typename at_rule_body < T , 0 >::type , current_read >
		{
		} ;
		template < typename LR0s >
		struct get_top_rules
			: tmp::list_to_set
			<
				typename tmp::filter
				<
					is_non_read < tmp::arg < 0 > > ,
					typename get_top_rules_helper
					<
						typename tmp::set_to_list < LR0s >::type
					>::type
				>::type
			>
		{
		} ;
		template < typename T >
		struct get_next_read_helper ;
		template < typename ... Ts >
		struct get_next_read_helper < tmp::list < Ts ... > >
			: get_next_read_helper < typename tmp::tail < tmp::list < Ts ... > >::type >
		{
		} ;
		template < typename ... Ts >
		struct get_next_read_helper < tmp::list < current_read , Ts ... > >
			: tmp::head < tmp::list < Ts ... > >
		{
		} ;
		template < typename T >
		struct get_next_read
			: get_next_read_helper < typename get_rule_body < T >::type >
		{
		} ;
		template < typename T , typename seq >
		struct not_elem
			: tmp::not_
			<
				tmp::elem
				<
					T ,
					seq
				>
			>
		{
		} ;
		template < typename set , typename I , typename env >
		struct new_LR0s
			: tmp::filter
			<
				eval_elem
				<
					get_rule_head < tmp::arg < 0 > > ,
					typename tmp::map
					<
						get_next_read < tmp::arg < 0 > > ,
						typename tmp::filter
						<
							not_elem < tmp::arg < 0 > , set > ,
							I
						>::type
					>::type
				> ,
				typename tmp::filter
				<
					is_non_read < tmp::arg < 0 > > ,
					env
				>::type
			>
		{
		} ;
		template < typename set , typename I , typename env >
		struct make_closure_helper
			: tmp::eval_if
			<
				tmp::equal
				<
					typename tmp::list_to_set < set >::type ,
					typename tmp::union_
					<
						typename tmp::list_to_set < set >::type ,
						typename tmp::list_to_set < I >::type
					>::type
				> ,
				tmp::list_to_set < set > ,
				make_closure_helper
				<
					typename tmp::set_to_list
					<
						typename tmp::union_
						<
							typename tmp::list_to_set < set >::type ,
							typename tmp::list_to_set < I >::type
						>::type
					>::type ,
					typename new_LR0s
					<
						set ,
						I ,
						env
					>::type ,
					env
				>
			>
		{
		} ;
		template < typename I , typename env >
		struct make_closure
			: make_closure_helper
			<
				tmp::list < > ,
				typename tmp::set_to_list < I >::type ,
				typename tmp::set_to_list < env >::type
			>
		{
		} ;
		template < typename ... rules_type >
		class parser
		{
			using rules_type_ = typename make_rules
			<
				0 ,
				std::tuple < > ,
				rules_type ...
			>::type ;
			using LRs = typename make_LR0
			<
				rules_type_
			>::type ;
			using top_rules = typename get_top_rules < LRs >::type ;
			using closures = typename make_closure
			<
				top_rules ,
				LRs
			>::type ;
			rules_type_ rules_ ;
			typename tmp::print < closures >::type value ;
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
		template < typename rule_type , typename result_type , typename ... args_type >
		struct assign_to_function
		{
			using type = std::function < result_type ( const typename get_value_type < rule_type >::type & , const args_type & ... ) > ;
		} ;
		template < typename lhs_type , typename rhs_type , typename result_type , typename ... args_type >
		struct assign_to_function < shift_result < lhs_type , rhs_type > , result_type , args_type ... >
			: assign_to_function < lhs_type , result_type , typename get_value_type < rhs_type >::type , args_type ... >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct get_value_type < top_rule < T , id_type , id > >
		{
			using type = T ;
		} ;
		template < typename T , typename id_type , id_type id >
		struct get_value_type < rule < T , id_type , id > >
		{
			using type = T ;
		} ;
		template < typename T , typename id_type , id_type id >
		struct get_value_type < terminal < T , id_type , id > >
		{
			using type = T ;
		} ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct assign_result < lhs_type , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		struct assign_result < top_rule < T , id_type , id > , rhs_type >
		{
			using type = assign_result ;
			typename assign_to_function < rhs_type , T >::type value { } ;
		} ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		struct assign_result < rule < T , id_type , id > , rhs_type >
		{
			using type = assign_result ;
			typename assign_to_function < rhs_type , T >::type value { } ;
		} ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_type >
		struct shift_result < assign_result < lhs_lhs_type , lhs_rhs_type > , rhs_type > ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < lhs_type , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < assign_result < lhs_lhs_type , lhs_rhs_type > , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename lhs_type , typename rhs_type >
		struct shift_result
		{
			using type = shift_result ;
		} ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct shift_result < lhs_type , shift_result < rhs_lhs_type , rhs_rhs_type > >
			: shift_result < typename shift_result < lhs_type , rhs_lhs_type >::type , typename rhs_rhs_type::type >
		{
		} ;
		template < typename lhs_type , typename rhs_type >
		auto operator >> ( const lhs_type & , const rhs_type & ) -> typename shift_result < typename lhs_type::type , typename rhs_type::type >::type
		{
			return typename shift_result < typename lhs_type::type , typename rhs_type::type >::type { } ;
		}
		template < typename T , typename id_type , id_type id >
		template < typename rhs_type >
		auto top_rule < T , id_type , id >::operator = ( const rhs_type & ) -> assign_result < top_rule , typename rhs_type::type >
		{
			return assign_result < top_rule , typename rhs_type::type > { } ;
		} ;
		template < typename T , typename id_type , id_type id >
		template < typename rhs_type >
		auto rule < T , id_type , id >::operator = ( const rhs_type & ) -> assign_result < rule , typename rhs_type::type >
		{
			return assign_result < rule , typename rhs_type::type > { } ;
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