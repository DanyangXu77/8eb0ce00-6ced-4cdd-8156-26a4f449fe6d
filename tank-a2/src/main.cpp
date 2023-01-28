#include <stdio.h>
#include <string>

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         13              
// FrontRight           motor         17              
// MiddleLeft           motor         14              
// MiddleRight          motor         18              
// BackLeft             motor         15              
// BackRight            motor         19              
// Flywheel             motor         16              
// Inertial             inertial      20              
// Piston               digital_out   B               
// Controller1          controller                    
// Intake               motor         12              
// AngleChanger         digital_out   A               
// AirRelease           digital_out   D               
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

double pi = 3.1415926535897932384626433;

int brainLines = 0;

int velocity_ = 0;

float a = 0;
float b = 0;
float c = 0;

int reversed = 1;
bool reversed2 = true;

bool stop = false;
bool stop2 = true;

bool fly = true;
bool fly2 = true;

bool angchg = false;
bool angchg2 = true;

bool stopFly = false;

bool e = true;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Inertial.calibrate();
}

void waitUntFlySpd(float speed) {
  while (Flywheel.velocity(rpm) < speed) {

  }
}

void spinFlywheel() {
  float gain = 0.004;
  float error = velocity_;
  float prevError = velocity_;
  float tbh = 12;
  float voltage = 0;

  while (!stopFly) {
    error = velocity_ - Flywheel.velocity(rpm);
    voltage += gain * error;
    if (abs(error) - error != abs(prevError) - prevError) {
      voltage = 0.5 * (voltage + tbh);
      tbh = voltage;
      prevError = error;
    }
    Flywheel.spin(forward, voltage, volt);
    wait(50, msec);
  }
  
  stopFly = false;
}

void ee() {
  FrontLeft.spin(forward, 2, volt);
  FrontRight.spin(forward, 2, volt);
  MiddleLeft.spin(forward, 2, volt);
}

void ee_stop() {
  FrontLeft.stop();
  FrontRight.stop();
  MiddleLeft.stop();
}

void drivef(float dist, bool rev) {
  MiddleLeft.resetPosition();
  MiddleRight.resetPosition();
  BackLeft.setStopping(brake);
  BackRight.setStopping(brake);
  FrontLeft.setStopping(brake);
  FrontRight.setStopping(brake);
  MiddleLeft.setStopping(brake);
  MiddleRight.setStopping(brake);
  float deg = dist * 3 / 5 * 360 / 3.25 / pi;
  if (rev) {
    while (-1 * MiddleLeft.position(degrees) < deg) {
      FrontLeft.spin(reverse, 9, volt);
      FrontRight.spin(reverse, 9, volt);
      MiddleLeft.spin(reverse, 9, volt);
      MiddleRight.spin(reverse, 9, volt);
      BackLeft.spin(reverse, 9, volt);
      BackRight.spin(reverse, 9, volt);
    }
    FrontLeft.stop();
    FrontRight.stop();
    MiddleLeft.stop();
    MiddleRight.stop();
    BackLeft.stop();
    BackRight.stop();
  } else {
    while (MiddleLeft.position(degrees) < deg) {
      FrontLeft.spin(forward, 9, volt);
      FrontRight.spin(forward, 9, volt);
      MiddleLeft.spin(forward, 9, volt);
      MiddleRight.spin(forward, 9, volt);
      BackLeft.spin(forward, 9, volt);
      BackRight.spin(forward, 9, volt);
    }
    FrontLeft.stop();
    FrontRight.stop();
    MiddleLeft.stop();
    MiddleRight.stop();
    BackLeft.stop();
    BackRight.stop();
  }
}

