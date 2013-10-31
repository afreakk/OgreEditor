#ifndef WORLDSINGLETHREAD_H
#define WORLDSINGLETHREAD_H
#include "worldbase.h"
#include "object.h"
class worldsinglethread:public WorldBase
{
public:
    worldsinglethread(btScalar averageFPS,btScalar lowestFPS);
    void init(btVector3 & gravity);
    ~worldsinglethread();
private:


};
#endif // WORLDSINGLETHREAD_H
