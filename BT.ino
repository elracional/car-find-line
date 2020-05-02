#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(13,12); //Pines de entrada y salida, 13 Rx , 12 Tx

const int s0 = 7;  //color
const int s1 = 8;  //color
const int s2 = 9;  //color
const int s3 = 10;  //color
const int out = 11; //color
const int m1 = 6;   //motor1
const int m2 = 5; // motor2
const int mR = 2; // motor2 reversa
const int sl4 = 3;  //Seguidorlinea1
const int sl5 = 4;  //Segudirlinea2
int rojo = 0;  
int verde = 0;  
int azul = 0;  
String qActual = "q0";  //Estado inicial del carrito, se inicializa con el estado inicial
String qDeseada="";    //Variable que cambia conforme de le indica por medio de Bluetooth
int contador = 0;  //Variable que servirá especialmente al funcionamiento del automata
String cadena="";  //Variable que guardará la cadena que se reciba por medio de Bluetooth
char numeros [5] = {'1','2','3','4','0'}; // Alfabeto de automata -> alfabeto U numeros
//Definicion de las transiciones, partiendo de determinado estao para llegar a otro
  String q0_q1[]={"azul"};
  String q0_q2[]={"verde","azul"};
  String q0_q3[]={"verde","rojo"};
  String q0_q4[]={"verde"};

  String q1_q0[]={"azul"};
  String q1_q2[]={"rojo"};
  String q1_q3[]={"rojo","verde"};
  String q1_q4[]={"azul","verde"};

  String q2_q0[]={"azul","verde"};
  String q2_q1[]={"rojo"};
  String q2_q3[]={"verde"};
  String q2_q4[]={"azul"};
  
  String q3_q0[]={"rojo","verde"};
  String q3_q1[]={"verde","rojo"};
  String q3_q2[]={"verde"};
  String q3_q4[]={"rojo"};

  String q4_q0[]={"verde"};
  String q4_q1[]={"azul","rojo"};
  String q4_q2[]={"azul"};
  String q4_q3[]={"rojo"};

void q0();  //Estado inicial del automata
void q1();
void q2();
void q3();
void q4();
void q5();
void q6();
void q7();
void q8();
void q9();
void q10();
void q11();
void q12();
void q13();
void qError();
boolean siNumero(char numero);//Funcion que verifica si se recibe un numero valido (si se encuentra en el conjunto de numeros)
void leer_Cadenas();//Funcion que seencarga de leer cadenas desde bluetooth y de llevar acabo el proceso siguiente
void recorrerTransiciones(int qDeseada);//Funcion que recorre las transicions definidas
void color();//Funcon que obtiene valores directamente del sensor de color y sirve para evaluarlos
void girar(String color1);//Funcion que se encarga de hacer girar el carro en ciertas condiciones
void SeguidorLinea(String estado);//Funcion dedicada al seguimiento de linea

void setup() {
  BlueTooth.begin(9600);//Se inicia el serial definido
  pinMode(s0,OUTPUT);  //Se establecen los pines necesarios para el funconamiento y si sera de entrada o salida
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);
  pinMode (m1, OUTPUT); 
  pinMode(m2,OUTPUT);
  pinMode(mR,OUTPUT);
  pinMode (sl4, INPUT); 
  pinMode(sl5,INPUT); 
  digitalWrite(s0,HIGH);  //Se establecen desde el unicio para un correcto funcionamiento del sensor de color
  digitalWrite(s1,HIGH); 
}

void loop() {
  leer_Cadenas(); //Se evalua la funcion de leer cadenas todo el tiempo
}

void leer_Cadenas(){
  char caracter='\b';
  while (BlueTooth.available()>0) { 
    caracter = BlueTooth.read();//Se lee cacacter por caracter desde el bluetooth
    BlueTooth.flush();
    if(caracter==';'){
       cadena = cadena + ';'; //Primera verificacion, si la pase empieza le automata
       q0();
      }
      else{
        cadena = cadena + caracter;
      }
  }
}

void q0(){//Estado inicial del automata
  if(cadena.charAt(contador)=='p'){
      contador++;
      BlueTooth.println("En q0");
      q1();
    }else if(cadena.charAt(contador)=='a'){
      contador++;
      q7();
    }else{
      qError();
    }
}

