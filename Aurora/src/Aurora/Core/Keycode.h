#pragma once
#include <cstdint>

namespace Aurora
{
	using KeyCode = uint16_t;

	namespace Key
	{
		enum : KeyCode
		{
			Backspace = 8,
			Tab = 9,
			Enter = 13,
			Shift = 16,
			Control = 17,
			Alt = 18,
			CapsLock = 20,
			Escape = 27,
			Space = 32,
			PageUp = 33,
			PageDn = 34,
			End = 35,
			Home = 36,
			Delete = 46,
			//Apostrophe = 39, /* ' */
			//Comma = 44, /* , */
			//Minus = 45, /* - */
			//Period = 46, /* . */
			//Slash = 47, /* / */

			//D0 = 48, /* 0 */
			//D1 = 49, /* 1 */
			//D2 = 50, /* 2 */
			//D3 = 51, /* 3 */
			//D4 = 52, /* 4 */
			//D5 = 53, /* 5 */
			//D6 = 54, /* 6 */
			//D7 = 55, /* 7 */
			//D8 = 56, /* 8 */
			//D9 = 57, /* 9 */

			//Semicolon = 59, /* ; */
			//Equal = 61, /* = */

			LeftArrow = 37,
			UpArrow = 38,
			RightArrow = 39,
			DownArrow = 40,

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
			
			Num0 = 96,
			//LeftBracket = 91,  /* [ */
			//Backslash = 92,  /* \ */
			//RightBracket = 93,  /* ] */
			//GraveAccent = 96,  /* ` */

			//World1 = 161, /* non-US #1 */
			//World2 = 162, /* non-US #2 */

			///* Function keys */
			
			//Insert = 260,
			//PrintScreen = 283,
			//Pause = 284,
			F1 = 112,
			F2 = 113,
			F3 = 114,
			F4 = 115,
			F5 = 116,
			F6 = 117,
			F7 = 118,
			F8 = 118,
			F9 = 120,
			F10 = 121,
			F11 = 122,
			F12 = 123,
			F13 = 124,
			F14 = 125,
			F15 = 126,
			F16 = 127,
			F17 = 128,
			F18 = 129,
			F19 = 130,
			F20 = 131,
			F21 = 132,
			F22 = 133,
			F23 = 134,
			F24 = 135,

			NumLock = 144,
			ScrollLock = 145,

			///* Keypad */
			//KP0 = 320,
			//KP1 = 321,
			//KP2 = 322,
			//KP3 = 323,
			//KP4 = 324,
			//KP5 = 325,
			//KP6 = 326,
			//KP7 = 327,
			//KP8 = 328,
			//KP9 = 329,
			//KPDecimal = 330,
			//KPDivide = 331,
			//KPMultiply = 332,
			//KPSubtract = 333,
			//KPAdd = 334,
			//KPEnter = 335,
			//KPEqual = 336,

			LeftShift = 160,
			RightShift = 161,
			LeftControl = 162,
			RightControl = 163,
			
		};
	}
}