def file_read():
    # access_variables.py

    with open('values.txt', 'r') as file:
        variables = {}
        for line in file:
            key, value = line.strip().split('=')
            variables[key] = value

    # Use variables['WEIGHT'] and variables['PERCENT'] as needed
    print(variables['WEIGHT'])
    print(variables['PERCENT'],end="\n\n")
    
    return variables

def file_write(weight=-1, percent=-1):
    print("Old:")
    current_values = file_read()

    # Update variables only if weight or percent is not -1
    if weight != -1:
        current_values['WEIGHT'] = str(weight)
    if percent != -1:
        current_values['PERCENT'] = str(percent)

    # Write updated variables back to the file
    with open('values.txt', 'w') as file:
        for key, value in current_values.items():
            file.write(f'{key}={value}\n')
    
    print("Updated:")
    file_read() #Updated


file_write(weight=-1, percent=10)   #Write


