/*
fileedit.cpp

�������������� ����� - ���������� ��� editor.cpp

*/

/* Revision: 1.42 12.05.2001 $ */

/*
Modify:
  12.05.2001 DJ
    ! ��������� �� OnChangeFocus ���������� � Frame
  11.05.2001 OT
    ! ��������� Background
  10.05.2001 DJ
    + OnDestroy() (�� �������� ���������� �� view/edit history)
    + FileEditor::DisableHistory, DisableF6
    + Alt-F11 - �������� �������
    + ��� Ctrl-F10 ������������� �� ������
  07.05.2001 SVS
    ! SysLog(); -> _D(SysLog());
  07.05.2001 DJ
    + �������� NameList (���� ������ ��� �������� ������� �� ����� ���
      ��������� ������� F6)
    - ������ �� ����������
  06.05.2001 DJ
    ! �������� #include
    + ��������� F6
  07.05.2001 ��
    - ��������� �� "������������" ExitCode ����� � �� Frame :)
  06.05.2001 ��
    ! �������������� Window � Frame :)
  05.05.2001 DJ
    + �������� NWZ
  04.05.2001 DJ
    - � �������� ��������� 623-�� ��� ������� ���� 616:
      "�� �������� KEY_MACRO* � ProcessEditorInput()"
      ������ ��� �������.
  29.04.2001 ��
    + ��������� NWZ �� ����������
  28.04.2001 VVM
    + KeyBar ���� ����� ������������ �������.
  19.04.2001 SVS
    ! ������ SaveAs ����������� ������� ��� ������� Ctrl-Enter
  10.04.2001 IS
    ! �� ������ SetCurDir ��� ctrl-f10, ���� ������ ���� ��� ���� �� ��������
      �������, ��� ����� ���������� ����, ��� ��������� � ���������
      ������� �� ������������.
  05.04.2001 SVS
    + �������� ����� ������ "FileSaveAs" ��� ������� SaveAs
  28.03.2001 SVS
    ! ��������� � SaveFile ����� �������� - SaveAs?
  22.03.2001 SVS
    - "���������" ������� ����� ���������� �������
  18.03.2001 IS
    ! ������� ������� �������� ��� �������� �� "������ ��� ������" �
      "��� ������", ��� ����� ���������� �� ��������, ����� ��������� ������
      "�� �������, ��� ������ ������������� r/o ����" ��� ��� �������� ������.
  01.03.2001 IS
    - ���: �� �����������, �������� �� ���� �� ����� ���� �� ctrl-f10
  27.02.2001 SVS
    + ������� �� ������ ���� ������.
  26.02.2001 IS
    + � ������� ��� � �� ��� ������� :(
      ������ �� ����� ���� ����������� ����������, ������������� � ��������� ��
      alt-shift-f9, ���������, ����� �������� �������� ��������� � �����
      "��������� ������� �����", "��������� ��������"
  21.02.2001 IS
    + ��� ��������� alt-shift-f9 �������� � ���������� �����������
  15.02.2001 IS
    + ������� "���������� �����" � "del ������� �����"
      ��� ����� �������� ��������� �� AltShiftF9
  15.02.2001 IS
    + ������� ������ ��������� � ����� "������� ������ ���������" ��� �����
      �������� ��������� �� AltShiftF9
  01.02.2001 IS
    ! ��������� �� F6 ����� � ��������� �������� ����� �����, � �� ���������
  03.01.2001 SVS
    ! ��� KEY_ALTSHIFTF9 ������ ������� Show()
  19.12.2000 SVS
    + Alt-Shift-F9 - ����� ������� �������� (� ������ IS)
  16.12.2000 tran 1.15
    ! Ctrl-F10 ������� �� ��������� ������
  15.12.2000 SVS
    - Shift-F4, ����� ����. ������ ��������� :-(
  03.12.2000 SVS
    + "���� ���� ����� ������� ReadOnly..." ����� System � Hidden - ��������
      ��������.
  29.11.2000 SVS
    + ���� ���� ����� ������� ReadOnly ��� System ��� Hidden,
      � �������� �� ������ ���������, �� ������� �������.
  03.11.2000 OT
    ! �������� �������� ������������� ��������
  02.11.2000 OT
    ! �������� �������� �� ����� ������, ����������� ��� ��� �����.
  16.10.2000 SVS
    ! ������ 1.08 (#229)
  13.10.2000 tran 1.08
    ! ��� �������� ����������� �� IsFileModified ������ IsFileChanged()
  27.09.2000 SVS
    + ������ �����/����� � �������������� ������� PrintMan
    ! Ctrl-Alt-Shift - ���������, ���� ����.
  27.09.2000 SKV
    + ��� ����������� ���������������� ����� � Ctrl-O �������� FEdit.Hide()
  24.08.2000 SVS
    + ��������� ������� ������ ���������� �� ������� CtrlAltShift
  07.08.2000 SVS
    + ������� �������� ����������� �������������� ������
    + ������� ������������� KeyBar Labels - InitKeyBar()
  21.07.2000 SKV
    + ����� � ����������������� �� ������������� ����� �� CTRLF10
  29.06.2000 tran
    + �������� ���� �������������� ������
  28.06.2000 tran
    - (NT Console resize bug)
      adding FileEditor::SetScreenPosition
  25.06.2000 SVS
    ! ���������� Master Copy
    ! ��������� � �������� ���������������� ������
*/

