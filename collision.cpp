#include "collision.h"

void Collision::runCollisionCheck(vector <GameObject*> gameObjectList){
    for(vector <GameObject*>::iterator it_one = gameObjectList.begin();
        it_one != gameObjectList.end();
        it_one++){
        bool hasCollided = false;
        vector <GameObject*> collisionList;
        collisionList.reserve(100);
        for(vector <GameObject*>::iterator it_two = gameObjectList.begin();
            it_two != gameObjectList.end();
            it_two++){

            SDL_Rect boxOne = (*it_one)->getRect();
            SDL_Rect boxTwo = (*it_two)->getRect();

            if((boxTwo.x >= boxOne.x &&
               boxTwo.x <= (boxOne.x+boxOne.w) &&
               boxTwo.y >= boxOne.y &&
               boxTwo.y <= (boxOne.y+boxOne.h)) ||
               (boxOne.x >= boxTwo.x &&
                boxOne.x <= (boxTwo.x+boxTwo.w) &&
                boxOne.y >= boxTwo.y &&
                boxOne.y <= (boxTwo.y+boxTwo.h))){

                if((*it_two)->getId() != (*it_one)->getId()){
                    collisionList.push_back((GameObject*) (*it_two));
                    hasCollided = true;
                }

            }
        }
        if(hasCollided){
            if((*it_one)->isColliding()){
                (*it_one)->handleCollision(collisionList);
            }
            (*it_one)->setCollision(true);
        }
        else {
            (*it_one)->setCollision(false);
        }
        collisionList.empty();
    }
}
