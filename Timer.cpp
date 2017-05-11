/*
 * This Arduino library is for providing a timer
 * Copyright (C) 2016  Pierre-Loup Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Timer.h"

//Init the timer
void Timer::init(){
	stop();
}

//Set a delay in microseconds
void Timer::setDelay(uint32_t delay){
	_delay = delay;
}

//Set a delay in seconds
void Timer::setSeconds(uint16_t seconds){
	_delay = seconds * 1000;
}

//Set a delay in minutes and seconds. Seconds can be omitted.
void Timer::setMinutesSeconds(uint16_t minutes, uint8_t seconds){
	_delay = (minutes * 60L + seconds) * 1000L;
}

//Start the timer with given mode:
//-1 / Timer::LOOP laucnh an infinite loop
// 0 / Timer::ONCE launch one count
// Any value above 0: launch for that number of loops
void Timer::start(int16_t mode){
	_mode = mode;

	if(_mode > 0){
		_remainingLoops = _mode;
	}

	_now = millis();
	_last = _now;
	_start = _now;
	_end = _now + _delay;
	_pause = false;
	_running = true;
}

//Pause the timer
void Timer::pause(){
	_pause = !_pause;
}

//Stop the timer
void Timer::stop(){
	_start = 0;
	_now = 0;
	_last = 0;
	_end = 0;
	_remainingLoops = 0;
	_pause = false;
	_running = false;
}

//Update the timer. To be called as soon as possible, i.e. in your main loop.
//Return true if the count as ended, false other wise
bool Timer::update(){
	//If start has not been called yet, return false
	if(!_running) return false;

	_last = _now;
	_now = millis();

	//Test if pause is on or off.
	if(!_pause){
		//If pause is off, look if the delay has elapsed
		if(_now >= _end){
			//If yes, see if a loop has to be launched again, or not
			if(_mode != 0){
				if(_mode > 0){
					if((--_remainingLoops) <= 0) stop();
				}
				//Reinit delay for the new loop
				_end = _now + _delay;
			} else {
				//Stop the timer if there was no loop
				stop();				
			}
			return true;
		} else {
			return false;
		}
	} else {
		//If pause is on, end and start values are incremented by the time elapsed since last update
		_end += (_now - _last);
		_start += (_now - _last);
		return false;
	}
}

//Get milliseconds elapsed since timer start
uint32_t Timer::getCurrent(){
	return (_now - _start);
}

//Get total number of seconds elapsed since timer start
uint16_t Timer::getSeconds(){
	return ((_now - _start) / 1000);
}

//Get number of seconds elapsed since timer start, modulo 60
uint16_t Timer::getSecondsM(){
	return (((_now - _start) / 1000) % 60);
}

//Get number of minutes elapsed since timer start
uint16_t Timer::getMinutes(){
	return ((_now - _start) / 60000);

}

//Get milliseconds elapsed till timer stop
uint32_t Timer::getRCurrent(){
	return (_end - _now);
}

//Get total number of seconds elapsed till timer stop
uint16_t Timer::getRSeconds(){
	return (((_end - _now) / 1000));

}

//Get number of seconds elapsed till timer stop, modulo 60
uint16_t Timer::getRSecondsM(){
	return (((_end - _now) / 1000) % 60);
}

//Get number of minutes elapsed since timer stop
uint16_t Timer::getRMinutes(){
	return ((_end - _now) / 60000);

}
