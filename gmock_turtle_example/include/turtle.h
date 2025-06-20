// Ensures this header file is included only once during compilation
// Prevents duplicate symbol or redefinition errors
#pragma once
// Abstract interface for any drawable "Turtle"-like object.
// Defines a contract for how a turtle should behave — moving, drawing, and reporting position.
class Turtle {
public:

  // Virtual destructor with `= default` ensures proper cleanup of derived objects.
  // Marked `virtual` so that when deleting via base pointer, the correct subclass destructor is called.
  virtual ~Turtle() = default;

  // Pure virtual function — subclasses must implement this.
  // Lifts the turtle’s pen: subsequent movement won't draw anything.
  virtual void PenUp() = 0;

  // Puts the pen down: subsequent movement draws lines on the canvas.
  virtual void PenDown() = 0;

  // Moves the turtle forward by a specified distance.
  // The direction depends on its current heading (angle).
  virtual void Forward(int distance) = 0;

  // Rotates the turtle by 'degrees'. Typically:
  //   - positive for clockwise
  //   - negative for counter-clockwise
  virtual void Turn(int degrees) = 0;

  // Instantly moves the turtle to a new (x, y) coordinate.
  // May or may not draw a line depending on pen state.
  virtual void GoTo(int x, int y) = 0;

  // Returns the current X position of the turtle.
  // Marked `const` because it doesn’t modify the turtle’s state.
  virtual int GetX() const = 0;

  // Returns the current Y position of the turtle.
  // Also marked `const` for the same reason.
  virtual int GetY() const = 0;
};

