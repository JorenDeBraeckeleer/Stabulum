# Stabulum
Stabulum is my small 2d engine made for small arcade-like games.

Burger Time is an old arcade game I re-made for testing my engine.

Making an engine from scratch was a lot of fun, it was a school project we started were had to implement a lot of game design patterns. Making additions to the engine made it a fun and quik engine to work with.

A fun twist to show controller and keyboard support is a co-op mode, 2 Peter Pepper spawn and can work together to clear the stage.

## Subjects
### File Reading
The engine has a parser for Burger Time levels which are read from .txt files and converts this into a fully playable level.

Highscore is writen in a file and read when playing.
### Software Design / Game Programming Patterns
Game Loop, Update method, Command, State, Observer, EventQueue and Component. These are the patterns we saw at school and implemented in the engine.
### 3rd party
For physics I have a simple implementation of Box2D and for rendering SDL2. The renderer is very basic, I later added render layers to be able to work more efficiënt.
### Controller Support
Next to keyboard, also controller is supported in the engine. You can work with xbox, ps, switch or an engine controller when making your game. This is all done with a big input system I wrote.

## More
Visit my GitHub page for more projects and info!
