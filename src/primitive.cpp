#include "primitive.hpp"
#include "polyroots.hpp"

Primitive::~Primitive()
{
}

//Sphere::Sphere() : n_sphere(NonhierSphere(Point3D(0.0,0.0,0.0),1.0)){
//}

Sphere::~Sphere() 
{
}




Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

NonhierBox::~NonhierBox()
{
}


Intersection NonhierSphere::intersect(Point3D eye, Point3D pixel) {
  Intersection i;
  i.exist = false;
  double roots[2];
  double A = ((pixel[0] - eye[0]) * (pixel[0] - eye[0])) +
            ((pixel[1] - eye[1]) * (pixel[1] - eye[1])) +
            ((pixel[2] - eye[2]) * (pixel[2] - eye[2]));
  double B = (pixel[0] - eye[0])*(eye[0] - m_pos[0]) +
            (pixel[1] - eye[1])*(eye[1] - m_pos[1]) +
            (pixel[2] - eye[2])*(eye[2] - m_pos[2]);
  B = B * 2;
  double C = ((eye[0] - m_pos[0]) * (eye[0] - m_pos[0])) +
            ((eye[1] - m_pos[1]) * (eye[1] - m_pos[1])) +
            ((eye[2] - m_pos[2]) * (eye[2] - m_pos[2])) -
            m_radius * m_radius;
  int size = quadraticRoots(A,B,C,roots);
  if (size > 0) {
    double t = roots[0];
    if (size == 2) {
      if ((roots[1] < 0) && (roots[0] < 0)) {
        return i;
      }
      if (roots[1] < roots[0]) {
        t = roots[1];
      }
    }
    if (t < 0) {
      return i;
    }
    i.exist = true;
    double x = eye[0] + t * (pixel[0] - eye[0]);
    double y = eye[1] + t * (pixel[1] - eye[1]);
    double z = eye[2] + t * (pixel[2] - eye[2]);
    i.point = Point3D(x,y,z);
    Vector3D normal = Vector3D(x - m_pos[0], y - m_pos[1], z - m_pos[2]);
    i.normal = normal;
    i.distance = t;
  }
  return i;
}





double finddet(Vector3D v1, Vector3D v2, Vector3D v3) {
  double a = v1[0]*(v2[1]*v3[2] - v2[2]*v3[1]);
  double b = v2[0]*(v1[1]*v3[2] - v1[2]*v3[1]);
  double c = v3[0]*(v1[1]*v2[2] - v1[2]*v2[1]);
  return a - b + c;
}



Intersection planeintersect(std::vector<Point3D> points, Vector3D n, Point3D eye, Point3D pixel) {

  Intersection i;
  i.exist = false;
  int numpoints = points.size();

  // first get the intersection point
  //solve for D, AX + BY + CZ + D = 0, use the first point
  Point3D rp = points[0];
  double D = -n[0]*rp[0] - n[1]*rp[1] - n[2]*rp[2];
  // solve for intersection point
  double t = (0 - D - n[0]*eye[0] - n[1]*eye[1] - n[2]*eye[2]);
  t = t / (n[0]*(pixel[0]-eye[0]) + n[1]*(pixel[1]-eye[1]) + n[2]*(pixel[2]-eye[2]));
  // get x y z
  if (t < 0) {
//    std::cout << "t < 0! at: " << points[0] << points[1] << points[2] << points[3];
    return i;
  }

  double x = eye[0] + t*(pixel[0] - eye[0]);
  double y = eye[1] + t*(pixel[1] - eye[1]);
  double z = eye[2] + t*(pixel[2] - eye[2]);
  // see if within plane.
  Point3D point1, point2, point3;
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
        double det = finddet(A1, A2, A3);
        double det1 = finddet(b, A2, A3);
        double det2 = finddet(A1, b, A3);
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

//  std::cout << "normal is: " << n << ";";
//  std::cout << "points are: " << points[0] << points[1] << points[2] << points[3] << ";";
//  std::cout << "pixel is: " << pixel;
//  std::cout << "result is: ";
//  if (in) {
//    std::cout << "in!";
//  } else {
//    std::cout << "out!";
//  }
//  std::cout<<std::endl;



  return i;
}


