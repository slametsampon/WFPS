/*
  LocalPanel.h - Library untuk LocalPanel
  Ini adalah bagian dari MVC (Model View Control) pattern design
  Dibuat Oleh : Sam Feb 2021
*/
#ifndef LocalPanel_h
#define LocalPanel_h

#include  "Arduino.h"
#include  "viewLcd.h"
#include  "Model.h"
#include  "src\command\command.h"
#include  "src\analogInput\param.h"

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
    void attachModelMenu(AccessDataMenu*);//Pasang Model menu, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void attachModelParameter(AccessParam*);//Pasang Model parameter, penggunaan pointer ini sangat mutlak (JIKA TIDAK ERROR !!!!)
    void menu();
    void info();

  private:
    String _id;
    AccessDataMenu *_accessMenu;
    AccessParam *_accessParameter;
    command *_cmdInput[MAX_CMD_INPUT];
    ViewLcd    *_view;
    char _prevCmd;
    int _modeMenu = MODE_MENU_UTAMA;
    int _menuIndex, _prevMenuIndex, _paramIndex, _prevParamIndex;
    boolean _isParamChanged, _isSaved;

    void _viewMenu(int);//Tampilkan Menu ke LCD sesuai index-menu
    void _sendMenu(int);//Kirim Menu ke serial port sesuai index-menu
    void _viewParameter(int);//Tampilkan Parameter ke LCD sesuai index-Parameter
    void _sendParameter(int);//Kirim Parameter ke serial port sesuai index-Parameter
    int _increaseIndex();
    int _decreaseIndex();
    char _getCommand();
    void _menuMain(char);
    void _menuParameter(char);
    void _menuChangeParameter(char);
};//end of class
#endif
