/*
  locPan.h - Library untuk LocPan
  Dibuat Oleh : Sam March 18, 2021
*/

/* Dependencies */
#include "locPan.h"

//global function
LocPan::LocPan(String id):_id(id){
  _modeMenu = MODE_MENU_UTAMA;
}

void LocPan::info(){
  Serial.println(_id);
}

void LocPan::attachCmdIn(command *cmdIn){
  Serial.print("LocPan::attachCmdIn-");
  Serial.println(cmdInNbr);
  _cmdInput[cmdInNbr] = cmdIn;
  cmdInNbr++;
}

void LocPan::attachView(ViewLcd *view){
    Serial.println("LocPan::attachView(ViewLcd *view)");
    _view = view;
  }

void LocPan::attachModelMenu(AccessDataMenu *accessMenu){
    Serial.println("LocPan::attachModelMenu(AccessDataMenu *accessMenu)");
    _accessMenu = accessMenu;
  }
 
void LocPan::attachModelParameter(AccessParam *accessParameter){
    Serial.println("LocPan::attachModelParameter(AccessParam *accessParameter)");
    _accessParameter = accessParameter;
  }
 
void LocPan::menu(){

  char key = this->_getCommand();

  switch (_modeMenu)
    {
      case MODE_MENU_UTAMA:
        this->_menuMain(key);
        break;
      case MODE_MENU_PARAMETER:
        this->_menuParameter(key);
        break;
      case MODE_UBAH_PARAMETER:
        this->_menuChangeParameter(key);
        break;
      case 'N':
      default:
          break;
    }
}

//private function

void LocPan::_menuMain(char key){
  String keyStr = "";
  dataMenu menuData;
  int idx;//for index

  if(this->_menuIndex == 0){
    this->_sendMenu(this->_menuIndex);//kirim menu ke serial port
    this->_viewMenu(this->_menuIndex);//tampilkan menu ke lcd
  }

  switch (key) // See which menu item is selected and execute that correS_Pond function
    {
        case 'S':
          //Tempatkan menu di sini
          break;
        case 'U':
          //naikkan index
          idx = this->_increaseIndex();
          this->_sendMenu(idx);//kirim menu ke serial port
          this->_viewMenu(idx);//tampilkan menu ke lcd
          break;
        case 'D':
          //Turunkan index
          idx = this->_decreaseIndex();
          this->_sendMenu(idx);//kirim menu ke serial port
          this->_viewMenu(idx);//tampilkan menu ke lcd
          break;
        case 'L':
          //Tempatkan menu di sini
          break;
        case 'R':
          //ke menu parameter
          menuData = _accessMenu->read(this->_menuIndex);
          if (menuData.isHasParam){
            _modeMenu = MODE_MENU_PARAMETER;
            this->_paramIndex = PARAMETER_VALUE;
            this->menu();
          }
          break;
        case 'N'://No Key
        default:
          break;
    }
}

void LocPan::_menuParameter(char key){
  String keyStr = "";
  int idx;//for index

  if(this->_paramIndex == PARAMETER_VALUE){
    idx = this->_paramIndex;
    this->_sendMenu(idx);//kirim parameter ke serial port
    this->_viewMenu(idx);//tampilkan parameter ke lcd
  }

  switch (key)
    {
      case 'S':
        //Tempatkan menu di sini
        break;
      case 'U':
        //Naikkan Index
        idx = this->_increaseIndex();
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case 'D':
        //Naikkan Index
        idx = this->_decreaseIndex();
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case 'L':
        //kembali ke menu utama
        _modeMenu = MODE_MENU_UTAMA;
        this->_menuIndex = 0;
        this->menu();
        break;
      case 'R':
        //ke menu ubah parameter
        _modeMenu = MODE_UBAH_PARAMETER;
        this->menu();
        //this->_menuUbahParameter(paramData, NO_KEY);
        break;
      case 'N'://No Key
      default:
        break;
    }
}

void LocPan::_menuChangeParameter(char key){
  String keyStr = "";
  int idx, idxParam;
  param paramData = _accessParameter->getParam();

  switch (key)
    {
      case 'S':
        //save change to parameter
        if (this->_isSaved){
          this->_isSaved = false;//false is saved
          //idxParam = this->_accessParameter->getIndexParameter();
          //this->_accessParameter->setParameter(idxParam);
          _view->viewMessage(0,0,"Parameter saved");//tampilkan pesan pada baris 0, kolom 0              
          Serial.println("Parameter saved");          
        }
        break;
      case 'U':
        //Naikkan parameter
        idx = this->_paramIndex;
        //paramData = this->_accessParameter->increaseParameter(paramData,idx);
        this->_isParamChanged = true;
        this->_isSaved = true;//true is need to be saved
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case 'D':
        //turunkan parameter
        idx = this->_paramIndex;
        //paramData = this->_accessParameter->decreaseParameter(paramData,idx);
        this->_isParamChanged = true;
        this->_isSaved = true;//true is need to be saved
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case 'L':
        //kembali ke menu utama
        _modeMenu = MODE_MENU_PARAMETER;
        this->_paramIndex = PARAMETER_VALUE;
        this->menu();
        //this->_menuParameter(paramData, NO_KEY);
        break;
      case 'R':
        //ke menu ubah parameter
        break;
      case 'N'://No Key
      default:
        break;
    }
}