Intersection NonhierBox::intersect(Point3D eye, Point3D pixel) {
  //std::cout << "eye pixel: " << eye << pixel << std::endl;

  //bool b1, b2, b3, b4, b5, b6;
  Intersection i1, i2, i3, i4, i5, i6;
  i1.exist = false;
  i2.exist = false;
  i3.exist = false;
  i4.exist = false;
  i5.exist = false;
  i6.exist = false;

  //there are six planes we need to test each of them
  //left face x = m_pos[0];
  std::vector<Point3D> points1; // 1584
  Point3D leftfacepoint1 = m_pos;
  Point3D leftfacepoint2 = Point3D(m_pos[0], m_pos[1] + m_size, m_pos[2]);
  Point3D leftfacepoint3 = Point3D(m_pos[0], m_pos[1] + m_size, m_pos[2] + m_size);
  Point3D leftfacepoint4 = Point3D(m_pos[0], m_pos[1], m_pos[2] + m_size);
  points1.push_back(leftfacepoint1);
  points1.push_back(leftfacepoint2);
  points1.push_back(leftfacepoint3);
  points1.push_back(leftfacepoint4);
  Vector3D leftfacenormal = Vector3D(-1.0, 0.0, 0.0);
  i1 = planeintersect(points1, leftfacenormal, eye, pixel);
  //right face x = m_pos[0] + m_size;
  std::vector<Point3D> points2; //2673
  Point3D facepoint21 = Point3D(m_pos[0] + m_size, m_pos[1], m_pos[2]);
  Point3D facepoint22 = Point3D(m_pos[0] + m_size, m_pos[1] + m_size, m_pos[2]);
  Point3D facepoint23 = Point3D(m_pos[0] + m_size, m_pos[1] + m_size, m_pos[2] + m_size);
  Point3D facepoint24 = Point3D(m_pos[0] + m_size, m_pos[1], m_pos[2] + m_size);
  points2.push_back(facepoint21);
  points2.push_back(facepoint22);
  points2.push_back(facepoint23);
  points2.push_back(facepoint24);
  Vector3D rightfacenormal = Vector3D(1.0, 0.0, 0.0);
  i2 = planeintersect(points2, rightfacenormal, eye, pixel);
  //bot face y = m_pos[1];
  std::vector<Point3D> points3; //1234
  Point3D facepoint31 = Point3D(m_pos[0], m_pos[1], m_pos[2]);
  Point3D facepoint32 = Point3D(m_pos[0] + m_size, m_pos[1], m_pos[2]);
  Point3D facepoint33 = Point3D(m_pos[0] + m_size, m_pos[1], m_pos[2] + m_size);
  Point3D facepoint34 = Point3D(m_pos[0], m_pos[1], m_pos[2] + m_size);
  points3.push_back(facepoint31);
  points3.push_back(facepoint32);
  points3.push_back(facepoint33);
  points3.push_back(facepoint34);
  Vector3D botfacenormal = Vector3D(0.0, -1.0, 0.0);
  i3 = planeintersect(points3, botfacenormal, eye, pixel);
  //top face y = m_pos[1] + m_size
  std::vector<Point3D> points4; //5678
  Point3D facepoint41 = Point3D(m_pos[0], m_pos[1] + m_size, m_pos[2]);
  Point3D facepoint42 = Point3D(m_pos[0] + m_size, m_pos[1] + m_size, m_pos[2]);
  Point3D facepoint43 = Point3D(m_pos[0] + m_size, m_pos[1] + m_size, m_pos[2] + m_size);
  Point3D facepoint44 = Point3D(m_pos[0], m_pos[1] + m_size, m_pos[2] + m_size);
  points4.push_back(facepoint41);
  points4.push_back(facepoint42);
  points4.push_back(facepoint43);
  points4.push_back(facepoint44);
  Vector3D topfacenormal = Vector3D(0.0, 1.0, 0.0);
  i4 = planeintersect(points4, topfacenormal, eye, pixel);
  //back face z = m_pos[2];
  std::vector<Point3D> points5; // 1265
  Point3D facepoint51 = Point3D(m_pos[0], m_pos[1], m_pos[2]);
  Point3D facepoint52 = Point3D(m_pos[0] + m_size, m_pos[1], m_pos[2]);
  Point3D facepoint53 = Point3D(m_pos[0] + m_size, m_pos[1] + m_size, m_pos[2]);
  Point3D facepoint54 = Point3D(m_pos[0], m_pos[1] + m_size, m_pos[2]);
  points5.push_back(facepoint51);
  points5.push_back(facepoint52);
  points5.push_back(facepoint53);
  points5.push_back(facepoint54);
  Vector3D backfacenormal = Vector3D(0.0, 0.0, -1.0);
  i5 = planeintersect(points5, backfacenormal, eye, pixel);

  //front face z = m_pos[2] + m_size;
  std::vector<Point3D> points6; //4378
  Point3D facepoint61 = Point3D(m_pos[0], m_pos[1], m_pos[2] + m_size);
  Point3D facepoint62 = Point3D(m_pos[0] + m_size, m_pos[1], m_pos[2] + m_size);
  Point3D facepoint63 = Point3D(m_pos[0] + m_size, m_pos[1] + m_size, m_pos[2] + m_size);
  Point3D facepoint64 = Point3D(m_pos[0], m_pos[1] + m_size, m_pos[2] + m_size);
  points6.push_back(facepoint61);
  points6.push_back(facepoint62);
  points6.push_back(facepoint63);
  points6.push_back(facepoint64);
  Vector3D frontfacenormal = Vector3D(0.0, 0.0, 1.0);
  i6 = planeintersect(points6, frontfacenormal, eye, pixel);

  //std::cout<<std::endl;

  Intersection i;
  i.exist = false;

  std::vector<Intersection> is;
  is.push_back(i1);
  is.push_back(i2); 
  is.push_back(i3); 
  is.push_back(i4); 
  is.push_back(i5); 
  is.push_back(i6);
  std::vector<Intersection>::iterator it;
//  std::cout << "left right bot top back front distances are: ";
//  std::cout << i1.distance << "; ";
//  std::cout << i2.distance << "; ";
//  std::cout << i3.distance << "; ";
//  std::cout << i4.distance << "; ";
//  std::cout << i5.distance << "; ";
//  std::cout << i6.distance << "; ";
//  std::cout << std::endl;
  for (it = is.begin(); it != is.end(); it++) {
    if (((*it).exist) && ((*it).distance >= 0)) {
      if (!i.exist) {
        i.exist = true;
        i.point = (*it).point;
        i.normal = (*it).normal;
        i.distance = (*it).distance;
        //i.material = (*it).material;
      } else if (i.distance > (*it).distance) {
        i.exist = true;
        i.point = (*it).point;
        i.normal = (*it).normal;
        i.distance = (*it).distance;
        //i.material = (*it).material;
      }
    }

  }
  return i;  













}

