import requests
import base64
import time
from datetime import datetime

# Function to encode image to Base64
def encode_image_to_base64(image_path):
    with open(image_path, "rb") as image_file:
        encoded_image = base64.b64encode(image_file.read()).decode('utf-8')
    return encoded_image

def measure_recognition_time(image_path, server_url):
    # Encode image to Base64
    encoded_image_data = encode_image_to_base64(image_path)
    
    # Parameters to send in the POST request
    data = {
        'image': encoded_image_data,
        'w': 160,  # width
        'h': 160   # height
    }
    
    # Ghi lại thời gian gửi
    send_time = datetime.now()
    print(f"Sending time: {send_time}")
    
    # Bắt đầu đo thời gian
    start_time = time.time()
    
    # Gửi hình ảnh đến server
    response = requests.post(server_url, data=data)
    
    # Nhận kết quả nhận diện
    recognition_result = response.json()
    
    # Ghi lại thời gian nhận
    receive_time = datetime.now()
    print(f"Receiving time: {receive_time}")
    
    # Kết thúc đo thời gian
    end_time = time.time()
    
    # Tính tổng thời gian
    total_time = end_time - start_time
    
    print(f"Total time: {total_time} giây")
    return send_time, receive_time, total_time, recognition_result

# Ví dụ sử dụng
image_path = 'Dataset/test/anhthuan/thuan2.jpg'
server_url = '172.31.11.66'
send_time, receive_time, total_time, recognition_result = measure_recognition_time(image_path, server_url)

print(f"Result: {recognition_result}")
