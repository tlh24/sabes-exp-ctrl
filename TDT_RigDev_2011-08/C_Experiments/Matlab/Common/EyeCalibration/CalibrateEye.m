function varargout = CalibrateEye(varargin)
% CALIBRATEEYE M-file for CalibrateEye.fig
%      CALIBRATEEYE, by itself, creates a new CALIBRATEEYE or raises the existing
%      singleton*.
%
%      H = CALIBRATEEYE returns the handle to a new CALIBRATEEYE or the handle to
%      the existing singleton*.
%
%      CALIBRATEEYE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in CALIBRATEEYE.M with the given input arguments.
%
%      CALIBRATEEYE('Property','Value',...) creates a new CALIBRATEEYE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before CalibrateEye_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      btndaqstop.  All inputs are passed to CalibrateEye_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help CalibrateEye

% Last Modified by GUIDE v2.5 18-Nov-2010 09:12:13

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @CalibrateEye_OpeningFcn, ...
                   'gui_OutputFcn',  @CalibrateEye_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before CalibrateEye is made visible.
%=========================================================================
% Setup servers and GUI objects
%=========================================================================
function CalibrateEye_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to CalibrateEye (see VARARGIN)

ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain',strDisplayComputer);
DispCalibMtx = GetDisplayCalibMatrix( );
hVMain.SetTransformMatrix(DispCalibMtx); % set display calibration
hVDisk = actxserver('CP_Display.VDisk',strDisplayComputer);
hVDisk.SetScale(2);  %  MF added, Oct. 20, 2010
hEye=actxserver('CP_EyeTrack.Application', strEyeTrackComputer);
hEye.ConnectTracker();
pause(0.1)

% Set Init state
% hide Calibration panel
set(handles.pnlCalibration,'Visible','off');


% Set application globals
handles.CalibStruct = GetEyeCalibStruct();
handles.strCalibLocation = 'Loaded Calibration file';

% DCOM servers
handles.hVMain = hVMain;
handles.hVDisk = hVDisk;
handles.hEye = hEye;

handles.DaqOnFlag = 0;
handles.CurrTargetIdx = 0;
handles.nGridPoints   = 0;
handles.dMaxDaqTimeSec = 5;  % we keep last N seconds of the Eye data

% Validation flags
handles.ValidationOnFlag = 0;  
handles.GridNewClickFlag = 0;

% handles.EyeDataGrid =   % IScan coordinates corresponding to the grid points   

% Graphics Objects
handles.hCurrentGridPointtPlot = NaN;
handles.hEyeXY_TrajPlot = NaN;
handles.hEyeXY_PointPlot = NaN;
handles.hCalibFitPlot = NaN;

% end of application globals setup
guidata(hObject, handles); % set global data

% Set default values of grid and scales
% Grid
set(handles.txtN_PointsX,'String','4'); 
set(handles.txtN_PointsY,'String','3');

set(handles.txtCenterX,'String','0');
set(handles.txtCenterY,'String','150');
set(handles.txtHalfWidth,'String','90');
set(handles.txtHalfHeight,'String','90');

% Grid scale
set(handles.txtGridAxisXmin,'String','-120');
set(handles.txtGridAxisXmax,'String','120');
set(handles.txtGridAxisYmin,'String','0');
set(handles.txtGridAxisYmax,'String','300');

% Eye XY scale
set(handles.txtEyePosAxisXmin,'String','1800');
set(handles.txtEyePosAxisXmax,'String','3800');
set(handles.txtEyePosAxisYmin,'String','900');
set(handles.txtEyePosAxisYmax,'String','1700');

% Now use the values set above
CalcNewGrid( hObject, handles );
handles=guidata(hObject);  % get global data
UpdateSavedCalibInfo( handles );
SetGridAxes( handles );
SetEyePosAxes( handles );

% All click events will go to the parent - axes
set(get(handles.axEyeXY,'Children'),'HitTest','off');
set(get(handles.axGrid,'Children'),'HitTest','off');

% This disregards Z-order of the objects, but makes drawing faster
set(handles.axEyeXY, 'DrawMode', 'fast');
set(handles.axGrid, 'DrawMode', 'fast');
set(handles.axEyeX, 'DrawMode', 'fast');
set(handles.axEyeY, 'DrawMode', 'fast');