void q1(){
  if(cadena.charAt(contador)=='u'){
    contador++;
    BlueTooth.println("En q1");
    q2();
    }else{
      qError();
    }
}

void q2(){
  if(cadena.charAt(contador)=='n'){
    contador++;
    BlueTooth.println("En q2");
    q3();
    }else{
      qError();
    }
}

void q3(){
  if(cadena.charAt(contador)=='t'){
    contador++;
    BlueTooth.println("En q3");
    q4();
    }else{
      qError();
      }
}

void q4(){
  if(cadena.charAt(contador)=='o'){
    contador++;
    BlueTooth.println("En q4");
    q5();
    }else{
      qError();
      }
}

void q5(){
  if(siNumero(cadena.charAt(contador))){
    contador++;
    BlueTooth.println("En q5");
    q6();
    }else{
      qError();
      }
}

void q6(){
  if(cadena.charAt(contador)==';'){
    contador++;
    BlueTooth.println("En q6");
    q13();
    }else{
      qError();
      }
}

void q7(){
  if(cadena.charAt(contador)=='p'){
    contador++;
    BlueTooth.println("En q7");
    q8();
    }else{
      qError();
      }
}

void q8(){
  if(cadena.charAt(contador)=='a'){
    contador++;
    BlueTooth.println("En q8");
    q9();
    }else{
      qError();
      }
}

void q9(){
  if(cadena.charAt(contador)=='g'){
    contador++;
    BlueTooth.println("En q9");
    q10();
    }else{
      qError();
      }
}

void q10(){
  if(cadena.charAt(contador)=='a'){
    contador++;
    BlueTooth.println("En q10");
    q11();
    }else{
      qError();
      }
}

void q11(){
  if(cadena.charAt(contador)=='r'){
    contador++;
    BlueTooth.println("En q11");
    q12();
    }else{
      qError();
      }
}

void q12(){
  if(cadena.charAt(contador)==';'){
    contador++;
    BlueTooth.println("En q12");
    q13();
    }else{
      qError();
      }
}

void q13(){//Estado final, si se llega aqui es por que el comando fue valido
  BlueTooth.println("Comando aceptado");
  if(cadena.equals("apagar;")){
     digitalWrite(m1,LOW);
     digitalWrite(m2,LOW);
     digitalWrite(mR,LOW);
     BlueTooth.println("Apagar");
  }else{//Si el comando aceptado es diferente a apagar, se empieza
    switch(cadena.charAt(5)){//Se evalua el nuemero existente en la cadena, que será el destino deseado
      case '1': recorrerTransiciones(numero.toInt());
                qDeseada = "q1";
        break;
      case '2': recorrerTransiciones(numero.toInt());
                qDeseada="q2";
        break;
      case '3': recorrerTransiciones(numero.toInt());
                qDeseada="q3";
        break;
      case '4': recorrerTransiciones(numero.toInt());
                qDeseada="q4";
        break;
      case '0': recorrerTransiciones(numero.toInt());
                qDeseada="q0";
        break;
      default: qError(); //En casos desconocidos se mnada alamar a qError para el manejo de 
    }
  }
}

boolean siNumero(char numero){//Se recorel el conjunto d enumeros para verificar si se oorgó un numero valido
  for(int i=0;i<5;i++){
    if(numeros[i]==numero)
      return true;
    }
  return false;
}

void qError(){//Funcion para evaluar cadenas no validas
  BlueTooth.println("Comando introducido no valido");
  cadena="";
  contador=0;
}

