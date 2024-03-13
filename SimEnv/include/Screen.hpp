// Collision_And_Gravity_Sim.h: arquivo de inclusão para arquivos de inclusão padrão do sistema,
// ou arquivos de inclusão específicos a um projeto.

#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

extern unsigned int width = 1700;
extern unsigned int height = 900;

extern const float zoomAmount = 1.02f;

extern RenderWindow window(VideoMode(width, height), "Simulation Environment");

extern View view(Vector2f(0, 0), Vector2f(width, height));

// TODO: Referencie os cabeçalhos adicionais de que seu programa precisa aqui.
