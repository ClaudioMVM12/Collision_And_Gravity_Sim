// Collision_And_Gravity_Sim.cpp: define o ponto de entrada para o aplicativo.
//

#include <Screen.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main(){

	window.setFramerateLimit(120);

    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen()){

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

	return 0;
}
