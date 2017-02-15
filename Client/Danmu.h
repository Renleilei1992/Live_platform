#ifndef DANMU_H
#define DANMU_H

#include <QLabel>
#include <QRect>
#include <QColor>
#include <QDebug>
#include <QTextCharFormat>
#include <QPainter>
#include <iostream>
#include <QTime>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPoint>


class Danmu : public QLabel
{

    Q_OBJECT

  public:

      Danmu(QWidget * parent,QString text,QString color,
            int type,QRect rect,QPoint point,QFont danmuFont = QFont("SimHei",20,100),
            double Transparency = 1.00,int runTime=3000);       //构造函数，常用

      ~Danmu();     //析构函数

      //一些成员变量的Get方法与Set方法
      void setPoint(QPoint point);

      int getPosX();

      int getPosY();

      void setPosX(int posx);

      void setPosY(int posy);

      void setColor(QString color);

      QString getColor();

      void setType(int type);

      int getType();

      void setQColor(QColor qcolor);

      QColor getQColor();

      void setQFont(QFont danmuFont);

      QFont getQFont();

      void setTransparency(double Transparency);

      double getTransparency();

      void setScreenRect(QRect screenRect);

      QRect getScreenRect();

      int getRunTime();

      void setRunTime(int runTime);

      QPropertyAnimation * getanimation();

  protected:
      void paintEvent(QPaintEvent *);       //重点，弹幕的绘制函数

  private:
      int PosX;
      int PosY;
      QString DText;
      QString color;
      QColor qcolor;
      int type;
      QFont danmuFont;
      int DHeight;
      double Transparency;
      QRect screenrect;
      QPropertyAnimation *anim2;
      QPoint point;
      int runTime;
};

#endif // DANMU_H
