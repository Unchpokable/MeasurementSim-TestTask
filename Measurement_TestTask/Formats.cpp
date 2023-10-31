#include "Formats.h"


Bracket RoundBrackets()
{
    return Bracket { '(', ')' };
}


Bracket SquareBrackets()
{
    return Bracket { '[', ']' };
}

Bracket GetBracket(Brackets brackets)
{
    switch(brackets) {
        case BR_ROUND:
            return RoundBrackets();
        case BR_SQUARE:
            return SquareBrackets();
    }

    return RoundBrackets();
}

