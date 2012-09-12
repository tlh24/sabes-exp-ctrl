# Makefile for figures sfo visit. 

FIGS = present_impl.svg new_impl.svg bmi5.svg

TARGS = $(FIGS:%.svg=%.pdf) 
PNGS = $(BIGFIGS:%.svg=%.png)

all: $(TARGS) $(PNGS) impl.pdf

clean: 
	rm -rf *.pdf *.out *.aux *.log *.nav *.snm *.toc

impl.pdf: impl.tex
	pdflatex $<
	okular impl.pdf
	
%.pdf: %.svg
	inkscape $< -A $@
	
%.png: %.svg
	inkscape $< -w 1300 -y 100 -D -e $@