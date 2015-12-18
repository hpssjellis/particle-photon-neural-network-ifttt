//PUT YOUR GLOBAL VARIABLES HERE

String myType = "EntryNode";    // Very important
                    // can only be one of the following
                    // "StartNode" max = 1,  sent instruction by "DO" IFTTT 
                    // "EndNode" max = 8,    sent Instructions by "DO" IFTTTT
                    // "NormalNade" no max   runs automatically
int myUniqueNodeNumber = 0; // This has to be unique for each node "Photon"
                            // entry string is 8 digits for 8 entry's example 10000000



volatile bool myFlag1 = false;
volatile bool myFlag2 = false;
volatile bool myFlag3 = false;
volatile bool myStable1 = false;

          bool ifEntryNodeThenFire = false;
          int myCount = 0;
          int myA0 = 0;  // range from 0-4095
          int myFireLimit = 2000;
          int fire0, fire1, fire2, fire3, fire4, fire5, fire6, fire7 = 0;
          // 0 = do not fire, 1= fire
          
       

Timer myTimerD7(10000, myD7Function);   
// slow down the number of published events sent to IFTTT
// presently set to one event every 30 seconds
// after myTimerD7.reset() waits 30 seconds to activate myD7Function

Timer myTimerStable(500, myStableFunction);   

 
Timer myTimer3(163, my3Function);   // prime number frequency

// 59   157   269   389   509   643   773   919   Hz
 
 
  
void myStableFunction(){
    
    myFlag2 = true; //resets the flag

}  
      
 void my3Function(){
    
    myFlag3 = true; //resets the flag

}  
      
     
   
void myD7Function(){
    
    myFlag1 = true; //resets the flag

}  
     
    
    
 // Any general setup stuff goes here   
void setup(){
    
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
   // pinMode(A0, INPUT_PULLDOWN );  //strangely not set for analog read


    myTimerD7.start(); 
    // activate the timer to slow information to IFTTT

    myTimerStable.start(); 
     
    Particle.subscribe("x-Fire", myNeuralFunction, MY_DEVICES);  // private
    
    // Particle.subscribe("x-fire", myNeuralFunction);  // public
    // expecting x= G for good or B for bad learning
    // expecting Fire= #### the analog read value that sets a node fire.
    if ( myType == "EntryNode"){   // only load this for starting nodes
          Particle.subscribe("my-EntryNode", myEntryFunction, MY_DEVICES);  // private will probably have to make public
    }

    
}


void myNeuralFunction(const char *event, const char *data){   
    
    
    String myCode = String(data);  
    myCode.toUpperCase();   
    // int pinNumber = myCode.charAt(0);

    if (myCode.startsWith("G")){myStable1 = true;}  //set boolean flag to true if Good
    // Sent by "DO" IFTTT
 
    if (myCode.startsWith("P")){
        myStable1 = false;   //set boolean flag to true if Good
        myFlag3 = true; //get the prime number frequency  node on/off routine going
        myTimerStable.stop();   // reset timer to start fresh
        myTimer3.reset();   // reset timer to start fresh
        }  
    
    
    if (myCode.startsWith("B")){          //set boolean flag to false if Bad  
        myStable1 = false;
        myFlag3 = false;
        myTimerStable.reset();   // reset timer to start fresh
        myTimer3.stop();   // reset timer to start fresh
        Particle.publish("Log-this-to-google-drive", String(myFlag2), 60, PRIVATE);
    }
    // Sent by "DO" IFTTT  
    
    
    // String  myActivity = myCode.substring(2,6);     // take 4 characters starting at the 3rd.
     
    // Following sets the 2nd and on characters to integers
    String myOptional = myCode.substring(2);      
    myFireLimit = myOptional.toInt(); 

    myTimerD7.reset();   // reset timer to start fresh
    data = "STOP";
    // change the data so that the function does not fire again
    
}






void myEntryFunction(const char *event, const char *data){   
    
    String myEntryCode = String(data);  
    myEntryCode.toUpperCase();  
    String  myActivity = myEntryCode.substring(myUniqueNodeNumber, myUniqueNodeNumber+1); 
    
    if (myActivity == "1"){
        // trun on this node until changed
       ifEntryNodeThenFire = true;
    } else {
        // turn this node off
       ifEntryNodeThenFire = false; 
    }
    
   myFireLimit = 5000;
   // set the firelimit above what is possible so that this node is not controlled by any inputs
    
    
}










