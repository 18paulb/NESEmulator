//
// Created by Brandon Paul on 5/6/24.
//

#ifndef NESEMULATOR_SYSTEMPART_H
#define NESEMULATOR_SYSTEMPART_H

class SystemPart {
public:
    virtual void step_to(int newCount) = 0;
};
#endif //NESEMULATOR_SYSTEMPART_H
