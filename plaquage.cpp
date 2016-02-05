#include "plaquage.h"
#include"global.h"
#include"plan.h"
#include<QtCore/qmath.h>
#include <QVector>
#include <QVector3D>

#include<global.h>
plaquage::plaquage()
{
}
void plaquage::setbarycentrecoord(float x,float y,float z)
{
    this->xcoordinatebarycentre=x;
    this->ycoordinatebarycentre=y;
    this->zcoordinatebarycentre=z;
}

float plaquage::getXbarycentrecoord()
{
    return this->xcoordinatebarycentre;

}

float plaquage::getYbarycentrecoord()
{
    return this->ycoordinatebarycentre;

}

float plaquage::getZbarycentrecoord()
{
    return this->zcoordinatebarycentre;

}
void plaquage::plaquercube(){


}
QVector<QVector3D> plaquage::getintersection(QVector<QVector3D> vertex){
    QVector<QVector3D> result;
    //float alpha=-99,beta=-99,gamma=-99,alpha1=-99,beta1=-99,gamma1=-99;

    for(size_t i=0;i<vertex.size();++i)
    {
        for(size_t j=0; j<montab.size()-4000;++j){
            const float alpha = (((montab[j+1].y() -montab[j+4000].y())*(vertex[i].x() - montab[j+4000].x()) + (montab[j+4000].x() - montab[j+1].x())*(vertex[i].y() - montab[j+4000].y())) /((montab[j+1].y() -montab[j+4000].y())*(montab[j].x() - montab[j+4000].x()) + (montab[j+4000].x() - montab[j+1].x())*(montab[j].y() - montab[j+4000].y())));
            const float beta = ((montab[j+4000].y() - montab[j+1].y())*(vertex[i].x() - montab[j+4000].x()) + (montab[j].x() - montab[j+4000].x())*(vertex[i].y() - montab[j+4000].y())) /((montab[j+1].y() - montab[j+4000].y())*(montab[j].x() - montab[j+4000].x()) + (montab[j+4000].x() - montab[j+1].x())*(montab[j].y() - montab[j+4000].y()));
            const float gamma = 1 - alpha - beta;

            const float alpha1= ((montab[j+4001].y() -montab[j+4000].y())*(vertex[i].x() - montab[j+4000].x()) + (montab[j+4000].x() - montab[j+4001].x())*(vertex[i].y() - montab[j+4000].y())) /((montab[j+4001].y() -montab[j+4000].y())*(montab[j+1].x() - montab[j+4000].x()) + (montab[j+4000].x() - montab[j+4001].x())*(montab[j+1].y() - montab[j+4000].y()));
            const float beta1 = ((montab[j+4000].y() - montab[j+4001].y())*(vertex[i].x() - montab[j+4000].x()) + (montab[j+1].x() - montab[j+4000].x())*(vertex[i].y() - montab[j+4000].y())) /((montab[j+4001].y() - montab[j+4000].y())*(montab[j+1].x() - montab[j+4000].x()) + (montab[j+4000].x() - montab[j+4001].x())*(montab[j+1].y() - montab[j+4000].y()));
            const float gamma1 = 1 - alpha1 - beta1;
            if (alpha>=0 && beta>=0 && gamma>=0){
                result.push_back(vertex[i]);
                result.push_back(montab[j]);
                result.push_back(montab[j+1]);
                result.push_back(montab[j+4000]);
                break;


            } else if(alpha1>=0 && beta1>=0 && gamma1>=0){
                result.push_back(vertex[i]);
                result.push_back(montab[j+1]);
                result.push_back(montab[j+4001]);
                result.push_back(montab[j+4000]);
                break;

            }

        }
    }

return result;
}

bool plaquage::onSegment(QVector3D p, QVector3D q, QVector3D r)
{
    if (q.x() <= max(p.x(), r.x()) && q.x() >= min(p.x(), r.x()) &&
        q.y() <= max(p.y(), r.y()) && q.y() >= min(p.y(), r.y()))
       return true;

    return false;
}



