#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
#include"boost/mpl/int.hpp"
#include"boost/mpl/vector.hpp"
#include"boost/mpl/equal.hpp"
#include"boost/mpl/copy_if.hpp"
#include"boost/mpl/unique.hpp"
#include"boost/mpl/transform.hpp"
#include"boost/mpl/front_inserter.hpp"
#include"boost/mpl/print.hpp"
namespace parser_combinator
{
	namespace parser
	{
		namespace mpl = boost::mpl ;
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
			: make_rules < index + 1 , std::tuple < type_in_tuple ... , first_only_tuple < args_head , mpl::int_ < index > > > , args_type ... >
		{
		} ;
		template < typename T1 >
		struct make_pair
		{
			template < typename T2 >
			struct apply
			{
				using type = mpl::pair < T2 , T1 > ;
			} ;
		} ;
		template < typename T >
		struct shift_to_vector ;
		template < typename T , typename id_type , id_type id >
		struct shift_to_vector < top_rule < T , id_type , id > >
		{
			using type = mpl::vector < top_rule < T , id_type , id > > ;
		} ;
		template < typename T , typename id_type , id_type id >
		struct shift_to_vector < rule < T , id_type , id > >
		{
			using type = mpl::vector < rule < T , id_type , id > > ;
		} ;
		template < typename T , typename id_type , id_type id >
		struct shift_to_vector < terminal < T , id_type , id > >
		{
			using type = mpl::vector < terminal < T , id_type , id > > ;
		} ;
		template < typename lhs_type , typename rhs_type >
		struct shift_to_vector < shift_result < lhs_type , rhs_type > >
			: mpl::push_back < typename shift_to_vector < lhs_type >::type , rhs_type >
		{
		} ;
		struct current_read
		{
		} ;
		template < typename T1 , typename T2 , typename T3 , typename T4 >
		struct vector_to_LR0
			: mpl::eval_if
			<
				std::is_same < T3 , T4 > ,
				mpl::push_back
				<
					T1 ,
					typename mpl::push_back < T2 , current_read >::type
				> ,
				vector_to_LR0
				<
					typename mpl::push_back
					<
						T1 ,
						typename mpl::insert < T2 , T3 , current_read >::type
					>::type ,
					T2 ,
					typename mpl::next < T3 >::type ,
					T4
				>
			>
		{
		} ;
		template < typename T >
		struct assign_to_vector ;
		template < typename lhs_type , typename rhs_type >
		struct assign_to_vector < assign_result < lhs_type , rhs_type > >
		{
			using seq_type = typename shift_to_vector < rhs_type >::type ;
			using type = typename mpl::transform
			<
				typename vector_to_LR0
				<
					mpl::vector < > ,
					seq_type ,
					typename mpl::begin < seq_type >::type ,
					typename mpl::end < seq_type >::type
				>::type ,
				mpl::push_back < mpl::vector < lhs_type > , mpl::_ >
			>::type ;
		} ;
		template < typename T >
		struct make_LR0 ;
		template < >
		struct make_LR0 < std::tuple < > >
		{
			using type = mpl::vector < > ;
		} ;
		template < typename lhs_type , typename rhs_type >
		struct make_LR0 < assign_result < lhs_type , rhs_type > >
			: assign_to_vector < assign_result < lhs_type , rhs_type > >
		{
		} ;
		template < typename T1 , typename T2 >
		struct make_LR0 < first_only_tuple < T1 , T2 > >
			: mpl::transform
			<
				typename make_LR0 < T1 >::type ,
				make_pair < T2 >
			>
		{
		} ;
		template < typename T1 , typename ... T_ >
		struct make_LR0 < std::tuple < T1 , T_ ... > >
			: mpl::unique
			<
				typename mpl::copy
				<
					typename make_LR0 < T1 >::type ,
					mpl::back_inserter < typename make_LR0 < std::tuple < T_ ... > >::type >
				>::type ,
				std::is_same < mpl::_1 , mpl::_2 >
			>
		{
		} ;
		template < typename T >
		struct is_top_rule
			: mpl::false_
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_top_rule < top_rule < T , id_type , id > >
			: mpl::true_
		{
		} ;
		template < typename T >
		struct eval_is_top_rule
			: is_top_rule < typename T::type >
		{
		} ;
		template < typename T >
		struct is_not_terminal ;
		template < typename T , typename id_type , id_type id >
		struct is_not_terminal < top_rule < T , id_type , id > >
			: mpl::true_
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_not_terminal < rule < T , id_type , id > >
			: mpl::true_
		{
		} ;
		template < typename T , typename id_type , id_type id >
		struct is_not_terminal < terminal < T , id_type , id > >
			: mpl::false_
		{
		} ;
		template < typename T >
		struct first
		{
			using type = typename T::first ;
		} ;
		template < typename T >
		struct second
		{
			using type = typename T::second ;
		} ;
		template < typename T >
		struct concat
			: mpl::fold
			<
				T ,
				mpl::vector < > ,
				mpl::copy
				<
					mpl::_2 ,
					mpl::back_inserter < mpl::_1 >
				>
			>
		{
		} ;
		template < typename T >
		struct eval
			: T::type
		{
		} ;
		template < typename T , typename set >
		struct elem
			: mpl::fold
			<
				set ,
				mpl::bool_ < true > ,
				mpl::and_ < std::is_same < mpl::_2 , T > , mpl::_1 >
			>
		{
		} ;
		template < typename T , typename set >
		struct eval_elem
			: elem
			<
				typename T::type ,
				set
			>
		{
		} ;
		template < typename T >
		struct get_rule_head
			: mpl::at < typename T::first , mpl::int_ < 0 > >
		{
		} ;
		template < typename T >
		struct get_rule_body
			: mpl::at < typename T::first , mpl::int_ < 1 > >
		{
		} ;
		template < typename T , int N >
		struct at_rule_body
			: mpl::at < typename get_rule_body < T >::type , mpl::int_ < N > >
		{
		} ;
		template < typename LR0s >
		struct get_top_rules_helper
			: mpl::copy_if
			<
				LR0s ,
				eval_is_top_rule < get_rule_head < mpl::_ > > ,
				mpl::back_inserter < mpl::vector < > >
			>
		{
		} ;
		template < typename T >
		struct is_non_read
			: std::is_same < typename at_rule_body < T , 0 >::type , current_read >
		{
		} ;
		template < typename LR0s >
		struct get_top_rules
			: mpl::copy_if
			<
				typename get_top_rules_helper < LR0s >::type ,
				is_non_read < mpl::_ > ,
				mpl::back_inserter < mpl::vector < > >
			>
		{
		} ;
		template < typename T >
		struct get_next_read
			: mpl::deref
			<
				typename mpl::next
				<
					typename mpl::find
					<
						typename get_rule_body < T >::type ,
						current_read
					>::type
				>::type
			>
		{
		} ;
		template < typename rules , typename env >
		struct collect_rules_helper
		{
			using interim_rules = typename mpl::transform
			<
				rules ,
				get_next_read < mpl::_ >
			>::type ;
			using rules_ = typename mpl::unique
			<
				interim_rules ,
				std::is_same < mpl::_1 , mpl::_2 >
			>::type ;
			using interim_next_rules = typename mpl::copy_if
			<
				env ,
				eval_elem < get_rule_head < mpl::_ > , rules_ > ,
				mpl::back_inserter < mpl::vector < > >
			>::type ;
			using type = typename mpl::copy_if
			<
				interim_next_rules ,
				is_non_read < mpl::_ > ,
				mpl::back_inserter < mpl::vector < > >
			>::type ;
		} ;
		template < typename rules , typename env >
		struct collect_rules
			: mpl::unique
			<
				typename collect_rules_helper
				<
					rules ,
					env
				>::type ,
				std::is_same < mpl::_1 , mpl::_2 >
			>
		{
		} ;
		template < typename T1 , typename T2 >
		struct is_not_include
			: mpl::not_
			<
				typename elem
				<
					T1 ,
					T2
				>::type
			>
		{
		} ;
		template < typename newer , typename interim >
		struct true_newer
			: mpl::copy_if
			<
				newer ,
				is_not_include < mpl::_ , interim > ,
				mpl::back_inserter < mpl::vector < > >
			>
		{
		} ;
		template < typename interim , typename newer , typename env >
		struct make_closure
			: mpl::if_
			<
				mpl::empty < typename true_newer < newer , interim >::type > ,
				interim ,
				make_closure
				<
					typename concat
					<
						mpl::vector
						<
							interim ,
							typename true_newer < newer , interim >::type
						>
					>::type ,
					typename collect_rules
					<
						typename true_newer < newer , interim >::type ,
						env
					>::type ,
					env
				>
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
			using LRs = typename make_LR0 < rules_type_ >::type ;
			using top_rules = typename get_top_rules < LRs >::type ;
			using type = typename make_closure
			<
				top_rules ,
				typename collect_rules
				<
					top_rules ,
					LRs
				>::type ,
				LRs
			>::type ;
			rules_type_ rules_ ;
			// typename mpl::print < type >::type value ;
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