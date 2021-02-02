/* 
 *
 *
 * Project End Zoom & Teams Meetings Button
 * Description: Press the button to end your meeting
 * Author: javierinho
 * Date: January 2021
 * Inspired by https://github.com/alan707/zoom_button
 * License: GNU GPLv3 
 *
 * Tested on:
 * Windows 10
 * OSX 10.14.1
 */

#include <Keyboard.h>


// Uncomment your target OS & app
//const int target = 0; // OSX_Teams
//const int target = 1; // OSX_Zoom
//const int target = 2; // Windows_Teams
const int target = 3; // Windows_Zoom
 
// Digital PIN to use
int pin = 9; // D9 on my board

// Variables
int pinState = 0;
bool is_button_pressed = false;
bool keystroke_sent = false;

// Constants for searching
const char * osx_Teams = "Microsoft Teams";
const char * osx_Zoom = "zoom.us";
const char * windows_Teams = "Teams";
const char * windows_Zoom = "Zoom";


void windows_Search(const char * txt) {
  // Search for app in Windows 10 Start Menu's search, then open it to (re)gain focus

  Serial.println("Searching in Windows Search");
  delay(2000);

  // https://superuser.com/questions/1151706/what-is-the-new-windows-10-search-shortcut
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
  delay(2000);
  Keyboard.println(txt);
  delay(200);
  Keyboard.press(KEY_RETURN);
  delay(200);
  Keyboard.releaseAll();
  delay(2000);

  // The previous commands set focus on main Teams window. Now we change focus to current call window:
  // THIS DOES NOT WORK
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('`');
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
  delay(2000);
}

void end_Win_Zoom() {
  // Get app in focus

  // CURRENTLY NOT WORKING


  //windows_Search(windows_Zoom);
  
  // sending Alt + q shortcut
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('q');
  delay(100);
  Keyboard.releaseAll();
  
  // Confirm we want to exit
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll(); 
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.releaseAll();

  
}

void end_Win_Teams() {
  // Get app in focus
  
  // CURRENTLY NOT WORKING
  
  //windows_Search(windows_Teams);

  
  // Ctrl+Shift+B: Prompt to End or Leave Meeting
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('b');
  delay(100);
  Keyboard.releaseAll();
}

void osx_Search(const char * txt) {
  // Search for app in OSX's Spotlight search, then open it to (re)gain focus


  // CURRENTLY NOT WORKING
  
  Keyboard.press(KEY_BACKSPACE);
  delay(200);
  Keyboard.releaseAll();
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(' ');
  delay(200);
  Keyboard.releaseAll();
  Keyboard.println(txt);
  delay(200);
  Keyboard.press(KEY_RETURN);
  delay(200);
  Keyboard.releaseAll();
  delay(400);
}

void end_OSX_Zoom() {
  // Make sure Zoom app has focus
  osx_Search(osx_Zoom);
  
  // https://support.zoom.us/hc/en-us/articles/205683899-hot-keys-and-keyboard-for-zoom
  // press and release enter key to confirm we want to end meeting 
  Keyboard.print(KEY_RETURN);
}

void end_OSX_Teams() {
  // Make sure Teams app has focus
  osx_Search(osx_Teams);
  
  // There's currently no shotcut to end the call but you can tab-cycle to the hang-up button
  for (int tab=1; tab<10; tab++){
    Keyboard.press(KEY_TAB);
    delay(300);
    Keyboard.releaseAll();    
  }
  Keyboard.press(KEY_RETURN);
  delay(300);
  Keyboard.releaseAll();  
}

 

void setup(){
  // Start serial console
  Serial.begin(9600);
  
  // wait for serial
  while (!Serial) {}; 
  
  // start keyboard
  Keyboard.begin();
  
  // sets digital pin as input
  pinMode(pin,INPUT);
}

void loop() {
  pinState = digitalRead(pin); // 1 if HIGH, 0 if LOW
  
  if (pinState) {
    Serial.println("Read: HIGH");
    is_button_pressed = true;
  } else {
    Serial.println("Read: LOW");
    delay(500);
    is_button_pressed = false;
    keystroke_sent = false;
  }
  
  if (is_button_pressed && !keystroke_sent) {
    switch (target) { 
      case 0: // OSX_Teams
        end_OSX_Teams();
        break;
      case 1: // OSX_Zoom
        end_OSX_Zoom();
        break;
      case 2: // Win_Teams
        end_Win_Teams();
        break;
      case 3: // Win_Zoom
        end_Win_Zoom();
        break;
    }
    keystroke_sent = true;
  }
}
