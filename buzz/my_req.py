import requests

#url = 'https://api64.ipify.org?format=json'
url = 'http://www.google.com/'
proxy = {'http': 'http://216.137.184.253', 'https': 'https://216.137.184.253'}
#proxy = {'http': 'http://192.168.100.100', 'https': 'https://192.168.100.100'}
proxy_auth = requests.auth.HTTPProxyAuth('one', 'one')

try:
    response = requests.get(url, proxies=proxy, auth=proxy_auth, verify=False)
    #response = requests.get(url)
    print(response.text)
except requests.exceptions.RequestException as e:
    print(f"Error: {e}")