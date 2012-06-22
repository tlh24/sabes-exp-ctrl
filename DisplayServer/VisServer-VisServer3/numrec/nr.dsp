# Microsoft Developer Studio Project File - Name="nr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=nr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nr.mak" CFG="nr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nr - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "nr - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "nr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "nr - Win32 Release"
# Name "nr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Addint.c
# End Source File
# Begin Source File

SOURCE=.\Airy.c
# End Source File
# Begin Source File

SOURCE=.\Amebsa.c
# End Source File
# Begin Source File

SOURCE=.\Amoeba.c
# End Source File
# Begin Source File

SOURCE=.\Amotry.c
# End Source File
# Begin Source File

SOURCE=.\Amotsa.c
# End Source File
# Begin Source File

SOURCE=.\Anneal.c
# End Source File
# Begin Source File

SOURCE=.\Anorm2.c
# End Source File
# Begin Source File

SOURCE=.\Arcmak.c
# End Source File
# Begin Source File

SOURCE=.\Arcode.c
# End Source File
# Begin Source File

SOURCE=.\Arcsum.c
# End Source File
# Begin Source File

SOURCE=.\Asolve.c
# End Source File
# Begin Source File

SOURCE=.\Atimes.c
# End Source File
# Begin Source File

SOURCE=.\Avevar.c
# End Source File
# Begin Source File

SOURCE=.\Balanc.c
# End Source File
# Begin Source File

SOURCE=.\Banbks.c
# End Source File
# Begin Source File

SOURCE=.\Bandec.c
# End Source File
# Begin Source File

SOURCE=.\Banmul.c
# End Source File
# Begin Source File

SOURCE=.\Bcucof.c
# End Source File
# Begin Source File

SOURCE=.\Bcuint.c
# End Source File
# Begin Source File

SOURCE=.\Beschb.c
# End Source File
# Begin Source File

SOURCE=.\Bessi.c
# End Source File
# Begin Source File

SOURCE=.\Bessi0.c
# End Source File
# Begin Source File

SOURCE=.\Bessi1.c
# End Source File
# Begin Source File

SOURCE=.\Bessik.c
# End Source File
# Begin Source File

SOURCE=.\Bessj.c
# End Source File
# Begin Source File

SOURCE=.\Bessj0.c
# End Source File
# Begin Source File

SOURCE=.\Bessj1.c
# End Source File
# Begin Source File

SOURCE=.\Bessjy.c
# End Source File
# Begin Source File

SOURCE=.\Bessk.c
# End Source File
# Begin Source File

SOURCE=.\Bessk0.c
# End Source File
# Begin Source File

SOURCE=.\Bessk1.c
# End Source File
# Begin Source File

SOURCE=.\Bessy.c
# End Source File
# Begin Source File

SOURCE=.\Bessy0.c
# End Source File
# Begin Source File

SOURCE=.\Bessy1.c
# End Source File
# Begin Source File

SOURCE=.\Beta.c
# End Source File
# Begin Source File

SOURCE=.\Betacf.c
# End Source File
# Begin Source File

SOURCE=.\Betai.c
# End Source File
# Begin Source File

SOURCE=.\Bico.c
# End Source File
# Begin Source File

SOURCE=.\Bksub.c
# End Source File
# Begin Source File

SOURCE=.\Bnldev.c
# End Source File
# Begin Source File

SOURCE=.\Brent.c
# End Source File
# Begin Source File

SOURCE=.\Broydn.c
# End Source File
# Begin Source File

SOURCE=.\Bsstep.c
# End Source File
# Begin Source File

SOURCE=.\Caldat.c
# End Source File
# Begin Source File

SOURCE=.\Chder.c
# End Source File
# Begin Source File

SOURCE=.\Chebev.c
# End Source File
# Begin Source File

SOURCE=.\Chebft.c
# End Source File
# Begin Source File

SOURCE=.\Chebpc.c
# End Source File
# Begin Source File

SOURCE=.\Chint.c
# End Source File
# Begin Source File

SOURCE=.\Chixy.c
# End Source File
# Begin Source File

SOURCE=.\Choldc.c
# End Source File
# Begin Source File

SOURCE=.\Cholsl.c
# End Source File
# Begin Source File

SOURCE=.\Chsone.c
# End Source File
# Begin Source File

SOURCE=.\Chstwo.c
# End Source File
# Begin Source File

