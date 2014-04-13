# parser combinator library

## Motivation

There is a boost::split the famous parser EDSL, but this is a LL parser, it is not possible to perform the analysis of the LR grammar.

In addition, it is too complicated To use easily.

Therefore, we decided to also serve the purpose of learning about SLR parsing algorithm(in addition, other), and make your own.

## Notice

* I was prepared as described in page 119 from page 110 of [ISBN978-4-7819-1315-5](http://www.saiensu.co.jp/?page=book_details&ISBN=ISBN978-4-7819-1315-5).
* The library is made ​​using the [FTMP](https://github.com/minamiyama1994/FTMP) Library.

## Sample

See [test.cpp](https://github.com/minamiyama1994/parser_combinator/blob/master/test.cpp)

## Compiler

I'm sure the compiler of the following

* GCC4.8.10
* Clang3.4
