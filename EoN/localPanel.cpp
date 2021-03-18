/*
  LocalPanel.h - Library untuk LocalPanel
  Dibuat Oleh : Sam March 18, 2021
*/

/* Dependencies */
#include "localPanel.h"

//global function
LocalPanel::LocalPanel(String id):_id(id){
  _modeMenu = MODE_MENU_UTAMA;
}

void LocalPanel::attachCmdIn(command *cmdIn){
  Serial.print("LocalPanel::attachCmdIn-");
  Serial.println(cmdInNbr);
  _cmdInput[cmdInNbr] = cmdIn;
  cmdInNbr++;
}

void LocalPanel::attachView(ViewLcd *view){
    Serial.println("LocalPanel::pasangView");
    _view = view;
  }

//private function
char LocalPanel::_getCommand(){
  char rawCmd = NO_KEY;
  for (int i=0; i < this->cmdInNbr; i++){
      rawCmd = _cmdInput[i]->ambilCode();
      if (rawCmd != NO_KEY){
          _prevCmd = rawCmd;
          break;
      }
  }
  return rawCmd;
}

void LocalPanel::menu(){
  char key = this->_getCommand();

}

