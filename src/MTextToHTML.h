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

//v0.0 copyright Comine.com 20150816U1847
#ifndef MTextToHTML_h
#define MTextToHTML_h

/////////////////////////////////////////////////
#include "MStdLib.h"
#include "MStringBuffer.h"

//******************************************************
//**  MTextToHTML class
//******************************************************
class MTextToHTML
	{
	////////////////////////////////////////////////
	MStringBuffer mBuffer;
	
	////////////////////////////////////////////////
	void ClearObject(void);
	

	////////////////////////////////////////////////
	public:
	MTextToHTML(bool create=false);
	~MTextToHTML(void);
	bool Create(void);
	bool Destroy(void);
	const char *GetHTML(const char *text);			// Returns pointer to html text.=0 on failure
	};

#endif // MTextToHTML_h

