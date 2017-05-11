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


#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

#include <stdint.h>

class Timer{
public:

	enum mode_t{
		LOOP = -1,
		ONCE,
	};

	void init();
	void setDelay(uint32_t delay);
	void setSeconds(uint16_t seconds);
	void setMinutesSeconds(uint16_t minutes, uint8_t seconds = 0);
	void start(int16_t mode = ONCE);
	void pause();
	void stop();

	bool update();

	uint32_t getCurrent();
	uint16_t getSeconds();
	uint16_t getSecondsM();
	uint16_t getMinutes();

	uint32_t getRCurrent();
	uint16_t getRSeconds();
	uint16_t getRSecondsM();
	uint16_t getRMinutes();

protected:

	uint32_t _start, _now, _last, _end, _delay;
	uint16_t _remainingLoops;

	int8_t _mode;

	bool _pause, _running;
};

#endif