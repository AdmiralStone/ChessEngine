#include "Colors.hpp"

const Color darkGrey    =  {26,31,40,255};
const Color lightGreen  =  {234,235,200,255};
const Color darkGreen =     {119,154,88,255};
const Color red =           {233,33,77,255};
const Color lightRed =      {255,81,116,255};
const Color orange =        {226,116,17,255};
const Color yellow =        {237,234,4,255};
const Color purple =        {166,0,247,255};
const Color cyan =          {21,204,209,255};
const Color blue =          {13,64,216,255};
const Color darkBlue =      {44,44,127,255};
const Color lightBlue =     {59,85,162,255};
const Color lastMoveLight = {208,237,62,150};
const Color lastMoveDark  = {180,195,51,170};

bool ColorEq(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}
