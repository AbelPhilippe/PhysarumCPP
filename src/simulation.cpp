#include "simulation.h"
#include "config.h"

#include "glad.h"

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

PhysarumSim::PhysarumSim()
{
    trail.resize(WIDTH * HEIGHT, 0.0f);
    trail_next.resize(WIDTH * HEIGHT, 0.0f);
    food.resize(WIDTH * HEIGHT, 0.0f);

    initAgents();
    initFood();
}

float PhysarumSim::randf()
{
    return rand() / (float)RAND_MAX;
}

void PhysarumSim::initAgents()
{
    for (int i = 0; i < NUM_AGENTS; i++) {

        float angle = randf() * 2.0f * M_PI;
        float radius = randf() * 50.0f;

        agents.push_back({
            WIDTH/2 + cos(angle) * radius,
            HEIGHT/2 + sin(angle) * radius,
            randf() * 2.0f * M_PI
        });
    }
}

void PhysarumSim::addFoodCircle(int cx, int cy, float radius, float strength) {
        for (int x = -radius; x <= radius; x++) {
            for (int y = -radius; y <= radius; y++) {

                int px = cx + x;
                int py = cy + y;

                if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT) continue;

                float dist = sqrt(x*x + y*y);
                if (dist <= radius) {
                    int idx = py * WIDTH + px;
                    food[idx] += strength * (1.0f - dist / radius);
                }
            }
        }
    }

void PhysarumSim::initFood() {
        addFoodCircle(200, 200, 30, 300.0f);
        addFoodCircle(700, 700, 30, 300.0f);
        addFoodCircle(200, 700, 30, 300.0f);
    }

float PhysarumSim::sense(float x, float y, float angle) {

        int sx = (int)(x + cos(angle) * SENSOR_DIST);
        int sy = (int)(y + sin(angle) * SENSOR_DIST);

        if (sx < 0 || sx >= WIDTH || sy < 0 || sy >= HEIGHT)
            return 0.0f;

        int idx = sy * WIDTH + sx;

        return trail[idx] * TRAIL_WEIGHT + food[idx] * FOOD_WEIGHT;
    }

void PhysarumSim::updateAgents() {

        for (auto &a : agents) {

            float f = sense(a.x, a.y, a.angle);
            float l = sense(a.x, a.y, a.angle - SENSOR_ANGLE);
            float r = sense(a.x, a.y, a.angle + SENSOR_ANGLE);

            // directional decision
            if (f > l && f > r) {
                // maintains direction
            }
            else if (l > r) {
                a.angle -= TURN_SPEED;
            }
            else if (r > l) {
                a.angle += TURN_SPEED;
            }
            else {
                a.angle += (randf() - 0.5f) * RANDOM_STRENGTH;
            }

            // global exploration
            if (randf() < EXPLORATION_CHANCE) {
                a.angle = randf() * 2.0f * M_PI;
            }

            // --------- moviment ---------
            a.x += cos(a.angle) * STEP_SIZE;
            a.y += sin(a.angle) * STEP_SIZE;

            // ------------- wrap -------------
            if (a.x < 0) a.x += WIDTH;
            if (a.x >= WIDTH) a.x -= WIDTH;
            if (a.y < 0) a.y += HEIGHT;
            if (a.y >= HEIGHT) a.y -= HEIGHT;

            int ix = (int)a.x;
            int iy = (int)a.y;
            int idx = iy * WIDTH + ix;

            //          --- deposits trail ---
            trail[idx] = std::min(trail[idx] + 1.2f, 20.0f);

            //           --- consumes food ---
            if (food[idx] > 0.0f) {
                food[idx] -= CONSUME_RATE;
                if (food[idx] < 0.0f) food[idx] = 0.0f;

                // Extra reinforcement -> creates connections
                trail[idx] += 7.5f;
            }
        }
    }

void PhysarumSim::diffuse(){

        for (int x = 1; x < WIDTH-1; x++) {
            for (int y = 1; y < HEIGHT-1; y++) {

                int i = y * WIDTH + x;

                float sum = 0.0f;

                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        sum += trail[(y+dy)*WIDTH + (x+dx)];
                    }
                }

                float blurred = sum / 9.0f;

                float value = trail[i] + (blurred - trail[i]) * DIFFUSE_RATE;
                value *= DECAY_RATE;

                trail_next[i] = value;
            }
        }

        trail.swap(trail_next);
    }

void PhysarumSim::updateFood(){
    for (auto &f : food) {
            f *= FOOD_DECAY;
        }
}

void PhysarumSim::update(){
     updateAgents();
        diffuse();
        //updateFood();             (optional)
}

void PhysarumSim::render(){

        std::vector<unsigned char> pixels(WIDTH * HEIGHT * 3);

        for (int i = 0; i < WIDTH * HEIGHT; i++) {

            float t = std::min(trail[i] / 6.0f, 1.0f);
            float f = std::min(food[i] / 80.0f, 1.0f);

            t = pow(t, 0.6f);

            unsigned char r, g, b;

            if (f > 0.05f) {
                r = g = b = (unsigned char)(f * 255);
            } else {
                r = (unsigned char)(t * 200);
                g = (unsigned char)(t * 255);
                b = (unsigned char)(t * 80);
            }

            pixels[i*3+0] = r;
            pixels[i*3+1] = g;
            pixels[i*3+2] = b;
        }

        glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

}

