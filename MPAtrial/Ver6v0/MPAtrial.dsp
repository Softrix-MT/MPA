# Microsoft Developer Studio Project File - Name="MPAtrial" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MPAtrial - Win32 Release
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "MPAtrial.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "MPAtrial.mak" CFG="MPAtrial - Win32 Release"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "MPAtrial - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "MPAtrial - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../Support"
# PROP Intermediate_Dir "../Object"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../Support" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x411
# ADD RSC /l 0x411
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../Support\MPAtri06x86.lib"

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../Support"
# PROP Intermediate_Dir "../Object"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "../../Support" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x411
# ADD RSC /l 0x411
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../Support\MPAtri06x86d.lib"

!ENDIF 

# Begin Target

# Name "MPAtrial - Win32 Release"
# Name "MPAtrial - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "IA32 Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCE\IA32\MPAadd32.asm

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAadd32.asm
InputName=MPAadd32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAadd32.asm
InputName=MPAadd32

"$(IntDir)\$(InputName)d.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Zi /Fo"$(IntDir)\$(InputName)d.obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA32\MPAdiv32.asm

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAdiv32.asm
InputName=MPAdiv32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAdiv32.asm
InputName=MPAdiv32

"$(IntDir)\$(InputName)d.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Zi /Fo"$(IntDir)\$(InputName)d.obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA32\MPAmul32.asm

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAmul32.asm
InputName=MPAmul32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAmul32.asm
InputName=MPAmul32

"$(IntDir)\$(InputName)d.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Zi /Fo"$(IntDir)\$(InputName)d.obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA32\MPAopr32.asm

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAopr32.asm
InputName=MPAopr32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAopr32.asm
InputName=MPAopr32

"$(IntDir)\$(InputName)d.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Zi /Fo"$(IntDir)\$(InputName)d.obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA32\MPAshl32.asm

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAshl32.asm
InputName=MPAshl32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAshl32.asm
InputName=MPAshl32

"$(IntDir)\$(InputName)d.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Zi /Fo"$(IntDir)\$(InputName)d.obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA32\MPAshr32.asm

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAshr32.asm
InputName=MPAshr32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAshr32.asm
InputName=MPAshr32

"$(IntDir)\$(InputName)d.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Zi /Fo"$(IntDir)\$(InputName)d.obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA32\MPAsub32.asm

!IF  "$(CFG)" == "MPAtrial - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAsub32.asm
InputName=MPAsub32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Fo"$(IntDir)\$(InputName).obj" "$(InputPath)"

# End Custom Build

!ELSEIF  "$(CFG)" == "MPAtrial - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=.\../Object
InputPath=..\SOURCE\IA32\MPAsub32.asm
InputName=MPAsub32

"$(IntDir)\$(InputName)d.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /coff /Cx /Zi /Fo"$(IntDir)\$(InputName)d.obj" "$(InputPath)"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "IA64 Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\SOURCE\IA64\MPAadd64.asm
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA64\MPAdiv64.asm
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA64\MPAmul64.asm
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA64\MPAopr64.asm
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA64\MPAshl64.asm
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA64\MPAshr64.asm
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\SOURCE\IA64\MPAsub64.asm
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=..\SOURCE\CharValue.cpp
# End Source File
# Begin Source File

SOURCE=..\SOURCE\DivExact.cpp
# End Source File
# Begin Source File

SOURCE=..\SOURCE\GirderLimit.cpp
# End Source File
# Begin Source File

SOURCE=..\SOURCE\Support.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Group "Global Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Support\MPAtrial.h
# End Source File
# End Group
# Begin Group "Local Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\INCLUDE\MPA.inc
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\StdHead.h
# End Source File
# End Group
# End Group
# End Target
# End Project
