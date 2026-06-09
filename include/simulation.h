#pragma once

#include <vector>
#include "agent.h"

class PhysarumSim
{
public:
    PhysarumSim();

    void update();
    void render();

private:

    std::vector<Agent> agents;
    std::vector<float> trail;
    std::vector<float> trail_next;
    std::vector<float> food;

    float randf();

    void initAgents();
    void initFood();

    void addFoodCircle(int cx,int cy,float radius,float strength);

    float sense(float x,float y,float angle);

    void updateAgents();
    void diffuse();
    void updateFood();
};