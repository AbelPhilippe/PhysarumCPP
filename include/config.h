#pragma once

// Dimensions && NUM Agents
const int WIDTH  = 800;
const int HEIGHT = 800;

const int NUM_AGENTS = 250000;

// sensors
const float SENSOR_DIST  = 30.0f;
const float SENSOR_ANGLE = 0.5f;
const float TURN_SPEED   = 0.35f;
const float STEP_SIZE    = 1.8f;

// dynamics
const float RANDOM_STRENGTH = 1.2f;
const float EXPLORATION_CHANCE = 0.08f;

// enviroment
const float DIFFUSE_RATE = 0.45f;
const float DECAY_RATE   = 0.84f;

// food (optional)
const float FOOD_DECAY = 0.995f;
const float FOOD_WEIGHT = 16.0f;
const float TRAIL_WEIGHT = 0.3f;
const float CONSUME_RATE = 0.3f;