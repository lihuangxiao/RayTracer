#include "mesh.hpp"
#include <iostream>
#include <limits>


// This is mesh.cpp file
Mesh::Mesh(const std::vector<Point3D>& verts,
           const std::vector< std::vector<int> >& faces)
  : m_verts(verts),
    m_faces(faces)
{
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  std::cerr << "mesh({";
  for (std::vector<Point3D>::const_iterator I = mesh.m_verts.begin(); I != mesh.m_verts.end(); ++I) {
    if (I != mesh.m_verts.begin()) std::cerr << ",\n      ";
    std::cerr << *I;
  }
  std::cerr << "},\n\n     {";
  
  for (std::vector<Mesh::Face>::const_iterator I = mesh.m_faces.begin(); I != mesh.m_faces.end(); ++I) {
    if (I != mesh.m_faces.begin()) std::cerr << ",\n      ";
    std::cerr << "[";
    for (Mesh::Face::const_iterator J = I->begin(); J != I->end(); ++J) {
      if (J != I->begin()) std::cerr << ", ";
      std::cerr << *J;
    }
    std::cerr << "]";
  }
  std::cerr << "});" << std::endl;
  return out;
}











double finddet1(Vector3D v1, Vector3D v2, Vector3D v3) {
  double a = v1[0]*(v2[1]*v3[2] - v2[2]*v3[1]);
  double b = v2[0]*(v1[1]*v3[2] - v1[2]*v3[1]);
  double c = v3[0]*(v1[1]*v2[2] - v1[2]*v2[1]);
  return a - b + c;
}








Intersection planeintersect1(std::vector<Point3D> points, Vector3D n, Point3D eye, Point3D pixel) {
  Intersection i;
  i.exist = false;
  int numpoints = points.size();
  Point3D rp = points[0];
  double D = -n[0]*rp[0] - n[1]*rp[1] - n[2]*rp[2];
  double t = (0 - D - n[0]*eye[0] - n[1]*eye[1] - n[2]*eye[2]);
  t = t / (n[0]*(pixel[0]-eye[0]) + n[1]*(pixel[1]-eye[1]) + n[2]*(pixel[2]-eye[2]));
  if (t < 0) {
    return i;
  }
  double x = eye[0] + t*(pixel[0] - eye[0]);
  double y = eye[1] + t*(pixel[1] - eye[1]);
  double z = eye[2] + t*(pixel[2] - eye[2]);
  Point3D point1, point2, point3;
  //Point3D pointp = Point3D(x,y,z);
  bool in = false;
  for (int i = 0; i < numpoints; i++) {
    for (int j = i + 1; j < numpoints; j++) {
      for (int k = j + 1; k < numpoints; k++) {
        Point3D p0 = points[i];
        Point3D p1 = points[j];
        Point3D p2 = points[k];
        Vector3D b = Vector3D(eye[0] - p0[0], eye[1] - p0[1], eye[2] - p0[2]);
        Vector3D A1 = Vector3D(p1[0] - p0[0], p1[1] - p0[1], p1[2] - p0[2]);
        Vector3D A2 = Vector3D(p2[0] - p0[0], p2[1] - p0[1], p2[2] - p0[2]);
        Vector3D A3 = Vector3D(pixel[0] - eye[0], pixel[1] - eye[1], pixel[2] - eye[2]);
        double det = finddet1(A1, A2, A3);
        double det1 = finddet1(b, A2, A3);
        double det2 = finddet1(A1, b, A3);
        double aa = det1/det;
        double bb = det2/det;
        if ((aa >= 0) && (bb >= 0) && (aa + bb <= 1)) {
          in = true;
        }
      }
    }
  }
  if (in) {
    i.exist = true;
    i.point = Point3D(x,y,z);
    i.normal = n;
    i.distance = t;
  }
  return i;
}


