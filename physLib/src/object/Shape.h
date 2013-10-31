#ifndef SHAPE_H
#define SHAPE_H

#include "BtOgrePG.h"
#include "BtOgreGP.h"

namespace Shapez
{
    enum { sphere, box, trimesh, cylinder, convex, capsule, allignedBox, orientedBox,none };

   inline btCollisionShape* setupShape(int shapeType, BtOgre::StaticMeshToShapeConverter& converter)
    {
        switch(shapeType)
        {
        case Shapez::sphere: return converter.createSphere(); break;
        case Shapez::box: return converter.createBox(); break;
        case Shapez::trimesh: return converter.createTrimesh(); break;
        case Shapez::cylinder: return converter.createCylinder(); break;
        case Shapez::convex: return converter.createConvex(); break;
        case Shapez::capsule: return converter.createCapsule(); break;

        }
        return NULL;
    }
   inline btCollisionShape* setupShapeAnimated(int shapeType, BtOgre::AnimatedMeshToShapeConverter& converter)
    {
        switch(shapeType)
        {
        case Shapez::sphere: return converter.createSphere(); break;
        case Shapez::box: return converter.createBox(); break;
        case Shapez::trimesh: return converter.createTrimesh(); break;
        case Shapez::cylinder: return converter.createCylinder(); break;
        case Shapez::convex: return converter.createConvex(); break;
        case Shapez::capsule: return converter.createCapsule(); break;
        //case Shapez::allignedBox: return converter.createAlignedBox()

        }
        return NULL;
    }
}
namespace ConvexShapez {
    enum { sphere, box, cylinder, convex, capsule,none };
    inline btConvexShape* setupShape(int shapeType, BtOgre::StaticMeshToShapeConverter& converter)
     {
         switch(shapeType)
         {
         case ConvexShapez::sphere: return converter.createSphere(); break;
         case ConvexShapez::box: return converter.createBox(); break;
         case ConvexShapez::cylinder: return converter.createCylinder(); break;
         case ConvexShapez::convex: return converter.createConvex(); break;
         case ConvexShapez::capsule: return converter.createCapsule(); break;

         }
         return NULL;
     }
}
#endif // SHAPE_H
