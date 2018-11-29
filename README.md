# TGH GUI

This is an alpha version of my GUI Library for ESP8266 and ESP32. This library allows you to write some simple code in the Arduino language, which describes the layout of some GUI, the GUI elements used, their callbacks and more.

Then, the ESP will automatically host a webpage where it provides the given GUI.

The examples provided have been tested and they work for both ESP8266 and ESP32, but the library is still heavily experimental and should not yet be used for production.

Everything is buttersmooth, since the communication itself uses websockets. This allows you to update the values displayed tens, if not hundreds of times per second.

Numerous GUI elements are supported.

## Supported GUI elements

![image of some nice GUI elements](https://i.imgur.com/ZF3XQDp.png)

- Text

Any text can be placed on the page and then can be updated dynamically from the ESP. Rich HTML can be optionally used to style this text.
  
- Label

  An output intended for displaying some value, e.g. a reading of a temperature sensor or similar.
  
- Checkboxes

  Checkboxes have a callback that sends the current status (checked/unchecked) back to the ESP.

- Sliders

  Sliders have 2 callbacks: one when the user releases them and one while the user is scrolling; this means that you can, for instance, dynamically control the brightness of some LED by moving the slider.
  
- Text boxes

  There are 2 different types of text inputs: TextInput and TextArea, the latter being a multi-line input. Those have no callbacks as of today, but it's possible for the ESP to poll the current text.
  
- List boxes

  An element with an optional callback firing on the change of the selected list item; optionally, it's also possible for the ESP to actively poll the value
  
- Buttons

An element which can fire a callback when clicked.
  
## Layout control

In addition to the aforementioned GUI elements, various containers have been implemented to allow the user to control the layout of the GUI elements. Those are:

- hBox

A container, which organises the components inside it horizontally; if the screen resolution of the device used to view the GUI doesn't allow this, the content wraps (and the layout switches to vertical automatically).

- hBox

A container, which organises the components inside it vertically.

- tabbedPane, tab

The content can be organized into tabs, grouped by context. 

![image of tabs](https://i.imgur.com/OVA1Pbr.png)

## Synchronization

It's possible to access the properties of the individual GUI elements on per-client basis. That is, it's possible to change the text
that one client connected to the ESP sees, while showing a different text to the other clients; similarly, it's possible to make (some, this is a WIP) objects synchronized. This means that, for instance, if one user checks a checkbox, all users will have it checked as well automatically. So far, the synchronization works for checkboxes and sliders; thinking about implementing it for tab switching, but this has a low priority.

## Dependencies

Right now, the following libraries need to be installed for this library to work:

- ArduinoJson
https://arduinojson.org

- WebSockets library

https://github.com/Links2004/arduinoWebSockets

But soon I will be porting the library to ESP32, which is when I will include more dependencies due to the AsyncWebServer library.

## Usage

Copying the content of data to the spiffs of your ESP and copying the files of this library to the libraries should be enough, but this library has not yet been tested as a library (but with a bit of fiddling around, it should work...)


