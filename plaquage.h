#ifndef PLAQUAGE_H
#define PLAQUAGE_H
#include<vector>
#include <QVector>
#include <QVector3D>
#include<point.h>

class plaquage
{
    float xcoordinatebarycentre;
    float ycoordinatebarycentre;
    float zcoordinatebarycentre;
    QVector<QVector3D> montab;
public:
    plaquage();
    void setbarycentrecoord(float x,float y,float z);
    float getZbarycentrecoord();
    float getYbarycentrecoord();
    float getXbarycentrecoord();
    QVector<QVector3D> getintersection(QVector<QVector3D> vertex);
    void plaquercube();
    bool onSegment(QVector3D p, QVector3D q, QVector3D r);
    bool invertex(QVector3D p,QVector<QVector3D> vertex);
    int orientation(QVector3D p, QVector3D q, QVector3D r);
    bool doIntersect(QVector3D p1, QVector3D q1, QVector3D p2, QVector3D q2);
    QVector3D getintersectionoftwolines(QVector3D a,QVector3D b,QVector3D c,QVector3D d);
    QVector<QVector3D> getbounds(QVector<QVector3D> vertex);
    QVector<QVector3D> findintersectpoint(QVector<QVector3D> vertex,QVector<QVector3D>montab);
    QVector<QVector3D> vertexbaseplaquer(QVector<QVector3D> intersection);
    bool surporpose(QVector3D a,QVector3D b,QVector3D c,QVector3D d);
    bool sommet(QVector3D vertex);
    QVector<QVector3D> ikhan(QVector<QVector3D> vertex, QVector<QVector3D> triangles);
    float distancetwopoints(QVector3D a,QVector3D b);
    bool isequalplanime(QVector3D a,QVector3D b);
    void setmontab(QVector<QVector3D> tab);



    bool collinear(QVector3D p0, QVector3D p1, QVector3D p2, QVector3D p3);
    QVector3D ptintersect(QVector3D p0, QVector3D p1, QVector3D p2, QVector3D p3);
    QVector<float> boundsofintersection(QVector<QVector3D> intersection);
    QVector<QVector3D> sortofintersection(QVector<QVector3D> intersection, QVector<QVector3D> vertex);




};

#endif // PLAQUAGE_H
