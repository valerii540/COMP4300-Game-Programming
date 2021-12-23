#ifndef COMP4300_GAME_PROGRAMMING_CINPUT_H
#define COMP4300_GAME_PROGRAMMING_CINPUT_H

namespace CInputNS {
    enum InputAction {
        None, Up, Left, Right, Down, Shoot
    };
}

class CInput {
public:
    CInputNS::InputAction action = CInputNS::None;
};

#endif //COMP4300_GAME_PROGRAMMING_CINPUT_H
