#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>
#include <string>

using namespace std;

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
	Qin(ifstream &ifs) :
		errorCode(0)
	{
		HWND hWnd = ::FindWindowA("UnityWndClass", "原神");
		if(!hWnd)
		{
			errorCode = 1;
			return;
		}
		::SetForegroundWindow(hWnd);

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
				cout <<"name:"<< line.substr(5) << endl;
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
					play(hWnd, static_cast<unsigned>(IsCharUpperA(e) ? e : (e - 'a' + 'A')));
				play(hWnd, 500, true);
			}

			play(hWnd, 500, true);
			cout << endl;
		}

		/*
		//MusicNote a(MusicNote::H::Do);
		play(hWnd, MusicNoteH::Do);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::Do);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::So);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::So);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::La);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::La);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::So);
		play(hWnd, 1000, true);

		play(hWnd, MusicNoteH::Fa);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::Fa);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::Mi);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::Mi);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::Re);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::Re);
		play(hWnd, 500, true);
		play(hWnd, MusicNoteH::Do);
		play(hWnd, 1000, true);
		*/

		return;

	}

	Qin(const Qin &) = delete;

	~Qin()
	{
		::SetForegroundWindow(::GetConsoleWindow());
		cout << "over" << endl;
	}

	operator int()
	{
		return errorCode;
	}

private:
	bool play(HWND hWnd, const MusicNoteH &h)
	{
		return play(hWnd, static_cast<unsigned>(h));
	}
	bool play(HWND hWnd, const MusicNoteM &m)
	{
		return play(hWnd, static_cast<unsigned>(m));
	}
	bool play(HWND hWnd, const MusicNoteL &l)
	{
		return play(hWnd, static_cast<unsigned>(l));
	}
	bool play(HWND hWnd, unsigned note)
	{
		cout << char(note);

		::PostMessageA(hWnd, WM_KEYDOWN, note, 0x100001);
		this_thread::sleep_for(chrono::milliseconds(30));
		::PostMessageA(hWnd, WM_KEYUP, note, 0xc0100001);

		return true;
	}
	bool play(HWND hWnd, unsigned delay, bool reserved)
	{
		cout << " ";
		this_thread::sleep_for(chrono::milliseconds(delay));
		return reserved;
	}
public:
	int errorCode;

};

int main(int argc, char **argv)
{
	if(argc <= 1)
	{
		cout << "缺少曲谱文件名" << endl;
		return -1;
	}

	ifstream ifs(argv[1]);
	return Qin(ifs);
}