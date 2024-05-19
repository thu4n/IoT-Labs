from tensorflow.keras.preprocessing.image import ImageDataGenerator
import os
import numpy as np
from os import listdir
import cv2

# Define the data directory containing subfolders
data_dir = "Dataset/processed"

# Define the output directory for augmented images
output_dir = "Dataset/augmented"

# Define data augmentation parameters
datagen = ImageDataGenerator(
    rotation_range=20,  # Rotate images by 20 degrees randomly
    width_shift_range=0.2,  # Shift images horizontally by 20%
    height_shift_range=0.2,  # Shift images vertically by 20%
    shear_range=0.2,  # Shear images by 20%
    zoom_range=0.2,  # Zoom images by 20%
    horizontal_flip=True  # Flip images horizontally randomly
)

# Loop through each subfolder class
for folder in listdir(data_dir):
  class_dir = f"{data_dir}/{folder}"

  # Check if it's a directory and not a file
  if os.path.isdir(class_dir):
    # Define output directory for this class
    output_class_dir = f"{output_dir}/{folder}"
    os.makedirs(output_class_dir, exist_ok=True)  # Create directory if it doesn't exist

    # Loop through each image in the class directory
    for filename in listdir(class_dir):
      img_path = f"{class_dir}/{filename}"

      # Read the image
      img = cv2.imread(img_path)

      # Convert to RGB format (if needed)
      img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

      # Generate augmented images
      for i in range(20):
        # Generate augmented image
        augmented_img = next(datagen.flow(np.expand_dims(img, axis=0), batch_size=1))
        # Save the augmented image with a new name
        new_filename = f"{output_class_dir}/{filename[:-4]}_{i+1}.{filename[-4:]}"
        cv2.imwrite(new_filename, cv2.cvtColor(augmented_img[0], cv2.COLOR_RGB2BGR))


print("Data augmentation completed!")
