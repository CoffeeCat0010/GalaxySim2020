#pragma once
#include "Corepch.h"
#include "Math/MVec.h"
#include "BaseClasses/Event.h"

namespace Application
{
	//Currently only windows is supported
	#ifdef _WIN32
	enum class KeyCode
	{
		NONE = 0,
		// Start Alphabet
		A_KEY = 0x41, B_KEY = 0x42, C_KEY = 0x43, D_KEY = 0x44,
		E_KEY = 0x45, F_KEY = 0x46, G_KEY = 0x47, H_KEY = 0x48,
		I_KEY = 0X49, J_KEY = 0x4a, K_KEY = 0x4b, L_KEY = 0x4c,
		M_KEY = 0x4d, N_KEY = 0x4e, O_KEY = 0x4f, P_KEY = 0x50,
		Q_KEY = 0x51, R_KEY = 0x52, S_KEY = 0x53, T_KEY = 0x54,
		U_KEY = 0x55, V_KEY = 0x56, W_KEY = 0x57, X_KEY = 0x58,
		Y_KEY = 0x59, Z_KEY = 0x5a,
		//Start Num Keys
		ZERO_KEY = 0x30, ONE_KEY = 0x31, TWO_KEY = 0x32, THREE_KEY = 0x33, 
		FOUR_KEY = 0x34, FIVE_KEY = 0x35, SIX_KEY = 0x36, SEVEN_KEY = 0x37, 
		EIGHT_KEY = 0x38, NINE_KEY = 0x39,
		//Start Numpad Keys
		NUMPAD0 = VK_NUMPAD0, NUMPAD1 = VK_NUMPAD1, NUMPAD2 = VK_NUMPAD2, NUMPAD3 = VK_NUMPAD3, 
		NUMPAD4 = VK_NUMPAD4, NUMPAD5 = VK_NUMPAD5, NUMPAD6 = VK_NUMPAD6, NUMPAD7 = VK_NUMPAD7,
		NUMPAD8 = VK_NUMPAD8, NUMPAD9 = VK_NUMPAD9, NUMPAD_LOCK = VK_NUMLOCK, NUMPAD_ADD = VK_ADD, 
		NUMPAD_SUB = VK_SUBTRACT, NUMPAD_MULT = VK_MULTIPLY, NUMPAD_DIV = VK_DIVIDE, 
		//Start Function Keys for now only F1 - F12 are supported
		F1_KEY = VK_F1, F2_KEY = VK_F2, F3_KEY = VK_F3, F4_KEY = VK_F4,
		F5_KEY = VK_F5, F6_KEY = VK_F6, F7_KEY = VK_F7, F8_KEY = VK_F8,
		F9_KEY = VK_F9, F10_KEY = VK_F10, F11_KEY = VK_F11, F4_KEY = VK_F12,
		//Start Misc Keys
		LSHFT_KEY = VK_LSHIFT, RSHFT_KEY = VK_RSHIFT, LCTRL_KEY = VK_LCONTROL, RCTRL_KEY = VK_RCONTROL,
		ESC_KEY = VK_ESCAPE, RETRN_KEY = VK_RETURN, 
		// Self defined shift codes
		SHFT_A = 0x141, SHFT_B = 0x142, SHFT_C = 0x143, SHFT_D = 0x144,
		SHFT_E = 0x145, SHFT_F = 0x146, SHFT_G = 0x147, SHFT_H = 0x148,
		SHFT_I = 0X149, SHFT_J = 0x14a, SHFT_K = 0x14b, SHFT_L = 0x14c,
		SHFT_M = 0x14d, SHFT_N = 0x14e, SHFT_O = 0x14f, SHFT_P = 0x150,
		SHFT_Q = 0x151, SHFT_R = 0x152, SHFT_S = 0x153, SHFT_T = 0x154,
		SHFT_U = 0x155, SHFT_V = 0x156, SHFT_W = 0x157, SHFT_X = 0x158,
		SHFT_Y = 0x159, SHFT_Z = 0x15a,
		SHFT_ZERO  = 0x130, SHFT_ONE  = 0x131, SHFT_TWO = 0x132, SHFT_THREE = 0x133, 
		SHFT_FOUR  = 0x134, SHFT_FIVE = 0x135, SHFT_SIX = 0x136, SHFT_SEVEN = 0x137,
		SHFT_EIGHT = 0x138, SHFT_NINE = 0x139,
	};
	#else
	#error "CURRENTLY ONLY WINDOWS KEY BINDINGS ARE SUPPORTED FOR KEY EVENTS"
	#endif
	//TODO: Figure out if this should only be defined in debug
	//TODO: LONG-TERM: consider other languages 
	static const std::unordered_map<KeyCode,char> kcToChar =
	{
		// Start Alphabet
		{A_KEY,  'a'}, {B_KEY,  'b'}, {C_KEY,  'c'}, {D_KEY,  'd'}, {E_KEY,  'e'}, {F_KEY,  'f'},
		{G_KEY,  'g'}, {H_KEY,  'h'}, {I_KEY,  'i'}, {J_KEY,  'j'}, {K_KEY,  'k'}, {L_KEY,  'l'},
		{M_KEY,  'm'}, {N_KEY,  'n'}, {O_KEY,  'o'}, {P_KEY,  'p'}, {Q_KEY,  'q'}, {R_KEY,  'r'},
		{S_KEY,  's'}, {T_KEY,  't'}, {U_KEY,  'u'}, {V_KEY,  'v'}, {W_KEY,  'w'}, {X_KEY,  'x'},
		{Y_KEY,  'y'}, {Z_KEY,  'z'},
		{SHFT_A, 'A'}, {SHFT_B, 'B'}, {SHFT_C, 'C'}, {SHFT_D, 'D'}, {SHFT_E, 'E'}, {SHFT_F, 'F'},
		{SHFT_G, 'G'}, {SHFT_H, 'H'}, {SHFT_I, 'I'}, {SHFT_J, 'J'}, {SHFT_K, 'K'}, {SHFT_L, 'L'},
		{SHFT_M, 'M'}, {SHFT_N, 'N'}, {SHFT_O, 'O'}, {SHFT_P, 'P'}, {SHFT_Q, 'Q'}, {SHFT_R, 'R'},
		{SHFT_S, 'S'}, {SHFT_T, 'T'}, {SHFT_U, 'U'}, {SHFT_V, 'V'}, {SHFT_W, 'W'}, {SHFT_X, 'X'},
		{SHFT_Y, 'Y'}, {SHFT_Z, 'Z'},
		// Start Numbers
		{ZERO_KEY, '0'}, {ONE_KEY, '1'}, {TWO_KEY, '2'}, {THREE_KEY, '3'}, {FOUR_KEY, '4'}, {FIVE_KEY, '5'},
		{SIX_KEY, '6'}, {SEVEN_KEY, '7'}, {EIGHT_KEY, '8'}, {NINE_KEY, '9'}, {NUMPAD0, '0'}, {NUMPAD1, '1'},
		{NUMPAD2, '2'}, {NUMPAD3, '3'}, {NUMPAD4, '4'}, {NUMPAD5, '5'}, {NUMPAD6, '6'}, {NUMPAD7, '7'}, 
		{NUMPAD8, '8'}, {NUMPAD9, '9'},
		
		// Start Misc

		{NUMPAD_MULT, '*'}, {NUMPAD_DIV, '/'}, {NUMPAD_SUB, '-'}, {NUMPAD_ADD, '+'}, 
		{SHFT_ZERO, ')'}, {SHFT_ONE, '!'}, {SHFT_TWO, '@'},   {SHFT_THREE, '#'}, {SHFT_FOUR, '$'}, 
		{SHFT_FIVE, '%'}, {SHFT_SIX, '^'}, {SHFT_SEVEN, '&'}, {SHFT_EIGHT, '*'}, {SHFT_NINE, '('}

	};
	#ifdef DEBUG


