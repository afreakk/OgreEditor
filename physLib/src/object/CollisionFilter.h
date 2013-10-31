#ifndef COLLISIONFILTER_H
#define COLLISIONFILTER_H
namespace CollisionLayer
{
    #define BIT(x) (1<<(x))
    ///collisionLayers , use int layer = ONE|TWO to combine ONE and TWO
    enum  {
        NOTHING = 0,
        DEFAULT = BIT(0),
        ONE = BIT(1),
        TWO = BIT(2),
        THREE = BIT(3),
        FOUR = BIT(4),
        FIVE = BIT(5),
        SIX = BIT(6),
        CHARACTER = BIT(7)
    };

}
#endif // COLLISIONFILTER_H
