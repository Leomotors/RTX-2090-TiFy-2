# RTX 2090 TiFy V2

Version 2 (Rewrite, because for old projects, Refactor is not different from Rewrite)
of the ~~popular~~ meme generator [RTX 2090 TiFy](https://github.com/Leomotors/RTX-2090-TiFy)

_work in progress_

## Project Structure

- RTX-2090-Ti -> Core Structure of App
- RTXTest -> Test for RTX-2090-Ti (Core Lib) with Google Test
  <br/><br/>
- WinUI -> UI for Windows with winrt + WinUI2 (because 3 does not have Mica)
- wxWidgets -> UI for Linux with wxWidgets (GTK3)

## Developing - Windows

- opencv_world455.dll and opencv_world455d.dll should exists at /WinUI
