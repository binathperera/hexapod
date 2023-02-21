
void revert(){  //Pulls the body to the correct position
  d1.setPWM(0,0,angleToPulse(90));
  L1_stat=false;
  d2.setPWM(0,0,angleToPulse(90));
  L2_stat=false;
  d1.setPWM(4,0,angleToPulse(90));
  d2.setPWM(4,0,angleToPulse(90));
  d1.setPWM(8,0,angleToPulse(90));
  L5_stat=false;
  d2.setPWM(8,0,angleToPulse(90));
  L6_stat=false;
  }
void position_legs(){ //Positions the legs 1,2,5 and 6 by lifting and placing
  if(!L1_stat){
    d1.setPWM(1,0,angleToPulse(45));        //Lift leg 1
    d1.setPWM(0,0,angleToPulse(L1_angle));  //Position leg 1
    d1.setPWM(1,0,angleToPulse(legPlacementAngle));        //Place leg 1
    L1_stat=true;
    }
  delay(100);
  
  if(!L2_stat){
    d2.setPWM(1,0,angleToPulse(135));        //Lift leg 2
    d2.setPWM(0,0,angleToPulse(L2_angle));  //Position leg 2
    d2.setPWM(1,0,angleToPulse(180-legPlacementAngle));        //Place leg 2
     L2_stat=true;
    }
 
  delay(100);
  
  if(!L5_stat){
    d1.setPWM(9,0,angleToPulse(45));        //Lift leg 5
    delay(50);
    d1.setPWM(8,0,angleToPulse(L5_angle));  //Position leg 5
    delay(100);
    d1.setPWM(9,0,angleToPulse(legPlacementAngle));        //Place leg 5
    delay(10);
    L5_stat=true;
    }
  
  if(!L6_stat){
    d2.setPWM(9,0,angleToPulse(135));        //Lift leg 6
    d2.setPWM(8,0,angleToPulse(L6_angle));  //Position leg 6
    d2.setPWM(9,0,angleToPulse(180-legPlacementAngle));        //Place leg 6
    L6_stat=true;
    }
  
  delay(100);
}

void moveForward(){
  lcd.clear();
  unblink();
  printLCD("FORWARD",1,3);
  mov_set1(1);
  delay(100);
  
  mov_set2(1);
  delay(100);
  revert();
  delay(100);
  }

  
void moveBackward(){
  lcd.clear();
  unblink();
  printLCD("REVERSE",1,3);
  mov_set1(2);
  delay(100);
  
  mov_set2(2);
  delay(100);
  revert();
  delay(100);

  }

  
void turnLeft(){
  lcd.clear();
  unblink();
  printLCD("Turning",1,2);
  printLCD("LEFT",2,3);
  mov_set1(3);
  delay(100);
  mov_set2(3);
  delay(100);
  revert();
  delay(100);
  }

  
