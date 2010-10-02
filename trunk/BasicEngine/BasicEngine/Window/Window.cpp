#include "Window.h"

#include "ApplicationProperties.h"


//Create the window with the parameters it receives
bool cWindow::Init (cApplicationProperties &lProperties)
{

	//1.- variable Initialization
	
	mDC = NULL;
	mWnd = NULL;
	mInstance = GetModuleHandle(NULL);
	mProperties = lProperties;
	

	//2 .- Window Initialization or Register the window

	WNDCLASS lWndClass; // Windows Class Structure
	lWndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Size, And Own DC For Window.
	//lWndClass.lpfnWndProc = (WNDPROC) WndProc; // WndProc Handles Messages   //YORMAN LA QUITO POR AHORA, PARA VER DONDE VA
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
	

	//3.- Prepare to Window for FullScreen

	if (lProperties.mbFullscreen)
	{
		DEVMODE lScreenSettings; // Device Mode
		
		memset(&lScreenSettings,0,sizeof(lScreenSettings));// Clear the memory
		
		lScreenSettings.dmSize = sizeof(lScreenSettings);
		lScreenSettings.dmPelsWidth = lProperties.muiWidth;
		lScreenSettings.dmPelsHeight = lProperties.muiHeight;
		lScreenSettings.dmBitsPerPel = lProperties.muiBits;
		lScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		
		// Try To Set Selected Mode And Get Results.
		LONG lResult = ChangeDisplaySettings(&lScreenSettings,CDS_FULLSCREEN);
		if (lResult != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox (NULL, 
											"The Requested Fullscreen Mode Is Not	Supported By \n Your Video Card. Use Windowed Mode Instead?",
											"ERROR",	MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				mProperties.mbFullscreen = false;
			}
			else
			{
				MessageBox(NULL, "Program Will Now Close.","ERROR",
				MB_OK|MB_ICONSTOP);
				return false;
			}
		}
	}


	//4.- Create Window
	DWORD lExStyle;
	DWORD lStyle;
	
	if (mProperties.mbFullscreen)
	{
		lExStyle=WS_EX_APPWINDOW; // Window Extended Style
		lStyle=WS_POPUP; // Windows Style
		ShowCursor(FALSE); // Hide Mouse Pointer
		}
	else
	{
		lExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; 		// Window Extended Style
		lStyle=WS_OVERLAPPEDWINDOW; // Windows Style
	}
	
	RECT lWindowRect;
	lWindowRect.left = (long)0;
	lWindowRect.right = (long)lProperties.muiWidth;
	lWindowRect.top = (long)0;
	lWindowRect.bottom = (long)lProperties.muiHeight;
	
	AdjustWindowRectEx(&lWindowRect, lStyle, FALSE, lExStyle);
	
	// Create The Window
	mWnd = CreateWindowEx (lExStyle,
												lProperties.macApplicationName.c_str(), // Class Name
												lProperties.macApplicationName.c_str(), // Window Title
												lStyle | // Defined Window Style
												WS_CLIPSIBLINGS | // Required Window Style
												WS_CLIPCHILDREN, // Required Window Style
												0, 0, // Window Position
												lWindowRect.right-lWindowRect.left, // Calculate Window Width
												lWindowRect.bottom-lWindowRect.top, // Calculate Window Height
												NULL, // No Parent Window
												NULL, // No Menu
												mInstance, // Instance
												NULL);
	if (!mWnd)
	{
		Deinit(); // Reset The Display
		MessageBox(NULL,"Window Creation Error.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(mWnd,SW_SHOW);
	SetForegroundWindow(mWnd);
	SetFocus(mWnd);


	//Device access context
	mDC = GetDC(mWnd);
	if (!mDC)
	{
		Deinit();
		MessageBox(NULL,"Can't access the HDC.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}


//This function will update the window and respond to possible events come of it.
void cWindow::Update()
{

}


//This function will eliminate the window
bool cWindow::Deinit()
{
	return true;
}