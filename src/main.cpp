/*    
    MClipToHTML.exe : Converts text in Windows Clipboard to HTML text.
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

//v1.0 copyright Comine.com 20170328T1456
#include <Windows.h>
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MClipBoard.h"
#include "MTextToHTML.h"
#include "MLicenseGPL.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MClipToHTML";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()<1)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL license(true);
		license.Print();
		return 0;
		}

	// Create a dummy button windows
	HWND hwindow=CreateWindowA("BUTTON",GApplicationName,WS_OVERLAPPEDWINDOW,
			100,100,100,100,NULL,NULL,GetModuleHandle(NULL),NULL);
	if(hwindow==NULL)
		{
		MStdPrintf("**Unable to create a window for using clipboard\n");
		return 1;
		}

	MClipBoard clipboard;
	if(clipboard.Create(hwindow)==false)
		{
		MStdPrintf("**Unable to init clip board\n");
		DestroyWindow(hwindow);
		return 2;
		}

	if(clipboard.HasText()==false)
		{
		MStdPrintf("** clip board does not contain any text data");
		clipboard.Destroy();
		DestroyWindow(hwindow);
		return 3;
		}

	MTextToHTML htmlgen;
	if(htmlgen.Create()==false)
		{
		clipboard.Destroy();
		DestroyWindow(hwindow);
		return 4;
		}

	MBuffer textdata;
	if(clipboard.GetText(textdata)==false)
		{
		MStdPrintf("**Unable to get text from clipboard\n");
		htmlgen.Destroy();
		clipboard.Destroy();
		DestroyWindow(hwindow);
		return 5;
		}

	const char *newhtmltext=htmlgen.GetHTML(textdata.GetBuffer() );
	if(newhtmltext==0)
		{
		htmlgen.Destroy();
		clipboard.Destroy();
		DestroyWindow(hwindow);
		return 6;
		}

	// Put converted text back into clipboard
	if(clipboard.CopyText(newhtmltext)==false)
		{
		htmlgen.Destroy();
		clipboard.Destroy();
		DestroyWindow(hwindow);
		return 7;
		}

	MStdPrintf("converted text to html in clipboard");
	
	htmlgen.Destroy();
	clipboard.Destroy();
	DestroyWindow(hwindow);

	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?|-gpl]\n"
				"           v%s copyright Comine.com\n"
				"           use -gpl to see GPL License\n"
				"\n"
				"   Program will convert text in the clipboard into html text.\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