set(handles.btnInvokeCalibration,'Enable','off');

% --- Outputs from this function are returned to the command line.
%=========================================================================
% Not used now
%=========================================================================
function varargout = CalibrateEye_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
% varargout{1} = handles.output;

%  MF Added.  Spit out the handles so other functions can access them.
varargout{1} = handles;

%=========================================================================
% Quit Application - shows confirm dialog
%=========================================================================
function QuitApplication(handles)

user_response = modaldlg('Title','Confirm Quit');
switch lower(user_response)
case 'no'
	% take no action
case 'yes'
	% Set transform to the latest saved file
% 	EyeCalibMatrix = GetEyeCalibMatrix( );
%   hEye.SetTransformMatrix( EyeCalibMatrix );
                  %.
	%                  .
	%                  .
	delete(handles.figMain) % close application
end

%=========================================================================
% Updates info text on the current calibration 
% Current calibration is loaded at the startup
%=========================================================================
function UpdateSavedCalibInfo( handles )

CalibStruct = handles.CalibStruct;
strCalibInfo = sprintf('Description: %s\nCalib. Type: %d\nDate: %s\nSource:  %s\n', ...
                       CalibStruct.strDescription,  CalibStruct.CalibType,...
                       datestr(CalibStruct.DateTime), handles.strCalibLocation );

set(handles.lblCalibrationFileInfo,'String', strCalibInfo);


%=========================================================================
% Updates current target state: Grid plot + text
%=========================================================================
function UpdateCurrentTarget( hObject, handles )

CurrTargetIdx = handles.CurrTargetIdx;
PrevTargetIdx = handles.PrevTargetIdx;


strCurrentTarget = sprintf('Current Target:    %d', CurrTargetIdx);
set(handles.lblCurrentTarget,'String', strCurrentTarget);


%% Get current Grid Point
idx1 = handles.TargetsIdx(CurrTargetIdx,1);
idx2 = handles.TargetsIdx(CurrTargetIdx,2);
X = handles.GridX(idx1,idx2);
Y = handles.GridY(idx1,idx2);
handles.CurrentX = X;
handles.CurrentY = Y;

% delete previous current grid point
if ishandle(handles.hCurrentGridPointtPlot)
  delete(handles.hCurrentGridPointtPlot);
end

% plot current grid point point
axes(handles.axGrid);
hold on;  % add to the existing plot
handles.hCurrentGridPointtPlot(1)=plot(X,Y,'r.');   % central point
handles.hCurrentGridPointtPlot(2)=plot(X,Y,'ro','markersize',10); % outer circle

% greyout previous EyeXY traj and EyeXY point 
if PrevTargetIdx>0 
  if ishandle(handles.hEyeXY_TrajPlot(PrevTargetIdx))
    set(handles.hEyeXY_TrajPlot(PrevTargetIdx),...
        'markersize',3,'markerfac','none','markered',[.6 .6 .6]);
    set(handles.hEyeXY_PointPlot(PrevTargetIdx),...
        'markeredge',[1 .5 .5],'markerfac',[1 .5 .5]);
  end
end

% higlight current EyeXY traj and EyeXY point 
if ishandle(handles.hEyeXY_TrajPlot(CurrTargetIdx))
  set(handles.hEyeXY_TrajPlot(CurrTargetIdx),...
      'markersize',3,'markerfac','none','markered',[0 0 0]);
  set(handles.hEyeXY_PointPlot(CurrTargetIdx),...
      'markeredge',[1 0 0],'markerfac',[1 0 0]);
end

guidata(hObject, handles); % set global data


%=========================================================================
% Updates Count of Acquired points
%=========================================================================
function UpdatePointsCount( handles )

nPointsAcq = sum(~isnan(handles.EyeDataGrid(:,1)));
strPointsAcquired = sprintf('Points Acquired:    %d', nPointsAcq );
set(handles.lblPointsAcquired,'String', strPointsAcquired);

%=========================================================================
% Updates Count of Acquired points
%=========================================================================
function RestoreStateOfShowHide( handles )
set(handles.pnlGridParameters,'Visible','on'); % Show Grid Parameters panel

