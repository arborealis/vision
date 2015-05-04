# Entoptic Sim

OSC Client that spits out test osc data in the form of an OSC string packet that look like this:

```
[/A/C1 OSC-string:`0.934847,0.967667,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.918743,0,0,0,0,0.933927,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.983912,0,0,0.981289,0,0,0,0,0,0,0,0.928788,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.954362,0.958915,0,0,0,0,0.906563,0,0,0,0.980445,0,0,0.962922,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.931076,0,0,0.995334,0,0,0,0,0,0,0,0.982881,0,0,0,0,0,0,0,0,0.919610,0,0,0,0,0,0.956571,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.917023,0,0.931294,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0']
```
The cell values start at the left corner of the instrument/camera grid and read left to right, top to bottom.


## Requirements
* homebrew
  * ```ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"```
* git
 * ```brew install git```
* cmake
 * ```brew install cmake```
* boost
 * ```brew install boost```


## Installation
* ```git clone https://github.com/arborealis/vision.git```
* ```cd vision/entoptic-sim```
* ```cmake .``` 
* ```make```


## Usage
* ```./bin/sim [optional ip address of server] [optional port]```
 * the ip address deafults to 127.0.0.1, and port to 7000
* if you want to see the raw data being spit out, open the same directory in a different terminal window and run ```./bin/OscDump```

