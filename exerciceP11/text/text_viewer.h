#pragma once

#include <iostream>
#include "support_a_dessin.h"

class TextViewer : public SupportADessin {
public:
 TextViewer(std::ostream& flot)
    : flot(flot)
  {}
  virtual ~TextViewer() = default;
  // on ne copie pas les TextViewer
  TextViewer(TextViewer const&)            = delete; 
  TextViewer& operator=(TextViewer const&) = delete;
   // mais on peut les déplacer
  TextViewer(TextViewer&&)            = default; 
  TextViewer& operator=(TextViewer&&) = default;

  virtual void dessine (MontagneGaussienne const& a_dessiner) override;
  virtual void dessine (Ciel const& a_dessiner)               override;
  virtual void dessine (Systeme const& a_dessiner)            override;


private:
  std::ostream& flot;
};
