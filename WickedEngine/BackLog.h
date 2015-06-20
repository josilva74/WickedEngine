#ifndef BACKLOG
#define BACKLOG
#include "WickedEngine.h"

static class BackLog
{
private:
	static deque<string> stream;
	static unsigned int deletefromline;
	static mutex logMutex;
	static const float speed;
	static float pos;
	static int scroll;
	static stringstream inputArea;
	enum State{
		IDLE,
		DISABLED,
		ACTIVATING,
		DEACTIVATING,
	};
	static State state;
	static int RENDERWIDTH, RENDERHEIGHT;
public:
	static void Initialize(int width, int height);
	static void CleanUp();
	static void Toggle();
	static void Scroll(int direction);
	static void Update();
	static void Draw();

	static string getText();
	static void clear();
	static void post(const char* input);
	static void input(const char& input);
	static void acceptInput();
	static void deletefromInput();
	static void save(ofstream& file);

	static deque<string> history;
	static int historyPos;
	static void historyPrev();
	static void historyNext();

	static bool isActive(){return state==IDLE;}
};

#endif