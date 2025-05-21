// BattleGround.hpp
#ifndef BATTLEGROUND_HPP
#define BATTLEGROUND_HPP

class BattleGround3D {
private:
    float radius;
    int segments;

public:
    BattleGround3D(float r, int s);
    void draw();
};

#endif
