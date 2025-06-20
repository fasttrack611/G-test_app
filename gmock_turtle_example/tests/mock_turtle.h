#pragma once  // Ensures this header is included only once during compilation

#include <gmock/gmock.h>  // Imports Google Mock macros like MOCK_METHOD
#include "../include/turtle.h"  // Includes the base Turtle interface that we'll mock

// MockTurtle is a test double that simulates the Turtle interface
// It's used in unit tests to verify how other classes interact with Turtle
class MockTurtle : public Turtle {
public:
  // Mocks the PenUp() method — simulates lifting the pen so movement doesn’t draw
  MOCK_METHOD(void, PenUp, (), (override));

  // Mocks the PenDown() method — simulates putting the pen down to enable drawing
  MOCK_METHOD(void, PenDown, (), (override));

  // Mocks Forward(int distance) — simulates moving forward by a specified distance
  MOCK_METHOD(void, Forward, (int distance), (override));

  // Mocks Turn(int degrees) — simulates turning the turtle by a given angle
  MOCK_METHOD(void, Turn, (int degrees), (override));

  // Mocks GoTo(int x, int y) — simulates jumping to a specified coordinate
  MOCK_METHOD(void, GoTo, (int x, int y), (override));

  // Mocks GetX() — simulates retrieving the current X position of the turtle
  MOCK_METHOD(int, GetX, (), (const, override));

  // Mocks GetY() — simulates retrieving the current Y position of the turtle
  MOCK_METHOD(int, GetY, (), (const, override));
};

