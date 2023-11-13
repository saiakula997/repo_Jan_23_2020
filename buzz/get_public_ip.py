import requests

def get_public_ip():
    try:
        response = requests.get('https://httpbin.org/ip')
        ip_address = response.json().get('origin')
        return ip_address
    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
        return None

if __name__ == "__main__":
    public_ip = get_public_ip()
    if public_ip:
        print(f"Your public IP address is: {public_ip}")