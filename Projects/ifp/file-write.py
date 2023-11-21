with open('values.txt', 'r') as file:
    lines = file.readlines()

# Update variables as needed
lines[0] = 'WEIGHT=new_value1\n'
lines[1] = 'PERCENT=new_value2\n'

with open('values.txt', 'w') as file:
    file.writelines(lines)
