#pragma once

enum Brackets
{
    BR_ROUND,
    BR_SQUARE
};

struct Bracket
{
    char Open, Close;
};

Bracket RoundBrackets();
Bracket SquareBrackets();

//Returns Bracket struct with Open-Close brackets by given type
Bracket GetBracket(Brackets brackets);