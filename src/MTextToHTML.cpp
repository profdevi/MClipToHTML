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

//v1.0 copyright Comine.com 20170328T1423
#include "MStdLib.h"
#include "MStringBuffer.h"
#include "MTextToHTML.h"


//******************************************************
//**  Module elements
//******************************************************
////////////////////////////////////////////////
static int GFindHTMLCount(const char *txt)
	{
	int count=0;
	for(int i=0;txt[i]!=0;++i)
		{
		const char ch=txt[i];
		if(ch=='\r') {  continue;  }
		if(ch=='\n')
			{
			// MStdPrintf("<br/>\n");  
			// MStdPrintf("<br/>\r\n");  windows
			#ifdef MSTDLIB_OS_WINDOWS
			count=count+7;
			#else
			count=count+6;
			#endif 
			
			continue;
			}

		if(ch=='>')
			{
			// MStdPrintf("&gt;");
			count=count+4;
			continue;	
			}

		if(ch=='<')
			{
			// MStdPrintf("&lt;");
			count=count+4;
			continue;
			}

		if(ch=='\t')
			{
			// 1 tab stop= 4 spaces
			//MStdPrintf("&nbsp;&nbsp;&nbsp;&nbsp;");
			count=count+6*4;
			continue;
			}

		if(ch=='\"')
			{
			//MStdPrintf("&quot;");
			count=count+6;
			continue;
			}

		if(ch=='\'')
			{
			// &apos; does not work on IE
			// MStdPrintf("&#39;");
			count=count+5;
			continue;
			}

		if(ch==' ')
			{
			// MStdPrintf("&nbsp;");
			count=count+6;
			continue;
			}

		if(ch=='&')
			{
			// MStdPrintf("&amp;");
			count=count+5;
			continue;
			}

		if(ch<32 || ch>=128)
			{
			// MStdPrintf("&#%d",(int)ch);
			char buf[20];
			MStdSPrintf(buf,sizeof(buf)-2,"&#%d",(int)ch);
			const int writelength=MStdStrLen(buf);
			MStdAssert(writelength>0);

			count=count + writelength;
			continue;
			}

		// MStdPrintf("%c",ch);
		count = count + 1;
		}
	
	return count;
	}


//******************************************************
//**  MTextToHTML class
//******************************************************
void MTextToHTML::ClearObject(void)
	{
	}



////////////////////////////////////////////////
MTextToHTML::MTextToHTML(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MTextToHTML::~MTextToHTML(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MTextToHTML::Create(void)
	{
	Destroy();	
	return true;
	}


////////////////////////////////////////////////
bool MTextToHTML::Destroy(void)
	{
	mBuffer.Destroy();
	ClearObject();
	return true;
	}


/////////////////////////////////////////////////
const char *MTextToHTML::GetHTML(const char *text)
	{
	MStdAssert(text!=0);

	const int htmllength=GFindHTMLCount(text);
	if(htmllength<=0)
		{
		return 0;
		}

	if(mBuffer.Create(htmllength+100)==false)
		{
		return 0;
		}

	mBuffer.Clear();

	for(int i=0;text[i]!=0;++i)
		{
		const unsigned char ch=text[i];

		if(ch=='\r') {  continue;  }
		if(ch=='\n')
			{
			// MStdPrintf("<br/>\n");  
			// MStdPrintf("<br/>\r\n");  windows
			#ifdef MSTDLIB_OS_WINDOWS
			mBuffer.Add("<br/>\r\n");
			#else
			mBuffer.Add("<br/>\n");
			#endif 

			continue;
			}

		if(ch=='>')
			{
			mBuffer.Add("&gt;");
			continue;	
			}

		if(ch=='<')
			{
			mBuffer.Add("&lt;");
			continue;
			}

		if(ch=='\t')
			{
			// 1 tab stop= 4 spaces
			mBuffer.Add("&nbsp;&nbsp;&nbsp;&nbsp;");
			continue;
			}

		if(ch=='\"')
			{
			mBuffer.Add("&quot;");
			continue;
			}

		if(ch=='\'')
			{
			// &apos; does not work on IE
			mBuffer.Add("&#39;");
			continue;
			}

		if(ch==' ')
			{
			mBuffer.Add("&nbsp;");
			continue;
			}

		if(ch=='&')
			{
			mBuffer.Add("&amp;");
			continue;
			}

		if(ch<32 || ch>=128)
			{
			// MStdPrintf("&#%d",(int)ch);
			char buf[20];
			MStdSPrintf(buf,sizeof(buf)-2,"&#%d",(int)ch);
			mBuffer.Add(buf);
			continue;
			}

		mBuffer.Add(ch);
		}

	return mBuffer.Get();
	}


