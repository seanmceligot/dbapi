#ifndef __GREENAPP
#define __GREENAPP

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/utils.h"
#include "wx/grid.h"
#include "wx/colordlg.h"
#include "wx/app.h"
#include "wx/frame.h"


class GreenFrame : public wxFrame {
	wxGrid * _grid;
	void createMenu();
	void createGrid();
public:
  GreenFrame(wxFrame* frame);
};

class GreenApp : public wxApp {
	GreenFrame _frame;
public:
	GreenApp(): _frame(NULL) {};
  virtual bool OnInit();
};


#endif