SOURCE=.\Cisi.c
# End Source File
# Begin Source File

SOURCE=.\Cntab1.c
# End Source File
# Begin Source File

SOURCE=.\Cntab2.c
# End Source File
# Begin Source File

SOURCE=.\Complex.c
# End Source File
# Begin Source File

SOURCE=.\Convlv.c
# End Source File
# Begin Source File

SOURCE=.\Copy.c
# End Source File
# Begin Source File

SOURCE=.\Correl.c
# End Source File
# Begin Source File

SOURCE=.\Cosft1.c
# End Source File
# Begin Source File

SOURCE=.\Cosft2.c
# End Source File
# Begin Source File

SOURCE=.\Covsrt.c
# End Source File
# Begin Source File

SOURCE=.\Crank.c
# End Source File
# Begin Source File

SOURCE=.\Cyclic.c
# End Source File
# Begin Source File

SOURCE=.\Daub4.c
# End Source File
# Begin Source File

SOURCE=.\Dawson.c
# End Source File
# Begin Source File

SOURCE=.\Dbrent.c
# End Source File
# Begin Source File

SOURCE=.\Ddpoly.c
# End Source File
# Begin Source File

SOURCE=.\Decchk.c
# End Source File
# Begin Source File

SOURCE=.\Df1dim.c
# End Source File
# Begin Source File

SOURCE=.\Dfour1.c
# End Source File
# Begin Source File

SOURCE=.\Dfpmin.c
# End Source File
# Begin Source File

SOURCE=.\Dfridr.c
# End Source File
# Begin Source File

SOURCE=.\Dftcor.c
# End Source File
# Begin Source File

SOURCE=.\Dftint.c
# End Source File
# Begin Source File

SOURCE=.\Difeq.c
# End Source File
# Begin Source File

SOURCE=.\Dlinmin.c
# End Source File
# Begin Source File

SOURCE=.\Dpythag.c
# End Source File
# Begin Source File

SOURCE=.\Drealft.c
# End Source File
# Begin Source File

SOURCE=.\Dsprsax.c
# End Source File
# Begin Source File

SOURCE=.\Dsprstx.c
# End Source File
# Begin Source File

SOURCE=.\Dsvbksb.c
# End Source File
# Begin Source File

SOURCE=.\Dsvdcmp.c
# End Source File
# Begin Source File

SOURCE=.\Eclass.c
# End Source File
# Begin Source File

SOURCE=.\Eclazz.c
# End Source File
# Begin Source File

SOURCE=.\Ei.c
# End Source File
# Begin Source File

SOURCE=.\Eigsrt.c
# End Source File
# Begin Source File

SOURCE=.\Elle.c
# End Source File
# Begin Source File

SOURCE=.\Ellf.c
# End Source File
# Begin Source File

SOURCE=.\Ellpi.c
# End Source File
# Begin Source File

SOURCE=.\Elmhes.c
# End Source File
# Begin Source File

SOURCE=.\Erfcc.c
# End Source File
# Begin Source File

SOURCE=.\Erff.c
# End Source File
# Begin Source File

SOURCE=.\Erffc.c
# End Source File
# Begin Source File

SOURCE=.\Eulsum.c
# End Source File
# Begin Source File

SOURCE=.\Evlmem.c
# End Source File
# Begin Source File

SOURCE=.\Expdev.c
# End Source File
# Begin Source File

SOURCE=.\Expint.c
# End Source File
# Begin Source File

SOURCE=.\F1dim.c
# End Source File
# Begin Source File

SOURCE=.\Factln.c
# End Source File
# Begin Source File

SOURCE=.\Factrl.c
# End Source File
# Begin Source File

SOURCE=.\Fasper.c
# End Source File
# Begin Source File

SOURCE=.\Fdjac.c
# End Source File
# Begin Source File

SOURCE=.\Fgauss.c
# End Source File
# Begin Source File

SOURCE=.\Fill0.c
# End Source File
# Begin Source File

SOURCE=.\Fit.c
# End Source File
# Begin Source File

SOURCE=.\Fitexy.c
# End Source File
# Begin Source File

SOURCE=.\Fixrts.c
# End Source File
# Begin Source File

SOURCE=.\Fleg.c
# End Source File
# Begin Source File

SOURCE=.\Flmoon.c
# End Source File
# Begin Source File

SOURCE=.\Fmin.c
# End Source File
# Begin Source File

