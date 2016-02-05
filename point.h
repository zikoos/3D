#ifndef POINT_H
#define POINT_H
#include<iostream>
using namespace std;
class  point
{
public:
     point();
     point(double x, double y, double z);
     void afficher(ostream &flux) const;
     void setabs(double x);
     void setord(double y);
     void setalt(double z);
     double getabs();
     double getord();
     double getalt();

private:
     double abs;
     double ord;
     double alt;
};

std::ostream &operator<<(ostream &flux, point const& p);

#endif // POINT_H
