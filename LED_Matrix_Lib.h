//LED Matrix pins //possible change to chars
int r1_pin; 
int g1_pin; 
int b1_pin; 
int r2_pin; 
int g2_pin; 
int b2_pin; 
int E_pin; 
int A_pin; 
int B_pin; 
int C_pin; 
int D_pin; 
int clk_pin; 
int lat_pin; 
int OE_pin;   

//turns integer [0-31] into a binary array (4 bits)
void intToBinArray(char n, bool * addyBits ){
  for(int i = 0; i < 4; i++){
    addyBits[3-i] = n%2;
    n = n/2; 
  }  
}  

//clears the led matrix screen
void clearScreen(){  
  digitalWrite(clk_pin, LOW);  
  digitalWrite(lat_pin, LOW); 
  
  for(int i = 0; i < 16; i++){ // for each row 
    bool addyBits[] = {0,0,0,0};
    intToBinArray(i, addyBits);
    
    if(addyBits[3] == 0){
      digitalWrite(D_pin, LOW); 
    }
    else{
      digitalWrite(D_pin, HIGH); 
    } 
    
    if(addyBits[2] == 0){
      digitalWrite(C_pin, LOW); 
    }
    else{
      digitalWrite(C_pin, HIGH); 
    } 
    
    if(addyBits[1] == 0){
      digitalWrite(B_pin, LOW); 
    }
    else{
      digitalWrite(B_pin, HIGH); 
    } 
    
    if(addyBits[0] == 0){
      digitalWrite(A_pin, LOW); 
    }
    else{
      digitalWrite(A_pin, HIGH); 
    } 
    
    //row address is set 
    for(int c = 0; c < 64; c++){ //for each col
      digitalWrite(r1_pin, LOW); 
      digitalWrite(b1_pin, LOW); 
      digitalWrite(g1_pin, LOW); 
      
      digitalWrite(r2_pin, LOW); 
      digitalWrite(b2_pin, LOW); 
      digitalWrite(g2_pin, LOW);  
      
      digitalWrite(clk_pin, HIGH); 
      digitalWrite(clk_pin, LOW); 
      
    } 
    
    digitalWrite(lat_pin, HIGH); 
    digitalWrite(lat_pin, LOW);  
    digitalWrite(OE_pin, HIGH); 
    digitalWrite(OE_pin, LOW); 
    }
  
  
}  

//sets the address of the led matrix to 0
void setMatrixAddyToZero(){
  digitalWrite(A_pin, LOW); 
  digitalWrite(B_pin, LOW); 
  digitalWrite(C_pin, LOW); 
  digitalWrite(D_pin, LOW); 
  digitalWrite(E_pin, LOW);  
} 

//initalizes the LED matrix with the pin parameters  
void init_LED_Matrix(int lat_pin_arg, int clk_pin_arg, int OE_pin_arg, int r1_pin_arg, int g1_pin_arg, int b1_pin_arg, int r2_pin_arg, int g2_pin_arg, int b2_pin_arg, int A_pin_arg, int B_pin_arg, int C_pin_arg, int D_pin_arg, int E_pin_arg){
//pin setup 
    lat_pin = lat_pin_arg;  
    digitalWrite(lat_pin,LOW);
    pinMode(lat_pin, OUTPUT);   
    

    clk_pin = clk_pin_arg;  
    digitalWrite(clk_pin, LOW);
    pinMode(clk_pin, OUTPUT);   
    
    OE_pin = OE_pin_arg;  
    digitalWrite(OE_pin, LOW);
    pinMode(OE_pin, OUTPUT);       
    

    r1_pin = r1_pin_arg;  
    digitalWrite(r1_pin,LOW); 
    pinMode(r1_pin, OUTPUT);    
    

    g1_pin = g1_pin_arg; 
    digitalWrite(g1_pin, LOW);
    pinMode(g1_pin, OUTPUT);     
    

    b1_pin = b1_pin_arg; 
    digitalWrite(b1_pin,LOW);
    pinMode(b1_pin, OUTPUT);  
   

    r2_pin = r2_pin_arg; 
    digitalWrite(r2_pin, LOW); 
    pinMode(r2_pin, OUTPUT);     
    
    g2_pin = g2_pin_arg;  
    digitalWrite(g2_pin,LOW);
    pinMode(g2_pin, OUTPUT);    
    
    b2_pin = b2_pin_arg;  
    digitalWrite(b2_pin, LOW);
    pinMode(b2_pin, OUTPUT);     
   

    E_pin = E_pin_arg;  
    digitalWrite(E_pin,LOW);
    pinMode(E_pin, OUTPUT);    
   

    A_pin = A_pin_arg;  
    digitalWrite(A_pin, LOW);
    pinMode(A_pin, OUTPUT);     
    
    B_pin = B_pin_arg;  
    digitalWrite(B_pin,LOW);
    pinMode(B_pin, OUTPUT);    
    

    C_pin = C_pin_arg;  
    digitalWrite(C_pin, LOW);
    pinMode(C_pin, OUTPUT);     
   

    D_pin = D_pin_arg;  
    digitalWrite(D_pin,LOW);
    pinMode(D_pin, OUTPUT);  
    
    clearScreen();  
    setMatrixAddyToZero(); 
}


