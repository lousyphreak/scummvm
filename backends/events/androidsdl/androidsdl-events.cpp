/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/scummsys.h"

#if defined(ANDROIDSDL)

#include "backends/events/androidsdl/androidsdl-events.h"
#include "backends/platform/androidsdl/androidsdl-sdl.h"
#include <SDL_screenkeyboard.h>

bool AndroidSdlEventSource::handleMouseButtonDown(SDL_Event &ev, Common::Event &event) {
	if (ev.button.button == SDL_BUTTON_LEFT)
		event.type = Common::EVENT_LBUTTONDOWN;
	else if (ev.button.button == SDL_BUTTON_RIGHT)
		event.type = Common::EVENT_RBUTTONDOWN;
#if defined(SDL_BUTTON_WHEELUP) && defined(SDL_BUTTON_WHEELDOWN)
	else if (ev.button.button == SDL_BUTTON_WHEELUP)
		event.type = Common::EVENT_WHEELUP;
	else if (ev.button.button == SDL_BUTTON_WHEELDOWN)
		event.type = Common::EVENT_WHEELDOWN;
#endif
#if defined(SDL_BUTTON_MIDDLE)
	else if (ev.button.button == SDL_BUTTON_MIDDLE) {
		event.type = Common::EVENT_MBUTTONDOWN;

		static int show_onscreen = 0;
		if (show_onscreen == 0) {
			SDL_ANDROID_SetScreenKeyboardShown(0);
			show_onscreen++;
		} else if (show_onscreen==1) {
			SDL_ANDROID_SetScreenKeyboardShown(1);
			show_onscreen++;
		}
		if (show_onscreen == 2)
			show_onscreen = 0;
	}
#endif
	else
		return false;

	processMouseEvent(event, ev.button.x, ev.button.y);

	return true;
}

bool AndroidSdlEventSource::remapKey(SDL_Event &ev, Common::Event &event) {
	if (false) {}

	if (ev.key.keysym.sym == SDLK_LCTRL) {
		event.type = Common::EVENT_KEYDOWN;
		event.kbd.keycode = Common::KEYCODE_F5;
		return true;
	} else {
		// Let the events fall through if we didn't change them, this may not be the best way to
		// set it up, but i'm not sure how sdl would like it if we let if fall through then redid it though.
		// and yes i have an huge terminal size so i dont wrap soon enough.
		event.type = Common::EVENT_KEYDOWN;
		event.kbd.keycode = (Common::KeyCode)ev.key.keysym.sym;
		event.kbd.ascii = mapKey(ev.key.keysym.sym, ev.key.keysym.mod, ev.key.keysym.unicode);
	}

	return false;
}

#endif
