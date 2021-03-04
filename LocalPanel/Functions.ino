/*
 * General functions description
 * sam March 01, 2021
*/
void setupParameter(){
  parameter param;
  Serial.println("LcdKeypadOOP-setupParameter");

  //fire Zone1.
  param.id = "Smoke-1";
  param.unit = "%";
  param.indexMenu = 1;
  param.value = 51;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  param.increment = 1.1;
  accessParameter.add(param);

  //fire Zone1.
  param.id = "Smoke-2";
  param.unit = "%";
  param.indexMenu = 2;
  param.value = 32;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  param.increment = 2;
  accessParameter.add(param);

  //fire Zone1.
  param.id = "Smoke-3";
  param.unit = "%";
  param.indexMenu = 3;
  param.value = 83;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  param.increment = 23;
  accessParameter.add(param);

  //fire Zone1.
  param.id = "Smoke-4";
  param.unit = "%";
  param.indexMenu = 4;
  param.value = 64;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  param.increment = 4;
  accessParameter.add(param);

  //fire Zone1.
  param.id = "Smoke-5";
  param.unit = "%";
  param.indexMenu = 5;
  param.value = 95;
  param.highRange = 100;
  param.lowRange = 0;
  param.highLimit = 80;
  param.lowLimit = 40;
  param.increment = 15;
  accessParameter.add(param);
}

void setupMenuUtama(){
  dataMenu  dtMenu;

  Serial.println("LcdKeypadOOP-setupMenuUtama");

  dtMenu.hasParameter = false;
  dtMenu.pesan1 ="Fire Protection System";
  dtMenu.pesan2 ="Salman Alfarisi";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 1";
  dtMenu.pesan2 ="Parameter 1";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 2";
  dtMenu.pesan2 ="Parameter 2";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 3";
  dtMenu.pesan2 ="Parameter 3";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 4";
  dtMenu.pesan2 ="Parameter 4";
  accessMenuUtama.add(dtMenu);

  dtMenu.hasParameter = true;
  dtMenu.pesan1 ="Fire Zone 5";
  dtMenu.pesan2 ="Parameter 5";
  accessMenuUtama.add(dtMenu);

}