SOURCE=.\Four1.c
# End Source File
# Begin Source File

SOURCE=.\Fourew.c
# End Source File
# Begin Source File

SOURCE=.\Fourfs.c
# End Source File
# Begin Source File

SOURCE=.\Fourn.c
# End Source File
# Begin Source File

SOURCE=.\Fpoly.c
# End Source File
# Begin Source File

SOURCE=.\Fred2.c
# End Source File
# Begin Source File

SOURCE=.\Fredin.c
# End Source File
# Begin Source File

SOURCE=.\Frenel.c
# End Source File
# Begin Source File

SOURCE=.\Frprmn.c
# End Source File
# Begin Source File

SOURCE=.\Ftest.c
# End Source File
# Begin Source File

SOURCE=.\Gamdev.c
# End Source File
# Begin Source File

SOURCE=.\Gammln.c
# End Source File
# Begin Source File

SOURCE=.\Gammp.c
# End Source File
# Begin Source File

SOURCE=.\Gammq.c
# End Source File
# Begin Source File

SOURCE=.\Gasdev.c
# End Source File
# Begin Source File

SOURCE=.\Gaucof.c
# End Source File
# Begin Source File

SOURCE=.\Gauher.c
# End Source File
# Begin Source File

SOURCE=.\Gaujac.c
# End Source File
# Begin Source File

SOURCE=.\Gaulag.c
# End Source File
# Begin Source File

SOURCE=.\Gauleg.c
# End Source File
# Begin Source File

SOURCE=.\Gaussj.c
# End Source File
# Begin Source File

SOURCE=.\Gcf.c
# End Source File
# Begin Source File

SOURCE=.\Golden.c
# End Source File
# Begin Source File

SOURCE=.\Gser.c
# End Source File
# Begin Source File

SOURCE=.\Hpsel.c
# End Source File
# Begin Source File

SOURCE=.\Hpsort.c
# End Source File
# Begin Source File

SOURCE=.\Hqr.c
# End Source File
# Begin Source File

SOURCE=.\Hufapp.c
# End Source File
# Begin Source File

SOURCE=.\Hufdec.c
# End Source File
# Begin Source File

SOURCE=.\Hufenc.c
# End Source File
# Begin Source File

SOURCE=.\Hufmak.c
# End Source File
# Begin Source File

SOURCE=.\Hunt.c
# End Source File
# Begin Source File

SOURCE=.\Hypdrv.c
# End Source File
# Begin Source File

SOURCE=.\Hypgeo.c
# End Source File
# Begin Source File

SOURCE=.\Hypser.c
# End Source File
# Begin Source File

SOURCE=.\Icrc.c
# End Source File
# Begin Source File

SOURCE=.\Icrc1.c
# End Source File
# Begin Source File

SOURCE=.\Igray.c
# End Source File
# Begin Source File

SOURCE=.\Iindexx.c
# End Source File
# Begin Source File

SOURCE=.\Indexx.c
# End Source File
# Begin Source File

SOURCE=.\Interp.c
# End Source File
# Begin Source File

SOURCE=.\Irbit1.c
# End Source File
# Begin Source File

SOURCE=.\Irbit2.c
# End Source File
# Begin Source File

SOURCE=.\Jacobi.c
# End Source File
# Begin Source File

SOURCE=.\Jacobn.c
# End Source File
# Begin Source File

SOURCE=.\Julday.c
# End Source File
# Begin Source File

SOURCE=.\Kendl1.c
# End Source File
# Begin Source File

SOURCE=.\Kendl2.c
# End Source File
# Begin Source File

SOURCE=.\Kermom.c
# End Source File
# Begin Source File

SOURCE=.\Ks2d1s.c
# End Source File
# Begin Source File

SOURCE=.\Ks2d2s.c
# End Source File
# Begin Source File

SOURCE=.\Ksone.c
# End Source File
# Begin Source File

SOURCE=.\Kstwo.c
# End Source File
# Begin Source File

SOURCE=.\Laguer.c
# End Source File
# Begin Source File

SOURCE=.\Lfit.c
# End Source File
# Begin Source File

SOURCE=.\Linbcg.c
# End Source File
# Begin Source File

SOURCE=.\Linmin.c
# End Source File
# Begin Source File

SOURCE=.\Lnsrch.c
# End Source File
# Begin Source File

SOURCE=.\Locate.c
# End Source File
# Begin Source File

