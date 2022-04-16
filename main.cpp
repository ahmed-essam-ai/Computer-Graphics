#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <Windows.h>
#include <math.h>
void swap(int& x1, int& y1, int& x2, int& y2)
{
	int tmp = x1;
	x1 = x2;
	x2 = tmp;
	tmp = y1;
	y1 = y2;
	y2 = tmp;
}
int Round(double x)
{
	return (int)(x + 0.5);
}
void DrawLine1(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (abs(dy) <= abs(dx))
	{
		if (x1 > x2)swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, c);
		int x = x1;
		while (x < x2)
		{
			x++;
			double y = y1 + (double)(x - x1)*dy / dx;
			SetPixel(hdc, x, Round(y), c);

		}
	}
	else {
		if (y1 > y2)swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, c);
		int y = y1;
		while (y < y2)
		{
			y++;
			double x = x1 + (double)(y - y1)*dx / dy;
			SetPixel(hdc, Round(x), y, c);
		}
	}

}
void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{
	SetPixel(hdc, xc + a, yc + b, color);
	DrawLine1(hdc,xc,yc, xc + a, yc + b, RGB(255,0,0));
	SetPixel(hdc, xc - a, yc + b, color);
	DrawLine1(hdc,xc,yc, xc - a, yc + b, RGB(0,255,0));
	SetPixel(hdc, xc - a, yc - b, color);
	DrawLine1(hdc,xc,yc, xc - a, yc - b, RGB(0,0 , 255));
	SetPixel(hdc, xc + a, yc - b, color);
	DrawLine1(hdc,xc,yc, xc + a, yc - b, RGB(128,0,0));
	SetPixel(hdc, xc + b, yc + a, color);
	DrawLine1(hdc,xc,yc, xc + b, yc + a, RGB(255,255,0));
	SetPixel(hdc, xc - b, yc + a, color);
	DrawLine1(hdc,xc,yc, xc - b, yc + a, RGB(128,0,128));
	SetPixel(hdc, xc - b, yc - a, color);
	DrawLine1(hdc,xc,yc, xc - b, yc - a, RGB(0,0 , 128));
	SetPixel(hdc, xc + b, yc - a, color);
	DrawLine1(hdc,xc,yc, xc + b, yc - a, RGB(192,192,192));
}

void CircleIterativePolar(HDC hdc, int xc, int yc, int R, COLORREF color)
{
	double x = R, y = 0;
	double dtheta = 1.0 / R;
	double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
	//Draw8Points(hdc, xc, yc, R, 0, color);
	while (x>y)
	{
		double x1 = x*cdtheta - y*sdtheta;
		y = x*sdtheta + y*cdtheta;
		x = x1;
		Draw8Points(hdc, xc, yc, x, y, color);
		//DrawLine1(hdc, xc, yc, Round(x), Round(y), RGB(255, 0, 0));
	}
}
void Draw8Lines(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{
	DrawLine1(hdc,xc,yc, xc + a, yc + b, color);
	DrawLine1(hdc,xc,yc, xc - a, yc + b, color);
	DrawLine1(hdc,xc,yc, xc - a, yc - b, color);
	DrawLine1(hdc,xc,yc, xc + a, yc - b, color);
	DrawLine1(hdc,xc,yc, xc + b, yc + a, color);
	DrawLine1(hdc,xc,yc, xc - b, yc + a, color);
	DrawLine1(hdc,xc,yc, xc - b, yc - a, color);
	DrawLine1(hdc,xc,yc, xc + b, yc - a, color);
}

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
int x , y , x2 ,y2, raduis ;
static int index=0 ;
static int  index2=0;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
    case WM_LBUTTONDOWN:
        if(index==0){
            x=LOWORD(lParam);
            y=HIWORD(lParam);
            index=1;
        }

        break;
    case WM_RBUTTONDOWN:
        if(index==1){
            x2=LOWORD(lParam);
            y2=HIWORD(lParam);
            //DrawLine1(hdc, x, y, x2, y2, RGB(255, 0, 0));

            raduis=sqrt(pow(y2-y , 2) + pow(x-x2 , 2));

            //if(index2==0){
                CircleIterativePolar(hdc,  x,  y,  raduis, RGB(0, 0, 0));
                index=0;
                //index2=1;
                //}
            //Draw8Lines(hdc, x, y, 0, raduis, RGB(255, 0, 0));
            ReleaseDC(hwnd, hdc);
            }
        break;
    case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
