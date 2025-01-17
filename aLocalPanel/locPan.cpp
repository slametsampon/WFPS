/*
  locPan.h - Library untuk LocPan
  Dibuat Oleh : Sam March 18, 2021
*/

/* Dependencies */
#include "locPan.h"

//global function
LocPan::LocPan(String id):_id(id){

  _modeMenu = MODE_MENU_MAIN;
  _menuIndex = 0;
  this->_initPrevIndex();

}

void LocPan::attachDipAddr(DipAddr *dipAddr){
    Serial.println("LocPan::attachDipAddr(DipAddr *dipAddr)");
    _dipAddr = dipAddr;
}

int LocPan::getAddress(){
  return _dipAddr->getAddr();
}

void LocPan::init(){
  _dipAddr->init();

  for (int i=0; i < this->cmdInNbr; i++){
      _cmdInput[i]->init();
  }

  this->_setupMenu();
  this->_setupParameter();

}

void LocPan::info(){
  Serial.println("LocPan::info()=>Local Panel System");
  Serial.print("_id : ");
  Serial.println(_id);

  _dipAddr->info();

  for (int i=0; i < this->cmdInNbr; i++){
      _cmdInput[i]->info();
  }
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
 
void LocPan::updateParameter(){
  _dataParam = _accessParameter->getParam();

}

int LocPan::getException(){
    int exp = _exception;
    if (exp != NO_EXCEPTION)_exception = NO_EXCEPTION;
    return exp;
}

void LocPan::menu(){

  char key = this->_getCommand();

  switch (_modeMenu){
    case MODE_MENU_MAIN:
      this->_menuMain(key);
      break;
    case MODE_MENU_PARAMETER:
      this->_menuParameter(key);
      break;
    case MODE_CHANGE_PARAMETER:
      this->_menuChangeParameter(key);
      break;
    case NO_KEY:
    default:
        break;
  }
}

//private function

void LocPan::_initPrevIndex(){
  _prevMenuIndex = DEFAULT_INDEX;//default value
  _prevParamIndex = DEFAULT_INDEX;//default value
}

void LocPan::_menuMain(char key){
  dataMenu menuData;
  int idx;//for index

  if(this->_menuIndex == 0){
    this->_sendMenu(this->_menuIndex);//kirim menu ke serial port
    this->_viewMenu(this->_menuIndex);//tampilkan menu ke lcd
  }

  switch (key) // See which menu item is selected and execute that correS_Pond function
    {
        case SELECT:
          //Tempatkan menu di sini
          break;
        case UP:
          //naikkan index
          idx = this->_increaseIndex();
          this->_sendMenu(idx);//kirim menu ke serial port
          this->_viewMenu(idx);//tampilkan menu ke lcd
          break;
        case DOWN:
          //Turunkan index
          idx = this->_decreaseIndex();
          this->_sendMenu(idx);//kirim menu ke serial port
          this->_viewMenu(idx);//tampilkan menu ke lcd
          break;
        case LEFT:
          //Tempatkan menu di sini
          break;
        case RIGHT:
          //ke menu parameter
          menuData = _accessMenu->read(this->_menuIndex);
          if (menuData.isHasParam){
            _modeMenu = MODE_MENU_PARAMETER;
            this->updateParameter();//update dataParameter
            this->_initPrevIndex();
            this->_paramIndex = PARAMETER_VALUE;
            this->menu();
          }
          break;
        case NO_KEY://No Key
        default:
          break;
    }
}

void LocPan::_menuParameter(char key){
  int idx;//for index

  if(this->_paramIndex == PARAMETER_VALUE){
    idx = this->_paramIndex;
    this->_sendParameter(idx);//kirim parameter ke serial port
    this->_viewParameter(idx);//tampilkan parameter ke lcd
  }

  switch (key)
    {
      case SELECT:
        //Tempatkan menu di sini
        break;
      case UP:
        //Naikkan Index
        idx = this->_increaseIndex();
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case DOWN:
        //Naikkan Index
        idx = this->_decreaseIndex();
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case LEFT:
        //kembali ke menu utama
        _modeMenu = MODE_MENU_MAIN;
        this->_menuIndex = 0;
        this->menu();
        break;
      case RIGHT:
        if(!_accessParameter->isChangeAble(this->_paramIndex))return;//exit

        //ke menu ubah parameter
        _modeMenu = MODE_CHANGE_PARAMETER;
        this->_isParamChanged = true;
        this->menu();
        //this->_menuUbahParameter(paramData, NO_KEY);
        break;
      case NO_KEY://No Key
      default:
        break;
    }
}

void LocPan::_menuChangeParameter(char key){

  int idx = this->_paramIndex;

  if(this->_isParamChanged){
    this->_sendParameter(idx);//kirim parameter ke serial port 
    this->_viewParameter(idx);//tampilkan parameter ke lcd
  }

  switch (key)
    {
      case SELECT:
        //save change to parameter
        if (this->_isSaved){
          this->_isSaved = false;//false is saved
          this->_accessParameter->setParam(_dataParam);
          _view->viewMessage(0,0,"Parameter saved");//tampilkan pesan pada baris 0, kolom 0              
          Serial.println("Parameter saved");

          _exception = LOCAL_PARAMETER_EXCEPTION;//exception occur for parameter change          
          this->updateParameter();//update dataParameter
        }
        break;
      case UP:
        //Naikkan parameter
        this->_increaseParameter(idx);
        this->_isParamChanged = true;
        this->_isSaved = true;//true is need to be saved
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case DOWN:
        //turunkan parameter
        this->_decreaseParameter(idx);
        this->_isParamChanged = true;
        this->_isSaved = true;//true is need to be saved
        this->_sendParameter(idx);//kirim parameter ke serial port
        this->_viewParameter(idx);//tampilkan parameter ke lcd
        break;
      case LEFT:
        //kembali ke menu utama
        _modeMenu = MODE_MENU_PARAMETER;
        this->_paramIndex = PARAMETER_VALUE;
        this->menu();
        //this->_menuParameter(paramData, NO_KEY);
        break;
      case RIGHT:
        //ke menu ubah parameter
        break;
      case NO_KEY://No Key
      default:
        break;
    }
}

char LocPan::_getCommand(){
  char rawCmd = NO_KEY;
  for (int i=0; i < this->cmdInNbr; i++){
      rawCmd = _cmdInput[i]->getCode();
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
    else if(this->_modeMenu == MODE_CHANGE_PARAMETER){
      _view->viewMessage(0,0,"Change Parameter");
    }

    switch (index)
    {
    case PARAMETER_VALUE:
      _view->viewMessage(1,0,"value : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.value));//pesan pada baris 2
      break;
    
    case PARAMETER_LOW_RANGE:
      _view->viewMessage(1,0,"LoRng : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.lowRange));//pesan pada baris 2
      break;
    
    case PARAMETER_HIGH_RANGE:
      _view->viewMessage(1,0,"HiRng : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.highRange));//pesan pada baris 2
      break;
    
    case PARAMETER_LOW_LIMIT:
      _view->viewMessage(1,0,"LoLmt : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.lowLimit));//pesan pada baris 2
      break;
    
    case PARAMETER_HIGH_LIMIT:
      _view->viewMessage(1,0,"HiLmt : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.highLimit));//pesan pada baris 2
      break;
    
    case PARAMETER_INCREMENT:
      _view->viewMessage(1,0,"Incr : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.increment));//pesan pada baris 2
      break;
    
    case PARAMETER_ALFA_EMA:
      _view->viewMessage(1,0,"AlfaEma : ");//pesan pada baris 2
      _view->viewMessage(1,10,String(_dataParam.alfaEma));//pesan pada baris 2
      break;
    
    case PARAMETER_OPERATION_MODE:
      _view->viewMessage(1,0,"Mode : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.operationMode));//pesan pada baris 2
      break;
    
    case PARAMETER_ALARM:
      _view->viewMessage(1,0,"Alarm : ");//pesan pada baris 2
      _view->viewMessage(1,8,String(_dataParam.alarm));//pesan pada baris 2
      break;
    
    default:
      break;
    }
  }
}

void LocPan::_sendParameter(int index){
  
  String paramStr;
  boolean isUpdate = false;

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
    else if(this->_modeMenu == MODE_CHANGE_PARAMETER){
      Serial.println("Change Parameter");
    }

    switch (index)
    {
      case PARAMETER_VALUE:
        paramStr = "value : ";
        paramStr =  String(paramStr + _dataParam.value);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_LOW_RANGE:
        paramStr = "LoRng : ";
        paramStr =  String(paramStr + _dataParam.lowRange);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_HIGH_RANGE:
        paramStr = "HiRng : ";
        paramStr =  String(paramStr + _dataParam.highRange);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_LOW_LIMIT:
        paramStr = "LoLmt : ";
        paramStr =  String(paramStr + _dataParam.lowLimit);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_HIGH_LIMIT:
        paramStr = "HiLmt : ";
        paramStr =  String(paramStr + _dataParam.highLimit);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_INCREMENT:
        paramStr = "Incr : ";
        paramStr =  String(paramStr + _dataParam.increment);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_ALFA_EMA:
        paramStr = "AlfaEma : ";
        paramStr =  String(paramStr + _dataParam.alfaEma);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_OPERATION_MODE:
        paramStr = "Mode : ";
        paramStr =  String(paramStr + _dataParam.operationMode);
        Serial.println(paramStr);
        break;
      
      case PARAMETER_ALARM:
        paramStr = "Incr : ";
        paramStr =  String(paramStr + _dataParam.alarm);
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
      case MODE_MENU_MAIN:
        if (_menuIndex < (AccessDataMenu::getmenuNbr()-1)) _menuIndex++;
        else _menuIndex = 0;
        return _menuIndex;
        break;
      case MODE_MENU_PARAMETER:
        if (_paramIndex < PARAMETER_OPERATION_MODE) _paramIndex++;
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
      case MODE_MENU_MAIN:
        if (_menuIndex > 0) _menuIndex--;
        else _menuIndex = AccessDataMenu::getmenuNbr()-1;
        return _menuIndex;
        break;
      case MODE_MENU_PARAMETER:
        if (_paramIndex > PARAMETER_VALUE) _paramIndex--;
        else _paramIndex = PARAMETER_OPERATION_MODE;
        return _paramIndex;
        break;
      case MODE_CHANGE_PARAMETER:
        //Tempatkan menu di sini
        break;
      default:
          break;
    }
}

void LocPan::_increaseParameter(int idParam){
  float percentInc = _dataParam.increment/100.0;
  float range = _dataParam.highRange - _dataParam.lowRange;
  float increment = percentInc * range;
  float tempVal;

  switch (idParam)
  {
    case PARAMETER_LOW_RANGE:
      tempVal = _dataParam.lowRange + increment;
      if(tempVal < _dataParam.lowLimit) _dataParam.lowRange = tempVal;
      break;
    
    case PARAMETER_HIGH_RANGE:
      tempVal = _dataParam.highRange + increment;
      if(tempVal < _dataParam.highRange) _dataParam.highRange = tempVal;
      break;
    
    case PARAMETER_LOW_LIMIT:
      tempVal = _dataParam.lowLimit + increment;
      if(tempVal < _dataParam.highLimit) _dataParam.lowLimit = tempVal;
      break;
    
    case PARAMETER_HIGH_LIMIT:
      tempVal = _dataParam.highLimit + increment;
      if(tempVal < _dataParam.highRange) _dataParam.highLimit = tempVal;
      break;
    
    case PARAMETER_INCREMENT:
      _dataParam.increment = _dataParam.increment + _dataParam.increment * DELTA_INCREMENT;
      break;
    
    default:
      break;
  }
}

void LocPan::_decreaseParameter(int idParam){
  float percentInc = _dataParam.increment/100.0;
  float range = _dataParam.highRange - _dataParam.lowRange;
  float increment = percentInc * range;
  float tempVal;

  switch (idParam)
  {
    case PARAMETER_LOW_RANGE:
      tempVal = _dataParam.lowRange - increment;
      if(tempVal > _dataParam.lowRange) _dataParam.lowRange = tempVal;
      break;
    
    case PARAMETER_HIGH_RANGE:
      tempVal = _dataParam.highRange - increment;
      if(tempVal > _dataParam.highLimit) _dataParam.highRange = tempVal;
      break;
    
    case PARAMETER_LOW_LIMIT:
      tempVal = _dataParam.lowLimit - increment;
      if(tempVal > _dataParam.lowRange) _dataParam.lowLimit = tempVal;
      break;
    
    case PARAMETER_HIGH_LIMIT:
      tempVal = _dataParam.highLimit - increment;
      if(tempVal > _dataParam.lowLimit) _dataParam.highLimit = tempVal;
      break;
    
    case PARAMETER_INCREMENT:
      _dataParam.increment = _dataParam.increment - _dataParam.increment * DELTA_INCREMENT;
      break;
    
    default:
      break;
  }
}

void LocPan::_setupParameter(){
  param dtParam;
  Serial.println("LocPan::_setupParameter()");

  //fire Zone1.
  dtParam.unit = "%";
  dtParam.value = 51;
  dtParam.highRange = 100;
  dtParam.lowRange = 0;
  dtParam.highLimit = 80;
  dtParam.lowLimit = 40;
  dtParam.alfaEma = ALFA_EMA;
  dtParam.alarm = NO_ALARM;
  dtParam.increment = 2.0;

  String locId = "ZONE-";
  locId = String(locId + _dipAddr->getAddr());

  _accessParameter->init(locId, dtParam);
}

void LocPan::_setupMenu(){
  String locId = "Fire Zone-";
  dataMenu  dtMenu;

  Serial.println("LocPan::_setupMenu()");

  dtMenu.isHasParam = false;
  dtMenu.Messages_0 ="Fire Protection System";
  dtMenu.Messages_1 ="Salman Alfarisi";
  _accessMenu->add(dtMenu);

  //specific zone configuration  
  dtMenu.isHasParam = true;
  dtMenu.Messages_0 ="Fire Zone-1";
  dtMenu.Messages_1 ="Parameters";

  locId = String(locId + _dipAddr->getAddr());
  locId.toCharArray(dtMenu.Messages_0,16);
  _accessMenu->add(dtMenu);
}