char LocPan::_getCommand(){
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

void LocPan::_viewMenu(int index){
    dataMenu tempMenu;
    if(_prevMenuIndex != index){
      tempMenu = _accessMenu->read(index);
      _view->clearView();//hapus semua tampilan dulu
      _view->viewMessage(0,0,tempMenu.Messages_0);//pesan1 pada baris 1
      _view->viewMessage(1,0,tempMenu.Messages_1);//pesan2 pada baris 2
      _prevMenuIndex = index;
    }
  }

void LocPan::_sendMenu(int index){
    dataMenu tempMenu;
    if(_prevMenuIndex != index){
      tempMenu = _accessMenu->read(index);
      Serial.print("index : ");
      Serial.println(index);
      Serial.println(tempMenu.Messages_0);
      Serial.println(tempMenu.Messages_1);

      //_prevMenuIndex = index;
    }
  }

void LocPan::_viewParameter(int index){
  //String paramStr;
  boolean isUpdate = false;
  param dataParam = _accessParameter->getParam();

  //check if display need to be updated
  if(_prevParamIndex != index){
    _prevParamIndex = index;
    if (this->_modeMenu == MODE_MENU_PARAMETER) isUpdate = true;
  } 
  else{
    if (this->_isParamChanged)isUpdate = true;
    this->_isParamChanged = false;
  }

  if(isUpdate){
    isUpdate = false;
    _prevParamIndex = index;
    _view->clearView();//hapus semua tampilan dulu

    if(this->_modeMenu == MODE_MENU_PARAMETER){
      _view->viewMessage(0,0,_accessParameter->toString());
    }
    else if(this->_modeMenu == MODE_UBAH_PARAMETER){
      _view->viewMessage(0,0,"Change Parameter");
    }

    switch (index)
    {
    case PARAMETER_VALUE:
      _view->viewMessage(1,0,"Value : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(dataParam.value));//pesan pada baris 2
      break;
    
    case PARAMETER_LOW_RANGE:
      _view->viewMessage(1,0,"LoRng : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(dataParam.lowRange));//pesan pada baris 2
      break;
    
    case PARAMETER_HIGH_RANGE:
      _view->viewMessage(1,0,"HiRng : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(dataParam.highRange));//pesan pada baris 2
      break;
    
    case PARAMETER_LOW_LIMIT:
      _view->viewMessage(1,0,"LoLmt : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(dataParam.lowLimit));//pesan pada baris 2
      break;
    
    case PARAMETER_HIGH_LIMIT:
      _view->viewMessage(1,0,"HiLmt : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(dataParam.highLimit));//pesan pada baris 2
      break;
    
    case PARAMETER_INCREMENT:
      _view->viewMessage(1,0,"Incr : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(dataParam.increment));//pesan pada baris 2
      break;
    
    default:
      break;
    }
  }
}

void LocPan::_sendParameter(int index){
  
  String paramStr;
  boolean isUpdate = false;
  param dataParam = _accessParameter->getParam();

  //check if display need to be updated
  if(_prevParamIndex != index){
    //_prevParamIndex = index;
    if (this->_modeMenu == MODE_MENU_PARAMETER) isUpdate = true;
  } 
  else{
    if (this->_isParamChanged)isUpdate = true;
    //this->_isParamChanged = false;
  }

  if(isUpdate){
    if(this->_modeMenu == MODE_MENU_PARAMETER){
      Serial.println(_accessParameter->toString());
    }
    else if(this->_modeMenu == MODE_UBAH_PARAMETER){
      Serial.println("Change Parameter");
    }

    switch (index)
    {
      case PARAMETER_VALUE:
        paramStr = "Value : ";
        paramStr =  String(paramStr + dataParam.value);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_LOW_RANGE:
        paramStr = "LoRng : ";
        paramStr =  String(paramStr + dataParam.lowRange);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_HIGH_RANGE:
        paramStr = "HiRng : ";
        paramStr =  String(paramStr + dataParam.highRange);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_LOW_LIMIT:
        paramStr = "LoLmt : ";
        paramStr =  String(paramStr + dataParam.lowLimit);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_HIGH_LIMIT:
        paramStr = "HiLmt : ";
        paramStr =  String(paramStr + dataParam.highLimit);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_INCREMENT:
        paramStr = "Incr : ";
        paramStr =  String(paramStr + dataParam.increment);
        Serial.println(paramStr);
        break;
      
      default:
        break;
      }
    }
  }

int LocPan::_increaseIndex(){
  switch (_modeMenu)
    {
      case MODE_MENU_UTAMA:
        if (_menuIndex < (AccessDataMenu::getmenuNbr()-1)) _menuIndex++;
        else _menuIndex = 0;
        return _menuIndex;
        break;
      case MODE_MENU_PARAMETER:
        if (_paramIndex < PARAMETER_INCREMENT) _paramIndex++;
        else _paramIndex = PARAMETER_VALUE;
        return _paramIndex;
        break;
      default:
          break;
    }
}
 
int LocPan::_decreaseIndex(){
  switch (_modeMenu)
    {
      case MODE_MENU_UTAMA:
        if (_menuIndex > 0) _menuIndex--;
        else _menuIndex = AccessDataMenu::getmenuNbr()-1;
        return _menuIndex;
        break;
      case MODE_MENU_PARAMETER:
        if (_paramIndex > PARAMETER_VALUE) _paramIndex--;
        else _paramIndex = PARAMETER_INCREMENT;
        return _paramIndex;
        break;
      case MODE_UBAH_PARAMETER:
        //Tempatkan menu di sini
        break;
      default:
          break;
    }
}
