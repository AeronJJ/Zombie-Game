#ifndef RENDERER_H
#define RENDERER_H

#include <cmath>

#include "Coord3D.h"
#include "Scene.h"
#include "Entity.h"
#include "N5110.h"
#include <memory>

class Renderer {
public:
  Renderer(Scene* world, N5110* lcd); // Constructor, 
  ~Renderer();
  void render();
  void updateScene(Scene* scene);
  Scene* getScene();
  int scale(double y);

  int zPosition(Coord3D pos, int depth);

private:
  Scene* world_;
  N5110* lcd_;

  int zones_ = 6;
  double zoneWidth_;
  Coord3D* sceneSize_;
  Coord3D scaledPosition(Coord3D pos);

  Sprite* currentSprite_;
  
  Entity** entities_;
  int maxEntities_; // This value is limited, be careful!!

  bool checkFocus_(Sprite* spr, int x, int y);
  int focuserX_;
  int focuserY_;
  int offsetX_;
  int offsetY_;
  
};

#endif