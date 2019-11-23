#include <vector.h>

main()
{
  {
    unitv3f unitv( 1, 0, 0 );
    
    cross3f cross = unitv.cross();
    
    cout << "unitv: " << unitv << endl;
    cout << "up:    " << cross.up() << endl;
    cout << "side:  " << cross.side() << endl;
  }

  {
    unitv3f unitv( 0, 1, 0 );
    
    cross3f cross = unitv.cross();
    
    cout << "unitv: " << unitv << endl;
    cout << "up:    " << cross.up() << endl;
    cout << "side:  " << cross.side() << endl;
  }


  {
    unitv3f unitv( 0, 0, 1 );
    
    cross3f cross = unitv.cross();
    
    cout << "unitv: " << unitv << endl;
    cout << "up:    " << cross.up() << endl;
    cout << "side:  " << cross.side() << endl;
  }
}
  
