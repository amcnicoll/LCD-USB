Gui, Font, s10, Tahoma
Gui, Add, Edit, x32 y90 w180 h20 Limit32 vLin1, 
Gui, Add, Edit, x322 y90 w180 h20 Limit32 vLin3, 
Gui, Add, Edit, x32 y130 w180 h20 Limit32 vLin2, 
Gui, Add, Edit, x322 y130 w180 h20 Limit32 vLin4, 
Gui, Font, s16, Tahoma
Gui, Add, Text, x172 y30 w280 h30 +Center +BackgroundTrans, LCD-USB Control Panel
Gui, Font, s10, Tahoma
Gui, Add, Button, x222 y90 w70 h20 , Line A0
Gui, Add, Button, x222 y130 w70 h20 , Line A1
Gui, Add, Button, x512 y90 w70 h20 , Line B0
Gui, Add, Button, x512 y130 w70 h20 , Line B1
Gui, Add, Slider, x322 y180 w180 h30 Range0-255 gFan1Slide vFan1, 20
Gui, Add, Slider, x322 y220 w180 h30 Range0-255 gFan2Slide vFan2, 20
Gui, Add, Slider, x322 y260 w180 h30 Range0-255 gLightSlide vLight, 20
Gui, Add, Button, x32 y180 w260 h30 , Backlight On
Gui, Add, Button, x32 y220 w260 h30 , Backlight Off
Gui, Add, Button, x32 y260 w260 h30 , Clear LCD's
Gui, Add, Text, x512 y180 w90 h30 , Fan 1
Gui, Add, Text, x512 y220 w90 h30 , Fan 2
Gui, Add, Text, x512 y260 w90 h30 , Lights

; Generated using SmartGUI Creator 4.0
Gui, Show, x522 y226 h320 w617, LCD-USB Control Panel
Return

ButtonLineA0:
Gui, Submit, NoHide
StringReplace, Lin1, Lin1, %A_Space%, ~0, 1
Run, usblcd.exe 6 %Lin1%,,Hide
Return

ButtonLineA1:
Gui, Submit, NoHide
StringReplace, Lin2, Lin2, %A_Space%, ~0, 1
Run, usblcd.exe 7 %Lin2%,,Hide
Return

ButtonLineB0:
Gui, Submit, NoHide
StringReplace, Lin3, Lin3, %A_Space%, ~0, 1
Run, usblcd.exe 8 %Lin3%,,Hide
Return

ButtonLineB1:
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

Fan1Slide:
Gui, Submit, NoHide
Run, usblcd.exe 3 %Fan1%,,Hide
Return

Fan2Slide:
Gui, Submit, NoHide
Run, usblcd.exe 4 %Fan2%,,Hide
Return

LightSlide:
Gui, Submit, NoHide
Run, usblcd.exe 5 %Light%,,Hide
Return

GuiClose:
ExitApp