#include "headers.hpp"
#pragma hdrstop

#include "fileedit.hpp"
#include "global.hpp"
#include "fn.hpp"
#include "lang.hpp"
#include "keys.hpp"
#include "ctrlobj.hpp"
#include "filepanels.hpp"
#include "panel.hpp"
#include "dialog.hpp"
#include "fileview.hpp"
#include "ctrlobj.hpp"
#include "manager.hpp"
#include "namelist.hpp"
#include "history.hpp"
#include "cmdline.hpp"

FileEditor::FileEditor(char *Name,int CreateNewFile,int EnableSwitch,
                       int StartLine,int StartChar,int DisableHistory,
                       char *PluginData)
{
  SetPosition(0,0,ScrX,ScrY);
  FullScreen=TRUE;
  Init(Name,CreateNewFile,EnableSwitch,StartLine,StartChar,DisableHistory,PluginData);
}


FileEditor::FileEditor(char *Name,int CreateNewFile,int EnableSwitch,
            int StartLine,int StartChar,char *Title,
            int X1,int Y1,int X2,int Y2)
{
  SetPosition(X1,Y1,X2,Y2);
  FullScreen=(X1==0 && Y1==0 && X2==ScrX && Y2==ScrY);
  FEdit.SetTitle(Title);
  Init(Name,CreateNewFile,EnableSwitch,StartLine,StartChar,TRUE,"");
}


