#include "material.hpp"

Material::~Material()
{
}

PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks, double shininess)
  : m_kd(kd), m_ks(ks), m_shininess(shininess)
{
}


PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflection, double refraction)
  : m_kd(kd), m_ks(ks), m_shininess(shininess), m_reflection(reflection), m_refraction(refraction)
{
}



PhongMaterial::~PhongMaterial()
{
}

/*
void PhongMaterial::apply_gl() const
{
  // Perform OpenGL calls necessary to set up this material.
}
*/
