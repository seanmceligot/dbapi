#Boa:Frame:wxFrame1

from wxPython.wx import *
from wxPython.grid import *
import browse

def create(parent):
    return wxFrame1(parent)

[wxID_WXFRAME1, wxID_WXFRAME1LEFTPANEL, wxID_WXFRAME1PANEL3, 
 wxID_WXFRAME1TABLEGRID, wxID_WXFRAME1TOPPANEL, 
] = map(lambda _init_ctrls: wxNewId(), range(5))

class wxFrame1(wxFrame):
    def _init_utils(self):
        # generated method, don't edit
        pass

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wxFrame.__init__(self, id=wxID_WXFRAME1, name='', parent=prnt,
              pos=wxPoint(256, 167), size=wxSize(683, 445),
              style=wxDEFAULT_FRAME_STYLE, title='wxFrame1')
        self._init_utils()
        self.SetClientSize(wxSize(683, 445))
        EVT_CHAR(self, self.OnWxframe1Char)

        self.leftPanel = wxPanel(id=wxID_WXFRAME1LEFTPANEL, name='leftPanel',
              parent=self, pos=wxPoint(0, 56), size=wxSize(136, 392),
              style=wxTAB_TRAVERSAL)
        self.leftPanel.SetBackgroundColour(wxColour(216, 191, 216))

        self.topPanel = wxPanel(id=wxID_WXFRAME1TOPPANEL, name='topPanel',
              parent=self, pos=wxPoint(-1, -1), size=wxSize(681, 100),
              style=wxTAB_TRAVERSAL)
        self.topPanel.SetBackgroundColour(wxColour(255, 255, 255))

        self.panel3 = wxPanel(id=wxID_WXFRAME1PANEL3, name='panel3',
              parent=self, pos=wxPoint(136, 104), size=wxSize(544, 336),
              style=wxTAB_TRAVERSAL)
        self.panel3.SetBackgroundColour(wxColour(159, 159, 95))

        self.tableGrid = wxGrid(id=wxID_WXFRAME1TABLEGRID, name='tableGrid',
              parent=self.panel3, pos=wxPoint(8, 8), size=wxSize(528, 320),
              style=0)
        self.tableGrid.SetBackgroundColour(wxColour(192, 192, 192))

    def __init__(self, parent):
        self._init_ctrls(parent)
    def browse(self, tableName):
        b = browse.Browser()
        b.desc(tableName, self.tableGrid)

    def OnWxframe1Char(self, event):
        event.Skip()
