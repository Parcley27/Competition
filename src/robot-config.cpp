#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// Drivetrain
motor leftMotor = motor(PORT1, ratio18_1, false);
motor rightMotor = motor(PORT2, ratio18_1, true);

inertial robotInertial = inertial(PORT12);

smartdrive robotDrive = smartdrive(leftMotor, rightMotor, robotInertial, 319.9, 320, 40, mm, 1);

// Arm
//motor arm = motor(PORT3, ratio18_1, false);

// Intake
motor intake = motor(PORT3, ratio18_1, false);

// Controller
controller mainController = controller(primary);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */

void vexcodeInit(void) {
  // Start robot setup (initalization)
  Brain.Screen.print("Initalizing Robot...");
  Brain.Screen.newLine();

  // Calibrate inertial sensor for drivetrain
  Brain.Screen.newLine();
  Brain.Screen.print("Calibrating Interial Sensor...");
  robotInertial.calibrate();

  // Budget thread pause
  while (robotInertial.isCalibrating()) {
    // Wait
  }

  Brain.Screen.newLine();
  Brain.Screen.print("Inertial Sensor Calibrated");
  Brain.Screen.newLine();

  // Set drivetrain profiles
  Brain.Screen.newLine();
  Brain.Screen.print("Setting Drivetrain Profiles...");

  robotDrive.setDriveVelocity(75, percent);
  robotDrive.setTurnVelocity(50, percent);

  leftMotor.setStopping(brake);
  rightMotor.setStopping(brake);

  Brain.Screen.newLine();
  Brain.Screen.print("Drivetrain Ready");
  Brain.Screen.newLine();

  // Set motor profiles
  Brain.Screen.newLine();
  Brain.Screen.print("Setting Motor Profiles...");

  /* Block out arm because it is not being used any more
  arm.setVelocity(100, percent);
  arm.setReversed(false);
  arm.setStopping(brake);
  */

  intake.setVelocity(100, percent);
  intake.setReversed(false);
  intake.setStopping(brake);

  Brain.Screen.newLine();
  Brain.Screen.print("Motors Ready");
  Brain.Screen.newLine();

  // Display completed state
  Brain.Screen.newLine();
  Brain.Screen.print("Robot Ready");

}