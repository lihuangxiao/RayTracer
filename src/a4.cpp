#include "a4.hpp"
#include "image.hpp"
//#include <algorithm>
//#include <math.h>
#include <cmath>
#include <math.h>



void a4_render(// What to render
               SceneNode* root,
               // Where to output the image
               const std::string& filename,
               // Image size
               int width, int height,
               // Viewing parameters
               const Point3D& eye, const Vector3D& view,
               const Vector3D& up, double fov,
               // Lighting parameters
               const Colour& ambient,
               const std::list<Light*>& lights
               )
{
  // Fill in raytracing code here.
  std::cerr << "Stub: a4_render(" << root << ",\n     "
            << filename << ", " << width << ", " << height << ",\n     "
            << eye << ", " << view << ", " << up << ", " << fov << ",\n     "
            << ambient << ",\n     {";
  for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I) {
    if (I != lights.begin()) std::cerr << ", ";
    std::cerr << **I;
  }
  std::cerr << "});" << std::endl;



  Vector3D view2 = view;
  view2.normalize();
  Point3D pixelcenterpoint = Point3D(eye[0] + view2[0], eye[1] + view2[1], eye[2] + view2[2]);
  Vector3D centertoright = view.cross(up);// or left? need to make sure.
  centertoright[0] = abs(centertoright[0]);
  Vector3D centertotop = up;
  centertoright.normalize();
  centertotop.normalize();

  //std:: cout << view2 << pixelcenterpoint << centertoright << centertotop << std::endl;

  Image img(width, height, 3);

  double angle = fov * M_PI / 360;
  double w_co = tan(angle) * 2 / width;
  double h_co = tan(angle) * 2 / height;

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        if (x == (9*width/10) &&(y==0)) {
          std::cout << "90% completed!" <<std::endl;
        } else if (x == (8*width/10) &&(y==0)) {
          std::cout << "80% completed!" <<std::endl;
        } else if (x == (7*width/10) &&(y==0)) {
          std::cout << "70% completed!" <<std::endl;
        } else if (x == (6*width/10) &&(y==0)) {
          std::cout << "60% completed!" <<std::endl;
        } else if (x == (5*width/10) &&(y==0)) {
          std::cout << "50% completed!" <<std::endl;
        } else if (x == (4*width/10) &&(y==0)) {
          std::cout << "40% completed!" <<std::endl;
        } else if (x == (3*width/10) &&(y==0)) {
          std::cout << "30% completed!" <<std::endl;
        } else if (x == (2*width/10) &&(y==0)) {
          std::cout << "20% completed!" <<std::endl;
        } else if (x == (1*width/10) &&(y==0)) {
          std::cout << "10% completed!" <<std::endl;
        } else {}
          float xf, yf;
          for (xf = x + 0.25; xf < x + 0.99; xf += 0.25) {
            for (yf = y + 0.25; yf < y + 0.99; yf += 0.25) {
              double pixelpointx = pixelcenterpoint[0] + 
                                  (xf-(width/2)) * w_co * centertoright[0] -
                                  (yf-(height/2)) * h_co * centertotop[0];
              double pixelpointy = pixelcenterpoint[1] +
                                  (xf-(width/2)) * w_co * centertoright[1] -
                                  (yf-(height/2)) * h_co * centertotop[1];
              double pixelpointz = pixelcenterpoint[2] +
                                  (xf-(width/2)) * w_co * centertoright[2] -
                                  (yf-(height/2)) *h_co * centertotop[2];
              Point3D pixelpoint = Point3D(pixelpointx, pixelpointy, pixelpointz);
              Intersection i = root->intersect(eye, pixelpoint);
              if (i.exist) {
                i.normal.normalize();
                double R = 0;
                double G = 0;
                double B = 0;
                // ambient lighting
                R += ambient.R() * i.material->get_kd1();
                G += ambient.G() * i.material->get_kd2();
                B += ambient.B() * i.material->get_kd3();
                for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I) {
                  Point3D lightposition = (*I)->position;
                  Colour lightcolour = (*I)->colour;
                  Vector3D Lin = Vector3D(lightposition[0] - i.point[0],
                                          lightposition[1] - i.point[1],
                                          lightposition[2] - i.point[2]);
                  // lambertian lighting
                  Lin.normalize();
                  double costheta = Lin.dot(i.normal);
                  Intersection tmpinter;
                  tmpinter = root->intersect(lightposition, i.point);
                  if ((tmpinter.exist) && ((tmpinter.distance < 0.9999) && (tmpinter.distance > 0.0001))) {
                  } else {
//                     R += lightcolour.R()/* * fmax(costheta, 0) */* i.material->get_kd1();
//                     G += lightcolour.G()/* * fmax(costheta, 0) */* i.material->get_kd2();
//                     B += lightcolour.B()/* * fmax(costheta, 0) */* i.material->get_kd3();
                     R += lightcolour.R() * fmax(costheta, 0) * i.material->get_kd1();
                     G += lightcolour.G() * fmax(costheta, 0) * i.material->get_kd2();
                     B += lightcolour.B() * fmax(costheta, 0) * i.material->get_kd3();


                  }
                  // specular lighting, normal*costheta*2 - Lin
                  Vector3D eyein = Vector3D(eye[0] - i.point[0], eye[1] - i.point[1], eye[2] - i.point[2]);
                  double cosen = eyein.dot(i.normal);
                  Vector3D Lout = Vector3D(2*(i.normal[0])*cosen - eyein[0],
                                           2*(i.normal[1])*cosen - eyein[1],
                                           2*(i.normal[2])*cosen - eyein[2]);
                  Lout.normalize();
                  double cosalpha = Lout.dot(Lin);
                  if (costheta < 0) {
                    cosalpha = 0;
                  } else if (cosen < 0) {
                    cosalpha = 0;
                  } else {
                  }
                  if ((tmpinter.exist) &&((tmpinter.distance < 0.99) && (tmpinter.distance > 0.01))) {
                  } else {
                    R += lightcolour.R() * pow((fmax(0, cosalpha)), (i.material->get_m_shininess())) * i.material->get_ks1();
                    G += lightcolour.G() * pow((fmax(0, cosalpha)), (i.material->get_m_shininess())) * i.material->get_ks2();
                    B += lightcolour.B() * pow((fmax(0, cosalpha)), (i.material->get_m_shininess())) * i.material->get_ks3();
                  }
                }
                img(x,y,0) += R;
                img(x,y,1) += G;
                img(x,y,2) += B;
              } else {
                img(x,y,0)+=1; //+= (double)y/(double)height-(double)x/5/(double)height;
                img(x,y,1)+=1; //+= (double)y/(double)height-(double)x/5/(double)height;
                img(x,y,2)+=1; //+= (double)y/(double)height-(double)x/5/(double)height;
              }
            }
          }
          img(x,y,0) = img(x,y,0)/9;
          img(x,y,1) = img(x,y,1)/9;
          img(x,y,2) = img(x,y,2)/9;
        }
  }
  img.savePng(filename);
}
