# PINS and NEEDLES
PINS (Pygmalion Integrated Network System) is a real-time connection monitor dashboard that reads, manages, and modifies client connections. 
The objective of this application is to provide developers with an easy to set up host server that manages real-time connections for 
applications such as multiplayer games, collaborative editing, and more. 

## Features

### Planned Features

Currently PINS and NEEDLES has these major features planned for development:
- Connection Management UI
- Custom Scripting
- Whitelisting/Blacklisting
- Custom Packets
- Open Source SDK

## How to Use
PINS refers to the graphical UI host application that accepts and manages client connections, while NEEDLES refers to the backend SDK that developers
can use to create client connections to connect with a PINS host.

## Progress
Currently we are working on NEEDLES to support the creation of PINS. 

## Getting Started
To get started, run the following to clone the repository:

```
git clone --recursive https://github.com/Pygmalion-Project/PINS
```

This will initialize and download all the required git submodules for the dependencies PINS uses. If you've already
cloned PINS normally, you can also run the following to download submodules:

```
git submodule update --init --recursive
```

Once everything is properly cloned, navigate to the scripts folder and run the setup script for your respective OS! For example,
for windows users the commands will be:

```
cd scripts
./WIN_Setup.bat
```

Note that this builds project files for **Visual Studio 2019**. If you use a different version of visual studio, you may need to use a different version of premake
(located in the `vendor/premake/bin` folder) and modify the respective build script. 

This will generate all the solution files needed using premake. Once that succeeds, you're all set! You can now open the .sln file in Visual Studio 2019 and start 
using PINS! The startup project should be specified to PINS, so you'll be able to just press Run and Debug to try it out!