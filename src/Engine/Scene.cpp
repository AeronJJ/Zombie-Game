#include "Scene.h"
#include <vector>

Scene::Scene(Coord3D botLeft, Coord3D topRight, Entity* player, InputConfig* config)
    : bottomLeft_(botLeft), topRight_(topRight), size_(topRight.x-botLeft.x, topRight.y - botLeft.y, topRight.z-botLeft.z), player_(player){
  // This assumes that the bottom left is actually at the bottom left...
  setInputConfig(config);
  focusedEntity_ = nullptr;
  focuser_ = nullptr;
  entities_ = new Entity*[maxEntities_];
  nextFree_ = 0;
  for (int i = 0; i < maxEntities_; i++) {
    entities_[i] = nullptr;
  }

  scenes_ = new Scene*[maxScenes_];
  for (int i = 0; i < maxScenes_; i++) {
    scenes_[i] = nullptr;
  }
  addEntity(player_);
  setFocuser(player_);

}

Scene::~Scene() {
  focusedEntity_ = nullptr;
  focuser_ = nullptr;
  player_ = nullptr;
  for (int i = 0; i < nextFree_; i++) {
    if (entities_[i] != nullptr && entities_[i]->ownedByScene()) {
      delete entities_[i];
    }
    //delete entities_[i]; // Bad, do not want to delete entities that were not created by this scene. Need to make a flag in entities, or switch to smart pointers.
  }
  delete [] entities_;

  delete [] scenes_;
};

double Scene::getDepth() {
  return size_.y;
}

double Scene::getWidth() {
  return size_.x;
}

double Scene::getHeight() {
  return size_.z;
}

Coord3D* Scene::getSize() {
  return &size_;
}

bool Scene::checkBounds(Coord3D point) {
  // Returns true if the inputted co-ordinate is inside the bounds of the scene

  return ((bottomLeft_.x <= point.x && point.x <= topRight_.x) &&
         (bottomLeft_.y <= point.y && point.y <= topRight_.y) &&
         (bottomLeft_.z <= point.z && point.z <= topRight_.z));
}

Scene* Scene::update() {
  for (int i = 0; i < nextFree_; i++) {
    if (entities_[i] != nullptr) {
      int index = entities_[i]->goToScene();
      if (validateSceneIndex_(index)) {
        goToSceneFlag_ = index;
      }
    }
  }
  if (validateSceneIndex_(goToSceneFlag_)) {
    int index = goToSceneFlag_;
    goToSceneFlag_ = -1;
    return scenes_[index];
  }
  else {
    internalUpdate_();
    return nullptr;
  }
}

void Scene::internalUpdate_() {
  sortEntities();
  int i = 0;
  while(entities_[i] != nullptr) {
    entities_[i]->update();
    i++;
  }
}

bool Scene::addEntity(Entity* newEntity) {
  // Because the entity list gets sorted every time the scene is updated (we will also sort the list every time an entity is removed), 
  // we can assume that all the free slots are at the end of the list, and that nextFree_ should be equal to the amount of alive entities.
  if (nextFree_ < maxEntities_-1) {
    newEntity->Alive = true;
    entities_[nextFree_] = newEntity;
    nextFree_++;
    return true;
  }
  else {
    return false;
  }

}

void Scene::removeEntity(Entity* deadEntity) {
  // ONLY CALL THIS FUNCTION FOR ENTITIES CREATED INSIDE THE SCENE... TO DO: add a flag
  for (int i = 0; i < maxEntities_; i++) {
    if (entities_[i] == deadEntity) {
      delete entities_[i]; // Dangerous, quite dangerous..
      entities_[i] = nullptr;
      nextFree_--;
    }
  }
  sortEntities();
}

Entity** Scene::getEntities() {
  return entities_;
}

int Scene::getMaxEntities() {
  return maxEntities_;
}

/*
void Scene::sortEntities() {

  Entity* temp = nullptr;

  int countNull = 0;
  for (int i = 0; i < maxEntities_; i++) {
    if (entities_[i] == nullptr) {countNull++;}
  }

  int index = 0;
  while (index < maxEntities_ - countNull) {
    int maxIndex = index;
    for (int i = index+1; i < maxEntities_; i++) {
      if (entities_[i] != nullptr && (entities_[maxIndex] == nullptr || entities_[i]->getPosition().y > entities_[maxIndex]->getPosition().y)) {
        maxIndex = i;
      }
    }
    temp = entities_[index];
    entities_[index] = entities_[maxIndex];
    entities_[maxIndex] = temp;
    index++;
  }

  temp = nullptr;
}*/

void Scene::sortEntities() {
  std::sort(entities_, entities_ + maxEntities_, positionCheck_);
}

bool Scene::positionCheck_(Entity* ent1, Entity* ent2) {
  // Returns true if ent1 should be sorted before ent2.
  if (ent1 == nullptr) {
    return false; 
  }
  else if (ent2 == nullptr) {
    return true;
  }
  else {
    return ent1->getPosition().y > ent2->getPosition().y;
  }
}

InputConfig* Scene::getInputConfig() {
  return sceneInputConfig_;
}

void Scene::setInputConfig(InputConfig* newConf) {
  sceneInputConfig_ = newConf;
}

void Scene::setFocused(Entity* focus) {
  if (focusedEntity_ != nullptr) {
    focusedEntity_->desetFocus();
  }
  focusedEntity_ = focus;
  focusedEntity_->setFocus();
}

Entity* Scene::getFocused() {return focusedEntity_;}

void Scene::setFocuser(Entity* focus) {
  focuser_ = focus;
}

Entity* Scene::getFocuser() {
  return focuser_;
}

void Scene::resetFocused() {
  if (focusedEntity_ != nullptr) {
    focusedEntity_->desetFocus();
    focusedEntity_ = nullptr;
  }
}

void Scene::setScene(int index, Scene* scn) {
  if (validateSceneIndex_(index)) {
    scenes_[index] = scn;
  }
}

Scene* Scene::getScene(int index) {
  if (validateSceneIndex_(index)) {
    return scenes_[index];
  }
  else {
    return nullptr;
  }
}

void Scene::goToScene(int index) {
  if (validateSceneIndex_(index)) {
    goToSceneFlag_ = index;
  }
}

bool Scene::validateSceneIndex_(int index) {
  return index > -1 && index < maxScenes_;
}

int Scene::getAlive() { return nextFree_; }