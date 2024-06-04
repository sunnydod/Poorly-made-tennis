# Poorly-made-tennis
A really barebones version of tennis against yourself
Game Rules

To start press the right button
Wait until the light reaches the last Neopixel and press the corresponding sides button
If you succeed the light will bounce back to the other side, and you should repeat this until level 5
At level 5 if you can bounce it back and forth 5 more times you will get the win screen

Nuances
	
If you press the button too soon, you will take damage.  If you take 3 damage you will lose.
If the light reaches the other side you will lose.

Inputs and outputs

(Inputs)
Right button
Left button
RightbuttonISR
LeftbuttonISR

CircuitPlayground.playTone(500,3000) [lose sound]
All Neopixels red [lose screen]
CircuitPlayground.playTone(5000,3000) [win sound]
All Neopixesl green [win screen]



Press the right button to start the game.  There will be a red light that bounces back and forth between the two sides of the CPX board using the Neopixels.  You need to press the corresponding sides button before it reaches the last Neopixel or you will lose the game. There are 5 levels, and to advance to the next level you need to bounce the ball 5 times in the current level.  If you complete all 5 levels you will reach the win screen!
