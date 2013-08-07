#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
namespace parser_combinator
{
	namespace parser
	{
		template < typename lhs_type , typename rhs_type >
		struct assign_result ;
		template < typename lhs_type , typename rhs_type >
		struct shift_result ;
		template < typename lhs_type , typename rhs_type >
		struct or_result ;
		template < typename T , typename id_type , id_type id >
		struct rule
		{
			using type = T ;
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
		public :
			using type = T ;
			static constexpr id_type value = id ;
			terminal ( ) = default ;
			terminal ( const terminal & ) = default ;
			terminal ( terminal && ) = default ;
			auto operator = ( const terminal & ) -> terminal & = default ;
			auto operator = ( terminal && ) -> terminal & = default ;
			~ terminal ( ) = default ;
		} ;
		template < typename T , typename id_type , id_type id , typename rhs_lhs_type , typename rhs_rhs_type >
		class assign_result < rule < T , id_type , id > , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename T , typename id_type , id_type id , typename rhs_type >
		class assign_result < rule < T , id_type , id > , rhs_type >
		{
		public :
			using type = assign_result ;
		} ;
		template < typename T , typename id_type , id_type id , typename rhs_lhs_type , typename rhs_rhs_type >
		class assign_result < rule < T , id_type , id > , shift_result < rhs_lhs_type , rhs_rhs_type > >
		{
		public :
			using type = assign_result ;
		} ;
		template < typename T , typename id_type , id_type id , typename rhs_lhs_type , typename rhs_rhs_type >
		class assign_result < rule < T , id_type , id > , or_result < rhs_lhs_type , rhs_rhs_type > >
			: public or_result < typename assign_result < rule < T , id_type , id > , rhs_lhs_type >::type , typename assign_result < rule < T , id_type , id > , rhs_rhs_type >::type >
		{
		public :
		} ;
		template < typename lhs_type , typename rhs_type >
		class shift_result
		{
		public :
			using type = shift_result ;
		} ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_type >
		class shift_result < assign_result < lhs_lhs_type , lhs_rhs_type > , rhs_type > ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		class shift_result < lhs_type , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		class shift_result < assign_result < lhs_lhs_type , lhs_rhs_type > , assign_result < rhs_lhs_type , rhs_rhs_type > > ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_type >
		class shift_result < or_result < lhs_lhs_type , lhs_rhs_type > , rhs_type >
			: public or_result < typename shift_result < lhs_lhs_type , rhs_type >::type , typename shift_result < lhs_rhs_type , rhs_type >::type >
		{
		} ;
		template < typename lhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		class shift_result < lhs_type , or_result < rhs_lhs_type , rhs_rhs_type > >
			: public or_result < typename shift_result < lhs_type , rhs_lhs_type >::type , typename shift_result < lhs_type , rhs_rhs_type >::type >
		{
		} ;
		template < typename lhs_lhs_type , typename lhs_rhs_type , typename rhs_lhs_type , typename rhs_rhs_type >
		class shift_result < or_result < lhs_lhs_type , lhs_rhs_type > , or_result < rhs_lhs_type , rhs_rhs_type > >
			: public or_result < typename shift_result < or_result < lhs_lhs_type , lhs_rhs_type > , rhs_lhs_type >::type , typename shift_result < or_result < lhs_lhs_type , lhs_rhs_type > , rhs_rhs_type >::type >
		{
		} ;
		template < typename lhs_type , typename rhs_type >
		class or_result
		{
		public :
			using type = or_result ;
		} ;
		template < typename lhs_type , typename rhs_type >
		auto operator >> ( const lhs_type & , const rhs_type & ) -> shift_result < lhs_type , rhs_type >
		{
			return shift_result < lhs_type , rhs_type > { } ;
		}
		template < typename lhs_type , typename rhs_type >
		auto operator | ( const lhs_type & , const rhs_type & ) -> or_result < lhs_type , rhs_type >
		{
			return or_result < lhs_type , rhs_type > { } ;
		}
		template < typename T , typename id_type , id_type id >
		template < typename rhs_type >
		auto rule < T , id_type , id >::operator = ( const rhs_type & ) -> assign_result < rule , rhs_type >
		{
			return assign_result < rule , rhs_type > { } ;
		} ;
	}
}
#endif
using namespace parser_combinator::parser ;
enum class id_type
{
	Dummy ,
	Expression ,
	Add_expression ,
	Mul_expression ,
	Term ,
	Number ,
	Add_operator ,
	Mul_operator ,
	Lp ,
	Rp
} ;
rule < double , id_type , id_type::Expression > expression ;
rule < double , id_type , id_type::Add_expression > add_expression ;
rule < double , id_type , id_type::Mul_expression > mul_expression ;
rule < double , id_type , id_type::Term > term ;
terminal < double , id_type , id_type::Number > number ;
terminal < const char * const , id_type , id_type::Add_operator > add_operator ;
terminal < const char * const , id_type , id_type::Mul_operator > mul_operator ;
terminal < const char * const , id_type , id_type::Lp > lp ;
terminal < const char * const , id_type , id_type::Rp > rp ;
auto func = [ & ] ( )
{
	expression = add_expression ;
	add_expression = ( add_expression >> add_operator >> mul_expression ) | mul_expression ;
	mul_expression = ( mul_expression >> mul_operator >> term ) | ( mul_expression >> mul_operator >> term ) | term ;
	term = number | lp >> expression >> rp ;
} ;