void drivefs(float dist, bool rev) {
  MiddleLeft.resetPosition();
  MiddleRight.resetPosition();
  BackLeft.setStopping(hold);
  BackRight.setStopping(hold);
  FrontLeft.setStopping(hold);
  FrontRight.setStopping(hold);
  MiddleLeft.setStopping(hold);
  MiddleRight.setStopping(hold);
  float deg = dist * 3 / 5 * 360 / 3.25 / pi;
  if (rev) {
    while (-1 * MiddleLeft.position(degrees) < deg) {
      FrontLeft.spin(reverse, 5, volt);
      FrontRight.spin(reverse, 5, volt);
      MiddleLeft.spin(reverse, 5, volt);
      MiddleRight.spin(reverse, 5, volt);
      BackLeft.spin(reverse, 5, volt);
      BackRight.spin(reverse, 5, volt);
    }
    FrontLeft.stop();
    FrontRight.stop();
    MiddleLeft.stop();
    MiddleRight.stop();
    BackLeft.stop();
    BackRight.stop();
  } else {
    while (MiddleLeft.position(degrees) < deg) {
      FrontLeft.spin(forward, 5, volt);
      FrontRight.spin(forward, 5, volt);
      MiddleLeft.spin(forward, 5, volt);
      MiddleRight.spin(forward, 5, volt);
      BackLeft.spin(forward, 5, volt);
      BackRight.spin(forward, 5, volt);
    }
    FrontLeft.stop();
    FrontRight.stop();
    MiddleLeft.stop();
    MiddleRight.stop();
    BackLeft.stop();
    BackRight.stop();
  }
}

