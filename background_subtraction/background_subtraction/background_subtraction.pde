import gab.opencv.*;
import processing.video.*;
import org.opencv.imgproc.Imgproc;
import org.opencv.core.Mat;
import org.opencv.core.Core;
import org.opencv.core.Size;
import org.opencv.core.CvType;

OpenCV opencv;
Capture cam;
Mat avg, frame, diff;
PImage img;

void setup() {
  cam = new Capture(this, 640, 480);
  size(cam.width, cam.height);
  opencv = new OpenCV(this, cam.width, cam.height);
  //opencv.useGray();

  cam.start();
  frameRate(30);
  opencv.loadImage(cam);

  frame = opencv.getGray();
  avg = new Mat();
  diff = new Mat();
  frame.convertTo(avg, CvType.CV_32F);
  frame.convertTo(diff, CvType.CV_32F);
}

void draw() {
  scale(2);  
  opencv.loadImage(cam);
  
  frame = opencv.getGray();
  frame.convertTo(frame, CvType.CV_32F);

  Imgproc.accumulateWeighted(frame, avg, 0.1);
  Core.subtract(frame, avg, diff);
  Core.convertScaleAbs(diff, diff);
//
//  opencv.toPImage(diff, img);
////  arrayCopy(diff, img.pixels);
////  img.updatePixels();
//  image(img,0,0);
}

