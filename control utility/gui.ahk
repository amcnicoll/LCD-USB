Gui, Font, s10, Tahoma
Gui, Add, Edit, x32 y90 w180 h20 Limit32 vLin1, 
Gui, Add, Edit, x322 y90 w180 h20 Limit32 vLin3, 
Gui, Add, Edit, x32 y130 w180 h20 Limit32 vLin2, 
Gui, Add, Edit, x322 y130 w180 h20 Limit32 vLin4, 
Gui, Font, s16, Tahoma
Gui, Add, Text, x172 y30 w280 h30 +Center +BackgroundTrans, LCD-USB Control Panel
Gui, Font, s10, Tahoma
Gui, Add, Button, x222 y90 w70 h20 , Line 1A
Gui, Add, Button, x222 y130 w70 h20 , Line 2A
Gui, Add, Button, x512 y90 w70 h20 , Line 1B
Gui, Add, Button, x512 y130 w70 h20 , Line 2B
Gui, Add, Slider, x322 y180 w180 h30 , 25
Gui, Add, Slider, x322 y220 w180 h30 , 25
Gui, Add, Slider, x322 y260 w180 h30 , 25
Gui, Add, Button, x32 y180 w260 h30 , Backlight On
Gui, Add, Button, x32 y220 w260 h30 , Backlight Off
Gui, Add, Button, x32 y260 w260 h30 , Clear LCD's
Gui, Add, Text, x512 y180 w90 h30 , Fan 1
Gui, Add, Text, x512 y220 w90 h30 , Fan 2
Gui, Add, Text, x512 y260 w90 h30 , Lights

; Generated using SmartGUI Creator 4.0
Gui, Show, x522 y226 h320 w617, LCD-USB Control Panel
Return

ButtonLine1A:
Gui, Submit, NoHide
StringReplace, Lin1, Lin1, %A_Space%, ~0, 1
Run, usblcd.exe 6 %Lin1%,,Hide
Return

ButtonLine2A:
Gui, Submit, NoHide
StringReplace, Lin2, Lin2, %A_Space%, ~0, 1
Run, usblcd.exe 7 %Lin2%,,Hide
Return

ButtonLine1B:
Gui, Submit, NoHide
StringReplace, Lin3, Lin3, %A_Space%, ~0, 1
Run, usblcd.exe 8 %Lin3%,,Hide
Return

ButtonLine2B:
Gui, Submit, NoHide
StringReplace, Lin4, Lin4, %A_Space%, ~0, 1
Run, usblcd.exe 9 %Lin4%,,Hide
Return

ButtonBacklightOn:
Run, usblcd.exe 1,,Hide
Return

ButtonBacklightOff:
Run, usblcd.exe 0,,Hide
Return

ButtonClearLCD's:
Run, usblcd.exe 2,,Hide
Return

GuiClose:
ExitApp