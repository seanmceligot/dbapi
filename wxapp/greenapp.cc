#include "greenapp.hh"

IMPLEMENT_APP(GreenApp)

bool GreenApp::OnInit()
{
	_frame = new wxFrame(NULL, "GreenApp", wxPoint(50,50), wxSize(450,300));
	_frame->Show(TRUE);
	SetTopWindow(_frame);
	createMenu();
	createGrid();
	return TRUE;
}

static enum { MENU_EXIT, MENU_BROWSE_TABLE };
void GreenApp::createMenu() {
  // Make a menubar
  wxMenu *file_menu = new wxMenu;
  file_menu->Append(MENU_EXIT, "E&xit");

  wxMenu *table_menu = new wxMenu;
  table_menu->Append(MENU_BROWSE_TABLE, "&Browse");

  wxMenuBar *menu_bar = new wxMenuBar;
  menu_bar->Append(file_menu, "&File");
  menu_bar->Append(table_menu, "&Table");
  frame->SetMenuBar(menu_bar);
}
void GreenApp::createGrid() {
  // Make a grid
  _frame->grid = new wxGrid(_frame, 0, 0, 400, 400);

  _frame->grid->CreateGrid(10, 8);
  _frame->grid->SetColumnWidth(3, 200);
  _frame->grid->SetRowHeight(4, 45);
  _frame->grid->SetCellValue("First cell", 0, 0);
  _frame->grid->SetCellValue("Another cell", 1, 1);
  _frame->grid->SetCellValue("Yet another cell", 2, 2);
  _frame->grid->SetCellTextFont(* wxTheFontList->FindOrCreateFont(10, wxROMAN, wxITALIC, wxNORMAL), 0, 0);
  _frame->grid->SetCellTextColour(*wxRED, 1, 1);
  _frame->grid->SetCellBackgroundColour(*wxCYAN, 2, 2);
  if (cellBitmap1 && cellBitmap2)
  {
    _frame->grid->SetCellAlignment(wxCENTRE, 5, 0);
    _frame->grid->SetCellAlignment(wxCENTRE, 6, 0);
    _frame->grid->SetCellBitmap(cellBitmap1, 5, 0);
    _frame->grid->SetCellBitmap(cellBitmap2, 6, 0);
  }
  
  _frame->grid->UpdateDimensions();
  
}
