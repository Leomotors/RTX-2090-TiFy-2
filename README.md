# RTX 2090 TiFy V2

Version 2 (Rewrite, because for old projects, Refactor is not different from Rewrite)
of the ~~popular~~ meme generator [RTX 2090 TiFy](https://github.com/Leomotors/RTX-2090-TiFy)

_work in progress_

## Project Structure

- RTX-2090-Ti -> Core Structure of App, contains classes and functions
  that is shared between Windows and Linux Version
- RTXTest -> Unit Test App with MSTest for shared files (RTX-2090-Ti)
  <br/><br/>
- WinUI -> UI for Windows with winrt + WinUI2 (because 3 does not have Mica)
- \<Undecided library\> -> UI for Linux

## Developing - Windows

- Run preprocess.js with node

- Set OpenCV_DIR to OpenCV's Directory

- Copy opencv_world455.dll and opencv_world455d.dll to ./WinUI