SOURCE=.\Lop.c
# End Source File
# Begin Source File

SOURCE=.\Lubksb.c
# End Source File
# Begin Source File

SOURCE=.\Ludcmp.c
# End Source File
# Begin Source File

SOURCE=.\Machar.c
# End Source File
# Begin Source File

SOURCE=.\Matadd.c
# End Source File
# Begin Source File

SOURCE=.\Matsub.c
# End Source File
# Begin Source File

SOURCE=.\Medfit.c
# End Source File
# Begin Source File

SOURCE=.\Memcof.c
# End Source File
# Begin Source File

SOURCE=.\Metrop.c
# End Source File
# Begin Source File

SOURCE=.\Mgfas.c
# End Source File
# Begin Source File

SOURCE=.\Mglin.c
# End Source File
# Begin Source File

SOURCE=.\Midexp.c
# End Source File
# Begin Source File

SOURCE=.\Midinf.c
# End Source File
# Begin Source File

SOURCE=.\Midpnt.c
# End Source File
# Begin Source File

SOURCE=.\Midsql.c
# End Source File
# Begin Source File

SOURCE=.\Midsqu.c
# End Source File
# Begin Source File

SOURCE=.\Miser.c
# End Source File
# Begin Source File

SOURCE=.\Mmid.c
# End Source File
# Begin Source File

SOURCE=.\Mnbrak.c
# End Source File
# Begin Source File

SOURCE=.\Mnewt.c
# End Source File
# Begin Source File

SOURCE=.\Moment.c
# End Source File
# Begin Source File

SOURCE=.\Mp2dfr.c
# End Source File
# Begin Source File

SOURCE=.\Mpdiv.c
# End Source File
# Begin Source File

SOURCE=.\Mpinv.c
# End Source File
# Begin Source File

SOURCE=.\Mpmul.c
# End Source File
# Begin Source File

SOURCE=.\Mpops.c
# End Source File
# Begin Source File

SOURCE=.\Mppi.c
# End Source File
# Begin Source File

SOURCE=.\Mprove.c
# End Source File
# Begin Source File

SOURCE=.\Mpsqrt.c
# End Source File
# Begin Source File

SOURCE=.\Mrqcof.c
# End Source File
# Begin Source File

SOURCE=.\Mrqmin.c
# End Source File
# Begin Source File

SOURCE=.\MyStuff.cpp
# End Source File
# Begin Source File

SOURCE=.\Newt.c
# End Source File
# Begin Source File

SOURCE=.\Nrutil.c
# End Source File
# Begin Source File

SOURCE=.\Odeint.c
# End Source File
# Begin Source File

SOURCE=.\Orthog.c
# End Source File
# Begin Source File

SOURCE=.\Pade.c
# End Source File
# Begin Source File

SOURCE=.\Pccheb.c
# End Source File
# Begin Source File

SOURCE=.\Pcshft.c
# End Source File
# Begin Source File

SOURCE=.\Pearsn.c
# End Source File
# Begin Source File

SOURCE=.\Period.c
# End Source File
# Begin Source File

SOURCE=.\Piksr2.c
# End Source File
# Begin Source File

SOURCE=.\Piksrt.c
# End Source File
# Begin Source File

SOURCE=.\Pinvs.c
# End Source File
# Begin Source File

SOURCE=.\Plgndr.c
# End Source File
# Begin Source File

SOURCE=.\Poidev.c
# End Source File
# Begin Source File

SOURCE=.\Polcoe.c
# End Source File
# Begin Source File

SOURCE=.\Polcof.c
# End Source File
# Begin Source File

SOURCE=.\Poldiv.c
# End Source File
# Begin Source File

SOURCE=.\Polin2.c
# End Source File
# Begin Source File

SOURCE=.\Polint.c
# End Source File
# Begin Source File

SOURCE=.\Powell.c
# End Source File
# Begin Source File

SOURCE=.\Predic.c
# End Source File
# Begin Source File

SOURCE=.\Probks.c
# End Source File
# Begin Source File

SOURCE=.\Psdes.c
# End Source File
# Begin Source File

SOURCE=.\Pwt.c
# End Source File
# Begin Source File

SOURCE=.\Pwtset.c
# End Source File
# Begin Source File

SOURCE=.\Pythag.c
# End Source File
# Begin Source File

SOURCE=.\Pzextr.c
# End Source File
# Begin Source File

SOURCE=.\Qgaus.c
# End Source File
# Begin Source File

