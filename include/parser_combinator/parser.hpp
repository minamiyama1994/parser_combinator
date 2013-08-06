#ifndef PARSER_COMBINATOR_PARSER_HPP
#define PARSER_COMBINATOR_PARSER_HPP
namespace parser_combinator
{
	namespace parser
	{
		class parser
		{
		public :
			parser ( ) = delete ;
			parser ( const parser & ) = delete ;
			parser ( parser && ) = delete ;
			auto operator = ( const parser & ) -> parser & = delete ;
			auto operator = ( parser && ) -> parser & = delete ;
			~ parser ( ) = default ;
		} ;
	}
}
#endif
/*
rule < double > expression ;
rule < double > add_expression ;
rule < double > mul_expression ;
rule < double > term ;
terminal < double > number ;
top_rule rule
{
	expression = add_expression ,
	add_expression = ( add_expression >> '+' >> mul_expression ) | ( add_expression >> '-' >> mul_expression ) | mul_expression ,
	mul_expression = ( mul_expression >> '*' >> term ) | ( mul_expression >> '/' >> term ) | ( mul_expression >> '%' >> term ) | term ,
	term = number | '(' >> expression >> ')'
} ;
*/
