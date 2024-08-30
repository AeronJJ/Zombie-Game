#ifndef ENTITY_H
#define ENTITY_H

#include "Coord3D.h"
#include "Messenger.h"

struct Sprite {
  Sprite();
  Sprite(int rows, int cols, int* data, bool reverse = false);
  int* data;
  int rows;
  int cols;
  bool reverse = false;
};

class Entity{
    public:
    Entity(Messenger* messenger = nullptr, bool createdByScene = false); // Constructor

    virtual ~Entity();
    virtual void update();

    Coord3D getPosition();
    void moveEntity(Coord3D);
    virtual void shiftEntity(Coord3D);
    void moveEntityByPixel(double x, double y);

    bool Alive = false;

    int getRows(int scale);
    int getCols(int scale);

    void setSprite(int row, int col, int* sprite, int scale); // Deprecated.
    void setSprite(int row, int col, int* sprite);
    void setSprite(Sprite* sprite, int scale); // Set specific sprite
    void setSprite(Sprite* sprite); // Set all sprites

    void setRows(int row, int pos);
    void setCols(int col, int pos);

    int* getSpriteData(int scale);

    Sprite* getSprite(int scale);

    void setFocus();
    void desetFocus();

    virtual void shot();

    int goToScene();

    Coord3D getOffset();

    int getNextFree();
    void setNextFree(int);

    int getJustification();
    void setJustification(int just);
    void togglePause();

    bool ownedByScene();
    
    private:
    Coord3D position_;

    int nextFree_; // For "linked" list.
    
    bool createdByScene_;

    protected:

    Messenger* messenger_;

    Sprite** sprites_;
    int maxSprites = 6;

    int justification_ = 1; // 1 is centered, 0 is left justified, 2 is right justified, other values are possible...

    void setOffset_(int x, int y);
    void setOffset_(Coord3D ofs);
    Coord3D offset_ = Coord3D (0,0,0);

    bool focused_ = false;
    int goToScene_ = -1;

    bool paused_ = false;

};

#endif