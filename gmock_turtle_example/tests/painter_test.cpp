#include <gtest/gtest.h>           // Google Test framework for writing unit tests
#include "mock_turtle.h"           // Includes the mock class that simulates the Turtle interface
#include "../include/painter.h"    // Includes the Painter class you're testing

// Common Google Mock matchers to simplify assertions
using ::testing::AtLeast;          // Matches when a method is called at least N times
using ::testing::Exactly;          // Matches when a method is called exactly N times
using ::testing::_;                // Wildcard: matches any parameter (used for flexibility)

// Test fixture class that sets up a reusable test environment
// Inherits from ::testing::Test to allow shared setup between multiple test cases
class PainterTest : public ::testing::Test {
protected:
//  MockTurtle turtle;               // Mock object to simulate drawing behavior
    testing::NiceMock<MockTurtle> turtle;
    Painter painter{&turtle};        // Painter under test, initialized with the mock turtle
};


// This test verifies that Painter::DrawRectangle() produces the correct drawing commands
TEST_F(PainterTest, DrawsRectangle) {
  // Expect the pen to be placed down at least once (to begin drawing)
  EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));

  // NOTE: The following line is commented out; it should be corrected to:
  // Expect the turtle to move forward 4 times (2 width + 2 height) with any value
  // EXPECT_CALL(turtle, Forward(_)).Times(Exactly(4));

  // Expect four right-angle turns (90° each) — one after each side
  EXPECT_CALL(turtle, Turn(90)).Times(Exactly(4));

  // Expect the pen to be lifted at least once after drawing completes
  EXPECT_CALL(turtle, PenUp()).Times(AtLeast(1));

  // Assert that the DrawRectangle call returns true, indicating successful drawing logic
  EXPECT_TRUE(painter.DrawRectangle(100, 50));
}


// This test case verifies that Painter::DrawRectangle() calls Turtle methods
// in the exact order required to draw a rectangle of size 100x50.
TEST_F(PainterTest, SequenceMatters) {
  using ::testing::Sequence;  // Import Google Mock's Sequence utility
  Sequence seq;               // Create a sequence object to enforce method call order

  // Begin enforcing a strict sequence of expected Turtle calls:

  EXPECT_CALL(turtle, PenDown()).InSequence(seq);
  // The pen must go down before any drawing begins

  EXPECT_CALL(turtle, Forward(100)).InSequence(seq);
  // Move forward to draw the top side (width = 100)

  EXPECT_CALL(turtle, Turn(90)).InSequence(seq);
  // Turn to start drawing the right vertical side

  EXPECT_CALL(turtle, Forward(50)).InSequence(seq);
  // Draw the right side (height = 50)

  EXPECT_CALL(turtle, Turn(90)).InSequence(seq);
  // Turn to face the bottom edge

  EXPECT_CALL(turtle, Forward(100)).InSequence(seq);
  // Draw the bottom side (same width)

  EXPECT_CALL(turtle, Turn(90)).InSequence(seq);
  // Turn to face the left edge

  EXPECT_CALL(turtle, Forward(50)).InSequence(seq);
  // Draw the left side (same height)


  EXPECT_CALL(turtle, Turn(90)).InSequence(seq);
  // Final turn brings the turtle back to its original heading

  EXPECT_CALL(turtle, PenUp()).InSequence(seq);
  // Lift the pen after completing the rectangle
  // Ensures no unintended drawing as the turtle exits

  // Trigger the actual operation
  painter.DrawRectangle(100, 50);
  // This should invoke all the expected calls above, in the defined order
}