Intersection Sphere::intersect(Point3D eye, Point3D pixel) {
  Intersection i;
  i.exist = false;
  i = nh_sphere.intersect(eye, pixel);
  return i;
}

Intersection Cube::intersect(Point3D eye, Point3D pixel) {
  Intersection i;
  i.exist = false;
  i = nh_box.intersect(eye,pixel);
  return i;
}

Intersection Primitive::intersect(Point3D eye, Point3D pixel) {
  (void)eye;
  (void)pixel;

  Intersection i;
  i.exist = false;
  return i;
}















// final project: extra primitives!
Cone::~Cone()
{
}
Cylinder::~Cylinder()
{
}


Intersection unitCircleIntersect(Point3D eye, Point3D pixel, int ycor) {
  Intersection i;
  i.exist = false;
  i.distance = INFINITY;
  double t;
  if ((pixel[1] - eye[1]) != 0) {
    t = (ycor - eye[1]) / (pixel[1] - eye[1]);
  } else {
    return i;
  }
  if (t < 0) {
    return i;
  }
  double x = eye[0] + t * (pixel[0] - eye[0]);
  double y = eye[1] + t * (pixel[1] - eye[1]);
  double z = eye[2] + t * (pixel[2] - eye[2]);
  if ((x*x + z*z) <= 1) {
    i.exist = true;
    i.distance = t;
    i.point = Point3D(x,y,z);
    if (ycor == 0) {
      i.normal = Vector3D(0.0, -1.0, 0.0);
    } else if (ycor == 1) {
      i.normal = Vector3D(0.0, 1.0, 0.0);
    }
  }
  return i;
}






