#include "point.h"
#include "global.h"


point::point()
{
    abs=0;
    ord=0;
    alt=0;
}
point::point(double x, double y, double z)
{
    abs=x;
    ord=y;
    alt=z;
}

ostream &operator <<(ostream &flux, point const& p)

{

    p.afficher(flux) ;

    return flux;

}
void point::afficher(std::ostream &flux) const
{
    flux << abs << ";" << ord << ";" << alt ;
}
void point::setabs(double x)
{
    abs=x;
}
void point::setord(double y)
{
    ord=y;
}
void point::setalt(double z)
{
    alt=z;
}
double point::getabs()
{
    return abs;
}

double point::getord()
{
    return ord;
}

double point::getalt()
{
    return alt;
}
