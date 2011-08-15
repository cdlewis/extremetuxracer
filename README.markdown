Extreme Tux Racer
=================

This is a fork of Extreme Tux Racer which supports Microsoft's Kinect sensor as an input device on the Windows platform. As Tux accelerates down the racetrack, the user can steer the penguin by tilting his or her head left or right; lean forward to paddle and backward to brake.

Overview
--------

In order to maintain compatibility with Linux and Mac OS X, all of the Kinect processing is done in a standalone C# application. All skeletal information interesting to Extreme Tux Racer is transmitted via a UDP socket. Thanks to this modularized design, Extreme Tux Racer can still be compiled on platforms for which the official Kinect SDK is not available. As another benefit, the original Extreme Tux Racer source didn't have to be adapted so it compiles with Visual Studio.

Usage
-----

To try Extreme Tux Racer's Kinect support, make sure the latest beta of the Kinect for Windows SDK is installed on your machine; then compile the KinectDaemon with Visual Studio. Connect your Kinect sensor and run the executable to start processing skeletal information.

Compile Extreme Tux Racer on Windows in the [MingGW](http://www.mingw.org/) environment via the Makefile provided. Make sure SDL, SDL\_image, SDL\_net, SDL_mixer, freetype2, libpng, zlib, libintl, and ActiveTcl are installed. When you start the game, a UDP server connection will be established. Once a new race begins, simply tilt left, right, forward, or back to control Tux. The game runs best when the resolution is cranked all the way up.
