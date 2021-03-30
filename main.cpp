#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>
#include <string>

using namespace std;

namespace GenshinImpact {
	class Qin
	{
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
				play_main(e, 555);
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

			unsigned space = 555;
			string line;
			while(getline(ifs, line))
			{
				if("name" == line.substr(0, 4))
				{
					cout << "name:" << line.substr(5) << endl;
					continue;
				}

				if("t:" == line.substr(0, 2))
				{
					stringstream ss;
					ss << line.substr(2);
					ss >> space;
					cout << "每音符间隔:" << space << endl;
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
						play_main(static_cast<unsigned>(IsCharUpperA(e) ? e : (e - 'a' + 'A')), space);
				}

				play_wait(space);
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
			hGenshinWnd = ::FindWindowA("UnityWndClass", "原神");
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
			return play_main(static_cast<unsigned>(h), 555);
		}
		bool play(const MusicNoteM &m)
		{
			return play_main(static_cast<unsigned>(m), 555);
		}
		bool play(const MusicNoteL &l)
		{
			return play_main(static_cast<unsigned>(l), 555);
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