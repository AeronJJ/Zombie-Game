#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include "InputConfig.h"
#include <algorithm>

#include <vector>

class Scene {
  // Should scene contain the list of entities????? I don't see why not, different scenes contain different entities, so if you want to move to a different "window", you just change which scene is passed to the renderer.
  public:
  Scene(Coord3D botLeft, Coord3D backTopRight, Entity* player, InputConfig* config);
  ~Scene();

  bool checkBounds(Coord3D point);
  Coord3D* getSize();
  double getDepth();
  double getWidth();
  double getHeight();

  virtual Scene* update();

  InputConfig* getInputConfig();
  void setInputConfig(InputConfig* newConf);

  bool addEntity(Entity* newEntity);
  void removeEntity(Entity* deadEntity);
  Entity** getEntities();
  int getMaxEntities();
  void sortEntities();

  void setFocused(Entity* focus);
  Entity* getFocused();

  void resetFocused();

  void setFocuser(Entity* focus);
  Entity* getFocuser();

  void setScene(int, Scene*);
  Scene* getScene(int);
  void goToScene(int);

  int getAlive();

  protected:
  void internalUpdate_();
  int goToSceneFlag_ = -1; // Every update checks this flag
  bool validateSceneIndex_(int index);

  int nextFree_;
  const int maxEntities_ = 20;

  private:
  InputConfig* sceneInputConfig_ = nullptr;

  static bool positionCheck_(Entity* ent1, Entity* ent2);

  int maxScenes_ = 5;
  Scene** scenes_;

  Coord3D bottomLeft_;
  Coord3D topRight_;
  Coord3D size_;
  double depth_;
  double width_;
  double height_;

  Entity** entities_;
  
  Entity* focusedEntity_;
  Entity* focuser_;

  Entity* player_; // Every scene needs a player?
};

#endif