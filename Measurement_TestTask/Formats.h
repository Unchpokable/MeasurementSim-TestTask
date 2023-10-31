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