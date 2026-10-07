# BuildingForPCEcosystem-Uni

## 1. Introduction

In this task I was tasked with making a scalable foundation for a PC game using either unreal or unity (I used Unreal). This includes implementing:

* Dynamic Resolution and Aspect Ratio UI - Have a main menu that correctly scales amongst different PC aspect ratios

* Graphic Scalability Settings - Implement a basic graphics settings to handle hardware fragmentation

* Action-Based Input System - Implement a character or camera controller that utilizes the engines modern input system 

This task is important as these parts being set up correctly is a very important factor in ensuring your game has similar experience on any different platform it may be played on.

## 2. Implementation

First thing I did in this project was the graphics settings, and to do that I drummed up a quick settings menu widget with a backdrop and option selector being a text box with a button on the left and right for switching the options in those directions respectively.

![](https://file.garden/aSY-yx_ZmANpQe1l/Year2Tasks/EGraphicValues.png)
Graphic Values Enum

To make things simpler in logic I made a enum to represent 5 different graphic settings respectively.

![](https://file.garden/aSY-yx_ZmANpQe1l/Year2Tasks/ButtonSwaping.png)
Logic for left and right button

Then I made a system to swap between the items in the enum as the left and right button were pressed.

![](https://file.garden/aSY-yx_ZmANpQe1l/Year2Tasks/GraphicSetting.png)
Logic for actually applying graphics settings

Then after the enum is set correctly a sequence of three things plays out. First, it checks the enum to see if its on the lowest or greatest option and if it is it will hide either the left or right button to signal to the user that they are on the lowest/highest setting and prevent them from going any lower or higher at that moment. Next, the actual in game settings are modified. This is done by getting the game settings object in unreal and run the "SetOverallScalabilityLevel" function on the object using the graphics value enum as int as the input for the value for the function and then apply the new settings by running that function on the object. Finally for visual feedback the text box on the widget is set to whatever graphic setting the setting is currently on.

Next thing I did for the project was the logic for managing different input types. Luckily in unreal though the enhanced input actions system setting up input for different hardware is as easy as telling unreal to track say the E key for a keyboard and then Face button down for a controller. This way unreal will just be tracking for the input of either of these two types without any extra logic needed to facilitate using a keyboard and then a controller and vice versa. 

![Logic for  grabbing input button as text](https://file.garden/aSY-yx_ZmANpQe1l/Year2Tasks/InputButtonKeyGrabber.png)
Logic for  grabbing input button as text

Along with this I have also made a function to get the name of of the input for any action. For example I can get whatever key is used to jump as a text element with this function dynamically changing the output based on what input device is being used

Finally I did the "Dynamic Resolution and Aspect Ratio UI" part of this project which includes the ability to change screen resolution and with this making sure the UI element resize dynamically to the screen size. This ensuring that the UI can be read on any screen size.

![Logic for populating resolution box](https://file.garden/aSY-yx_ZmANpQe1l/Year2Tasks/GenerateResolution.png)
Logic for populating resolution box

To make the selector for different resolutions is a created a combo box in my UI, which can be used to make a drop down of options, and populated it using a function which can grab all screen resolutions for display the user is using and then formatting it correctly to ensure it can be used easily when being set later on.

![Different Widget Anchors](https://file.garden/aSY-yx_ZmANpQe1l/Year2Tasks/WidgetAnchor01.png)

![](https://file.garden/aSY-yx_ZmANpQe1l/Year2Tasks/WidgetAnchor02.png)

Different Widget Anchors

Next to ensure that the UI dynamically sizes to the size of the screen I used widget anchors. One type I used was centering the anchor on the UI element which would ensure the UI would keep the same relative spacing regardless of resolution changes. The other is fixing the anchor to the corners of the widget which separate to the other type will not keep its general position as well but will keep the same relative scale of the element compared to the size of the screen.

## 3. Outcome 


The final result has the player in a default scene being able to interact and move with a item using both a keyboard and controller respectively. Along with this I have a options screen accessed by pressing the E button where the graphics can be changed and can also change the resolution of the screen to any size the chosen monitor allows. The UI also dynamically sizes based on said resolution 

I can confirm that all the task requirements as I have implemented:

* Dynamic Resolution and Aspect Ratio UI - There is a options box to switch resolution and the UI scales realistically as the screen size changes

* Graphic Scalability Settings - I have implemented the basic ability to switch between the overall scalability settings

* Action-Based Input System - The game can allow for both controller and keyboard play with inbuilt functions to allow for text elements to be created

## 4. Bibliography
Unreal Engine 5.7 Documentation | Unreal Engine 5.7 Documentation | Epic Developer Community (s.d.) At: https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-5-7-documentation (Accessed 03/12/2025).

