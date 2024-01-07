import os
import datetime
import requests

if not os.path.exists('./logs'):
    os.makedirs('./logs')

today = datetime.datetime.now().strftime('%Y-%m-%d')
log_filename = f'./logs/{today}.log'

if not os.path.exists(log_filename):
    with open(log_filename, 'w'): pass

if not os.path.exists('./no-network.sys'):
    location_data = requests.get('https://am.i.mullvad.net/json').json()

    latitude = location_data.get('latitude', 'Error')
    longitude = location_data.get('longitude', 'Error')
    city = location_data.get('city', 'Error')
    country = location_data.get('country', 'Error')
    organization = location_data.get('organization', 'Error')

    log_data = input('> ')

    log_entry = f"{datetime.datetime.now()}\n\tHeader:\n\t\tCoordinates: {latitude}, {longitude}\n\t\tNamed location: {city}, {country}\n\t\tTelecom provider: {organization}\n\tBody:\n\t\t{log_data}\n\n"
else:
    log_data = input('> ')

    log_entry = f"{datetime.datetime.now()}\n\tHeader:\n\t\tCoordinates: Network Disabled\n\t\tNamed location: Network Disabled\n\t\tTelecom provider: Network Disabled\n\tBody:\n\t\t{log_data}\n\n"

with open(log_filename, 'a') as f:
    f.write(log_entry)