import requests

url = 'http://www.google.com'
#ip_address = '216.137.184.253'
ip_address = '195.222.189.105'

proxies = {
    'http': f'http://{ip_address}',
    'https': f'https://{ip_address}',
}

try:
    response = requests.get(url, proxies=proxies, timeout=5, verify=False)
    print(response.text)
except requests.exceptions.RequestException as e:
    print(f"Error: {e}")