#!/usr/bin/env python
#Boa:App:BoaApp

from wxPython.wx import *

import dbFrame

modules ={'dbFrame': [1, 'Main frame of Application', 'dbFrame.py']}

class BoaApp(wxApp):
    def OnInit(self):
        wxInitAllImageHandlers()
        self.main = dbFrame.create(None)
        # needed when running from Boa under Windows 9X
        self.SetTopWindow(self.main)
        self.main.browse("people")
        self.main.Show(1)
        #self.main.Show();self.main.Hide();self.main.Show()
        return 1

def main():
    application = BoaApp(0)
    application.MainLoop()
    #application.browse("people")

if __name__ == '__main__':
    main()
