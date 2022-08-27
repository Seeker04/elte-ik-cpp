#include <iostream>
#include "devec.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include "devec.h"

const int max = 1000;

int main()
{
  int your_mark = 1;
  /* 2-es */
  devec<int> da( max );
  da.push_back( 3 );
  da.push_front( 1 );
  da.push_back( 7 );
  da.push_front( 8 );

  devec<int> db( max );
  db.push_back( 2 );
  int* pos = &db.at( 0 );
  db.push_front( 2 );

  for( int i = 0; i < ( max / 2 )  - 1; ++i )
  {
    db.push_front( i );
    db.push_back( i );
  }

  devec<std::string> ds( max );
  ds.push_back( "World" );
  ds.push_front( "Hello" );

  if ( "Hello" == ds.at( 0 ) && 7 == da.at( 3 ) &&
       db.at( 0 ) == db.at( max - 1 ) &&
       &db.at( max / 2 ) == pos &&  2 == *pos &&
       max - 1 == &db.at( max - 1 ) - &db.at( 0 ) )
  {
    your_mark = da.at( 2 ) - da.at( 1 );
  }
  /**/
  /* 3-as */
  const devec<std::string> cds = ds;
  ds[ 1 ].push_back( '!' );
  ++da[ 0 ];

  if ( your_mark == cds.size() && 4 == da.size() &&
       "World!" == ds[ 1 ] && "Hello" == cds[ 0 ] &&
        9 == da[ 0 ] )
  {
    your_mark = da[ 2 ];
  }
  /**/
  /* 4-es */
  devec<int>::iterator it = da.begin();
  *it = 5;

  if ( 4 * 4 == std::accumulate( da.begin(), da.end(), 0 ) &&
       4 == std::count( db.begin(), db.end(), 2 ) &&
       1 == std::count( da.begin(), da.end(), your_mark ) )
  {
    your_mark = da[ 0 ] - da[ 1 ];
  }
  /**/
  /* 5-os */
  devec<bool> dv( max );
  dv.push_back( false );
  dv[ 0 ] = true;

  std::vector<int> vi = da;
  std::vector<std::string> vs = cds;

  if ( dv[ 0 ] && 2 == vs.size() && 'H' == vs[ 0 ][ 0 ] &&
       4 * 4 == std::accumulate( vi.begin(), vi.end(), 0 ) )
  {
    your_mark = dv.size() + vi.size();
  }
  /**/
  std::cout << "Your mark is "
            << your_mark;
  std::endl( std::cout );
}
