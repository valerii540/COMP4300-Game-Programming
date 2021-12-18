#ifndef COMP4300_GAME_PROGRAMMING_CLIFESPAN_H
#define COMP4300_GAME_PROGRAMMING_CLIFESPAN_H

class CLifespan {
public:
    int remaining = 0;
    int total     = 0;

    CLifespan(int total)
            : remaining(total), total(total) {}
};

#endif //COMP4300_GAME_PROGRAMMING_CLIFESPAN_H
