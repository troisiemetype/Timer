#Timer
This library provides a simple timer usable in an arduino sketch.
Simply copy the folder in your current library folder, then `#include "Timer.h"` in your `.ino` file.

After calling `init()` in your setup, there are three ways you can a set a timer duration:
`setDelay(delay)` will set a delay in microseconds (max is 2³²).
`setSeconds(seconds)` will set a delay in seconds (max is 2¹⁶).
`setMinutesSeconds(minutes, secondes)` will set a delay in minutes and seconds (max is 2¹⁶ for minutes, 2⁸ for seconds).

Once the delay set, you can use the timer like this:
`start()` will simply launch the timer.
Additionnaly, you can use `start(Timer::LOOP)` to create an infinite loop, where the timer automaticly start again when delay is elapsed.
Finally, you can also use `start(x)`, where is the number of loop you whant the timer to proceed before to stop.

`pause()` will pause the timer until `pause()` is called again.
`stop()` will stop the timer before it has reach its end.

Last but no least, call `update()` as often as you can (i.e. from the main loop). It will return `true` when delay is elapsed, `false` otherwise. You can call it even if the timer is stopped or paused. In taht case it will also return `false`.

This library is based on the `millis()` function provided by Arduino.