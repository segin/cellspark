#!/bin/bash

# Function to display cellular info
display_info() {
    # Get data from termux-telephony-deviceinfo and parse with jq
    info=$(termux-telephony-deviceinfo)
    network_operator_name=$(echo "$info" | jq -r '.network_operator_name')
    network_type=$(echo "$info" | jq -r '.network_type')
    data_state=$(echo "$info" | jq -r '.data_state')
    data_activity=$(echo "$info" | jq -r '.data_activity')

    # Get terminal dimensions
    rows=$(tput lines)
    cols=$(tput cols)

    # Clear the screen
    clear

    # Print the information in the center of the screen
    tput cup $((rows / 2 - 2)) $(((cols - 20) / 2))
    echo "Cellular Information"
    tput cup $((rows / 2 - 1)) $(((cols - 20) / 2))
    echo "===================="
    tput cup $((rows / 2)) $(((cols - 30) / 2))
    echo "Operator: $network_operator_name"
    tput cup $((rows / 2 + 1)) $(((cols - 30) / 2))
    echo "Network Type: $network_type"
    tput cup $((rows / 2 + 2)) $(((cols - 30) / 2))
    echo "Data State: $data_state"
    tput cup $((rows / 2 + 3)) $(((cols - 30) / 2))
    echo "Data Activity: $data_activity"
    tput cup $((rows - 1)) 0
    echo "Press 'q' to quit"
}

# Main loop
while true; do
    display_info
    # Read user input with a timeout of 1 second
    read -t 1 -n 1 key
    if [[ $key == "q" ]]; then
        break
    fi
done

# Clear the screen on exit
clear