void FileEditor::Init(char *Name,int CreateNewFile,int EnableSwitch,
                      int StartLine,int StartChar,int DisableHistory,
                      char *PluginData)
{
  /* $ 07.05.2001 DJ */
  EditNamesList = NULL;
  KeyBarVisible = TRUE;
  /* DJ $ */
  /* $ 10.05.2001 DJ */
  FileEditor::DisableHistory = DisableHistory;
  EnableF6 = EnableSwitch;
  /* DJ $ */
  if (*Name==0)
    return;
  FEdit.SetPluginData(PluginData);
  FEdit.SetHostFileEditor(this);
  _D(SysLog("Editor;:Editor(), EnableSwitch=%i",EnableSwitch));
  SetCanLoseFocus(EnableSwitch);
  GetCurrentDirectory(sizeof(StartDir),StartDir);
  strcpy(FileName,Name);
  if (sizeof(FullFileName)<=ConvertNameToFull(FileName,FullFileName, sizeof(FullFileName))) {
    return;
  }

  if (EnableSwitch)
  {
    int FramePos=FrameManager->FindFrameByFile(MODALTYPE_EDITOR,FullFileName);
    if (FramePos!=-1)
    {
      int MsgCode=Message(0,2,MSG(MEditTitle),FullFileName,MSG(MAskReload),
                          MSG(MCurrent),MSG(MReload));
      switch(MsgCode)
      {
        case 0:
          FrameManager->ActivateFrameByPos (FramePos);
          return;
        case 1:
          break;
        default:
          return;
      }
    }
  }

  /* $ 29.11.2000 SVS
     ���� ���� ����� ������� ReadOnly ��� System ��� Hidden,
     � �������� �� ������ ���������, �� ������� �������.
  */
  /* $ 03.12.2000 SVS
     System ��� Hidden - �������� ��������
  */
  /* $ 15.12.2000 SVS
    - Shift-F4, ����� ����. ������ ��������� :-(
  */
  DWORD FAttr=GetFileAttributes(Name);
  if((Opt.EditorReadOnlyLock&2) &&
     FAttr != -1 &&
     (FAttr &
        (FILE_ATTRIBUTE_READONLY|
           /* Hidden=0x2 System=0x4 - ������������� �� 2-� ���������,
              ������� ��������� ����� 0110.0000 �
              �������� �� ���� ����� => 0000.0110 � ��������
              �� ����� ������ ��������  */
           ((Opt.EditorReadOnlyLock&0x60)>>4)
        )
     )
  )
  /* SVS $ */
  {
    if(Message(MSG_WARNING,2,MSG(MEditTitle),Name,MSG(MEditRSH),
                             MSG(MEditROOpen),MSG(MYes),MSG(MNo)))
    {
      //SetLastError(ERROR_ACCESS_DENIED);
      return;
    }
  }
  /* SVS 03.12.2000 $ */
  /* SVS $ */

  FEdit.SetPosition(X1,Y1,X2,Y2-1);
  FEdit.SetStartPos(StartLine,StartChar);
  int UserBreak;
  if (!FEdit.ReadFile(FileName,UserBreak) && (!CreateNewFile || UserBreak))
  {
    if (UserBreak!=1)
    {
      Message(MSG_WARNING|MSG_ERRORTYPE,1,MSG(MEditTitle),MSG(MEditCannotOpen),FileName,MSG(MOk));
      ExitCode=0;
    }
    else
      ExitCode=3;
    return;
  }
  ShowConsoleTitle();
  EditKeyBar.SetOwner(this);
  EditKeyBar.SetPosition(X1,Y2,X2,Y2);

  /* $ 07.08.2000 SVS
    ! ���, �������� KeyBar ������� � ��������� ������� */
  InitKeyBar();
  /* SVS $*/

/*///
  Process();
  ExitCode=IsFileChanged() ? 1 : 2;
  if (!DisableHistory)
    4->ViewHistory->AddToHistory(FullFileName,MSG(MHistoryEdit),1);
*///
   MacroMode=MACRO_EDITOR; ///

}

