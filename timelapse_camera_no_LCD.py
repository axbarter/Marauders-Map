import time
import os
import subprocess
from gpiozero import LED,Button
from picamera import PiCamera

yellow = LED(16)
button = Button(15)

with PiCamera() as camera:
    #camera.start_preview()
	path, dirs, files = os.walk('/home/pi/photo_output').next()
	file_count = len(files)
	print (file_count)
	frame = 1 + file_count
    	while True:
		button.wait_for_press()
        	yellow.source = button.values
		print ("About to capture photo")
        	camera.capture('/home/pi/photo_output/frame%03d.jpg' % frame)
        	print (frame)
		frame +=1