	static const std::unordered_map<KeyCode, std::string> kcToChar_DEBUG =
	{
		// Start Alphabet
		{A_KEY, "a"}, {B_KEY, "b"}, {C_KEY, "c"}, {D_KEY, "d"}, {E_KEY, "e"}, {F_KEY, "f"},
		{G_KEY, "g"}, {H_KEY, "h"}, {I_KEY, "i"}, {J_KEY, "j"}, {K_KEY, "k"}, {L_KEY, "l"},
		{M_KEY, "m"}, {N_KEY, "n"}, {O_KEY, "o"}, {P_KEY, "p"}, {Q_KEY, "q"}, {R_KEY, "r"},
		{S_KEY, "s"}, {T_KEY, "t"}, {U_KEY, "u"}, {V_KEY, "v"}, {W_KEY, "w"}, {X_KEY, "x"},
		{Y_KEY, "y"}, {Z_KEY, "z"},
		// Start Numbers
		{ZERO_KEY, "0"}, {ONE_KEY, "1"}, {TWO_KEY, "2"}, {THREE_KEY, "3"}, {FOUR_KEY, "4"}, 
		{FIVE_KEY, "5"}, {SIX_KEY, "6"}, {SEVEN_KEY, "7"}, {EIGHT_KEY, "8"}, {NINE_KEY, "9"}, 
		
		{NUMPAD0, "NUMPAD \"0\""}, {NUMPAD1, "NUMPAD \"1\""}, {NUMPAD2, "NUMPAD \"2\""}, {NUMPAD3, "NUMPAD \"3\""}, 
		{NUMPAD4, "NUMPAD \"4\""}, {NUMPAD5, "NUMPAD \"5\""}, {NUMPAD6, "NUMPAD \"6\""}, {NUMPAD7, "NUMPAD \"7\""},
		{NUMPAD8, "NUMPAD \"8\""}, {NUMPAD9, "NUMPAD \"9\""},

		// Start Misc
		{NUMPAD_MULT, "NUMPAD \"*\""}, {NUMPAD_DIV, "NUMPAD \"/\""}, {NUMPAD_SUB, "NUMPAD \"-\""}, {NUMPAD_ADD, "NUMPAD \"+\""},
		{LSHFT_KEY, "Left Shift"}, {RSHFT_KEY, "Right Shift"}, {LCTRL_KEY, "Left Control"}, {RCTRL_KEY, "Right Control"}
	};
	#endif // DEBUG

