
#ifndef __SWRAY_H_
#define __SWRAY_H_

#include <qwidget.h>
#include <qpixmap.h>

#include <SW/color.h>
#include <SW/env.h>

class SWRay : public QWidget
{
 protected:
  SWenv   * _env;
  QPixmap * _qpixmap;

  void paintEvent(QPaintEvent *);

 public:
  SWRay( QWidget *parent=0, const char *name=0);

  void drawImage();
};

#endif

