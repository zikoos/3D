#include "objet.h"
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<QVector3D>
#include<plaquage.h>
#include<global.h>
#include <mnt.h>
#include<math.h>


using namespace std;

objet::objet(){
}

objet::~objet(){

}


void objet::loadobjet(const string &pathfile){
    // vider les 3 tableaux
    sommets.clear();
    normals.clear();
    index.clear();

    //initialisation du chargeur
    Assimp::Importer import3D;
    // initialisation de l'objet qui va avoir les données chargées
    const aiScene* scene = import3D.ReadFile(pathfile, aiProcess_Triangulate | aiProcess_SortByPType);
    // vertex, texture et normal de l'objet 3D

    if(scene){

            if(scene->HasMeshes())
            {
                for(unsigned int i=0; i<scene->mNumMeshes; ++i)
                {
                    getData(scene->mMeshes[i]);
                    adapterObjet();

                }
            }
    }

    else{
        qDebug() << "Error loading file: (assimp:) " << import3D.GetErrorString();

    }
}

void objet::getData(aiMesh *objet){

    int vertindexoffset = sommets.size()/3;
    xMin = objet->mVertices[0].x;
    yMin = objet->mVertices[0].y;
    zMin = objet->mVertices[0].z;
    xMax = objet->mVertices[0].x;
    yMax = objet->mVertices[0].y;
    zMax = objet->mVertices[0].z;
    //  Vertices
        if(objet->mNumVertices > 0)
        {
            for(uint i=0; i<objet->mNumVertices; ++i)  //objet->mNumVertices
            {
                aiVector3D &vec = objet->mVertices[i];

                sommets.push_back(vec.x);
                //cout << "point : " << vec.x << endl;

                if (vec.x < xMin){
                    xMin =  vec.x;

                }
                if(vec.x > xMax){
                 xMax  = vec.x;
                }
                sommets.push_back(vec.y);
                //cout << "point1 : " << vec.y << endl;

                if(vec.y < yMin){
                    yMin = vec.y;
                }
                if(vec.y > yMax){
                    yMax = vec.y;
                }
                sommets.push_back(vec.z);
                //cout << "point 2 : " << vec.z << endl;

                if(vec.z < zMin){
                    zMin = vec.z;
                }
                if(vec.z > zMax){
                    zMax = vec.z;

                }
            }
        }
        //  Normals
        if(objet->HasNormals())
        {
            normals.resize(sommets.size());

            int nind = vertindexoffset * 3;

            for(uint j=0; j<objet->mNumVertices; ++j)
            {
                aiVector3D &vec = objet->mNormals[j];
                normals[nind] = vec.x;
                normals[nind+1] = vec.y;
                normals[nind+2] = vec.z;
                nind += 3;
            };
        }
        //  indexes
        for(uint t = 0; t<objet->mNumFaces; ++t)
        {
            aiFace* face = &objet->mFaces[t];
            if(face->mNumIndices != 3)
            {
                qDebug() << "Warning: 3 indices, ignoring this primitive." << face->mNumIndices;
                continue;
            }

            index.push_back(face->mIndices[0]+vertindexoffset);
            index.push_back(face->mIndices[1]+vertindexoffset);
            index.push_back(face->mIndices[2]+vertindexoffset);
        }
}

void objet::drawobjet(){

    if (!sommets.isEmpty()){

            glClear(GL_DEPTH_BUFFER_BIT);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);

            glVertexPointer(3,GL_FLOAT,0,sommets.constData());

            glNormalPointer(GL_FLOAT,0,normals.constData());

            glDrawElements(GL_TRIANGLES,index.size(),GL_UNSIGNED_INT,index.constData());
            //glDrawArrays(GL_POLYGON,0,sommets.size());
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);

    }

}


float objet::getxMax(){
        return abs(xMax);
}

float objet::getyMax(){

     return abs(yMax);
}

float objet::getzMax(){

    return abs(zMax);
}

float objet::getxMin(){

    return xMin;
}

float objet::getyMin(){

    return yMin;
}

float objet::getzMin(){

    return zMin;
}

//******* le tableau d'intersection d'un segment avec l'MNT
void objet::segment_intersection()
{
    QVector<QVector3D>  interspoints,interspoints1,interspoints2,interspoints3;
    interspoints = plaquageteste.findintersectpoint(segmentAB,mntteste.getmontab());
    plaquercube(segmentAB, interspoints);

    interspoints1 = plaquageteste.findintersectpoint(segmentBC,mntteste.getmontab());
    plaquercube(segmentBC, interspoints1);

    interspoints2 = plaquageteste.findintersectpoint(segmentCD,mntteste.getmontab());
    plaquercube(segmentCD, interspoints2);

    interspoints3 = plaquageteste.findintersectpoint(segmentDA,mntteste.getmontab());

    plaquercube(segmentDA, interspoints3);

}

