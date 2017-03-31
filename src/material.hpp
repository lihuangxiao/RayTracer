#ifndef CS488_MATERIAL_HPP
#define CS488_MATERIAL_HPP

#include "algebra.hpp"

class Material {
public:
  virtual ~Material();
//  virtual void apply_gl() const = 0;
  virtual void print() {}

  virtual double get_ks1() {return 0.0;}
  virtual double get_ks2() {return 0.0;}
  virtual double get_ks3() {return 0.0;}

  virtual double get_kd1(){return 0.0;}
  virtual double get_kd2(){return 0.0;}
  virtual double get_kd3(){return 0.0;}


  virtual Colour get_m_kd() {return Colour(0.0,0.0,0.0);}
  virtual Colour get_m_ks() {return Colour(0.0,0.0,0.0);}
  virtual double get_m_shininess() {return 0.0;}
  virtual void set_m_kd(Colour kd){(void)kd;}
  virtual void set_m_ks(Colour ks){(void)ks;}
  virtual void set_m_shininess(double shininess){(void)shininess;}



protected:
  Material()
  {
  }
};

class PhongMaterial : public Material {
public:
  PhongMaterial(const Colour& kd, const Colour& ks, double shininess);
  PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflection, double refraction);





  virtual ~PhongMaterial();

//  virtual void apply_gl() const;

  virtual void print() {
    std::cout << "m_kd is : " << m_kd << std::endl;
    std::cout << "m_ks is : " << m_ks << std::endl;
    std::cout << "m_shininess is: " << m_shininess <<std::endl <<std::endl;
  }


  virtual double get_ks1() {
    return m_ks.R();
  }
  virtual double get_ks2() {
    return m_ks.G();
  }
  virtual double get_ks3() {
    return m_ks.B();
  }

  virtual double get_kd1() {
    return m_kd.R();
  }
  virtual double get_kd2() {
    return m_kd.G();
  }
  virtual double get_kd3() {
    return m_kd.B();
  }

  PhongMaterial & operator= (const PhongMaterial & other)
    {
        if (this != &other) // protect against invalid self-assignment
        {
          m_kd = other.m_kd;
          m_ks = other.m_ks;
          m_shininess = other.m_shininess;
        }
        // by convention, always return *this
        return *this;
   }

  Colour m_kd;
  Colour m_ks;
  double m_shininess;
  double m_reflection;
  double m_refraction;





  virtual Colour get_m_kd() {
    return m_kd;
  }
  virtual Colour get_m_ks() {
    return m_ks;
  }
  virtual double get_m_shininess() {
    return m_shininess;
  }

  virtual void set_m_kd(Colour kd) {
    m_kd = kd;
  }
  virtual void set_m_ks(Colour ks) {
    m_ks = ks;
  }
  virtual void set_m_shininess(double shininess) {
    m_shininess = shininess;
  }






private:
//  Colour m_kd;
//  Colour m_ks;

//  double m_shininess;
};


#endif
