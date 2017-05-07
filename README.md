# RoMaSynthesizer
The RoMaSythesizer is a polyphone software synthesizer written in C++, which generates sound 
in a combination of additive and subtractive synthesis. The software is part of 
a project at [TU Berlin](http://www.ak.tu-berlin.de) in the seminar 
[Klangsynthese](https://gitlab.tubit.tu-berlin.de/henrikvoncoler/Klangsynthese_PI). 
This software is designed to run on the [Raspberry Pi 3](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/) 
with a costum [Arch Linux](https://www.archlinux.org/) distribution. If you want
to use this software yourself, make sure you follow the installation instructions
below. The following flowchart gives an overview of the implementation.

<p align="center">
    <img src="./Flowchart.png" width="800">
</p>

## Dependencys
### Library
The following external librarys are needed to compile the senthesizer onto your 
system:  
* [liblo](http://liblo.sourceforge.net/)
* [jackcpp](https://github.com/x37v/jackcpp)
* [rtmidi](https://www.music.mcgill.ca/~gary/rtmidi/index.html#download)
* [boost](http://www.boost.org/)

### Jack
A [Jack](http://www.jackaudio.org/) audio server is fundamental to run the 
synthesizer. Make sure you have a solid jack audio environment running. The 
buffer size we use on the Raspberry Pi is <span style="color:red">256</span> 
and the sample rate is <span style="color:red">48kHz</span>. This might differ 
from your system and you are free to find the right jack settings.

### Open Sound Control
The RoMaSynthesizer can be controlled via OSC. We use the app [TouchOSC](https://hexler.net/software/touchosc) by 
Hexler, which is available in the Android and iOS Appstores.
Alternativley the Pure Data file in ./osc can be used to control the parameters.

### Midi
To "play" the Synthesizer you need a external midi keyboard, which is shown in 
the flowchart, or you can connect in jack a software midi keyboard like the 
[Cadence-XY Controller](http://kxstudio.linuxaudio.org/Applications:Cadence-XYController).

## Installation
To install the software, make sure you checked out the dependencys and follow the 
next steps.

1. Download / Clone the Repository:
```javascript
    git clone git@gitlab.tubit.tu-berlin.de:markus.wende/RoMa_Synthesizer_One.git
```

2. (optional) if you downloaded as a .zip file, unzip the archiv

3. cd into the folder:
```javascript
    cd RoMa_Synthesizer_One*
```
