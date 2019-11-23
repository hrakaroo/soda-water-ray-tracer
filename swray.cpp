#include "swray.h"

#include <qpainter.h>
#include <math.h>
#include <iostream.h>

SWRay::SWRay(QWidget *parent=0, const char *name=0) :
  QWidget( parent, name)
{ 
  // No flicker
  setBackgroundMode(NoBackground);

  _env = new SWenv( 700, 700 );
}

void SWRay::drawImage()
{
  // ... hard set the pixels for now
  int pixelsX = rect().width();
  int pixelsY = rect().height();

  _qpixmap = new QPixmap( pixelsX, pixelsY );
  
  QPainter qpainter;

  qpainter.begin( _qpixmap, this);

  cout << "Mapping photons" << endl;
  _env->mapPhotons();

  cout << "Start rendering" << endl;
  
  int count = 0;

  for( int y = 0; y < pixelsY; y ++)
    {
      if( count ++ % 50 == 0 ) cout << endl;
      cout << ".";

      for( int x = 0; x < pixelsX; x++ )
	{
	  SWcolor color = _env->color(x, y);

	  QColor qcolor( color.redInt(), 
			 color.greenInt(),
			 color.blueInt() );
	  qpainter.setPen( QPen(qcolor, 1));
	  qpainter.drawPoint( x, y );
	}
    }

  cout << "Done rendering" << endl;

  if( _qpixmap->save( "swray.png", "PNG") )
    cout << "Saved to file: swray.png" << endl;
}

void SWRay::paintEvent(QPaintEvent *)
{
  QPainter qpainter(this);

  bitBlt(this, 0, 0, _qpixmap);
}
