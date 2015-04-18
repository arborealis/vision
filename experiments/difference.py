#!/usr/bin/env python

import cv
import time
import numpy

class Target:
    def __init__(self):
        self.capture = cv.CaptureFromCAM(0)
        cv.SetCaptureProperty(self.capture, cv.CV_CAP_PROP_FRAME_WIDTH, 320);
        cv.SetCaptureProperty(self.capture, cv.CV_CAP_PROP_FRAME_HEIGHT, 240);
        frame = cv.QueryFrame(self.capture)
        frame_size = cv.GetSize(frame)

        frame = cv.QueryFrame(self.capture)
        cv.NamedWindow("Target", 1)

    def run(self):
        frame = cv.QueryFrame(self.capture)
        frame_size = cv.GetSize(frame)
        
        # Capture the first frame from webcam for image properties
        display_image = cv.QueryFrame(self.capture)
        
        # Greyscale image, thresholded to create the motion mask:
        grey_image = cv.CreateImage(cv.GetSize(frame), cv.IPL_DEPTH_8U, 1)
        
        # The RunningAvg() function requires a 32-bit or 64-bit image...
        running_average_image = cv.CreateImage(cv.GetSize(frame), cv.IPL_DEPTH_32F, 3)
        # ...but the AbsDiff() function requires matching image depths:
        running_average_in_display_color_depth = cv.CloneImage(display_image)
        
        # The difference between the running average and the current frame:
        difference = cv.CloneImage(display_image)
        
        frame_count = 0
        
        t0 = time.time()
        
        while True:
            # Capture frame from webcam
            camera_image = cv.QueryFrame(self.capture)
            
            frame_count += 1
            frame_t0 = time.time()
            
            # Create an image with interactive feedback:
            display_image = cv.CloneImage(camera_image)
            
            # Create a working "color image" to modify / blur
            color_image = cv.CloneImage(display_image)

            # Smooth to get rid of false positives
            cv.Smooth(color_image, color_image, cv.CV_GAUSSIAN, 19, 0)
            
            # Use the Running Average as the static background            
            # a = 0.020 leaves artifacts lingering way too long.
            # a = 0.320 works well at 320x240, 15fps.  (1/a is roughly num frames.)
            cv.RunningAvg(color_image, running_average_image, 0.320, None)
            
            # Convert the scale of the moving average.
            cv.ConvertScale(running_average_image, running_average_in_display_color_depth, 1.0, 0.0)
            
            # Subtract the current frame from the moving average.
            cv.AbsDiff(color_image, running_average_in_display_color_depth, difference)
            
            # Convert the image to greyscale.
            cv.CvtColor(difference, grey_image, cv.CV_RGB2GRAY)

            # Threshold the image to a black and white motion mask:
            cv.Threshold(grey_image, grey_image, 2, 255, cv.CV_THRESH_BINARY)
            # Smooth and threshold again to eliminate "sparkles"
            cv.Smooth(grey_image, grey_image, cv.CV_GAUSSIAN, 19, 0)
            cv.Threshold(grey_image, grey_image, 240, 255, cv.CV_THRESH_BINARY)
            
            grey_image_as_array = numpy.asarray(cv.GetMat(grey_image))
            non_black_coords_array = numpy.where(grey_image_as_array > 3)
            # Convert from numpy.where()'s two separate lists to one list of (x, y) tuples:
            non_black_coords_array = zip(non_black_coords_array[1], non_black_coords_array[0])
            
            # Listen for ESC or ENTER key
            c = cv.WaitKey(7) % 0x100
            if c == 27 or c == 10:
                break
            
            cv.ShowImage("Target", difference)
            
            # If only using a camera, then there is no time.sleep() needed, 
            # because the camera clips us to 15 fps.  But if reading from a file,
            # we need this to keep the time-based target clipping correct:
            frame_t1 = time.time()
            
        t1 = time.time()
        time_delta = t1 - t0
        processed_fps = float(frame_count) / time_delta
        print "Got %d frames. %.1f s. %f fps." % (frame_count, time_delta, processed_fps)
        
if __name__=="__main__":
    t = Target()
    t.run()
