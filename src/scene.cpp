#include "scene.hpp"
#include <iostream>



double get_distance (Point3D p1, Point3D p2) {
  double ret1 = (p2[0] - p1[0])*(p2[0] - p1[0]);
  double ret2 = (p2[1] - p1[1])*(p2[1] - p1[1]);
  double ret3 = (p2[2] - p1[2])*(p2[2] - p1[2]);
  double ret = ret1 + ret2 + ret3;
  ret = sqrt(ret);
  return ret;
}



Intersection SceneNode::intersect(Point3D eye, Point3D pixel) {
//////////////////////////////////hirar code
  Point3D eye2 = m_invtrans * eye;
  Point3D pixel2 = m_invtrans * pixel;
////////////////////////////////////////////
  Intersection i;
  i.exist = false;
  // assumes non -hirarchical geonodes are right under
  std::list<SceneNode*>::iterator it;
  for (it = m_children.begin(); it != m_children.end(); ++it) {
    Intersection ii = (*it)->intersect(eye2, pixel2);
/////////////////////////////////hirar code
    if (ii.exist) {
      ii.point = m_trans * ii.point;
      Point3D myeye = m_trans * eye2;
      Point3D mypixel = m_trans * pixel2;
      ii.distance = (get_distance(ii.point, eye) / get_distance(pixel, eye));
      Matrix4x4 myinv = m_invtrans;
      ii.normal = myinv.transpose() * ii.normal;
//      ii.normal.normalize();
    }
///////////////////////////////////////////
    if (ii.exist) {
      if (!i.exist) {
        i.exist = true;
        i.point = ii.point;
        i.normal = ii.normal;
        i.material = ii.material;
        i.distance = ii.distance;
      } else if (i.distance > ii.distance) {
        i.exist = true;
        i.point = ii.point;
        i.normal = ii.normal;
        i.material = ii.material;
        i.distance = ii.distance;
      }
      if (ii.distance < 0) {
        std::cout << "wtf!" <<std::endl;
      }
    }
    // assumes only one object atm
    //i = (*it)->intersect(eye, pixel);
  }

  return i;
}


Intersection GeometryNode::intersect(Point3D eye, Point3D pixel) {
//////////////////////////////////hirar code
  Point3D eye2 = m_invtrans * eye;
  Point3D pixel2 = m_invtrans * pixel;
////////////////////////////////////////////
  Intersection ii = m_primitive->intersect(eye2, pixel2);
/////////////////////////////////hirar code
    if (ii.exist) {
      ii.point = m_trans * ii.point;
      Point3D myeye = m_trans * eye2;
      Point3D mypixel = m_trans * pixel2;
      ii.distance = (get_distance(ii.point, myeye) / get_distance(mypixel, myeye));
      Matrix4x4 myinv = m_invtrans;
      ii.normal = myinv.transpose() * ii.normal;
//      ii.normal.normalize();
    }
///////////////////////////////////////////
  if (ii.exist) {
    ii.material = m_material;
  }
  return ii;
}

Intersection JointNode::intersect(Point3D eye, Point3D pixel) {
  Intersection i;
  i.exist = false;
//////////////////////////////////hirar code
  Point3D eye2 = m_invtrans * eye;
  Point3D pixel2 = m_invtrans * pixel;
////////////////////////////////////////////
  std::list<SceneNode*>::iterator it;
  for (it = m_children.begin(); it != m_children.end(); ++it) {
    Intersection ii = (*it)->intersect(eye2, pixel2);
/////////////////////////////////hirar code
    if (ii.exist) {
      ii.point = m_trans * ii.point;
      Point3D myeye = m_trans * eye2;
      Point3D mypixel = m_trans * pixel2;
      ii.distance = (get_distance(ii.point, myeye) / get_distance(mypixel, myeye));
      Matrix4x4 myinv = m_invtrans;
      ii.normal = myinv.transpose() * ii.normal;
//      ii.normal.normalize();
    }
///////////////////////////////////////////
    if (ii.exist) {
      if (!i.exist) {
        i.exist = true;
        i.point =  ii.point;
        i.normal =  ii.normal;
        i.material = ii.material;
        i.distance = ii.distance;
      } else if (i.distance > ii.distance) {
        i.exist = true;
        i.point = ii.point;
        i.normal = ii.normal;
        i.material = ii.material;
        i.distance = ii.distance;
      }
    }
  }
  return i;
}










SceneNode::SceneNode(const std::string& name)
  : m_name(name)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::rotate(char axis, double angle)
{
  Vector4D v1, v2, v3, v4;
  angle = (angle / 180.0) * M_PI;
  float cosine = cos(angle);
  float sine = sin(angle);
  v4 = Vector4D(0.0, 0.0, 0.0, 1.0);
  switch(axis) {
    case 'x':
      v1 = Vector4D(1.0, 0.0, 0.0, 0.0);
      v2 = Vector4D(0.0, cosine, -sine, 0.0);
      v3 = Vector4D(0.0, sine, cosine, 0.0);
      break;
    case 'z':
      v1 = Vector4D(cosine, -sine, 0.0, 0.0);
      v2 = Vector4D(sine, cosine, 0.0, 0.0);
      v3 = Vector4D(0.0, 0.0, 1.0, 0.0);
      break;
    case 'y':
      v1 = Vector4D(cosine, 0.0, sine, 0.0);
      v2 = Vector4D(0.0, 1.0, 0.0, 0.0);
      v3 = Vector4D(-sine, 0.0, cosine, 0.0);
      break;
    default:
      break;
  }
  Matrix4x4 transM = Matrix4x4(v1, v2, v3, v4);
  set_transform(m_trans * transM);
}

void SceneNode::scale(const Vector3D& amount)
{
  float x_scale = amount[0];
  float y_scale = amount[1];
  float z_scale = amount[2];

  Vector4D v1 = Vector4D(x_scale, 0.0f, 0.0f, 0.0f);
  Vector4D v2 = Vector4D(0.0f, y_scale, 0.0f, 0.0f);
  Vector4D v3 = Vector4D(0.0f, 0.0f, z_scale, 0.0f);
  Vector4D v4 = Vector4D(0.0f, 0.0f, 0.0f, 1.0f);
  Matrix4x4 transM = Matrix4x4(v1, v2, v3, v4);
  set_transform(m_trans * transM);
}

void SceneNode::translate(const Vector3D& amount)
{
  Vector4D v1 = Vector4D(1.0f, 0.0f, 0.0f, amount[0]);
  Vector4D v2 = Vector4D(0.0f, 1.0f, 0.0f, amount[1]);
  Vector4D v3 = Vector4D(0.0f, 0.0f, 1.0f, amount[2]);
  Vector4D v4 = Vector4D(0.0f, 0.0f, 0.0f, 1.0f);
  Matrix4x4 transM = Matrix4x4(v1, v2, v3, v4);
  set_transform(m_trans * transM);
}

bool SceneNode::is_joint() const
{
  return false;
}

JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
}

JointNode::~JointNode()
{
}

bool JointNode::is_joint() const
{
  return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
  m_joint_x.min = min;
  m_joint_x.init = init;
  m_joint_x.max = max;
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;
  m_joint_y.max = max;
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
}
 
