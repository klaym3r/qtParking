#include "slot.h"

Slot::Slot() {}

void Slot::center() {
    x_ = x_ + w_ / 2;
    y_ = y_ + h_ / 2;
}
