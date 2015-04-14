import gab.opencv.*;
import processing.video.*;
import org.opencv.imgproc.Imgproc;
import org.opencv.core.Mat;
import org.opencv.core.Core;
import org.opencv.core.Size;
import org.opencv.core.CvType;

OpenCV opencv;
Capture cam;
Mat frame, previous, diff;
PImage img;
int start_time = millis();
int count = 0;

void setup() {
  frameRate(60);
  size(1280, 720);
  
  cam = new Capture(this, width, height);
  img = new PImage(width, height);
  opencv = new OpenCV(this, width, height);

  cam.start();
  opencv.loadImage(cam);

  frame = opencv.getGray();
  diff = new Mat();
  previous = new Mat();
  frame.convertTo(previous, CvType.CV_32F);
  frame.convertTo(diff, CvType.CV_32F);
}

void draw() {
  //scale(2);  
  if (cam.available()) 
    cam.read();
  else
    return;
      
  opencv.loadImage(cam);
  frame = opencv.getGray();
  frame.convertTo(frame, CvType.CV_32F);

  //Imgproc.accumulateWeighted(frame, prev, 0.1);
  Core.subtract(frame, previous, diff);
  Core.convertScaleAbs(diff, diff);
  previous = frame;
  
  opencv.toPImage(diff, img);
  image(img,0,0);
  
  count++;
  
  if (millis() - start_time > 5000) {
    double fps = (float)count / (millis() - start_time) * 1000;
    println("Effect framerate: " + fps + "fps");
    start_time = millis();
    count = 0;
  }
}

