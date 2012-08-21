#ifndef __GTKGLX_H__
#define __GTKGLX_H__

void setupGLX(GtkWidget *area);
void freeGLX();
int configureGLX(GtkWidget *widget);
int realizeGLX(GtkWidget *w, void*); 
int exposeGLX(GtkWidget *widget);
int swapGLX(); 

#endif