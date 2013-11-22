//#include"parser_combinator/lexer.hpp"
#include"parser_combinator/parser.hpp"
//namespace bx = boost::xpressive ;
//namespace pl = parser_combinator::lexer ;
namespace pp = parser_combinator::parser ;
DECL_RULE_IDS_BEGIN ( id )
	DECL_RULE_ID ( s_id )
	DECL_RULE_ID ( pp_id )
	DECL_RULE_ID ( vp_id )
	DECL_RULE_ID ( np_id )
	DECL_RULE_ID ( n_id )
	DECL_RULE_ID ( p_id )
	DECL_RULE_ID ( v_id )
	DECL_RULE_ID ( tens_id )
/*
	DECL_RULE_ID ( expr_id )
	DECL_RULE_ID ( term_id )
	DECL_RULE_ID ( fact_id )
	DECL_RULE_ID ( plus_operation_id )
	DECL_RULE_ID ( minus_operation_id )
	DECL_RULE_ID ( mul_operation_id )
	DECL_RULE_ID ( div_operation_id )
	DECL_RULE_ID ( lp_id )
	DECL_RULE_ID ( rp_id )
	DECL_RULE_ID ( number_id )
*/
DECL_RULE_IDS_END
auto main ( ) -> int
{
	/*
	bx::sregex regex = bx::bos >> ( "instance" | + ( boost::xpressive::range ( 'a' , 'z' ) | boost::xpressive::range ( 'A' , 'Z' ) ) ) ;
	bx::smatch result ;
	if ( bx::regex_search ( std::string { "instanceof" } , result , regex ) )
	{
		std::clog << result.str ( ) << std::endl ;
	}
	std::cout << std::endl ;
	std::string input { std::istreambuf_iterator < char > { std::cin } , std::istreambuf_iterator < char > { } } ;
	auto lexer = pl::make_lexer ( input.begin ( ) , input.end ( ) ,
	"instance" , [ & ] ( const std::string & str )
	{
		std::cout << str << std::endl ;
	} ,
	+ ( boost::xpressive::range ( 'a' , 'z' ) | boost::xpressive::range ( 'A' , 'Z' ) ) , [ & ] ( const std::string & str )
	{
		std::cout << "word : " << str << std::endl ;
	} ,
	+ boost::xpressive::range ( '0' , '9' ) , [ & ] ( const std::string & str )
	{
		std::cout << "number : " << str << std::endl ;
	} ,
	+ ( boost::xpressive::set = ' ' , '\t' , '\r' , '\n' ) , [ & ] ( const std::string & )
	{
		std::cout << "space" << std::endl ;
	} ) ;
	lexer ( ) ;
	*/
	/*
	DECL_TOP_RULE ( double , id::expr_id , expr ) ;
	DECL_RULE ( double , id::term_id , term ) ;
	DECL_RULE ( double , id::fact_id , fact ) ;
	DECL_TERMINAL ( std::string , id::plus_operation_id , plus_operation ) ;
	DECL_TERMINAL ( std::string , id::minus_operation_id , minus_operation ) ;
	DECL_TERMINAL ( std::string , id::mul_operation_id , mul_operation ) ;
	DECL_TERMINAL ( std::string , id::div_operation_id , div_operation ) ;
	DECL_TERMINAL ( std::string , id::lp_id , lp ) ;
	DECL_TERMINAL ( std::string , id::rp_id , rp ) ;
	DECL_TERMINAL ( double , id::number_id , number ) ;
	*/
	DECL_TOP_RULE ( void * , id::s_id , s ) ;
	DECL_RULE ( void * , id::pp_id , pp ) ;
	DECL_RULE ( void * , id::vp_id , vp ) ;
	DECL_RULE ( void * , id::np_id , np ) ;
	DECL_TERMINAL ( void * , id::n_id , n ) ;
	DECL_TERMINAL ( void * , id::p_id , p ) ;
	DECL_TERMINAL ( void * , id::v_id , v ) ;
	DECL_TERMINAL ( void * , id::tens_id , tens ) ;
	auto psr = pp::make_parser
	(
		( s = pp >> vp ) ( [ ] ( void * , void * ) { return nullptr ; } ) ,
		( pp = np >> p ) ( [ ] ( void * , void * ) { return nullptr ; } ) ,
		( vp = pp >> vp ) ( [ ] ( void * , void * ) { return nullptr ; } ) ,
		( vp = v >> tens ) ( [ ] ( void * , void * ) { return nullptr ; } ) ,
		( np = n ) ( [ ] ( void * ) { return nullptr ; } )
	/*
		( expr = term ) ,
		( expr = expr >> plus_operation >> term ) ( [ ] ( double arg1 , const std::string & , double arg2 ) { return arg1 + arg2 ; } ) ,
		( expr = expr >> minus_operation >> term ) ( [ ] ( double arg1 , const std::string & , double arg2 ) { return arg1 - arg2 ; } ) ,
		( term = fact ) ,
		( term = term >> mul_operation >> fact ) ( [ ] ( double arg1 , const std::string & , double arg2 ) { return arg1 * arg2 ; } ) ,
		( term = term >> div_operation >> fact ) ( [ ] ( double arg1 , const std::string & , double arg2 ) { return arg1 / arg2 ; } ) ,
		( fact = lp >> expr >> rp ) ( [ ] ( const std::string & , double arg , const std::string & ) { return arg ; } ) ,
		( fact = number )
	*/
	) ;
	static_cast < void > ( psr ) ;
}