//bitmap for the contents to be displayed on the led matrix  
//the bitmap is a 32 by 64 bitmap where the bottom left corner is the pixel (0,0)
//the rgb parameter that exist for some fucntions of this class reprsent the color for the object
//to be drawn on the LED matrix. You can think of this paramter as a 3 length bit string where 0b000 = black
//0b111 = white, ob100 = red, 0b010 = green, 0b001 = blue, 0b011 = the color you get when you mix blue and green, 
//and so on. The 
class DataMatrix{
  public: 
    char matrixTable[32][64]; 

    //clears the bitmap
    void clearDataMatrix(){
      for(int r = 0; r < 32; r++){
        for(int c = 0; c < 64; c++){
          matrixTable[r][c] = 0; 
        }
      }
    } 


    //adds a pixel to the bitmap at position (x,y) with color rgb
    void addPixel(char x, char y, char rgb){ 
      if(x >= 0 && x < 64 && y >= 0 && y < 32){
      matrixTable[31-y][x] = rgb;
    }  
    }

    //adds a rectangle to the bitmap where (x,y) is the location of the bottom left corner of the rectangle  
    //use this function to add vertical lines, not the addLine function
    void addRect(char x, char y, char l, char w, char rgb){
      for(char r = 0; r < w; r++){
        for(char c = 0; c < l; c++){
          addPixel(x+c,y+r,rgb); 
        }
      }
    } 

    //adds a line into the bitmap where (x1,y1) and (x2,y2) are the endpoints of the line 
    //don't use this function for vertical lines, it won't work. Instead use the addRect function
    void addLine(char x1, char y1, char x2, char y2, char rgb){ 
      char dx = abs(x1-x2); 
      char dy = abs(y1-y2); 

      for(int x = x1; x <= x2; x++){
        int y = (dy*(x))/dx; 
        addPixel(x,y,rgb);
      }
    }

    //prints out the contents of the bitmap, where the number at (x,y) represents the pixel 
    //color for that pixel
    void printDataMatrix(){
      Serial.println("******"); 
      char r = 0; 
      char c = 0; 
      for(r=0; r< 32; r++){
        for(c=0; c< 64; c++){
          Serial.print(matrixTable[r][c],DEC);  
          Serial.print(" , ");
        } 
        Serial.println("-");
    }  
      Serial.println("*******");
    }
}; 

//outputs the bitmap of the DataMatrix *dm onto the LED matrix
void drawLEDMatrix(DataMatrix * dm){
    char r = 0; 
    char c = 0;  

    bool addyBits[] = {0,0,0,0}; 
    for(r = 0; r < 16; r++){   
      for(c = 0; c < 64; c++){  

            bool rgbBits[] = {0,0,0,0}; 
            intToBinArray(dm->matrixTable[31-r][63-c],rgbBits);  


            if(rgbBits[1] == true){
                digitalWrite(r1_pin,HIGH);
            } 
            else{
                digitalWrite(r1_pin,LOW); 
            } 

            if(rgbBits[2] == true){
                digitalWrite(g1_pin,HIGH);
            } 
            else{
                digitalWrite(g1_pin,LOW); 
            } 

            if(rgbBits[3] == true){
                digitalWrite(b1_pin,HIGH);
            } 
            else{
                digitalWrite(b1_pin,LOW); 
            }  

            intToBinArray(dm->matrixTable[31-r-16][63-c],rgbBits);

            if(rgbBits[1] == true){
                digitalWrite(r2_pin,HIGH);
            } 
            else{
                digitalWrite(r2_pin,LOW); 
            } 

            if(rgbBits[2] == true){
                digitalWrite(g2_pin,HIGH);
            } 
            else{
                digitalWrite(g2_pin,LOW); 
            } 

            if(rgbBits[3] == true){
                digitalWrite(b2_pin,HIGH);
            } 
            else{
                digitalWrite(b2_pin,LOW); 
            } 

            digitalWrite(clk_pin,HIGH); 
            digitalWrite(clk_pin,LOW); 
        } 

    
      digitalWrite(OE_pin, HIGH); 

     
      intToBinArray(r,addyBits);   
     
        if(addyBits[3] == 0){
        digitalWrite(A_pin, LOW); 
        }
        else{
        digitalWrite(A_pin, HIGH); 
        } 
        
        if(addyBits[2] == 0){
        digitalWrite(B_pin, LOW); 
        }
        else{
        digitalWrite(B_pin, HIGH); 
        } 
        
        if(addyBits[1] == 0){
        digitalWrite(C_pin, LOW); 
        }
        else{
        digitalWrite(C_pin, HIGH); 
        } 
        
        if(addyBits[0] == 0){
        digitalWrite(D_pin, LOW); 
        }
        else{
        digitalWrite(D_pin, HIGH); 
        }    
    
         

      digitalWrite(lat_pin, HIGH); 
      digitalWrite(lat_pin, LOW);  
      digitalWrite(OE_pin, LOW);  
         
    }
    

}
