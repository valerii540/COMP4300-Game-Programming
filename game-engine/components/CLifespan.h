#ifndef COMP4300_GAME_PROGRAMMING_CLIFESPAN_H
#define COMP4300_GAME_PROGRAMMING_CLIFESPAN_H

class CLifespan {
public:
    const int total;
    int       remaining;

    explicit CLifespan(int total)
            : remaining(total), total(total) {}
};

#endif //COMP4300_GAME_PROGRAMMING_CLIFESPAN_H
