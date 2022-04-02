# WinUI

The UI Implementation of RTX 2090 TiFy using WinUI 2 with UWP C++/WinRT

*For Windows Only, it is already mentioned in its name*

WinUI is a UI library for creating Windows-Looking app on Windows. (Note: WinUI is also supported on React Native. These are only two ways you can make native windows11-looking app.)

I prefer WinUi 2 over 3 because 3 is very new and does not support Mica. Moreover, the Xaml Controls Gallery still using WinUI 2. But when WinUI 3 get upgraded, I will definitely switch.

## The folder structure looks ugly?

Yes it is, I have tried moving CPP files into folders, and guess what?

*Compilation Error*

But Visual Studio has filter, so, if you open this project in Visual Studio.
The folder structures may look a bit more friendly.

## Tips & Trick

To be able to write a beautiful Windows App like this, you need... endurance,
to read documentations, go through hundreds of YouTube Video, thousands of Stack Overflow.

```
========================================================================
    C++/WinRT RTX-2090-TiFy Project Overview
========================================================================

This project demonstrates how to get started writing XAML apps directly
with standard C++, using the C++/WinRT SDK component and XAML compiler 
support to generate implementation headers from interface (IDL) files.
These headers can then be used to implement the local Windows Runtime 
classes referenced in the app's XAML pages.

Steps:
1. Create an interface (IDL) file to define any local Windows Runtime 
    classes referenced in the app's XAML pages.
2. Build the project once to generate implementation templates under 
    the "Generated Files" folder, as well as skeleton class definitions 
    under "Generated Files\sources".  
3. Use the skeleton class definitions for reference to implement your
    Windows Runtime classes.

========================================================================
Learn more about C++/WinRT here:
http://aka.ms/cppwinrt/
========================================================================
```
