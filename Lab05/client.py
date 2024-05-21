#!/usr/bin/python3

import cv2
import os
import time
import requests
import base64

# Define the GStreamer pipeline for the CSI camera
def gstreamer_pipeline(
    capture_width=1280,
    capture_height=720,
    display_width=1280,
    display_height=720,
    framerate=20,  # Set framerate to 20 fps
    flip_method=0,
):
    return (
        "nvarguscamerasrc ! "
        "video/x-raw(memory:NVMM), "
        "width=(int)%d, height=(int)%d, "
        "format=(string)NV12, framerate=(fraction)%d/1 ! "
        "nvvidconv flip-method=%d ! "
        "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGRx ! "
        "videoconvert ! "
        "video/x-raw, format=(string)BGR ! appsink"
        % (
            capture_width,
            capture_height,
            framerate,
            flip_method,
            display_width,
            display_height,
        )
    )

def encode_image_to_base64(image_path):
    with open(image_path, "rb") as image_file:
        encoded_image = base64.b64encode(image_file.read()).decode('utf-8')
    return encoded_image

# Create a directory to save the images
url = 'http://172.31.11.66:8000/recog'
output_dir = "captured_frames"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Initialize the camera
cap = cv2.VideoCapture(gstreamer_pipeline(flip_method=0), cv2.CAP_GSTREAMER)

if cap.isOpened():
    try:
        frame_count = 0
        start_time = time.time()
        duration = 5  # capture duration in seconds

        while True:  # Capture 120 frames
            ret_val, frame = cap.read()
            if not ret_val:
                break

            # Save the frame as an image file
            frame_filename = os.path.join(output_dir, f"frame_{frame_count:04d}.jpg")
            cv2.imwrite(frame_filename, frame)
            frame_count += 1


            # Display the frame (optional)
            cv2.imshow('CSI Camera', frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

            # Check if the duration has passed
            if time.time() - start_time > duration:
                break

        frame_count -= 1
        filename = f"frame_{frame_count:04d}.jpg"
        img_path = f'{output_dir}/{filename}'
        encoded_image_data = encode_image_to_base64(frame_filename)
        data = {
            'image': encoded_image_data,
            'w': 160,  #  width
            'h': 160   #  height
        }

        # Sending the POST request
        sent_time = time.time()
        response = requests.post(url, data=data)
        received_time = time.time()

        # Printing the response
        print("==================================")
        print(f"Response from server:{response.text}")
        print(f"Execution time:{received_time - sent_time}")
        print("==================================")
    finally:
        cap.release()
        cv2.destroyAllWindows()
else:
    print("Unable to open camera")