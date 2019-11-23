#include <qapplication.h>
#include "swray.h"

int main(int argc, char **argv)
{
  QApplication qapp(argc, argv);

  SWRay swray;

  swray.setGeometry(50, 50, 700, 700);
  swray.drawImage();
  
  qapp.setMainWidget( & swray );

  swray.show();
  return qapp.exec();
}
