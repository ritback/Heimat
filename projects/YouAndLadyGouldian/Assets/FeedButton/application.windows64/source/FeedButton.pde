import processing.serial.*;
import processing.sound.*;

import java.util.Date;
import http.requests.*;


Serial mPort;  // Create object from Serial class
int mSerialVal;      // Data received from the serial port


ArrayList<SoundFile> mSoundFiles;
SoundFile mCurrentSoundFile;
int mCurrentSoundFileIndex;


// --------------------------------------------------------------------
void setup() 
{
  size(300, 100);
  
  String portName = Serial.list()[1];
  println(portName);
  mPort = new Serial(this, portName, 9600);
  
  String path = sketchPath() + "/data";
  println("Listing all filenames in a directory: ");
  String[] filenames = listFileNames(path);
  printArray(filenames);
  
  mSoundFiles = new ArrayList();
  for (int i = 0; i < filenames.length; ++i)
  {
    mSoundFiles.add(new SoundFile(this, filenames[i]));
  }
  mCurrentSoundFileIndex = 0;
  randomizeCurrentSoundFile();
  
  mCurrentSoundFile.amp(2);
  
}

void exit()
{
  mSoundFiles.clear();
}

// --------------------------------------------------------------------
void draw()
{
  if ( mPort.available() > 0)
  {  // If data is available,
  
    mSerialVal = mPort.read();         // read it and store it in val
    
    println("Data: ", mSerialVal);
  
    if (mSerialVal == 49) // data received = '1'
    {
      loadStrings("https://youandladygouldian.com/birdparams/food/put");
      mCurrentSoundFile.stop();
      randomizeCurrentSoundFile();
      mCurrentSoundFile.play();
    }
  }
  
  background(200);
  
  textSize(32);
  fill(0, 102, 153);
  String soundFilePath = "current index: " + mCurrentSoundFileIndex;
  text(soundFilePath, 10, 30);
}

// --------------------------------------------------------------------
String[] listFileNames(String dir) {
  File file = new File(dir);
  if (file.isDirectory()) {
    String names[] = file.list();
    return names;
  } else {
    // If it's not a directory
    return null;
  }
}

void randomizeCurrentSoundFile()
{
  if (false)
  {
    int i = floor(random(0, mSoundFiles.size() - 0.0001));
    mCurrentSoundFileIndex = i;
  }
  else
  {
    mCurrentSoundFileIndex++;
    mCurrentSoundFileIndex %= mSoundFiles.size();
  }
  
  mCurrentSoundFile = mSoundFiles.get(mCurrentSoundFileIndex);
}


void keyPressed()
{
  if (key == 'p')
  {
    loadStrings("https://youandladygouldian.com/birdparams/food/put");
    mCurrentSoundFile.stop();
    randomizeCurrentSoundFile();
    mCurrentSoundFile.play();
  }
}