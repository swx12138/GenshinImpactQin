#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>
#include <string>

using namespace std;

namespace GenshinImpact {
	class Qin
	{
		constexpr static const int pai = 555;
		enum class MusicNoteH :unsigned
		{
			Do = 'Q',
			Re = 'W',
			Mi = 'E',
			Fa = 'R',
			So = 'T',
			La = 'Y',
			Si = 'U'
		};
		enum class MusicNoteM :unsigned
		{
			Do = 'A',
			Re = 'S',
			Mi = 'D',
			Fa = 'F',
			So = 'G',
			La = 'H',
			Si = 'J'
		};
		enum class MusicNoteL :unsigned
		{
			Do = 'Z',
			Re = 'X',
			Mi = 'C',
			Fa = 'V',
			So = 'B',
			La = 'N',
			Si = 'M'
		};
	public:
		Qin()
		{
			if(!getGenshinWnd())
				return;

			string xxx = "QQTTYYT RREEWWQ TTRREEW TTRREEW QQTTYYT RREEWWQ";
			for(auto e : xxx)
			{
				play_main(e, 200);
			}
		}

		Qin(ifstream &ifs)
		{
			if(!getGenshinWnd())
				return;

			if(!ifs)
			{
				errorCode = 2;
				return;
			}

			string line;
			while(getline(ifs, line))
			{
				if("name" == line.substr(0, 4))
				{
					cout << "name:" << line.substr(5) << endl;
					continue;
				}

				if("from" == line.substr(0, 4))
				{
					cout << "from:" << line.substr(5) << endl;
					continue;
				}

				for(auto e : line)
				{
					if((e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z'))
						play_main(static_cast<unsigned>(IsCharUpperA(e) ? e : (e - 'a' + 'A')), pai);
				}

				play_wait(pai);
				cout << endl;
			}

			return;

		}

		Qin(const Qin &) = delete;

		~Qin()
		{
			::SetForegroundWindow(::GetConsoleWindow());
			cout << "\nover" << endl;
		}

		operator int()
		{
			return errorCode;
		}

	private:
		bool getGenshinWnd()
		{
			hGenshinWnd = ::FindWindowA("UnityWndClass", "Ô­Éñ");
			if(!hGenshinWnd)
			{
				errorCode = 1;
				return false;
			}

			if(!::SetForegroundWindow(hGenshinWnd))
			{
				errorCode = GetLastError();
				return false;
			}

			return true;
		}

		bool play(const MusicNoteH &h)
		{
			return play_main(static_cast<unsigned>(h), pai);
		}
		bool play(const MusicNoteM &m)
		{
			return play_main(static_cast<unsigned>(m), pai);
		}
		bool play(const MusicNoteL &l)
		{
			return play_main(static_cast<unsigned>(l), pai);
		}

		bool play_main(unsigned note, unsigned delay)
		{
			cout << char(note);

			::PostMessageA(hGenshinWnd, WM_KEYDOWN, note, 0x100001);
			this_thread::sleep_for(chrono::milliseconds(30));
			::PostMessageA(hGenshinWnd, WM_KEYUP, note, 0xc0100001);
			this_thread::sleep_for(chrono::milliseconds(delay));


			return true;
		}

		void play_wait(unsigned delay)
		{
			cout << " ";
			this_thread::sleep_for(chrono::milliseconds(delay));
		}
	public:
		int errorCode = 0;
		HWND hGenshinWnd;
	};
}

int main(int argc, char **argv)
{
	if(argc <= 1)
	{
		return GenshinImpact::Qin();
	}

	ifstream ifs(argv[1]);
	return GenshinImpact::Qin(ifs);
}