Intersection Cone::intersect(Point3D eye, Point3D pixel) {
  Intersection i;
  i.exist = false;
  double roots[2];
  double A = ((pixel[0] - eye[0]) * (pixel[0] - eye[0])) -
            ((pixel[1] - eye[1]) * (pixel[1] - eye[1])) +
            ((pixel[2] - eye[2]) * (pixel[2] - eye[2]));
  double B = (pixel[0] - eye[0]) * eye[0] -
            (pixel[1] - eye[1]) * eye[1] +
            (pixel[2] - eye[2]) * eye[2];
  B = B * 2;
  double C = (eye[0] * eye[0]) -
             (eye[1] * eye[1]) +
             (eye[2] * eye[2]);
  int size = quadraticRoots(A,B,C,roots);
  if (size > 0) {
    double t = roots[0];
    if (size == 2) {
      if ((roots[1] < 0) && (roots[0] < 0)) {
      } else {
        if (roots[1] < roots[0]) {
          t = roots[1];
        }
      }
    }
    if (t < 0) {
    } else {
      double x = eye[0] + t * (pixel[0] - eye[0]);
      double y = eye[1] + t * (pixel[1] - eye[1]);
      double z = eye[2] + t * (pixel[2] - eye[2]);
      if ((y > 1) || (y < 0)) {
      } else {
        i.point = Point3D(x,y,z);
        Point3D botPoint;
        if (z >= 0) {
          botPoint = Point3D(x, 0, sqrt(1 - x*x));
        } else {
          botPoint = Point3D(x, 0, -sqrt(1 - x*x));
        }
        Vector3D normal = Vector3D((x+0)/2, -0.5, sqrt(1-(x*x))/2);
        normal.normalize();
        i.normal = normal;
        i.distance = t;
        i.exist = true;
      }
    }
  }
  Intersection i2;
  i2.exist = false;
  i2 = unitCircleIntersect(eye, pixel, 1);
  if (!i.exist) {
    return i2;
  }
  if (!i2.exist) {
    return i;
  }
  if (i2.distance <= i.distance){
    return i2;
  }
  return i;
}


Intersection Cylinder::intersect(Point3D eye, Point3D pixel) {
  Intersection i1;
  i1.exist = false;
  i1.distance = INFINITY;
  Intersection i2;
  i2.exist = false;
  i2.distance = INFINITY;
  i1 = unitCircleIntersect(eye, pixel, 0);
  i2 = unitCircleIntersect(eye, pixel, 1);

  Intersection i;
  i.exist = false;
  i.distance = INFINITY;

  double roots[2];
  double A = ((pixel[0] - eye[0]) * (pixel[0] - eye[0])) +
             ((pixel[2] - eye[2]) * (pixel[2] - eye[2]));
  double B = (pixel[0] - eye[0]) * eye[0] +
             (pixel[2] - eye[2]) * eye[2];
  B = B * 2;
  double C = (eye[0] * eye[0]) +
             (eye[2] * eye[2]) - 1;
  int size = quadraticRoots(A,B,C,roots);
  if (size > 0) {
    double t = roots[0];
    if (size == 2) {
      if (roots[1] < roots[0]) {
        t = roots[1];
      }
    }
    if (!(t < 0)) {
      double x = eye[0] + t * (pixel[0] - eye[0]);
      double y = eye[1] + t * (pixel[1] - eye[1]);
      double z = eye[2] + t * (pixel[2] - eye[2]);
      if ((y<=1) && (y>=0)) {
        i.exist = true;
        i.distance = t;
        i.normal = Vector3D(x,0,z);
        i.point = Point3D(x,y,z);
      }
    }
  }

//  if (!(i.exist) || (i1.exist) || (i2.exist)) {
//    std::cout << i.distance << " " << i1.distance << " " << i2.distance << std::endl;
//  }


  if ((i.distance <= i1.distance) && (i.distance <= i2.distance)) {
    return i;
  } 
  if ((i1.distance <= i.distance) && (i1.distance <= i2.distance)) {
    return i1;
  }
  if ((i2.distance <= i1.distance) && (i2.distance <= i.distance)) {
    return i2;
  }









  return i;
}



