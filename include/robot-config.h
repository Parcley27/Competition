using namespace vex;

// Include brain for main.cpp
extern brain Brain;

// Include drivetrain for main.cpp
extern smartdrive robotDrive;

// Include raw drivetrain motors for main.cpp
extern motor leftMotor;
extern motor rightMotor;

// Include other motors for main.cpp
//extern motor arm;
extern motor intake;

extern controller mainController;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
