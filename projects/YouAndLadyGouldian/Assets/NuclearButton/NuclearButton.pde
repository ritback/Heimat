import processing.serial.*;
import processing.sound.*;


Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port


SoundFile soundFile;
String soundFilePath;



void setup() 
{
  size(300, 100);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[1];
    println(portName);
  myPort = new Serial(this, portName, 9600);
  
  soundFilePath = "Explosion+2.mp3";
  soundFile = new SoundFile(this, soundFilePath);
  
  
  
}

void draw()
{
  if ( myPort.available() > 0)
  {  // If data is available,
  
    val = myPort.read();         // read it and store it in val
    
    println("Data: ", val);
    
    if (val == 49)
    {
      soundFile.stop();
      soundFile.play();
    }
  }
  background(200);
  
  textSize(32);
  fill(0, 102, 153);
  text(soundFilePath, 10, 30);
}

void keyPressed()
{
  switch(key)
  {
    case '1':
      soundFilePath = "Explosion+2.mp3"; loadSelected();
      break;
    case '2':
      soundFilePath = "leroy.swf.mp3"; loadSelected();
      break;
    case '3':
      soundFilePath = "dramatic.swf.mp3"; loadSelected();
      break;
    case '4':
      soundFilePath = "igothtepower.mp3"; loadSelected();
      break;
    case '5':
      soundFilePath = "sound-9______.mp3"; loadSelected();
      break;
    case '6':
      soundFilePath = "nooo.swf.mp3"; loadSelected();
      break;
    case '7':
      soundFilePath = "tada.swf.mp3"; loadSelected();
      break;
    case '8':
      soundFilePath = "doh.swf.mp3"; loadSelected();
      break;
    case '9':
      soundFilePath = "Explosion+2.mp3"; loadSelected();
      break;
      
  }
  
    
}

void loadSelected()
{
  //println(soundFilePath);
    soundFile = new SoundFile(this, soundFilePath);
}