cmake_minimum_required(VERSION 3.10)

project(Robot_Contest)

# add the executable
add_executable(robotContest
        src/robotContest.cpp
        src/RobotContestSimulator.cpp
	src/HardwareSimulator.cpp
	src/UserInterface.cpp
	src/Robot.cpp
	src/BeaconSensor.cpp
	src/HWBeaconSensor.cpp
	src/Clock.cpp
	src/InputPort.cpp
	src/OutputPort.cpp
	src/PlayingField.cpp
	src/Processor.cpp
	src/TouchSensor.cpp
	src/HWTouchSensor.cpp
	src/Vector.cpp
	src/Matrix.cpp
	src/Motor.cpp
	src/Integrator.cpp
	src/nrutil.cpp
	src/InteractingRobots.cpp
	src/MotorDriverElectronics.cpp
	src/RobotController.cpp
	src/PlaceboRobotController.cpp
	src/DouglasRobotController.cpp
	src/MoralesRobotController.cpp
	src/StokesRobotController.cpp
	src/MulhollandRobotController.cpp)

target_include_directories(robotContest PUBLIC include)
