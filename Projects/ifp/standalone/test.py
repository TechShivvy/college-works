from crontab import CronTab

# Replace this list with your [hh, mm] pairs
time_pairs = [
    [11, 30],
    [12, 0],
    [23, 15],
]

# Initialize the cron tab
cron = CronTab(user='cse1100')  # Replace 'your_username' with your actual username

cron.remove_all()
# Define the command to run
command = 'echo hello world'

# Iterate through the time pairs and add cron jobs
for hh, mm in time_pairs:
    job = cron.new(command=command)
    job.setall(f'{mm} {hh} * * *')  # Set the minute and hour
    job.enable()

# Write the cron jobs to the crontab
cron.write()

