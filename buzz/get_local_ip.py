import socket

def get_local_ip():
    try:
        # Create a socket connection to an external server
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(('8.8.8.8', 80))  # Connect to Google's public DNS server
        local_ip = s.getsockname()[0]
        s.close()
        return local_ip
    except socket.error as e:
        print(f"Error: {e}")
        return None

if __name__ == "__main__":
    local_ip = get_local_ip()
    if local_ip:
        print(f"Your local IP address is: {local_ip}")