/* $ 07.08.2000 SVS
  ������� ������������� KeyBar Labels
*/
void FileEditor::InitKeyBar(void)
{
  /* $ 29.06.2000 tran
     ������� �������� ���� �������������� ������ */
  /* $ 10.05.2001 DJ
     ������� �� EnableF6 ������ CanLoseFocus
  */
  char *FEditKeys[]={MSG(MEditF1),MSG(MEditF2),MSG(MEditF3),MSG(MEditF4),MSG(MEditF5),EnableF6 ? MSG(MEditF6):"",MSG(MEditF7),MSG(MEditF8),MSG(MEditF9),MSG(MEditF10),MSG(MEditF11),MSG(MEditF12)};
  /* DJ $ */
  char *FEditShiftKeys[]={MSG(MEditShiftF1),MSG(MEditShiftF2),MSG(MEditShiftF3),MSG(MEditShiftF4),MSG(MEditShiftF5),MSG(MEditShiftF6),MSG(MEditShiftF7),MSG(MEditShiftF8),MSG(MEditShiftF9),MSG(MEditShiftF10),MSG(MEditShiftF11),MSG(MEditShiftF12)};
  char *FEditAltKeys[]={MSG(MEditAltF1),MSG(MEditAltF2),MSG(MEditAltF3),MSG(MEditAltF4),MSG(MEditAltF5),MSG(MEditAltF6),MSG(MEditAltF7),MSG(MEditAltF8),MSG(MEditAltF9),MSG(MEditAltF10),MSG(MEditAltF11),MSG(MEditAltF12)};
  char *FEditCtrlKeys[]={MSG(MEditCtrlF1),MSG(MEditCtrlF2),MSG(MEditCtrlF3),MSG(MEditCtrlF4),MSG(MEditCtrlF5),MSG(MEditCtrlF6),MSG(MEditCtrlF7),MSG(MEditCtrlF8),MSG(MEditCtrlF9),MSG(MEditCtrlF10),MSG(MEditCtrlF11),MSG(MEditCtrlF12)};

  if(CtrlObject->Plugins.FindPlugin(SYSID_PRINTMANAGER) == -1)
    FEditAltKeys[5-1]="";
  /* tran $ */
  /* $ 07.08.2000 SVS
     ������� �������� ����������� �������������� ������ */
  char *FEditAltShiftKeys[]={MSG(MEditAltShiftF1),MSG(MEditAltShiftF2),MSG(MEditAltShiftF3),MSG(MEditAltShiftF4),MSG(MEditAltShiftF5),MSG(MEditAltShiftF6),MSG(MEditAltShiftF7),MSG(MEditAltShiftF8),MSG(MEditAltShiftF9),MSG(MEditAltShiftF10),MSG(MEditAltShiftF11),MSG(MEditAltShiftF12)};
  char *FEditCtrlShiftKeys[]={MSG(MEditCtrlShiftF1),MSG(MEditCtrlShiftF2),MSG(MEditCtrlShiftF3),MSG(MEditCtrlShiftF4),MSG(MEditCtrlShiftF5),MSG(MEditCtrlShiftF6),MSG(MEditCtrlShiftF7),MSG(MEditCtrlShiftF8),MSG(MEditCtrlShiftF9),MSG(MEditCtrlShiftF10),MSG(MEditCtrlShiftF11),MSG(MEditCtrlShiftF12)};
  char *FEditCtrlAltKeys[]={MSG(MEditCtrlAltF1),MSG(MEditCtrlAltF2),MSG(MEditCtrlAltF3),MSG(MEditCtrlAltF4),MSG(MEditCtrlAltF5),MSG(MEditCtrlAltF6),MSG(MEditCtrlAltF7),MSG(MEditCtrlAltF8),MSG(MEditCtrlAltF9),MSG(MEditCtrlAltF10),MSG(MEditCtrlAltF11),MSG(MEditCtrlAltF12)};
  /* SVS $*/

  EditKeyBar.Set(FEditKeys,sizeof(FEditKeys)/sizeof(FEditKeys[0]));
  EditKeyBar.SetShift(FEditShiftKeys,sizeof(FEditShiftKeys)/sizeof(FEditShiftKeys[0]));
  EditKeyBar.SetAlt(FEditAltKeys,sizeof(FEditAltKeys)/sizeof(FEditAltKeys[0]));
  EditKeyBar.SetCtrl(FEditCtrlKeys,sizeof(FEditCtrlKeys)/sizeof(FEditCtrlKeys[0]));

  /* $ 07.08.2000 SVS
     ������� �������� ����������� �������������� ������ */
  EditKeyBar.SetCtrlAlt(FEditCtrlAltKeys,sizeof(FEditCtrlAltKeys)/sizeof(FEditCtrlAltKeys[0]));
  EditKeyBar.SetCtrlShift(FEditCtrlShiftKeys,sizeof(FEditCtrlShiftKeys)/sizeof(FEditCtrlShiftKeys[0]));
  EditKeyBar.SetAltShift(FEditAltShiftKeys,sizeof(FEditAltShiftKeys)/sizeof(FEditAltShiftKeys[0]));
  /* SVS $ */

  EditKeyBar.Show();
  SetKeyBar(&EditKeyBar);
  FEdit.SetEditKeyBar(&EditKeyBar);
}
/* SVS $ */

