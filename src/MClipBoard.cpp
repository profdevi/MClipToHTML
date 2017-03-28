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

//v2.0 copyright Comine.com  20170328T1345
#include <windows.h>
#include "MStdLib.h"
#include "MBuffer.h"
#include "MClipBoard.h"


//**********************************************************
//** MClipBoard Code
//**********************************************************
void MClipBoard::ClearObject(void)
	{
	mhWndOwner=NULL;
	}

	
/////////////////////////////////////////////////////////////
MClipBoard::MClipBoard(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MClipBoard::MClipBoard(HWND howner)
	{
	mhWndOwner=NULL;
	if(Create(howner)==false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MClipBoard::~MClipBoard(void) {  Destroy();  }


////////////////////////////////////////////////
bool MClipBoard::Create(HWND howner)
	{
	Destroy();
	if(howner==NULL)
		{
		Destroy();  return false;
		}

	mhWndOwner=howner;  

	return true;
	}


////////////////////////////////////////////////
bool MClipBoard::Destroy(void)
	{
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
bool MClipBoard::CopyText(const char *text)
	{
	if(OpenClipboard(mhWndOwner)==FALSE)
		{
		return false;
		}

	// Empty the clipboard before saving
	EmptyClipboard();

	HGLOBAL hmemory=GlobalAlloc(GMEM_MOVEABLE,MStdStrLen(text)+1);
	if(hmemory==NULL)
		{
		CloseClipboard();  return false;
		}

	char *fixedmemory=(char *)GlobalLock(hmemory);
	if(fixedmemory==NULL)
		{
		GlobalFree(hmemory);  CloseClipboard();  return false;
		}

	MStdStrCpy(fixedmemory,text);

	GlobalUnlock(hmemory); 

	SetClipboardData(CF_TEXT,hmemory);

	CloseClipboard();  return true;
	}


////////////////////////////////////////////////
bool MClipBoard::GetText(MBuffer &text)
	{
	if(OpenClipboard(mhWndOwner)==FALSE)
		{
		return false;
		}

	if(IsClipboardFormatAvailable(CF_TEXT)==FALSE)
		{  CloseClipboard();  return false;  }

	// CopyClipboard Data
	HGLOBAL hglobal=GetClipboardData(CF_TEXT);
	if(hglobal==NULL)
		{
		CloseClipboard();  return false;
		}


	const char *clipdata=(const char *)GlobalLock(hglobal);
	if(clipdata==NULL)
		{
		CloseClipboard();  return false;
		}

	if(text.Create(MStdStrLen(clipdata)+1)==false)
		{
		GlobalUnlock(hglobal); CloseClipboard();  return false;
		}
	
	if(text.SetString(clipdata)==false)
		{
		GlobalUnlock(hglobal); CloseClipboard();  return false;
		}

	GlobalUnlock(hglobal); CloseClipboard();
	return true;
	}


//////////////////////////////////////////////////////////
bool MClipBoard::HasText(void)						// Check if clipboard has text
	{
	if(OpenClipboard(mhWndOwner)==FALSE)
		{
		return false;
		}

	if(IsClipboardFormatAvailable(CF_TEXT)==FALSE)
		{  CloseClipboard();  return false;  }
	
	CloseClipboard();  return true;
	}


//////////////////////////////////////////////////////
bool MClipBoard::Clear(void)
	{
	if(OpenClipboard(mhWndOwner)==FALSE)
		{
		return false;
		}

	if(EmptyClipboard()==FALSE)
		{  CloseClipboard();  return false;  }
	
	CloseClipboard();  return true;
	}



