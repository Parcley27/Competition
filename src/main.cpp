/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Choose autonomous mode (defend or attack)
const bool autonomousIsOffensive = false;

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void offensiveAutonomous(void) {
  // Offensive Autonomous code here
}

void defensiveAutonomous(void) {
  // Defensive Autonomous code here
  robotDrive.setDriveVelocity(100.0, pct);
  robotDrive.setTurnVelocity(100.0, pct);
  
  // Drive to middle and turn
  robotDrive.driveFor(130, distanceUnits::cm);
  robotDrive.turnToHeading(-90.0, rotationUnits::deg);

  // Score ball
  intake.spin(reverse);
  robotDrive.setDriveVelocity(10.0, pct);
  robotDrive.driveFor(10.0, distanceUnits::cm);
  robotDrive.setDriveVelocity(100.0, pct);
  robotDrive.driveFor(-20.0, distanceUnits::cm);
  intake.stop();

  // Turn around and grab new ball
  robotDrive.turnToHeading(90.0, rotationUnits::deg);
  intake.spin(forward);
  robotDrive.driveFor(20.0, distanceUnits::cm);
  robotDrive.turnToHeading(-90.0, rotationUnits::deg);
  robotDrive.driveFor(40.0, distanceUnits::cm);
  intake.spin(reverse);
  robotDrive.driveFor(-20.0, distanceUnits::cm);
  intake.stop();

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  /*
  Brain.Screen.newLine();
  Brain.Screen.print("Ready for user controll");
  */

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // Tribal intake
    if (mainController.ButtonR1.pressing()) {
      // Pull ball in
      intake.spin(forward);

    } else if (mainController.ButtonR2.pressing()) {
      // Push ball out
      intake.spin(reverse);

    } else {
      // Stop motor
      intake.stop();
    }

    /* Not used
    // Arm motor
    if (mainController.ButtonL1.pressing()) {
      // Move arm up
      arm.spin(forward);

    } else if (mainController.ButtonL2.pressing()) {
      // Move arm down
      arm.spin(reverse);

    } else {
      // Stop motor
      arm.stop();
    }
    */

    // Drivetrain controller
    // Refer to block battle car code. Remember to leave easy joystick cusomization
    // https://github.com/Parcley27/Arduino-Block-Battle/blob/main/Car_Software.ino#L229

    /* Input key
    .Axis1 == Left/Right on Right
    .Axis2 == Up/Down on Right

    .Axis3 == Up/Down on Left
    .Axis4 == LeftRight on Left
    */

    // Motor speed and turining modifiers
    int speedModifier = 100;
    int turnStrength = 100;

    // Get controller axis measurements
    int yAxis = mainController.Axis3.position();
    int xAxis = mainController.Axis1.position();

    // Set motor and turn speeds
    int motorSpeed = yAxis;
    int turnSpeed = xAxis;

    // Modify speeds
    motorSpeed = motorSpeed * speedModifier / 100;
    turnSpeed = turnSpeed * turnStrength / 100;

    // Find motor speeds
    double leftSideSpeed = motorSpeed + turnSpeed;
    double rightSideSpeed = motorSpeed - turnSpeed;

    // Set motor velocities
    leftMotor.setVelocity(leftSideSpeed, pct);
    rightMotor.setVelocity(rightSideSpeed, pct);

    // Turn on motors
    leftMotor.spin(fwd);
    rightMotor.spin(fwd);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.

  if (autonomousIsOffensive == true) {
    // Run offensive auton.
    Competition.autonomous(offensiveAutonomous);
  } else if (autonomousIsOffensive == false) {
    // Run defensive auton.
    Competition.autonomous(defensiveAutonomous);
  }

  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
