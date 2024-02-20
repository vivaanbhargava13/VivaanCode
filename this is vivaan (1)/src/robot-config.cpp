#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
inertial gyroo = inertial(PORT6);
motor intake = motor(PORT15, ratio18_1, false);
motor catapult = motor(PORT4, ratio18_1, true);
digital_out horizontal = digital_out(Brain.ThreeWirePort.G);
digital_out intakepistonb = digital_out(Brain.ThreeWirePort.B);
digital_out vertical = digital_out(Brain.ThreeWirePort.H);
controller Controller1 = controller(primary);
rotation RotationRight = rotation(PORT21, false);
rotation RotationLeft = rotation(PORT3, false);
optical Opticall = optical(PORT2);
motor backleft = motor(PORT17, ratio6_1, true);
motor middleleft = motor(PORT16, ratio6_1, true);
motor frontleft = motor(PORT12, ratio6_1, true);
motor backright = motor(PORT18, ratio6_1, false);
motor middleright = motor(PORT13, ratio6_1, false);
motor frontright = motor(PORT1, ratio6_1, false);
motor cata2 = motor(PORT19, ratio18_1, false);

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