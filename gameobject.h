#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class GameObject {
protected:
    struct pos {
        int x, y;
    } position;

public:
    void setXY(int x, int y) {
        position.x =x;
        position.y=y;
    }

    void setX(int x){position.x = x;}
    void setY(int y){position.y = y;}

    int getX(){ return position.x;}
    int getY(){ return position.y;}
    pos getPosition(){return position;}
};

#endif /* __GAMEOBJECT_H__ */