/* $ 07.05.2001 DJ
   � ����������� ������� EditNamesList, ���� �� ��� ������, � � SetNamesList()
   ������� EditNamesList � �������� ���� ��������
*/

FileEditor::~FileEditor()
{
  if (EditNamesList)
    delete EditNamesList;
}

void FileEditor::SetNamesList (NamesList *Names)
{
  if (EditNamesList == NULL)
    EditNamesList = new NamesList;
  Names->MoveData (EditNamesList);
}

/* DJ $ */

void FileEditor::Show()
{
  if (FullScreen)
  {
    EditKeyBar.SetPosition(0,ScrY,ScrX,ScrY);
    EditKeyBar.Redraw();
    SetPosition(0,0,ScrX,ScrY-1);
    FEdit.SetPosition(0,0,ScrX,ScrY-1);
  }
  ScreenObject::Show();
}


void FileEditor::DisplayObject()
{
  FEdit.Show();
}


int FileEditor::ProcessKey(int Key)
{
  switch(Key)
  {
    /* $ 24.08.2000 SVS
       + ��������� ������� ������ ���������� �� ������� CtrlAltShift
    */
    case KEY_CTRLALTSHIFTPRESS:
      if(!(Opt.AllCtrlAltShiftRule & CASR_EDITOR))
        return(TRUE);
    case KEY_CTRLO:
      /*$ 27.09.2000 skv
        To prevent redraw in macro with Ctrl-O
      */
      FEdit.Hide();
      /* skv$*/
      FrameManager->ShowBackground();
      WaitKey(Key==KEY_CTRLALTSHIFTPRESS?KEY_CTRLALTSHIFTRELEASE:-1);
      Show();
      return(TRUE);
/*
      Hide();
      if (CtrlObject->Cp()->LeftPanel!=CtrlObject->Cp()->RightPanel)
        CtrlObject->FrameManager->ShowBackground();

      else
      {
        EditKeyBar.Hide();
        if(Opt.AllCtrlAltShiftRule & CASR_EDITOR)
          WaitKey(Key==KEY_CTRLALTSHIFTPRESS?KEY_CTRLALTSHIFTRELEASE:-1);
      }
      EditKeyBar.Show();
      Show();
      return(TRUE);
    /* SVS $ */
    case KEY_F2:
    case KEY_SHIFTF2:
      {
        static int TextFormat=0;
        int NameChanged=FALSE;
        if (Key==KEY_SHIFTF2)
        {
          const char *HistoryName="NewEdit";
          static struct DialogData EditDlgData[]=
          {
            /* 0 */ DI_DOUBLEBOX,3,1,72,11,0,0,0,0,(char *)MEditTitle,
            /* 1 */ DI_TEXT,5,2,0,0,0,0,DIF_SHOWAMPERSAND,0,(char *)MEditSaveAs,
            /* 2 */ DI_EDIT,5,3,70,3,1,(DWORD)HistoryName,DIF_HISTORY,0,"",
            /* 3 */ DI_TEXT,3,4,0,0,0,0,DIF_BOXCOLOR|DIF_SEPARATOR,0,"",
            /* 4 */ DI_TEXT,5,5,0,0,0,0,0,0,(char *)MEditSaveAsFormatTitle,
            /* 5 */ DI_RADIOBUTTON,5,6,0,0,0,0,DIF_GROUP,0,(char *)MEditSaveOriginal,
            /* 6 */ DI_RADIOBUTTON,5,7,0,0,0,0,0,0,(char *)MEditSaveDOS,
            /* 7 */ DI_RADIOBUTTON,5,8,0,0,0,0,0,0,(char *)MEditSaveUnix,
            /* 8 */ DI_TEXT,3,9,0,0,0,0,DIF_BOXCOLOR|DIF_SEPARATOR,0,"",
            /* 9 */ DI_BUTTON,0,10,0,0,0,0,DIF_CENTERGROUP,1,(char *)MOk,
            /*10 */ DI_BUTTON,0,10,0,0,0,0,DIF_CENTERGROUP,0,(char *)MCancel,
          };
          MakeDialogItems(EditDlgData,EditDlg);
          strcpy(EditDlg[2].Data,FileName);
          EditDlg[5].Selected=EditDlg[6].Selected=EditDlg[7].Selected=0;
          EditDlg[5+TextFormat].Selected=TRUE;
          Dialog Dlg(EditDlg,sizeof(EditDlg)/sizeof(EditDlg[0]));
          Dlg.SetPosition(-1,-1,76,13);
          Dlg.SetHelp("FileSaveAs");
          Dlg.Process();
          if (Dlg.GetExitCode()!=9 || *EditDlg[2].Data==0)
            return(FALSE);
          Unquote(EditDlg[2].Data);
          RemoveTrailingSpaces(EditDlg[2].Data);
          NameChanged=LocalStricmp(EditDlg[2].Data,FileName)!=0;
          strcpy(FileName,EditDlg[2].Data);
//          ConvertNameToFull(FileName,FullFileName, sizeof(FullFileName));
          if (ConvertNameToFull(FileName,FullFileName, sizeof(FullFileName)) >= sizeof(FullFileName)){
            return FALSE;
          }
          if (EditDlg[5].Selected)
            TextFormat=0;
          if (EditDlg[6].Selected)
            TextFormat=1;
          if (EditDlg[7].Selected)
            TextFormat=2;
        }
        ShowConsoleTitle();
        chdir(StartDir);

        if (NameChanged && GetFileAttributes(FileName)!=0xFFFFFFFF)
          if (Message(MSG_WARNING,2,MSG(MEditTitle),FileName,MSG(MEditExists),
                      MSG(MEditOvr),MSG(MYes),MSG(MNo))!=0)
            return(TRUE);

        while (FEdit.SaveFile(FileName,0,Key==KEY_SHIFTF2 ? TextFormat:0,Key==KEY_SHIFTF2)==0)
          if (Message(MSG_WARNING|MSG_ERRORTYPE,2,MSG(MEditTitle),MSG(MEditCannotSave),
                      FileName,MSG(MRetry),MSG(MCancel))!=0)
            break;
      }
      return(TRUE);
    case KEY_F6:
      /* $ 10.05.2001 DJ
         ���������� EnableF6
      */
      if (EnableF6 &&
          (FEdit.IsFileChanged() || GetFileAttributes(FullFileName)!=0xFFFFFFFF))
      {
        long FilePos=FEdit.GetCurPos();
        /* $ 01.02.2001 IS
           ! ��������� ����� � ��������� �������� ����� �����, � �� ���������
        */
        if (ProcessQuitKey())
        {
          /* $ 06.05.2001 DJ
             ��������� F6 ��� NWZ
          */
          /* $ 07.05.2001 DJ
             ��������� NamesList
          */
          FileViewer *Viewer = new FileViewer (FullFileName, GetCanLoseFocus(), FALSE,
            FALSE, FilePos, NULL, EditNamesList);
          /* DJ $ */
          FrameManager->ReplaceFrame (this, Viewer);
          /* DJ $ */
        }
        /* IS $ */
        ShowTime(2);
      }
      /* DJ $ */
      return(TRUE);
    /*$ 21.07.2000 SKV
        + ����� � ����������������� �� ������������� ����� �� CTRLF10
    */
    case KEY_CTRLF10:
      {
        if(GetCanLoseFocus())
        {
          /* $ 01.03.2001 IS
               - ���: �� �����������, �������� �� ���� �� ����� ����
          */
          if(!ProcessQuitKey()) return TRUE;
          /* IS $ */
          if(strchr(FileName,'\\') || strchr(FileName,'/'))
          {
            char DirTmp[NM],ADir[NM],PDir[NM],*NameTmp;
            strncpy(DirTmp,FileName,NM);
            NameTmp=PointToName(DirTmp);
            if(NameTmp>DirTmp)NameTmp[-1]=0;
            CtrlObject->Cp()->GetAnotherPanel(CtrlObject->Cp()->ActivePanel)->GetCurDir(PDir);
            CtrlObject->Cp()->ActivePanel->GetCurDir(ADir);
            /* $ 10.04.2001 IS
                 �� ������ SetCurDir, ���� ������ ���� ��� ���� �� ��������
                 �������, ��� ����� ���������� ����, ��� ��������� � ���������
                 ������� �� ������������.
            */
            BOOL AExist=LocalStricmp(ADir,DirTmp)==0,
                 PExist=LocalStricmp(PDir,DirTmp)==0;
            // ���� ������ ���� ���� �� ��������� ������
            if ( !AExist && PExist)
            {
                CtrlObject->Cp()->ProcessKey(KEY_TAB);
            }
            if(!AExist && !PExist)
                CtrlObject->Cp()->ActivePanel->SetCurDir(DirTmp,TRUE);
            /* IS */
            CtrlObject->Cp()->ActivePanel->GoToFile(NameTmp);
          }else
          {
            CtrlObject->Cp()->ActivePanel->SetCurDir(StartDir,TRUE);
            CtrlObject->Cp()->ActivePanel->GoToFile(FileName);
          }
          /* $ 10.05.2001 DJ
             ������������� � ������
          */
          FrameManager->SwitchToPanels();
          /* DJ $ */
        }
        return (TRUE);
      }
    /* SKV $*/

    case KEY_SHIFTF10:
      ProcessKey(KEY_F2);
    case KEY_ESC:
    case KEY_F10:
      ProcessQuitKey();
      return(TRUE);

    /* $ 27.09.2000 SVS
       ������ �����/����� � �������������� ������� PrintMan
    */
    case KEY_ALTF5:
    {
      if(CtrlObject->Plugins.FindPlugin(SYSID_PRINTMANAGER) != -1)
        CtrlObject->Plugins.CallPlugin(SYSID_PRINTMANAGER,OPEN_EDITOR,0); // printman
      return TRUE;
    }
    /* SVS $*/

    /* $ 19.12.2000 SVS
       ����� ������� �������� (� ������ IS)
    */
    case KEY_ALTSHIFTF9:
      /* $ 26.02.2001 IS
           ������ � ��������� ������ EditorOptions
      */
      struct EditorOptions EdOpt;

      EdOpt.TabSize=FEdit.GetTabSize();
      EdOpt.ExpandTabs=FEdit.GetConvertTabs();
      EdOpt.PersistentBlocks=FEdit.GetPersistentBlocks();
      EdOpt.DelRemovesBlocks=FEdit.GetDelRemovesBlocks();
      EdOpt.AutoIndent=FEdit.GetAutoIndent();
      EdOpt.AutoDetectTable=FEdit.GetAutoDetectTable();
      EdOpt.CursorBeyondEOL=FEdit.GetCursorBeyondEOL();
      EdOpt.CharCodeBase=FEdit.GetCharCodeBase();
      //EdOpt.BSLikeDel=FEdit.GetBSLikeDel();

      EditorConfig(EdOpt);
      EditKeyBar.Show(); //???? ����� ��????

      FEdit.SetTabSize(EdOpt.TabSize);
      FEdit.SetConvertTabs(EdOpt.ExpandTabs);
      FEdit.SetPersistentBlocks(EdOpt.PersistentBlocks);
      FEdit.SetDelRemovesBlocks(EdOpt.DelRemovesBlocks);
      FEdit.SetAutoIndent(EdOpt.AutoIndent);
      FEdit.SetAutoDetectTable(EdOpt.AutoDetectTable);
      FEdit.SetCursorBeyondEOL(EdOpt.CursorBeyondEOL);
      FEdit.SetCharCodeBase(EdOpt.CharCodeBase);
      //FEdit.SetBSLikeDel(EdOpt.BSLikeDel);
      /* IS $ */
      FEdit.Show();
      return TRUE;
    /* SVS $ */

    /* $ 10.05.2001 DJ
       Alt-F11 - �������� view/edit history
    */
    case KEY_ALTF11:
      if (GetCanLoseFocus())
        CtrlObject->CmdLine->ShowViewEditHistory();
      return TRUE;
    /* DJ $ */

    default:
      /* $ 28.04.2001 DJ
         �� �������� KEY_MACRO* ������� - ��������� ReadRec � ���� ������
         ����� �� ������������� �������������� �������, ��������� ������������
         �����
      */
      if(Key&KEY_MACROSPEC_BASE) // ��������� MACRO
         return(FEdit.ProcessKey(Key));
      /* DJ $ */
      if (CtrlObject->Macro.IsExecuting() ||
        !FEdit.ProcessEditorInput(FrameManager->GetLastInputRecord()))
      {
        /* $ 22.03.2001 SVS
           ��� ������� �� ��������� :-)
        */
        if (FullScreen && !CtrlObject->Macro.IsExecuting())
          EditKeyBar.Show();
        /* SVS $ */
        if (!EditKeyBar.ProcessKey(Key))
          return(FEdit.ProcessKey(Key));
      }
      return(TRUE);
  }
}


