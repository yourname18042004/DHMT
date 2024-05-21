#ifndef DISPLAY_H
#define DISPLAY_H

#include <Graphics/Graphics.h>

#include <iostream>

class Display
{
protected:
	int WIDTH;
	int HEIGHT;

	GLFWwindow* window;

	int crntTime;
	int timeDiff;
	int prevTime;
	int counter;

public:

	Display();
	Display(int width, int height);
	~Display();

	void Init();
	void Loop();
	virtual void Draw();
	void Delete();
};

#endif // !DISPLAY_H


