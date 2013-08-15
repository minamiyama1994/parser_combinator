#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
#include"boost/mpl/vector.hpp"
#include"boost/mpl/push_back.hpp"
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
		template < typename type_tuple , typename ... args_type >
		struct make_rules ;
		template < typename ... type_in_tuple >
		struct make_rules < std::tuple < type_in_tuple ... > >
		{
			using type = std::tuple < type_in_tuple ... > ;
		} ;
		template < typename ... type_in_tuple , typename args_head , typename ... args_type >
		struct make_rules < std::tuple < type_in_tuple ... > , args_head , args_type ... >
			: make_rules < std::tuple < type_in_tuple ... , args_head > , args_type ... >
		{
		} ;
		template < typename ... rules_type >
		class parser
		{
			using rules_type_ = typename make_rules < std::tuple < > , rules_type ... >::type ;
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