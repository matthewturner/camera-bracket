[![PlatformIO CI](https://github.com/matthewturner/camera-bracket/actions/workflows/platformio.yml/badge.svg)](https://github.com/matthewturner/camera-bracket/actions/workflows/platformio.yml)

# Camera Bracket

Controls direction of a webcam.

## Installing Platform IO

Install command line tools by following the installation instructions for [Windows](https://docs.platformio.org/en/latest/core/installation.html#windows)

## Serial Monitor

Deploy code to your Arduino and run the following command in a terminal:

```powershell
 pio device monitor --eol=CRLF --echo --filter=send_on_enter
```

## Unit Testing

Run the following command after installing Platform IO:

```powershell
pio test -e native
```
