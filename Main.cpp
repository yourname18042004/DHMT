#include <Graphics/Display.h>
#include <Graphics/Graphics.h> 
#include "random"
#include "DocFile.h"

int main()
{
	DocFile display("",400, 400);

	display.InitObject();
	display.Loop();
	display.Delete();
}
