# Introduction to Robotics (2023 - 2024)

This is a repository of my solutions to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files

<details>
  <summary>  
    Homework 1 - RGB LED
  </summary>
  
  ### RGB LED with 3 potentiometers
  ### Components:
  * 1 RGB LED
  * 3 potentiometers
  * 1 resistor and wires as needed
  ### Technical Task:
  * Use a separate potentiometer for controlling each color of the RGB LED: Red, Green, and Blue. This control must leverage digital electronics. Specifically, you need to read the potentiometer’s value with Arduino and then write a mapped value to the LED pins.
### Photo:
![](https://github.com/Moarcas/IntroductionToRobotics/blob/master/Homework1/homework1.jpg)

### Video:
[![Watch the video](https://img.youtube.com/vi/LmKkNPQ6G3c/maxresdefault.jpg)](https://youtube.com/shorts/LmKkNPQ6G3c?feature=share)
</details>

<details>
  <summary>
    Homework2 - Elevator simulator
  </summary>
  
  ### Elevator simulator
  ### Components:
  * 4 LEDs (3 for each floor and 1 for the elevator's operational state)
  * 3 buttons for floor calls
  * 1 buzzer
  * resistors and wires as needed
  ### Technical Task:
  * Design a control system that simulates a 3-floor elevator using the Arduino
    platform. Here are the specific requirements:
    * LED Indicators: Each of the 3 LEDs should represent one of the 3 floors.
      The LED corresponding to the current floor should light up. Additionally,
      another LED should represent the elevator’s operational state. It should
      blink when the elevator is moving and remain static when stationary.
    * Buttons: Implement 3 buttons that represent the call buttons from the
      3 floors. When pressed, the elevator should simulate movement towards
      the floor after a short interval (2-3 seconds).
    * Buzzer:
      The buzzer should sound briefly during the following scenarios:
      * Elevator arriving at the desired floor (something resembling a ”cling”).
      * Elevator doors closing and movement (pro tip: split them into 2
      different sounds)
    * State Change & Timers: If the elevator is already at the desired floor,
      pressing the button for that floor should have no effect. Otherwise, after
      a button press, the elevator should ”wait for the doors to close” and then
      ”move” to the corresponding floor. If the elevator is in movement, it
      should either do nothing or it should stack its decision (get to the first
      programmed floor, open the doors, wait, close them and then go to the
      next desired floor).
    * Debounce: Remember to implement debounce for the buttons to avoid
      unintentional repeated button presses.
  ### Bonus - decision-stack":
  * Added a "decision-stack”. When using a normal elevator, you usually
    press multiple numbers and the elevator takes you there in order.
  * I incorporated a linked list to keep track of every button pressed, creating a "decision-stack" feature.
  
  ### Photo:
  ![](https://github.com/Moarcas/IntroductionToRobotics/blob/master/Homework2/Homework2.jpg)

  ### Video:
  [![Watch the video](https://img.youtube.com/vi/2r7shoO6HCo/maxresdefault.jpg)](https://youtube.com/shorts/2r7shoO6HCo?feature=share)
  </details>

  <details>
    <summary>
       Homework3 - 7 segment display drawing
    </summary>
    
<h1 align="center">Homework3 - 7 Segment Display Drawing</h1>

<p align="center">
  <img src="https://github.com/Moarcas/IntroductionToRobotics/blob/master/Homework3/homework3.jpg" alt="7 Segment Display Photo">
</p>

<h2 align="center">General description:</h2>

<p align="center">
  You will use the joystick to control the position of
  the segment and ”draw” on the display. The movement between segments
  should be natural, meaning they should jump from the current position
  only to neighbors, but without passing through ”walls”.
</p>

<h2 align="center">Components</h2>

- 1 x 7-segment display
- 1 x joystick
- Resistors and wires as needed

<h2 align="center">Technical Task</h2>

<p align="center">
  The 7-segment display should have the initial position on the DP (decimal point). The current position always blinks, regardless of whether the segment is on or off. The joystick is used to move from one position to its neighboring segments.
</p>

<h2 align="center">Button Functions</h2>

- Short pressing the button toggles the segment state from ON to OFF or from OFF to ON.
- Long pressing the button resets the entire display by turning all the segments OFF and moving the current position to the decimal point.

<h2 align="center">Video</h2>

<p align="center">
  <a href="https://youtu.be/SJGTRuJBMLk">
    <img src="https://img.youtube.com/vi/SJGTRuJBMLk/maxresdefault.jpg" alt="Watch the video">
  </a>
</p>
  </details>
  


