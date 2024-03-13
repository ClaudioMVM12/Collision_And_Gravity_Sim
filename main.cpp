// Collision_And_Gravity_Sim.cpp: define o ponto de entrada para o aplicativo.
//

#include <PhysicsFuncs.hpp>

#define PI 3.14159265358979323846
#define g 9.8007
#define G 6.67*pow(10, -11)

using namespace std;
using namespace physics_func;
using namespace sf;

string AppMode = "Default";

int main() {

    cout << "------------------------------------------------------------------" << endl;

    cout << "\t Welcome to the collision and gravity force simulation" << endl;

    cout << "Choose one option:" << endl;

    cout << "Default Simulation (3-body problem) (press D)" << endl;
    cout << "Earth Gravity model (press E)" << endl;
    cout << "Gravity force model (press F)" << endl;

    while (true) {

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            AppMode = "Default";
            break;
        }

        if (Keyboard::isKeyPressed(Keyboard::E)) {
            AppMode = "Earth Gravity";
            break;
        }

        if (Keyboard::isKeyPressed(Keyboard::F)) {
            AppMode = "Gravity force";
            break;
        }
    }

    cout << "------------------------------------------------------------------" << endl;
    cout << "\t\t\t World Creation" << endl;
    cout << "Press the right mouse button to create a standard an object." << endl;
    cout << "Press the right mouse button + C keyboard to create an object." << endl;
    cout << "------------------------------------------------------------------" << endl;

    window.setFramerateLimit(120);

    if(AppMode == "Gravity force")
        Gravity_force_model(window, view, width, height, zoomAmount, AppMode);
    if(AppMode == "Earth Gravity")
        Earth_gravity_model(window, view, width, height, zoomAmount);
    if (AppMode == "Default")
        Gravity_force_model(window, view, width, height, zoomAmount, AppMode);

	return 0;
}
