#pragma once

/*
infolist.hpp

�������������� ������
*/
/*
Copyright � 1996 Eugene Roshal
Copyright � 2000 Far Group
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "panel.hpp"
#include "dizviewer.hpp"
#include "macro.hpp"

class InfoList:public Panel
{
	// ��������� ������
	struct InfoListSectionState
	{
		bool Show;   // ��������/��������?
		SHORT Y;     // ���?
	};

	enum InfoListSectionStateIndex
	{
		// ������� �� ������! ������ ��������� � �����!
		ILSS_DISKINFO,
		ILSS_MEMORYINFO,
		ILSS_DIRDESCRIPTION,
		ILSS_PLDESCRIPTION,
		ILSS_POWERSTATUS,

		ILSS_LAST
	};

	private:
		DizViewer *DizView;
		FARMACROAREA PrevMacroMode;
		bool OldWrapMode;
		bool OldWrapType;
		string strDizFileName;
		InfoListSectionState SectionState[ILSS_LAST];

	private:
		virtual void DisplayObject() override;
		bool ShowDirDescription(int YPos);
		bool ShowPluginDescription(int YPos);

		void PrintText(const string& Str);
		void PrintText(LNGID MsgID);
		void PrintInfo(const string& Str);
		void PrintInfo(LNGID MsgID);
		void SelectShowMode(void);
		void DrawTitle(string &strTitle,int Id,int &CurY);

		int  OpenDizFile(const string& DizFile,int YPos);
		void SetMacroMode(int Restore = FALSE);
		void DynamicUpdateKeyBar();

	public:
		InfoList();
	private:
		virtual ~InfoList();

	public:
		virtual int ProcessKey(int Key) override;
		virtual int ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent) override;
		virtual __int64 VMProcess(int OpCode,void *vParam=nullptr,__int64 iParam=0) override;
		virtual void Update(int Mode) override;
		virtual void SetFocus() override;
		virtual void KillFocus() override;
		virtual string &GetTitle(string &Title,int SubLen=-1,int TruncSize=0) override;
		virtual BOOL UpdateKeyBar() override;
		virtual void CloseFile() override;
		virtual int GetCurName(string &strName, string &strShortName) override;
		virtual int UpdateIfChanged(int UpdateMode) override;
};
