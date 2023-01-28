#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT13, ratio6_1, true);
motor FrontRight = motor(PORT17, ratio6_1, false);
motor MiddleLeft = motor(PORT14, ratio18_1, true);
motor MiddleRight = motor(PORT18, ratio6_1, false);
motor BackLeft = motor(PORT15, ratio6_1, true);
motor BackRight = motor(PORT19, ratio6_1, false);
motor Flywheel = motor(PORT16, ratio18_1, false);
inertial Inertial = inertial(PORT20);
digital_out Piston = digital_out(Brain.ThreeWirePort.B);
controller Controller1 = controller(primary);
motor Intake = motor(PORT12, ratio6_1, true);
digital_out AngleChanger = digital_out(Brain.ThreeWirePort.A);
digital_out AirRelease = digital_out(Brain.ThreeWirePort.D);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}