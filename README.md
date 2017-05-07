# RoMaSynthi
The RoMaSythi is a software synthesizer written in C++, which generates sound 
in a combination of additive and subtractive synthesis. The software is part of 
a project at [TU Berlin](http://www.ak.tu-berlin.de) and the Seminar 
[Klangsynthese](https://gitlab.tubit.tu-berlin.de/henrikvoncoler/Klangsynthese_PI).

This software is designed to run on the [Raspberry Pi 3](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/) 
with a costum [Arch Linux](https://www.archlinux.org/) distribution. If you want
to try this software yourself, make sure you follow the installation instructions
below.

The following flowchart gives an overview of the 

## Open Sound Control
The RoMaSynthesizer can be controlled via OSC. We use the app TouchOSC by 
Hexler, which is available in the Android and iOS Appstores.
Alternativley a PD file can be used to control the OSC controllable parameters.