void loop(){
     
    // your looping stuff goes here
    delay(10);     // just to slow things down a bit. remove later
    
    myA0 = analogRead(A0);  // read the voltage at A0 as a range form 0-4095

   if (myA0 >= myFireLimit || ifEntryNodeThenFire){
       
        RGB.brightness(200);    // 1=very low light, 255 = max
        // communicate that this node is firing   
       
       
        if (fire0 >= 1){digitalWrite(D0, HIGH);} else {digitalWrite(D0, LOW);}
        if (fire1 >= 1){digitalWrite(D1, HIGH);} else {digitalWrite(D1, LOW);}
        if (fire2 >= 1){digitalWrite(D2, HIGH);} else {digitalWrite(D2, LOW);}
        if (fire3 >= 1){digitalWrite(D3, HIGH);} else {digitalWrite(D3, LOW);}
        if (fire4 >= 1){digitalWrite(D4, HIGH);} else {digitalWrite(D4, LOW);}
        if (fire5 >= 1){digitalWrite(D5, HIGH);} else {digitalWrite(D5, LOW);}
        if (fire6 >= 1){digitalWrite(D6, HIGH);} else {digitalWrite(D6, LOW);}
        if (fire7 >= 1){digitalWrite(D7, HIGH);} else {digitalWrite(D7, LOW);}
       
        } else {
           RGB.brightness(1);    // 1=very low light, 255 = max
       // communicate that this mode is NOT firing
   }






    if (myStable1 && myFlag1){
  
        String myData = "myA0 = " + String(myA0) + " Limit = "  + String(myFireLimit);
        Particle.publish("Log-this-to-google-drive", myData, 60, PRIVATE);
        
        //Particle.publish("Log-this-to-google-drive", String(myA0), 60, PRIVATE);
        //Particle.publish("Log-this-to-google-drive", String(myFireLimit), 60, PRIVATE);
        // Particle.publish("Log-this-to-google-drive", String("Node001 "+myA0), 60, PUBLIC); 
        // this does not work combine strings earlier
             
        myTimerD7.reset();   // reset timer to start fresh
        myFlag1 = false;      // reset timer loop variable
        

        // digitalWrite(D7, LOW); // Used for debugging
         
    }
    
    
    
    
    
    
    if (!myStable1 && myFlag2){    // If the final result is not stable 
                          // then randomly change the Outputs
        
        // digitalWrite(D7, HIGH); // Used for debugging

                           
        int r = random(1, 20);
      
        //Particle.publish("Log-this-to-google-drive", String(r), 60, PRIVATE);     
        // see the random number in google drtive.
        // change the timer to 4000 from 500 before using publish.
        
        
        if (r==1){  fire0 = 0;  }  
        if (r==2){  fire0 = 1;  }  
        if (r==3){  fire1 = 0;  }  
        if (r==4){  fire1 = 1;  }  
        if (r==5){  fire2 = 0;  }  
        if (r==6){  fire2 = 1;  }  
        if (r==7){  fire3 = 0;  }  
        if (r==8){  fire3 = 1;  }  
        if (r==9){  fire4 = 0;  }  
        if (r==10){ fire4 = 1;  }  
        if (r==11){ fire5 = 0;  }  
        if (r==12){ fire5 = 1;  }  
        if (r==13){ fire6 = 0;  }  
        if (r==14){ fire6 = 1;  }  
        if (r==15){ fire7 = 0;  }  
        if (r==16){ fire7 = 1;  }  
       // if (r>16){digitalWrite(D7, HIGH);} else {digitalWrite(D7, LOW);}
                  
        myTimerStable.reset();   // reset timer to start fresh
        myFlag2 = false;      // reset timer loop variable   
    }
    
    
  
    
    if (!myStable1 && myFlag3){    // If the final result is not stable 
    
    if (fire7 == 1){    // take D7 and turn it off or on
        fire7 = 0;
    } else {fire7 = 1;}
    
    
                      
        myTimer3.reset();   // reset timer to start fresh
        myFlag3 = false;      // reset timer loop variable   
    }
    
    
    
  
}  // end main loop
