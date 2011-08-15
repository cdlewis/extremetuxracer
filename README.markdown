Extreme Tux Racer
=================

This is a fork of Extreme Tux Racer with support for Microsoft's Kinect sensor as an input device on the Windows platform. As Tux accelerates down the race track, the user can steer the penguin by tilting his or her head left or right, lean forward to paddle, and lean back to brake. Watch a [video](http://www.vimeo.com/27603312) of this in action!

Overview
--------

In order to maintain compatibility with Linux and Mac OS X, all of the Kinect processing is done in a standalone C# application. All skeletal information of interest to Extreme Tux Racer is transmitted via a UDP socket. Thanks to this modularized design, Extreme Tux Racer can still be compiled on platforms for which the official Kinect SDK is not available. As another benefit, the original Extreme Tux Racer source didn't have to be adapted so it compiles with Visual Studio.

Usage
-----

To try Extreme Tux Racer's Kinect support, make sure the latest beta of the Kinect for Windows SDK is installed on your machine; then compile `KinectDaemon` with Visual Studio. Connect your Kinect sensor and run the executable to start processing skeletal information.

Next, compile Extreme Tux Racer on Windows in a [MingGW](http://www.mingw.org/) environment via the Makefile provided. Make sure SDL, SDL\_image, SDL\_net, SDL_mixer, freetype2, libpng, zlib, libintl, and ActiveTcl are installed. When you start the game, a UDP server socket will be created. Once a new race begins, simply tilt left, right, forward, or back to control Tux.

The game runs best when the resolution is cranked all the way up.
