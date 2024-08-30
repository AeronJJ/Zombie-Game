#include "Renderer.h"
#include <memory>
#include <string>
#include <vector>

Renderer::Renderer(Scene* world, N5110* lcd) : world_(world), lcd_(lcd) {
  if (world_ != nullptr) {
    sceneSize_ = world_->getSize();
    zoneWidth_ = sceneSize_->y/zones_;
    entities_ = world_->getEntities();
    maxEntities_ = world_->getMaxEntities();
  }
}

Renderer::~Renderer() {
  // Nothing to delete :)
}

void Renderer::updateScene(Scene* scene) {
  if (scene != nullptr) {
    world_ = scene;
    sceneSize_ = world_->getSize();
    zoneWidth_ = sceneSize_->y/zones_;
    entities_ = world_->getEntities();
    maxEntities_ = world_->getMaxEntities();
  }
}

Scene* Renderer::getScene() {
  return world_;
}


void Renderer::render() {
  lcd_->clear();
  lcd_->drawCircle(74, 8, 4, FILL_TRANSPARENT);
  //lcd_->printChar('a', 1, 2);
  //lcd_->printString("Testing", 3, 3);
  if (world_ != nullptr) {
    world_->resetFocused();
    for (int i = 0; i < world_->getAlive(); i++) {
      if (entities_[i]->Alive && entities_[i] != nullptr) {
        Coord3D position = scaledPosition(entities_[i]->getPosition());
        int spriteDepth = scale(position.y);
        
        if (spriteDepth != 0 ) { // Change to >.
          currentSprite_ = entities_[i]->getSprite(spriteDepth-1);
          if (currentSprite_ != nullptr && currentSprite_->data != nullptr) {
            int rows = currentSprite_->rows;
            int cols = currentSprite_->cols;
            int x = position.x*84-floor(entities_[i]->getJustification() * cols/2);
            int y = 48*(1-(0.2*position.y + position.z))-rows;

            if (world_->getFocuser() == entities_[i]) {
              focuserX_ = x;
              focuserY_ = y;
              Coord3D offset = entities_[i]->getOffset();
              offsetX_ = offset.x;
              offsetY_ = offset.y;
            }
            
            else if (world_->getFocuser() == nullptr) {
              focuserX_ = -1;
              focuserY_ = -1;
            }
            else if (checkFocus_(currentSprite_, x, y)) {
              world_->setFocused(entities_[i]);
            }

            lcd_->drawSprite(x, y, rows, cols, (int*)currentSprite_->data, currentSprite_->reverse);
          }
        }
      }
    }
    currentSprite_ = nullptr;
  }
  lcd_->refresh();
}

int Renderer::scale(double y) {
  // This function returns the level of zoom based on the sprites position,
  // returns number between 1 and zones_, or 0 if out of bounds. Lower y means
  // that it is closer to the camera.
  //double zoneWidth = world_->getDepth() / zones_; // Constant, should only calc once, store in scene class, should also store zones_ in scene

  if (y > world_->getDepth() || y < 0) {
  //if (y > 1 || y < 0) {
    return 0;
  } else if (y == 0){
    return 1;
  } else {
    return std::ceil(y / zoneWidth_);
  }
}

Coord3D Renderer::scaledPosition(Coord3D pos) {
  Coord3D scalePos(pos.x/sceneSize_->x, pos.y/sceneSize_->y, pos.z/sceneSize_->z);
  return scalePos;
}

int Renderer::zPosition(Coord3D pos, int depth) {
  return 0;
}

bool Renderer::checkFocus_(Sprite* spr, int x, int y) {
  x -= offsetX_;
  y -= offsetY_;
  if (x < focuserX_ && focuserX_ < spr->cols + x && y < focuserY_ && focuserY_ < spr->rows + y && spr->data[focuserX_ - x + spr->cols * (focuserY_ - y)] != 0) {
    return true;
  }
  else return false;
}