if( handles.nGridPoints > 0) 
  set(handles.pnlIScanDAQ,'Visible','on'); % Show Daq panel
  set(handles.btnDaqStart,'Visible','on'); % Hide Stop button
  set(handles.btnDaqStop,'Visible','off'); % Hide Stop button
  set(handles.btnNext,'Visible','on'); % Show Next button
  set(handles.btnPrev,'Visible','on'); % Show Prev button
end

%% if collected ALL DataPoints show Calibration panel
if(~any(isnan(handles.EyeDataGrid)))
  set(handles.pnlCalibration,'Visible','on');
end

set(handles.pnlValidation,'Visible','on');
set(handles.btnValidationStop,'Visible','off'); % Hide Stop button
set(handles.btnValidationStart,'Visible','on'); % Show Start button


%=========================================================================
% New Grid button
%=========================================================================
% --- Executes on button press in btnNewGrid.
function btnNewGrid_Callback(hObject, eventdata, handles)
% hObject    handle to btnNewGrid (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

CalcNewGrid( hObject, handles );

%-------------------------------------------------------------------------
function CalcNewGrid( hObject, handles )

nPointsX = str2double(get(handles.txtN_PointsX,'String')); 
nPointsY = str2double(get(handles.txtN_PointsY,'String'));

% Check input values
if(nPointsX<2 || nPointsY<2)
  return
end

CenterX = str2double(get(handles.txtCenterX,'String'));
CenterY = str2double(get(handles.txtCenterY,'String'));

HalfWidth = str2double(get(handles.txtHalfWidth,'String'));
HalfHeight = str2double(get(handles.txtHalfHeight,'String'));

% Clear all graphs
cla(handles.axGrid); 
cla(handles.axEyeXY);
cla(handles.axEyeX);
cla(handles.axEyeY);

% Create grid points indexes
PointIdx=1;
for i=1:nPointsY,
  for j=1:nPointsX,
    TargetsIdx(PointIdx,:) = [j i];
    PointIdx=PointIdx+1;
  end
end

nGridPoints   = (nPointsX*nPointsY);       

handles.nGridPoints   = nGridPoints;
handles.TargetsIdx = TargetsIdx;

% calc grid points positions
stepX = 2*HalfWidth/(nPointsX-1);
stepY = 2*HalfHeight/(nPointsY-1);
[GridX,GridY] = meshgrid(-HalfWidth:stepX:HalfWidth , -HalfHeight:stepY:HalfHeight);

handles.GridX = GridX' + CenterX;
handles.GridY = GridY' + CenterY;

% plot grid points
axes(handles.axGrid); 
hold on;
plot(handles.GridX,handles.GridY,'bo');

handles.CurrTargetIdx = 1;
handles.PrevTargetIdx = 0;

% Reset Stuff
handles.EyeDataGrid = NaN*zeros(nGridPoints,2);
handles.hEyeXY_TrajPlot = NaN*zeros(nGridPoints,1);
handles.hEyeXY_PointPlot = NaN*zeros(nGridPoints,1);
guidata(hObject, handles); % set global data

UpdateCurrentTarget( hObject, handles );
UpdatePointsCount( handles );
RestoreStateOfShowHide( handles );

% all click events will go the parent
set(get(handles.axGrid,'Children'),'HitTest','off'); 
% 

%=========================================================================
% Set (Grid Axes)  button
%=========================================================================
% --- Executes on button press in btnSetGridAxes.
function btnSetGridAxes_Callback(hObject, eventdata, handles)
% hObject    handle to btnSetGridAxes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
SetGridAxes( handles );


function SetGridAxes( handles )

Xmin = str2double(get(handles.txtGridAxisXmin,'String'));
Xmax = str2double(get(handles.txtGridAxisXmax,'String'));
Ymin = str2double(get(handles.txtGridAxisYmin,'String'));
Ymax = str2double(get(handles.txtGridAxisYmax,'String'));
% Set the scale
axis(handles.axGrid, [Xmin Xmax Ymin Ymax]);

%=========================================================================
% Set (Eye Pos Axes)  button
%=========================================================================
% --- Executes on button press in btnSetEyePosAxes.
function btnSetEyePosAxes_Callback(hObject, eventdata, handles)
% hObject    handle to btnSetEyePosAxes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
SetEyePosAxes( handles );


function SetEyePosAxes( handles )

Xmin = str2double(get(handles.txtEyePosAxisXmin,'String'));
Xmax = str2double(get(handles.txtEyePosAxisXmax,'String'));
Ymin = str2double(get(handles.txtEyePosAxisYmin,'String'));
Ymax = str2double(get(handles.txtEyePosAxisYmax,'String'));
% Set the scale
axis(handles.axEyeXY, [Xmin Xmax Ymin Ymax]);

%=========================================================================
% Next Target button
%=========================================================================
% --- Executes on button press in btnNext.
function btnNext_Callback(hObject, eventdata, handles)
% hObject    handle to btnNext (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% Get btnNext Target ID
PrevTargetIdx = handles.CurrTargetIdx;
CurrTargetIdx = PrevTargetIdx + 1;
if( CurrTargetIdx > handles.nGridPoints ) % wrap around
  CurrTargetIdx = 1; 
end
handles.CurrTargetIdx = CurrTargetIdx;
handles.PrevTargetIdx = PrevTargetIdx;

UpdateCurrentTarget( hObject, handles );



%=========================================================================
% Prev Target
%=========================================================================
% --- Executes on button press in btnPrev.
function btnPrev_Callback(hObject, eventdata, handles)
% hObject    handle to btnPrev (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% Get btnNext Target ID
PrevTargetIdx = handles.CurrTargetIdx;
CurrTargetIdx = PrevTargetIdx - 1;
if( CurrTargetIdx < 1 ) % wrap around
  CurrTargetIdx = handles.nGridPoints; 
end
handles.CurrTargetIdx = CurrTargetIdx;
handles.PrevTargetIdx = PrevTargetIdx;

UpdateCurrentTarget( hObject, handles );


%=========================================================================
% Start DAQ button
%=========================================================================
% --- Executes on button press in btnDaqStart.
function btnDaqStart_Callback(hObject, eventdata, handles)
% hObject    handle to btnDaqStart (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% Set DAQ-on state
set(handles.btnDaqStop,'Visible','on'); % Show Stop button
set(handles.btnDaqStart,'Visible','off'); % Hide Start button
set(handles.btnNext,'Visible','off'); % Hide Next button
set(handles.btnPrev,'Visible','off'); % Hide Prev button
set(handles.pnlCalibration,'Visible','off'); % Hide Calibration panel
set(handles.pnlGridParameters,'Visible','off'); % Hide Grid Parameters panel
set(handles.pnlValidation,'Visible','off'); % Hide Validation panel


% clear time graphs of X and Y
cla(handles.axEyeX);  
cla(handles.axEyeY);

CurrTargetIdx = handles.CurrTargetIdx;

% Delete previous plots for this point
if(ishandle(handles.hEyeXY_TrajPlot(CurrTargetIdx)))
  delete(handles.hEyeXY_TrajPlot(CurrTargetIdx));
end

if(ishandle(handles.hEyeXY_PointPlot(CurrTargetIdx)))
  delete(handles.hEyeXY_PointPlot(CurrTargetIdx));
end

% display the disk at the current position
hVDisk = handles.hVDisk;
hVDisk.SetXY([handles.CurrentX handles.CurrentY]);
%hVDisk.SetScale(2);
hVDisk.SetColor([1 0 0]);
hVDisk.Show;

pause(0.1); % give the subject some time


nDaqPointsMax = handles.dMaxDaqTimeSec * 120;  % we assume 120 Hz IScan rate

hEye = handles.hEye;
UnityMtx = ...
  [ 0, 0;
    1, 0;
    0, 1;
    0, 0;
    0, 0;
    0, 0; ];

hEye.SetTransformMatrix(UnityMtx);

StartIdx = hEye.GetDataIndexLatest; 
% Collect first nDaqPoints
nDaqPoints = 20;
if  nDaqPoints > nDaqPointsMax
  nDaqPoints = nDaqPointsMax;
end
iIdx0 = StartIdx - nDaqPoints +1;
[dTime, dXY] = invoke( hEye, 'GetDataBuffered', iIdx0, nDaqPoints );

dTimeStart = dTime(1);
% plot the results and save the handles 
axes(handles.axEyeX);
hTX_plot=plot(dTime,dXY(1, :),'.');
axes(handles.axEyeY);
hTY_plot=plot(dTime,dXY(2,:),'.');
axes(handles.axEyeXY); 
hold on;
hXY_plot=plot(dXY(1,:),dXY(2,:),'.','color','k');
hLastEyeXY_Plot=plot(dXY(1,end),dXY(2,end),'ro','markerface','r'); 
handles.hEyeXY_PointPlot(CurrTargetIdx) = hLastEyeXY_Plot;

% loop until DaqOnFlag is reset in btnDaqStop_Callback()
handles.DaqOnFlag = 1;
guidata(hObject, handles); % set global data
while handles.DaqOnFlag   

  % Collect data
  LastIdx = hEye.GetDataIndexLatest;
  nDaqPoints = LastIdx - StartIdx +1;
  if  nDaqPoints > nDaqPointsMax
    nDaqPoints = nDaqPointsMax;
  end
  iIdx0 = LastIdx - nDaqPoints + 1;
  [dTime, dXY] = invoke( hEye, 'GetDataBuffered', iIdx0, nDaqPoints );
  dTime = (dTime - dTimeStart)*0.001;   % Convert time to seconds relative to the DAQ start
  %% Update Plots
  set(hTX_plot,'Xdata',dTime,'Ydata',dXY(1,:));
  set(hTY_plot,'Xdata',dTime,'Ydata',dXY(2,:));
  set(hXY_plot,'Xdata',dXY(1,:),'Ydata',dXY(2,:));
  set(hLastEyeXY_Plot,'Xdata',dXY(1,end),'Ydata',dXY(2,end));
  set(get(handles.axEyeXY,'Children'),'HitTest','off'); % all clicks will go to the parent

  drawnow;

  pause(.05);  % less than 20Hz update rate, btnStart_Callback() can run during pause
  handles=guidata(hObject);  % get global data (DaqOnFlag)
end

hVDisk.Hide;

% plot acquired point - filled-in disk
axes(handles.axGrid); 
plot(handles.CurrentX, handles.CurrentY,'bo','markerfac','b');

% Save Last EyePos as Data
handles.EyeDataGrid(CurrTargetIdx,:) = dXY(:,end);
handles.hEyeXY_TrajPlot(CurrTargetIdx)   = hXY_plot;

% set(get(handles.axEyeXY,'Children'),'HitTest','off')
%set(h3,'ButtonDownFcn',get(handles.axEyeXY,'ButtonDownFcn'));
%set(h4,'ButtonDownFcn',get(handles.axEyeXY,'ButtonDownFcn'));

guidata(hObject, handles); % set global data
RestoreStateOfShowHide( handles );
UpdatePointsCount( handles );



%=========================================================================
% Stop DAQ button
%=========================================================================
% --- Executes on button press in btnDaqStop.
function btnDaqStop_Callback(hObject, eventdata, handles)
% hObject    handle to btnDaqStop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.DaqOnFlag = 0;  % stop data collection
guidata(hObject, handles); % set global data

%=========================================================================
% Start Validation button
%=========================================================================
% --- Executes on button press in btnValidationStart.
function btnValidationStart_Callback(hObject, eventdata, handles)
% hObject    handle to btnValidationStart (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Set Validation-on state
set(handles.btnValidationStop,'Visible','on'); % Show Stop button
set(handles.btnValidationStart,'Visible','off'); % Hide Start button
set(handles.pnlCalibration,'Visible','off'); % Hide Calibration panel
set(handles.pnlGridParameters,'Visible','off'); % Hide Grid Parameters panel
set(handles.pnlIScanDAQ,'Visible','off'); % Hide Daq panel

% display the disk at the current position
hVDisk = handles.hVDisk;
hVDisk.Hide;
hVDisk.SetXY([0 0]);
%hVDisk.SetScale(2);
hVDisk.SetColor([1 0 0]);

% plot invisible target point
axes(handles.axGrid); 
hold on;
hValidationPoint_Plot = plot( 0, 0, '+', 'Visible', 'off');
set(hValidationPoint_Plot,'markersize',12, 'LineWidth', 2, 'color', [0 0.5 0.5] );

hEye = handles.hEye;
CalibMtx = handles.CalibStruct.CalibMtx;
hEye.SetTransformMatrix( CalibMtx );

% TODO: ????
% set(get(handles.axGrid,'Children'),'HitTest','off');

% loop until DaqOnFlag is reset in btnStart_Callback()
handles.ValidationOnFlag = 1;  
handles.GridNewClickFlag = 0;
guidata(hObject, handles); % set global data

% all click events will go the parent
set(get(handles.axGrid,'Children'),'HitTest','off'); 
hDaqPointsPlot = [];

while handles.ValidationOnFlag   
  if handles.GridNewClickFlag
    hVDisk.SetXY(handles.GridClickXY);
    hVDisk.Show;
    handles.GridNewClickFlag = 0;
    set(hValidationPoint_Plot,'Xdata',handles.GridClickXY(1),'Ydata',handles.GridClickXY(2));
    set(hValidationPoint_Plot,'Visible', 'on');
  end
  
  % Collect data
  nDaqPoints = 20;
  [LastIdx, dTime, dXY] = invoke( hEye, 'GetDataLatest', nDaqPoints );
  if ishandle(hDaqPointsPlot)
    set(hDaqPointsPlot,'Xdata',dXY(1,:),'Ydata',dXY(2,:));
  else
    hDaqPointsPlot = plot(dXY(1,:), dXY(2,:), '.k');
  end
  % all click events will go the parent
  set(get(handles.axGrid,'Children'),'HitTest','off'); 
  drawnow;
  pause(.05);  % less than 20Hz update rate, btnStart_Callback() can run during pause
  handles=guidata(hObject);  % get global data (ValidationOnFlag)
end

hVDisk.Hide;

delete(hValidationPoint_Plot);
delete(hDaqPointsPlot);
RestoreStateOfShowHide( handles );


%=========================================================================
% Stop Validation button
%=========================================================================
% --- Executes on button press in btnValidationStop.
function btnValidationStop_Callback(hObject, eventdata, handles)
% hObject    handle to btnValidationStop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.ValidationOnFlag = 0;  % stop validation
guidata(hObject, handles); % set global data



%=========================================================================
% Calc Calibration button
%=========================================================================
% --- Executes on button press in btnCalcCalibration.
function btnCalcCalibration_Callback(hObject, eventdata, handles)
% hObject    handle to btnCalcCalibration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



%% DEP VARIABLES - Table Coordinates
TB(:,1)=handles.GridX( handles.TargetsIdx(:,1), 1 );
TB(:,2)=handles.GridY( 1, handles.TargetsIdx(:,2) );

%% INDEP VARIABLES - Iscan Coords
EY     = handles.EyeDataGrid;
Npts   = size(EY,1);


CalibType = get(handles.lstCalibrationType,'Value');

switch ( CalibType )
  case {1}
    DATX = [ones(Npts,1), EY];
    DATY = DATX;
  case {2}
    DATX = [ones(Npts,1), EY, EY(:,1).^2, EY(:,1).*EY(:,2), EY(:,2).^2];
    DATY = DATX;
end

%  get regression coefficients
CalibCoeffs = [ (DATX'*DATX)\(DATX'*TB(:,1))  (DATY'*DATY)\(DATY'*TB(:,2)) ];

EYcalib = [DATX*CalibCoeffs(:,1) DATY*CalibCoeffs(:,2)];  %  calibrated data   
dist    = TB - EYcalib;         %  model fit
RMSEcal = sqrt(mean( sum(dist.^2,2) )); % Root Mean Cartesian Distance Error

% Delete previous calibration fit plot if any
if ishandle( handles.hCalibFitPlot )
  delete( handles.hCalibFitPlot );
end
% plot new calibration fit
axes(handles.axGrid);
handles.hCalibFitPlot = plot(EYcalib(:,1),EYcalib(:,2),'ro','markerfac','r','UserData','eyeCal');

strDescription = get(handles.txtCalibrationFileTag,'String');

% Make CalibMtx size 6x2 even when linear approx. is used
CalibMtx = zeros(6,2);
CalibMtx(1:size(CalibCoeffs,1),1:size(CalibCoeffs,2)) = CalibCoeffs;
CalibStruct.CalibMtx = CalibMtx;
CalibStruct.CalibType = CalibType;         
CalibStruct.strDescription = strDescription;
CalibStruct.GridXY = TB;
CalibStruct.DataXY = EY;
CalibStruct.DateTime = now();

handles.CalibStruct = CalibStruct;
handles.strCalibLocation = 'Calculated Calibration file';

set(handles.btnInvokeCalibration,'Enable','off');
guidata(hObject, handles); % set global data
UpdateSavedCalibInfo( handles );


%=========================================================================
% Save Calibration button
%=========================================================================
% --- Executes on button press in btnSaveCalibration.
function btnSaveCalibration_Callback(hObject, eventdata, handles)
% hObject    handle to btnSaveCalibration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

CalibStruct = handles.CalibStruct;
strDescription = get(handles.txtCalibrationFileTag,'String');
CalibStruct.strDescription = strDescription;
SaveEyeCalibStruct( CalibStruct );


handles.CalibStruct = GetEyeCalibStruct();
handles.strCalibLocation = 'Saved Calibration file';

set(handles.btnInvokeCalibration,'Enable','on');
guidata(hObject, handles); % set global data
UpdateSavedCalibInfo( handles );


%=========================================================================
% Invoke Calibration button
%=========================================================================
% --- Executes on button press in btnInvokeCalibration.
function btnInvokeCalibration_Callback(hObject, eventdata, handles)
% hObject    handle to btnInvokeCalibration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

EyeCalibMatrix = GetEyeCalibMatrix( );
hEye = handles.hEye;
hEye.SetTransformMatrix( EyeCalibMatrix );
guidata(hObject, handles);
  
%=========================================================================
% Quit button 
%=========================================================================
% --- Executes on button press in btnQuit.
function btnQuit_Callback(hObject, eventdata, handles)
% hObject    handle to btnQuit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Confirm quitting
QuitApplication(handles);


%=========================================================================
% Window X button 
%=========================================================================
% --- Executes when user attempts to close figMain.
function figMain_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figMain (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Confirm quitting
QuitApplication(handles);


%=========================================================================
% Axis axEyeXY mouse click
%=========================================================================
% --- Executes on mouse press over axes background.
function axEyeXY_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to axEyeXY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

ClickUpDownCoord = get(hObject,'CurrentPoint');
dXY = ClickUpDownCoord(1,1:2);

% no current target?
if handles.CurrTargetIdx < 1
  return
end
% Is DAQ on?
if handles.DaqOnFlag
  return 
end
% do we have the red dot yet?
if ~ishandle(handles.hEyeXY_PointPlot(handles.CurrTargetIdx))
  return
end

% set red dot coordinates to this point
set(handles.hEyeXY_PointPlot(handles.CurrTargetIdx),'Xdata',dXY(1),'Ydata',dXY(2));
drawnow

% assign click coordinates to the EyeData at this grid point
handles.EyeDataGrid(handles.CurrTargetIdx,:) = dXY;
guidata(hObject, handles); % set global data


%=========================================================================
% Axis axGrid mouse click
%=========================================================================
% --- Executes on mouse press over axes background.
function axGrid_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to axGrid (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

ClickUpDownCoord = get(hObject,'CurrentPoint');
dXY = ClickUpDownCoord(1,1:2);

if ~handles.ValidationOnFlag
  return
end

handles.GridClickXY = dXY;
handles.GridNewClickFlag = 1;

guidata(hObject, handles); % set global data


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%






function txtCenterX_Callback(hObject, eventdata, handles)
% hObject    handle to txtCenterX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of txtCenterX as text
%        str2double(get(hObject,'String')) returns contents of txtCenterX as
%        a double

% --- Executes during object creation, after setting all properties.
function txtCenterX_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtCenterX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function txtHalfWidth_Callback(hObject, eventdata, handles)
% hObject    handle to txtHalfWidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of txtHalfWidth as text
%        str2double(get(hObject,'String')) returns contents of txtHalfWidth as a double

% --- Executes during object creation, after setting all properties.
function txtHalfWidth_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtHalfWidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function txtHalfHeight_Callback(hObject, eventdata, handles)
% hObject    handle to txtHalfHeight (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of txtHalfHeight as text
%        str2double(get(hObject,'String')) returns contents of txtHalfHeight as a double

% --- Executes during object creation, after setting all properties.
function txtHalfHeight_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtHalfHeight (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function txtCenterY_Callback(hObject, eventdata, handles)
% hObject    handle to txtCenterY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of txtCenterY as text
%        str2double(get(hObject,'String')) returns contents of txtCenterY as a double

% --- Executes during object creation, after setting all properties.
function txtCenterY_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtCenterY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function txtN_PointsX_Callback(hObject, eventdata, handles)
% hObject    handle to txtN_PointsX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of txtN_PointsX as text
%        str2double(get(hObject,'String')) returns contents of txtN_PointsX as a double

% --- Executes during object creation, after setting all properties.
function txtN_PointsX_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtN_PointsX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function txtN_PointsY_Callback(hObject, eventdata, handles)
% hObject    handle to txtN_PointsY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of txtN_PointsY as text
%        str2double(get(hObject,'String')) returns contents of txtN_PointsY as a double

% --- Executes during object creation, after setting all properties.
function txtN_PointsY_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtN_PointsY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function txtGridAxisYmin_Callback(hObject, eventdata, handles)
% hObject    handle to txtGridAxisYmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtGridAxisYmin as text
%        str2double(get(hObject,'String')) returns contents of txtGridAxisYmin as a double


% --- Executes during object creation, after setting all properties.
function txtGridAxisYmin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtGridAxisYmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtGridAxisYmax_Callback(hObject, eventdata, handles)
% hObject    handle to txtGridAxisYmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtGridAxisYmax as text
%        str2double(get(hObject,'String')) returns contents of txtGridAxisYmax as a double


% --- Executes during object creation, after setting all properties.
function txtGridAxisYmax_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtGridAxisYmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtGridAxisXmin_Callback(hObject, eventdata, handles)
% hObject    handle to txtGridAxisXmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtGridAxisXmin as text
%        str2double(get(hObject,'String')) returns contents of txtGridAxisXmin as a double


% --- Executes during object creation, after setting all properties.
function txtGridAxisXmin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtGridAxisXmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtGridAxisXmax_Callback(hObject, eventdata, handles)
% hObject    handle to txtGridAxisXmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtGridAxisXmax as text
%        str2double(get(hObject,'String')) returns contents of txtGridAxisXmax as a double


% --- Executes during object creation, after setting all properties.
function txtGridAxisXmax_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtGridAxisXmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function txtCalibrationFileTag_Callback(hObject, eventdata, handles)
% hObject    handle to txtCalibrationFileTag (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtCalibrationFileTag as text
%        str2double(get(hObject,'String')) returns contents of txtCalibrationFileTag as a double


% --- Executes during object creation, after setting all properties.
function txtCalibrationFileTag_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtCalibrationFileTag (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end






% --- Executes on selection change in lstCalibrationType.
function lstCalibrationType_Callback(hObject, eventdata, handles)
% hObject    handle to lstCalibrationType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns lstCalibrationType contents as cell array
%        contents{get(hObject,'Value')} returns selected item from lstCalibrationType


% --- Executes during object creation, after setting all properties.
function lstCalibrationType_CreateFcn(hObject, eventdata, handles)
% hObject    handle to lstCalibrationType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




function txtEyePosAxisYmin_Callback(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisYmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtEyePosAxisYmin as text
%        str2double(get(hObject,'String')) returns contents of txtEyePosAxisYmin as a double


% --- Executes during object creation, after setting all properties.
function txtEyePosAxisYmin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisYmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtEyePosAxisYmax_Callback(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisYmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtEyePosAxisYmax as text
%        str2double(get(hObject,'String')) returns contents of txtEyePosAxisYmax as a double


% --- Executes during object creation, after setting all properties.
function txtEyePosAxisYmax_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisYmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtEyePosAxisXmin_Callback(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisXmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtEyePosAxisXmin as text
%        str2double(get(hObject,'String')) returns contents of txtEyePosAxisXmin as a double


% --- Executes during object creation, after setting all properties.
function txtEyePosAxisXmin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisXmin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtEyePosAxisXmax_Callback(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisXmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtEyePosAxisXmax as text
%        str2double(get(hObject,'String')) returns contents of txtEyePosAxisXmax as a double


% --- Executes during object creation, after setting all properties.
function txtEyePosAxisXmax_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtEyePosAxisXmax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




