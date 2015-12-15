//PUT YOUR GLOBAL VARIABLES HERE
volatile bool myFlag1 = false;
volatile bool myStable1 = false;
          int myCount = 0;
          int myA0 = 0;  // range from 0-4095
          int myFireLimit = 2000;

Timer myTimerD7(7000, myD7Function);   
// slow down the number of published events sent to IFTTT
// presently set to one event every 7 seconds
// after myTimerD7.reset() waits 7 seconds to activate myD7Function

  
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

     
    Particle.subscribe("x-Fire", myNeuralFunction, MY_DEVICES);  // private
    
    // Particle.subscribe("x-fire", myNeuralFunction);  // public
    // expecting x= G for good or B for bad learning
    // expecting Fire= #### the analog read value that sets a node fire.

    
}


void myNeuralFunction(const char *event, const char *data){   
    
    
    String myCode = String(data);
    // int pinNumber = myCode.charAt(0);

    if (myCode.startsWith("G")){myStable1 = true;}  //set boolean flag to true if Good
 
    if (myCode.startsWith("B")){myStable1 = false;}  //set boolean flag to false if Bad  
    
    // String  myActivity = myCode.substring(2,6);     // take 4 characters starting at the 3rd.
     
    // Following sets the 2 and on characters to integers
    String myOptional = myCode.substring(3);      
    myFireLimit = myOptional.toInt(); 
    
    myTimerD7.reset();   // reset timer to start fresh
    data = "STOP";
    // change the data so that the function does not fire again
    
}


void loop(){
     
    // your looping stuff goes here
    myA0 = analogRead(A0);  // read the voltage at A0 as a range form 0-4095

    if (myStable1 && myFlag1){
  
        Particle.publish("Log-this-to-google-drive", String("Node001 "+myA0), 60, PRIVATE);
        // Particle.publish("Log-this-to-google-drive", String("Node001 "+myA0), 60, PUBLIC);
             
        myTimerD7.reset();   // reset timer to start fresh
        myFlag1 = false;      // reset timer loop variable
        
         digitalWrite(D7, LOW);
    }
    
    if (!myStable1){
        
         digitalWrite(D7, HIGH);  // just to see if it is working
                                 // this is going to happen to fast
                                 
        int r = random(1, 20);
        if (r==1){ digitalWrite(D0, HIGH);  }  
        if (r==2){ digitalWrite(D0, LOW);  }  
        if (r==3){ digitalWrite(D1, HIGH);  }  
        if (r==4){ digitalWrite(D1, LOW);  }  
        if (r==5){ digitalWrite(D2, HIGH);  }  
        if (r==6){ digitalWrite(D2, LOW);  }  
        if (r==7){ digitalWrite(D3, HIGH);  }  
        if (r==8){ digitalWrite(D3, LOW);  }  
        if (r==9){ digitalWrite(D4, HIGH);  }  
        if (r==10){ digitalWrite(D4, LOW);  }  
        if (r==11){ digitalWrite(D5, HIGH);  }  
        if (r==12){ digitalWrite(D5, LOW);  }  
        if (r==13){ digitalWrite(D6, HIGH);  }  
        if (r==14){ digitalWrite(D6, LOW);  }  
        if (r==15){ digitalWrite(D7, HIGH);  }  
        if (r==16){ digitalWrite(D7, LOW);  }  

        
    }
  
}
