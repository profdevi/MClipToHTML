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
#ifndef MClipBoard_h
#define MClipBoard_h

#include <windows.h>
#include "MStdLib.h"
#include "MBuffer.h"

////////////////////////////////////////////////////
class MClipBoard
	{
	HWND mhWndOwner;

	////////////////////////////////////////////////
	void ClearObject(void);

	////////////////////////////////////////////////
	public:
	MClipBoard(void);
	MClipBoard(HWND howner);
	~MClipBoard(void);
	bool Create(HWND howner);				// Construct the object state
	bool Destroy(void);						// Detstroy the object state
	bool CopyText(const char *text);		// Copy text into Windows Clipboard
	bool GetText(MBuffer &text);			// Get Text from Windows clipboard
	bool HasText(void);						// Check if clipboard has text
	bool Clear(void);						// Clears clipboard
	};

#endif // MClipBoard_h