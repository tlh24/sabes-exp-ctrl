function varargout = Monkey_getMorphometrics(action,varargin)
%
%
%
%
%  MF June 30, 2008.
%

global hW hL optionTrgObjS hText1 hText2 otherObjS
global hCursor hCursorRing
global Params O
global outStruct

if nargin == 0
  action = 'run';
end

if isequal(lower(action), 'run')
  Monkey_getMorphometrics('init',varargin{:});
end

if ~(iscom(hW) & iscom(hL) & ~isempty(optionTrgObjS)) & ~(strncmpi(lower(action), 'setup',5) | isequal(lower(action), 'init'))
  Monkey_getMorphometrics('setup on');
end


switch lower(action)

  case 'init'

    Params = SensIntReaching_Params(0);

    DEFAULTS.defaultCountDownDuration = 10;
    DEFAULTS.marker = 1;
    DEFAULTS.name = 'Dmitri';
    fnd = fieldnames(DEFAULTS);
    vi = 1;
    while vi < length(varargin)
      if ~ischar(varargin{vi})
        fprintf('Skipping non-string input arg\n');
        vi = vi + 1;
      else
        idx = strmatch(varargin{vi},fnd);
        if ~isempty(idx)
          if length(idx) > 1, error('Too many matches'); end
          DEFAULTS.(fnd{idx}) = varargin{vi+1};
          vi = vi + 2;
        else
          fprintf('Uknown arg: \t%s.\nSkipping.\n',varargin{vi});
          vi = vi + 1;
        end
      end
    end
    O = DEFAULTS;
    clear DEFAULTS;

    O.outputdir = fullfile(ExperimentGetDataDir,'MattF',O.name,'');

    optionsList = [     ...
      {'L. Eye'};       ...
      {'C. Eye'};       ...
      {'R. Eye'};       ...
      {'R. Shldr'};     ...
      {'Mirror'};       ...
      {'Table'};        ...
      {'Filter'};       ...
      {'Cancel'};       ...
      {'Done'};         ...
      ];
    [optionsInfo(1:length(optionsList)).Color] = deal([0 1 0]);
    optionsInfo(end-1).Color = [1 0 0];
    optionsInfo(end).Color = [1 1 0];

    O.optionsInfo = optionsInfo;
    O.optionsList = optionsList;

    fprintf('\n\nCapturing Data for: %s\n\n\n',upper(O.name));

    return

  case 'capture'

    activeTrgs = varargin{1};
    pause(0.5);  %

    hCursor.Show;
    hCursorRing.Show;

    Ntrgs = length(activeTrgs); %eval(sprintf('length(%s);',activeTrgs));
    lockOk = 1;
    done = 0;
    while ~done

      [handxy,handvel] = TrialGetKin(hL,O.marker,5);
      pos = handxy(end,:);

      posOk = 0;
      for ti = 1:Ntrgs
        tL = activeTrgs(ti).trgLoc; %eval(sprintf('%s(ti).trgLoc;',activeTrgs));
        tR = activeTrgs(ti).trgRad; %eval(sprintf('%s(ti).trgRad;',activeTrgs));
        posOk = max(posOk,ti.*TrialInBox(pos,tL,tR));
      end

      hCursor.SetXY(pos);
      hCursorRing.SetXY(pos);

      if posOk
        if ~lockOk
          %  If cursor is in a target when this is called then assume it's a spurious capture.
          %  Wait until the cursor is outside of all active targets before responding to a
          %  capture.
          ToneStart(850,0.1);
          done = 1;
        else
          ToneStart(300,1);  %  Warning tone.
        end
      else
        %  if ~posOk then we are not in any active targets.  Turn off the
        %  lock and allow for capture.
        lockOk = 0;
        ToneStart(0,0);  %  Turn off warning tone.
      end

    end
    hCursor.Hide;
    hCursorRing.Hide;

    varargout = {posOk};

    return

  case 'run'

    % O = Monkey_getMorphometrics('init');


    done = 0;
    while ~done
      hW.HideGroup(0);
      hW.ShowGroup(1);

      capturedTrg = Monkey_getMorphometrics('capture',optionTrgObjS);

      if capturedTrg
        done = Monkey_getMorphometrics('doOption',capturedTrg);
      else
        error('huh?');
      end

    end
    Monkey_getMorphometrics('setup off');

    return

  case 'docountdown'

    if length(varargin)
      cd = varargin{1};
    else
      cd = O.defaultCountDownDuration;
    end

    hW.StartBatchDraw;
    hText2.SetXY(Params.wsCenter);
    hText2.SetText('');
    hText2.Show;
    hW.FinishBatchDraw;

    for i = cd:-1:0
      hText2.SetText(num2str(i));
      pause(1);
    end
    hText2.Hide;

    return

  case 'checkok'

    targrad = 8;
    xrng = [range(Params.wsBounds(:,1))];
    yrng = [range(Params.wsBounds(:,2))];
    os = [-60 -20];
    dx = [xrng/4.5 0]; % range(Params.wsBounds(:,2))/5
    dy = [0 yrng/7];
    otherObjS(1).hTrg.SetXY(Params.wsCenter + os - dx);
    otherObjS(1).trgLoc = otherObjS(1).hTrg.GetXY;
    otherObjS(1).hTrg.SetScale(targrad*0.75);
    otherObjS(1).trgRad = otherObjS(1).hTrg.GetScale;
    otherObjS(1).hTrg.Show;
    otherObjS(1).hText.SetXY(otherObjS(1).trgLoc + dy);
    otherObjS(1).txtLoc = otherObjS(1).hText.GetXY;
    otherObjS(1).hText.SetText('Yes');
    otherObjS(1).hText.SetScale(45);
    otherObjS(1).hText.Show;

    otherObjS(2).hTrg.SetXY(Params.wsCenter + os + dx + [-35 -35]);
    otherObjS(2).trgLoc = otherObjS(2).hTrg.GetXY;
    otherObjS(2).hTrg.SetScale(targrad);
    otherObjS(2).trgRad = otherObjS(2).hTrg.GetScale;
    otherObjS(2).hTrg.Show;
    otherObjS(2).hText.SetXY(otherObjS(2).trgLoc + dy);
    otherObjS(2).txtLoc = otherObjS(2).hText.GetXY;
    otherObjS(2).hText.SetText('No');
    otherObjS(2).hText.SetScale(45);
    otherObjS(2).hText.Show;

    capturedTrg = Monkey_getMorphometrics('capture',otherObjS(1:2));

    otherObjS(1).hTrg.Hide;
    otherObjS(2).hTrg.Hide;
    otherObjS(1).hText.Hide;
    otherObjS(2).hText.Hide;

    if capturedTrg == 1
      out = 1;
    else
      out = 0;
    end

    varargout = {out};

    return

  case 'docornertargets'

    xrng = [range(Params.wsBounds(:,1))];
    yrng = [range(Params.wsBounds(:,2))];
    os = [-55 0];
    dx = [xrng/4.5 0];
    dy = [0 yrng/10];

    %  Target to capture
    otherObjS(1).hTrg.SetScale(8);
    otherObjS(1).trgRad = otherObjS(1).hTrg.GetScale/4;  %  Must grab center

    %  Cancel button
    otherObjS(2).hTrg.SetXY(Params.wsCenter + os);
    otherObjS(2).trgLoc = otherObjS(2).hTrg.GetXY;
    otherObjS(2).hTrg.SetScale(8);
    otherObjS(2).trgRad = otherObjS(2).hTrg.GetScale;
    otherObjS(2).hTrg.SetColor([1 0 0]);
    otherObjS(2).hTrg.Show;
    otherObjS(2).hText.SetXY(Params.wsCenter + os - dy);
    otherObjS(2).txtLoc = otherObjS(2).hText.GetXY;
    otherObjS(2).hText.SetText('Cancel');
    otherObjS(2).hText.SetScale(20);
    otherObjS(2).hText.Show;

    tlocs = [Params.wsCenter; ...
      Params.wsBounds(1,1) Params.wsBounds(1,2); ...
      Params.wsBounds(2,1)/1.75 Params.wsBounds(1,2); ...
      Params.wsBounds(1,1) Params.wsBounds(2,2); ...
      Params.wsBounds(2,1)/1.75 Params.wsBounds(2,2); ...
      ];

    goahead = 1;
    coords = zeros(size(tlocs,1),3);
    for ci = 1:size(tlocs,1)
      cx = tlocs(ci,1);
      cy = tlocs(ci,2);
      if goahead
        otherObjS(1).hTrg.SetXY([cx cy]);
        otherObjS(1).trgLoc = otherObjS(1).hTrg.GetXY;
        otherObjS(1).hTrg.Show;
        capturedTrg = Monkey_getMorphometrics('capture',otherObjS(1:2));
        if capturedTrg == 1  %  Target captured
          [handxy,handvel] = TrialGetKin(hL,O.marker,5,[1 2 3]);
          coords(ci,:) = handxy(end,:);
        else  % Cancel button selected
          hW.HideGroup(0);
          goahead = 0;
          coords = nan;
        end
      end

    end
    hW.HideGroup(0);

    varargout = {coords};

    return

  case 'dooption'

    whichOpt = varargin{1};

    hW.HideGroup(1);

    out = 0;
    switch whichOpt

      case 1  %  L. Eye

        hText1.SetText('Hold Marker at Left Eye Location');
        hText1.Show;
        Monkey_getMorphometrics('doCountDown');
        [handxy,handvel] = TrialGetKin(hL,O.marker,5,[1 2 3]);
        hText1.SetText('Ok?');
        if Monkey_getMorphometrics('checkOk')
          outStruct.LeftEyeLoc = handxy(end,:);
          hText1.Hide;
          hText2.SetText('Data Captured.');
          hText2.Show;
          optionTrgObjS(whichOpt).hOptionTrg.SetFillFlag(0);
          pause(0.75);
        else
          hText2.SetText('Cancelled');
          hText2.Show;
          pause(1.0);
        end

      case 2  %  C. Eye

        hText1.SetText('Hold Marker at Cyclopean Eye Location');
        hText1.Show;
        Monkey_getMorphometrics('doCountDown');
        [handxy,handvel] = TrialGetKin(hL,O.marker,5,[1 2 3]);
        hText1.SetText('Ok?');
        if Monkey_getMorphometrics('checkOk')
          outStruct.CycEyeLoc = handxy(end,:);
          hText1.Hide;
          hText2.SetText('Data Captured.');
          hText2.Show;
          optionTrgObjS(whichOpt).hOptionTrg.SetFillFlag(0);
          pause(0.75);
        else
          hText2.SetText('Cancelled');
          hText2.Show;
          pause(1.0);
        end

      case 3  %  R. Eye

        hText1.SetText('Hold Marker at Right Eye Location');
        hText1.Show;
        Monkey_getMorphometrics('doCountDown');
        [handxy,handvel] = TrialGetKin(hL,O.marker,5,[1 2 3]);
        hText1.SetText('Ok?');
        if Monkey_getMorphometrics('checkOk')
          outStruct.RightEyeLoc = handxy(end,:);
          hText1.Hide;
          hText2.SetText('Data Captured.');
          hText2.Show;
          optionTrgObjS(whichOpt).hOptionTrg.SetFillFlag(0);
          pause(0.75);
        else
          hText2.SetText('Cancelled');
          hText2.Show;
          pause(1.0);
        end

      case 4  %  R. Shoulder

        hText1.SetText('Hold Marker at Right Shoulder Location');
        hText1.Show;
        Monkey_getMorphometrics('doCountDown');
        [handxy,handvel] = TrialGetKin(hL,O.marker,5,[1 2 3]);
        hText1.SetText('Ok?');
        if Monkey_getMorphometrics('checkOk')
          outStruct.RightShoulderLoc = handxy(end,:);
          hText1.Hide;
          hText2.SetText('Data Captured.');
          hText2.Show;
          optionTrgObjS(whichOpt).hOptionTrg.SetFillFlag(0);
          pause(0.75);
        else
          hText2.SetText('Cancelled');
          hText2.Show;
          pause(1.0);
        end

      case 5  %  Mirror
        hText1.SetText('Place marker in targets on MIRROR.');
        hText1.Show;
        coords = Monkey_getMorphometrics('doCornerTargets');
        hText1.Hide;
        if ~isnan(coords)
          outStruct.MirrorCoords = coords;
          hText2.SetText('Data Captured.');
          hText2.Show;
          optionTrgObjS(whichOpt).hOptionTrg.SetFillFlag(0);
          pause(0.75);
        else
          hText2.SetText('Cancelled');
          hText2.Show;
          pause(1.0);
        end

      case 6  %  Table

        hText1.SetText('Place marker in targets on TABLE.');
        hText1.Show;
        coords = Monkey_getMorphometrics('doCornerTargets');
        hText1.Hide;
        if ~isnan(coords)
          outStruct.TableCoords = coords;
          hText2.SetText('Data Captured.');
          hText2.Show;
          optionTrgObjS(whichOpt).hOptionTrg.SetFillFlag(0);
          pause(0.75);
        else
          hText2.SetText('Cancelled');
          hText2.Show;
          pause(1.0);
        end

      case 7  %  Filter

        hText1.SetText('Place marker in targets on Filter.');
        hText1.Show;
        coords = Monkey_getMorphometrics('doCornerTargets');
        hText1.Hide;
        if ~isnan(coords)
          outStruct.FilterCoords = coords;
          hText2.SetText('Data Captured.');
          hText2.Show;
          optionTrgObjS(whichOpt).hOptionTrg.SetFillFlag(0);
          pause(0.75);
        else
          hText2.SetText('Cancelled');
          hText2.Show;
          pause(1.0);
        end

      case 8  %  Cancel
        hText1.SetText('Cancel??');
        hText1.Show;
        if Monkey_getMorphometrics('checkOk')
          out = 1;
        else
          out = 0;
        end

      case 9  %  Done
        hText1.SetText('Exit & Save data??');
        hText1.Show;
        if Monkey_getMorphometrics('checkOk')
          Monkey_getMorphometrics('savedata');
          out = 1;
        else
          out = 0;
        end

      otherwise

    end
    hText1.Hide;
    hText2.Hide;

    varargout = {out};

    return

  case 'savedata'

    hText1.Hide;
    tstr1 = sprintf('Save Data for %s?',O.name);
    hText1.SetScale(25);
    hText1.SetText(tstr1);
    hText1.Show;

    if Monkey_getMorphometrics('checkOk')
      hText1.Hide;

      [suc,mdmsg] = mkdir(O.outputdir);
      [suc2,mdmsg] = mkdir(fullfile(O.outputdir,'Backups',''));
      if ~(suc & suc2)
        errstr = sprintf('Couldn''t create new DIR: %s.',O.outputdir);
        hText1.SetScale(15);
        hText1.SetText(errstr);
        hText1.Show;

        hText2.SetScale(15);
        hText2.SetXY(hText1.GetXY + [10 -30]);
        hText2.SetText('Not Saving');
        hText2.Show;
        pause(1);

      else
        if exist(fullfile(O.outputdir,'MorphometricData.mat'),'file') == 2
          load(fullfile(O.outputdir,'MorphometricData'),'morphoData');
          if ~isequal(O.name,morphoData.name)
            hText1.SetText('Wrong loaded data!. Quitting.');
            hText1.Show;
            pause(2);
            error('Subject name in loaded morphoData doesn''t match!');
          end
          fn = fieldnames(outStruct);
          for fi = 1:length(fn)
            %  Only overwrite the fields for data we collected this time.
            morphoData.(fn{fi}) = outStruct.(fn{fi});
          end
          morphoData.updateDate = datestr(now);
          rptstr = 'Data File Updated.';
        else
          morphoData = outStruct;
          morphoData.name = O.name;
          morphoData.createDate = datestr(now);
          morphoData.updateDate = morphoData.createDate;
          rptstr = 'Data File Created.';
        end

        save(fullfile(O.outputdir,'MorphometricData'),'morphoData');  %  Save the data
        fprintf('\nSaved morphoData for %s\n',O.name);
        bustr = sprintf('MorphometricData_%s_%s',O.name,datestr(now,30));
        save(fullfile(O.outputdir,'Backups',bustr),'morphoData');  %  Save a backup copy
        fprintf('\nSaved backup copy of morphoData for %s\n',O.name);
        hText1.SetScale(20);
        hText1.SetText(rptstr);
        hText1.Show;
        pause(1.3);
      end
    end
    hText1.Hide;

    return

  case 'setup on'

    ServerNamesInclude;

    %% LIBERTY
    if iscom(hL)
      fprintf('Tracker is already running! \n');
    else
      fprintf('Connecting to the Tracker\n');
      hL = actxserver(strTrackerName, strTrackerComputer);
    end

    %% VISSERVER
    hcnt = 0;
    ang = [0:30]/30*2*pi;
    if (iscom(hW)), % Don't do anything
      fprintf('VisServer is already running! \n');
    else
      fprintf('CP_Display...\n');
      hW = actxserver('CP_Display.VMain', strDisplayComputer);
    end

    trgZ = 0.75;

    %% Create visserver objects
    %optionTrgObjS = struct([]);
    for oti = 1:size(O.optionsList,1)
      if (length(optionTrgObjS)<oti) | isempty(optionTrgObjS(oti).hOptionTrg) | ~iscom(optionTrgObjS(oti).hOptionTrg)
        fprintf('... %i ',oti);
        optionTrgObjS(oti).hOptionTrg = actxserver('CP_Display.VDisk',strDisplayComputer);

        optionTrgObjS(oti).hText = actxserver('CP_Display.VText',strDisplayComputer);
        optionTrgObjS(oti).hText.Hide;
        optionTrgObjS(oti).hText.SetScale(50);
      end
    end
    fprintf('\n');

    for i = 1:5
      fprintf('... %i ',i);
      otherObjS(i).hTrg = actxserver('CP_Display.VDisk',strDisplayComputer);
      otherObjS(i).hTrg.SetZ(trgZ);

      otherObjS(i).hText = actxserver('CP_Display.VText',strDisplayComputer);
      otherObjS(i).hText.Hide;
      otherObjS(i).hText.SetScale(50);
      otherObjS(i).hText.SetZ(trgZ);
    end
    fprintf('\n');

    if isempty(hCursor) | ~iscom(hCursor),      % Feedback finger handle
      % fprintf('... %i ',hcnt);
      hCursor      = actxserver('CP_Display.VPolygon',strDisplayComputer);
      hCursor.SetVertices([cos(ang); sin(ang)]);
      hCursor.SetZ(0.12);
    end

    if isempty(hCursorRing) | ~iscom(hCursorRing)
      hCursorRing = actxserver('CP_Display.VPolygon',strDisplayComputer);
      hCursorRing.SetVertices([cos(ang); sin(ang)]);
      hCursorRing.SetZ(0.1);
    end

    if isempty(hText1)  | ~iscom(hText1)
      hText1 = actxserver('CP_Display.VText',strDisplayComputer);
      hText1.Hide;
      hText1.SetScale(25);
      hText1.SetZ(trgZ);
    end

    if isempty(hText2)  | ~iscom(hText2)
      hText2 = actxserver('CP_Display.VText',strDisplayComputer);
      hText2.Hide;
      hText2.SetScale(30);
      hText2.SetZ(trgZ);
    end

    fprintf('Tone Test . . . ');
    ToneStart(500, 0.5);
    fprintf('Done.\n')

    targetrad = 10;

    ul = [Params.wsBounds(1,1) Params.wsBounds(2,2)];
    wsbRange = range(Params.wsBounds,1);
    ploc = ul + [-45 -95];
    delt = [27 0];
    vd = wsbRange(2)/6.25;
    hd = targetrad*1.3;
    for oi = 1:size(O.optionsList,1)
      vd = -vd;
      hd = -hd;
      xy = ploc + delt.*(oi-1);
      optionTrgObjS(oi).hText.SetXY(xy + [hd vd]);
      optionTrgObjS(oi).hText.SetZ(trgZ);
      optionTrgObjS(oi).hText.SetText(O.optionsList{oi});
      optionTrgObjS(oi).hText.SetScale(15);
      optionTrgObjS(oi).hText.SetAngle(60);
      optionTrgObjS(oi).hText.Show;
      optionTrgObjS(oi).textLoc = xy + [0 vd];
      optionTrgObjS(oi).hText.SetGroupID(1);

      optionTrgObjS(oi).hOptionTrg.SetXY(xy);
      optionTrgObjS(oi).hOptionTrg.SetZ(trgZ);
      optionTrgObjS(oi).hOptionTrg.SetScale(targetrad);
      optionTrgObjS(oi).hOptionTrg.Show;
      optionTrgObjS(oi).hOptionTrg.SetFillFlag(1);
      optionTrgObjS(oi).hOptionTrg.SetColor(O.optionsInfo(oi).Color);
      optionTrgObjS(oi).trgLoc = xy;
      optionTrgObjS(oi).trgRad = targetrad;
      optionTrgObjS(oi).hOptionTrg.SetGroupID(1);
    end

    hText1.SetXY(ploc + [105 30]);
    hText2.SetXY(ploc + [wsbRange(1)/2.5 -50]);

    hCursor.SetColor([1 1 1]);
    hCursor.SetScale(targetrad/4);
    hCursor.SetFillFlag(1);

    hCursorRing.SetColor([0 0 0]);
    hCursorRing.SetScale(hCursor.GetScale);
    hCursorRing.SetFillFlag(0);

    return

  case 'setup off'


    fprintf('Close Down VisServer, IScan and TDT...\n')
    if (iscom(hL)),         delete(hL);             end
    if (iscom(hW)),         delete(hW);             end
    if iscom(hText1),       delete(hText1);         end
    if iscom(hText2),       delete(hText2);         end
    if iscom(hCursor),      delete(hCursor);        end
    if iscom(hCursorRing),  delete(hCursorRing);    end

    fprintf('\n');
    for oti = 1:length(optionTrgObjS)
      if ~isempty(optionTrgObjS)
        if ~isempty(optionTrgObjS(oti).hOptionTrg) & iscom(optionTrgObjS(oti).hOptionTrg)
          fprintf('Deleting optionTrgObjS ... %i ',oti);
          delete(optionTrgObjS(oti).hOptionTrg);
        end
        if ~isempty(optionTrgObjS(oti).hText) & iscom(optionTrgObjS(oti).hText)
          delete(optionTrgObjS(oti).hText);
        end
      end
    end
    fprintf('\n');

    for oti = 1:length(otherObjS)
      if ~isempty(otherObjS)
        if ~isempty(otherObjS(oti).hTrg) & iscom(otherObjS(oti).hTrg)
          fprintf('Deleting otherObjS... %i ',oti);
          delete(otherObjS(oti).hTrg);
        end
        if ~isempty(otherObjS(oti).hText) & iscom(otherObjS(oti).hText)
          delete(otherObjS(oti).hText);
        end
      end
    end
    fprintf('\n');

  otherwise
    error('Unknown action');

end