// Ensures this header file is included only once during compilation
// Prevents duplicate symbol or redefinition errors
#pragma once

// Include the declaration of the Turtle abstract class
// Painter depends on the Turtle interface to draw
#include "turtle.h"

///////////////////////////
// Definition of Painter //
///////////////////////////
class Painter {
public:
  // Constructor: receives a pointer to a Turtle (likely a real or mock subclass)
  // The 'explicit' keyword prevents implicit conversion if someone accidentally passes a raw pointer
  explicit Painter(Turtle* turtle) : turtle_(turtle) {}

  // DrawRectangle method: instructs the turtle to draw a rectangle
  // Parameters:
  //   - width: the length of the horizontal sides
  //   - height: the length of the vertical sides
  bool DrawRectangle(int width, int height) {
    turtle_->PenDown(); // Start drawing

    for (int i = 0; i < 2; ++i) {
      // Move forward by 'width' units
      turtle_->Forward(width);
      // Turn 90 degrees to prepare for vertical edge
      turtle_->Turn(90);
      // Move forward by 'height' units
      turtle_->Forward(height);
      // Turn 90 degrees again to prepare for the next horizontal edge
      turtle_->Turn(90);
    }

    turtle_->PenUp(); // Stop drawing after completing the rectangle
    return true;       // Indicate the draw operation succeeded
  }

private:
  // Pointer to a Turtle object used to delegate drawing behavior
  // This is a form of dependency injection and enables testability (e.g., with mocks)
  Turtle* turtle_;
};

