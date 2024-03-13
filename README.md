# Collision and Gravity Simulation

This program use a graphical interface (using SFML) to study and simulate the physics of collision and gravity force between circular particles in a 2D Environment. You have two modes:

1. Gravity force mode

In this mode, you start with a empty world wihout walls that can be fulled with particles by two forms:

* Generating a Standard particle (with pre-defined parameters) using the _Right Click of the Mouse_;
* Generating a Custom particle using pressing _C+Right Click of the Mouse_.

### Particle parameters in Gravity force mode:

* Radius (standard value of 10);
* Mass (standard value of 6e+11);
* X axis Velocity (standard value of 15);
* Y axis Velocity (standard value of 3);
* X axis Acceleration (standard value of 0);
* Y axis Acceleration (standard value of 0).

### Settings of Gravity force mode:

* In the same time that those particles are created, they interact with each other by gravity force;
* This simulation have collision handling mechanics;
* The collision handling mechanism its simply the distance between particles´s center;
* Its possible to change the Coefficient of restitution (e) and the way of energy behave by that, just by code;
* You can use the keys M to maximize the window and L to minimize it;
* The camera uses the baricenter of the system of particles to be the center of view;
* The simulation runs in real time and evolves by iteration using the verlet numerical method, which has a timestep varible that can be changed by code.

2. Earth Gravity mode

In this mode, you start with a empty world with walls that can be fulled with particles by two forms:

* Generating a Standard particle (with pre-defined parameters) using the _Right Click of the Mouse_;
* Generating a Custom particle using pressing _C+Right Click of the Mouse_;

### Particle parameters in Earth Gravity mode:
* Radius (standard value of 40);
* Mass (standard value of 60);
* X axis Velocity (standard value of 0);
* Y axis Velocity (standard value of 0);
* X axis Acceleration (standard value of 0);
* Y axis Acceleration (standard value of g=9.800665).

As the name sugests, here when don´t have the gravity attraction force between two particles, just the acceleration of gravity force in the Y component due to Earth.

### Settings Earth Gravity mode:

* This simulation have collision handling mechanics;
* The collision handling mechanism its simply the distance between particles´s center;
* Its possible to change the Coefficient of restitution (e) and the way of energy behave by that, just by code;
* Collisions against the wall modify the velocity components according to the restitution coefficient;
* The simulation runs in real time and evolves by iteration using the verlet numerical method, which has a timestep varible that can be changed by code.

## Instalation

Collision and Gravity Simulation does not come with an installer. To use the application, you can clone this repository and run the exe file in \out\build\x64-debug\.
