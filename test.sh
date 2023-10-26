#!/bin/bash

Help()
{
    echo "Usage : test.sh \$(root-folder)"
    echo "Root folder must contain:"
    echo -e "\t- main.cpp which will be compiled and used to run tests"
    echo -e "\t- test/ containing input/ and output/ such that"
    echo -e "\t  each input/*.txt matches the corresponding output/*.txt"
}

Cleanup()
{
    if [ -d temp_output_dir ];
    then
        rm -r temp_output_dir
    fi

    if [ -f $1/a.out ];
    then
        rm $1/a.out
    fi
}

CleanupSucess()
{
    Cleanup
    exit 0
}

CleanupFailure()
{
    Cleanup
    exit 1
}

if [ $# -ne 1 ];
then
    Help;
else
    
    if g++ $1/main.cpp -o $1/a.out;
    then
        echo "*************Compiling main.cpp succeeded!**************";
    else
        echo "***************Compiling main.cpp failed!***************";
        echo "************************Aborting************************";
        CleanupFailure;
    fi

    if [ -d $1/test/input ] && [ -d $1/test/output ];
    then

        # fresh initialize temp_output_dir
        if [ -d temp_output_dir ];
        then
            rm -r temp_output_dir;
        fi
        mkdir temp_output_dir;

        # testing loop
        for input_file in $1/test/input/*.txt
        do
            if [ -f "$input_file" ];
            then
                basename="$(basename $input_file)";
                $1/a.out < "$input_file" > "temp_output_dir/$basename";

                if [ -f "$1/test/output/$basename" ]; 
                then
                    if diff "temp_output_dir/$basename" "$1/test/output/$basename" > /dev/null;
                    then
                        echo -e "Test $basename : \033[0;32mpassed!\033[0m";
                    else
                        echo -e "Test $basename : \033[0;31mfailed!\033[0m";
                    fi
                else
                    echo -e "Test $basename : \033[1;33mno output!\033[0m";
                fi
            fi
        done
        CleanupSucess
    else
        echo "***********$1 is not a valid testing directory**********";
        CleanupFailure;
    fi
    
fi