printf "Welcome to the Number Guessing Game!\n"
printf "Please enter the target number: "
read target

begin=1
end=10
guess=0

guess_number() {
    printf "Please enter a number between $begin and $end: "
    read guess
}

while [ $guess -ne $target ]; do
    guess_number;
    if [ "$guess" -lt "$target" ]; then
        begin=$guess
    elif [ "$target" -lt "$guess" ]; then
        end=$guess
    else
        printf "Bingo!\n"
    fi
done