int FileEditor::ProcessQuitKey()
{
  int FirstSave=1;
  while (1)
  {
    chdir(StartDir);
    int SaveCode=FEdit.SaveFile(FileName,FirstSave,0,FALSE);
    if (SaveCode==2)
      break;
    if (SaveCode==1)
    {
      SetExitCode (XC_QUIT);
      break;
    }
    if (Message(MSG_WARNING|MSG_ERRORTYPE,2,MSG(MEditTitle),MSG(MEditCannotSave),
                FileName,MSG(MRetry),MSG(MCancel))!=0)
      break;
    FirstSave=0;
  }
  return GetExitCode() == XC_QUIT;
}


int FileEditor::ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent)
{
  if (!EditKeyBar.ProcessMouse(MouseEvent))
    if (!FEdit.ProcessEditorInput(FrameManager->GetLastInputRecord()))
      if (!FEdit.ProcessMouse(MouseEvent))
        return(FALSE);
  return(TRUE);
}


int FileEditor::GetTypeAndName(char *Type,char *Name)
{
  if ( Type ) strcpy(Type,MSG(MScreensEdit));
  if ( Name ) strcpy(Name,FullFileName);
  return(MODALTYPE_EDITOR);
}


void FileEditor::ShowConsoleTitle()
{
  char Title[NM+20];
  sprintf(Title,MSG(MInEditor),PointToName(FileName));
  SetFarTitle(Title);
}


/* $ 28.06.2000 tran
 (NT Console resize)
 resize editor */
void FileEditor::SetScreenPosition()
{
  if (FullScreen)
  {
    SetPosition(0,0,ScrX,ScrY);
    Show();
  }
}
/* tran $ */

/* $ 10.05.2001 DJ
   ���������� � view/edit history
*/

void FileEditor::OnDestroy()
{
  if (!DisableHistory)
    CtrlObject->ViewHistory->AddToHistory(FullFileName,MSG(MHistoryEdit),1);
}
