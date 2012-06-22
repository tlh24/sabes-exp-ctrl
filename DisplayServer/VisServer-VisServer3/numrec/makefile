# Makefile for Numerical recipes in C
INSTALL_LIB = /home/sabes/lib
INSTALL_INCLUDE = /usr/local/include

# CC=gcc
CC=cc

# these flags good for hopper (2100a 5/300) using gcc
# Tim Leek 5/96
#CFLAGS= -O3 -I/home/sabes/include -ansi
CFLAGS= -fast -I/home/sabes/include 

#CFLAGS= -fast -I$(otherdir) -Bdynamic -ansi -PIC 
RM=rm -f
#targetlib=libnrc.a
targetlib=libnrc.so

nrobjs=addint.o airy.o amebsa.o amoeba.o amotry.o amotsa.o anneal.o anorm2.o \
arcmak.o arcode.o arcsum.o asolve.o atimes.o avevar.o badluk.o balanc.o \
banbks.o bandec.o banmul.o bcucof.o bcuint.o beschb.o bessi.o bessi0.o \
bessi1.o bessik.o bessj.o bessj0.o bessj1.o bessjy.o bessk.o bessk0.o \
bessk1.o bessy.o bessy0.o bessy1.o beta.o betacf.o betai.o bico.o \
bksub.o bnldev.o brent.o broydn.o bsstep.o caldat.o chder.o chebev.o \
chebft.o chebpc.o chint.o chixy.o choldc.o cholsl.o chsone.o chstwo.o \
cisi.o cntab1.o cntab2.o complex.o convlv.o copy.o correl.o cosft1.o \
cosft2.o covsrt.o crank.o cyclic.o daub4.o dawson.o dbrent.o ddpoly.o \
decchk.o df1dim.o dfour1.o dfpmin.o dfridr.o dftcor.o dftint.o difeq.o \
dlinmin.o dpythag.o drealft.o dsprsax.o dsprstx.o dsvbksb.o dsvdcmp.o \
eclass.o eclazz.o ei.o eigsrt.o elle.o ellf.o ellpi.o elmhes.o erfcc.o \
erff.o erffc.o eulsum.o evlmem.o expdev.o expint.o f1dim.o factln.o \
factrl.o fasper.o fdjac.o fgauss.o fill0.o fit.o fitexy.o fixrts.o \
fleg.o flmoon.o fmin.o four1.o fourew.o fourfs.o fourn.o fpoly.o \
fred2.o fredex.o fredin.o frenel.o frprmn.o ftest.o gamdev.o gammln.o \
gammp.o gammq.o gasdev.o gaucof.o gauher.o gaujac.o gaulag.o gauleg.o \
gaussj.o gcf.o golden.o gser.o hpsel.o hpsort.o hqr.o hufapp.o hufdec.o \
hufenc.o hufmak.o hunt.o hypdrv.o hypgeo.o hypser.o icrc.o icrc1.o \
igray.o iindexx.o indexx.o interp.o irbit1.o irbit2.o jacobi.o jacobn.o \
julday.o kendl1.o kendl2.o kermom.o ks2d1s.o ks2d2s.o ksone.o kstwo.o \
laguer.o lfit.o linbcg.o linmin.o lnsrch.o locate.o lop.o lubksb.o \
ludcmp.o machar.o matadd.o matsub.o medfit.o memcof.o metrop.o mgfas.o \
mglin.o midexp.o midinf.o midpnt.o midsql.o midsqu.o miser.o mmid.o \
mnbrak.o mnewt.o moment.o mp2dfr.o mpdiv.o mpinv.o mpmul.o mpops.o \
mppi.o mprove.o mpsqrt.o mrqcof.o mrqmin.o newt.o nrutil.o odeint.o \
orthog.o pade.o pccheb.o pcshft.o pearsn.o period.o piksr2.o piksrt.o \
pinvs.o plgndr.o poidev.o polcoe.o polcof.o poldiv.o polin2.o polint.o \
powell.o predic.o probks.o psdes.o pwt.o pwtset.o pythag.o pzextr.o \
qgaus.o qrdcmp.o qromb.o qromo.o qroot.o qrsolv.o qrupdt.o qsimp.o \
qtrap.o quad3d.o quadct.o quadmx.o quadvl.o ran0.o ran1.o ran2.o ran3.o \
ran4.o rank.o ranpt.o ratint.o ratlsq.o ratval.o rc.o rd.o realft.o \
rebin.o red.o relax.o relax2.o resid.o revcst.o reverse.o rf.o rj.o \
rk4.o rkck.o rkdumb.o rkqs.o rlft3.o rofunc.o rotate.o rsolv.o rstrct.o \
rtbis.o rtflsp.o rtnewt.o rtsafe.o rtsec.o rzextr.o savgol.o scrsho.o \
select.o selip.o sfroid.o shell.o shoot.o shootf.o simp1.o simp2.o \
simp3.o simplx.o simpr.o sinft.o slvsm2.o slvsml.o sncndn.o snrm.o \
sobseq.o solvde.o sor.o sort.o sort2.o sort3.o spctrm.o spear.o \
sphbes.o sphfpt.o sphoot.o splie2.o splin2.o spline.o splint.o spread.o \
sprsax.o sprsin.o sprspm.o sprstm.o sprstp.o sprstx.o stifbs.o stiff.o \
stoerm.o svbksb.o svdcmp.o svdfit.o svdvar.o toeplz.o tptest.o tqli.o \
trapzd.o tred2.o tridag.o trncst.o trnspt.o ttest.o tutest.o twofft.o \
vander.o vegas.o voltra.o wt1.o wtn.o wwghts.o zbrac.o zbrak.o zbrent.o \
zrhqr.o zriddr.o zroots.o

all:: $(targetlib)

$(targetlib): $(nrobjs)
	$(RM) $(targetlib)
	$(AR) clq $(targetlib) $(nrobjs)
	ranlib $(targetlib)

clean: 
	$(RM) $(nrobjs) $(targetlib)

install:
	cp $(targetlib) $(INSTALL_LIB)
	ranlib $(targetlib)
	cp $(otherdir)/nr.h $(INSTALL_INCLUDE)
	cp $(otherdir)/nrutil.h $(INSTALL_INCLUDE)
