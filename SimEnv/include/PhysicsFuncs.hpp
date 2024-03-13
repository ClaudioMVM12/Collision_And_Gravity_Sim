#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include <Screen.hpp>

using namespace std;
using namespace sf;

namespace physics_func {

    class Ball {

    public:
        float radius;
        float mass;
        Vector2f pos;
        Vector2f vel;
        Vector2f acel;

        Ball(float r, float m, Vector2f p, Vector2f v, Vector2f a) {
            radius = r;
            mass = m;
            pos = p;
            vel = v;
            acel = a;
        }
    };

	bool IfCollisionCC(Vector2f c1pos, float r1, Vector2f c2pos, float r2);

	vector < vector < float > > VResultant(Ball ball0, Ball ball1, float e);

	vector <vector < float > > ApplyGforce(Ball ball0, Ball ball1);

    void Gravity_force_model(RenderWindow& window, View view, unsigned int width, unsigned int height, float zoomAmount, string model);

    void Earth_gravity_model(RenderWindow& window, View view, unsigned int width, unsigned int height, float zoomAmount);
}