/*
Intersection Mesh::boundingbox(Point3D eye, Point3D pixel) {
  // bounding box
  std::vector<Point3D>::iterator bbit;
  double xmin = INFINITY;
  double ymin = INFINITY;
  double zmin = INFINITY;
  double xmax = -INFINITY;
  double ymax = -INFINITY;
  double zmax = -INFINITY;
  for (bbit = m_verts.begin(); bbit != m_verts.end(); bbit++) {
    Point3D pp = (*bbit);
    if (pp[0] < xmin) {xmin = pp[0];}
    if (pp[0] > xmax) {xmax = pp[0];}
    if (pp[1] < ymin) {ymin = pp[1];}
    if (pp[1] > ymax) {ymax = pp[1];}
    if (pp[2] < zmin) {zmin = pp[2];}
    if (pp[2] > zmax) {zmax = pp[2];}
  }
  std::vector<Point3D> myverts;
  std::vector<int> myface1;
  std::vector<int> myface2;
  std::vector<int> myface3;
  std::vector<int> myface4;
  std::vector<int> myface5;
  std::vector<int> myface6;
  std::vector<std::vector<int> >myfaces;
  myverts.push_back(Point3D(xmin,ymin,zmin));
  myverts.push_back(Point3D(xmin,ymin,zmax));
  myverts.push_back(Point3D(xmin,ymax,zmin));
  myverts.push_back(Point3D(xmin,ymax,zmax));
  myverts.push_back(Point3D(xmax,ymin,zmin));
  myverts.push_back(Point3D(xmax,ymin,zmax));
  myverts.push_back(Point3D(xmax,ymax,zmin));
  myverts.push_back(Point3D(xmax,ymax,zmax));
  myface1.push_back(0);
  myface1.push_back(1);
  myface1.push_back(3);
  myface1.push_back(2);
  myface2.push_back(0);
  myface2.push_back(2);
  myface2.push_back(6);
  myface2.push_back(4);
  myface3.push_back(0);
  myface3.push_back(1);
  myface3.push_back(5);
  myface3.push_back(4);
  myface4.push_back(7);
  myface4.push_back(3);
  myface4.push_back(2);
  myface4.push_back(6);
  myface5.push_back(7);
  myface5.push_back(6);
  myface5.push_back(4);
  myface5.push_back(5);
  myface6.push_back(7);
  myface6.push_back(5);
  myface6.push_back(1);
  myface6.push_back(3);
  myfaces.push_back(myface1);
  myfaces.push_back(myface2);
  myfaces.push_back(myface3);
  myfaces.push_back(myface4);
  myfaces.push_back(myface5);
  myfaces.push_back(myface6);
  Mesh Mymesh = Mesh(myverts, myfaces);
  Intersection myint = Mymesh.intersect(eye,pixel);
  if (!myint.exist) {
    return i;
  }
}
*/



Intersection Mesh::intersect(Point3D eye, Point3D pixel) {
  Intersection i;
  i.exist = false;

  std::vector<Intersection> is;
  std::vector< std::vector<int> >::iterator it;


  // bounding box
  std::vector<Point3D>::iterator bbit;
  double xmin = INFINITY;
  double ymin = INFINITY;
  double zmin = INFINITY;
  double xmax = -INFINITY;
  double ymax = -INFINITY;
  double zmax = -INFINITY;

  for (bbit = m_verts.begin(); bbit != m_verts.end(); bbit++) {
    Point3D pp = (*bbit);
    if (pp[0] < xmin) {xmin = pp[0];}
    if (pp[0] > xmax) {xmax = pp[0];}
    if (pp[1] < ymin) {ymin = pp[1];}
    if (pp[1] > ymax) {ymax = pp[1];}
    if (pp[2] < zmin) {zmin = pp[2];}
    if (pp[2] > zmax) {zmax = pp[2];}
  }


  double size = fmax((xmax-xmin),fmax((ymax-ymin),(zmax-zmin)));

  // Bounding box
  NonhierBox mynh = NonhierBox(Point3D(xmin,ymin,zmin), size);
///////////////////////////////////////////////
//  bool displaybb = false;
//////////////////////////////////////////////
  Intersection myint = mynh.intersect(eye,pixel);
  if (!myint.exist) {
    return i;
///////////////////////////////////////////
//    displaybb = true;
//////////////////////////////////////////
  }
//////////////////////////////////////////   
//  return myint;
//////////////////////////////////////////


  for (it = m_faces.begin(); it != m_faces.end(); it++) {
    std::vector<Point3D> points;
    std::vector<int>::iterator intiterator;
    for (intiterator = (*it).begin(); intiterator != (*it).end(); intiterator++) {
      points.push_back(m_verts[*intiterator]);
    }
    Point3D p1 = m_verts[(*it)[0]];
    Point3D p2 = m_verts[(*it)[1]];
    Point3D p3 = m_verts[(*it)[2]];
    Vector3D v1 = Vector3D(p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]);
    Vector3D v2 = Vector3D(p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]);
    Vector3D facenormal = v1.cross(v2);
    Intersection tmpi = planeintersect1(points, facenormal, eye, pixel);
    is.push_back(tmpi);
  }
  std::vector<Intersection>::iterator it1;
  for (it1 = is.begin(); it1 != is.end(); it1++) {
    if (((*it1).exist) && ((*it1).distance >= 0)) {
      if (!i.exist) {
        i.exist = true;
        i.point = (*it1).point;
        i.normal = (*it1).normal;
        i.distance = (*it1).distance;
        //i.material = (*it).material;
      } else if (i.distance > (*it1).distance) {
        i.exist = true;
        i.point = (*it1).point;
        i.normal = (*it1).normal;
        i.distance = (*it1).distance;
        //i.material = (*it).material;
      }
    }
  }
  return i;
}