void recorrerTransiciones(int qDeseada){//Funcion que recorre las transiciones que debe seguir el carro dependiendo su  
  if(qActual=="q0"){                    //posicion final y actual
    switch(qDeseada){
      case 1: 
          for(int i=0;i<1;i++){
            girar(q0_q1[i],qActual);//En cada condicion, se recorre el arreglo donde se ha guardado la transicion que va a seguir
          }                         //para llegar al estado deseado, esto se hace al leer los colores que conectan los estados
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 2:
          for(int i=0;i<2;i++){
            girar(q0_q2[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 3:
          for(int i=0;i<2;i++){
            girar(q0_q3[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 4:
          for(int i=0;i<1;i++){
            girar(q0_q4[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      default: break;
    }
  }
  if(qActual=="q1"){
    switch(qDeseada){
      case 0: 
          for(int i=0;i<1;i++){
            girar(q1_q0[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 2:
          for(int i=0;i<1;i++){
            girar(q1_q2[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 3:
          for(int i=0;i<2;i++){
            girar(q1_q3[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 4:
          for(int i=0;i<2;i++){
            girar(q1_q4[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      default: break;
    }
  }
  if(qActual=="q2"){
    switch(qDeseada){
      case 1: 
          for(int i=0;i<1;i++){
            girar(q2_q1[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 0:
          for(int i=0;i<2;i++){
            girar(q2_q0[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 3:
          for(int i=0;i<1;i++){
            girar(q2_q3[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 4:
          for(int i=0;i<1;i++){
            girar(q2_q4[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      default: break;
    }
  }
  if(qActual=="q3"){
    switch(qDeseada){
      case 1: 
          for(int i=0;i<2;i++){
            girar(q3_q1[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 2:
          for(int i=0;i<1;i++){
            girar(q3_q2[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 0:
          for(int i=0;i<2;i++){
            girar(q3_q0[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 4:
          for(int i=0;i<1;i++){
            girar(q3_q4[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      default: break;
    }
  }
  if(qActual=="q4"){
    switch(qDeseada){
      case 1: 
          for(int i=0;i<2;i++){
            girar(q4_q1[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 2:
          for(int i=0;i<1;i++){
            girar(q4_q2[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 3:
          for(int i=0;i<1;i++){
            girar(q4_q3[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      case 0:
          for(int i=0;i<1;i++){
            girar(q4_q0[i],qActual);
          }
          BlueTooth.println("Comando finalizado \nEstado actual: "+qActual);
        break;
      default: break;
    }
  }
}
 
void SeguidorLinea(String estado){//Funcion que se encarga del funcionamiento del seguidor de linea la transportarse de una estado a otro
  while(digitalRead(sl4)!= LOW && digitalRead(sl5)!=LOW){//Se va a relaizar mientras ambos motores sensores regresen 0
      if(digitalRead(sl4)== HIGH && digitalRead(sl5)== HIGH)//Cada if esta adecuado a las condiciones que se pueden dar, y se obtendra 
      {                                                     //a configuracion de los motores necesaria para que se continue con el trayecto
           digitalWrite (m1, HIGH);
           digitalWrite (m2, HIGH);
      }
  
      if(digitalRead(sl4)== HIGH && digitalRead(sl5)== LOW)
      {
          digitalWrite (m1, LOW);
          digitalWrite (m2, HIGH);
      }
      if(digitalRead(sl4)== LOW && digitalRead(sl5)== HIGH)
      {
          digitalWrite (m1, HIGH);
          digitalWrite (m2, LOW);
      } 
  }
  qActual = estado;//Se reasigna el estado actual del carro al termino del seguidor de linea
}

void girar(String color1,String qActual){//Funcion que identifica los colores que se estan evaluado en el sensor
  if(color1=="rojo"){
      do{//Se hara girar el carro sobre su propio eje hasta que encuentre el color que se necesita, al encontrarlo
        color();//Se pasa el control del carro al seguidor de linea
         digitalWrite (m1, HIGH);
         digitalWrite (mR, HIGH);//Salidas necesarias para que el carro gire sobre su propio eje en el punto actual
      }while(!(rojo < azul && verde > azul && rojo < 25));
      delay (500);
      SeguidorLinea(qActual);
    }
  if(color1=="azul"){
       do{
        color();
         digitalWrite (m1, HIGH);
         digitalWrite (mR, HIGH);
   
        }
      while(!(azul < rojo && azul < verde && verde < rojo));
      delay (500);
      SeguidorLinea(qActual);
    }
  if(color1=="verde"){
      do{
        color();
         digitalWrite (m1, HIGH);
         digitalWrite (mR, HIGH);
   
        }
      while(!(rojo > verde && azul > verde));
      delay (500);
      SeguidorLinea(qActual);
  }
}

void color()//Funcion que evalua los resultados obtenidos por el sensor
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);//Se asigna una y otra vez los valores arrojados por el sensor
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);   
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);    
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}
