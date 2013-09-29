#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
#include<functional>
#include<tuple>
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
namespace parser_combinator
{
	namespace parser
	{
		namespace detail
		{
			enum class internal_id_type
			{
				internal_id
			} ;
		}
		struct current_read
		{
			using type = current_read ;
		} ;
		struct end_read
		{
			using type = end_read ;
		} ;
		template < typename tuple >
		struct tuple_to_list ;
		template < typename list >
		struct to_tuple ;
		template < typename ... tuple >
		struct tuple_to_list < std::tuple < tuple ... > >
		{
			using type = tmp::list < tuple ... > ;
		} ;
		template < typename ... list >
		struct to_tuple < tmp::list < list ... > >
		{
			using type = std::tuple < list ... > ;
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
		struct to_LR0 ;
		template < typename ... T1 , typename T2 , typename  ... T2s >
		struct to_LR0 < tmp::list < T1 ... > , tmp::list < T2 , T2s ... > >
			: tmp::cons
			<
				tmp::list < T1 ... , current_read , T2 , T2s ... > ,
				typename to_LR0
				<
					tmp::list < T1 ... , T2 > ,
					tmp::list < T2s ... >
				>::type
			>
		{
		} ;
		template < typename ... T1 >
		struct to_LR0 < tmp::list < T1 ... > , tmp::list < > >
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
				typename to_LR0
				<
					tmp::list < > ,
					typename shift_to_list < rhs_type >::type
				>::type
			>
		{
		} ;
		template < typename T >
		struct make_LR0 ;
		template < typename T >
		struct make_LR0_helper ;
		template < >
		struct make_LR0_helper < std::tuple < > >
		{
			using type = tmp::set < > ;
		} ;
		template < typename lhs_type , typename rhs_type >
		struct make_LR0_helper < assign_result < lhs_type , rhs_type > >
			: tmp::to_set
			<
				typename assign_to_list
				<
					assign_result < lhs_type , rhs_type >
				>::type
			>
		{
		} ;
		template < typename T1 , typename T2 >
		struct make_LR0_helper < first_only_tuple < T1 , T2 > >
			: tmp::map
			<
				tmp::list < tmp::arg < 0 > , T2 > ,
				typename tmp::to_list < typename make_LR0_helper < T1 >::type >::type
			>
		{
		} ;
		template < typename T1 , typename ... T_ >
		struct make_LR0_helper < std::tuple < T1 , T_ ... > >
			: tmp::to_set
			<
				typename tmp::concat
				<
					tmp::list
					<
						typename make_LR0_helper < T1 >::type ,
						typename tmp::to_list
						<
							typename make_LR0_helper < std::tuple < T_ ... > >::type
						>::type
					>
				>::type
			>
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
		struct is_top_rule
			: tmp::integral < bool , false >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_top_rule < top_rule < T , id_type , id > >
			: tmp::integral < bool , true >
		{
		} ;
		template < typename LR0s >
		struct get_top_rules_helper
			: tmp::filter
			<
				tmp::eval < is_top_rule < get_rule_head < tmp::arg < 0 > > > > ,
				LR0s
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
		template < typename T >
		struct is_non_read
			: tmp::equal < typename at_rule_body < T , 0 >::type , current_read >
		{
		} ;
		template < typename LR0s >
		struct get_top_rules
			: tmp::to_set
			<
				typename tmp::filter
				<
					is_non_read < tmp::arg < 0 > > ,
					typename get_top_rules_helper
					<
						typename tmp::to_list < LR0s >::type
					>::type
				>::type
			>
		{
		} ;
		template < typename T >
		struct get_top_rule
			: tmp::head
			<
				typename tmp::map
				<
					get_rule_head < tmp::arg < 0 > > ,
					typename tmp::to_list
					<
						typename get_top_rules
						<
							typename make_LR0_helper < T >::type
						>::type
					>::type
				>::type
			>
		{
			static_assert
			(
				tmp::size <
					typename tmp::unique
					<
						typename tmp::map
						<
							get_rule_head < tmp::arg < 0 > > ,
							typename tmp::to_list
							<
								typename get_top_rules
								<
									typename make_LR0_helper < T >::type
								>::type
							>::type
						>::type
					>::type
				>::type::value == 1 ,
				""
			) ;
		} ;
		template < typename rule >
		struct rule_normalize ;
		template < typename rule >
		struct rule_normalize_element ;
		template < typename rule , typename index >
		struct rule_normalize < tmp::list < rule , index > >
			: tmp::list
			<
				tmp::list
				<
					typename rule_normalize_element
					<
						typename get_rule_head
						<
							tmp::list < rule , index >
						>::type
					>::type ,
					typename tmp::map
					<
						rule_normalize_element < tmp::arg < 0 > > ,
						typename get_rule_body
						<
							tmp::list < rule , index >
						>::type
					>::type
				> ,
				index
			>
		{
		} ;
		template < typename T >
		struct rule_normalize_element
		{
			using type = T ;
		} ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct rule_normalize_element < rule_type < T , id_type , id > >
			: rule < T , id_type , id >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct rule_normalize_element < terminal < T , id_type , id > >
			: terminal < T , id_type , id >
		{
		} ;
		template < typename T >
		struct make_LR0
			: tmp::to_set
			<
				typename tmp::concat
				<
					tmp::list
					<
						typename tmp::map
						<
							tmp::list
							<
								tmp::arg < 0 > ,
								tmp::integral < int , 0 >
							> ,
							typename assign_to_list
							<
								assign_result
								<
									top_rule
									<
										typename get_value_type
										<
											typename get_top_rule < T >::type
										>::type ,
										detail::internal_id_type ,
										detail::internal_id_type::internal_id
									> ,
									typename rule_normalize_element
									<
										typename get_top_rule < T >::type
									>::type
								>
							>::type
						>::type ,
						typename tmp::map
						<
							rule_normalize < tmp::arg < 0 > > ,
							typename tmp::to_list
							<
								typename make_LR0_helper < T >::type
							>::type
						>::type
					>
				>::type
			>
		{
		} ;
		template < typename T >
		struct is_not_terminal ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct is_not_terminal < rule_type < T , id_type , id > >
			: tmp::integral < bool , true >
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_not_terminal < terminal < T , id_type , id > >
			: tmp::integral < bool , false >
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
		template < typename T >
		struct is_read_end
			: tmp::equal
			<
				current_read ,
				typename tmp::last < typename get_rule_body < T >::type >::type
			>
		{
		} ;
		template < typename set , typename I , typename env >
		struct new_LR0s
			: tmp::filter
			<
				tmp::eval
				<
					tmp::elem
					<
						get_rule_head < tmp::arg < 0 > > ,
						typename tmp::map
						<
							get_next_read < tmp::arg < 0 > > ,
							typename tmp::filter
							<
								tmp::not_ < is_read_end < tmp::arg < 0 > > > ,
								typename tmp::filter
								<
									not_elem < tmp::arg < 0 > , set > ,
									I
								>::type
							>::type
						>::type
					>
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
					typename tmp::to_set < set >::type ,
					typename tmp::union_
					<
						typename tmp::to_set < set >::type ,
						typename tmp::to_set < I >::type
					>::type
				> ,
				tmp::to_set < set > ,
				make_closure_helper
				<
					typename tmp::to_list
					<
						typename tmp::union_
						<
							typename tmp::to_set < set >::type ,
							typename tmp::to_set < I >::type
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
				typename tmp::to_list < I >::type ,
				typename tmp::to_list < env >::type
			>
		{
		} ;
		template < typename T >
		struct promote_reading ;
		template < typename T >
		struct promote_reading_helper ;
		template < typename T >
		struct promote_reading
			: tmp::list
			<
				tmp::list
				<
					typename get_rule_head < T >::type ,
					typename promote_reading_helper
					<
						typename get_rule_body < T >::type
					>::type
				> ,
				typename tmp::at < T , tmp::integral < int , 1 > >::type
			>
		{
		} ;
		template < typename T >
		struct promote_reading_helper
			: tmp::cons
			<
				typename tmp::head < T >::type ,
				typename promote_reading_helper
				<
					typename tmp::tail < T >::type
				>::type
			>
		{
		} ;
		template < typename T , typename ... T_ >
		struct promote_reading_helper < tmp::list < current_read , T , T_ ... > >
			: tmp::list < T , current_read , T_ ... >
		{
		} ;
		template < typename I , typename X , typename env >
		struct make_goto
			: make_closure
			<
				typename tmp::map
				<
					promote_reading < tmp::arg < 0 > > ,
					typename tmp::filter
					<
						tmp::eval < tmp::equal < get_next_read < tmp::arg < 0 > > , tmp::id < X > > > ,
						typename tmp::filter
						<
							tmp::not_ < is_read_end < tmp::arg < 0 > > > ,
							I
						>::type
					>::type
				>::type ,
				env
			>
		{
		} ;
		template < typename Is , typename env >
		struct make_closures ;
		template < typename I , typename env >
		struct make_closures_helper
			: tmp::map
			<
				make_goto < I , tmp::arg < 0 > , env > ,
				typename tmp::map
				<
					get_next_read < tmp::arg < 0 > > ,
					typename tmp::filter
					<
						tmp::not_ < is_read_end < tmp::arg < 0 > > > ,
						typename tmp::to_list < I >::type
					>::type
				>::type
			>
		{
		} ;
		template < typename Is , typename env >
		struct new_Is
			: tmp::union_
			<
				typename tmp::to_set
				<
					typename tmp::concat
					<
						typename tmp::map
						<
							make_closures_helper < tmp::arg < 0 > , env > ,
							typename tmp::to_list < Is >::type
						>::type
					>::type
				>::type ,
				Is
			>
		{
		} ;
		template < typename Is , typename env >
		struct make_closures
			: tmp::eval_if
			<
				tmp::equal
				<
					typename new_Is < Is , env >::type ,
					Is
				> ,
				tmp::id < Is > ,
				make_closures
				<
					typename new_Is < Is , env >::type ,
					env
				>
			>
		{
		} ;
		template < typename rule >
		struct remove_current_read_helper
			: tmp::filter
			<
				tmp::not_ < tmp::equal < tmp::arg < 0 > , current_read > > ,
				typename get_rule_body < rule >::type
			>
		{
		} ;
		template < typename rule >
		struct remove_current_read
			: tmp::list
			<
				tmp::list
				<
					typename get_rule_head < rule >::type ,
					typename remove_current_read_helper < rule >::type
				> ,
				typename tmp::at < rule , tmp::integral < int , 1 > >::type
			>
		{
		} ;
		template < typename A , typename env >
		struct make_first_helper ;
		template < typename T , typename id_type , id_type id , typename env >
		struct make_first_helper < tmp::list < terminal < T , id_type , id > > , env >
			: tmp::set < terminal < T , id_type , id > >
		{
		} ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id , typename env >
		struct make_first_helper < tmp::list < rule_type < T , id_type , id > > , env >
			: tmp::to_set
			<
				typename tmp::concat
				<
					typename tmp::map
					<
						tmp::eval
						<
							tmp::to_list
							<
								tmp::eval
								<
									make_first_helper
									<
										get_rule_body < tmp::arg < 0 > > ,
										tmp::id < env >
									>
								>
							>
						> ,
						typename tmp::filter
						<
							tmp::eval
							<
								tmp::equal
								<
									tmp::id < rule_type < T , id_type , id > > ,
									tmp::eval < get_rule_head < tmp::arg < 0 > > >
								>
							> ,
							env
						>::type
					>
				>::type
			>
		{
		} ;
		template < typename list , typename env >
		struct make_first_helper
			: make_first_helper
			<
				tmp::list < typename tmp::head < list >::type > ,
				env
			>
		{
		} ;
		template < typename A , typename env >
		struct make_first
			: make_first_helper
			<
				A ,
				typename tmp::unique
				<
					typename tmp::map
					<
						remove_current_read < tmp::arg < 0 > > ,
						typename tmp::to_list < env >::type
					>::type
				>::type
			>
		{
		} ;
		template < typename A , typename env >
		struct make_follow ;
		template < typename A , typename head , typename body , typename env >
		struct iterate_make_follow ;
		template < typename A , typename head , typename body , typename env >
		struct iterate_make_follow
			: iterate_make_follow < A , head , typename tmp::tail < body >::type , env >
		{
		} ;
		template < typename A , typename head , typename ... body , typename env >
		struct iterate_make_follow < A , head , tmp::list < A , body ... > , env >
			: tmp::union_
			<
				typename make_first < tmp::list < body ... > , env >::type ,
				typename iterate_make_follow
				<
					A ,
					head ,
					tmp::list < body ... > ,
					env
				>::type
			>
		{
		} ;
		template < typename A , typename head , typename env >
		struct iterate_make_follow < A , head , tmp::list < A > , env >
			: make_follow < head , env >
		{
		} ;
		template < typename A , typename head , typename env >
		struct iterate_make_follow < A , head , tmp::list < > , env >
			: tmp::set < >
		{
		} ;
		template < typename A , typename rule , typename env >
		struct iterate_make_follow_wrapper
			: iterate_make_follow
			<
				A ,
				typename get_rule_head < rule >::type ,
				typename get_rule_body < rule >::type ,
				env
			>
		{
		} ;
		template < typename A , typename env >
		struct make_follow_helper
			: tmp::to_set
			<
				typename tmp::concat
				<
					typename tmp::map
					<
						tmp::to_list < tmp::arg < 0 > > ,
						typename tmp::map
						<
							iterate_make_follow_wrapper < A , tmp::arg < 0 > , env > ,
							env
						>::type
					>::type
				>::type
			>
		{
		} ;
		template < typename A , typename env >
		struct make_follow
			: tmp::insert
			<
				typename make_follow_helper
				<
					A ,
					typename tmp::unique
					<
						typename tmp::map
						<
							remove_current_read < tmp::arg < 0 > > ,
							typename tmp::to_list < env >::type
						>::type
					>::type
				>::type ,
				end_read
			>
		{
		} ;
		template < int index , typename list >
		struct numbering ;
		template < int index , typename list >
		struct numbering
			: tmp::insert_dict
			<
				typename tmp::head < list >::type ,
				tmp::integral < int , index > ,
				typename numbering
				<
					index + 1 ,
					typename tmp::tail < list >::type
				>::type
			>
		{
		} ;
		template < int index >
		struct numbering < index , tmp::list < > >
			: tmp::dict < >
		{
		} ;
		template < typename T >
		struct collect_cmponent ;
		template < typename ... T >
		struct collect_cmponent < tmp::list < T ... > >
			: tmp::foldl
			<
				tmp::eval
				<
					tmp::union_
					<
						tmp::id < tmp::arg < 0 > > ,
						collect_cmponent < tmp::arg < 1 > >
					>
				> ,
				tmp::set < > ,
				tmp::list < T ... >
			>
		{
		} ;
		template < typename T1 , typename T2 >
		struct collect_cmponent < first_only_tuple < T1 , T2 > >
			: collect_cmponent < T1 >
		{
		} ;
		template < typename T , typename ... T_ , typename int_type >
		struct collect_cmponent < tmp::list < tmp::list < T , tmp::list < T_ ... > > , int_type > >
			: tmp::insert
			<
				typename collect_cmponent < tmp::list < T_ ... > >::type ,
				T
			>
		{
		} ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct collect_cmponent < rule_type < T , id_type , id > >
			: tmp::set < rule_type < T , id_type , id > >
		{
		} ;
		template < >
		struct collect_cmponent < current_read >
			: tmp::set < >
		{
		} ;
		template < typename ... rules_type >
		class parser
		{
			using rules_type_ = typename make_rules
			<
				1 ,
				tmp::list < > ,
				rules_type ...
			>::type ;
			using LRs = typename make_LR0
			<
				rules_type_
			>::type ;
			using top_rules = typename get_top_rules < LRs >::type ;
			using closures = typename make_closures
			<
				tmp::set < typename make_closure < top_rules , LRs >::type > ,
				LRs
			>::type ;
			using numbered_closures = typename numbering
			<
				0 ,
				typename tmp::to_list < closures >::type
			>::type ;
			using types_list = typename collect_cmponent
			<
				typename tmp::to_list < LRs >::type
			>::type ;
			using terminals = typename tmp::filter
			<
				tmp::not_ < is_not_terminal < tmp::arg < 0 > > > ,
				types_list
			>::type ;
			using non_terminals = typename tmp::filter
			<
				is_not_terminal < tmp::arg < 0 > > ,
				types_list
			>::type ;
			rules_type_ rules_ ;
			//typename tmp::print < tmp::list < terminals , non_terminals > >::type value ;
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
			static type value ;
		} ;
		template < typename rule_type , typename result_type , typename ... args_type >
		typename assign_to_function < rule_type , result_type , args_type ... >::type assign_to_function < rule_type , result_type , args_type ... >::value = [ ] ( const typename get_value_type < rule_type >::type & arg0 , const args_type & ... args ) { return result_type { arg0 , args ... } ; } ;
		template < typename lhs_type , typename rhs_type , typename result_type , typename ... args_type >
		struct assign_to_function < shift_result < lhs_type , rhs_type > , result_type , args_type ... >
			: assign_to_function < lhs_type , result_type , typename get_value_type < rhs_type >::type , args_type ... >
		{
		} ;
		template < template < typename T_ , typename id_type_ , id_type_ id_ > class rule_type , typename T , typename id_type , id_type id >
		struct get_value_type < rule_type < T , id_type , id > >
		{
			using type = T ;
		} ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		struct assign_result < lhs_type , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		struct assign_result < top_rule < T , id_type , id > , rhs_type >
		{
			using type = assign_result ;
			static typename assign_to_function < rhs_type , T >::type value ;
		} ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		struct assign_result < rule < T , id_type , id > , rhs_type >
		{
			using type = assign_result ;
			static typename assign_to_function < rhs_type , T >::type value ;
		} ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		typename assign_to_function < rhs_type , T >::type assign_result < top_rule < T , id_type , id > , rhs_type >::value { assign_to_function < rhs_type , T >::value } ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		typename assign_to_function < rhs_type , T >::type assign_result < rule < T , id_type , id > , rhs_type >::value { assign_to_function < rhs_type , T >::value } ;
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