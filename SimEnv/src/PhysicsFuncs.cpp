#include <iostream>
#include <cmath>
#include <vector>

#include <Screen.hpp>

#define PI 3.14159265358979323846
#define g 9.8007
#define G 6.67*pow(10, -11)

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


    bool IfCollisionCC(Vector2f c1pos, float r1, Vector2f c2pos, float r2) {

        float dx = c2pos.x - c1pos.x;

        float dy = c2pos.y - c1pos.y;

        float distance = dx * dx + dy * dy;

        float sumRadii = (r1 + r2) * (r1 + r2);

        return sumRadii >= distance;
    }


    vector < vector < float > > VResultant(Ball ball0, Ball ball1, float e) {

        float x0 = ball0.pos.x;
        float y0 = ball0.pos.y;

        float x1 = ball1.pos.x;
        float y1 = ball1.pos.y;

        float m0 = ball0.mass;
        float m1 = ball1.mass;

        float u0x = ball0.vel.x;
        float u0y = ball0.vel.y;

        float u1x = ball1.vel.x;
        float u1y = ball1.vel.y;

        float a0 = atan2(y1 - y0, x1 - x0);
        float b0 = atan2(u0y, u0x);
        float c0 = b0 - a0;

        float a1 = atan2(y0 - y1, x0 - x1);
        float b1 = atan2(u1y, u1x);
        float c1 = b1 - a1;

        float u0 = sqrt(u0x * u0x + u0y * u0y);
        float u1 = sqrt(u1x * u1x + u1y * u1y);

        float u01 = u0 * cos(c0);
        float u00 = u0 * sin(c0);

        float u10 = u1 * cos(c1);
        float u11 = u1 * sin(c1);

        float v01 = (((-m1 * e + m0) * u01) - ((e + 1) * u10)) / (m0 + m1);
        float v10 = ((-(m1 - m0 * e) * u10) + ((e + 1) * u01)) / (m0 + m1);

        float v0x = u00 * (-sin(a0)) + v01 * (cos(a0));
        float v0y = u00 * (cos(a0)) + v01 * (sin(a0));

        float v1x = u11 * (-sin(a1)) - v10 * (cos(a1));
        float v1y = u11 * (cos(a1)) - v10 * (sin(a1));

        vector< vector < float > > pars{ { v0x, v0y }, { v1x,v1y} };

        return pars;
    }


    vector <vector < float > > ApplyGforce(Ball ball0, Ball ball1) {

        float m0 = ball0.mass;
        float m1 = ball1.mass;

        float dx = ball1.pos.x - ball0.pos.x;
        float dy = ball1.pos.y - ball0.pos.y;

        float r = sqrt(dx * dx + dy * dy);

        ball1.acel.x = G * m0 * dx / pow(r, 3);
        ball1.acel.y = G * m0 * dy / pow(r, 3);

        ball0.acel.x = G * m1 * (-dx) / pow(r, 3);
        ball0.acel.y = G * m1 * (-dy) / pow(r, 3);

        float a0x = -ball0.acel.x;
        float a0y = -ball0.acel.y;

        float a1x = -ball1.acel.x;
        float a1y = -ball1.acel.y;

        vector< vector< float > > pars{ { a0x, a0y }, { a1x, a1y } };

        return pars;
    }

    
    float dotProduct(const Vector2f& v1, const Vector2f& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    
    void Gravity_force_model(RenderWindow& window, View view, unsigned int width, unsigned int height, float zoomAmount, string model) {

        float e = 0;

        float timestep = 1;

        vector< Ball > particles;

        if (model == "Default") {
            float w = 0.75984;

            Ball circle3(16, 5.8e+12, Vector2f(0, 300), Vector2f(-w, 0), Vector2f(0, 0));

            Ball circle1(16, 5.8e+12, Vector2f(-sqrt(3) / 2 * 300, -1 / 2 * 300), Vector2f(w * (1 / 2), w * (-sqrt(3) / 2)), Vector2f(0, 0));

            Ball circle2(16, 5.8e+12, Vector2f(sqrt(3) / 2 * 300, -1 / 2 * 300), Vector2f(w * (1 / 2), w * (sqrt(3) / 2)), Vector2f(0, 0));

            particles.push_back(circle1);
            particles.push_back(circle2);
            particles.push_back(circle3);
        }

        while (window.isOpen()) {

            Event event;

            while (window.pollEvent(event)) {

                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {

                    Vector2i MousePosition = Mouse::getPosition(window);

                    Vector2f localMousePosition = window.mapPixelToCoords(MousePosition);

                    Vector2f p(localMousePosition.x, localMousePosition.y);

                    Vector2f v(3, 15);

                    Vector2f a(0, 0);

                    Ball circle(10, 6e+11, p, v, a);

                    if (Keyboard::isKeyPressed(Keyboard::C)) {

                        Ball& newcircle = circle;

                        cout << "\t\t\tCreative Mode" << endl;

                        cout << "radius: ";

                        cin >> newcircle.radius;

                        cout << "mass: ";

                        cin >> newcircle.mass;

                        cout << "vx: " << endl;

                        cin >> newcircle.vel.x;

                        cout << "vy: " << endl;

                        cin >> newcircle.vel.y;

                        cout << "\t\t\tPlanet has been created" << endl;

                        particles.push_back(circle);
                    }
                    else {
                        cout << "Planet has been created" << endl;
                        particles.push_back(circle);
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::M)) {
                    view.zoom(1.f / zoomAmount);
                }

                if (Keyboard::isKeyPressed(Keyboard::L)) {
                    view.zoom(zoomAmount);
                }
            }

            for (int i = 0; i < particles.size();i++) {

                Ball& circle = particles[i];

                float svx = 0, svy = 0;
                float sax = 0, say = 0;

                Vector2u size = window.getSize();
                width = size.x;
                height = size.y;

                circle.acel = { 0.f, 0.f };

                for (int j = 0; j < particles.size(); j++) {


                    if (j != i) {

                        Ball& otherCircle = particles[j];

                        vector < vector < float> > Ar = ApplyGforce(circle, otherCircle);

                        sax += Ar[0][0];
                        say += Ar[0][1];
                    }
                }

                circle.acel.x = sax;
                circle.acel.y = say;

                circle.vel.x += circle.acel.x * timestep / 2;
                circle.vel.y += circle.acel.y * timestep / 2;

                circle.pos.x += circle.vel.x * timestep;
                circle.pos.y += circle.vel.y * timestep;

                for (int j = 0; j < particles.size(); j++) {

                    if (j != i) {
                        Ball& otherCircle = particles[j];

                        if (IfCollisionCC(circle.pos, circle.radius, otherCircle.pos, otherCircle.radius)) {

                            vector< vector < float > > Vr = VResultant(circle, otherCircle, e);

                            svx += Vr[0][0];
                            svy += Vr[0][1];

                            Vector2f collisionNormal = circle.pos - otherCircle.pos;
                            float distance = sqrt(dotProduct(collisionNormal, collisionNormal));
                            collisionNormal /= distance;

                            float overlap = circle.radius + otherCircle.radius - sqrt(pow(circle.pos.x - otherCircle.pos.x, 2) + pow(circle.pos.y - otherCircle.pos.y, 2));

                            Vector2f relativeVelocity = circle.vel - otherCircle.vel;
                            float relativeSpeed = dotProduct(relativeVelocity, collisionNormal);

                            if (relativeSpeed > 0)
                                break;

                            float impulseScalar = -(1 + e) * relativeSpeed /
                                (1 / circle.mass + 1 / otherCircle.mass);

                            Vector2f impulse = impulseScalar * collisionNormal;

                            circle.vel += impulse / circle.mass;
                            otherCircle.vel -= impulse / otherCircle.mass;
                        }
                    }
                }

                circle.vel.x += svx + circle.acel.x * timestep / 2;
                circle.vel.y += svy + circle.acel.y * timestep / 2;

                circle.pos.x += circle.vel.x * timestep;
                circle.pos.y += circle.vel.y * timestep;
            }

            if (particles.size() >= 3) {

                Vector2f bar(0, 0);

                float n = particles.size();

                for (Ball& circle : particles) {

                    bar.x += circle.pos.x / n;

                    bar.y += circle.pos.y / n;
                }

                view.setCenter(bar.x, bar.y);
            }

            window.setView(view);

            window.clear();

            for (const Ball& circle : particles) {

                CircleShape ballfig(circle.radius);

                ballfig.setFillColor(Color::Red);

                ballfig.setPosition(circle.pos);

                window.draw(ballfig);
            }

            window.display();
        }

    }


    void Earth_gravity_model(RenderWindow& window, View view, unsigned int width, unsigned int height, float zoomAmount) {

        float e = 0.5;

        float timestep = 1;

        vector< Ball > particles;

        while (window.isOpen()) {

            Event event;

            while (window.pollEvent(event)) {

                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {

                    Vector2i MousePosition = Mouse::getPosition(window);

                    Vector2f localMousePosition = window.mapPixelToCoords(MousePosition);

                    Vector2f p(localMousePosition.x, localMousePosition.y);

                    Vector2f v(0, 0);

                    Vector2f a(0, g);

                    Ball circle(40, 60, p, v, a);

                    if (Keyboard::isKeyPressed(Keyboard::C)) {

                        Ball& newcircle = circle;

                        cout << "\t\t\tCreative Mode" << endl;

                        cout << "radius: ";

                        cin >> newcircle.radius;

                        cout << "mass: ";

                        cin >> newcircle.mass;

                        cout << "vx: " << endl;

                        cin >> newcircle.vel.x;

                        cout << "vy: " << endl;

                        cin >> newcircle.vel.y;

                        cout << "\t\t\tPlanet has been created" << endl;

                        particles.push_back(circle);
                    }
                    else {
                        cout << "Planet has been created" << endl;
                        particles.push_back(circle);
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::M)) {
                    view.zoom(1.f / zoomAmount);
                }

                if (Keyboard::isKeyPressed(Keyboard::L)) {
                    view.zoom(zoomAmount);
                }
            }

            for (int i = 0; i < particles.size();i++) {

                Ball& circle = particles[i];

                // Walls generation
                if (circle.pos.x < 0 || circle.pos.x > float(width) - 2 * circle.radius) {
                    circle.vel.x *= -e;
                    circle.pos.x = std::max(0.0f, std::min(circle.pos.x, float(width) - 2 * circle.radius));
                }

                if (circle.pos.y < 0 || circle.pos.y > float(height) - 2 * circle.radius) {
                    circle.vel.y *= -e;
                    circle.pos.y = std::max(0.0f, std::min(circle.pos.y, float(height) - 2 * circle.radius));
                }

                circle.vel.x += circle.acel.x * timestep / 2;
                circle.vel.y += circle.acel.y * timestep / 2;

                circle.pos.x += circle.vel.x * timestep;
                circle.pos.y += circle.vel.y * timestep;

                for (int j = 0; j < particles.size(); j++) {

                    if (j != i) {
                        Ball& otherCircle = particles[j];

                        if (IfCollisionCC(circle.pos, circle.radius, otherCircle.pos, otherCircle.radius)) {

                            vector< vector < float > > Vr = VResultant(circle, otherCircle, e);

                            circle.vel.x += Vr[0][0]/10;
                            circle.vel.y += Vr[0][1]/10;

                            Vector2f collisionNormal = circle.pos - otherCircle.pos;
                            float distance = sqrt(dotProduct(collisionNormal, collisionNormal));
                            collisionNormal /= distance;

                            float overlap = circle.radius + otherCircle.radius - sqrt(pow(circle.pos.x - otherCircle.pos.x, 2) + pow(circle.pos.y - otherCircle.pos.y, 2));

                            Vector2f relativeVelocity = circle.vel - otherCircle.vel;
                            float relativeSpeed = dotProduct(relativeVelocity, collisionNormal);

                            if (relativeSpeed > 0)
                                break;

                            float impulseScalar = -(1 + e) * relativeSpeed /
                                (1 / circle.mass + 1 / otherCircle.mass);

                            Vector2f impulse = impulseScalar * collisionNormal;

                            circle.vel += impulse / circle.mass;
                            otherCircle.vel -= impulse / otherCircle.mass;
                        }
                    }
                }

                circle.vel.x += circle.acel.x * timestep / 2;
                circle.vel.y += circle.acel.y * timestep / 2;

                circle.pos.x += circle.vel.x * timestep;
                circle.pos.y += circle.vel.y * timestep;
            }

            window.clear();

            for (const Ball& circle : particles) {

                CircleShape ballfig(circle.radius);

                ballfig.setFillColor(Color::Red);

                ballfig.setPosition(circle.pos);

                window.draw(ballfig);
            }

            window.display();
        }

    }

}
