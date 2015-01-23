# obnoxious-sound-meter
Blinks incessantly at you when your music is too loud. Arduino + LEDs + Electret Mic Amp.

This is a project for the Arduino Uno with:

1) An Electret Microphone Amplifier (Here, a MAX9814 Electret Microphone Amplifier (found at https://www.adafruit.com/products/1713)
-- REQUIRES SOLDERING

2) Four LEDs

3) A DC Buzzer (SPKBZ-221005) (Or multitonal Piezo buzzer)

You will also require a breadboard.

This is designed to blink incessantly when you have your music up too loudly in the house or in your car. It will also gently remind you how loud your music is with glowing LEDs as your music passes the attached arbitrary "obnoxious levels". It's for all of you that love to listen to your music but don't want to disrupt those around you. 

The wiring setup looks like this:
https://cloud.githubusercontent.com/assets/9125578/5884268/5d6897d6-a329-11e4-9b0d-ac69f871f46f.png
Please note that this diagram shows a 3-output mic amp, while ours has 5 outputs (Fritzing, the handy program used to make this diagram, didn't have the illustration available).  

To connect your amp correctly, the purple wire in the diagram goes from OUT on the amp to the A0 analog pin on the Arduino.
The white wire goes from GND on the amp to GND on the Arduino.
The yellow wire goes from Vdd on the amp to the 3.3V pin on the Arduino.
-- Not shown: another wire must go from the GAIN on the amp to the same line as the Vdd wire on the breadboard to match the volt levels in the Arduino code.
-- The leftover output on the amp can be left clear.

If you do not connect the GAIN, the code will still work but you will need to adjust the sound levels in the if statement accordingly.

Here is a handy chart to show you how obnoxious you're being with your music:
https://cloud.githubusercontent.com/assets/9125578/5884275/755bbc88-a329-11e4-8f1a-1b32f0daf6e7.png

Have fun!
