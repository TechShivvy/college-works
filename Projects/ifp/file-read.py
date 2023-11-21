# access_variables.py

with open('values.txt', 'r') as file:
    variables = {}
    for line in file:
        key, value = line.strip().split('=')
        variables[key] = value

# Use variables['variable1'] and variables['variable2'] as needed
print(variables['WEIGHT'])
print(variables['PERCENT'])