void rotate(float deg, bool dir) {
  float a = 0;
  Inertial.resetRotation();
  BackLeft.setStopping(hold);
  BackRight.setStopping(hold);
  FrontLeft.setStopping(hold);
  FrontRight.setStopping(hold);
  MiddleLeft.setStopping(hold);
  MiddleRight.setStopping(hold);
  if (dir) {
    FrontLeft.spin(reverse, 4, volt);
    FrontRight.spin(forward, 4, volt);
    MiddleLeft.spin(reverse, 4, volt);
    MiddleRight.spin(forward, 4, volt);
    BackLeft.spin(reverse, 4, volt);
    BackRight.spin(forward, 4, volt);
    while (Inertial.rotation(degrees) > -deg) {
    }
    FrontLeft.spin(forward, 3, volt);
    FrontRight.spin(reverse, 3, volt);
    MiddleLeft.spin(forward, 3, volt);
    MiddleRight.spin(reverse, 3, volt);
    BackLeft.spin(forward, 3, volt);
    BackRight.spin(reverse, 3, volt);
    while (Inertial.rotation(degrees) < -deg) {
    }
    FrontLeft.spin(reverse, 2, volt);
    FrontRight.spin(forward, 2, volt);
    MiddleLeft.spin(reverse, 2, volt);
    MiddleRight.spin(forward, 2, volt);
    BackLeft.spin(reverse, 2, volt);
    BackRight.spin(forward, 2, volt);
    while (Inertial.rotation(degrees) > -deg) {
    }
    FrontLeft.spin(forward, 1, volt);
    FrontRight.spin(reverse, 1, volt);
    MiddleLeft.spin(forward, 1, volt);
    MiddleRight.spin(reverse, 1, volt);
    BackLeft.spin(forward, 1, volt);
    BackRight.spin(reverse, 1, volt);
    while (Inertial.rotation(degrees) < -deg && a < 3) {
      a += 0.02;
    }
    FrontLeft.stop();
    FrontRight.stop();
    MiddleLeft.stop();
    MiddleRight.stop();
    BackLeft.stop();
    BackRight.stop();
  } else {
    FrontLeft.spin(forward, 4, volt);
    FrontRight.spin(reverse, 4, volt);
    MiddleLeft.spin(forward, 4, volt);
    MiddleRight.spin(reverse, 4, volt);
    BackLeft.spin(forward, 4, volt);
    BackRight.spin(reverse, 4, volt);
    while (Inertial.rotation(degrees) < deg) {
    }
    FrontLeft.spin(reverse, 3, volt);
    FrontRight.spin(forward, 3, volt);
    MiddleLeft.spin(reverse, 3, volt);
    MiddleRight.spin(forward, 3, volt);
    BackLeft.spin(reverse, 3, volt);
    BackRight.spin(forward, 3, volt);
    while (Inertial.rotation(degrees) > deg) {
    }
    FrontLeft.spin(forward, 2, volt);
    FrontRight.spin(reverse, 2, volt);
    MiddleLeft.spin(forward, 2, volt);
    MiddleRight.spin(reverse, 2, volt);
    BackLeft.spin(forward, 2, volt);
    BackRight.spin(reverse, 2, volt);
    while (Inertial.rotation(degrees) < deg) {
    }
    FrontLeft.spin(reverse, 1, volt);
    FrontRight.spin(forward, 1, volt);
    MiddleLeft.spin(reverse, 1, volt);
    MiddleRight.spin(forward, 1, volt);
    BackLeft.spin(reverse, 1, volt);
    BackRight.spin(forward, 1, volt);
    while (Inertial.rotation(degrees) > deg && a < 3) {
      a += 0.02;
    }
    FrontLeft.stop();
    FrontRight.stop();
    MiddleLeft.stop();
    MiddleRight.stop();
    BackLeft.stop();
    BackRight.stop();
  }
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

void autonomous(void) {
  thread sf(spinFlywheel);
  
  Intake.setMaxTorque(100, percent);
  Flywheel.setMaxTorque(100, percent);
  BackLeft.setMaxTorque(100, percent);
  BackRight.setMaxTorque(100, percent);
  FrontLeft.setMaxTorque(100, percent);
  FrontRight.setMaxTorque(100, percent);
  MiddleLeft.setMaxTorque(100, percent);
  MiddleRight.setMaxTorque(100, percent);
  BackLeft.setVelocity(200, rpm);
  BackRight.setVelocity(200, rpm);
  FrontLeft.setVelocity(200, rpm);
  FrontRight.setVelocity(200, rpm);
  MiddleLeft.setVelocity(200, rpm);
  MiddleRight.setVelocity(200, rpm);
  BackLeft.setStopping(hold);
  BackRight.setStopping(hold);
  FrontLeft.setStopping(hold);
  FrontRight.setStopping(hold);
  MiddleLeft.setStopping(hold);
  MiddleRight.setStopping(hold);

  Intake.spin(forward, 100, percent);
  velocity_ = 200;
  drivef(24, false);
  rotate(22.5, false);
  drivef(18, false);
  Intake.stop();
  waitUntFlySpd(177.5);
  Intake.spinFor(reverse, 400, degrees, 600, rpm);
  waitUntFlySpd(177.5);
  Intake.spinFor(reverse, 400, degrees, 600, rpm);
  waitUntFlySpd(177.5);
  Intake.spinFor(reverse, 400, degrees, 600, rpm);
  wait(500, msec);
  rotate(67.5, false);
  drivef(30, true);
  rotate(45, true);
  drivef(9, true);
  ee();
  drivef(1, true);
  Intake.spinFor(forward, 600, degrees, 200, rpm);
  ee_stop();

  // Intake.spin(forward, 100, percent);
  // Flywheel.spin(forward, 100, percent);
  // drivef(12, false);
  // drivefs(14, false);
  // rotate(150, true);
  // Intake.stop();
  // Indexer.set(true);
  // wait(150, msec);
  // Indexer.set(false);
  // wait(750, msec);
  // Indexer.set(true);
  // wait(150, msec);
  // Indexer.set(false);
  // wait(750, msec);
  // Indexer.set(true);
  // wait(150, msec);
  // Indexer.set(false);
  // wait(100, msec);
  // drivef(3, false);
  // Flywheel.stop();
  // rotate(70, true);
  // drivef(30, false);
  // rotate(45, false);
  // drivef(5, false);
  // ee();
  // Intake.spinFor(reverse, 360, degrees, 100, rpm);
  // ee_stop();
  // wait(500, msec);
  // rot40();
  // rotArc();
  // drivef(10, false);
  // FrontLeft.spin(forward, 2, volt);
  // MiddleLeft.spin(forward, 2, volt);
  // BackLeft.spin(forward, 2, volt);
  // Intake.spinFor(reverse, 420, degrees, 100, rpm);
  wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                 e - Andrew Zhao 2022            User Control Task         */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  thread sf(spinFlywheel);

  Intake.spin(forward, 12, volt);
  BackLeft.setStopping(coast);
  BackRight.setStopping(coast);
  FrontLeft.setStopping(coast);
  FrontRight.setStopping(coast);
  MiddleLeft.setStopping(coast);
  MiddleRight.setStopping(coast);
  Intake.setMaxTorque(100, percent);
  Flywheel.setMaxTorque(100, percent);
  BackLeft.setMaxTorque(100, percent);
  BackRight.setMaxTorque(100, percent);
  FrontLeft.setMaxTorque(100, percent);
  FrontRight.setMaxTorque(100, percent);
  MiddleLeft.setMaxTorque(100, percent);
  MiddleRight.setMaxTorque(100, percent);
  Flywheel.setVelocity(200, rpm);
  BackLeft.setVelocity(200, rpm);
  BackRight.setVelocity(200, rpm);
  FrontLeft.setVelocity(200, rpm);
  FrontRight.setVelocity(200, rpm);
  MiddleLeft.setVelocity(200, rpm);
  MiddleRight.setVelocity(200, rpm);
  velocity_ = 170;

  // User control code here, inside the loop
  while (1) {
    b = Controller1.Axis2.position(percent);
    c = Controller1.Axis3.position(percent);

    // if (reversed == 1) {
    //   FrontLeft.spin(forward, c + a, percent);
    //   FrontRight.spin(forward, c - a, percent);
    //   BackLeft.spin(forward, c + a, percent);
    //   BackRight.spin(forward, c - a, percent);
    //   MiddleLeft.spin(forward, c + a, percent);
    //   MiddleRight.spin(forward, c - a, percent);
    // } else {
    //   FrontLeft.spin(reverse, c - a, percent);
    //   FrontRight.spin(reverse, c + a, percent);
    //   BackLeft.spin(reverse, c - a, percent);
    //   BackRight.spin(reverse, c + a, percent);
    //   MiddleLeft.spin(reverse, c - a, percent);
    //   MiddleRight.spin(reverse, c + a, percent);
    // }

    if (reversed == 1) {
      FrontLeft.spin(forward, c, percent);
      FrontRight.spin(forward, b, percent);
      BackLeft.spin(forward, c, percent);
      BackRight.spin(forward, b, percent);
      MiddleLeft.spin(forward, c, percent);
      MiddleRight.spin(forward, b, percent);
    } else {
      FrontLeft.spin(reverse, b, percent);
      FrontRight.spin(reverse, c, percent);
      BackLeft.spin(reverse, b, percent);
      BackRight.spin(reverse, c, percent);
      MiddleLeft.spin(reverse, b, percent);
      MiddleRight.spin(reverse, c, percent);
    }

    if (Controller1.ButtonL1.pressing() && !Controller1.ButtonR1.pressing()) {
      Intake.spin(forward, 100, percent);
    } else if (Controller1.ButtonR1.pressing()) {
      Intake.spin(reverse, 100, percent);
    } else {
      Intake.stop();
    }

    if (Controller1.ButtonL2.pressing()) {
      if (fly2) {
        fly = !fly;
        fly2 = false;
        if (fly) {
          velocity_ = 180;
        } else {
          velocity_ = 0;
        }
      }
    } else {
      fly2 = true;
    }

    if (Controller1.ButtonX.pressing()) {
      if (reversed2) {
        reversed = !reversed;
        reversed2 = false;
        if (reversed) {
          Controller1.Screen.newLine();
          Controller1.Screen.print("Drivetrain Reversed         ");
          Brain.Screen.newLine();
          Brain.Screen.print("[INFO] Drivetrain Reversed");
          brainLines += 1;
        } else {
          Controller1.Screen.newLine();
          Controller1.Screen.print("Drivetrain Forward          ");
          Brain.Screen.newLine();
          Brain.Screen.print("[INFO] Drivetrain Forward");
          brainLines += 1;
        }
      }
    } else {
      reversed2 = true;
    }

    if (Controller1.ButtonA.pressing()) {
      Controller1.Screen.newLine();
      Controller1.Screen.print("Flywheel Speed: ");
      Controller1.Screen.print(Flywheel.velocity(percent));
      Controller1.Screen.print("           ");
      Brain.Screen.newLine();
      Brain.Screen.print("[INFO] Flywheel Speed: ");
      Brain.Screen.print(Flywheel.velocity(percent));
      brainLines += 1;
    }

    if (Controller1.ButtonR2.pressing()) {
      if (angchg2) {
        angchg = !angchg;
        AngleChanger.set(angchg);
        angchg2 = false;
      }
    } else {
      angchg2 = true;
    }

    if (Controller1.ButtonLeft.pressing()) {
      stopFly = true;
    }

    if (Controller1.ButtonRight.pressing()) {
      Piston.set(true);
      Controller1.Screen.newLine();
      Controller1.Screen.print("Releasing Extension    ");
      Brain.Screen.newLine();
      Brain.Screen.print("[INFO] Releasing Extension    ");
      brainLines += 1;
      wait(1000, msec);
      Controller1.Screen.newLine();
      Controller1.Screen.print("Releasing Air        ");
      Brain.Screen.newLine();
      Brain.Screen.print("[INFO] Releasing Air");
      AirRelease.set(true);
      brainLines += 1;
    }

    if (brainLines > 12) {
      brainLines = 0;
      Brain.Screen.setCursor(0, 1);
      Brain.Screen.clearScreen();
    }
  }
  wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}