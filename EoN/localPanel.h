/*
  LocalPanel.h - Library untuk LocalPanel
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 2021
*/
#ifndef LocalPanel_h
#define LocalPanel_h

#include "Arduino.h"
#include "KeyPad.h"
#include "viewLcd.h"
#include "src\command\command.h"

const int MODE_MENU_UTAMA = 1;
const int MODE_MENU_PARAMETER = 2;
const int MODE_UBAH_PARAMETER = 3;

class LocalPanel
{
  public:
    static unsigned char cmdInNbr;
    static unsigned char getCmdInNbr(){
      return cmdInNbr;
    }
    LocalPanel(String);//constructor
    void attachCmdIn(command*);//Pasang command, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachView(ViewLcd*);//Pasang View, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void menu();
  private:
    String _id;
    KeyPad *_keyPad;
    command *_cmdInput[MAX_CMD_INPUT];
    ViewLcd    *_view;
    char _prevCmd;
    int _modeMenu = MODE_MENU_UTAMA;

    char _getCommand();
};//end of class
#endif
