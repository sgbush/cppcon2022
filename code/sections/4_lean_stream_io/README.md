# Lean stream IO example
Build this example using the `build.sh` script.  This will create three executables:
* Bare bones, no stream IO at all
* Conventional stream IO, links in a big, fat chunk of library code
* Minimal but functional custum stream IO code
The script assumes that you have an ARM cross compiler in /opt/arm/arm-none-eabi/bin.  You may have to make adjustments for your setup.