SOURCE=.\Qrdcmp.c
# End Source File
# Begin Source File

SOURCE=.\Qromb.c
# End Source File
# Begin Source File

SOURCE=.\Qromo.c
# End Source File
# Begin Source File

SOURCE=.\Qroot.c
# End Source File
# Begin Source File

SOURCE=.\Qrsolv.c
# End Source File
# Begin Source File

SOURCE=.\Qrupdt.c
# End Source File
# Begin Source File

SOURCE=.\Qsimp.c
# End Source File
# Begin Source File

SOURCE=.\Qtrap.c
# End Source File
# Begin Source File

SOURCE=.\Quad3d.c
# End Source File
# Begin Source File

SOURCE=.\Quadct.c
# End Source File
# Begin Source File

SOURCE=.\Quadmx.c
# End Source File
# Begin Source File

SOURCE=.\Quadvl.c
# End Source File
# Begin Source File

SOURCE=.\Ran0.c
# End Source File
# Begin Source File

SOURCE=.\Ran1.c
# End Source File
# Begin Source File

SOURCE=.\Ran2.c
# End Source File
# Begin Source File

SOURCE=.\Ran3.c
# End Source File
# Begin Source File

SOURCE=.\Ran4.c
# End Source File
# Begin Source File

SOURCE=.\Rank.c
# End Source File
# Begin Source File

SOURCE=.\Ranpt.c
# End Source File
# Begin Source File

SOURCE=.\Ratint.c
# End Source File
# Begin Source File

SOURCE=.\Ratlsq.c
# End Source File
# Begin Source File

SOURCE=.\Ratval.c
# End Source File
# Begin Source File

SOURCE=.\Rc.c
# End Source File
# Begin Source File

SOURCE=.\Rd.c
# End Source File
# Begin Source File

SOURCE=.\Realft.c
# End Source File
# Begin Source File

SOURCE=.\Rebin.c
# End Source File
# Begin Source File

SOURCE=.\Red.c
# End Source File
# Begin Source File

SOURCE=.\Relax.c
# End Source File
# Begin Source File

SOURCE=.\Relax2.c
# End Source File
# Begin Source File

SOURCE=.\Resid.c
# End Source File
# Begin Source File

SOURCE=.\Revcst.c
# End Source File
# Begin Source File

SOURCE=.\Reverse.c
# End Source File
# Begin Source File

SOURCE=.\Rf.c
# End Source File
# Begin Source File

SOURCE=.\Rj.c
# End Source File
# Begin Source File

SOURCE=.\Rk4.c
# End Source File
# Begin Source File

SOURCE=.\Rkck.c
# End Source File
# Begin Source File

SOURCE=.\Rkdumb.c
# End Source File
# Begin Source File

SOURCE=.\Rkqs.c
# End Source File
# Begin Source File

SOURCE=.\Rlft3.c
# End Source File
# Begin Source File

SOURCE=.\Rofunc.c
# End Source File
# Begin Source File

SOURCE=.\Rotate.c
# End Source File
# Begin Source File

SOURCE=.\Rsolv.c
# End Source File
# Begin Source File

SOURCE=.\Rstrct.c
# End Source File
# Begin Source File

SOURCE=.\Rtbis.c
# End Source File
# Begin Source File

SOURCE=.\Rtflsp.c
# End Source File
# Begin Source File

SOURCE=.\Rtnewt.c
# End Source File
# Begin Source File

SOURCE=.\Rtsafe.c
# End Source File
# Begin Source File

SOURCE=.\Rtsec.c
# End Source File
# Begin Source File

SOURCE=.\Rzextr.c
# End Source File
# Begin Source File

SOURCE=.\Savgol.c
# End Source File
# Begin Source File

SOURCE=.\Scrsho.c
# End Source File
# Begin Source File

SOURCE=.\Select.c
# End Source File
# Begin Source File

SOURCE=.\Selip.c
# End Source File
# Begin Source File

SOURCE=.\Shell.c
# End Source File
# Begin Source File

SOURCE=.\Shoot.c
# End Source File
# Begin Source File

SOURCE=.\Shootf.c
# End Source File
# Begin Source File

SOURCE=.\Simp1.c
# End Source File
# Begin Source File

SOURCE=.\Simp2.c
# End Source File
# Begin Source File

SOURCE=.\Simp3.c
# End Source File
# Begin Source File

