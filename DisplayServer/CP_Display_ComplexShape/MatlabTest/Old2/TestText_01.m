% strVisServerName = 'VisServer1';
strDisplayComputer = 'localhost';

hVMain = actxserver('CP_Display.VMain'); 
% hVMain.GetVersion

hVText = actxserver('CP_Display.VText');
% hVText.GetText
% hVText.GetFontName
% hVText.GetFontUnderlineFlag
% hVText.GetFontItalicFlag
% hVText.GetFontWeight

% hVText.SetText('!olleH');
% hVText.SetFontName('Courier New');
% hVText.SetFontUnderlineFlag(1);
% hVText.SetFontItalicFlag(1);
% hVText.SetFontWeight(500);

% hVText.GetText
% hVText.GetFontName
% hVText.GetFontUnderlineFlag
% hVText.GetFontItalicFlag
% hVText.GetFontWeight

FontSize = 50;
hVText.SetXY([512 384]);
hVText.SetScale(FontSize);
hVText.SetText('AAAAAAA');
hVText.Show;


hVDisk = actxserver('CP_Display.VDisk', strDisplayComputer); 
hVDisk.SetXY([512,384]);
hVDisk.SetN_Vertices(4);
hVDisk.SetRadius(FontSize*sqrt(2)/2);
hVDisk.SetColor([1 0 1]);
hVDisk.SetFillFlag(0);
hVDisk.Rotate(45);
hVDisk.Show;

% hVText.Rotate(-30);
%hVText.SetFillFlag(1);
%if iscom(hVMain)  release(hVMain); end;
