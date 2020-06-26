[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![stable](http://badges.github.io/stability-badges/dist/stable.svg)](http://github.com/badges/stability-badges)

# Hardware-Monitor-Applet
Hardware Monitor Applet is an applet that usses the LCD from some Logitech gaming keyboards (eg. G15, G19, G910). This applet uses the information comming from Open Hardware Monitor or HWiNFO and displays it on the LCD. The Applet can only be used on a Windows operating system.

## System requirements
### Windows
- Operating system: Vista (SP2), 7 (SP1), 8 (8.1), 10
- Version 2.0 does only support x64
- Logitech keyboard: G13, G15, G510, G19, G910
- [Logitech Gaming Software (8.52 or higher)](https://support.logitech.com/nl_be/Product/gaming-software)
- [Visual C++ Redistributable for Visual Studio 2013](http://www.microsoft.com/en-us/download/details.aspx?id=40784)
- [HWiNFO32/64](http://www.hwinfo.com/) OR [Open Hardware Monitor](http://openhardwaremonitor.org/)

## Linux
- Logitech keyboard: G19
- Required software: [G19Daemon](https://github.com/mortendynamite/g19daemon)
- [InfluxDb](https://www.influxdata.com/)

## Manual
Manual can be read on the [Manual page](manual.md).

## Changelog
### HMA Version 2.0 (TBA)
- Add Linux support
- Add InfluxDB support
- Some GUI changes

### HMA Version 1.0 (04-04-2015)
- Renamed application from 'Open Hardware Monitor Applet' to 'Hardware Monitor Applet'.
- Renewed full source code
- Added support for HWiNFO and Open Hardware Monitor
- Customization capabilities
- Added Graph screen for G19 users.
- Multi Language support

### Deprecated

#### OHM Version 0.2.5 (14-09-2013)
- Update to VS2013
- Added GPU Load (for NVidia cards) and added GPU Memory Load
- Fixed HD crash bug
- Added log file when somethings goes wrong


#### OHMA Version 0.2.4 (25-12-2012) 
- Set applet as foreground.
- Update to VS2012.

#### OHMA Version 0.2.3 (19-08-2012) 
- Fixed error when only 1 core was seen with some cpu's (eg. AMD athlon X4) that had only 1 temp sensor.

#### Version 0.2.2 (11-08-2012) 
- Fixed issue where the applet didn't connect to WMI-database.
- Adjust HDD tab text.

#### OHMA Version 0.2.1 (09-08-2012) 
- Adjust CPU tab layout

#### OHMA Version 0.2.0.0.1 (08-08-2012) by Andy 
- Adjusted Logitech G19 screen size errors
- Optimized code & resources for less memory usage
- Added cpu clock speed reading & displaying
- Adjust memory tab layout
- Adjust hdd tab layout
- Adjust GPU tab layout

#### OHMA Version 0.2.0 (07-08-2012) 
- Add support for Logitech G19 keyboards.

#### Version 0.1.4 (06-08-2012) 
- Fixed a lot of bugs for the G19.

#### OHMA Version 0.1.3 (06-08-2012) 
- Fixed the scroll bug on G15 keyboards.
#### Version 0.1.2 (05-08-2012) 
- Added new page with memory load and date and time.
#### OHMA Version 0.1.1 (05-08-2012) 
- Auto start bug is fixed.

#### OHMA Version 0.1.0 (04-08-2012) 

I'm happy to announce you the first release of the applet for Open Hardware Monitor. This release is only tested on Logitech G15. Logitech G19 support will be added later.

## Screenshots
[Graph screen](https://github.com/lonelobo0070/Hardware-Monitor-Applet/blob/master/Resources/Screenshots/Graph%20screen.png)  
[Stast screen](https://github.com/lonelobo0070/Hardware-Monitor-Applet/blob/master/Resources/Screenshots/NormalScreen.png)  
[Settings](https://github.com/lonelobo0070/Hardware-Monitor-Applet/blob/master/Resources/Screenshots/settings.png)  