	class KeyEvent : public Event
	{
	protected:
		KeyCode m_code;
	protected:
		KeyEvent (EventType eventType, KeyCode KC)
			:Event (eventType, CatInputEvent | CatKeyEvent), m_code(KC)
		{}
	public:
		virtual EventType getEventType () const override;
		virtual std::string getName () const override;
		inline KeyCode getKeyCode () const { return m_code; }
	};
	class KeyPressedEvent : public KeyEvent
	{
	protected:
		bool m_isRepeat;
		/// <summary>
		/// Key modifing the event ie. "Control", "Shift", etc.
		/// </summary>
		KeyCode m_modifier;
	public:
		KeyPressedEvent (KeyCode KC, bool isRepeat, KeyCode modifier = KeyCode::NONE)
			:KeyEvent (EventType::KeyPressed, KC), m_isRepeat (isRepeat), m_modifier (modifier)
		{}
		inline EventType getEventType () const override { return m_eventType; }
		inline std::string getName () const override { return "KeyPressedEvent"; }
		#ifdef DEBUG
		inline std::string toString () const override
		{
			return (m_modifier != KeyCode::NONE ? kcToChar_DEBUG.at (m_modifier) + " + " : "") + 
				kcToChar_DEBUG.at (m_code) + " Pressed! Is a Repeat: " + (m_isRepeat ? "True" : "False");
		}
		#endif
		inline KeyCode getModifier () { return m_modifier; }
		inline bool isRepeat () { return m_isRepeat; }

	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent (KeyCode KC, bool isRepeat)
			:KeyEvent (EventType::KeyReleased, KC)
		{}
		inline EventType getEventType () const override { return m_eventType; }
		inline std::string getName () const override { return "KeyPressedEvent"; }
		#ifdef DEBUG
		inline std::string toString () const override
		{
			return kcToChar_DEBUG.at (m_code) + " Released!";
		}
		#endif
	};

}