//*******plaquagecube
void objet::plaquercube(QVector<QVector3D> segment,QVector<QVector3D>  interspoints){




    for(size_t i=0;i<tabcube.size()-1;i++){



        if(plaquageteste.isequalplanime(tabcube[i],segment[0])  && plaquageteste.isequalplanime(tabcube[i+1],segment[1]) ){

            tabcube[i].setX(interspoints[0].x());
            tabcube[i].setY(interspoints[0].y());
            tabcube[i].setZ(interspoints[0].z());
            int j=1;
            for(;j<interspoints.size()-1;j++){

                tabcube.insert(tabcube.begin()+i+j, interspoints[j]);
            }
            tabcube[i+j].setX(interspoints[interspoints.size()-1].x());
            tabcube[i+j].setY(interspoints[interspoints.size()-1].y());
            tabcube[i+j].setZ(interspoints[interspoints.size()-1].z());

        }

    }


}
//*****plaquer objet
void objet::plaquerobjet(){
    QVector<QVector3D> base;
    QVector<QVector3D> basemnt;
    QVector3D bol;

    bool premier=true;
    for(unsigned int i=0;i<sommets.size()-2;i=i+3){
        if(sommets[i+2]==zMin){
            bol.setX(sommets[i]);
            bol.setY(sommets[i+1]);
            bol.setZ(sommets[i+2]);
            if(premier){
                base.push_back(bol);
                premier=false;
            }else
            if(!insommets(bol,base))
             base.push_back(bol);


        }
    }
     QVector<QVector3D>  mnttest=mntteste.getmontab();
     QVector3D p1(mnttest[0].x(),mnttest[0].y(),mnttest[0].z());
     QVector3D p2(mnttest[1].x(),mnttest[1].y(),mnttest[1].z());
     QVector3D p3(mnttest[4001].x(),mnttest[4001].y(),mnttest[4001].z());
     QVector3D p4(mnttest[4000].x(),mnttest[4000].y(),mnttest[4000].z());
     basemnt.push_back(p1);
     basemnt.push_back(p2);
     basemnt.push_back(p3);
     basemnt.push_back(p4);
     float k=0.2;
     float cote =qAbs(p1.x()-p2.x());

     for(size_t i=0;i<=sommets.size()-2;i=i+3){

        for(size_t j=0;j<base.size();++j){
                float dif1=qAbs(base[j].x()-sommets[i]);
                float dif2=qAbs(base[j].y()-sommets[i+1]);


                if(dif1<=k&&dif2<=k&&base[j].z()==sommets[i+2]){

                    sommets_plaquage.push_back(basemnt[j].x());
                    sommets_plaquage.push_back(basemnt[j].y());
                    sommets_plaquage.push_back(basemnt[j].z());

                }else
                if(dif1<=k&&dif2<=k){
                    sommets_plaquage.push_back(basemnt[j].x());
                    sommets_plaquage.push_back(basemnt[j].y());
                    sommets_plaquage.push_back(cote+basemnt[j].z());

                }

            }
    }
}


void objet::drawobjetcouper(){

    if (!sommets_plaquage.isEmpty()){
            glClear(GL_DEPTH_BUFFER_BIT);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);

            glVertexPointer(3,GL_FLOAT,0,sommets_plaquage.constData());

            glNormalPointer(GL_FLOAT,0,normals.constData());

            glDrawElements(GL_TRIANGLES,index.size(),GL_UNSIGNED_INT,index.constData());
            //glDrawArrays(GL_POLYGON,0,sommets.size());
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);

    }

}

void objet::drawobjetfinal(){

        glDisable(GL_LIGHTING);
        //glColor3b(1,0,0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, tabcube.constData());
        glDrawArrays(GL_LINE_LOOP,0,tabcube.size() );
        glDisableClientState(GL_VERTEX_ARRAY);

}

bool objet::insommets(QVector3D p,QVector<QVector3D> vertex){

    bool in=false;
    int epsilon=0;
    float dif1,dif2;
    for(unsigned int i=0;i<vertex.size();i++){
        dif1=qAbs(p.x()-vertex[i].x());
        dif2=qAbs(p.y()-vertex[i].y());
        if( dif1<=epsilon && dif2<=epsilon   ){
            in=true;
            break;
        }
    }
    return in;
}

void objet:: adapterObjet() //float x, float y, float z)

{
    //900000.00 1944975.00 1073.00
    float x=900015, y=1944965, z=1073;
    float width=25, height=25, length=25;

    QVector3D A(x+width,y-height,z), B(x+width,y,z), C(x,y,z), D(x,y-height,z), E(x+width,y-height,z+length), F(x,y-height,z+length), G(x,y,z+length), H(x+width,y,z+length);
   //QVector3D testA(900000,1944980,1073),testB(900025,1944980,1073);
            tabcube.push_back(H);
            tabcube.push_back(B);
            tabcube.push_back(C);
            tabcube.push_back(G);
            tabcube.push_back(H);
            tabcube.push_back(E);
            tabcube.push_back(F);
            tabcube.push_back(D);
            tabcube.push_back(A);
            tabcube.push_back(E);
            tabcube.push_back(F);
            tabcube.push_back(G);
            tabcube.push_back(C);
            tabcube.push_back(D);
            tabcube.push_back(A);
            tabcube.push_back(B);


            //plaquageteste.setZreal(tabcube);


            //segmentAB.push_back(testA);
            //segmentAB.push_back(testB);

            segmentAB.push_back(A);
            segmentAB.push_back(B);

            segmentBC.push_back(B);
            segmentBC.push_back(C);

            segmentCD.push_back(C);
            segmentCD.push_back(D);

            segmentDA.push_back(D);
            segmentDA.push_back(A);

            segment_intersection();
}


