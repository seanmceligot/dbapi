#ifndef __CONTROLLER_HH
#define __CONTROLLER_HH

#include "appmem.hh"
#include "util.hh"
//TODO: Controll = Action
class Controller {
  void handle(Model* model, StrQueue args);
};

#endif
