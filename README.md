# TurnOffTV
Arduino project that will turn off the TV after a certain amount of inactivity

Start with running one of the "recv" sketches, with an IR receiver connected to pin X.
Press the off button on your TV's remote and check what the sketch logs on serial.

Next:

Connect a PIR to pin Y
Connect an IR transmitter to pin X

Load the "IdleWatch" sketch, place the arduino where the PIR can see the sofa, and the IR transmitter can reach the TV.

Todo:
Add an indicator of some sorts, that warns you when you are sitting too still. At the moment you get no warning, the TV just suddenly turns off.

