There are a few quirks to be aware of with this program:

1. Some teams' runControlLoop() code depends on their classes being in
   some initial state, which is set when their Robot Controller object
   is instantiated. For this reason, if you want to watch the same
   pursuer and evader competition more than once, you will need to
   make sure that the pursuer and evader objects get deleted and then
   created again.  This can be done by choosing menu option 6, "Change
   players."  For example: suppose you watched pursuer 3 versus evader
   2, and you'd like to watch it again.  To ensure you reinitialized
   the robot controllers, you would need to choose option 6, "Change
   players" and choose pursuer 3 and evader 2 again. This will delete
   the RobotController objects and then re-create them.  Then, you'd
   also want to choose menu option 5, "Reset simulation."

2. I added a menu option 4, "Display processor state," mainly for
   debugging purposes. If you choose this, you will be able to see the
   values for processor output ports 0 and 1, the value for processor
   input port 0, and the current time that the simulated processor
   has.  Processor output ports 0 and 1 are connected to the right and
   left motors, respectively. So, for example, if you choose option 4,
   and it says that processor output port number 1 is set to 0x84,
   then that means that during the previous time step, the robot
   controller might have done something like

     leftMotor.setVoltage( -0.3 );

   since 0.3 / 0.075 = 4, and the 1 in the 7th bit position in 0x84
   means that a negative value should be used.

   The input ports are "wired" as follows: bit 0 is connected to the
   beacon sensor, bit 1 is connnected to the right touch sensor, and
   bit 2 is connected to the left touch sensor. So, if the program
   says that the input port is set to 0x05, this means that during the
   previous time step, the beacon sensor (bit 0) detected the beacon
   of the other robot, the left touch sensor (bit 2) detected a robot
   or a wall, and the right touch sensor (bit 1) did not detect
   anything.

   Keep in mind that these values come from the previous time step and
   thus do not necessarily reflect the current situation.

3. This program was put together very quickly and there are likely
   bugs/defects that I haven't discovered yet.  Please let me know if
   you discover any.
