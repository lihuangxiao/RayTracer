#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"
#include <vector>

class Primitive {
public:
  virtual ~Primitive();

  virtual Intersection intersect(Point3D eye, Point3D pixel);

  int id;
};
/**
class Sphere : public Primitive {
public:
  virtual ~Sphere();
  virtual Intersection intersect(Point3D eye, Point3D pixel);

  NonhierSphere n_sphere;
};

class Cube : public Primitive {
public:
  virtual ~Cube();
  virtual Intersection intersect(Point3D eye, Point3D pixel);
  
  NohierBox nh_box;
};
**/
class NonhierSphere : public Primitive {
public:
  NonhierSphere(const Point3D& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual Intersection intersect(Point3D eye, Point3D pixel);


private:
  Point3D m_pos;
  double m_radius;
};


class Sphere : public Primitive {
public:
  Sphere():nh_sphere(NonhierSphere(Point3D(0.0,0.0,0.0), 1.0)){}
  virtual ~Sphere();
  virtual Intersection intersect(Point3D eye, Point3D pixel);

  NonhierSphere nh_sphere;
};














class NonhierBox : public Primitive {
public:
  NonhierBox(const Point3D& pos, double size)
    : m_pos(pos), m_size(size)
  {
  }
  
  virtual ~NonhierBox();
  virtual Intersection intersect(Point3D eye, Point3D pixel);


private:
  Point3D m_pos;
  double m_size;
};


class Cube : public Primitive {
public:
  Cube():nh_box(NonhierBox(Point3D(0.0,0.0,0.0), 1.0)){}
  virtual ~Cube();
  virtual Intersection intersect(Point3D eye, Point3D pixel);
  
  NonhierBox nh_box;
};


















// final project: extra primitives!
class Cone : public Primitive {
public:
  Cone(const Point3D& pos, double radius, double height)
    : m_pos(pos), m_radius(radius), m_height(height)
  {
  }
  Cone()
    : m_pos(Point3D(0.0, 0.0, 0.0)), m_radius(1.0), m_height(1.0)
  {
  }
  virtual ~Cone();
  virtual Intersection intersect(Point3D eye, Point3D pixel);

private:
  Point3D m_pos;
  double m_radius;
  double m_height;
};


class Cylinder : public Primitive {
public:
  Cylinder(const Point3D& pos, double radius, double height)
    : m_pos(pos), m_radius(radius), m_height(height)
  {
  }
  Cylinder()
    : m_pos(Point3D(0.0, 0.0, 0.0)), m_radius(1.0), m_height(1.0)
  {
  }
  virtual ~Cylinder();
  virtual Intersection intersect(Point3D eye, Point3D pixel);


private:
  Point3D m_pos;
  double m_radius;
  double m_height;
};




#endif