int plaquage::orientation(QVector3D p, QVector3D q, QVector3D r)
{

    int val = (q.y() - p.y()) * (r.x()- q.x()) -
              (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}



bool plaquage::doIntersect(QVector3D p1, QVector3D q1, QVector3D p2, QVector3D q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}
QVector3D plaquage::getintersectionoftwolines(QVector3D a,QVector3D b,QVector3D c,QVector3D d){
    QVector3D res;
    float yi,xi,a1=0,b1,a2=0,b2;

    if(b.x()!=a.x()){
        a1 =(b.y()-a.y())/(b.x()-a.x());
        b1 = a.y() - a1*a.x();
    }
    if(d.x()!=c.x()){
        a2 =(d.y()-c.y())/(d.x()-c.x());
        b2 = c.y() - a2*c.x();
       }

    if(a1!=a2){
        //yi=(b2-(a2/a1)*b1)/(1-a2/a1);
        //xi=(yi-b1)/a1;
        xi=(b2-b1)/(a1-a2);
        yi=a1*xi+b1;
    }
    else {
        //xi=(b1-b2)/a2;
        //yi=b1;
        xi=a.x();
        yi=a.y();
          }/*else {
                 float xi=0;
                 float yi=b1;
    }*/


    res.setX(xi);
    res.setY(yi);
    res.setZ(-99);
    return res;



}
QVector<QVector3D> plaquage::getbounds(QVector<QVector3D> vertex){
    QVector<QVector3D> res;
    QVector<QVector3D>  mestriangles=getintersection(vertex);
    QVector3D p1,p2,p3,p4;
    float xmax =vertex[0].x();
    float xmin =vertex[vertex.size()-1].x();

    float ymax =vertex[0].y();//mestriangles[0].y();
    float ymin =vertex[vertex.size()-1].y();//mestriangles[0].y();


    for(unsigned int i=0;i<mestriangles.size();++i){
        if(xmin>mestriangles[i].x())
            xmin=mestriangles[i].x();

        if(xmax<mestriangles[i].x())
            xmax=mestriangles[i].x();

        if(ymin>mestriangles[i].y())
            ymin=mestriangles[i].y();

        if(ymax<mestriangles[i].y())
            ymax=mestriangles[i].y();

    }
    p1.setX(xmin);
    p1.setY(ymax);
    p1.setZ(0);

    p2.setX(xmax);
    p2.setY(ymax);
    p2.setZ(0);

    p3.setX(xmax);
    p3.setY(ymin);
    p3.setZ(0);

    p4.setX(xmin);
    p4.setY(ymin);
    p4.setZ(0);

    res.push_back(p1);
    res.push_back(p2);
    res.push_back(p3);
    res.push_back(p4);

    return res;

}


QVector<QVector3D> plaquage::vertexbaseplaquer(QVector<QVector3D> intersection)
{
    QVector<QVector3D>  res;
    QVector3D respoint;
    Plan monplan;
    QVector<float> normal;
    QVector<float>  getpointZ;
    int i=1;

 for(unsigned int j=0;j<intersection.size()-4;j=j+4)
     {
        normal=monplan.normale(intersection[i],intersection[i+1],intersection[i+2]);
        getpointZ=monplan.planeEquation(intersection[i],intersection[j],normal);
        respoint.setX(getpointZ[0]);
        respoint.setY(getpointZ[1]);
        respoint.setZ(getpointZ[2]);
        res.push_back(respoint);
        i=i+4;

     }
 return res;


}
bool plaquage::invertex(QVector3D p,QVector<QVector3D> vertex){
    bool in=false;
    int epsilon=5;
    float dif1,dif2;
    for(unsigned int i=0;i<vertex.size();i++){
        dif1=qAbs(p.x()-vertex[i].x());
        dif2=qAbs(p.y()-vertex[i].y());
        if( dif1<epsilon && dif2<epsilon   ){
            in=true;
            break;
        }

    }
    return in;


}

bool plaquage::surporpose(QVector3D a,QVector3D b,QVector3D c,QVector3D d){

    bool res=false;
    float a1=0,b1=0,y1,y2;


    if((b.x()!=a.x())){
     a1 =(b.y()-a.y())/(b.x()-a.x());
     b1 = a.y() - a1*a.x();
     y1=a1*c.x()+b1;
     y2=a1*d.x()+b1;
    }else if((b.y()==c.y() && a.y()==c.y() && b.y()>d.y()&&a.y()==d.y()))
        res=true;
    else if((b.x()==c.x() && a.x()==c.x() && b.x()>d.x()&&a.x()==d.x()))
            res=true;


    if(y1==c.y() && y2==d.y()){
       res=true;
    }
    return res;


}




















bool plaquage::sommet(QVector3D vertex){
        bool sommet =false;
        for(unsigned int j=0;j<montab.size();++j){

            if(vertex.x()==montab[j].x() && vertex.y()==montab[j].y()){
                sommet =true;

            }

        }

    return sommet;
}












float plaquage::distancetwopoints(QVector3D a,QVector3D b){
    float dx = qPow((a.x()-b.x()), 2);
    float dy = qPow((a.y()-b.y()), 2);

    float res =qSqrt(dx+dy);
    return res;
}
bool plaquage::isequalplanime(QVector3D a,QVector3D b){

    bool res =false;
    int epsilon=5;
    float dif1,dif2;
        dif1=qAbs(a.x()-b.x());
        dif2=qAbs(a.y()-b.y());
    if(dif1<epsilon && dif2<epsilon){
        res=true;
    }
    return res;

}
/***********************************************************************/
bool plaquage::collinear(QVector3D p0,QVector3D p1,QVector3D p2,QVector3D p3){
    bool coll =false;

    float  s10_x, s10_y, s32_x, s32_y, denom;
        s10_x = p1.x() - p0.x();
        s10_y = p1.y() - p0.y();
        s32_x = p3.x() - p2.x();
        s32_y = p3.y() - p2.y();

        denom = s10_x * s32_y - s32_x * s10_y;
        if (denom == 0)
            coll= true;
        return coll;
}
//********************************************************************
QVector3D plaquage::ptintersect(QVector3D p0, QVector3D p1, QVector3D p2, QVector3D p3){
    float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y,s_numer, t_numer, denom, t,tx,ty,tz=-99;
    QVector3D res;
        s10_x = p1.x() - p0.x() ;
        s10_y = p1.y() - p0.y();
        s32_x = p3.x() - p2.x();
        s32_y = p3.y()- p2.y();

        denom = s10_x * s32_y - s32_x * s10_y;


        s02_x = p0.x() - p2.x();
        s02_y = p0.y() - p2.y();
        s_numer = s10_x * s02_y - s10_y * s02_x;


        t_numer = s32_x * s02_y - s32_y * s02_x;

        // Collision detected
        t = t_numer / denom;
        tx=p0.x() + (t * s10_x);
        ty=p0.y()+ (t * s10_y);

            res.setX( tx);
            res.setY( ty);
            // z =)
            if (p2.x()!=p3.x())
                    tz = (tx - p2.x()) / (p3.x() - p2.x());
                else if(p0.y()!=p3.y())
                    tz = (ty - p2.y()) / (p3.y() - p2.y());

                 res.setZ(p3.z() + (p3.z() - p3.z())*tz);



        return res;

}

//********************************************/


QVector<QVector3D> plaquage::findintersectpoint(QVector<QVector3D> vertex, QVector<QVector3D> montab){
    QVector<QVector3D> res;
    QVector<QVector3D> res2;
    QVector3D inters;
    //res.push_back(vertex[0]);
    bool segment1=true;
    bool segment2=true;
    bool segment3=true;
    bool premier=true;
    bool dernier=true;
    int mdxV1=fmod(vertex[0].x(),25);
    int mdyV1=fmod(vertex[0].y(),25);
    int mdxV2=fmod(vertex[1].x(),25);
    int mdyV2=fmod(vertex[1].y(),25);




            for (size_t j=0;j<montab.size()-4000;++j){

                /*if(isequalplanime(montab[j],vertex[0])){
                    if(!isequalplanime(montab[j],res[res.size()-1])&&!invertex(montab[j],res)){
                        res.push_back(montab[j]);
                        //break;
                    }

                }*/

                    if(segment1 ){


                                if(collinear(montab[j+1],montab[j],vertex[0],vertex[1]) && mdxV1==0 && mdyV1==0){
                                    if(doIntersect(montab[j+1],montab[j],vertex[0],vertex[1])){
                                        float da=distancetwopoints(montab[j],montab[j+1]);
                                        float db=distancetwopoints(vertex[0],vertex[1]);
                                        if(da<=db){
                                                if(!invertex(montab[j],res)){

                                                    res.push_back(montab[j]);

                                                }
                                        }else{
                                            if(!invertex(vertex[1],res)){
                                                res.push_back(vertex[1]);
                                                break;
                                                }
                                            }

                                        }



                                }else {segment1=false;}


                    }


                            /**************************************************************/
                            if(segment2){


                                        if(collinear(montab[j+1],montab[j+4000],vertex[0],vertex[1])&& mdxV1==0 && mdyV1==0){
                                            {if(doIntersect(montab[j+1],montab[j+4000],vertex[0],vertex[1])){
                                                float da=distancetwopoints(montab[j+1],montab[j+4000]);
                                                float db=distancetwopoints(vertex[0],vertex[1]);
                                                if(da<=db){
                                                        if(!invertex(montab[j+1],res)){

                                                            res.push_back(montab[j+1]);
                                                        }


                                                }else{
                                                    if(!invertex(vertex[1],res)){
                                                        res.push_back(vertex[1]);
                                                        break;
                                                    }

                                                }

                                            }
                                            }
                                        }else segment2=false;


                            }
                            /*************************************/
                            if(segment3){


                                        if(collinear(montab[j],montab[j+4000],vertex[0],vertex[1]) && mdxV1==0 && mdyV1==0){
                                            { if(doIntersect(montab[j],montab[j+4000],vertex[0],vertex[1])){
                                                float da=distancetwopoints(montab[j],montab[j+4000]);
                                                float db=distancetwopoints(vertex[0],vertex[1]);
                                                if(da<=db){
                                                        if(!invertex(montab[j],res)){

                                                            res.push_back(montab[j]);
                                                            j=j+3999;
                                                        }


                                                }else{
                                                    if(!invertex(vertex[1],res)){
                                                        res.push_back(vertex[1]);
                                                        break;
                                                        }
                                                    }

                                                }/*
                                                else if(doIntersect(montab[j],montab[j+1],vertex[0],vertex[1])){
                                                    inters=ptintersect(montab[j],montab[j+1],vertex[0],vertex[1]);
                                                    if(!invertex(inters,res))
                                                        res.push_back(inters);
                                                    }*/


                                               }


                                        }

                                           else segment3=false;


                            }



                /**********************************************/


















                /**********************************************/





                if(!segment1&& !segment2&& !segment3){
                    if(premier){
                        res.push_back(vertex[0]);
                        premier=false;
                    }
                    if(doIntersect(montab[j],montab[j+1],vertex[0],vertex[1])){
                    inters=ptintersect(montab[j],montab[j+1],vertex[0],vertex[1]);
                    if(!invertex(inters,res))
                        res.push_back(inters);
                    }

                    if(doIntersect(montab[j],montab[j+4000],vertex[0],vertex[1])){
                    inters=ptintersect(montab[j],montab[j+4000],vertex[0],vertex[1]);
                    if(!invertex(inters,res))
                        res.push_back(inters);
                    }

                    if(doIntersect(montab[j+4000],montab[j+1],vertex[0],vertex[1])){
                    inters=ptintersect(montab[j+4000],montab[j+1],vertex[0],vertex[1]);
                    if(!invertex(inters,res))
                        res.push_back(inters);
                    }



                }

                double mod =fmod(j+2,4000);
                if(mod==0) j=j+1;


            }



        if(!segment1&& !segment2&& !segment3){
            res.push_front(vertex[1]);
        }
QVector<QVector3D> resfinal;
resfinal=trieintersect(vertex,res);



 return resfinal;
}
//************************************************boundsintesction*******************
QVector<float> plaquage::boundsofintersection(QVector<QVector3D> intersection){
    QVector<float> res;
    float xmin=intersection[0].x();
    float ymin=intersection[0].y();
    float xmax=intersection[0].x();
    float ymax=intersection[0].y();
    for(unsigned int i=1;i<intersection.size();++i){
        if(xmin>intersection[i].x()) xmin=intersection[i].x();
        if(ymin>intersection[i].y()) ymin=intersection[i].y();
        if(xmax<intersection[i].x()) xmax=intersection[i].x();
        if(ymax<intersection[i].y()) ymax=intersection[i].y();

    }
    res.push_back(xmin);
    res.push_back(ymin);
    res.push_back(xmax);
    res.push_back(ymax);
    return res;


}
//sort intersection ******************
QVector<QVector3D> plaquage::sortofintersection(QVector<QVector3D> intersection,QVector<QVector3D> vertex){
    QVector<QVector3D> res;
    for(unsigned int i=0;i<vertex.size();++i){
        for(unsigned int j=0;i<intersection.size();++i){

        }

    }




}
void plaquage::setmontab(QVector<QVector3D> tab){
    montab=tab;
}
//**************************************************************
QVector<QVector3D>  plaquage::trieintersect(QVector<QVector3D> vertex,QVector<QVector3D> intesct){
    QVector<QVector3D> res;


    for(unsigned int k=0;k<intesct.size();++k){
        if(isequalplanime(vertex[0],intesct[k])){
         res.push_back(intesct[k]);
            break;
        }

    }

    int indicemin;
    for(unsigned int i=0;i<res.size();++i){
        float dmin=distancetwopoints(vertex[0],vertex[1]);
        int j=0;
        for(;j<intesct.size();++j){
            float d=distancetwopoints(res[i],intesct[j]);
            if(invertex(intesct[j],res)){
                continue;

            }else
            if(d<dmin){
                dmin=d;
                indicemin=j;

            }



        }
       if(!invertex(intesct[indicemin],res)){
           if(!isequalplanime(vertex[0],intesct[indicemin]))
        res.push_back(intesct[indicemin]);
        }


    }

     if(!invertex(vertex[1],res)){
        for(unsigned int k=0;k<intesct.size();++k){
            if(isequalplanime(vertex[1],intesct[k])){
             res.push_back(intesct[k]);
                break;
            }
         }

    }


    return res;



}
//************************Zeal************
void plaquage::setZreal(QVector<QVector3D> points){
QVector<QVector3D>tabZreal;
Plan A;
QVector<float> normal;
tabZreal=getintersection(points);
int k=0;
for(int j=0;j<tabZreal.size()-3;j=j+4){
    normal=A.normale(tabZreal[j+1],tabZreal[j+2],tabZreal[j+3]);
    QVector<float> z;
    z=A.planeEquation(tabZreal[j+1],tabZreal[j],normal);
    points[k].setZ(z[2]);
    k=k+1;

}
}