void turnRight(){
  lcd.clear();

  
  unblink();
  printLCD("Turning",1,2);
  printLCD("RIGHT",2,3);
  mov_set1(4);
  delay(100);
  mov_set2(4);
  delay(100);
  revert();
  delay(100);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mov_set1(int mode){
  if(mode==1){//Forward
    if(!L1_stat){//If L1 is not in default position.
      d1.setPWM(1, 0, angleToPulse(45) );//Lift leg 1
      }
    d2.setPWM(5, 0, angleToPulse(135) );  //Lift leg 4
    d1.setPWM(9, 0, angleToPulse(45) );  //Lift leg 5
    delay(500);
    d1.setPWM(0, 0, angleToPulse(90+STEPLENGTH) );//Turn leg 1
    d2.setPWM(4, 0, angleToPulse(90-STEPLENGTH) );//Turn leg 4
    d1.setPWM(8, 0, angleToPulse(90+STEPLENGTH) );//Turn leg 5
    delay(500);
    d1.setPWM(2, 0, angleToPulse(80) );//turn feet 1
    d2.setPWM(6, 0, angleToPulse(100) );//turn feet 4
    d1.setPWM(10, 0, angleToPulse(80) );//turn feet 5
    delay(500);
    d1.setPWM(1, 0, angleToPulse(legPlacementAngle) );//Keep leg 1
    d2.setPWM(5, 0, angleToPulse(180-legPlacementAngle) );//Keep leg 4
    d1.setPWM(9, 0, angleToPulse(legPlacementAngle) );//Keep leg 5
    delay(500);
    }
  if(mode==2){//Reverse
    d1.setPWM(1, 0, angleToPulse(45) );      //Lift leg 1
    d2.setPWM(5, 0, angleToPulse(135) );      //Lift leg 4

    if(!L5_stat){//If L5 is not in default position.
          d1.setPWM(9, 0, angleToPulse(45) );//Lift leg 5
      }
    delay(500);
    d1.setPWM(0, 0, angleToPulse(90-STEPLENGTH) );     //Turn leg 1
    d2.setPWM(4
    , 0, angleToPulse(90+STEPLENGTH) );     //Turn leg 4
    d1.setPWM(8, 0, angleToPulse(90-STEPLENGTH) );     //Turn leg 5
    delay(500);
    d1.setPWM(1, 0, angleToPulse(legPlacementAngle) ); //Place leg 1
    d2.setPWM(5, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 4
    d1.setPWM(9, 0, angleToPulse(legPlacementAngle) ); //Place leg 5
    delay(500);
    }
  if(mode==3){//Turn Left
    d1.setPWM(1, 0, angleToPulse(45) ); //Lift leg 1
    d2.setPWM(5, 0, angleToPulse(135) ); //Lift leg 4
    if(!L5_stat){ //If L5 is not in default position.
      d1.setPWM(9, 0, angleToPulse(45) ); //Lift leg 5
    }
    delay(500);
    d1.setPWM(0, 0, angleToPulse(90-STEPLENGTH) );//Turn leg 1
    d2.setPWM(4, 0, angleToPulse(90-STEPLENGTH) ); //Turn leg 4
    d1.setPWM(8, 0, angleToPulse(90-STEPLENGTH) );//Turn leg 5
    delay(500);
    d1.setPWM(1, 0, angleToPulse(legPlacementAngle) );//Place leg 1
    d2.setPWM(5, 0, angleToPulse(180-legPlacementAngle) );//Place leg 4
    d1.setPWM(9, 0, angleToPulse(legPlacementAngle) );//Place leg 5
    delay(500);
    }
  if(mode==4){//Turn Right
    if(!L1_stat){ //If L1 is not in default position.
      d1.setPWM(1, 0, angleToPulse(45) ); //Lift leg 1
    }
    d2.setPWM(5, 0, angleToPulse(135) );   //Lift leg 4
    d1.setPWM(9, 0, angleToPulse(45) );   //Lift leg 5
    delay(500);
    d1.setPWM(0, 0, angleToPulse(90+STEPLENGTH) );   //Turn leg 1
    d2.setPWM(4, 0, angleToPulse(90+STEPLENGTH) );  //Turn leg 4
    d1.setPWM(8, 0, angleToPulse(90+STEPLENGTH) );   //Turn leg 5
    delay(500);
    d1.setPWM(1, 0, angleToPulse(legPlacementAngle) );   //Place leg 1  
    d2.setPWM(5, 0, angleToPulse(180-legPlacementAngle) );   //Place leg 4
    d1.setPWM(9, 0, angleToPulse(legPlacementAngle) );   //Place leg 5
    delay(500);
    }
  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mov_set2(int mode){
  if(mode==1){//Forward
    if(!L2_stat){ //If L2 is not in default position.
      d2.setPWM(1, 0, angleToPulse(135) );  //Lift leg 2
    }
    d1.setPWM(5, 0, angleToPulse(45) );  //Lift leg 3
    d2.setPWM(9, 0, angleToPulse(135) );  //Lift leg 6
    delay(500);
    d2.setPWM(0, 0, angleToPulse(90-STEPLENGTH) ); //Turn leg 2
    d1.setPWM(4, 0, angleToPulse(90+STEPLENGTH) ); //Turn leg 3
    d2.setPWM(8, 0, angleToPulse(90-STEPLENGTH) ); //Turn leg 6
    delay(500);
    d2.setPWM(1, 0, angleToPulse(180-legPlacementAngle) );  //Place leg 2 
    d1.setPWM(5, 0, angleToPulse(legPlacementAngle) );  //Place leg 3  
    d2.setPWM(9, 0, angleToPulse(180-legPlacementAngle) );  //Place leg 6
    delay(500);
    }
  if(mode==2){//Reverse
    d2.setPWM(1, 0, angleToPulse(135) ); //Lift leg 2
    d1.setPWM(5, 0, angleToPulse(45) ); //Lift leg 3
    if(!L6_stat){ //If L6 is not in default position.
      d2.setPWM(9, 0, angleToPulse(135) ); //Lift leg 6
    }
    delay(500);
    d2.setPWM(0, 0, angleToPulse(90+STEPLENGTH) ); //Turn leg 2
    d1.setPWM(4, 0, angleToPulse(90-STEPLENGTH) ); //Turn leg 3
    d2.setPWM(8, 0, angleToPulse(90+STEPLENGTH) ); //Turn leg 6
    delay(500);
    d2.setPWM(1, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 2 
    d1.setPWM(5, 0, angleToPulse(legPlacementAngle) ); //Place leg 3 
    d2.setPWM(9, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 6 
    delay(500);
    }
  if(mode==3){//Turn Left
    if(!L2_stat){ //If L2 is not in default position.
      d2.setPWM(1, 0, angleToPulse(135) ); //Lift leg 2
    }
    d1.setPWM(5, 0, angleToPulse(45) ); //Lift leg 3
    d2.setPWM(9, 0, angleToPulse(135) ); //Lift leg 6
    delay(500);
    d2.setPWM(0, 0, angleToPulse(90-STEPLENGTH) ); //Turn leg 2
    d1.setPWM(4, 0, angleToPulse(90-STEPLENGTH)); //Turn leg 3
    d2.setPWM(8, 0, angleToPulse(90-STEPLENGTH) ); //Turn leg 6
    delay(500);
    d2.setPWM(1, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 2
    d1.setPWM(5, 0, angleToPulse(legPlacementAngle) ); //Place leg 3 
    d2.setPWM(9, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 6 
    delay(500);
    }
  if(mode==4){//Turn Right
    d2.setPWM(1, 0, angleToPulse(135) ); //Lift leg 2
    d1.setPWM(5, 0, angleToPulse(45) ); //Lift leg 3
    if(!L6_stat){ //If L6 is not in default position.
      d2.setPWM(9, 0, angleToPulse(135) ); //Lift leg 6
    }
    delay(500);
    d2.setPWM(0, 0, angleToPulse(90+STEPLENGTH) ); //Turn leg 2
    d1.setPWM(4, 0, angleToPulse(90+STEPLENGTH)); //Turn leg 3
    d2.setPWM(8, 0, angleToPulse(90+STEPLENGTH) ); //Turn leg 6
    delay(500);
    d2.setPWM(1, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 2
    d1.setPWM(5, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 3
    d2.setPWM(9, 0, angleToPulse(180-legPlacementAngle) ); //Place leg 6
    delay(500);
    }
  }
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


