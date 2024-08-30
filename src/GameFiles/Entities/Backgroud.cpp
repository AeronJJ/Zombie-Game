#include "Background.h"

Background::Background() : Entity(nullptr) {
  Coord3D pos(0.5,1,-0.2);
  moveEntity(pos);
  backgroundSprite.cols = 84;
  backgroundSprite.rows = 40;
  backgroundSprite.data = (int*)BACKGROUND;
  setSprite(&backgroundSprite);
}
