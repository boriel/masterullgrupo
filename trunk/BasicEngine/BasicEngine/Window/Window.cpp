#include "Window.h"

#include "ApplicationProperties.h"


//Create the window with the parameters it receives
bool cWindow::Init (cApplicationProperties &lProperties)
{

	//variable Initialization
	mDC = NULL;
	mWnd = NULL;
	mInstance = GetModuleHandle(NULL);
	mProperties = lProperties;
	/*

	//Window Initialization or Register the window
	WNDCLASS lWndClass; // Windows Class Structure
	lWndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Size, And Own DC For Window.
	lWndClass.lpfnWndProc = (WNDPROC) WndProc; // WndProc Handles Messages
	lWndClass.cbClsExtra = 0; // No Extra Window Data
	lWndClass.cbWndExtra = 0; // No Extra Window Data
	lWndClass.hInstance = mInstance; // Set The Instance
	lWndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Load The Default Icon
	lWndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Load The Arrow Pointer
	lWndClass.hbrBackground = NULL; // No Background Required For GL
	lWndClass.lpszMenuName = NULL; // We Don't Want A Menu
	lWndClass.lpszClassName = lProperties.macApplicationName.c_str(); // Set The Class Name
	
	int liRet = RegisterClass(&lWndClass);
	if (!liRet) // Attempt To Register The Window Class
	{
		DWORD lError = GetLastError();
		MessageBox(NULL,"Failed to Register the window", "ERROR", MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	*/

	return true;
}


//This function will update the window and respond to possible events come of it.
void cWindow::Update()
{

}


//This function will eliminate the window
bool cWindow::DeInit()
{
	return true;
}