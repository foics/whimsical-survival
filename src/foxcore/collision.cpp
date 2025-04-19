#include "foxcore/collision.hpp"

bool isOverlapping(Object *object, Object *otherObject) {
    if (object->x + object->width >= otherObject->x && object->x <= otherObject->x + otherObject->width && object->y + object->height >= otherObject->y && object->y <= otherObject->y + otherObject->width) {
        return true;
    } else {
        return false;
    }
}
