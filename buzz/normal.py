port requests

url = 'http://www.google.com'

try:
    response = requests.get(url)
    print(response.text)
except requests.exceptions.RequestException as e:
    print(f"Error: {e}")