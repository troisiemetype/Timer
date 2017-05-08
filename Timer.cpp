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

void Timer::init(){
	stop();
}

void Timer::setDelay(uint32_t delay){
	_delay = delay;
}

void Timer::setSeconds(uint16_t seconds){
	_delay = seconds * 1000;
}

void Timer::setMinutesSeconds(uint16_t minutes, uint8_t seconds){
	_delay = (minutes * 60 + seconds) * 1000;
}

void Timer::start(int16_t mode){
	_mode = mode;

	if(_mode > 0){
		_remainingLoops = _mode;
	}

	_now = millis();
	_last = _now;
	_end = _now + _delay;
	_pause = false;
	_running = true;
}

void Timer::pause(){
	_pause = !_pause;
}

void Timer::stop(){
	_now = 0;
	_last = 0;
	_end = 0;
	_remainingLoops = 0;
	_pause = false;
	_running = false;
}

bool Timer::update(){
	if(!_running) return false;

	_last = _now;
	_now = millis();

	if(!_pause){
		if(_now >= _end){
			if(_mode != 0){
				if(_mode > 0){
					if((--_remainingLoops) <= 0) stop();
				}
				_end = _now + _delay;
			} else {
				stop();				
			}

			return true;
		} else {
			return false;
		}
	} else {
		_end += (_now - _last);
	}
}
