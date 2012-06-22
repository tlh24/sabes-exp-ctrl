function varargout = MonkeyEyeOctagon(varargin)
% MONKEYEYEOCTAGON M-file for MonkeyEyeOctagon.fig
%      MONKEYEYEOCTAGON, by itself, creates a new MONKEYEYEOCTAGON or raises the existing
%      singleton*.
%
%      H = MONKEYEYEOCTAGON returns the handle to a new MONKEYEYEOCTAGON or the handle to
%      the existing singleton*.
%
%      MONKEYEYEOCTAGON('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MONKEYEYEOCTAGON.M with the given input arguments.
%
%      MONKEYEYEOCTAGON('Property','Value',...) creates a new MONKEYEYEOCTAGON or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before MonkeyEyeOctagon_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to MonkeyEyeOctagon_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Copyright 2002-2003 The MathWorks, Inc.

% Edit the above text to modify the response to help MonkeyEye

% Last Modified by GUIDE v2.5 16-Dec-2004 19:00:09

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @MonkeyEyeOctagon_OpeningFcn, ...
                   'gui_OutputFcn',  @MonkeyEyeOctagon_OutputFcn, ...
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


% --- Executes just before MonkeyEyeOctagon is made visible.
function MonkeyEyeOctagon_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to MonkeyEyeOctagon (see VARARGIN)

fprintf(1,'\n IScan Calibration Routine \n')

% Check Vis Server status
if (isfield(handles,'hW')), % Don't do anything
    fprintf(1,'VisServer Up and Running \n')
else % Start up Visserver
    fprintf(1,'Start Up VisServer...\n')
    hW=actxserver('visserver.viswindow');pause(.1);
    hD=actxserver('visserver.visdisk');
    hD.color = [1 0 0];

    handles.hW = hW;
    handles.hD = hD;
end

handles.stop = 1;    % Flag for state of collecting data

% Clear Axes
cla(handles.axes1); % Liberty frame
cla(handles.axes2); % IScan frame - Horizontal vs Time
cla(handles.axes3); % IScan frame - Vertical vs Time
cla(handles.axes4); % IScan frame - V vs H

% Choose default command line output for MonkeyEyeOctagon
handles.output = hObject;

% Run plotgrid for default grid
PlotGrid_Callback(hObject,[],handles);
handles = guidata(hObject);  % reload since changed in PlotGrid

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes MonkeyEyeOctagon wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = MonkeyEyeOctagon_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



%=========================================================================
% PLOT GRID
%=========================================================================
% --- Executes on button press in PlotGrid.
function PlotGrid_Callback(hObject, eventdata, handles)
% hObject    handle to PlotGrid (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if(~handles.stop) return; end

cla(handles.axes1);
cla(handles.axes4);

handles.currentTarg = 0;

X0  = str2double(get(handles.X0_input,'String'));
Y0  = str2double(get(handles.Y0_input,'String'));
L   = str2double(get(handles.L_input,'String'));
Npt = str2double(get(handles.Npt_input,'String')); 


nVert = Npt;
center = [X0 Y0];
p = zeros(nVert+1,2);
for i = 1:nVert,
    theta = (2*pi/nVert)*(i-1);
    p(i,:)  = center + L*[cos(theta-(pi/2)) sin(theta-(pi/2))];
end

% Add center
p(nVert+1,:) = [X0 Y0];

Totpt   = Npt + 1;       

handles.Total_pts   = Totpt;
%handles.TargetsGrid = p(randperm(Totpt),:);
handles.TargetsGrid = p(1:Totpt,:);

handles.GridX = p(:,1);
handles.GridY = p(:,2);

handles.Xmin = -150;
handles.Xmax = 150;
handles.Ymin = -100;
handles.Ymax = 100;

axes(handles.axes1); hold on;
for i=1:Totpt,
    h=plot(handles.GridX(i),handles.GridY(i),'bo');
    set(h,'UserData',['Targ',num2str(i)]);
end
axis([handles.Xmin handles.Xmax handles.Ymin handles.Ymax]);

% grid off
set(get(handles.axes1,'Children'),'HitTest','off');

% Reset Calibrate to "Grayed Out"
set(handles.Calibrate,'BackgroundColor',.6275*[1 1 1]);

% Start loop through targets
handles.currentTarg = 0;

% Reset Stuff
handles.DataGrid = NaN*zeros(Totpt,2);;
handles.hEyeTraj = NaN*zeros(Totpt,1);
handles.hEyeData = NaN*zeros(Totpt,1);
handles.calibrated = 0;
set(handles.calibratedText,'Visible','off');
set(handles.ValidationTest,'Visible','off');

% update handles structure
guidata(hObject, handles);

fprintf(1,'\nTotal number of targets = %d\n',Totpt)
fprintf(1,'Press Next button to plot each target. \n')
Next_Callback(hObject, eventdata, handles); % Start with 1st target


%=========================================================================
% NEXT TARGET
%=========================================================================
% --- Executes on button press in Next.
function Next_Callback(hObject, eventdata, handles)
% hObject    handle to Next (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if(~handles.stop) return; end

%% Get Next Target ID
last   = handles.currentTarg;
next   = last + 1;
if( next>handles.Total_pts ) next=1; end
handles.currentTarg = next;
set(handles.currentTargText,'String',num2str(next));

%% Get Next Grid Point
X = handles.GridX(next);
Y = handles.GridY(next);
handles.currentX = X;
handles.currentY = Y;

%% Plot Current Target Marker
axes(handles.axes1);
deleteKids(handles.axes1,'current');
h=[plot(X,Y,'r.'),plot(X,Y,'ro')];
set(h(2),'markersize',10);
set(h,'UserData','current','HitTest','off');

% GrayOut previous targets EyeData
if(last>0 & ishandle(handles.hEyeTraj(last)))
    set(handles.hEyeTraj(last),...
        'markersize',3,'markerfac','none','markered',[.6 .6 .6]);
    set(handles.hEyeData(last),...
        'markeredge',[1 .5 .5],'markerfac',[1 .5 .5]);
end

% SAVE
guidata(hObject, handles); % update handles structure


%=========================================================================
% ISCAN ACQUISITION ON/OFF
%=========================================================================

% START --- Executes on button press in Start.
function Start_Callback(hObject, eventdata, handles)
% hObject    handle to Start (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

cla(handles.axes2);
cla(handles.axes3);

curr = handles.currentTarg;

% Delete Old Data
if(ishandle(handles.hEyeTraj(curr)))
    delete(handles.hEyeTraj(curr));
    delete(handles.hEyeData(curr));
end

handles.hD.pos   = [handles.currentX handles.currentY];
handles.hD.color = [1 0 0];
handles.hD.show  = 1;


BlinkDT   = .1;
UpdateDT  = .2;

EyeOpen;  % will move
EyeStart; 
handles.stop=0;

guidata(hObject, handles); % update handles structure
tic; 
targ_on=1;  update_ct=0;
while ~handles.stop,
    %% Blink Object
    if( rem( ceil(toc/BlinkDT),2) ~= targ_on ),
        targ_on=~targ_on;
        handles.hD.show=targ_on;
    end
    
    %% Update Plots
    if( floor(toc/UpdateDT) > update_ct ),
        update_ct=update_ct+1;
        [t,e] = EyeBuffer;  %% Get Buffer Data
        if(update_ct==1) % First Time Draw
            axes(handles.axes2)
            h1=plot(t,e(:,1),'-.');
            axes(handles.axes3)
            h2=plot(t,e(:,2),'-.');
            axes(handles.axes4); hold on;
            h3=plot(e(:,1),e(:,2),'.');      set(h3,'color','k');
            h4=plot(e(end,1),e(end,2),'ro'); set(h4,'markerfac','r');
            
%%% HERE!!!!            
            axis([2100 3100 1000 1600]);
            
            
        else             % Otherwise Update
            set(h1,'Xdata',t,'Ydata',e(:,1));
            drawnow
            set(h2,'Xdata',t,'Ydata',e(:,2));
            drawnow
            set(h3,'Xdata',e(:,1),'Ydata',e(:,2));
            drawnow
            set(h4,'Xdata',e(end,1),'Ydata',e(end,2));
        end
    end

%    drawnow  % Gives Stop_Callback time to edge in
    pause(.07);
    handles=guidata(hObject);
end

% Cleanup
[t,e,eR,err]=EyeStop;
EyeClose  % Move???
handles.hD.show=0;

% Save Last EyePos as Data
handles.DataGrid(curr,:) = e(end,:);
handles.err(curr)        = err;
handles.hEyeTraj(curr)   = h3;
handles.hEyeData(curr)   = h4;
h=findKids(handles.axes1,['Targ',num2str(curr)]);
set(h,'markerfac','b');

set(get(handles.axes4,'Children'),'HitTest','off')
%set(h3,'ButtonDownFcn',get(handles.axes4,'ButtonDownFcn'));
%set(h4,'ButtonDownFcn',get(handles.axes4,'ButtonDownFcn'));

%% After Collecting All DataPoints, Highlight Calibrate Button
if(~any(isnan(handles.DataGrid)))
    set(handles.Calibrate,'BackgroundColor',[255 128 64]/255);
end

guidata(hObject, handles); % update handles structure



% STOP --- Executes on button press in Stop.
function Stop_Callback(hObject, eventdata, handles)
% hObject    handle to Stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.stop=1;
guidata(hObject, handles); % update handles structure



%=========================================================================
% CALIBRATION
%=========================================================================
% --- Executes on button press in Calibrate.
function Calibrate_Callback(hObject, eventdata, handles)
% hObject    handle to Calibrate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


%% DEP VARIABLES - Table Coordinates
%%%TB(:,1)=handles.GridX( handles.TargetsGrid(:,1), 1 );
%%%TB(:,2)=handles.GridY( 1, handles.TargetsGrid(:,2) );
TB(:,1)=handles.GridX;
TB(:,2)=handles.GridY;

%% INDEP VARIABLES - Iscan Coords
EY     = handles.DataGrid;
Npts   = size(EY,1);

switch (get(handles.calibrationType,'Value'))
    case {1}
        DATX = [ones(Npts,1), EY(:,1)];
        DATY = [ones(Npts,1), EY(:,2)];
    case {2}
        DATX = [ones(Npts,1), EY];
        DATY = DATX;
    case {3}
        DATX = [ones(Npts,1), EY, EY(:,1).^2, EY(:,1).*EY(:,2), EY(:,2).^2];
        DATY = DATX;
end

%%  get regression coeffiecients
regCoef = [ (DATX'*DATX)\(DATX'*TB(:,1))  (DATY'*DATY)\(DATY'*TB(:,2)) ];
EYcalib = [DATX*regCoef(:,1) DATY*regCoef(:,2)];              %%  calibrated data   
dist    = TB - EYcalib;         %%  model fit
RMSEcal = sqrt(mean( sum(dist.^2,2) )); %% Root Mean Cartesian Distance Error


axes(handles.axes1);
deleteKids(handles.axes1,'eyeCal');
set(plot(EYcalib(:,1),EYcalib(:,2),'ro'),'markerfac','r','UserData','eyeCal');


eyeCalibration.dataTable     = TB;
eyeCalibration.dataEyes      = EY;
eyeCalibration.dataEyesCalib = EYcalib;
eyeCalibration.calibCoef     = regCoef;
eyeCalibration.calibType     = get(handles.calibrationType,'Value');

temp = cd;
cd ..
cd MonkeyEyeCalib
eval(sprintf('save %s eyeCalibration',handles.calFilename));
cd(temp);

handles.dataTable     = TB;
handles.dataEyesCalib = EYcalib;
handles.calibCoef     = regCoef;
handles.calibrated    = 1;
set(handles.calibratedText,'Visible','on')
set(handles.ValidationTest,'Visible','on')

guidata(hObject, handles); % update handles structure


%%%%%%%%% CALIBRATION TYPE
% --- Executes on selection change in calibrationType.
function calibrationType_Callback(hObject, eventdata, handles)
% hObject    handle to calibrationType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns calibrationType contents as cell array
%        contents{get(hObject,'Value')} returns selected item from calibrationType

% If you reset type, then recalibrate
if(handles.calibrated)
    Calibrate_Callback(handles.Calibrate, eventdata, handles)
end

% --- Executes during object creation, after setting all properties.
function calibrationType_CreateFcn(hObject, eventdata, handles)
% hObject    handle to calibrationType (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
set(hObject, 'String', {'1st Order (Diagonal)', '1st Order', '2nd Order'})



%%%%%%%%% CALIBRATION FILENAME
function Filename_Callback(hObject, eventdata, handles)
% hObject    handle to Filename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of Filename as text
%        str2double(get(hObject,'String')) returns contents of Filename as a double

str = get(hObject,'String');
handles.calFilename = [str,'_EyeCal.mat'];
fprintf(1,'\n Calibration Datafile: %s \n',handles.calFilename)

if(~isfield(handles,'calFilename'))
    set(handles.LoadCalibration,'ForegroundColor',.3*[1 1 1],'BackgroundColor',.6*[1 1 1]);
else
    set(handles.LoadCalibration,'ForegroundColor',[0 0 0],'BackgroundColor',[1 1 1]);
end
guidata(hObject,handles);

% --- Executes during object creation, after setting all properties.
function Filename_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Filename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.

set(hObject,'String','');
handles.calFilename = '_EyeCal.mat';

%%%%%%%%% LOADING EXISTING CALIBRATIONS
% --- Executes during object creation, after setting all properties.
function LoadCalibration_CreateFcn(hObject, eventdata, handles)
% hObject    handle to LoadCalibration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

if(~isfield(handles,'calFilename'))
    set(hObject,'ForegroundColor',.3*[1 1 1],'BackgroundColor',.6*[1 1 1]);
else
    set(hObject,'ForegroundColor',[0 0 0],'BackgroundColor',[1 1 1]);
end

% --- Executes on button press in LoadCalibration.
function LoadCalibration_Callback(hObject, eventdata, handles)
% hObject    handle to LoadCalibration (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if(~isfield(handles,'calFilename'))
    set(hObject,'ForegroundColor',.3*[1 1 1],'BackgroundColor',.6*[1 1 1]);
    return
end

load(handles.calFilename);
handles.dataEyesCalib = eyeCalibration.dataEyesCalib;
handles.calibCoef     = eyeCalibration.calibCoef;
handles.calibrated    = 1;

axes(handles.axes1);
deleteKids(handles.axes1,'eyeCal');
h = plot(handles.dataEyesCalib(:,1),handles.dataEyesCalib(:,2),'ro');
set(h,'markerfac','r','UserData','eyeCal');

set(handles.calibratedText,'Visible','on')
set(handles.ValidationTest,'Visible','on')

fprintf(1,'\n Calibration Datafile %s loaded \n',handles.calFilename)
guidata(hObject, handles); % update handles structure

%=========================================================================
% VALIDATION TEST
%=========================================================================
% --- Executes on button press in ValidationTest.
function ValidationTest_Callback(hObject, eventdata, handles)
% hObject    handle to ValidationTest (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


deleteKids(handles.axes1,'Val');
deleteKids(handles.axes4,'Val');

for i=1:handles.Total_pts,
    if(ishandle(handles.hEyeTraj(i))) delete( handles.hEyeTraj(i) ); end
end

fprintf(1,'Test calibration results...\n')
fprintf(1,'Sample a point on the Grid  \n')

handles.hD.color = [1 0 0];
BlinkDT   = .1;
UpdateDT  = .2;
TestDT    = 5;
button    = 0;
targ_on   = 1;
update_ct = 0;

EyeOpen;
EyeStart;

axes(handles.axes1);
[x, y, button] = ginput(1); % Select point with mouse
handles.hD.pos=[x y];
set(plot(x,y,'b*'),'UserData','Val'); % Plot selected point

tic;
while (toc < TestDT)  %%      
    if ( rem (ceil(toc/BlinkDT), 2) ~= targ_on),  % Blink target
        targ_on =~targ_on;
        handles.hD.show=targ_on;
    end
    if ( floor (toc/UpdateDT) > update_ct ), 
        update_ct  = update_ct + 1;
        e = EyeUpdate; % Get Eye Data
        axes(handles.axes4); hold on;
        h1=plot(e(1),e(2),'r+');             % Plot IScan data
        set(h1,'UserData','Val');
        drawnow
        Npts = 1;
        switch (get(handles.calibrationType,'Value'))
            case {1}
                DATX = [ones(Npts,1), e(1)];
                DATY = [ones(Npts,1), e(2)];
            case {2}
                DATX = [ones(Npts,1), e];
                DATY = DATX;
            case {3}
                DATX = [ones(Npts,1), e, e(1)^2, e(1)*e(2), e(2)^2];
                DATY = DATX;
        end
        EYcalib = [DATX*handles.calibCoef(:,1) DATY*handles.calibCoef(:,2)];    %%  calibrated data   
        axes(handles.axes1);
        h2=plot(EYcalib(1),EYcalib(2),'rs');
        set(h2,'markerface','r','markersiz',4,'UserData','Val');
        drawnow
    end
    pause(UpdateDT/3);
end

handles.hD.show = 0;
EyeStop;
EyeClose;


%=========================================================================
% VISSERVER START/STOP
%=========================================================================
% --- Executes on button press in StartVisServer.
function StartVisServer_Callback(hObject, eventdata, handles)
% hObject    handle to StartVisServer (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% Check Vis Server status
if (isfield(handles,'hW')&~isempty(handles.hW)), % Don't do anything
    fprintf(1,'VisServer Already Up and Running \n')
    % Get the current position of the GUI from the handles structure
    % to pass to the modal dialog.
    pos_size = get(handles.figure1,'Position');
    % Call modaldlg with the argument 'Position'.
    user_response = checkVisServer('Title','VisServer Status');
else % Start up Visserver
    fprintf(1,'Start Up VisServer...\n')
    hW=actxserver('visserver.viswindow');pause(.1);
    hD=actxserver('visserver.visdisk');
    hD.color = [1 0 0];
    hD.radius = 5;
    handles.hW = hW;
    handles.hD = hD;
end
guidata(hObject, handles); % update handles structure

% STOP --- Executes on button press in StopVisServer.
function StopVisServer_Callback(hObject, eventdata, handles)
% hObject    handle to StopVisServer (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

delete(handles.hD)
delete(handles.hW); handles.hW=[];

guidata(hObject, handles); % update handles structure


%=========================================================================
% Other functions 
%=========================================================================
% --- Executes on mouse press over axes background.
function axes4_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to axes4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


p=get(hObject,'CurrentPoint');

handles.DataGrid(handles.currentTarg,:) = p(1,1:2);

if(ishandle(handles.hEyeData(handles.currentTarg)))
    set(handles.hEyeData(handles.currentTarg),'Xdata',p(1,1),'Ydata',p(1,2))
else
    h=plot(p(1),p(2),'ro'); set(h,'markerfac','r');
    handles.hEyeData(handles.currentTarg)=h;
end
drawnow
guidata(hObject, handles); % update handles structure


% --- Grid parameters
function X0_input_Callback(hObject, eventdata, handles)
% hObject    handle to X0_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of X0_input as text
%        str2double(get(hObject,'String')) returns contents of X0_input as
%        a double

% --- Executes during object creation, after setting all properties.
function X0_input_CreateFcn(hObject, eventdata, handles)
% hObject    handle to X0_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function Y0_input_Callback(hObject, eventdata, handles)
% hObject    handle to Y0_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of Y0_input as text
%        str2double(get(hObject,'String')) returns contents of Y0_input as a double

% --- Executes during object creation, after setting all properties.
function Y0_input_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Y0_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function L_input_Callback(hObject, eventdata, handles)
% hObject    handle to Xwid_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of Xwid_input as text
%        str2double(get(hObject,'String')) returns contents of Xwid_input as a double

% --- Executes during object creation, after setting all properties.
function L_input_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Xwid_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function Npt_input_Callback(hObject, eventdata, handles)
% hObject    handle to Xpt_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hints: get(hObject,'String') returns contents of Xpt_input as text
%        str2double(get(hObject,'String')) returns contents of Xpt_input as a double

% --- Executes during object creation, after setting all properties.
function Npt_input_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Xpt_input (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if(isobject(handles.hD)) delete(handles.hD); end
if(isobject(handles.hW)) delete(handles.hW); end

% Hint: delete(hObject) closes the figure
delete(hObject);


%%%%%%%%%%%% HELPERS
function deleteKids(hObject,userdat)
%% Delete all kids of hObject that have userdata=userdat
delete(findKids(hObject,userdat));

%%%%%%%%%%%% HELPERS
function hout=findKids(hObject,userdat)
%% Return handles to all kids of hObject that have userdata=userdat
hout=[];
for h=get(hObject,'Children')',
    ud=get(h,'UserData');
    if( ~isempty(ud) & strcmp(ud,userdat) )
        hout(end+1) = h;
    end
end