SOURCE=.\Simplx.c
# End Source File
# Begin Source File

SOURCE=.\Simpr.c
# End Source File
# Begin Source File

SOURCE=.\Sinft.c
# End Source File
# Begin Source File

SOURCE=.\Slvsm2.c
# End Source File
# Begin Source File

SOURCE=.\Slvsml.c
# End Source File
# Begin Source File

SOURCE=.\Sncndn.c
# End Source File
# Begin Source File

SOURCE=.\Snrm.c
# End Source File
# Begin Source File

SOURCE=.\Sobseq.c
# End Source File
# Begin Source File

SOURCE=.\Solvde.c
# End Source File
# Begin Source File

SOURCE=.\Sor.c
# End Source File
# Begin Source File

SOURCE=.\Sort.c
# End Source File
# Begin Source File

SOURCE=.\Sort2.c
# End Source File
# Begin Source File

SOURCE=.\Sort3.c
# End Source File
# Begin Source File

SOURCE=.\Spctrm.c
# End Source File
# Begin Source File

SOURCE=.\Spear.c
# End Source File
# Begin Source File

SOURCE=.\Sphbes.c
# End Source File
# Begin Source File

SOURCE=.\Splie2.c
# End Source File
# Begin Source File

SOURCE=.\Splin2.c
# End Source File
# Begin Source File

SOURCE=.\Spline.c
# End Source File
# Begin Source File

SOURCE=.\Splint.c
# End Source File
# Begin Source File

SOURCE=.\Spread.c
# End Source File
# Begin Source File

SOURCE=.\Sprsax.c
# End Source File
# Begin Source File

SOURCE=.\Sprsin.c
# End Source File
# Begin Source File

SOURCE=.\Sprspm.c
# End Source File
# Begin Source File

SOURCE=.\Sprstm.c
# End Source File
# Begin Source File

SOURCE=.\Sprstp.c
# End Source File
# Begin Source File

SOURCE=.\Sprstx.c
# End Source File
# Begin Source File

SOURCE=.\Stifbs.c
# End Source File
# Begin Source File

SOURCE=.\Stiff.c
# End Source File
# Begin Source File

SOURCE=.\Stoerm.c
# End Source File
# Begin Source File

SOURCE=.\Svbksb.c
# End Source File
# Begin Source File

SOURCE=.\Svdcmp.c
# End Source File
# Begin Source File

SOURCE=.\Svdfit.c
# End Source File
# Begin Source File

SOURCE=.\Svdvar.c
# End Source File
# Begin Source File

SOURCE=.\Toeplz.c
# End Source File
# Begin Source File

SOURCE=.\Tptest.c
# End Source File
# Begin Source File

SOURCE=.\Tqli.c
# End Source File
# Begin Source File

SOURCE=.\Trapzd.c
# End Source File
# Begin Source File

SOURCE=.\Tred2.c
# End Source File
# Begin Source File

SOURCE=.\Tridag.c
# End Source File
# Begin Source File

SOURCE=.\Trncst.c
# End Source File
# Begin Source File

SOURCE=.\Trnspt.c
# End Source File
# Begin Source File

SOURCE=.\Ttest.c
# End Source File
# Begin Source File

SOURCE=.\Tutest.c
# End Source File
# Begin Source File

SOURCE=.\Twofft.c
# End Source File
# Begin Source File

SOURCE=.\Vander.c
# End Source File
# Begin Source File

SOURCE=.\Vegas.c
# End Source File
# Begin Source File

SOURCE=.\Voltra.c
# End Source File
# Begin Source File

SOURCE=.\Wt1.c
# End Source File
# Begin Source File

SOURCE=.\Wtn.c
# End Source File
# Begin Source File

SOURCE=.\Wwghts.c
# End Source File
# Begin Source File

SOURCE=.\Zbrac.c
# End Source File
# Begin Source File

SOURCE=.\Zbrak.c
# End Source File
# Begin Source File

SOURCE=.\Zbrent.c
# End Source File
# Begin Source File

SOURCE=.\Zrhqr.c
# End Source File
# Begin Source File

SOURCE=.\Zriddr.c
# End Source File
# Begin Source File

SOURCE=.\Zroots.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Complex.h
# End Source File
# Begin Source File

SOURCE=.\Nr.h
# End Source File
# Begin Source File

SOURCE=.\Nrutil.h
# End Source File
# End Group
# End Target
# End Project
